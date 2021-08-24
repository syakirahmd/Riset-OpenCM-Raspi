/*******************************************************************************
* Copyright 2016 ROBOTIS CO., LTD.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#include <Dynamixel2Arduino.h>
#define DXL_SERIAL   Serial3 //OpenCM9.04 EXP Board's DXL port Serial. (Serial1 for the DXL port on the OpenCM 9.04 board)
#define DEBUG_SERIAL Serial
const uint8_t DXL_DIR_PIN = 22; //OpenCM9.04 EXP Board's DIR PIN. (28 for the DXL port on the OpenCM 9.04 board)
/* syncWrite
  DYNAMIXEL PROTOCOL 1.0 supports Control Table address up to 255.
  Structures containing the necessary information to process the 'syncWrite' packet.
  typedef struct XELInfoBulkWrite{
    uint16_t addr;
    uint16_t addr_length;
    uint8_t* p_data;
    uint8_t id;
  } __attribute__((packed)) XELInfoBulkWrite_t;
  typedef struct InfoBulkWriteInst{
    XELInfoBulkWrite_t* p_xels;
    uint8_t xel_count;
    bool is_info_changed;
    InfoSyncBulkBuffer_t packet;
  } __attribute__((packed)) InfoBulkWriteInst_t;
*/

uint8_t SPEEDAX1 = 30;
uint8_t SPEEDAX2 = 300;
const uint8_t BROADCAST_ID = 254;
const float DYNAMIXEL_PROTOCOL_VERSION = 1.0;
const uint8_t DXL_ID_CNT = 2;
const uint8_t DXL_ID_LIST[DXL_ID_CNT] = {1, 2};
const uint16_t user_pkt_buf_cap = 128;
uint8_t user_pkt_buf[user_pkt_buf_cap];
const uint16_t SW_START_ADDR = 30; //Goal position
const uint16_t SW_ADDR_LEN = 2;
typedef struct sw_data{
  int32_t goal_posisiAX;
} __attribute__((packed)) sw_data_t;

sw_data_t sw_data[DXL_ID_CNT];
DYNAMIXEL::InfoSyncWriteInst_t sw_infos;
DYNAMIXEL::XELInfoSyncWrite_t info_xels_sw[DXL_ID_CNT];

Dynamixel2Arduino dxl(DXL_SERIAL, DXL_DIR_PIN);
using namespace ControlTableItem;

void setup() {
  uint8_t i;
  pinMode(LED_BUILTIN, OUTPUT);
  DEBUG_SERIAL.begin(115200);
  dxl.begin(1000000);
  dxl.setPortProtocolVersion(DYNAMIXEL_PROTOCOL_VERSION);
  
  for(i=0; i<DXL_ID_CNT; i++){
    dxl.torqueOff(DXL_ID_LIST[i]);
    dxl.setOperatingMode(DXL_ID_LIST[i], OP_POSITION);
  }
  dxl.torqueOn(BROADCAST_ID);
  delay(1000);
//  dxl.write(1, 32, (uint8_t*)&SPEEDAX1, 2, 10);
//  dxl.write(2, 32, (uint8_t*)&SPEEDAX2, 2, 10);
  
  while(!Serial);//tunggu sampe buka Serial Monitor
  DEBUG_SERIAL.println("Serial Monitor Ready!");
  while(!dxl.ping());
  DEBUG_SERIAL.println("Dynamixel Ready!");
  dxl.setGoalPosition(BROADCAST_ID, 10);
  delay(1000);

  // Fill the members of structure to syncWrite using internal packet buffer
  sw_infos.packet.p_buf = nullptr;
  sw_infos.packet.is_completed = false;
  sw_infos.addr = SW_START_ADDR;
  sw_infos.addr_length = SW_ADDR_LEN;
  sw_infos.p_xels = info_xels_sw;
  sw_infos.xel_count = 0;

  sw_data[0].goal_posisiAX = 0;
  sw_data[1].goal_posisiAX = 100;
  for(i=0; i<DXL_ID_CNT; i++){
    info_xels_sw[i].id = DXL_ID_LIST[i];
    info_xels_sw[i].p_data = (uint8_t*)&sw_data[i].goal_posisiAX;
    sw_infos.xel_count++;
  }
  sw_infos.is_info_changed = true;
}

void loop() {
  static uint32_t try_count = 0;
  uint8_t i, recv_cnt;
  for(i = 0; i < DXL_ID_CNT; i++){
    sw_data[i].goal_posisiAX = 100 + sw_data[i].goal_posisiAX;
    if(sw_data[i].goal_posisiAX >= 900){
      sw_data[i].goal_posisiAX = 0;
      }
    } sw_infos.is_info_changed = true;
 
  DEBUG_SERIAL.print("\n>>>>>> Sync Instruction Test : ");
  DEBUG_SERIAL.println(try_count++);
  if(dxl.syncWrite(&sw_infos) == true){
    DEBUG_SERIAL.println("[SyncWrite] Success");
    for(i=0; i<sw_infos.xel_count; i++){
      DEBUG_SERIAL.print("  ID: ");DEBUG_SERIAL.println(sw_infos.p_xels[i].id);
      DEBUG_SERIAL.print("\t Goal Position: ");DEBUG_SERIAL.println(sw_data[i].goal_posisiAX);
    }
  }else{
    DEBUG_SERIAL.print("[SyncWrite] Fail, Lib error code: ");
    DEBUG_SERIAL.print(dxl.getLastLibErrCode());
  }
  DEBUG_SERIAL.println();
  DEBUG_SERIAL.print("ID: ");
  DEBUG_SERIAL.print(dxl.readControlTableItem(ID, 1));
  DEBUG_SERIAL.println();
  DEBUG_SERIAL.print("Present Voltage: ");
  DEBUG_SERIAL.print(dxl.readControlTableItem(PRESENT_VOLTAGE, 1));
  DEBUG_SERIAL.println();
  DEBUG_SERIAL.print("Profile velocity: ");
  DEBUG_SERIAL.print(dxl.readControlTableItem(PROFILE_VELOCITY, 1));
  DEBUG_SERIAL.println();
  DEBUG_SERIAL.print("Moving Speed: ");
  DEBUG_SERIAL.print(dxl.readControlTableItem(MOVING_SPEED, 1));
  DEBUG_SERIAL.println();
  DEBUG_SERIAL.print("Present Speed: ");
  DEBUG_SERIAL.print(dxl.readControlTableItem(PRESENT_SPEED, 1));
  DEBUG_SERIAL.println();

  delay(250);
  DEBUG_SERIAL.println("=======================================================");

  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  delay(750);
}

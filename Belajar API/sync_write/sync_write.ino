#include <Dynamixel2Arduino.h>
#define DXL_SERIAL   Serial3 //OpenCM9.04 EXP Board's DXL port Serial. (Serial1 for the DXL port on the OpenCM 9.04 board)
#define DEBUG_SERIAL Serial

using namespace ControlTableItem;
const uint8_t DXL_DIR_PIN = 22; //OpenCM9.04 EXP Board's DIR PIN. (28 for the DXL port on the OpenCM 9.04 board)
uint8_t set_speed = 1000;
uint8_t set_position = 10;
const uint8_t turn_on = 1;
const uint8_t turn_off = 0;
const float DXL_PROTOCOL_VERSION = 1.0;
Dynamixel2Arduino dxl(DXL_SERIAL, DXL_DIR_PIN);

void setup() {
  dxl.begin(1000000);
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
  while(!DEBUG_SERIAL);
  Serial.println("Serial monitor Ready!");
  while(!dxl.scan());
//######################## Set Torsi & operation mode ###############################
  dxl.torqueOff(1);
  dxl.setOperatingMode(1, OP_POSITION);
  dxl.torqueOn(1);
  dxl.torqueOff(2);
  dxl.setOperatingMode(2, OP_POSITION);
  dxl.torqueOn(2);
  Serial.println(dxl.readControlTableItem(CW_ANGLE_LIMIT, 1));
  Serial.println(dxl.readControlTableItem(CCW_ANGLE_LIMIT, 1));
  Serial.print("Goal Position: "); 
  Serial.println(dxl.readControlTableItem(GOAL_POSITION, 1));
  dxl.setGoalPosition(1, 1000);
  dxl.setGoalPosition(2, 1000);
  delay(1000);
  Serial.println("Dynamixel ready!");
  delay(1000); 
  Serial.print("Goal Position: "); 
  Serial.println(dxl.readControlTableItem(GOAL_POSITION, 1));
//###################### reg write for goal position #################################  
  Serial.println("Seting up paramaeter for dynamixel");
//  dxl.writeControlTableItem(GOAL_POSITION, 1, 512);
//  dxl.writeControlTableItem(GOAL_POSITION, 2, 512);

  dxl.regWrite(1, 30, (uint8_t*)&set_position, 2, 10);
  dxl.action(1);
  
  Serial.print("Goal Position: "); 
  Serial.println(dxl.readControlTableItem(GOAL_POSITION, 1));
  delay(3000);
  
  set_position = 200;
  dxl.regWrite(1, 30, (uint8_t*)&set_position, 2, 10);
  dxl.action(1);
//  dxl.write(1, 32, (uint8_t*)&set_speed, 1, 10);
//  dxl.setGoalPosition(254, 1000);
//  Serial.println("done seting up");
//  Serial.println(dxl.readControlTableItem(GOAL_POSITION, 1));

  Serial.print("Get Last Lib Error: ");
  Serial.println(dxl.getLastLibErrCode());
  Serial.println("________________________________________________");
  delay(5000);
//################## Goal Position Action ###############################################  
//  Serial.println("action!");
//  dxl.action(1, 10);
}

void loop() {
//  if(dxl.getPresentPosition(1)<60){
//    dxl.setGoalPosition(1, 1000);
//  }
//  if(dxl.getPresentPosition(1)>900){
//    dxl.setGoalPosition(1, 50);
//  }
  Serial.print("Goal Position: "); 
  Serial.println(dxl.readControlTableItem(GOAL_POSITION, 1));
  Serial.print("present position:");
  Serial.println(dxl.getPresentPosition(1, UNIT_RAW));
  delay(500);
}

/* TODO
 * 1. cari tau kenapa reg write gak fungsi tapi wrire control table fungsi. soalnya kalo pake control table fungsi action gak ngaruh
 * 2. pelajarin lagi fungsi2 yg lain 
 *  
 */

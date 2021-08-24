#include <Dynamixel2Arduino.h>
#define DXL_SERIAL   Serial3 //OpenCM9.04 EXP Board's DXL port Serial. (Serial1 for the DXL port on the OpenCM 9.04 board)
#define DEBUG_SERIAL Serial

using namespace ControlTableItem;
const uint8_t DXL_DIR_PIN = 22; //OpenCM9.04 EXP Board's DIR PIN. (28 for the DXL port on the OpenCM 9.04 board)
const float DXL_PROTOCOL_VERSION = 1.0;
int DXL_ID = 1;
Dynamixel2Arduino dxl(DXL_SERIAL, DXL_DIR_PIN);

void setup() {
  dxl.begin(1000000);
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
  while(!DEBUG_SERIAL);
  Serial.println("Serial monitor Ready!");
  while(!dxl.scan());
  dxl.torqueOff(DXL_ID);
  dxl.setOperatingMode(DXL_ID, OP_POSITION);
  dxl.torqueOn(DXL_ID);
  bacaEEPROM();
  dxl.setGoalPosition(DXL_ID, 1000);
}

void loop() {
  
}

void bacaEEPROM(){
  Serial.println("==============================================================================================");
  Serial.print("Model Number: ");
  Serial.println(dxl.readControlTableItem(MODEL_NUMBER, DXL_ID)); 
  Serial.print("Firmware Version: ");
  Serial.println(dxl.readControlTableItem(FIRMWARE_VERSION, DXL_ID));
  Serial.print("Dynamixel ID: ");
  Serial.println(dxl.readControlTableItem(ID, DXL_ID));
  Serial.print("Baudrate: ");
  Serial.println(dxl.readControlTableItem(BAUD_RATE, DXL_ID));  
  Serial.print("Return Delay Time: ");
  Serial.println(dxl.readControlTableItem(RETURN_DELAY_TIME, DXL_ID));
  Serial.print("CW Angle Limit: ");
  Serial.println(dxl.readControlTableItem(CW_ANGLE_LIMIT, DXL_ID));
  Serial.print("CCW Angle Limit: ");
  Serial.println(dxl.readControlTableItem(CCW_ANGLE_LIMIT, DXL_ID));
  Serial.print("Temperature Limit: ");
  Serial.println(dxl.readControlTableItem(TEMPERATURE_LIMIT, DXL_ID));
  Serial.print("Min Voltage Limit: ");
  Serial.println(dxl.readControlTableItem(MIN_VOLTAGE_LIMIT, DXL_ID));
  Serial.print("Max voltage Limit: ");
  Serial.println(dxl.readControlTableItem(MAX_VOLTAGE_LIMIT, DXL_ID));
  Serial.print("Max Torque: ");
  Serial.println(dxl.readControlTableItem(MAX_TORQUE, DXL_ID));
  Serial.print("Status Return Level: ");
  Serial.println(dxl.readControlTableItem(STATUS_RETURN_LEVEL, DXL_ID));
  Serial.print("Alarm LED: ");
  Serial.println(dxl.readControlTableItem(ALARM_LED, DXL_ID));
  Serial.print("Shutdown: ");
  Serial.println(dxl.readControlTableItem(SHUTDOWN, DXL_ID));
  Serial.print("CW Compliance Margin: ");
  Serial.println(dxl.readControlTableItem(CW_COMPLIANCE_MARGIN, DXL_ID));
  Serial.print("CCW Compliance Margin: ");
  Serial.println(dxl.readControlTableItem(CCW_COMPLIANCE_MARGIN, DXL_ID));
  Serial.print("CW Compliance Slope: ");
  Serial.println(dxl.readControlTableItem(CW_COMPLIANCE_SLOPE, DXL_ID));
  Serial.print("CCW Compliance Slope: ");
  Serial.println(dxl.readControlTableItem(CCW_COMPLIANCE_SLOPE, DXL_ID));  
  Serial.print("Goal Position: "); 
  Serial.println(dxl.readControlTableItem(GOAL_POSITION, DXL_ID));
  Serial.print("Moving Speed: "); 
  Serial.println(dxl.readControlTableItem(MOVING_SPEED, DXL_ID));
  Serial.print("Torque Limit: "); 
  Serial.println(dxl.readControlTableItem(TORQUE_LIMIT, DXL_ID));
  Serial.print("Present Position: "); 
  Serial.println(dxl.readControlTableItem(PRESENT_POSITION, DXL_ID));  
  Serial.print("Present Speed: "); 
  Serial.println(dxl.readControlTableItem(PRESENT_SPEED, DXL_ID));
  Serial.print("Present Load: "); 
  Serial.println(dxl.readControlTableItem(PRESENT_LOAD, DXL_ID));  
  Serial.print("Present Vlotage: "); 
  Serial.println(dxl.readControlTableItem(PRESENT_VOLTAGE, DXL_ID));
  Serial.print("Present Temperature: "); 
  Serial.println(dxl.readControlTableItem(PRESENT_TEMPERATURE, DXL_ID));
  Serial.print("Registered: "); 
  Serial.println(dxl.readControlTableItem(REGISTERED, DXL_ID));
  Serial.print("Moving Status: "); 
  Serial.println(dxl.readControlTableItem(MOVING, DXL_ID));
  Serial.print("Lock Status: "); 
  Serial.println(dxl.readControlTableItem(LOCK, DXL_ID));
  Serial.print("Punch: "); 
  Serial.println(dxl.readControlTableItem(PUNCH, DXL_ID));
}

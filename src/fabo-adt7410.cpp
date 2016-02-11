#include "fabo-adt7410.h"

bool FaBoTemperature::searchDevice()
{
  byte device = 0x00;
  readI2c(ADT7410_WHO_AM_I_REG, 1, &device);
  
  if((device & ADT7410_DEVICE) == ADT7410_DEVICE){
    return true;
  } else {
    return false;
  }
}

void FaBoTemperature::configure()
{
  byte conf = ADT7410_16BIT_RESOLUTIION;
  conf |= ADT7410_16BIT_OP_MODE_1FAULT;
  conf |= ADT7410_CT_LOW;
  conf |= ADT7410_INT_LOW;
  conf |= ADT7410_INTERRUPT_MODE;
  conf |= ADT7410_OP_MODE_CONTINUOUS;

  writeI2c(ADT7410_CONFIGURATION_REG, conf); 
}

float FaBoTemperature::readTemperature()
{
  byte buffer[2];
  uint16_t val;
  float tmp;
  long  l_val;
  
  readI2c(ADT7410_TEMP_MSB_REG, 2,  buffer);

  val = (uint16_t)buffer[0] << 8;  
  val |= buffer[1];               

  l_val = (long)val;
  if(val & 0x8000) {         // 符号の判定    
    l_val = l_val - 65536;   // マイナスの場合
  }

  tmp = (float)l_val * 0.0078125;   // ival / 128

  return tmp;
}

// I2Cへの書き込み
void FaBoTemperature::writeI2c(byte register_addr, byte value) {
  Wire.begin();       // I2Cの開始
  Wire.beginTransmission(ADT7410_SLAVE_ADDRESS);  
  Wire.write(register_addr);         
  Wire.write(value);                 
  Wire.endTransmission();        
}

// I2Cへの読み込み
void FaBoTemperature::readI2c(byte register_addr, int num, byte buffer[]) {
  Wire.begin();       // I2Cの開始
  Wire.beginTransmission(ADT7410_SLAVE_ADDRESS); 
  Wire.write(register_addr);           
  Wire.endTransmission();         

  Wire.beginTransmission(ADT7410_SLAVE_ADDRESS); 
  Wire.requestFrom(ADT7410_SLAVE_ADDRESS, num);   

  int i = 0;
  while(Wire.available())        
  { 
    buffer[i] = Wire.read();   
    i++;
  }
  Wire.endTransmission();         
}

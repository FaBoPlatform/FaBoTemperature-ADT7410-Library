/**
 * @file  fabo-adt7410.cpp
 * @brief fabo libtary of ADT7410
 * @author Akira Sasaki
 * @date 2,10, 2016
 */
 #include "fabo-adt7410.h"

 /**
  * @brief Serch Device ADT7410
  * @retval true  : Found
  * @retval false : Not Found
  */
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

/**
 * @brief Set Config
 */
void FaBoTemperature::configure()
{
  byte conf = ADT7410_16BIT_RESOLUTION;
  conf |= ADT7410_16BIT_OP_MODE_1FAULT;
  conf |= ADT7410_CT_LOW;
  conf |= ADT7410_INT_LOW;
  conf |= ADT7410_INTERRUPT_MODE;
  conf |= ADT7410_OP_MODE_CONTINUOUS;

  writeI2c(ADT7410_CONFIGURATION_REG, conf);
}

/**
 * @brief Read Temperature
 * @return float : Temperature value
 */
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

/**
 * @brief Write I2C Data
 * @param [in] register_addr : Write Register Address
 * @param [in] value  : Write Data
 */
void FaBoTemperature::writeI2c(byte register_addr, byte value) {
  Wire.begin();
  Wire.beginTransmission(ADT7410_SLAVE_ADDRESS);
  Wire.write(register_addr);
  Wire.write(value);
  Wire.endTransmission();
}

/**
 * @brief Read I2C Data
 * @param [in] register_addr : register address
 * @param [in] num   : Data Length
 * @param [out] *buf : Read Data
 */
void FaBoTemperature::readI2c(byte register_addr, int num, byte buffer[]) {
  Wire.begin();
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

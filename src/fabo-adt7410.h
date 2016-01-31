#include "Arduino.h"
#include "Wire.h"

#define ADT7410_SLAVE_ADDRESS (0x48)

#define ADT7410_TEMP_MSB_REG 0x00
#define ADT7410_TEMP_LSB_REG 0x01
#define ADT7410_CONFIGURATION_REG 0x03
#define ADT7410_WHO_AM_I_REG 0x0B

#define ADT7410_DEVICE 0xC0

#define ADT7410_13BIT_RESOLUTIION 0b00000000
#define ADT7410_16BIT_RESOLUTIION 0b10000000
#define ADT7410_16BIT_OP_MODE_1FAULT 0b00000000
#define ADT7410_16BIT_OP_MODE_2FAULT 0b00100000
#define ADT7410_16BIT_OP_MODE_3FAULT 0b01000000
#define ADT7410_16BIT_OP_MODE_4FAULT 0b01100000
#define ADT7410_CT_LOW 0b00000000
#define ADT7410_CT_HIGH 0b00010000
#define ADT7410_INT_LOW 0b00000000
#define ADT7410_INT_HIGH 0b00001000
#define ADT7410_INTERRUPT_MODE 0b00000000
#define ADT7410_COMPARATOR_MODE 0b00000100
#define ADT7410_OP_MODE_CONTINUOUS 0b00
#define ADT7410_OP_MODE_ONESHOT 0b01
#define ADT7410_OP_MODE_SPS 0b10
#define ADT7410_OP_MODE_SHUTDOWN 0b11



class adt7410
{
public:
  bool searchDevice(void);
  void configure(void);
  float readTemperature(void);
private:
  void readI2c(byte register_addr, int num, byte *buf);
  void writeI2c(byte register_addr, byte value);
};

extern adt7410 faboTemperature;

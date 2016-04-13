/**
 * @file  fabo-adt7410.h
 * @brief fabo libtary of ADT7410
 * @author Akira Sasaki
 * @date 2,10, 2016
 */
#include "Arduino.h"
#include "Wire.h"

/** adt7410 Slave Address register */
#define ADT7410_SLAVE_ADDRESS (0x48)
/** Who_am_i register */
#define ADT7410_WHO_AM_I_REG 0x0B
/** Device check register */
#define ADT7410_DEVICE 0xC0

/** Temp Data(MSB) register */
#define ADT7410_TEMP_MSB_REG 0x00
/** Temp Data(LSB) register */
#define ADT7410_TEMP_LSB_REG 0x01
/** Config register */
#define ADT7410_CONFIGURATION_REG 0x03

/** Config Resolution : 13 bit */
#define ADT7410_13BIT_RESOLUTION 0b00000000
/** Config Resolution : 16 bit */
#define ADT7410_16BIT_RESOLUTION 0b10000000

/** Config Operation mode : continuous */
#define ADT7410_OP_MODE_CONTINUOUS 0b00000000
/** Config Operation mode : oneshot */
#define ADT7410_OP_MODE_ONESHOT 0b00100000
/** Config Operation mode : 1 SPS mode */
#define ADT7410_OP_MODE_SPS 0b01000000
/** Config Operation mode : shutdown */
#define ADT7410_OP_MODE_SHUTDOWN 0b01100000

/** Config INT/CT mode : interrupt */
#define ADT7410_INTERRUPT_MODE  0b00000000
/** Config INT/CT mode : comparator mode */
#define ADT7410_COMPARATOR_MODE 0b00010000

/** Config INT pin polarity : active low */
#define ADT7410_INT_LOW  0b00000000
/** Config INT pin polarity : active high */
#define ADT7410_INT_HIGH 0b00001000

/** Config CT pin polarity : active low */
#define ADT7410_CT_LOW  0b00000000
/** Config CT pin polarity : active high */
#define ADT7410_CT_HIGH 0b00000100

/** Config Fault queue : 1Fault */
#define ADT7410_16BIT_OP_MODE_1FAULT 0b00
/** Config Fault queue : 2Fault */
#define ADT7410_16BIT_OP_MODE_2FAULT 0b01
/** Config Fault queue : 3Fault */
#define ADT7410_16BIT_OP_MODE_3FAULT 0b10
/** Config Fault queue : 4Fault */
#define ADT7410_16BIT_OP_MODE_4FAULT 0b11

/**
 * @class FaBoTemperature
 * @brief ADT7410 Control
 */
class FaBoTemperature
{
public:
	bool searchDevice(void);
	void configure(void);
	float readTemperature(void);
private:
	void writeI2c(byte register_addr, byte value);
	void readI2c(byte register_addr, int num, byte *buf);
};

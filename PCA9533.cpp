#if 1
__asm volatile ("nop");
#endif

#include "PCA9533.h"

//    CONSTRUCTOR
PCA9533::PCA9533() {
//    _comBuffer = ping();
}

//    DESTRUCTOR
PCA9533::~PCA9533() {}

//    PING (0 = Success, other = Error code) details in ReadMe
byte PCA9533::ping() {
  Wire.beginTransmission(DEV_ADDR);
  return Wire.endTransmission();
}

bool PCA9533::init() {
  setReg(REG_PSC0, 0x00);
  setReg(REG_PSC1, 0x00);
  setReg(REG_PWM0, 0x00);
  setReg(REG_PWM1, 0x00);
  setReg(REG_LED, port_setting);
  return true;
}

//    SET REGISTER DATA
void PCA9533::setReg(reg_ptr_t regPtr, byte newSetting) {
    if (regPtr > 0) {
        initCall(regPtr);
        Wire.write(newSetting);
        endCall();
    }
}

//    INITIATE I2C COMMUNICATION
void PCA9533::initCall(reg_ptr_t regPtr) {
    Wire.beginTransmission(DEV_ADDR);
    Wire.write(regPtr);
}

//    SET MODE - Requires pin and mode to set. See header for details
// 	  Parameters IOx & LED_MODE_x (See header file)
void PCA9533::setMode(pin_t pin, led_out_mode_t newMode) {
    byte bit_mask;
    bit_mask = (3<<pin);
    port_setting = (port_setting & (~bit_mask)) | (newMode<<pin);
    setReg(REG_LED, port_setting);
}

//    SET MODE FOR ALL PINS :: Parameters ALL_ON | ALL_OFF
void PCA9533::setMode(mode_t newMode) {
    setReg(REG_LED, newMode);
}

//    SET PWM Registers :: Parameters REG_PWM0 | REG_PWM1
void PCA9533::setPWM(reg_ptr_t pwmPort, int pwmValue) {
	setReg(pwmPort, pwmValue);
}

//    SET PSC Registers :: Parameters REG_PSC0 | REG_PSC1
void PCA9533::setPSC(reg_ptr_t pscPort, int pscValue) {
	setReg(pscPort, pscValue);
}

//    STOP I2C COMMUNICATION
void PCA9533::endCall() {
    _comBuffer = Wire.endTransmission();
}

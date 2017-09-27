/*
  PCA9533 - Library for esp8266
  Copyright (c) 2017 Max Schmid. All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#if 1
__asm volatile ("nop");
#endif

#include "PCA9533.h"

//    CONSTRUCTOR
PCA9533::PCA9533() {
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

//    SET MODE - Requires pin and mode to set.
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

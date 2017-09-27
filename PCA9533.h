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

#ifndef PCA9533_h
#define PCA9533_h
//#endif

//#if !defined(ARDUINO_ARCH_AVR)
//#error “The PCA9533 library only supports AVR processors.”
//#endif

#include <Arduino.h>
#include "Wire.h"

namespace Pca9533 {
    const byte DEV_ADDR         = 0x62;
//    const byte NUM_BYTES        = 0x01;
//    const byte ALL_INPUT        = 0xFF;
//    const byte ALL_OUTPUT       = 0x00;
    const byte ALL_LOW          = 0x00;
    const byte ALL_HIGH         = 0xFF;
//    const byte ALL_NON_INVERTED = 0x00;
//    const byte ALL_INVERTED     = 0xFF;
    const byte COM_SUCCESS      = 0x00;

    typedef enum:byte {
        REG_INPUT    = 0,      // default
        REG_OUTPUT   = 1,
        REG_POLARITY = 2,
        REG_CONFIG   = 3
    } reg_ptr_t;

    typedef enum:byte {
        IO0 = 0,
        IO1 = 1,
        IO2 = 2,
        IO3 = 3
    } pin_t;

    typedef enum:byte {
        IO_OUTPUT = 0,
        IO_INPUT  = 1
    } mode_t;

    typedef enum:byte {
        IO_LOW  = 0,
        IO_HIGH = 1
    } state_t;

    typedef enum:byte {
        IO_NON_INVERTED = 0,
        IO_INVERTED     = 1
    } polarity_t;

    class PCA9533 {
         public:
            PCA9533();
            ~PCA9533();
            byte ping();
            void endCall();
    };
}

using namespace Pca9533;

#endif


/*
  Collection of I2C routines used in the PackMonitor project.
  (C) 2022 Gordon "gordonthree" McLellan
  Created August, 2022
*/

#pragma once
#ifndef packmonlib_h
#define packmonlib_h

#include <Arduino.h>
#include <Wire.h>

class PackMonLib {
    public:
        PackMonLib();

        void     i2cWriteUL(uint8_t slaveAddress, uint8_t cmdAddress, uint32_t cmdData) ;
        float    i2cReadF(uint8_t slaveAddress, uint8_t cmdAddress) ;
        uint32_t i2cReadUL(uint8_t slaveAddress, uint8_t cmdAddress);
        long     i2cReadI(int slaveAddress, int cmdAddress);

        float    i2cReadFloat(int slaveAddress, int cmdAddress);
        uint32_t i2cReadUlong(int slaveAddress, int cmdAddress);
        void     i2cWriteFloat(int slaveAddress, int cmdAddress, float cmdData) ;
        void     i2cWriteUlong(int slaveAddress, int cmdAddress, uint32_t cmdData);

    private:
        union ulongArray
        {
            uint32_t longNumber=0;
            uint8_t  byteArray[4];
        };

        union floatArray
        {
            float   floatNumber=0.0;
            uint8_t byteArray[4];
        };


};

#endif

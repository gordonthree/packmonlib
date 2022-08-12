/*
  Collection of I2C routines used in the PackMonitor project.
  (C) 2022 Gordon "gordonthree" McLellan
  Created August, 2022
*/

#pragma once
#ifndef packmonlib
#define packmonlib_h

#include <Arduino.h>
#include <Wire.h>

class PackMonLib {
    public:
        PackMonLib();

        double   i2cReadDouble (int slaveAddress, int cmdAddress);
        uint32_t i2cReadUlong  (int slaveAddress, int cmdAddress);
        int32_t  i2cReadLong   (int slaveAddress, int cmdAddress);
        uint8_t  i2cReadByte   (int slaveAddress, int cmdAddress);

        void     i2cWriteFloat(int slaveAddress, int cmdAddress, double cmdData) ;
        void     i2cWriteUlong(int slaveAddress, int cmdAddress, uint32_t cmdData);
        void     i2cWriteLong (int slaveAddress, int cmdAddress, int32_t cmdData);
        void     i2cWriteByte (int slaveAddress, int cmdAddress, uint8_t cmdData);
        
    private:
        union ulongArray
        {
            uint32_t longNumber=0;
            uint8_t  byteArray[4];
        } ubuffer;

        union longArray
        {
            int32_t  longNumber=0;
            uint8_t  byteArray[4];
        } lbuffer;

        union doubleArray
        {
            double  floatNumber=0.0;
            uint8_t byteArray[4];
        } dbuffer;


};

#endif

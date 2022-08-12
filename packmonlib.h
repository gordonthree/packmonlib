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

        double   readDouble (int slaveAddress, int cmdAddress);
        uint32_t readUlong  (int slaveAddress, int cmdAddress);
        int32_t  readLong   (int slaveAddress, int cmdAddress);
        uint8_t  readByte   (int slaveAddress, int cmdAddress);

        void     writeDouble(int slaveAddress, int cmdAddress, double cmdData) ;
        void     writeUlong (int slaveAddress, int cmdAddress, uint32_t cmdData);
        void     writeLong  (int slaveAddress, int cmdAddress, int32_t cmdData);
        void     writeByte  (int slaveAddress, int cmdAddress, uint8_t cmdData);
        
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

        const uint8_t writeBytes = 4;
        const uint8_t readBytes  = 4;

};

#endif

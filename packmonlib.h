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

        double   readDouble (int clientAddress, int cmdAddress);
        uint32_t readUlong  (int clientAddress, int cmdAddress);
        int32_t  readLong   (int clientAddress, int cmdAddress);
        uint8_t  readByte   (int clientAddress, int cmdAddress);

        void     writeDouble(int clientAddress, int cmdAddress, double cmdData) ;
        void     writeUlong (int clientAddress, int cmdAddress, uint32_t cmdData);
        void     writeLong  (int clientAddress, int cmdAddress, int32_t cmdData);
        void     writeByte  (int clientAddress, int cmdAddress, int8_t cmdData);
        
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

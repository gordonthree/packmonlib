/*
  Collection of I2C routines used in the PackMonitor project.
  (C) 2022 Gordon "gordonthree" McLellan
  Created August, 2022
*/

#include <Arduino.h>
#include <Wire.h>
#include "packmonlib.h"

PackMonLib::PackMonLib() {
  // constructor does nothing
};

float PackMonLib::i2cReadFloat(int slaveAddress, int cmdAddress) {
  union floatArray buffer;
  const char stopChar = '\0';
  const uint8_t readBytes = 4;
  Wire.beginTransmission(slaveAddress);                          // start transaction
  Wire.write(cmdAddress);                                        // tell slave we want to read this register
  Wire.endTransmission(false);                                   // send instruction, retain control of bus
  Wire.requestFrom(slaveAddress, readBytes, (bool) true);        // request 6 bytes from slave device and then release bus
  Wire.readBytesUntil(stopChar, buffer.byteArray , readBytes);    // read five bytes or until the first null

  return buffer.floatNumber;
}

uint32_t PackMonLib::i2cReadUlong(int slaveAddress, int cmdAddress) {
  union ulongArray buffer;
  const char stopChar = '\0';
  const uint8_t readBytes = 4;
  Wire.beginTransmission(slaveAddress);                          // start transaction
  Wire.write(cmdAddress);                                        // tell slave we want to read this register
  Wire.endTransmission(false);                                   // send instruction, retain control of bus
  Wire.requestFrom(slaveAddress, readBytes, (bool) true);        // request 6 bytes from slave device and then release bus
  Wire.readBytesUntil(stopChar, buffer.byteArray , readBytes);    // read five bytes or until the first null

  return buffer.longNumber;
}

int32_t PackMonLib::i2cReadLong(int slaveAddress, int cmdAddress) {
  union longArray buffer;
  const char stopChar = '\0';
  const uint8_t readBytes = 4;
  Wire.beginTransmission(slaveAddress);                          // start transaction
  Wire.write(cmdAddress);                                        // tell slave we want to read this register
  Wire.endTransmission(false);                                   // send instruction, retain control of bus
  Wire.requestFrom(slaveAddress, readBytes, (bool) true);        // request 6 bytes from slave device and then release bus
  Wire.readBytesUntil(stopChar, buffer.byteArray , readBytes);    // read five bytes or until the first null

  return buffer.longNumber;
}

uint8_t PackMonLib::i2cReadByte(int slaveAddress, int cmdAddress) {
  const char stopChar = '\0';
  const uint8_t readBytes = 1;
  uint8_t byteArray[4] = {0,0,0,0};
  uint8_t result = 0;
  Wire.beginTransmission(slaveAddress);                          // start transaction
  Wire.write(cmdAddress);                                        // tell slave we want to read this register
  Wire.endTransmission(false);                                   // send instruction, retain control of bus
  Wire.requestFrom(slaveAddress, readBytes, (bool) true);        // request 6 bytes from slave device and then release bus
  result = Wire.read();
  // Wire.readBytesUntil(stopChar, byteArray , readBytes);    // read five bytes or until the first null

  return result;
}
void PackMonLib::i2cWriteFloat(int slaveAddress, int cmdAddress, float cmdData) {
  union floatArray buffer;
  const uint8_t writeBytes = 4;
  buffer.floatNumber = cmdData;                       // convert float into byte array 
  Wire.beginTransmission(slaveAddress);               // begin transaction with slave address
  Wire.write(cmdAddress);                                 // tell slave we want to read this register
  Wire.write(buffer.byteArray, writeBytes);           // write bytes to buffer
  Wire.endTransmission(true);                         // send data
}

void PackMonLib::i2cWriteUlong(int slaveAddress, int cmdAddress, uint32_t cmdData) {
  union ulongArray buffer;                      // data conversion union
  const uint8_t writeBytes = 4;                 // it's always 4 bytes
  buffer.longNumber = cmdData;                  // convert ulong into byte array 
  Wire.beginTransmission(slaveAddress);         // begin transaction with slave address
  Wire.write(cmdAddress);                       // tell slave we want to read this register
  Wire.write(buffer.byteArray, writeBytes);     // write bytes to buffer
  Wire.endTransmission(true);                   // send data
}  
                    
void PackMonLib::i2cWriteLong(int slaveAddress, int cmdAddress, int32_t cmdData) {
  union longArray buffer;                      // data conversion union
  const uint8_t writeBytes = 4;                 // it's always 4 bytes
  buffer.longNumber = cmdData;                  // convert ulong into byte array 
  Wire.beginTransmission(slaveAddress);         // begin transaction with slave address
  Wire.write(cmdAddress);                       // tell slave we want to read this register
  Wire.write(buffer.byteArray, writeBytes);     // write bytes to buffer
  Wire.endTransmission(true);                   // send data
}  

void PackMonLib::i2cWriteByte(int slaveAddress, int cmdAddress, uint8_t cmdData) {
  uint8_t byteArray[4] = {0,0,0,0};
  const uint8_t writeBytes = 1;                 // it's always 4 bytes
  byteArray[0] = cmdData;
  Wire.beginTransmission(slaveAddress);         // begin transaction with slave address
  Wire.write(cmdAddress);                       // tell slave we want to read this register
  Wire.write(byteArray, writeBytes);     // write bytes to buffer
  Wire.endTransmission(true);                   // send data
}  
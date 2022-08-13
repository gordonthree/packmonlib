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

double PackMonLib::readDouble(int clientAddress, int cmdAddress) { // rad four bytes return float
  Wire.beginTransmission(clientAddress);                           // start transaction
  Wire.write(cmdAddress);                                          // tell slave we want to read this register
  Wire.endTransmission(false);                                     // send instruction, retain control of bus
  Wire.requestFrom(clientAddress, readBytes, (bool) true);         // request 6 bytes from slave device and then release bus
  Wire.readBytes(dbuffer.byteArray, readBytes);                    // read five bytes or until the first null

  return dbuffer.floatNumber;
}

uint32_t PackMonLib::readUlong(int clientAddress, int cmdAddress) { // read four bytes return Ulong
  Wire.beginTransmission(clientAddress);                            // start transaction
  Wire.write(cmdAddress);                                           // tell slave we want to read this register
  Wire.endTransmission(false);                                      // send instruction, retain control of bus
  Wire.requestFrom(clientAddress, readBytes, (bool) true);          // request 6 bytes from slave device and then release bus
  Wire.readBytes(ubuffer.byteArray, readBytes);                     // read five bytes or until the first null

  return ubuffer.longNumber;
}

int32_t PackMonLib::readLong(int clientAddress, int cmdAddress) { // read four bytes return long
  Wire.beginTransmission(clientAddress);                          // start transaction
  Wire.write(cmdAddress);                                         // tell slave we want to read this register
  Wire.endTransmission(false);                                    // send instruction, retain control of bus
  Wire.requestFrom(clientAddress, readBytes, (bool) true);        // request 6 bytes from slave device and then release bus
  Wire.readBytes(lbuffer.byteArray, readBytes);                   // read five bytes or until the first null

  return lbuffer.longNumber;
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

void PackMonLib::writeUlong(int clientAddress, int cmdAddress, uint32_t cmdData) {
  ubuffer.longNumber = cmdData;                                   // convert ulong into byte array 
  Wire.beginTransmission(clientAddress);                          // begin transaction with slave address
  Wire.write(cmdAddress);                                         // tell slave we want to read this register
  Wire.write(ubuffer.byteArray, writeBytes);                      // write bytes to buffer
  Wire.endTransmission(true);                                     // send data
}  
                    
void PackMonLib::writeLong(int clientAddress, int cmdAddress, int32_t cmdData) {
  lbuffer.longNumber = cmdData;                                   // convert ulong into byte array 
  Wire.beginTransmission(clientAddress);                          // begin transaction with slave address
  Wire.write(cmdAddress);                                         // tell slave we want to read this register
  Wire.write(lbuffer.byteArray, writeBytes);                      // write bytes to buffer
  Wire.endTransmission(true);                                     // send data
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
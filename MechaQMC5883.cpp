#include "MechaQMC5883.h"

#include <Wire.h>

void MechaQMC5883::setAddress(uint8_t addr){
  address = addr;
}

void MechaQMC5883::WriteReg(uint8_t Reg,uint8_t val){
  Wire.beginTransmission(address); //start talking
  Wire.write(Reg); // Tell the HMC5883 to Continuously Measure
  Wire.write(val); // Set the Register
  Wire.endTransmission();
}

void MechaQMC5883::init(){
  WriteReg(0x0B,0x01);
  //Define Set/Reset period
  //WriteReg(0x09,0x1D);

  setMode(Mode_Standby,ODR_200Hz,RNG_8G,OSR_512);
  /*
  Define
  OSR = 512
  Full Scale Range = 8G(Gauss)
  ODR = 200HZ
  set continuous measurement mode
  */
}

void MechaQMC5883::setMode(uint16_t mode,uint16_t odr,uint16_t rng,uint16_t osr){
  WriteReg(0x09,mode|odr|rng|osr);
}


void MechaQMC5883::softReset(){
  WriteReg(0x0A,0x80);
}

void read(uint16_t *x,uint16_t *y,uint16_t *z){
  Wire.requestFrom(addr, 6);
  if (6 <= Wire.available()) {
    x = Wire.read(); //LSB  x
    x |= Wire.read() << 8; //MSB  x
    y = Wire.read(); //LSB  z
    y |= Wire.read() << 8; //MSB z
    z = Wire.read(); //LSB y
    z |= Wire.read() << 8; //MSB y
  }
}
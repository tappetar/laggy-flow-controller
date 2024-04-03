/*
  Arduino Library for Serial MFC communication 

  To be used with SparkFun Transceiver Breakout - MAX3232
  https://www.sparkfun.com/products/11189

  -Rishi Tappeta
*/
#include <MFCSerial.h>

#include <inttypes.h>
#include <Wire.h>
#include "Print.h"



void MFCSerial::setFlow(float flow){
  if(flow > maxFlow){
    currentFlow = maxFlow;
    flow = 64000*maxFlow/5;
    port->print("\r\r" + unitID + (String)flow + "\r");
    return;
  }
  currentFlow = flow;
  flow = (flow/maxFlow)*64000;
  port->print("\r\r" + unitID + (String)flow + "\r");
}

void MFCSerial::setupFlow(){
  //help what is this supposed to do 
  return;
}

float MFCSerial::getFlow(){
  return currentFlow;
}

void MFCSerial::setUnitID(String ID){
  unitID = ID;
  port->print("\r\r" + unitID + "@=" + ID + "\r"); 
}

void MFCSerial::setMaxFlow(float f){
  maxFlow = f;
}




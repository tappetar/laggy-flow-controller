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

void MFCSerial::setupFlow(int baud, float max=5.0, String ID="A"){
  port.setTimeout(100);
  port.begin(38400);
  maxFlow = max;
  unitID = ID;
  port->print("\r\r" + unitID + "@=" + ID + "\r"); 
}

float MFCSerial::getFlow(){
  return currentFlow;
}



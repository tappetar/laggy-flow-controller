
MFCSerial FlowController(Serial1)

void setup(){

}

void loop(){
  Serial.println(FlowController.setFlow(1.0))
  delay(1000);
  Serial.println(FlowController.getFlow())
  delay(1000);
  Serial.println(FlowController.setFlow(2.0))
  delay(1000);
  Serial.println(FlowController.getFlow())
  delay(1000);
}
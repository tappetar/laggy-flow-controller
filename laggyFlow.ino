#include <LiquidCrystal_I2C.h>
#include <MFCSerial.h>
MFCSerial mfc1(&Serial2); //C
MFCSerial mfc2(&Serial1); //O
MFCSerial mfc3(&Serial3); //N



LiquidCrystal_I2C lcd(0x27,20,4);
String unitID = "A";
const float maxFlow = 5.0;
float adjustedFlowSet;  
float speed;
float TGas1 = 0.05;
float TGas2 = 0.05;
float Gas1 = 0;
float Gas2 = 0;
float Gas3 = 0;





void setup() {


  mfc1.setupFlow(38400, 5.0, "A");
  mfc2.setupFlow(38400, 5.0, "A");
  mfc3.setupFlow(38400, 5.0, "A");

  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(7, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(2, OUTPUT);
  digitalWrite(7, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(2, HIGH);

 
  lcd.init();
  lcd.clear();         
  lcd.backlight(); 

  lcd.setCursor(0,0); lcd.print("Sweep: ");
  lcd.setCursor(0,1); lcd.print("%C: ");
  lcd.setCursor(0,2); lcd.print("%O: ");
  lcd.setCursor(0,3); lcd.print("%N: ");
  lcd.setCursor(11,0); lcd.print("Spd: ");
  lcd.setCursor(8,1); lcd.print("C2: ");
  lcd.setCursor(8,2); lcd.print("O2: ");
  lcd.setCursor(8,3); lcd.print("N2: ");
  lcd.setCursor(15,1); lcd.print(", "); 
  lcd.setCursor(15,2); lcd.print(", "); 
  lcd.setCursor(15,3); lcd.print(", "); 




  Serial.begin(9600);

  Serial1.begin(38400);
  Serial1.setTimeout(100);

  Serial2.begin(38400);
  Serial2.setTimeout(100);

  Serial3.begin(34800);
  Serial3.setTimeout(100);

  Serial1.print("\r\r");
  Serial2.print("\r\r");
  Serial3.print("\r\r");
  

}

void loop() {
  double frac1 = map(analogRead(A3), 0, 1023, 0, 600);
  frac1 = frac1/10000;

  double frac2 = map(analogRead(A2), 0, 1023, 0, 1000);
  frac2 = frac2/1000;

  if(frac2+frac1 > 1){
    frac2 = 1.01-frac1;
  }

  double frac3 = abs(1-frac1-frac2);

  lcd.setCursor(3,1); lcd.print(frac1*100); 
  lcd.setCursor(3,2); lcd.print(frac2*100); 
  lcd.setCursor(3,3); lcd.print(frac3*100);  
  lcd.setCursor(7,2); lcd.print(" ");
 


  double sum = map(analogRead(A1),0, 1023, 5, 200);
  sum = sum/100;
  double TGas1 = frac1*sum;
  double TGas2 = frac2*sum;
  double TGas3 = frac3*sum;



  lcd.setCursor(11,1); lcd.print(TGas1); 
  lcd.setCursor(11,2); lcd.print(TGas2); 
  lcd.setCursor(11,3); lcd.print(TGas3);

  lcd.setCursor(7,3); lcd.print(" ");

  lcd.setCursor(6,0); lcd.print(sum); 
  speed = (analogRead(A4) + 50);
  lcd.setCursor(15,0); lcd.print(speed/25);

  // TGas1 = frac1*sum;
  // lcd.setCursor(6,2); lcd.print(TGas1);
  // TGas2 = sum*(1-frac1);
  // lcd.setCursor(6,3); lcd.print(TGas2);



  


  if(abs(TGas1-Gas1) > (speed/300000)){

    if(TGas1 > Gas1){
      Gas1 += speed/300000;
    }

    else{
      Gas1 -= speed/300000;
    } 

    lcd.setCursor(16,1); lcd.print(Gas1);

    adjustedFlowSet = (Gas1/maxFlow)*64000;
    Serial2.print("\r\r" + unitID + (String)adjustedFlowSet + "\r");
    //mfc1.setFlow(Gas1);

    
  }

  if(abs(TGas2-Gas2) > (speed/30000)){

    if(TGas2 > Gas2){
      Gas2 += speed/30000;
    }

    else{
      Gas2 -= speed/30000;
    } 


    lcd.setCursor(16,2); lcd.print(Gas2);

    //adjustedFlowSet = (Gas2/maxFlow)*64000;
    mfc2.setFlow(Gas2);
  }

  if(abs(TGas3-Gas3) > (speed/30000)){

    if(TGas3 > Gas3){
      Gas3 += speed/30000;
    }

    else{
      Gas3 -= speed/30000;
    } 


    lcd.setCursor(16,3); lcd.print(Gas3);

    //adjustedFlowSet = (Gas3/maxFlow)*64000;
    //Serial.println((String)adjustedFlowSet);
    //Serial3.print("\r\r" + unitID + (String)adjustedFlowSet + "\r");
    mfc3.setFlow(Gas3);
  }
    
    



  


}
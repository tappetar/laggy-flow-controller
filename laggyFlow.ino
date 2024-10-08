#include <LiquidCrystal_I2C.h>
#include <MFCSerial.h>
#include <SoftwareSerial.h>

SoftwareSerial fake3(6, 7);

MFCSerial mfc1(&Serial2); //C
MFCSerial mfc2(&Serial1); //O
MFCSerial mfc3(&fake3); //N



LiquidCrystal_I2C lcd(0x27,20,4);
String unitID = "A";
const float maxFlow = 5.0;
float adjustedFlowSet;  
float speed;
float Gas1 = 0;
float Gas2 = 0;
float Gas3 = 0;





void setup() {


  mfc1.setupFlow(38400, 5.0, "A");
  mfc2.setupFlow(38400, 5.0, "A");
  mfc3.setupFlow(38400, 5.0, "A");

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);

 
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

  fake3.begin(38400);

  Serial1.print("\r\r");
  Serial2.print("\r\r");
  Serial3.print("\r\r");
  

}

void loop() {
  
  float frac1 = map(analogRead(A2), 0, 1023, 0, 4000); // 0.01% of total sweep
  frac1 = frac1/10000.0;

  float frac2 = map(analogRead(A1), 0, 1023, 0, 10000); // 0.01% of total sweep
  frac2 = frac2/10000.0;

  if(frac2+frac1 > 1){
    frac2 = 1.0-frac1;
  }

  float frac3 = max(min(1.0-frac1-frac2,1.0),0.0);

  lcd.setCursor(3,1); lcd.print(frac1*100); 
  lcd.setCursor(3,2); lcd.print(frac2*100); 
  lcd.setCursor(3,3); lcd.print(frac3*100);  
  lcd.setCursor(7,2); lcd.print(" ");
 


  float sum = map(analogRead(A0),0, 1023, 5, 200); // 10 mL
  sum = sum/100.0;
  float TGas1 = frac1*sum;
  float TGas2 = frac2*sum;
  float TGas3 = frac3*sum;



  lcd.setCursor(11,1); lcd.print(TGas1); 
  lcd.setCursor(11,2); lcd.print(TGas2); 
  lcd.setCursor(11,3); lcd.print(TGas3);
  lcd.setCursor(7,3); lcd.print(" ");
  lcd.setCursor(6,0); lcd.print(sum); 
  speed = (analogRead(A3) + 50);
  lcd.setCursor(15,0); lcd.print(speed/25);




  


  if(abs(TGas1-Gas1) > (speed/300000)){

    if(TGas1 > Gas1){
      Gas1 += speed/300000;
    }

    else{
      Gas1 -= speed/300000;
    } 

    lcd.setCursor(16,1); lcd.print(Gas1);

    mfc1.setFlow(Gas1*10);
  }

  if(abs(TGas2-Gas2) > (speed/30000)){

    if(TGas2 > Gas2){
      Gas2 += speed/30000;
    }

    else{
      Gas2 -= speed/30000;
    } 

    lcd.setCursor(16,2); lcd.print(Gas2);

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

    mfc3.setFlow(Gas3);
  }
}

 #include <Servo.h>
#include <Wire.h>
//for the display {
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET     4
Adafruit_SSD1306 display(128, 64, &Wire, OLED_RESET);
//}

//for the ultrasonic sensor {
#define echoPin 2
#define triggerPin  10
//}

int mode;
int pot_set;
int deg;
long duration;
int distance;
//}

Servo servo1;//create servo object to control a servo
Servo servo2;//create servo object to control a servo
Servo servo3;//create servo object to control a servo
Servo servo4;//create servo object to control a servo
Servo servo5;//create servo object to control a servo

//for pot_cont {
int dataServo1 = 90; // Servo 1 rotation range(dataServo1=0~180)
int dataServo2 = 90; // Servo 2 rotation range(dataServo2=0~180) 
int dataServo3 = 90; // Servo 3 rotation range(dataServo3=0~180)
int dataServo4 = 90; // Servo 4 rotation range(dataServo4=0~180)
int dataServo5 = 90; // Servo 5 rotation range(dataServo5=35~90)

float dirServo1Offset = 0;    // define a variable for deviation(degree) of the servo
float dirServo2Offset = 0;    // define a variable for deviation(degree) of the servo
float dirServo3Offset = 0;    // define a variable for deviation(degree) of the servo
float dirServo4Offset = 0;    // define a variable for deviation(degree) of the servo
float dirServo5Offset = 0;    // define a variable for deviation(degree) of the servo
int val1;
int val2;
int val3;
int val4;
int val5;
//}
void setup() {
  servo1.attach(9);
  servo2.attach(6);
  servo3.attach(5);
  servo4.attach(3);
  servo5.attach(11);
  pinMode(4,INPUT);
  //for display {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(WHITE);
  display.clearDisplay();
  //}
  //for the ultrasonic sensor {
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  //}
  pinMode(48,INPUT);
  
  mode=1;
  pot_set=0;
}



  
    
 // Serial.print(analogRead(8));
  

 int when_buttonpress() {


  servo1.write(0);
  delay(2000);
  servo1.write(180);
  delay(2000);
  
  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
  servo4.write(90);
  servo5.write(90);
  delay(10000);
}

int ultrasonic_sensor() {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin,LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if(distance <= 8){
      if (not distance == 0){
       servo5.write(90);
      }
  } else {
    servo5.write(0);
  }
  
}

int arm_idle_pos() {
  //for servo {
  int i;
  i = ultrasonic_sensor();
  
  deg =0;
  
  servo1.write(deg);
  Serial.print("  servo1 ");
  Serial.print(deg);
  servo2.write(deg);
  Serial.print( "  servo2 ");
  Serial.print(deg);
  deg = 45;
  
  servo3.write(45);
  Serial.print("  servo3 ");
  Serial.print(deg);
  deg=90;
  servo4.write(deg);
  Serial.print("  servo4 ");
  Serial.print(deg);
  
}

int pot_setup(){
  servo1.write(dataServo1+dirServo1Offset);//goes to dataServo1 degrees 
  servo2.write(dataServo2+dirServo2Offset);//goes to dataServo2 degrees 
  servo3.write(dataServo3+dirServo3Offset);//goes to dataServo3 degrees 
  servo4.write(dataServo4+dirServo4Offset);//goes to dataServo4 degrees 
  servo5.write(dataServo5+dirServo5Offset);//goes to dataServo5 degrees 
}

int pot_cont(){
  servo1.write(dataServo1+dirServo1Offset);//goes to dataServo1 degrees 
  servo2.write(dataServo2+dirServo2Offset);//goes to dataServo2 degrees 
  servo3.write(dataServo3+dirServo3Offset);//goes to dataServo3 degrees 
  servo4.write(dataServo4+dirServo4Offset);//goes to dataServo4 degrees 
  servo5.write(dataServo5+dirServo5Offset);//goes to dataServo5 degrees 

  val1 = map(analogRead(0), 0, 1023, 0, 180);  
  val2 = map(analogRead(1), 0, 1023, 0, 180);  
  val3 = map(analogRead(2), 0, 1023, 0, 180);  
  val4 = map(analogRead(3), 0, 1023, 0, 180);
  val5 = map(analogRead(6), 0, 1023, 35, 90);  
 
  if(dataServo1>val1){dataServo1--;  }
  if(dataServo1<val1){dataServo1++;  }
  if(dataServo1>180) {dataServo1=180;}
  if(dataServo1<0)   {dataServo1=0;  }

  if(dataServo2>val2){dataServo2--;  }
  if(dataServo2<val2){dataServo2++;  }
  if(dataServo2>180) {dataServo2=180;}
  if(dataServo2<0)   {dataServo2=0;  }

  if(dataServo3>val3){dataServo3--;  }
  if(dataServo3<val3){dataServo3++;  }
  if(dataServo3>180) {dataServo3=180;}
  if(dataServo3<0)   {dataServo3=0;  }

  if(dataServo4>val4){dataServo4--;  }
  if(dataServo4<val4){dataServo4++;  }
  if(dataServo4>180) {dataServo4=180;}
  if(dataServo4<0)   {dataServo4=0;  }
  
  if(dataServo5>val5){dataServo5--;  }
  if(dataServo5<val5){dataServo5++;  }
  if(dataServo5>90) {dataServo5=90;}
  if(dataServo5<35)  {dataServo5=35; }
  delay(20);//wait for 0.05second
}
  

void loop() {
//for setting the mode
  if(digitalRead(48)==HIGH){
    mode = mode + 1;
    if(mode ==3){
      mode = 1;
    }
if(pot_set==0){
      int b;
      b = pot_setup();
      }
      int c;
      c = pot_cont();
    
    }
  
  Serial.print(digitalRead(48));
  //Set the font size
  display.setTextSize(2);
  //Set the display location
  display.setCursor(30,30);
  //String displayed
  display.print("TEST");
  //Began to show
  display.display();
  //}
   if(digitalRead(48) == LOW){
    int a;
    a = arm_idle_pos();
    
    if(digitalRead(4)==LOW){
      int y;
      y = when_buttonpress();
      }
   }
   if(mode==2){
//    if(pot_set==0){
//      int b;
//      b = pot_setup();
//      }
//      int c;
//      c = pot_cont();
//    
   }
}

#include <Keyboard.h>
#include <Mouse.h>

#define charging_PIN A0
#define analogue_PIN A1
#define SERIAL_PINA A14
#define SERIAL_PINB A15
#define SERIAL_PINC A16
#define SERIAL_PIND A17

float dataThreshold = 85;
float dataDifference = 0.0;
float sensitivity = 15;

float x1 = 0;
float x2 = 0;
float x3 = 0;
float x4 = 0;
float x5 = 0;
float x6 = 0;
float x7 = 0;
float x8 = 0;
float x9 = 0;
float xten = 0;
float x11 = 0;
float x12 = 0;
float x13 = 0;
float x14 = 0;
float x15 = 0;
float x16 = 0;

float measureValues(int charging_PIN, int analog_PIN){
  digitalWrite(charging_PIN, HIGH);//charge capacitor
  
  float analogData = analogRead(analog_PIN);
    
  //Serial.println(analogData);
  
  digitalWrite(charging_PIN, LOW);
  delay(1);
  return analogData;
}

void init_joystick (){
  Joystick.button(1, 0);
  Joystick.button(2, 0);
  Joystick.button(3, 0);
  Joystick.button(4, 0);
  Joystick.button(5, 0);
  Joystick.button(6, 0);
  Joystick.button(7, 0);
  Joystick.button(8, 0);
  Joystick.button(9, 0);
  Joystick.button(10, 0);
  Joystick.hat(-1);
  Joystick.sliderLeft(0);
  Joystick.sliderRight(0);
  Joystick.X(512);
  Joystick.Y(512);
  Joystick.Z(512);
  Joystick.Zrotate(512);
}

void needForSpeedFunction(float Up, float Down, float Left, float Right){
  if(Right > dataThreshold and Left < dataThreshold){
    dataDifference = (Right - dataThreshold)*sensitivity;
    Joystick.button(8, 1);
    Joystick.X(512 + dataDifference);//MoveRight 
    Joystick.send_now();
  }
  else if (Right < dataThreshold and Left > dataThreshold){
    dataDifference = (Left - dataThreshold)*sensitivity;
    Joystick.button(8, 1);
    Joystick.X(512-dataDifference);//MoveLeft 
    Joystick.send_now();
  }
  else{
    Joystick.X(512);//Centralize button
    Joystick.send_now();
  }
  
  if(Up > dataThreshold and Down < dataThreshold){
    dataDifference = (Up - dataThreshold)*sensitivity;
    Joystick.button(8, 1);
    Joystick.Y(512-dataDifference);//MoveUp
    Joystick.send_now();
  }
  else if(Up < dataThreshold and Down > dataThreshold){
    dataDifference = (Down - dataThreshold)*sensitivity;
    Joystick.button(8, 1);
    Joystick.Y(512+dataDifference);//MoveDown
    Joystick.send_now();
  }
  else{
    Joystick.Y(512);//Centralize button
    Joystick.send_now();
  }
  while (micros() % 200 != 0);  
}

void batmanFunction(float moveLeft, float moveRight,float Attack,float Counter){
  if(moveLeft > dataThreshold and moveRight < dataThreshold){
    Mouse.move(-50, 0, 0);
    delay(1);
  }
  
  else if(moveRight > dataThreshold and moveLeft < dataThreshold ){
    Mouse.move(50, 0, 0);
    delay(1);
  }
  else{
    Mouse.move(0,0,0);
  }
  
  if(Attack > dataThreshold){
    Mouse.click();
  }

  if(Counter > dataThreshold){
    Mouse.click(MOUSE_RIGHT);
  }
}

void transformersFunction(float Up, float Down, float Left, float Right){
  if(Right > dataThreshold and Left < dataThreshold){
    Keyboard.press(KEY_RIGHT_ARROW);
    delay(100);
  }
  else{
    Keyboard.release(KEY_RIGHT_ARROW);
  }
  
  if (Right < dataThreshold and Left > dataThreshold){
    Keyboard.press(KEY_LEFT_ARROW);
    delay(100);
  }
  else{
    Keyboard.release(KEY_LEFT_ARROW);
  }
   
  if(Up > dataThreshold and Down < dataThreshold){
    Keyboard.press(KEY_UP_ARROW);
    delay(100);
  }
  else{
    Keyboard.release(KEY_UP_ARROW);
  }
  
  if(Up < dataThreshold and Down > dataThreshold){
    Keyboard.press(KEY_DOWN_ARROW);
    delay(100);   
  }
  else{
    Keyboard.release(KEY_DOWN_ARROW);
  }
  
  if(Up > dataThreshold and Right > dataThreshold and Down > dataThreshold and Left > dataThreshold){
      Keyboard.print("f");
      delay(1);
  }
     
  if(Up > dataThreshold and Down > dataThreshold) {
    Keyboard.print((char)32); 
    delay(1);
  } 
  while (micros() % 200 != 0);  
}

void setup() {
  pinMode(charging_PIN, OUTPUT);
  pinMode(analogue_PIN, INPUT);

  pinMode(SERIAL_PINA, OUTPUT);
  pinMode(SERIAL_PINB, OUTPUT);
  pinMode(SERIAL_PINC, OUTPUT);
  pinMode(SERIAL_PIND, OUTPUT);
  
  Joystick.useManualSend(true);
  init_joystick ();
  Joystick.send_now(); 

  Mouse.begin();
  
  Serial.begin(9600);
}

void loop() { 
  for (int counter = 0; counter < 16; counter++){// put your main code here, to run repeatedly:
    switch (counter){
      case 0:
        digitalWrite(SERIAL_PINA, LOW);
        digitalWrite(SERIAL_PINB, LOW);
        digitalWrite(SERIAL_PINC, LOW);
        digitalWrite(SERIAL_PIND, LOW);
        delay(1); 
        
        x1 = measureValues(charging_PIN, analogue_PIN);
        //delay(1000);
        break;  
      case 1:
        digitalWrite(SERIAL_PINA, HIGH);
        digitalWrite(SERIAL_PINB, LOW);
        digitalWrite(SERIAL_PINC, LOW);
        digitalWrite(SERIAL_PIND, LOW);
        delay(1); 
        
        x2 = measureValues(charging_PIN, analogue_PIN);
        //delay(1000);
        break;
      case 2:
        digitalWrite(SERIAL_PINA, LOW);
        digitalWrite(SERIAL_PINB, HIGH);
        digitalWrite(SERIAL_PINC, LOW);
        digitalWrite(SERIAL_PIND, LOW);
        delay(1); 
        
        x3 = measureValues(charging_PIN, analogue_PIN);
        //delay(1000);
        break;
      case 3:
        digitalWrite(SERIAL_PINA, HIGH);
        digitalWrite(SERIAL_PINB, HIGH);
        digitalWrite(SERIAL_PINC, LOW);
        digitalWrite(SERIAL_PIND, LOW);
        delay(1); 

        x4 = measureValues(charging_PIN, analogue_PIN);
        //delay(1000);
        break;
      case 4:
        digitalWrite(SERIAL_PINA, LOW);
        digitalWrite(SERIAL_PINB, LOW);
        digitalWrite(SERIAL_PINC, HIGH);
        digitalWrite(SERIAL_PIND, LOW);
        delay(1); 

        x5 = measureValues(charging_PIN, analogue_PIN);
        //delay(1000);
        break;
      case 5:
        digitalWrite(SERIAL_PINA, HIGH);
        digitalWrite(SERIAL_PINB, LOW);
        digitalWrite(SERIAL_PINC, HIGH);
        digitalWrite(SERIAL_PIND, LOW);
        delay(1); 
      
        x6 = measureValues(charging_PIN, analogue_PIN);
        //delay(1000);
        break;
      case 6:
        digitalWrite(SERIAL_PINA, LOW);
        digitalWrite(SERIAL_PINB, HIGH);
        digitalWrite(SERIAL_PINC, HIGH);
        digitalWrite(SERIAL_PIND, LOW);
        delay(1); 
        
        x7 = measureValues(charging_PIN, analogue_PIN);
        //delay(1000);
        break;
     case 7:
        digitalWrite(SERIAL_PINA, HIGH);
        digitalWrite(SERIAL_PINB, HIGH);
        digitalWrite(SERIAL_PINC, HIGH);
        digitalWrite(SERIAL_PIND, LOW);
        delay(1); 
         
        x8 = measureValues(charging_PIN, analogue_PIN);
        //delay(1000);     
        break;
      case 8:
        digitalWrite(SERIAL_PINA, LOW);
        digitalWrite(SERIAL_PINB, LOW);
        digitalWrite(SERIAL_PINC, LOW);
        digitalWrite(SERIAL_PIND, HIGH);
        delay(1); 
         
        x9 = measureValues(charging_PIN, analogue_PIN);
        //delay(1000);
        break;
      case 9:
        digitalWrite(SERIAL_PINA, HIGH);
        digitalWrite(SERIAL_PINB, LOW);
        digitalWrite(SERIAL_PINC, LOW);
        digitalWrite(SERIAL_PIND, HIGH);
        delay(1); 
      
        xten = measureValues(charging_PIN, analogue_PIN);
        //delay(1000);
        break;
      case 10:
        digitalWrite(SERIAL_PINA, LOW);
        digitalWrite(SERIAL_PINB, HIGH);
        digitalWrite(SERIAL_PINC, LOW);
        digitalWrite(SERIAL_PIND, HIGH);
        delay(1); 
        
        x11 = measureValues(charging_PIN, analogue_PIN);
        //delay(1000);
        break;
      case 11:
        digitalWrite(SERIAL_PINA, HIGH);
        digitalWrite(SERIAL_PINB, HIGH);
        digitalWrite(SERIAL_PINC, LOW);
        digitalWrite(SERIAL_PIND, HIGH);
        delay(1); 
          
        x12 = measureValues(charging_PIN, analogue_PIN);
        //delay(1000);
        break;
      case 12:
        digitalWrite(SERIAL_PINA, LOW);
        digitalWrite(SERIAL_PINB, LOW);
        digitalWrite(SERIAL_PINC, HIGH);
        digitalWrite(SERIAL_PIND, HIGH);
        delay(1); 
        
        x13 = measureValues(charging_PIN, analogue_PIN);
        //delay(1000);
        break;
      case 13:
        digitalWrite(SERIAL_PINA, HIGH);
        digitalWrite(SERIAL_PINB, LOW);
        digitalWrite(SERIAL_PINC, HIGH);
        digitalWrite(SERIAL_PIND, HIGH);
        delay(1); 
        
        x14 = measureValues(charging_PIN, analogue_PIN);
        //delay(1000);
        break;
      case 14:
        digitalWrite(SERIAL_PINA, LOW);
        digitalWrite(SERIAL_PINB, HIGH);
        digitalWrite(SERIAL_PINC, HIGH);
        digitalWrite(SERIAL_PIND, HIGH);
        delay(1);  
        
        x15 = measureValues(charging_PIN, analogue_PIN);
        //delay(1000);
        break;
      case 15:
        digitalWrite(SERIAL_PINA, HIGH);
        digitalWrite(SERIAL_PINB, HIGH);
        digitalWrite(SERIAL_PINC, HIGH);
        digitalWrite(SERIAL_PIND, HIGH);
        delay(1);  
        
        x16 = measureValues(charging_PIN, analogue_PIN);
        //delay(1000);
        break;
     default:
        Serial.println("Error");
        init_joystick ();
        Joystick.send_now();
        break;
    }
  }
  Serial.print("A: "); Serial.print(x13); Serial.print(" "); Serial.print("B: "); Serial.print(x12); Serial.print(" "); 
  Serial.print("C: "); Serial.print(xten); Serial.print(" "); Serial.print("D: "); Serial.print(x11);  Serial.println(" ");

  //x12(B),x11(C),xten(D),x13(A)
  needForSpeedFunction(x12, x11, xten, x13);
  //batmanFunction(xten,x13,x12,x11);
  //transformersFunction(x12, x11, xten, x13);
}

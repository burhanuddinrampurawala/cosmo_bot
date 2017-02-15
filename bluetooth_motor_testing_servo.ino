/* 
* Bluetooh Basic: LED ON OFF - Avishkar
* Coder - Mayoogh Girish
* Website - http://bit.do/Avishkar
* Download the App : https://github.com/Mayoogh/Arduino-Bluetooth-Basic
* This program lets you to control a LED on pin 13 of arduino using a bluetooth module
*/
#include <Servo.h>

Servo myservo;           // create servo object to control a servo
int ledpin = 13;                        // twelve servo objects can be created on most boards
int sp0 = A0;
int sp1 = A1;
int sp2 = A2;
int sp3 = A3;
int sp4 = A4;
int sp5 = A5;
int sp6 = A6;                  // select the input pin for the potentiometer
int s0 = 0;
int s1 = 0;
int s2 = 0;
int s3 = 0;  
int s4 = 0;  
int s5 = 0;
int s6 = 0;                     // variable to store the value coming from the sensor
int pos = 0;                    // variable to store the servo position
int t = 500;
int motor_left[] = {2, 3};
int motor_right[] = {7, 8};
char data = 0;                //Variable for storing received data




void setup()
  {
   Serial.begin(9600);   //Sets the baud for serial data transmission                               
    int i;                // Setup motors
    for(i = 0; i < 2; i++)
    {
      pinMode(motor_left[i], OUTPUT);
      pinMode(motor_right[i], OUTPUT);
    }
    myservo.attach(9);
  
  pinMode(ledpin, OUTPUT);
  }


////////////////////fuctions///////////////////

void check_ground_sensor(int a, int b)
{ 
  
  if(a||b>t){
    motor_stop();
  }
 }


void motor_stop()
{
  digitalWrite(motor_left[0], LOW); 
  digitalWrite(motor_left[1], LOW); 
  digitalWrite(motor_right[0], LOW); 
  digitalWrite(motor_right[1], LOW);
  delay(25);
}

void drive_forward()
{ 
  s4 = analogRead(sp4);
  s5 = analogRead(sp5);
 //check_ground_sensor(s4,s5);
 
  s0 = analogRead(sp0);
  Serial.println(s0);
  //if(s0>t)
  {
  digitalWrite(motor_left[0], HIGH); 
  digitalWrite(motor_left[1], LOW); 
  digitalWrite(ledpin, HIGH);
  digitalWrite(motor_right[0], HIGH); 
  digitalWrite(motor_right[1], LOW); 
  }
  //else
  {
  //motor_stop();
  digitalWrite(ledpin, LOW);
  }
}

void drive_backward()
{  
  s4 = analogRead(sp4);
  s5 = analogRead(sp5);
  //check_ground_sensor(s4,s5);
  
  s2 = analogRead(sp2);
  //if(s2>t)
  {
    digitalWrite(motor_left[0], LOW); 
    digitalWrite(motor_left[1], HIGH); 
    digitalWrite(ledpin, HIGH);
    digitalWrite(motor_right[0], LOW); 
    digitalWrite(motor_right[1], HIGH); 
  }
 //else
 {
   digitalWrite(ledpin, LOW);
  //motor_stop();
  }
}

void turn_left(){
  s1 = analogRead(sp1);
  //if(s1>t)
  {
    digitalWrite(motor_left[0], LOW); 
    digitalWrite(motor_left[1], HIGH); 
     digitalWrite(ledpin, HIGH);
    digitalWrite(motor_right[0], HIGH); 
    digitalWrite(motor_right[1], LOW);
  }
    //else 
 {
  digitalWrite(ledpin, LOW);
  //motor_stop();
 }
}

void turn_right()
{
  s3 = analogRead(sp3);
  //if(s3>t)
  {
    digitalWrite(motor_left[0], HIGH); 
    digitalWrite(motor_left[1], LOW); 
    digitalWrite(ledpin, HIGH);
    digitalWrite(motor_right[0], LOW); 
    digitalWrite(motor_right[1], HIGH); 
  }
   //else
 {
   digitalWrite(ledpin, LOW);
    //motor_stop();
 }
}
void servo_happy(){
   for (pos = 0; pos <= 90; pos += 1) 
     {                                         // goes from 0 degrees to 180 degrees in steps of 1 degree
      myservo.write(pos);                     // tell servo to go to position in variable 'pos'
      delay(10);                             // waits 15ms for the servo to reach the position
     }
    delay(500);
   for (pos = 90; pos >= 0; pos -= 1) 
    {                                       // goes from 180 degrees to 0 degrees
    myservo.write(pos);                    // tell servo to go to position in variable 'pos'
    delay(10);                            // waits 15ms for the servo to reach the position
    }
  }
  
void servo_angry()
  {
   for (pos = 0; pos <= 90; pos += 1)   
    {                                           // goes from 0 degrees to 180 degrees in steps of 1 degree
      myservo.write(pos);                      // tell servo to go to position in variable 'pos'
      delay(3);                               // waits 15ms for the servo to reach the position
    }
   for (pos = 90; pos >= 0; pos -= 1) 
   {                                          
   myservo.write(pos);                     // tell servo to go to position in variable 'pos'
   delay(3);                              // waits 15ms for the servo to reach the position
  }               //exit for
 }                //exit angry



/////////////main loop//////////////


void loop()
{
    
   if(Serial.available() > 0)      // Send data only when you receive data:
   {
      data = Serial.read();        //Read the incoming data & store into data
     switch(data)
     {
      case 'f':
               drive_forward(); 
              // motor_stop();
               //Serial.println("1");
                break;
              
      case 'b':
                drive_backward();
               // delay(1000);
                //motor_stop();
                //Serial.println("2");
                break;
              
     case 'l':
               turn_left();
               //delay(1000);
               //motor_stop();
               //Serial.println("3");
               break;
              
      case 'r':
               turn_right();
               //delay(1000);
               //motor_stop();
               //Serial.println("4");
               break;

     case 't':
                
                motor_stop();
                Serial.println("stopped");
                break;

      case 'h':
               drive_forward();
               servo_happy();
               //delay(1000);
               motor_stop();
               Serial.println("happy");
               break;
               
      case 's':
               drive_backward();
               //servo_sad();
               //delay(1000);
              // motor_stop();
               Serial.println("sad");
               break;   
                
    case 'a':
               drive_backward();
               servo_angry();
               //delay(1000);
              // motor_stop();
               Serial.println("angry");
               break;    
   
    default:
            motor_stop();
            //delay(1000);
        
          //  Serial.println("default");        
      
   }
 }
}

/* 
* Bluetooh Basic: LED ON OFF - Avishkar
* Coder - VIDHI & SUVEENA
* Website - http://bit.do/Avishkar
* Download the App : https://github.com/Mayoogh/Arduino-Bluetooth-Basic
* This program lets you to control a LED on pin 13 of arduino using a bluetooth module
*/
#include <Servo.h>
#include<math.h> 

Servo myservo1;   

Servo myservo2; // create servo object to control a servo
int ledpin = 13;                        // twelve servo objects can be created on most boards
int sp0 = A0;
int sp1 = A1;
int sp2 = A2;
int sp3 = A3;
int sp4 = A4;
int sp5 = A5;
//int sp6 = A6;                  // select the input pin for the potentiometer
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
char data = 0;   
//int pos = 0;//Variable for storing received data
int neg = 0;
int voltage;
int voltage_1;



void setup()
  {
    Serial.begin(9600);   //Sets the baud for serial data transmission                               
    int i;                // Setup motors
    for(i = 0; i < 2; i++)
    {
      pinMode(motor_left[i], OUTPUT);
      pinMode(motor_right[i], OUTPUT);
    }
    myservo1.attach(6);
    myservo2.attach(4);
  
  pinMode(ledpin, OUTPUT);
  }


////////////////////fuctions//////////////////////

void check_ground_sensor()
{ 
   s4 = analogRead(sp4);
    s5 = analogRead(sp5);
 if(s4>50||s5>50){
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
  s0 = analogRead(sp0);
  if(s0>t)
  {
     
    check_ground_sensor();
  digitalWrite(motor_left[0], LOW); 
  digitalWrite(motor_left[1], HIGH); 
  digitalWrite(ledpin, HIGH);
  digitalWrite(motor_right[0], LOW); 
  digitalWrite(motor_right[1], HIGH); 
  delay(500);
  motor_stop();

  }
  else
  {
      Serial.write("o");
  motor_stop();
 // digitalWrite(ledpin, LOW);
  }
}

void drive_backward()
{  
   s2 = analogRead(sp2);
   //Serial.println(s2);
    
  if(s2>t)
  {
  
  check_ground_sensor();
 
    digitalWrite(motor_left[0], HIGH); 
    digitalWrite(motor_left[1], LOW); 
    digitalWrite(ledpin, HIGH);
    digitalWrite(motor_right[0], HIGH); 
     digitalWrite(motor_right[1], LOW);
    delay(800);
    motor_stop(); 
  }
  else
  {
// digitalWrite(ledpin, LOW);
  motor_stop();
  Serial.write("o");
  }
}

void turn_left(){
   
    check_ground_sensor();
    digitalWrite(motor_left[0], LOW); 
    digitalWrite(motor_left[1], HIGH); 
    digitalWrite(ledpin, HIGH);
    digitalWrite(motor_right[0], HIGH); 
    digitalWrite(motor_right[1], LOW);
    delay(500);                 
    motor_stop();
 
}
void spin_left(){
   
    check_ground_sensor();
    digitalWrite(motor_left[0], LOW); 
    digitalWrite(motor_left[1], HIGH); 
    digitalWrite(ledpin, HIGH);
    digitalWrite(motor_right[0], HIGH); 
    digitalWrite(motor_right[1], LOW);
    delay(1500);                 
    motor_stop();
 
}

void turn_right()
{
   
    check_ground_sensor();
    digitalWrite(motor_left[0], HIGH); 
    digitalWrite(motor_left[1], LOW); 
    digitalWrite(ledpin, HIGH);
    digitalWrite(motor_right[0], LOW); 
    digitalWrite(motor_right[1], HIGH); 
    delay(400);                          
    motor_stop();
}
void spin_right()
{
   
    check_ground_sensor();
    digitalWrite(motor_left[0], HIGH); 
    digitalWrite(motor_left[1], LOW); 
    digitalWrite(ledpin, HIGH);
    digitalWrite(motor_right[0], LOW); 
    digitalWrite(motor_right[1], HIGH); 
    delay(1300);                          
    motor_stop();
}
void servo_happy()
  {
    //drive_forward();
    for (neg=90,pos = 90; pos <= 180, neg>= 0; pos += 1,neg -= 1) 
     {                                         // goes from 0 degrees to 180 degrees in steps of 1 degree
      myservo1.write(pos);
      myservo2.write(neg); // tell servo to go to position in variable 'pos'
      delay(10);                             // waits 15ms for the servo to reach the position
     }
    delay(500);
   for (neg=0,pos = 180;neg<=90, pos >= 90; neg+=1,pos -= 1) 
    {                                       // goes from 180 degrees to 0 degrees
    myservo1.write(pos);
    myservo2.write(neg); // tell servo to go to position in variable 'pos'
    delay(10);                            // waits 15ms for the servo to reach the position
    }
  }
  
void servo_angry()
  {
   // drive_backward();
   for (neg=90,pos = 90; pos <= 180, neg>= 0; pos += 1,neg -= 1)   
    {                                           // goes from 0 degrees to 180 degrees in steps of 1 degree
      myservo1.write(pos);
      myservo2.write(neg); // tell servo to go to position in variable 'pos'
      delay(3);                               // waits 15ms for the servo to reach the position
    }
   for (neg=0,pos = 180;neg<=90, pos >= 90; neg+=1,pos -= 1) 
   {                                          
      myservo1.write(pos);
      myservo2.write(neg);                    // tell servo to go to position in variable 'pos'
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
               Serial.write("e");
                break;
              
      case 'b':
                drive_backward();
               // delay(1000);
                //motor_stop();
               // Serial.println("2");
                Serial.write("e");
                break;
              
     case 'r':
               turn_left();
               //delay(1000);
               motor_stop();
               //Serial.println("3");
               Serial.write("e");
               break;

      case 'A':
               spin_right();
               //delay(1000);
               motor_stop();
               Serial.write("e");
               //Serial.println("3");
               break;
                       
              
      case 'l':
               turn_right();
               //delay(1000);
               motor_stop();
               Serial.write("e");
               //Serial.println("4");
               break;

     case 'C':
               spin_left();
               
               //delay(1000);
               motor_stop();
               Serial.write("e");
               //Serial.println("4");
               break;          

     case 't':
                motor_stop();
                //Serial.println("stopped");
                Serial.write("e");
                break;

      case 'o':                   //hello
               drive_forward();
               drive_backward();
               servo_happy();
               //delay(1000);
               motor_stop();
              // Serial.println("happy");
               Serial.write("e");
               break;

      case 'h':                 //happy
               servo_happy();
               //delay(1000);
               motor_stop();
              // Serial.println("happy");
               Serial.write("e");
               break;

      case 'd':
               drive_forward();
               drive_backward();
               turn_right();
               turn_left();
               turn_left();
               turn_right();
               servo_angry();
               drive_forward();
               drive_backward();
               turn_left();
               turn_right();
               turn_right();
               turn_left();
               servo_angry();
            
               //delay(1000);
               motor_stop();
               //Serial.println("dance");
               Serial.write("e");
               break;
               
      case 's':
               drive_backward();
                servo_happy();
               //delay(1000);
               motor_stop();
               //Serial.println("sad");
               Serial.write("e");
               break;   
                
    case 'a':
               drive_backward();
               servo_angry();
               //delay(1000);
               motor_stop();
               //Serial.println("angry");
               Serial.write("e");
               break;    
   
    default:
            motor_stop();
            //delay(1000);
        
          //  Serial.println("default");        
      }

   }

  
     voltage=analogRead(A6);
     float voltage_1 = voltage * (7.5 / 1023.0);
    // Serial.println(voltage);
     
   if(voltage_1 <= 3.5)
   {
   
    Serial.write("v");
    
    }
    
 }


#include <ECE3.h>


#include <ECE3.h>



uint16_t sensorValues[8]; // right -> left, 0 -> 7

const int left_nslp_pin=31; // nslp ==> awake & ready for PWM
const int left_dir_pin=29;
const int left_pwm_pin=40;

const int right_nslp = 11;
const int right_dir = 30;
const int right_pwm = 39;

const int LED_RF = 41;
const int LF = 51;
//int count = 15;
///////////////////////////////////
void setup() {
// put your setup code here, to run once:
  pinMode(left_nslp_pin,OUTPUT);
  pinMode(left_dir_pin,OUTPUT);
  pinMode(left_pwm_pin,OUTPUT);

   pinMode(right_nslp,OUTPUT);
  pinMode(right_dir,OUTPUT);
  pinMode(right_pwm,OUTPUT);

//left
  digitalWrite(left_dir_pin,LOW);
  digitalWrite(left_nslp_pin,HIGH);
  
 digitalWrite(right_dir,LOW);
  digitalWrite(right_nslp,HIGH);


  pinMode(LED_RF, OUTPUT);
  pinMode(LF, OUTPUT);
   ECE3_Init();
  
  
//  ECE3_Init();

// set the data rate in bits/second for serial data transmission
  Serial.begin(9600); 
  delay(2000); //Wait 2 seconds before starting 
  
}
bool isEnd()
{ int sum = 0; 
for (int i = 0; i < 8; i++)
{
  sum +=  sensorValues[i];
}

 if (sum > 13000)
  return true;
  else 
  return false;
}
int counter = 0;
int odo = 0;
void loop() {
const int left = 95; 
const int right = 97; 

int leftSpd = 55; 
int rightSpd = 54; 
int factor[8] = {8,8,16,33,43,52};
 ECE3_read_IR(sensorValues); // right to left
int error = 0;
int count = 1;

for( unsigned char i = 3; i > 0 ; i--)
{
   error +=  count * (sensorValues[i] - sensorValues[7-i]);
   count *= 2;
}

 if((-500 < error && error < -50) || (50 < error && error < 500))
 {//Serial.println("last if ");
  leftSpd = left;
  rightSpd = right;
  analogWrite(left_pwm_pin,leftSpd);
  analogWrite(right_pwm,rightSpd); 
 
 }
 else if ( error  > 5000) 
 {
  leftSpd += factor[5];
  analogWrite(left_pwm_pin,leftSpd);
  analogWrite(right_pwm,rightSpd); 
 }
else if (3500 < error && error  < 5000) 
 { 
  leftSpd += factor[4];
  analogWrite(left_pwm_pin,leftSpd);
  analogWrite(right_pwm,rightSpd); 
 }
else if (1700 < error && error < 3500) 
 {
  leftSpd += factor[3];
  analogWrite(left_pwm_pin,leftSpd);
  analogWrite(right_pwm,rightSpd); 
 }
else if (1000 < error && error < 1700)
{
  leftSpd += factor[2];
  analogWrite(left_pwm_pin,leftSpd);
  analogWrite(right_pwm,rightSpd); 
}
else if (500 < error && error < 1000)
{
  leftSpd += factor[1];
  analogWrite(left_pwm_pin,leftSpd);
  analogWrite(right_pwm,rightSpd); 
}
 else if ( error  < -5000) 
 { 
  rightSpd += factor[5];
  analogWrite(left_pwm_pin,leftSpd);
  analogWrite(right_pwm,rightSpd); 
 }
else  if (-5000 < error && error < -3500)
 {
  rightSpd += factor[4];
  analogWrite(left_pwm_pin,leftSpd);
  analogWrite(right_pwm,rightSpd); 
 }
else if (-3500 < error && error < -1700)
 {
  rightSpd += factor[3];
  analogWrite(left_pwm_pin,leftSpd);
  analogWrite(right_pwm,rightSpd); 
 }
else if (-1000 > error && error > -1700)
{
  rightSpd += factor[2];
  analogWrite(left_pwm_pin,leftSpd);
  analogWrite(right_pwm,rightSpd); 
}
else if (-500 > error && error > -1000)
{
  rightSpd += factor[1];
  analogWrite(left_pwm_pin,leftSpd);
  analogWrite(right_pwm,rightSpd); 
}
else if((-500 < error && error < -50) || (50 < error && error < 500))
 {
  leftSpd = left;
  rightSpd = right;
  analogWrite(left_pwm_pin,leftSpd);
  analogWrite(right_pwm,rightSpd); 
 
 }
 if ( isEnd() == true)
 {
  counter++;
  if (counter == 3)
 { leftSpd = 200;
   rightSpd = 202;
   analogWrite(left_pwm_pin,leftSpd);
  analogWrite(right_pwm,rightSpd); 
  digitalWrite(right_dir,HIGH);
  delay(300);
  digitalWrite(right_dir,LOW);

 }
  
 }
 else if (isEnd() == false && counter < 3)
 {
  counter = 0;
 }
 odo =  (getEncoderCount_left() +  getEncoderCount_right())/2;
 if (odo >= 15000)
 {
digitalWrite(BLUE_LED, HIGH);
 }
analogWrite(left_pwm_pin,leftSpd);
analogWrite(right_pwm,rightSpd); 

    
  }
  

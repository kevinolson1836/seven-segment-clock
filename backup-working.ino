/*************************************************** 
  This is an example for our Adafruit 16-channel PWM & Servo driver
  Servo test - this will drive 8 servos, one after the other on the
  first 8 pins of the PCA9685

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/815
  
  These drivers use I2C to communicate, 2 pins are required to  
  interface.

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <ds3231.h>
 
struct ts t;

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x42);
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x41);

#define SERVOMIN  120 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  290 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

// our servo # counter
uint8_t servonum = 0;   //used for testing
int first_right;
int first_left;
int second_right;
int second_left;
int third_right;
int third_left;
int fourth_right;
int fourth_left;



int prev_right;
int prev_left;
int prev_right1;
int prev_left1;
int prev_right2;
int prev_left2;
int prev_right3;
int prev_left3;


unsigned prev_first;
unsigned prev_second;
unsigned prev_third;
unsigned prev_fourth;

int first_run = 1;

void setup() {
  Serial.begin(9600);
  Serial.println("8 channel Servo test!");

  pwm.begin();
  pwm2.begin();

  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  pwm2.setOscillatorFrequency(27000000);
  pwm2.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  Wire.begin();
  DS3231_init(DS3231_CONTROL_INTCN);
  /*----------------------------------------------------------------------------
  In order to set time set values below! commented out to not set it again every time it resets
  ----------------------------------------------------------------------------*/
  t.hour=3; 
  t.min=59;
  t.sec=50;
 
  DS3231_set(t);
  
}

void sleep_pin_1(int min, int max){
  delay(100);
  for (int min = 0; min < 16; min++){
    pwm.setPin(min,0,0);
  }
}

void sleep_pin_2(int min, int max){
  delay(100);
  for (int min = 0; min < 16; min++){
    pwm2.setPin(min,0,0);
  }
}
void first_top_servo(int status){
 /*    status will be 0 for down, 1 for up. pulselen(3rd param to setPWM) will have to be set per servo basis due to how I attached the arms)
 *     
 *      **
 *     |  | 
 *      --
 *     |  |
 *      --
 */
 //   Serial.println(status);
  if (status == 1){
    for (uint16_t pulselen = 290; pulselen < 497; pulselen++) {
              pwm.setPWM(0, 0, pulselen);
    }
   //    Serial.println("up");
  }
  else{
    for (uint16_t pulselen = 490; pulselen > 290; pulselen--) {
              pwm.setPWM(0, 0, pulselen);
            }
    //    Serial.println("down");
  }
}

void first_top_right_servo(int status){
 /*    status will be 0 for down, 1 for up. pulselen(3rd param to setPWM) will have to be set per servo basis due to how I attached the arms)
 *     
 *      --
 *     |  *
 *      --
 *     |  |
 *      --
 */
 //   Serial.println(status);
  if (status == 0){
    for (uint16_t pulselen = 110; pulselen < 285; pulselen++) {
              pwm.setPWM(1, 0, pulselen);
    }
   //    Serial.println("up");
  }
  else{
    for (uint16_t pulselen = 285; pulselen > 110; pulselen--) {
              pwm.setPWM(1, 0, pulselen);
            }     
    //    Serial.println("down");
  }
}

void first_top_left_servo(int status){
 /*    status will be 0 for down, 1 for up. pulselen(3rd param to setPWM) will have to be set per servo basis due to how I attached the arms)
 *     
 *      --
 *     *  | 
 *      --
 *     |  |
 *      --
 */
 //   Serial.println(status);
  if (status == 1){
    for (uint16_t pulselen1 = 290; pulselen1 < 490; pulselen1++) {
              pwm.setPWM(2, 0, pulselen1);
    }  
   //    Serial.println("up");
  }
  else{
    for (uint16_t pulselen2 = 490; pulselen2 > 290; pulselen2--) {
              pwm.setPWM(2, 0, pulselen2);
            }
    //    Serial.println("down");
  }
}

void first_bottom_left_servo(int status){
 /*    status will be 0 for down, 1 for up. pulselen(3rd param to setPWM) will have to be set per servo basis due to how I attached the arms)
 *     
 *      --
 *     |  | 
 *      --
 *     *  |
 *      --
 */
 //   Serial.println(status);
  if (status == 1){
    for (uint16_t pulselen1 = 297; pulselen1 < 497; pulselen1++) {
              pwm.setPWM(3, 0, pulselen1);
    }  
   first_left = 1; 
   //    Serial.println("up");
  }
  else{
    for (uint16_t pulselen2 = 497; pulselen2 > 297; pulselen2--) {
              pwm.setPWM(3, 0, pulselen2);
            }
    first_left = 0;
    //    Serial.println("down");
  }
}

void first_bottom_right_servo(int status){
 /*    status will be 0 for down, 1 for up. pulselen(3rd param to setPWM) will have to be set per servo basis due to how I attached the arms)
 *     
 *      --
 *     |  |
 *      --
 *     |  *
 *      --
 */
 //   Serial.println(status);
  if (status == 1){
    
    for (uint16_t pulselen1 = 293; pulselen1 > 150; pulselen1--) {
              pwm.setPWM(4, 0, pulselen1);
            }  
   first_right = 1;
   //    Serial.println("up");
  }
  else{
    for (uint16_t pulselen2 = 150; pulselen2 < 293; pulselen2++) {
              pwm.setPWM(4, 0, pulselen2);
    }
    first_right = 0;
    //    Serial.println("down");
  }
}

void first_bottom_servo(int status){
 /*    status will be 0 for down, 1 for up. pulselen(3rd param to setPWM) will have to be set per servo basis due to how I attached the arms)
 *     
 *      --
 *     |  | 
 *      --
 *     |  |
 *      **
 */
 //   Serial.println(status);
  if (status == 0){
    for (uint16_t pulselen = 179; pulselen < 353; pulselen++) {
              pwm.setPWM(5, 0, pulselen);
    }
   //    Serial.println("up");
  }
  else{
        for (uint16_t pulselen = 353; pulselen > 180; pulselen--) {
              pwm.setPWM(5, 0, pulselen);
            }  

    //    Serial.println("down");
  }
}

void first_middle_servo(int status){
 /*    status will be 0 for down, 1 for up. pulselen(3rd param to setPWM) will have to be set per servo basis due to how I attached the arms)
 *     
 *      --
 *     |  | 
 *      **
 *     |  |
 *      --
 */
 //   Serial.println(status);
  prev_right = first_right; 
  prev_left = first_left;
  first_bottom_right_servo(0);
  first_bottom_left_servo(0);
  delay(500);
  if (status == 1){
      for (uint16_t pulselen = 290; pulselen > 100; pulselen--) {
                pwm.setPWM(6, 0, pulselen);
              }  
   //    Serial.println("up");
  }
  else{
    for (uint16_t pulselen = 100; pulselen < 290; pulselen++) {
              pwm.setPWM(6, 0, pulselen);
    }
    //    Serial.println("down");
  }
  delay(500);
  first_bottom_right_servo(prev_right);
  first_bottom_left_servo(prev_left);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                                                              *******             start of first number functions             *******
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void first_zero(){
 first_top_servo(1);delay(50);
//  /first_top_right_servo(1);delay(50);
  first_top_left_servo(1);delay(50);
  first_bottom_left_servo(1);delay(50);
//  first_bottom_right_servo(1);delay(50);
  first_bottom_servo(1);delay(50);
//  first_middle_servo(0);delay(50);
  sleep_pin_1(0,7);
}

void first_one(){
  first_top_servo(0);delay(50);
//  /first_top_right_servo(1);delay(50);
  first_top_left_servo(0);delay(50);
  first_bottom_left_servo(0);delay(50);
// / first_bottom_right_servo(1);delay(50);
  first_bottom_servo(0);delay(50);
// / first_middle_servo(0);delay(50);
  sleep_pin_1(0,7);
}

void first_two(){
  first_top_servo(1);delay(50);
// / first_top_right_servo(1);delay(50);
//  /first_top_left_servo(0);delay(50);
  first_bottom_left_servo(1);delay(50);
  first_bottom_right_servo(0);delay(50);
  first_bottom_servo(1);delay(50);
  first_middle_servo(1);delay(50);
  sleep_pin_1(0,7);delay(50);
}

void first_three(){
// / first_top_servo(1);delay(50);
// / first_top_right_servo(1);delay(50);
// / first_top_left_servo(0);delay(50);
  first_bottom_left_servo(0);delay(50);
  first_bottom_right_servo(1);delay(50);
// / first_bottom_servo(1);delay(50);
///  first_middle_servo(1);delay(50);
  sleep_pin_1(0,7);
}

void first_four(){
  first_top_servo(0);delay(50);
// / first_top_right_servo(1);delay(50);
  first_top_left_servo(1);delay(50);
// / first_bottom_left_servo(0);delay(50);
// / first_bottom_right_servo(1);delay(50);
  first_bottom_servo(0);delay(50);
// / first_middle_servo(1);delay(50);
  sleep_pin_1(0,7);delay(50);
}

void first_five(){
  first_top_servo(1);delay(50);
  first_top_right_servo(0);delay(50);
//  /first_top_left_servo(1);delay(50);
///  first_bottom_left_servo(0);delay(50);
// / first_bottom_right_servo(1);delay(50);
  first_bottom_servo(1);delay(50);
// / first_middle_servo(1);delay(50);
  sleep_pin_1(0,7);
}

void first_six(){
// / first_top_servo(1);delay(50);
// / first_top_right_servo(0);delay(50);
// / first_top_left_servo(1);delay(50);
  first_bottom_left_servo(1);delay(50);
//  /first_bottom_right_servo(1);delay(50);
// / first_bottom_servo(1);delay(50);
///  first_middle_servo(1);delay(50);
  sleep_pin_1(0,7);
}
void first_seven(){
// / first_top_servo(1);delay(50);
  first_top_right_servo(1);delay(50);
  first_top_left_servo(0);delay(50);
  first_bottom_left_servo(0);delay(50);
  first_bottom_right_servo(1);delay(50);
  first_bottom_servo(0);delay(50);
  first_middle_servo(0);delay(50);
  sleep_pin_1(0,7);
}

void first_eight(){
//  /first_top_servo(1);delay(50);
//  /first_top_right_servo(1);delay(50);
  first_top_left_servo(1);delay(50);
  first_bottom_left_servo(1);delay(50);
  first_bottom_right_servo(1);delay(50);
  first_bottom_servo(1);delay(50);
  first_middle_servo(1);delay(50);
  sleep_pin_1(0,7);
}

void first_nine(){
// / first_top_servo(1);delay(50);
// / first_top_right_servo(1);delay(50);
// / first_top_left_servo(1);delay(50);
  first_bottom_left_servo(0);delay(50);
// / first_bottom_right_servo(1);delay(50);
// / first_bottom_servo(1);delay(50);
///  first_middle_servo(1);delay(50);
  sleep_pin_1(0,7);
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                                                              *******             start of second number             *******
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void second_top_servo(int status){
 /*    status will be 0 for down, 1 for up. pulselen(3rd param to setPWM) will have to be set per servo basis due to how I attached the arms)
 *     
 *      **
 *     |  | 
 *      --
 *     |  |
 *      --
 */
 //   Serial.println(status);
  if (status == 1){
    for (uint16_t pulselen = 290; pulselen < 460; pulselen++) {
              pwm.setPWM(7, 0, pulselen);
    }
//   Serial.println("second zero up");
  }
  else{
    for (uint16_t pulselen = 460; pulselen > 290; pulselen--) {
              pwm.setPWM(7, 0, pulselen);
            }
    //    Serial.println("down");
  }
}


void second_top_right_servo(int status){
 /*    status will be 0 for down, 1 for up. pulselen(3rd param to setPWM) will have to be set per servo basis due to how I attached the arms)
 *     
 *      --
 *     |  *
 *      --
 *     |  |
 *      --
 */
 //   Serial.println(status);
  if (status == 1){
    for (uint16_t pulselen = 245; pulselen > 92; pulselen--) {
              pwm.setPWM(8, 0, pulselen);
            }
//   Serial.println("second zero up");
  }
  else{
    for (uint16_t pulselen = 92; pulselen < 245; pulselen++) {
              pwm.setPWM(8, 0, pulselen);
    }
//    //    Serial.println("down");
  }
}

void second_top_left_servo(int status){
 /*    status will be 0 for down, 1 for up. pulselen(3rd param to setPWM) will have to be set per servo basis due to how I attached the arms)
 *     
 *      --
 *     *  | 
 *      --
 *     |  |
 *      --
 */
 //   Serial.println(status);
  if (status == 1){
    for (uint16_t pulselen1 = 270; pulselen1 < 480; pulselen1++) {
              pwm.setPWM(9, 0, pulselen1);
    }  
//   //    Serial.println("up");
  }
  else{
    for (uint16_t pulselen2 = 480; pulselen2 > 270; pulselen2--) {
              pwm.setPWM(9, 0, pulselen2);
            }
//    //    Serial.println("down");
  }
}

void second_bottom_left_servo(int status){
 /*    status will be 0 for down, 1 for up. pulselen(3rd param to setPWM) will have to be set per servo basis due to how I attached the arms)
 *     
 *      --
 *     |  | 
 *      --
 *     *  |
 *      --
 */
 //   Serial.println(status);
  if (status == 1){
    for (uint16_t pulselen1 = 290; pulselen1 < 495; pulselen1++) {
              pwm.setPWM(10, 0, pulselen1);
    }  
   second_left = 1; 
//   //    Serial.println("up");
  }
  else{
    for (uint16_t pulselen2 = 495; pulselen2 > 290; pulselen2--) {
              pwm.setPWM(10, 0, pulselen2);
            }
    second_left = 0;
//    //    Serial.println("down");
  }
}

void second_bottom_right_servo(int status){
 /*    status will be 0 for down, 1 for up. pulselen(3rd param to setPWM) will have to be set per servo basis due to how I attached the arms)
 *     
 *      --
 *     |  |
 *      --
 *     |  *
 *      --
 */
 //   Serial.println(status);
  if (status == 1){
    
    for (uint16_t pulselen1 = 290; pulselen1 > 110; pulselen1--) {
              pwm.setPWM(11, 0, pulselen1);
            }  
   second_right = 1;
//   //    Serial.println("up");
  }
  else{
    for (uint16_t pulselen2 = 110; pulselen2 < 290; pulselen2++) {
              pwm.setPWM(11, 0, pulselen2);
    }
    second_right = 0;
//    //    Serial.println("down");
  }
}

void second_bottom_servo(int status){
 /*    status will be 0 for down, 1 for up. pulselen(3rd param to setPWM) will have to be set per servo basis due to how I attached the arms)
 *     
 *      --
 *     |  | 
 *      --
 *     |  |
 *      **
 */
 //   Serial.println(status);
  if (status == 1){
    for (uint16_t pulselen = 360; pulselen > 150; pulselen--) {
              pwm.setPWM(12, 0, pulselen);
            }  
//   //    Serial.println("up");
  }
  else{
    for (uint16_t pulselen = 150; pulselen < 360; pulselen++) {
              pwm.setPWM(12, 0, pulselen);
    }
//    //    Serial.println("down");
  }
}

void second_middle_servo(int status){
 /*    status will be 0 for down, 1 for up. pulselen(3rd param to setPWM) will have to be set per servo basis due to how I attached the arms)
 *     
 *      --
 *     |  | 
 *      **
 *     |  |
 *      --
 */
 //   Serial.println(status);
  prev_right1 = second_right; 
  prev_left1 = second_left;
  second_bottom_right_servo(0);
  second_bottom_left_servo(0);
//  Serial.println("delaying 500");
  delay(500);
  if (status == 1){
      for (uint16_t pulselen = 280; pulselen > 100; pulselen--) {
                pwm.setPWM(13, 0, pulselen);
              }  
//   //    Serial.println("up");
  }
  else{
    for (uint16_t pulselen = 100; pulselen < 280; pulselen++) {
              pwm.setPWM(13, 0, pulselen);
    }
//    //    Serial.println("down");
  }
  delay(500);
//  second_bottom_right_servo(prev_right1);
//  second_bottom_left_servo(prev_left1);
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                                                              *******             start of second number functions             *******
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void second_zero(){
//  second_top_servo(1);delay(50);
//  second_top_right_servo(1);delay(50);
//  second_top_left_servo(1);delay(50);
//  second_bottom_right_servo(0);delay(50);
// / second_bottom_servo(1);delay(50);
  second_middle_servo(0);delay(50);
  second_bottom_left_servo(1);delay(50);
  second_bottom_right_servo(1);delay(50);
  sleep_pin_1(6,15);
}

void second_one(){
  second_middle_servo(0);delay(50);
  second_top_servo(0);delay(50);
// / second_top_right_servo(1);delay(50);
  second_top_left_servo(0);delay(50);
  second_bottom_left_servo(0);delay(50);
  second_bottom_right_servo(1);delay(50);
  second_bottom_servo(0);delay(50);
  sleep_pin_1(6,15);
}

void second_two(){
  second_middle_servo(1);delay(50);
  second_top_servo(1);delay(50);
//  /second_top_right_servo(1);delay(50);
// / second_top_left_servo(0);delay(50);
  second_bottom_left_servo(1);delay(50);
  second_bottom_right_servo(0);delay(50);
  second_bottom_servo(1);delay(50);
  sleep_pin_1(6,15);
}

void second_three(){
///  second_middle_servo(1);delay(50);
//  /second_top_servo(1);delay(50);
// / second_top_right_servo(1);delay(50);
// / second_top_left_servo(0);delay(50);
  second_bottom_left_servo(0);delay(50);
  second_bottom_right_servo(1);delay(50);
//  /second_bottom_servo(1);delay(50);
  sleep_pin_1(6,15);
}

void second_four(){
//  /second_middle_servo(1);delay(50);
  second_top_servo(0);delay(50);
//  /second_top_right_servo(1);delay(50);
  second_top_left_servo(1);delay(50);
//  /second_bottom_left_servo(0);delay(50);
//  /second_bottom_right_servo(1);delay(50);
  second_bottom_servo(0);delay(50);
  sleep_pin_1(6,15);
}

void second_five(){
// / second_middle_servo(1);delay(50);
  second_top_servo(1);delay(50);
  second_top_right_servo(0);delay(50);
///  second_top_left_servo(1);delay(50);
///  second_bottom_left_servo(0);delay(50);
// / second_bottom_right_servo(1);delay(50);
  second_bottom_servo(1);delay(50);
  sleep_pin_1(6,15);
}

void second_six(){
// / second_middle_servo(1);delay(50);
// / second_top_servo(1);delay(50);
///  second_top_right_servo(0);delay(50);
///  second_top_left_servo(1);delay(50);
  second_bottom_left_servo(1);delay(50);
//  /second_bottom_right_servo(1);delay(50);
//  /second_bottom_servo(1);delay(50);
  sleep_pin_1(6,15);
}
void second_seven(){
  second_middle_servo(0);delay(50);
// / second_top_servo(1);delay(50);
  second_top_right_servo(1);delay(50);
  second_top_left_servo(0);delay(50);
  second_bottom_left_servo(0);delay(50);
  second_bottom_right_servo(1);delay(50);
  second_bottom_servo(0);delay(50);
  sleep_pin_1(6,15);
}

void second_eight(){
  second_middle_servo(1);delay(50);
///  second_top_servo(1);delay(50);
// / second_top_right_servo(1);delay(50);
  second_top_left_servo(1);delay(50);
  second_bottom_left_servo(1);delay(50);
  second_bottom_right_servo(1);delay(50);
  second_bottom_servo(1);delay(50);
  sleep_pin_1(6,15);
}

void second_nine(){
//  /second_middle_servo(1);delay(50);
// / second_top_servo(1);delay(50);
// / second_top_right_servo(1);delay(50);
//  /second_top_left_servo(1);delay(50);
  second_bottom_left_servo(0);delay(50);
//  /second_bottom_right_servo(1);delay(50);
// / second_bottom_servo(1);delay(50);
// / sleep_pin_1(6,15);
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                                                              *******             start of third number             *******
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void third_top_servo(int status){
 /*    status will be 0 for down, 1 for up. pulselen(3rd param to setPWM) will have to be set per servo basis due to how I attached the arms)
 *     
 *      **
 *     |  | 
 *      --
 *     |  |
 *      --
 */

  if (status == 1){
    for (uint16_t pulselen = 190; pulselen < 390; pulselen++) {
              pwm2.setPWM(0, 0, pulselen);
    }
  }
  else{
    for (uint16_t pulselen = 390; pulselen > 190; pulselen--) {
              pwm2.setPWM(0, 0, pulselen);
            }
        Serial.println("down");
  }
}

void third_top_right_servo(int status){
 /*    status will be 0 for down, 1 for up. pulselen(3rd param to setPWM) will have to be set per servo basis due to how I attached the arms)
 *     
 *      --
 *     |  *
 *      --
 *     |  |
 *      --
 */
 //   Serial.println(status);
  if (status == 1){
    for (uint16_t pulselen = 365; pulselen > 190; pulselen--) {
              pwm2.setPWM(1, 0, pulselen);
            }
  }
  else{
    for (uint16_t pulselen = 190; pulselen < 365; pulselen++) {
              pwm2.setPWM(1, 0, pulselen);
    }
  }
}

void third_top_left_servo(int status){
 /*    status will be 0 for down, 1 for up. pulselen(3rd param to setPWM) will have to be set per servo basis due to how I attached the arms)
 *     
 *      --
 *     *  | 
 *      --
 *     |  |
 *      --
 */
 //   Serial.println(status);
  if (status == 1){
    for (uint16_t pulselen1 = 280; pulselen1 < 480; pulselen1++) {
              pwm2.setPWM(2, 0, pulselen1);
    }  
  }
  else{
    for (uint16_t pulselen2 = 480; pulselen2 > 280; pulselen2--) {
              pwm2.setPWM(2, 0, pulselen2);
            }

  }
}

void third_bottom_left_servo(int status){
 /*    status will be 0 for down, 1 for up. pulselen(3rd param to setPWM) will have to be set per servo basis due to how I attached the arms)
 *     
 *      --
 *     |  | 
 *      --
 *     *  |
 *      --
 */
 //   Serial.println(status);
  if (status == 1){
    for (uint16_t pulselen1 = 230; pulselen1 < 390; pulselen1++) {
              pwm2.setPWM(3, 0, pulselen1);
    }  
   third_left = 1; 
//   //    Serial.println("up");
  }
  else{
    for (uint16_t pulselen2 = 390; pulselen2 > 230; pulselen2--) {
              pwm2.setPWM(3, 0, pulselen2);
            }
    third_left = 0;
//    //    Serial.println("down");
  }
}

void third_bottom_right_servo(int status){
 /*    status will be 0 for down, 1 for up. pulselen(3rd param to setPWM) will have to be set per servo basis due to how I attached the arms)
 *     
 *      --
 *     |  |
 *      --
 *     |  *
 *      --
 */
 //   Serial.println(status);
  if (status == 1){
    
    for (uint16_t pulselen1 = 370; pulselen1 > 200; pulselen1--) {
              pwm2.setPWM(4, 0, pulselen1);
            }  
   third_right = 1;
//   //    Serial.println("up");
  }
  else{
    for (uint16_t pulselen2 = 200; pulselen2 < 370; pulselen2++) {
              pwm2.setPWM(4, 0, pulselen2);
    }
    third_right = 0;
//    //    Serial.println("down");
  }
}

void third_bottom_servo(int status){
 /*    status will be 0 for down, 1 for up. pulselen(3rd param to setPWM) will have to be set per servo basis due to how I attached the arms)
 *     
 *      --
 *     |  | 
 *      --
 *     |  |
 *      **
 */
 //   Serial.println(status);
  if (status == 1){
    for (uint16_t pulselen = 380; pulselen > 190; pulselen--) {
              pwm2.setPWM(5, 0, pulselen);
            }  
//   //    Serial.println("up");
  }
  else{
    for (uint16_t pulselen = 190; pulselen < 380; pulselen++) {
              pwm2.setPWM(5, 0, pulselen);
    }
//    //    Serial.println("down");
  }
}

void third_middle_servo(int status){
 /*    status will be 0 for down, 1 for up. pulselen(3rd param to setPWM) will have to be set per servo basis due to how I attached the arms)
 *     
 *      --
 *     |  | 
 *      **
 *     |  |
 *      --
 */
 //   Serial.println(status);
  prev_right2 = third_right; 
  prev_left2 = third_left;
  third_bottom_right_servo(0);
  third_bottom_left_servo(0);
//  Serial.println("delaying 500");
  delay(500);
  if (status == 1){
      for (uint16_t pulselen = 360; pulselen > 175; pulselen--) {
                pwm2.setPWM(6, 0, pulselen);
              }  
//   //    Serial.println("up");
  }
  else{
    for (uint16_t pulselen = 175; pulselen < 360; pulselen++) {
              pwm2.setPWM(6, 0, pulselen);
    }
//    //    Serial.println("down");
  }
  delay(500);
//  third_bottom_right_servo(prev_right2);
//  third_bottom_left_servo(prev_left2);
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                                                              *******             start of third number functions             *******
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void third_zero(){
  third_middle_servo(0);delay(50);
//  third_top_servo(1);delay(50);
  third_top_right_servo(1);delay(50);
//  third_top_left_servo(1);delay(50);
  third_bottom_left_servo(1);delay(50);
  third_bottom_right_servo(1);delay(50);
//  third_bottom_servo(1);delay(50);/
  sleep_pin_2(0,7);
}

void third_one(){
  third_top_servo(0);delay(50);
// / third_top_right_servo(1);delay(50);
  third_top_left_servo(0);delay(50);
  third_bottom_left_servo(0);delay(50);
  third_bottom_right_servo(1);delay(50);
  third_bottom_servo(0);delay(50);
//  third_middle_servo(0);delay(50);/
  sleep_pin_2(0,7);
}

void third_two(){
  third_middle_servo(1);delay(50);
  third_top_servo(1);delay(50);
// / third_top_right_servo(1);delay(50);
// / third_top_left_servo(0);delay(50);
  third_bottom_left_servo(1);delay(50);
  third_bottom_right_servo(0);delay(50);
  third_bottom_servo(1);delay(50);
  sleep_pin_2(0,7);
}

void third_three(){
//  /third_top_servo(1);delay(50);
// / third_top_right_servo(1);delay(50);
//  /third_top_left_servo(0);delay(50);
  third_bottom_left_servo(0);delay(50);
  third_bottom_right_servo(1);delay(50);
//  /third_bottom_servo(1);delay(50);
// / third_middle_servo(1);delay(50);
  sleep_pin_2(0,7);
}

void third_four(){
  third_top_servo(0);delay(50);
// / third_top_right_servo(1);delay(50);
  third_top_left_servo(1);delay(50);
//  /third_bottom_left_servo(0);delay(50);
//  /third_bottom_right_servo(1);delay(50);
  third_bottom_servo(0);delay(50);
//  /third_middle_servo(1);delay(50);
  sleep_pin_2(0,7);
}

void third_five(){
  third_top_servo(1);delay(50);
  third_top_right_servo(0);delay(50);
//  /third_top_left_servo(1);delay(50);
// / third_bottom_left_servo(0);delay(50);
// / third_bottom_right_servo(1);delay(50);
  third_bottom_servo(1);delay(50);
///  third_middle_servo(1);delay(50);
  sleep_pin_2(0,7);
}

void third_six(){
// / third_top_servo(1);delay(50);
///  third_top_right_servo(0);delay(50);
///  third_top_left_servo(1);delay(50);
  third_bottom_left_servo(1);delay(50);
// / third_bottom_right_servo(1);delay(50);
// / third_bottom_servo(1);delay(50);
//  /third_middle_servo(1);delay(50);
  sleep_pin_2(0,7);
}
void third_seven(){
// / third_top_servo(1);delay(50);
  third_top_right_servo(1);delay(50);
  third_top_left_servo(0);delay(50);
  third_bottom_left_servo(0);delay(50);
  third_bottom_right_servo(1);delay(50);
  third_bottom_servo(0);delay(50);
  third_middle_servo(0);delay(50);
  sleep_pin_2(0,7);
}

void third_eight(){
// / third_top_servo(1);delay(50);
// / third_top_right_servo(1);delay(50);
  third_top_left_servo(1);delay(50);
  third_bottom_left_servo(1);delay(50);
  third_bottom_right_servo(1);delay(50);
  third_bottom_servo(1);delay(50);
  third_middle_servo(1);delay(50);
  sleep_pin_2(0,7);
}

void third_nine(){
//  /third_top_servo(1);delay(50);
// / third_top_right_servo(1);delay(50);
//  /third_top_left_servo(1);delay(50);
  third_bottom_left_servo(0);delay(50);
//  /third_bottom_right_servo(1);delay(50);
// / third_bottom_servo(1);delay(50);
// / third_middle_servo(1);delay(50);
  sleep_pin_2(0,7);delay(50);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                                                              *******             start of fourth number             *******
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void fourth_top_servo(int status){
 /*    status will be 0 for down, 1 for up. pulselen(3rd param to setPWM) will have to be set per servo basis due to how I attached the arms)
 *     
 *      **
 *     |  | 
 *      --
 *     |  |
 *      --
 */

  if (status == 1){
    for (uint16_t pulselen = 190; pulselen < 340; pulselen++) {
              pwm2.setPWM(7, 0, pulselen);
    }
  }
  else{
    for (uint16_t pulselen = 340; pulselen > 190; pulselen--) {
              pwm2.setPWM(7, 0, pulselen);
            }
  }
}

void fourth_top_right_servo(int status){
 /*    status will be 0 for down, 1 for up. pulselen(3rd param to setPWM) will have to be set per servo basis due to how I attached the arms)
 *     
 *      --
 *     |  *
 *      --
 *     |  |
 *      --
 */
 //   Serial.println(status);
  if (status == 1){
    for (uint16_t pulselen = 300; pulselen > 110; pulselen--) {
              pwm2.setPWM(8, 0, pulselen);
            }
  }
  else{
    for (uint16_t pulselen = 110; pulselen < 300; pulselen++) {
              pwm2.setPWM(8, 0, pulselen);
    }
  }
}

void fourth_top_left_servo(int status){
 /*    status will be 0 for down, 1 for up. pulselen(3rd param to setPWM) will have to be set per servo basis due to how I attached the arms)
 *     
 *      --
 *     *  | 
 *      --
 *     |  |
 *      --
 */
 //   Serial.println(status);
  if (status == 1){
    for (uint16_t pulselen1 = 280; pulselen1 < 460; pulselen1++) {
              pwm2.setPWM(9, 0, pulselen1);
    }  
  }
  else{
    for (uint16_t pulselen2 = 460; pulselen2 > 280; pulselen2--) {
              pwm2.setPWM(9, 0, pulselen2);
            }

  }
}

void fourth_bottom_left_servo(int status){
 /*    status will be 0 for down, 1 for up. pulselen(3rd param to setPWM) will have to be set per servo basis due to how I attached the arms)
 *     
 *      --
 *     |  | 
 *      --
 *     *  |
 *      --
 */
 //   Serial.println(status);
  if (status == 1){
    for (uint16_t pulselen1 = 270; pulselen1 < 490; pulselen1++) {
              pwm2.setPWM(15, 0, pulselen1);
    }  
   third_left = 1; 
//   //    Serial.println("up");
  }
  else{
    for (uint16_t pulselen2 = 490; pulselen2 > 270; pulselen2--) {
              pwm2.setPWM(15, 0, pulselen2);
            }
    third_left = 0;
//    //    Serial.println("down");
  }
}

void fourth_bottom_right_servo(int status){
 /*    status will be 0 for down, 1 for up. pulselen(3rd param to setPWM) will have to be set per servo basis due to how I attached the arms)
 *     
 *      --
 *     |  |
 *      --
 *     |  *
 *      --
 */
 //   Serial.println(status);
  if (status == 1){
    
    for (uint16_t pulselen1 = 380; pulselen1 > 210; pulselen1--) {
              pwm2.setPWM(11, 0, pulselen1);
            }  
   third_right = 1;
//   //    Serial.println("up");
  }
  else{
    for (uint16_t pulselen2 = 210; pulselen2 < 380; pulselen2++) {
              pwm2.setPWM(11, 0, pulselen2);
    }
    third_right = 0;
//    //    Serial.println("down");
  }
}

void fourth_bottom_servo(int status){
 /*    status will be 0 for down, 1 for up. pulselen(3rd param to setPWM) will have to be set per servo basis due to how I attached the arms)
 *     
 *      --
 *     |  | 
 *      --
 *     |  |
 *      **
 */
    Serial.println("fart coulds");
  if (status == 1){
    for (uint16_t pulselen = 450; pulselen > 270; pulselen--) {
              pwm2.setPWM(12, 0, pulselen);
            }  
       Serial.println("up fart");
  }
  else{
    for (uint16_t pulselen = 270; pulselen < 450; pulselen++) {
              pwm2.setPWM(12, 0, pulselen);
    }
    Serial.println("down fart");
  }
}

void fourth_middle_servo(int status){
 /*    status will be 0 for down, 1 for up. pulselen(3rd param to setPWM) will have to be set per servo basis due to how I attached the arms)
 *     
 *      --
 *     |  | 
 *      **
 *     |  |
 *      --
 */
 //   Serial.println(status);
  prev_right3 = fourth_right; 
  prev_left3 = fourth_left;
  fourth_bottom_right_servo(0);
  fourth_bottom_left_servo(0);
//  Serial.println("delaying 500");
  delay(500);
  if (status == 1){
      for (uint16_t pulselen = 275; pulselen > 110; pulselen--) {
                pwm2.setPWM(13, 0, pulselen);
             }  
//   //    Serial.println("up");
  }
  else{
    for (uint16_t pulselen = 110; pulselen < 275; pulselen++) {
              pwm2.setPWM(13, 0, pulselen);
    }
//    //    Serial.println("down");
  }
  delay(500);
//  fourth_bottom_right_servo(prev_right3);
//  fourth_bottom_left_servo(prev_left3);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                                                              *******             start of fourth number functions             *******
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void fourth_zero(){
  fourth_middle_servo(0);delay(50);
//  fourth_top_servo(1);delay(50);/
//  fourth_top_right_servo(1);delay(50);/
//  fourth_top_left_servo(1);delay(50);/
  fourth_bottom_left_servo(1);delay(50);
  fourth_bottom_right_servo(1);delay(50);
//  fourth_bottom_servo(1);delay(50);/
  sleep_pin_2(6,16);
}

void fourth_one(){
//  fourth_middle_servo(0);delay(50);
  fourth_top_servo(0);delay(50);
//  fourth_top_right_servo(1);delay(50);
  fourth_top_left_servo(0);delay(50);
  fourth_bottom_left_servo(0);delay(50);
  fourth_bottom_right_servo(1);delay(50);
  fourth_bottom_servo(0);delay(50);
  sleep_pin_2(6,15);
}

void fourth_two(){
  fourth_middle_servo(1);delay(50);
  fourth_top_servo(1);delay(50);
//  fourth_top_right_servo(1);delay(50);
//  fourth_top_left_servo(0);delay(50);
  fourth_bottom_left_servo(1);delay(50);
//  fourth_bottom_right_servo(0);delay(50);
  fourth_bottom_servo(1);delay(50);
  sleep_pin_2(6,15);
}

void fourth_three(){
//  fourth_middle_servo(1);delay(50);
//  fourth_top_servo(1);delay(50);
//  fourth_top_right_servo(1);delay(50);
//  fourth_top_left_servo(0);delay(50);
  fourth_bottom_left_servo(0);delay(50);
  fourth_bottom_right_servo(1);delay(50);
//  fourth_bottom_servo(1);delay(50);
  sleep_pin_2(6,15);
}

void fourth_four(){
//  fourth_middle_servo(1);delay(50);
  fourth_top_servo(0);delay(50);
//  fourth_top_right_servo(1);delay(50);
  fourth_top_left_servo(1);delay(50);
//  fourth_bottom_left_servo(0);delay(50);
//  fourth_bottom_right_servo(1);delay(50);
  fourth_bottom_servo(0);delay(50);
  sleep_pin_2(6,15);
}

void fourth_five(){
//  fourth_middle_servo(1);delay(50);
  fourth_top_servo(1);delay(50);
  fourth_top_right_servo(0);delay(50);
//  fourth_top_left_servo(1);delay(50);
//  fourth_bottom_left_servo(0);delay(50);
//  fourth_bottom_right_servo(1);delay(50);
  fourth_bottom_servo(1);delay(50);
  sleep_pin_2(6,15);
}

void fourth_six(){
//  fourth_middle_servo(1);delay(50);
//  fourth_top_servo(1);delay(50);
//  fourth_top_right_servo(0);delay(50);
//  fourth_top_left_servo(1);delay(50);
  fourth_bottom_left_servo(1);delay(50);
//  fourth_bottom_right_servo(1);delay(50);
//  fourth_bottom_servo(1);delay(50);
  sleep_pin_2(6,15);
}
void fourth_seven(){
  fourth_middle_servo(0);delay(50);
//  fourth_top_servo(1);delay(50);
  fourth_top_right_servo(1);delay(50);
  fourth_top_left_servo(0);delay(50);
  fourth_bottom_left_servo(0);delay(50);
  fourth_bottom_right_servo(1);delay(50);
  fourth_bottom_servo(0);delay(50);
  sleep_pin_2(6,15);
}

void fourth_eight(){
  fourth_middle_servo(1);delay(50);
//  fourth_top_servo(1);delay(50);
//  fourth_top_right_servo(1);delay(50);
  fourth_top_left_servo(1);delay(50);
  fourth_bottom_left_servo(1);delay(50);
  fourth_bottom_right_servo(1);delay(50);
  fourth_bottom_servo(1);delay(50);
  sleep_pin_2(6,15);
}

void fourth_nine(){
//  fourth_middle_servo(1);delay(50);/
//  fourth_top_servo(1);delay(50);
//  fourth_top_right_servo(1);delay(50);
//  fourth_top_left_servo(1);delay(50);
  fourth_bottom_left_servo(0);delay(50);
//  fourth_bottom_right_servo(1);delay(50);
//  fourth_bottom_servo(1);delay(50);
  sleep_pin_2(6,15);
}


void loop() {

  DS3231_get(&t);

  unsigned first_diget = (t.hour / 10U) % 10;
  unsigned second_diget = (t.hour / 1U) % 10;
  unsigned third_diget = (t.min / 10U) % 10;
  unsigned fourth_diget = (t.min / 1U) % 10;
  Serial.print("t.hour---> ");
  Serial.print(t.hour);
  Serial.print("      t.min--->");
  Serial.print(t.min);
  Serial.print("      t.sec--->");
  Serial.println(t.sec);

  if (t.hour > 11 or t.hour == 0){

    if(t.hour == 13){ //1pm
      first_diget = 0;
      second_diget = 1;
    }
    
    if(t.hour == 14){  //2pm
      first_diget = 0;
      second_diget = 2;
    }
    
    if(t.hour == 15){ //3pm
      first_diget = 0;
      second_diget = 3;
    }
    
    if(t.hour == 16){ //4pm
      first_diget = 0;
      second_diget = 4;
    }
    
    if(t.hour == 17){ //5pm
      first_diget = 0;
      second_diget = 5;
    }
    
    if(t.hour == 18){//6pm
      first_diget = 0;
      second_diget = 6;
    }
    
    if(t.hour == 19){//7pm
      first_diget = 0;
      second_diget = 7;
    }
    
    if(t.hour == 20){//8pm
      first_diget = 0;
      second_diget = 8;
    }
    
    if(t.hour == 21){//9pm
      first_diget = 0;
      second_diget = 9;
    }
    
    if(t.hour == 22){ //10pm
      first_diget = 1;
      second_diget = 0;
    }
    
    if(t.hour == 23){//11pm
      first_diget = 1;
      second_diget = 1;
    }
    
    if(t.hour == 0){//12pm
      first_diget = 1;
      second_diget = 2;
    }
  }

  
  if(prev_fourth < fourth_diget || fourth_diget == 0){
    if(first_diget == 0 && prev_first != first_diget){
      first_zero();
    }
    if(first_diget == 1 && prev_first != first_diget){
      first_one();
    }
//    if(first_diget == 2 && prev_first != first_diget){
//      first_two();
//    }
//    if(first_diget == 3 && prev_first != first_diget){
//      first_three();
//    }
//    if(first_diget == 4 && prev_first != first_diget){
//      first_four();
//    }
//    if(first_diget == 5 && prev_first != first_diget){
//      first_five();
//    }
//    if(first_diget == 6 && prev_first != first_diget){
//      first_six();
//    }
//    if(first_diget == 7 && prev_first != first_diget){
//      first_seven();
//    }
//    if(first_diget == 8 && prev_first != first_diget){
//      first_eight();
//    }
//    if(first_diget == 9 && prev_first != first_diget){
//      first_nine();
//    }
  
  
  
    if(second_diget == 0 && prev_second != second_diget){
      second_zero();
    }
    if(second_diget == 1 && prev_second != second_diget){
      second_one();
    }
    if(second_diget == 2 && prev_second != second_diget){
      second_two();
    }
    if(second_diget == 3 && prev_second != second_diget){
      second_three();
    }
    if(second_diget == 4 && prev_second != second_diget){
      second_four();
    }
    if(second_diget == 5 && prev_second != second_diget){
      second_five();
    }
    if(second_diget == 6 && prev_second != second_diget){
      second_six();
    }
    if(second_diget == 7 && prev_second != second_diget){
      second_seven();
    }
    if(second_diget == 8 && prev_second != second_diget){
      second_eight();
    }
    if(second_diget == 9 && prev_second != second_diget){
      second_nine();
    }
  
  
    
  
    if(third_diget == 0 && prev_third != third_diget){
      third_zero();
    }
    if(third_diget == 1 && prev_third != third_diget){
      third_one();
    }
    if(third_diget == 2 && prev_third != third_diget){
      third_two();
    }
    if(third_diget == 3 && prev_third != third_diget){
      third_three();
    }
    if(third_diget == 4 && prev_third != third_diget){
      third_four();
    }
    if(third_diget == 5 && prev_third != third_diget){
      third_five();
    }
    if(third_diget == 6 && prev_third != third_diget){
      third_six();
    }
    if(third_diget == 7 && prev_third != third_diget){
      third_seven();
    }
    if(third_diget == 8 && prev_third != third_diget){
      third_eight();
    }
    if(third_diget == 9 && prev_third != third_diget){
      third_nine();
    }
  
  
  
    
    if(fourth_diget == 0 && prev_fourth != fourth_diget){
      fourth_zero();
    }
    if(fourth_diget == 1 && prev_fourth != fourth_diget){
      fourth_one();
    }
    if(fourth_diget == 2 && prev_fourth != fourth_diget){
      fourth_two();
    }
    if(fourth_diget == 3 && prev_fourth != fourth_diget){
      fourth_three();
    }
    if(fourth_diget == 4 && prev_fourth != fourth_diget){
      fourth_four();
    }
    if(fourth_diget == 5 && prev_fourth != fourth_diget){
      fourth_five();
    }
    if(fourth_diget == 6 && prev_fourth != fourth_diget){
      fourth_six();
    }
    if(fourth_diget == 7 && prev_fourth != fourth_diget){
      fourth_seven();
    }
    if(fourth_diget == 8 && prev_fourth != fourth_diget){
      fourth_eight();
    }
    if(fourth_diget == 9 && prev_fourth != fourth_diget){
      fourth_nine();
    }
    prev_first = first_diget;
    prev_second = second_diget;
    prev_third = third_diget;
    prev_fourth = fourth_diget;
  }

}

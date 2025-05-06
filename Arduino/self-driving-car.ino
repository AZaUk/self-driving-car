#include <Servo.h>
#include "NewPing.h"

int servoPin = 8;
int R_EN = 2;
int L_EN = 3;
int LPWM = 4;
int RPWM = 5;
int left_sensor_pin = 12;
int right_sensor_pin = 7;
int far_left_sensor_pin = 9;
int far_right_sensor_pin = 10;

#define TILT 11
#define FRONT_SENSOR_SEND A0
#define FRONT_SENSOR_RECEIVE A1
#define RIGHT_BACK_SENSOR_SEND A4
#define RIGHT_BACK_SENSOR_RECEIVE A5
// #define LEFT_BACK_SENSOR_SEND A4
// #define LEFT_BACK_SENSOR_RECEIVE A5
// #define UPPER_SENSOR_SEND A2
// #define UPPER_SENSOR_RECEIVE A3

NewPing front_sensor_sonar(FRONT_SENSOR_SEND, FRONT_SENSOR_RECEIVE, 200);
// NewPing upper_sensor_sonar(UPPER_SENSOR_SEND, UPPER_SENSOR_RECEIVE, 400);
NewPing right_back_sensor_sonar(RIGHT_BACK_SENSOR_SEND, RIGHT_BACK_SENSOR_RECEIVE, 400);
//NewPing left_back_sensor_sonar(LEFT_BACK_SENSOR_SEND, LEFT_BACK_SENSOR_RECEIVE, 400);
Servo steeringServo;

int front_sensor_distance, upper_sensor_distance, right_back_sensor_distance, left_back_sensor_distance = 0;
int last_turning_direction = 2; // 1 - right, 0 - left, 2 - to go straight

int speed = 70; // 55 to pass a hill
bool stop_the_car = false;
bool far_left_sensor_used = false;
bool hill_detected = false;
bool obstacle_passed = false;
bool first_turn, second_turn = false;
bool turn_far_right_sensor_off = false;


void setup() {
  Serial.begin(9600);
  steeringServo.attach(servoPin);
  pinMode(R_EN, OUTPUT);
  pinMode(L_EN, OUTPUT);
  pinMode(LPWM, OUTPUT);
  pinMode(RPWM, OUTPUT);
  pinMode(left_sensor_pin, INPUT);
  pinMode(right_sensor_pin, INPUT);
  pinMode(far_left_sensor_pin, INPUT);
  pinMode(far_right_sensor_pin, INPUT);
  steeringServo.write(88);
  pinMode(TILT, INPUT);
}

void loop() {
  digitalWrite(R_EN, HIGH);
  digitalWrite(L_EN, HIGH);

// Get white line sensors value
  int leftSensorValue = digitalRead(left_sensor_pin);
  int rightSensorValue = digitalRead(right_sensor_pin);
  int farLeftSensorValue = digitalRead(far_left_sensor_pin);
  int farRightSensorValue = digitalRead(far_right_sensor_pin);

// Get ultrasonic sensors value
  int front_sensor_distance = front_sensor_sonar.ping_cm();
  delay(10);
  // int upper_sensor_distance = upper_sensor_sonar.ping_cm();
  // delay(10);
  int right_back_sensor_distance = right_back_sensor_sonar.ping_cm();
  delay(10);
  // int left_back_sensor_distance = left_back_sensor_sonar.ping_cm();

// Move the car
  if (!stop_the_car) analogWrite(RPWM, speed);

// White line sensors
  if (leftSensorValue == 0 && rightSensorValue == 0) {
    analogWrite(RPWM, 00); //stop the car
    steeringServo.write(90);
    stop_the_car = true;
  } else if (leftSensorValue == 0) { //LOW means object is detected
    last_turning_direction = 0; // turn left
    steeringServo.write(94); // turn left
  } else if (rightSensorValue == 0) {
    last_turning_direction = 1; // turn right
    steeringServo.write(83); // turn right
  } else if (farLeftSensorValue == 0) {
    last_turning_direction = 0;
    steeringServo.write(130); // sharper turn (dk if servo can handle that)
  } else if (farRightSensorValue == 0) {
    last_turning_direction = 1;
    steeringServo.write(65);
  }


// Detect a hill
  int tilt_sensed = digitalRead(TILT);
  while (tilt_sensed == 0 && !hill_detected && !stop_the_car) { // TILT IS SENSED 
    steeringServo.write(88);
    analogWrite(RPWM, speed + 70);
    hill_detected = true;
    delay(1250);
    tilt_sensed = 1;
  }
  if (tilt_sensed == 1 && hill_detected && !stop_the_car) {
    steeringServo.write(88);
    analogWrite(RPWM, speed - 15);
    tilt_sensed = 3;
  }

// Ultrasonic sensors (detect the obstacle)
   if (!obstacle_passed) {
     if (front_sensor_distance < 60 && front_sensor_distance > 20 && !first_turn) {
       speed = speed - 10;
       steeringServo.write(104);
       first_turn = true;
     }

     if (first_turn && right_back_sensor_distance < 30 && right_back_sensor_distance > 0) {
       second_turn = true;
       first_turn = false;
       steeringServo.write(70);
       turn_far_right_sensor_off = true;
       obstacle_passed = true;
       speed = speed + 10;
     }
   }




// Tests (servo, motor)


//  steeringServo.write(70); //50
//  delay(2000);
//
//  steeringServo.write(100);
//  delay(2000);
//
//  steeringServo.write(110); //130
//  delay(2000);
//
//  steeringServo.write(75);
//  delay(2000);
  
//  for(int speed = 40; speed < 80; speed += 10) {
//    analogWrite(l_pwm, speed);
//    delay(500);
//  }
//
//  for(int speed = 100; speed > 0; speed -= 10) {
//    analogWrite(l_pwm, speed);
//    delay(500);
//  }
}

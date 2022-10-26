#include "DRV8825.h"
// For RAMPS 1.4
#define X_STEP_PIN 54
#define X_DIR_PIN 55
#define X_ENABLE_PIN 38

#define Y_STEP_PIN 60
#define Y_DIR_PIN 61
#define Y_ENABLE_PIN 56

#define Z_STEP_PIN 46
#define Z_DIR_PIN 48
#define Z_ENABLE_PIN 62

// extruder 1
#define E0_STEP_PIN 26
#define E0_DIR_PIN 28
#define E0_ENABLE_PIN 24

// extruder 2
#define E1_STEP_PIN 36
#define E1_DIR_PIN 34
#define E1_ENABLE_PIN 30

DRV8825 frontLeft(E1_STEP_PIN, E1_DIR_PIN, E1_ENABLE_PIN, 200 * 64);
DRV8825 frontRight(Y_STEP_PIN, Y_DIR_PIN, Y_ENABLE_PIN, 200 * 64);
DRV8825 backLeft(E0_STEP_PIN, E0_DIR_PIN, E0_ENABLE_PIN, 200 * 64);
DRV8825 backRight(X_STEP_PIN, X_DIR_PIN, X_ENABLE_PIN, 200 * 64);

enum COMMANDS
{
  STOP = 0x00,
  FWD = 0x01,
  REV = 0x02,
  LEFT = 0x03,
  RIGHT = 0x04,
  HALT = 0xff,
};

byte last_command = STOP;

long last_command_time = 0;  // ms since last command
long command_timeout = 1000; // ms to wait for next command before stopping

const int idle_speed = 60;

void setup()
{
  // put your setup code here, to run once:
  // use USB
  Serial.begin(115200);
  Serial.println("starting");

  // set up the LED
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  frontLeft.set_enabled(true);
  frontLeft.set_direction(false);
  frontLeft.set_speed(0);

  backLeft.set_enabled(true);
  backLeft.set_direction(false);
  backLeft.set_speed(0);

  frontRight.set_enabled(true);
  frontRight.set_direction(false);
  frontRight.set_speed(0);

  backRight.set_enabled(true);
  backRight.set_direction(false);
  backRight.set_speed(0);

  Serial.println("setup done");
}

long last_frequency_check_time = 0;
long counter = 0;
// micros
#define frequency_check_interval 1000000

void loop()
{
  update_motors();

  // just monitoring loop frequency; can comment out
  // counter += 1;
  // if (micros() - last_frequency_check_time > frequency_check_interval)
  // {
  //   Serial.print("hz: ");
  //   Serial.println(counter, DEC);
  //   counter = 0;
  //   last_frequency_check_time = micros();
  // }
  read_serial();
}

void update_motors()
{
  frontLeft.update();
  frontRight.update();
  backLeft.update();
  backRight.update();
}

void read_serial()
{
  if (Serial.available())
  {
    last_command = Serial.read();
    // last_command = Serial.read();
    switch (last_command)
    {
    case STOP:
      frontLeft.set_speed(0);
      frontRight.set_speed(0);
      backLeft.set_speed(0);
      backRight.set_speed(0);
      break;
    case FWD:
      frontLeft.set_speed(idle_speed);
      frontRight.set_speed(idle_speed);
      backLeft.set_speed(idle_speed);
      backRight.set_speed(idle_speed);

      frontLeft.set_direction(false);
      frontRight.set_direction(false);
      backLeft.set_direction(false);
      backRight.set_direction(false);
      digitalWrite(LED_BUILTIN, HIGH);
      break;
    case REV:
      frontLeft.set_speed(idle_speed);
      frontRight.set_speed(idle_speed);
      backLeft.set_speed(idle_speed);
      backRight.set_speed(idle_speed);

      frontLeft.set_direction(true);
      frontRight.set_direction(true);
      backLeft.set_direction(true);
      backRight.set_direction(true);
      digitalWrite(LED_BUILTIN, LOW);
      break;

    case RIGHT:
      frontLeft.set_speed(idle_speed);
      frontRight.set_speed(idle_speed);
      backLeft.set_speed(idle_speed);
      backRight.set_speed(idle_speed);

      frontLeft.set_direction(true);
      frontRight.set_direction(false);
      backLeft.set_direction(true);
      backRight.set_direction(false);
      break;

    case LEFT:
      frontLeft.set_speed(idle_speed);
      frontRight.set_speed(idle_speed);
      backLeft.set_speed(idle_speed);
      backRight.set_speed(idle_speed);

      frontLeft.set_direction(false);
      frontRight.set_direction(true);
      backLeft.set_direction(false);
      backRight.set_direction(true);
      break;
    default:
      break;
    }
  }
}
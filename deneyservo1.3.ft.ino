#include <AccelStepper.h>
#include <BluetoothSerial.h>

#define MotorInterfaceType 4
                                      // 4-2-3-1
AccelStepper motor1(MotorInterfaceType, 22, 4, 5, 2);
                                      // 4-2-3-1
AccelStepper motor2(MotorInterfaceType, 12, 5/*21*/, 4/*14*/ , 25);
                                      // 4-2-3-1
AccelStepper motor3(MotorInterfaceType, 16, 19, 21, 15);

BluetoothSerial SerialBT;

char gelenMetin;
int x = 500;
int y = 500;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32");
  motor1.setMaxSpeed(1000.0);
  motor2.setMaxSpeed(1000.0);
  motor3.setMaxSpeed(1000.0);
}

void Tersi(AccelStepper &motor, int &position) {
  motor.setAcceleration(50.0);
  motor.setSpeed(-200);
  motor.moveTo(position);
  position += 500;
}

void Duz(AccelStepper &motor, int &position) {
  motor.setAcceleration(50.0);
  motor.setSpeed(200);
  motor.moveTo(position);
  position -= 500;
}

void loop() {
  if (SerialBT.available()) {
    gelenMetin = SerialBT.read();
    if (gelenMetin == 'sag') {
      Tersi(motor1, x);
    } else if (gelenMetin == 'sol') {
      Duz(motor1, y);
    } else if (gelenMetin == 'ust') {
      Tersi(motor2, x);
    } else if (gelenMetin == 'alt') {
      Duz(motor2, y);
    } else if (gelenMetin == 'tut') {
      Tersi(motor3, x);
    } else if (gelenMetin == 'brk') {
      Duz(motor3, y);
    }
  }

  motor1.run();
  motor2.run();
  motor3.run();
}

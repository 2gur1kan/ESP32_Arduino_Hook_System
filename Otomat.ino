#include <AccelStepper.h>
#include <BluetoothSerial.h>

#define MotorInterfaceType 4
// Pin sırası 4-2-3-1 (Ortak pin kullanabilmek için bu şekilde)
AccelStepper motor1(MotorInterfaceType, 22, 4, 5, 2);
AccelStepper motor2(MotorInterfaceType, 12, 5, 4, 25);
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
    if (gelenMetin == '1') {
      Tersi(motor1, x);
    } else if (gelenMetin == '2') {
      Duz(motor1, y);
    } else if (gelenMetin == '3') {
      Tersi(motor2, x);
    } else if (gelenMetin == '4') {
      Duz(motor2, y);
    } else if (gelenMetin == '5') {
      Tersi(motor3, x);
    } else if (gelenMetin == '6') {
      Duz(motor3, y);
    }
  }

  motor1.run();
  motor2.run();
  motor3.run();
}

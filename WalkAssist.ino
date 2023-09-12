// Motor A connections
int enA = 9;
int in1 = 8;
int in2 = 7;
// Motor B connections
int enB = 3;
int in3 = 5;
int in4 = 4;
// Motor strength
int ratio = 200 / 35;
#include <NewPing.h>
#define TRIGGER_PIN 11
#define TRIG_PIN_12 12
#define TRIG_PIN_2 2
// #define ECHO_PIN_L1 10
#define MAX_DISTANCE 400
NewPing sonar_P12(TRIG_PIN_12, TRIG_PIN_12, MAX_DISTANCE);
// NewPing sonar_L1(TRIGGER_PIN_L1, ECHO_PIN_L1, MAX_DISTANCE);
NewPing sonar_P2(TRIG_PIN_2, TRIG_PIN_2, MAX_DISTANCE);
NewPing sonar_P6(6, 6, MAX_DISTANCE);
NewPing sonar_P11(11, 11, MAX_DISTANCE);
float tempval1;
float tempval2;
int finalval;
void setup()
{
    Serial.begin(9600);
    // Set all the motor control pins to outputs
    pinMode(enA, OUTPUT);
    pinMode(enB, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
    // Turn off motors - Initial state
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
}
void loop()
{
    delay(500);
    Serial.print("Ping P2: ");
    int iterations = 2;
    tempval1 = 0;
    tempval2 = 0;
    tempval1 = ((sonar_P2.ping_median(iterations) / 2) * 0.0343);
    if (tempval1 > 60)
    {
        tempval1 = 60;
    }
    if (tempval1 - tempval2 > 60 || tempval1 - tempval2 < -60)
    {
        tempval2 = (tempval1 * 0.02) + (tempval2 * 0.98);
    }
    else
    {
        tempval2 = (tempval1 * 0.4) + (tempval2 * 0.6);
    }
    finalval = tempval2;
    // finalval = sonar.ping(MAX_DISTANCE) * 0.0343 / 2;
    Serial.print(finalval);
    Serial.println("cm");
    int motor_strength = (35 - (finalval - 5)) * ratio;
    if (finalval < 40)
    {
        Serial.println("On");
        motorOn_L(motor_strength);
    }
    else
    {
        Serial.println("Off");
        motorOn_L(0);
    }

    Serial.print("Ping P12: ");
    iterations = 2;
    tempval1 = 0;
    tempval2 = 0;
    tempval1 = ((sonar_P12.ping_median(iterations) / 2) * 0.0343);
    if (tempval1 > 60)
    {
        tempval1 = 60;
    }
    if (tempval1 - tempval2 > 60 || tempval1 - tempval2 < -60)
    {
        tempval2 = (tempval1 * 0.02) + (tempval2 * 0.98);
    }
    else
    {
        tempval2 = (tempval1 * 0.4) + (tempval2 * 0.6);
    }
    finalval = tempval2;
    // finalval = sonar.ping(MAX_DISTANCE) * 0.0343 / 2;
    Serial.print(finalval);
    Serial.println("cm");
    motor_strength = (35 - (finalval - 5)) * ratio;
    if (finalval < 40)
    {
        Serial.println("On");
        motorOn_R(motor_strength);
    }
    else
    {
        Serial.println("Off");
        motorOn_R(0);
    }

    Serial.print("Ping P6: ");
    iterations = 2;
    tempval1 = 0;
    tempval2 = 0;
    tempval1 = ((sonar_P6.ping_median(iterations) / 2) * 0.0343);
    if (tempval1 > 60)
    {
        tempval1 = 60;
    }
    if (tempval1 - tempval2 > 60 || tempval1 - tempval2 < -60)
    {
        tempval2 = (tempval1 * 0.02) + (tempval2 * 0.98);
    }
    else
    {
        tempval2 = (tempval1 * 0.4) + (tempval2 * 0.6);
    }
    finalval = tempval2;
    // finalval = sonar.ping(MAX_DISTANCE) * 0.0343 / 2;
    Serial.print(finalval);
    Serial.println("cm");

    Serial.print("Ping P11: ");
    iterations = 2;
    tempval1 = 0;
    tempval2 = 0;
    tempval1 = ((sonar_P11.ping_median(iterations) / 2) * 0.0343);
    if (tempval1 > 60)
    {
        tempval1 = 60;
    }
    if (tempval1 - tempval2 > 60 || tempval1 - tempval2 < -60)
    {
        tempval2 = (tempval1 * 0.02) + (tempval2 * 0.98);
    }
    else
    {
        tempval2 = (tempval1 * 0.4) + (tempval2 * 0.6);
    }
    finalval = tempval2;
    // finalval = sonar.ping(MAX_DISTANCE) * 0.0343 / 2;
    Serial.print(finalval);
    Serial.println("cm");
}
void motorOn_L(int strength)
{
    analogWrite(enB, strength);
    // Turn on motor A
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
}
void motorOn_R(int strength)
{
    analogWrite(enA, strength);
    // Turn on motor B
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
}
void motorOn(int strength)
{
    analogWrite(enA, strength);
    analogWrite(enB, strength);
    // Turn on motor A & B
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
}
void motorOff()
{
    // Turn off motors B
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
}
// This function lets you control spinning direction of motors
void directionControl()
{
    // Set motors to maximum speed
    // For PWM maximum possible values are 0 to 255
    analogWrite(enA, 50);
    analogWrite(enB, 50);
    // Turn on motor A & B
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    delay(2000);
    // Now change motor directions
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    delay(2000);
    // Turn off motors
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
}
// This function lets you control speed of the motors
void speedControl()
{
    // Turn on motors
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    // Accelerate from zero to maximum speed
    for (int i = 0; i < 256; i++)
    {
        analogWrite(enA, i);
        analogWrite(enB, i);
        delay(20);
    }
    // Decelerate from maximum speed to zero
    for (int i = 50; i >= 0; --i)
    {
        analogWrite(enA, i);
        analogWrite(enB, i);
        delay(20);
    }
    // Now turn off motors
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
}
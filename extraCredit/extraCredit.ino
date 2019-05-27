// LINE FOLLOWING CAR
// MAIN FILE

// Motor Constants
const int left_nslp_pin  = 31;  // nslp = not sleep --> set high --> digitalWrite
const int left_dir_pin   = 29;  // control direction of motor --> digitalWrite
const int left_pwm_pin   = 40;  // use to control motor speed --> analogWrite
const int right_nslp_pin = 11;
const int right_dir_pin  = 30;
const int right_pwm_pin  = 39;

// Phototransistor Constants
const int photoPin1 = 65; // left side of car
const int photoPin2 = 48;
const int photoPin3 = 64;
const int photoPin4 = 47;
const int photoPin5 = 52;
const int photoPin6 = 68;
const int photoPin7 = 53;
const int photoPin8 = 69; // right side of car

// Transistor Weight Constants
const double photoWeight1 = -1.0;
const double photoWeight2 = -0.7;
const double photoWeight3 = -0.35;
const double photoWeight4 = -0.1;
const double photoWeight5 =  0.1;
const double photoWeight6 =  0.35;
const double photoWeight7 =  0.7;
const double photoWeight8 =  1.0;

// LED Constants
const int IR_LED_odd = 45;
const int IR_LED_even = 61;
const int LED = BLUE_LED;

// Delay Constants
const int microDelay = 5;
const int milliDelay = 2;

// Past Directions
const double errorThreshold = 50;

// PID Constants
const double kP = 40;
const double kD = 100;

const double kSP = 10;
const double kSD = 0;

// Variables
double pastDir;
double pastMotorSpeed;
int lineCount;
int pastReadingCount;
int pastSpeedError;

bool inSchoolZone;

// Encoder variables
int diffR;
int diffL;
const double maxTicks = 10;

const int ticksPerRev = 12;
const double wheelDiameter = 7; // Measure real value, cm
const double wheelCirc = 3.14 * wheelDiameter;

const double schoolZoneSpeed = 5;
const double normalSpeed = 15;
const double baseSpeed = 40;

int targetSpeed;

void setup() {
    Serial.begin(9600);
  
    setUpMotorPins();

    // Set up diode pins
    pinMode(IR_LED_odd, OUTPUT);
    pinMode(IR_LED_even, OUTPUT);
    pinMode(LED, OUTPUT);

    digitalWrite(IR_LED_odd, HIGH);
    digitalWrite(IR_LED_even, HIGH);
    digitalWrite(LED, LOW);
    
    pastDir = 0;
    lineCount = 0;
    pastReadingCount = 0;
    inSchoolZone = false;
    pastSpeedError = 0;
    diffR = 0;
    diffL = 0;

    targetSpeed = normalSpeed;

    analogWrite(right_pwm_pin, baseSpeed);
    analogWrite(left_pwm_pin, baseSpeed);
}

void loop() {

    // Run diode
    photoPinMode(OUTPUT);
    dwPhotoPins(HIGH);

    delayMicroseconds(microDelay);

    photoPinMode(INPUT);

    delay(milliDelay);

    // Calculate the position based on the weights
    bool refL1 = digitalRead(photoPin1);
    bool refL2 = digitalRead(photoPin2);
    bool refL3 = digitalRead(photoPin3);
    bool refL4 = digitalRead(photoPin4);
    bool refL5 = digitalRead(photoPin5);
    bool refL6 = digitalRead(photoPin6);
    bool refL7 = digitalRead(photoPin7);
    bool refL8 = digitalRead(photoPin8);

    double error = refL1 * photoWeight1 + refL2 * photoWeight2
                     + refL3 * photoWeight3 + refL4 * photoWeight4
                     + refL5 * photoWeight5 + refL6 * photoWeight6
                     + refL7 * photoWeight7 + refL8 * photoWeight8;

    int readingCount = refL1 + refL2 + refL3 + refL4 + refL5 + refL6 + refL7 + refL8;

    double motorSpeed = kP * error + kD * (error - pastDir);

    Serial.print(readingCount);
    Serial.print('\n');

    // Encoder speed calculation
    double diffAverage = (diffR + diffL) / 2;
    double currSpeed = maxTicks / diffAverage / ticksPerRev / 120 * wheelCirc / 0.001;

    double speedError = targetSpeed - currSpeed;

    double encoderSpeed = kSP * speedError + kSD * (speedError - pastSpeedError);

    // if the car is seeing the line, so all the sensors are lit up
    if(readingCount >= 6 && pastReadingCount < 6)
    {
        lineCount++;

        switch(lineCount)
        {
          case 1:
            inSchoolZone = true;
            targetSpeed = schoolZoneSpeed;
            break;
          case 2:
            inSchoolZone = false;
            targetSpeed = normalSpeed;
            break;
          case 3:
            analogWrite(right_pwm_pin, 0);
            analogWrite(left_pwm_pin, 0);
            pastMotorSpeed = 0;
            delay(10);
            break;
          default:
            break;
        }
    }

    // if the car is seeing more than 3 sensor values, it is probably bogus and should not be counted
    else if(readingCount > 3)
    {
        motorSpeed = pastMotorSpeed;
    }

    if(inSchoolZone)
    {
        digitalWrite(LED, HIGH);
    }
    else
    {
        digitalWrite(LED, LOW);
    }

    analogWrite(right_pwm_pin, baseSpeed + encoderSpeed + motorSpeed);
    analogWrite(left_pwm_pin, baseSpeed + encoderSpeed - motorSpeed);

    pastDir = error;
    pastMotorSpeed = motorSpeed;
    pastReadingCount = readingCount;
    pastSpeedError = speedError;
}

void setUpMotorPins()
{
    pinMode(left_nslp_pin, OUTPUT);
    pinMode(left_dir_pin, OUTPUT);
    pinMode(left_pwm_pin, OUTPUT);

    pinMode(right_nslp_pin, OUTPUT);
    pinMode(right_dir_pin, OUTPUT);
    pinMode(right_pwm_pin, OUTPUT);

    digitalWrite(left_nslp_pin, HIGH);
    digitalWrite(left_dir_pin, LOW);

    digitalWrite(right_nslp_pin, HIGH);
    digitalWrite(right_dir_pin, LOW);
}

void photoPinMode(bool state)
{
    pinMode(photoPin1, state);
    pinMode(photoPin2, state);
    pinMode(photoPin3, state);
    pinMode(photoPin4, state);
    pinMode(photoPin5, state);
    pinMode(photoPin6, state);
    pinMode(photoPin7, state);
    pinMode(photoPin8, state);
}

void dwPhotoPins(bool state)
{
    digitalWrite(photoPin1, state);
    digitalWrite(photoPin2, state);
    digitalWrite(photoPin3, state);
    digitalWrite(photoPin4, state);
    digitalWrite(photoPin5, state);
    digitalWrite(photoPin6, state);
    digitalWrite(photoPin7, state);
    digitalWrite(photoPin8, state);
}

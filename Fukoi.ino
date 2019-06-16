/**********************************
 Name: Fukai
 Description: air quality advisor
 Auth: Elisabeth Lorenzi Fernandez
***********************************/

// Pin input for smoke detector
int smokeA0 = A3;

// Pin output for red, green, blue leds.
int redLed = 2;
int greenLed = 1;
int blueLed = 0;

// Value readed from sensor. Initialize for fist iteration.
int analogSensor = 255;
// For storing prevoius analogSensor value.
int lastValue = 0;
// Maximum variance between two sensor readings that is considered similar.
unsigned int tolerance = 2;

// Color palette used for the different color that we display.
// Green -> best quality
// ...
// Red -> lesser quality

int red[] = {255,0,0};
int fuchsia[] = {255,0,60};
int purple[] = {255,0,210};
int blue[] = {0,0,255};
int cyan[] = {0,255,255};
int green[] = {0,255,0};


// Initialize pin modes and smoke detector acquisition rate
void setup() 
{
  // input 
  pinMode(smokeA0, INPUT);
  // Serial debug used on Arduino UNO (prototype)
  // Serial.begin(9600);
  // output
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT); 
}

// We are using catodic leds, so we need to reverse RGB values.
void displayColor(int color[]) 
{
  analogWrite(redLed, 255 - color[0]);
  analogWrite(greenLed, 255 - color[1]);
  analogWrite(blueLed, 255 - color[2]);
}

// compare two values within an given
boolean similar(int current, int last, int margin)
{
  int diff = current - last;
  if (diff < 0)
    diff = last - current;
 // Serial.print("similar.debug.diff = ");
 // Serial.println(diff);

  if ( diff > tolerance)
    return false;
  else
    return true;
}

/* debug info
void debug(int sensor, int last)
{ 
  Serial.print("Pin A0: ");
  Serial.print(sensor);
  Serial.print(" lastValue: ");
  Serial.println(last);
  //delay(1000);
} */
 
// BEGIN

// infinite loop
void loop() 
{
  if (similar(analogSensor,lastValue,tolerance))
  {  
     // Serial.println("[Similar!]");
     // debug(analogSensor,lastValue);
     analogSensor = analogRead(smokeA0);

  } else {
      lastValue = analogSensor;
      analogSensor = analogRead(smokeA0);

      // debug info
      // Serial.println("[DIFFERENT]");
      // debug(analogSensor, lastValue);

      // Checks if it has reached the threshold value
      if (analogSensor > 215)
      {
          displayColor(red);
      } else if (analogSensor > 175)
      {
          displayColor(fuchsia);
      } else if (analogSensor > 150)
      {
          displayColor(purple);
      } else if (analogSensor > 100)
      {
          displayColor(blue);
      } else if (analogSensor > 50)
      {
          displayColor(cyan);
      } else {
          displayColor(green);
      }
  }
  // sleep for 100ms
  delay(1000);
}

// END

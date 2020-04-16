#include <dht.h>

dht DHT;
#define DHT11_PIN 6

#define ECHOPIN 3
#define TRIGPIN 2

int sensorPin = A0;
const int buzzer = 7;
unsigned int sensorValue = 0;
int i;
char userinput;

int red = 10; //For the red LED
int yellow = 9; // For the yellow LED
int green = 8; // For Green LED


float distance; //For the ultrasonic sensor
float InDistance; //Ultrasonic sensor


//Code Setup 

void setup() {
  Serial.begin(9600);
  pinMode(ECHOPIN, INPUT); //Setup for the ECHOPin on the sensor
  pinMode(TRIGPIN, OUTPUT); //Setup for the TRIGPIN on the sensor
  pinMode(sensorPin, INPUT); //Setup for the nightmode for part 3
  pinMode(red, OUTPUT); //Red LED setup
  pinMode(yellow, OUTPUT); //Yellow LED setup
  pinMode(green, OUTPUT); //Green LED setup
  pinMode(buzzer, OUTPUT);

}


void loop() {


  if (Serial.available() > 0)

  userinput = Serial.read();
  Serial.print(userinput);
  if (Serial.peek() == -1) {


    if  (userinput == '1') {

      digitalWrite (red, 1 );
      delay(2000);
      digitalWrite (red, 0);
      delay (0);
      digitalWrite (yellow, 1);
      delay(1000);
      digitalWrite (yellow, 0);
      delay(0);
      digitalWrite (green, 1);
      delay (2000);
      digitalWrite (green, 0);
      delay(0);
      digitalWrite (yellow, 1);
      delay(1000);
      digitalWrite(yellow, 0);
      delay(0);

    }





    else if (userinput == '2') {

      InDistance = RangeF();
      digitalWrite(red, HIGH);
      delay(2000);
      digitalWrite(red, LOW);
      delay(0);


      InDistance = RangeF();
      if (InDistance < 10)
      {
        i = 0;
        for (i = 0; i < 10; i++)
        {
          digitalWrite(yellow, HIGH);
          delay(50);
          digitalWrite(yellow, LOW);
          delay(50);
          if (i < 10) {
            tone(buzzer, 5000);
            delay(100);
            noTone(buzzer);
            delay(100);
          }
        }
      }






      InDistance = RangeF();
      digitalWrite(yellow, HIGH);
      delay(1000);
      digitalWrite(yellow, LOW);
      delay(0);


      InDistance = RangeF();
      if (InDistance < 10)
      {
        i = 0;
        for (i = 0; i < 10; i++)
        {
          digitalWrite(yellow, HIGH);
          delay(100);
          digitalWrite(yellow, LOW);
          delay(100);
          if (i < 10) {

            tone(buzzer, 5000);
            delay(100);
            noTone(buzzer);
            delay(100);
          }
        }
      }


      {

        InDistance = RangeF();
        digitalWrite(green, HIGH);
        delay(2000);
        digitalWrite(green, LOW);
        delay(0);

        //delay(2000);

        InDistance = RangeF();

        if (InDistance < 10)
        {
          i = 0;
          for (i = 0; i < 10; i++)
          {
            digitalWrite(yellow, HIGH);
            delay(100);
            digitalWrite(yellow, LOW);
            delay(100);

            if (i < 10) {
              digitalWrite(red, LOW);
              digitalWrite(green, LOW);

              tone(buzzer, 5000);
              delay(100);
              noTone(buzzer);
              delay(100);
            }
          }
        }

      }
      {

        InDistance = RangeF();
        digitalWrite(yellow, HIGH);
        delay(1000);
        digitalWrite(yellow, LOW);
        delay(0);

        //delay(1000);

        InDistance = RangeF();
        if (InDistance < 10)
        {
          i = 0;
          for (i = 0; i < 10; i++)
          {
            digitalWrite(yellow, HIGH);
            delay(100);
            digitalWrite(yellow, LOW);
            delay(100);
            if (i < 10) {
              digitalWrite(red, LOW);
              digitalWrite(green, LOW);

              tone(buzzer, 5000);
              delay(100);
              noTone(buzzer);
              delay(100);
            }

          }
        }
      }
    }


    else if (userinput == '3') {

      lightRadar();
      InDistance = RangeF();
      if (sensorValue < 200) {
        digitalWrite(red, HIGH);
        digitalWrite(yellow, LOW);
        digitalWrite(green, LOW);
      }

      if (InDistance < 10) {
        digitalWrite(red, LOW);
        digitalWrite(yellow, LOW);
        digitalWrite(green, HIGH);
      }
    }



    else if (userinput == '4') {

      weatherSpec();


    }
  }
}



//Range Finder function
int  RangeF() {


  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);

  distance = pulseIn(ECHOPIN, HIGH);
  distance = distance / 58;
  Serial.print(distance);
  Serial.println("cm");
  delay(200);

  return distance;
}


//Night Mode Function
void lightRadar() {
  sensorValue = analogRead(sensorPin);
  Serial.print("Sensor Outage:");
  Serial.println(sensorValue);
  delay(500);

  return sensorValue;
}

//Weather FUnction

//This is a added feature where the DHT-11 reads the current temperature of the room.
int weatherSpec() {
  int chk = DHT.read11(DHT11_PIN);
  if (DHT.temperature > 26) {
    Serial.print("The weather is quite high today, please stay hydrated");
    Serial.println(DHT.temperature);
    digitalWrite (red, 1 );
    delay(2000);
    digitalWrite (red, 0);
    delay (0);
    digitalWrite (yellow, 1);
    delay(1000);
    digitalWrite (yellow, 0);
    delay(0);
    digitalWrite (green, 1);
    delay (2000);
    digitalWrite (green, 0);
    delay(0);
    digitalWrite (yellow, 1);
    delay(1000);
    digitalWrite(yellow, 0);
    delay(0);

  }
  else if (DHT.temperature < 25) {
    Serial.print("Drive slowly as the roads are icy as the temperature is");
    Serial.println(DHT.temperature);

    InDistance = RangeF();
    i = 0;
    for (i = 0; i < 10; i++)

      digitalWrite(yellow, HIGH);
    delay(1000);
    digitalWrite(yellow, LOW);
    delay(0);



    return weatherSpec;

  }
}

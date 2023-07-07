#include <stdio.h>
#include <string.h>

//Description: GPS Test for A9G only, that is get the location.
//version:v1.0
//Date:2019/11/23
//Author:Charlin
//web: http://www.makerfabs.com
//


#define DEBUG true
int PWR_KEY = 9;
int RST_KEY = 6;
int LOW_PWR_KEY = 5;

bool ModuleState=false;
unsigned long timeCount = millis();

char NMEA_message[80];

float GPS_latitude, GPS_longitude, GPS_speed;

void setup()
{
    pinMode(PWR_KEY, OUTPUT);
    pinMode(RST_KEY, OUTPUT);
    pinMode(LOW_PWR_KEY, OUTPUT);
    digitalWrite(RST_KEY, LOW);
    digitalWrite(LOW_PWR_KEY, HIGH);
    digitalWrite(PWR_KEY, HIGH);

    SerialUSB.begin(115200);
    while (!SerialUSB) {
        ; // wait for serial port to connect
    }
    Serial1.begin(115200);
    digitalWrite(PWR_KEY, LOW);
    delay(3000);
    digitalWrite(PWR_KEY, HIGH);
    delay(5000);
    ModuleState=moduleStateCheck();
    if(ModuleState==false)//if it's off, turn on it.
    {
      digitalWrite(PWR_KEY, LOW);
      delay(3000);
      digitalWrite(PWR_KEY, HIGH);
      delay(5000);
      SerialUSB.println("Now turnning the A9/A9G on.");
    }

    //GPS test
    sendData("AT+GPS=1", 1000, DEBUG);//1: turn on GPS  0:Turn off GPS
    sendData("AT+GPSRD=1", 1000, DEBUG);//Read NEMA information every 10 seconds 

    //sendData("AT+LOCATION=2", 1000, DEBUG);//AT+LOCATION=X  //1:Get base address, 2:get gps address
        
    //sendData("AT+CCID", 3000, DEBUG);
    //sendData("AT+CREG?", 3000, DEBUG);
    //sendData("AT+CGATT=1", 1000, DEBUG);
    //sendData("AT+CGACT=1,1", 1000, DEBUG);
    //sendData("AT+CGDCONT=1,\"IP\",\"CMNET\"", 1000, DEBUG);
    
    //sendData("AT+CIPSTART=\"TCP\",\"www.mirocast.com\",80", 2000, DEBUG);
    //timeCount=millis();
    SerialUSB.println("Maduino A9/A9G GPS Test Begin!");
}

void loop() {
  /*if (Serial1.available() >= 80 && Serial1.read() == '$') {
    // read 1 line
    for (uint8_t i = 0; i < 80; i++) {
      NMEA_message[i] = Serial1.read();
      if (NMEA_message[i] == 10) {
        break;        
      }
    }
    // extract GPS speed in km/h if NMEA message starts with $GNVTG
    if (NMEA_message[0] == 'G' && NMEA_message[1] == 'N' && NMEA_message[2] == 'V' && NMEA_message[3] == 'T' && NMEA_message[4] == 'G') {
      for (uint8_t i = 5; i < 80; i++) {
        if (NMEA_message[i] == 'N') {
          uint8_t j = i+2;
          while (NMEA_message[j] != ',') {
            j += 1;
          }
          GPS_speed = 0.0;
          uint8_t dec_places = 255;
          for (uint8_t index = i+2; index < j; index++) {
            if (NMEA_message[index] == '.') {
              dec_places = 0;
            } else {
              GPS_speed = GPS_speed * 10 + NMEA_message[index] - 48;
            }
            if (dec_places < 255) {
              dec_places += 1;
            }
            
          }
          GPS_speed /= pow(10, dec_places-1);
          break;
        }
      }
    }
  }*/
  if (Serial1.available() >= 80 && Serial1.read() == '$') {
    // read 1 line
    for (uint8_t i = 0; i < 80; i++) {
      NMEA_message[i] = Serial1.read();
      if (NMEA_message[i] == 10) {
        break;        
      }
    }
    // extract GPS info if NMEA message starts with $GNRMC
    if (NMEA_message[0] == 'G' && NMEA_message[1] == 'N' && NMEA_message[2] == 'R' && NMEA_message[3] == 'M' && NMEA_message[4] == 'C') {
      for (uint8_t i = 5; i < 80; i++) {
        // skip time
        if (NMEA_message[i] == 'A' || NMEA_message[i] == 'V') {
          // extract latitude
          uint8_t j = i+2;
          while (NMEA_message[j] != ',') {
            j += 1;
          }
          GPS_latitude = 0.0;
          uint8_t dec_places = 255;
          for (uint8_t index = i+2; index < j; index++) {
            if (NMEA_message[index] == '.') {
              dec_places = 0;
            } else {
              GPS_latitude = GPS_latitude * 10 + NMEA_message[index] - 48;
            }
            if (dec_places < 255) {
              dec_places += 1;
            }
          }
          GPS_latitude /= pow(10, dec_places-1);
          float latitude_sec = (GPS_latitude - (int)GPS_latitude) * 100;
          int latitude_min = (int)GPS_latitude % 100;
          int latitude_deg = (int)(GPS_latitude/100);
          GPS_latitude = latitude_deg + (float)latitude_min/60 + latitude_sec/3600;
          if (NMEA_message[j+1] == 'S') {
            GPS_latitude *= -1;
          }
          SerialUSB.print("Latitude: ");
          SerialUSB.print(latitude_deg);
          SerialUSB.print("*");
          SerialUSB.print(latitude_min);
          SerialUSB.print('\'');
          SerialUSB.print(latitude_sec);
          SerialUSB.print(NMEA_message[j+1]);
          SerialUSB.print(", ");
          SerialUSB.print(GPS_latitude, 7);
          
          // extract longitude
          i = j + 1;
          j = i + 2;;
          while (NMEA_message[j] != ',') {
            j += 1;
          }
          GPS_longitude = 0.0;
          dec_places = 255;
          for (uint8_t index = i+2; index < j; index++) {
            if (NMEA_message[index] == '.') {
              dec_places = 0;
            } else {
              GPS_longitude = GPS_longitude * 10 + NMEA_message[index] - 48;
            }
            if (dec_places < 255) {
              dec_places += 1;
            }
          }
          GPS_longitude /= pow(10, dec_places-1);
          float longitude_sec = (GPS_longitude - (int)GPS_longitude) * 100;
          int longitude_min = (int)GPS_longitude % 100;
          int longitude_deg = (int)(GPS_longitude/100);
          GPS_longitude = longitude_deg + (float)longitude_min/60 + longitude_sec/3600;
          if (NMEA_message[j+1] == 'W') {
            GPS_longitude *= -1;
          }
          SerialUSB.print("\tLongitude: ");
          SerialUSB.print(longitude_deg);
          SerialUSB.print("*");
          SerialUSB.print(longitude_min);
          SerialUSB.print('\'');
          SerialUSB.print(longitude_sec);
          SerialUSB.print(NMEA_message[j+1]);
          SerialUSB.print(", ");
          SerialUSB.print(GPS_longitude, 7);

          // extract speed
          i = j + 1;
          j = i + 2;
          while (NMEA_message[j] != ',') {
            j += 1;
          }
          GPS_speed = 0.0;
          dec_places = 255;
          for (uint8_t index = i+2; index < j; index++) {
            if (NMEA_message[index] == '.') {
              dec_places = 0;
            } else {
              GPS_speed = GPS_speed * 10 + NMEA_message[index] - 48;
            }
            if (dec_places < 255) {
              dec_places += 1;
            }
          }
          GPS_speed /= pow(10, dec_places-1);
          GPS_speed *= 1.852; // convert form knot to km/h
          SerialUSB.print("\tSpeed: ");
          SerialUSB.print(GPS_speed);
          SerialUSB.println(" km/h");
          break;
        }
      }
    }
  }
  if (millis() - timeCount > 1000) {
    
    timeCount = millis();  
  }
  
}

bool moduleStateCheck()
{
    int i = 0;
    bool state=false;
    for (i = 0; i < 10; i++)
    {
        String msg = String("");
        msg = sendData("AT", 1000, DEBUG);
        if (msg.indexOf("OK") >= 0)
        {
            SerialUSB.println("A9/A9G Module had turned on.");
            state=true;
            return state;
        }
        delay(500);
    }
    return state;
}

String sendData(String command, const int timeout, boolean debug)
{
    String response = "";
    Serial1.println(command);
    long int time = millis();
    while ((time + timeout) > millis())
    {
        while (Serial1.available())
        {
            char c = Serial1.read();
            response += c;
        }
    }
    if (debug)
    {
        SerialUSB.print(response);
    }
    return response;
}

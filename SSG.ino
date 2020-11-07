#include <DHT.h>

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include <SPI.h>
#include <SD.h>
   
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);
DHT dht(2, DHT11);
File myFile;
unsigned long time;

int temp, humid;

void setup(void) 
{
  Serial.begin(9600);
  Serial.println("Pressure Sensor Test"); Serial.println("");
  
  if(!bmp.begin())
  {

    Serial.print("Ooops, no BMP085 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

  if(!SD.begin(4)){
    Serial.println("SD Card Initializing Failed");
    while(1);
  }
  
  Serial.println("SD Card Initializing Done");


}
 
void loop(void) 
{
  Serial.println("Sucess");
  
  sensors_event_t event;
  bmp.getEvent(&event);
  time = millis();
  if (event.pressure)
  {
    myFile = SD.open("value.txt", FILE_WRITE);

    temp = dht.readTemperature();
    humid = dht.readHumidity();
    
    Serial.println(time);
    myFile.print(time);
    myFile.print("    ");
    
    Serial.print("Pressure:    ");
    Serial.print(event.pressure);
    Serial.println(" hPa");
    myFile.print(event.pressure);
    myFile.print("    ");    
    
    float temperature;
    bmp.getTemperature(&temperature);
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" C");
    myFile.print(temperature);
    myFile.print("    ");
    
    float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;
    Serial.print("Altitude:    "); 
    Serial.print(bmp.pressureToAltitude(seaLevelPressure, event.pressure)); 
    Serial.println(" m");
    Serial.println("");
    myFile.print(bmp.pressureToAltitude(seaLevelPressure, event.pressure));
    myFile.println("    ");

    Serial.print("dht temp: ");
    Serial.print(temp);
    Serial.println(" C");
    myFile.print(temp);
    myFile.print("    ");

    Serial.print("humidity: ");
    Serial.print(humid);
    Serial.println(" ");
    myFile.print(humid);
    myFile.print("    ");

    myFile.close();
  }
  else
  {
    Serial.println("Sensor error");
  }
  delay(1000);
}

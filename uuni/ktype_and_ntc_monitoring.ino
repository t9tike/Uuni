//#include <DHT_U.h>
//#include <DHT.h>
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_I2CRegister.h>
#include <Adafruit_SPIDevice.h>
#include <Adafruit_MAX31855.h>
#include <SPI.h>
#include "Adafruit_MAX31855.h"

//NTC Excelistä saadut kertoimet epälineaarista kalibrointia varten
float x6 = -0.1207;
float x5 = 1.8582;
float x4 = -11.392;
float x3 = 36.833;
float x2 = -67.967;
float x1 = 89.915;
float x = -25.917;

//Termoparipinnit
#define MAXDO   3
#define MAXCS   4
#define MAXCLK  5
#define MAXDO2   6
#define MAXCS2   7
#define MAXCLK2  8

//termoparien alustus parametreinä pinnit
Adafruit_MAX31855 thermocouple(MAXCLK, MAXCS, MAXDO);
Adafruit_MAX31855 thermocouple2(MAXCLK2, MAXCS2, MAXDO2);

//DHT PINNI jne, tämä vain testausta varten
//#define DHT_PIN 9
//#define DHTTYPE DHT11
//DHT dht(DHT_PIN, DHTTYPE);

//Määritellään ntc-arvoja
float thermNominal = 100000; //ntc nominal resistance
float tempNominal = 25;      //nominal temperature *C
#define BUFFERSIZE 10 

//ntc1
float ntc1BCoeff = 4092; //bcoefficent ntc1
float ntc1SR = 26700; //seriesresistor ntc1

//ntc2
float ntc2BCoeff = 4092; //bcoefficent ntc2
float ntc2SR = 26700; //seriesresistor ntc2

//pinnejä
#define NTCPIN1 A0
#define NTCPIN2 A1

//jotain muuta
int ntc1Buffer[BUFFERSIZE];
int ntc2Buffer[BUFFERSIZE];

//aikamuuttuja loggausta varten
//int aika = 0;

void setup() {
  Serial.begin(9600);
  //dht.begin();
 
  /* termopareja varten odotellaan */
  while (!Serial) delay(1); 
  delay(500);
  if (!thermocouple.begin() && !thermocouple2.begin()) {
    //Serial.println("ERROR.");
    while (1) delay(10);
  }
}

void loop() {
  /* NTC TERMISTOREIDEN MUUTTUJIA */
  float ntc1Avg = 0;
  float ntc2Avg = 0;
  float ntc1Res = 0;
  float ntc2Res = 0;
  float ntc1Temp = 0;
  float ntc2Temp = 0;

  //aikamuuttujan kasvatus ja tulostus loggausta varten
  //Serial.print("Aika: ");
  //Serial.print(aika);
  //aika += 5;
  
  //DHT LÄMPÖTILAA, vain testausta varten
  //float t = dht.readTemperature();
  //Serial.print(" DHTTEMP: ");
  //Serial.print(t);

    //MAX31855 sisäiset lämpötilat
   //Serial.print("KTYPEIN1 : ");
   //Serial.println(thermocouple.readInternal());
   //Serial.print("KTYPEIN2 : ");
   //Serial.println(thermocouple2.readInternal());

  /* Termoparien lämpötilojen luku Adafruitin kirjaston avulla + arvojen kirjoittaminen sarjaportille */
   double c = thermocouple.readCelsius();
   if (isnan(c)) {
     //Serial.println("Something wrong with thermocouple!");
   } else {
     Serial.print("KTYPE1 : ");
     Serial.println(c);
   }
   double c2 = thermocouple2.readCelsius();
   if (isnan(c)) {
     //Serial.println("Something wrong with thermocouple!");
   } else {
     Serial.print("KTYPE2 : ");
     Serial.println(c2);
   }


  for(int i = 0; i < BUFFERSIZE; i++){      //analogRead arvot luetaan bufferitaulukoihin ja lasketaan yhteen muuttujaan
    ntc1Buffer[i] = analogRead(NTCPIN1);
    ntc2Buffer[i] = analogRead(NTCPIN2);
    ntc1Avg += ntc1Buffer[i];
    ntc2Avg += ntc2Buffer[i];
    delay(10);
  }

  ntc1Avg = countAverage(ntc1Avg);          //lasketaan keskiarvot NTC termistoreiden sensoriarvoista
  ntc2Avg = countAverage(ntc2Avg);

  /* 
  Serial.print("NTC1 AVERAGE: "); //debuggausta varten tulostuksia
  Serial.println(ntc1Avg);
  Serial.print("NTC22 AVERAGE: ");
  Serial.println(ntc2Avg);
  Serial.print("NTC11 EI AVERAGE: ");
  Serial.println(analogRead(NTCPIN1));
*/
  float uOut1 = ntc1Avg * (5 / 1024.0);
  float uOut2 = ntc2Avg * (5 / 1024.0);
/* Arvojen tulostuksia testausta ja kalibrointia varten */
/*
  Serial.print(" NTC1Sensori: ");
  Serial.print(ntc1Avg);
  Serial.print(" NTC2Sensori: ");
  Serial.print(ntc2Avg);
  Serial.print(" NTC1Uout: ");

  Serial.print(uOut1);
  Serial.print(" NTC2Uout: ");
  Serial.print(uOut2);
*/  
  ntc1Res = countResistance(ntc1Avg, ntc1SR); //lasketaan resistanssit thermistoreille
  ntc2Res = countResistance(ntc2Avg, ntc2SR);

  /*
  Serial.print(" NTC1RESISTANCE: ");
  Serial.print(ntc1Res);
  Serial.print(" NTC2RESISTANCE: ");
  Serial.print(ntc2Res);
  */
  
  ntc1Temp = steinhartB(ntc1Res, thermNominal, ntc1BCoeff, tempNominal);    //tehdään steinhartin kaavan mukaiset muutokset resistanssista lämpötilaksi
  ntc2Temp = steinhartB(ntc2Res, thermNominal, ntc2BCoeff, tempNominal);

  /* Sarjaportille NTC termistoreiden lämpötila-arvot, tällä hetkellä Steinhartin kaavalla lasketut */
  //Serial.print("NTC2 : ");
  //Serial.println(ntc2Temp);
  //Serial.print("NTC1 : ");
  //Serial.println(ntc1Temp);  

/* Excelin avulla tehty epälineaarinen kalibrointi, alla niiden avulla saadut arvot */

  float ntc1ExcelTemp = excelNtc(uOut1);
  float ntc2ExcelTemp = excelNtc(uOut2);

  Serial.print("NTC1 : ");
  Serial.println(ntc1ExcelTemp);
  Serial.print("NTC2 : ");
  Serial.println(ntc2ExcelTemp);


  delay(5000);
}


//keskiarvolaskuri
float countAverage(float average){
  float realAvg = average / BUFFERSIZE;
  return realAvg;
}

//resistanssilaskuri
float countResistance(float analog, float resistor){
  float resistance = 1024 / 5;
  resistance = analog / resistance;
  resistance = (5 * resistor) / resistance - resistor;
  
  return resistance;
}

//steinhart 
float steinhartB(float resistance, float thermnominal, float bcoeff, float tempnom){
  float steinhart;
  steinhart = resistance / thermnominal;       // (R/Ro)
  steinhart = log(steinhart);                  // ln(R/Ro)
  steinhart /= bcoeff;                         // 1/B * ln(R/Ro)
  steinhart += 1.0 / (tempnom + 273.15);       // + (1/To)
  steinhart = 1.0 / steinhart;                 // Invert
  steinhart -= 273.15;                         // convert absolute temp to C
  return steinhart;
}

//Excel kertoimilla ntc lämpötilalaskurifunktio
float excelNtc(float uOut){
  //y = -0,1207x6 + 1,8582x5 - 11,392x4 + 36,833x3 - 67,967x2 + 89,915x - 25,917
  double u6 = pow(uOut, 6);
  double u5 = pow(uOut, 5);
  double u4 = pow(uOut, 4);
  double u3 = pow(uOut, 3);
  double u2 = pow(uOut, 2);

  float ntcTempExcel = x6 * u6 + x5 * u5 + x4 * u4 + x3 * u3 + x2 * u2 + x1 * uOut + x;

  return ntcTempExcel;
  
}

/*

 Sample code for Shinyei PPD42NS Particle Sensor. 
 http://www.sca-shinyei.com/pdf/PPD42NS.pdf

 This code measures the concentration of particulate matter in air defined as:
      particles per .01 cubic ft ( particles per 283 mL )

 Based on work by Chris Nafis http://www.howmuchsnow.com/arduino/airquality/grovedust/
  
 Connections:
 
   Sensor Pin 1 => Arduino GND
   Sensor Pin 3 => Arduino +5VDC
   Sensor Pin 4 => Arduino Digital Pin 3

*/

int pin = 3;
// Sample time in milliseconds 30 seconds
unsigned long sampletime_ms = 30000;
unsigned long starttime;
unsigned long duration = 0;
unsigned long elapsedtime = 0;
unsigned long timestamp = 0;

float ratio = 0;
float concentration = 0;

void setup() {
  Serial.begin(9600);
  pinMode(pin,INPUT);
  // Get current time to measure sample time
  starttime = millis();
}

void loop() {
  // Wait for low pulse and return pulse width duration. Time in micro seconds.
  duration = duration + pulseIn(pin, LOW);
  elapsedtime=millis()-starttime;
  // If sampling time is reached (30 seconds) then calculate concentration.
  if (elapsedtime > sampletime_ms) {
    ratio = duration/(elapsedtime*10.0);
    // Equation derived from datasheet by Chris Nafis
    concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62;
    timestamp=millis()/1000;
    Serial.print("Timestamp: ");
    Serial.print(timestamp);
    Serial.print(" Concentration: ");
    Serial.print(concentration);
    Serial.println(" particles per .01 cu ft");
    // Reset values for next sampling period.
    duration = 0;
    starttime = millis();
  }
}

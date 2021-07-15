// Soil Sensor and Battery Monitoring Node 206
//Author: Reese Holford



// Enable debug prints
#define MY_DEBUG

// Enable passive mode
#define MY_PASSIVE_NODE

// Passive mode requires static node ID
#define MY_NODE_ID 206

// Enable and select radio type attached
#define MY_RADIO_RF24

#include <MySensors.h>

#define SoilSensor_ID 0   // Id of the Soil Sensor
#define Battery_ID 1     // Id of the Battery
#define Solar_ID 2      //Id of Solar Panel

// Initialize general message
MyMessage msg(SoilSensor_ID, V_LEVEL);
MyMessage bat(Battery_ID, V_VOLTAGE);
MyMessage sol(Solar_ID, V_VOLTAGE);

//Initialize Sensor pin and output value sent 
int sensor_pin = A1; 
int battery_pin = A0;
int solar_pin = A2; //not used
int output_value;
int Green_LED = 3;
int Red_LED = 4;
int Signal_LED = 5;

//Initialize resistors and voltage calculations
float value = 0.0;
float value2 = 0.0;
float voltage;
float voltage2;
float R1 = 100000.0;
float R2 = 10000.0;


void setup()
{
 Serial.begin(9600);
 pinMode(Green_LED, OUTPUT);
 pinMode(Red_LED, OUTPUT);
}

void presentation()
{
  // Send the sketch version information to the gateway and controller
  sendSketchInfo("Soil Sensor Node 206", "1.0");

  // Register all sensors to gw (they will be created as child devices)
  present(SoilSensor_ID, S_MOISTURE);
  present(Battery_ID, S_MULTIMETER);
  present(Solar_ID, S_MULTIMETER);
  
}

void loop()
{
  // generate soil sensor data and send
  output_value= analogRead(sensor_pin);
  output_value = map(output_value,615,10,0,100);
  Serial.print("Moisture : ");
  Serial.print(output_value);
  Serial.println("%");
  send(msg.set(output_value));
  digitalWrite(Signal_LED, HIGH);
  delay(1000);
  digitalWrite(Signal_LED, LOW);
  delay(1000);

  //Send Battery Voltage
  value = analogRead(battery_pin);
 //voltage = value * ((5.0 / 1024) * ((R1 + R2) / R2));// for higher voltage sources
 voltage = value * ((4.2 / 1024));     //18650 Battery Voltage = 4.2 Volts
  Serial.print("Battery Voltage = ");
  Serial.println(voltage);
  send(bat.set(voltage, 2));
  delay(1000);

  //Send Solar Voltage
  //value2 = analogRead(solar_pin);
  //voltage2 = (value2 * (5.0 / 1024));
  //Serial.print("Solar Voltage = ");
  //Serial.println(voltage2);
  //send(sol.set(voltage2, 2));
  //delay(1000);


if (voltage >= 3.00){
  digitalWrite(Green_LED, HIGH);
}
  else{
  digitalWrite(Green_LED, LOW);
}

if (voltage <= 3.10){
  digitalWrite(Red_LED, HIGH);
}
  else{
  digitalWrite(Red_LED, LOW);
}


  
}

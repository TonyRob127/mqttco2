/* CO2 sensor simulation, publish data in an MQTT network.
Created by Juan Antonio Robledo Lara https://github.com/TonyRob127/mqttco2
Last mod: Feb 4th 2022 */

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

//callbacks
void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message: ");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char) payload[i]);
    }

    Serial.println();
    Serial.println("------------------");
  
  }
  
//WiFi info
const char *ssid = ""; //Enter WiFi name
const char *password = ""; //Enter WiFi passoword

//client/broker info
const char *mqtt_broker = "192.168.0.103";//Enter broker address
const char *topic = "co2/laboratory";
String client_id = "sensor_3";
const int mqtt_port = 1883; //Enter broker port

//creation of WiFi and MQTT clients
WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  
  //Serial communication
  Serial.begin(9600);

   //WiFi network connection
   delay(1000);
   WiFi.begin(ssid, password);
   Serial.println("Connecting to WiFi");
   while (WiFi.status() != WL_CONNECTED)
   {
    delay(1000);
    Serial.print(".");
    }
    Serial.println("\nWiFi connected!!");
    Serial.print("Sensor_3 IP address: "); 
    Serial.println(WiFi.localIP());

    //declare callbacks
    client.setCallback(callback);
    
    //Broker connection
    client.setServer(mqtt_broker, mqtt_port);
    delay(2000);
    Serial.print("Preparing connection to broker: ");
    Serial.println(mqtt_broker);
    delay(1000);
    Serial.printf("The client **%s** is attempting to connect to the broker...\n", client_id);
    while(!client.connected())
    {
      if(client.connect(client_id.c_str()))
      {
        Serial.println("Succesful connection to broker!!");
        } else
        {
          Serial.print("failed with state ");
          Serial.println(client.state());
          delay(2000);
          }
      }

      //Subscribe to topic
      //delay(1000);
      //Serial.print("Preparing to subscribe to topic: ");
      //Serial.println(topic);
      //client.subscribe(topic); // receives message from topic
      
      Serial.println("Starting publishing loop...");
      Serial.println("------------------");
}

void loop() {
  //Publishing loop
  delay(5000);
  int randNumber = random(0,100);
  //Serial.println(randNumber);
  String msg_string = String(randNumber);
  //const char *charBuf[50];
  //msg_string.toCharArray(charBuf, 50); 
  //Serial.println(msg_string);
  client.publish(topic, (char*) msg_string.c_str());
  client.loop();
}

/*
 Receiver code
 
*/
#include <SPI.h>              // include libraries
#include <LoRa.h>

#define nss 5
#define rst 34
#define dio0 2

boolean flag1 = false;
boolean flag2 = false;

boolean flag3 = false;
boolean flag4 = false; 

int RLY1=12;
int RLY2=13;
int RLY3=14;
int RLY4=27;

int Sensor1 = 0; 
int Sensor2 = 0; 
int Sensor3 = 0; 
int Sensor4 = 0; 

int relay1Status;
int relay2Status;
int relay3Status;
int relay4Status;

String outgoing;              // outgoing message

byte msgCount = 0;            // count of outgoing messages
byte localAddress = 0xFF;     // address of this device
byte destination = 0xBB;      // destination to send to
long lastSendTime = 0;        // last send time
int interval = 100;          // interval between sends

String statusmessage = "";

void setup() {
  Serial.begin(9600);                   // initialize serial


 pinMode(RLY1,OUTPUT);
  pinMode(RLY2,OUTPUT);
    pinMode(RLY3,OUTPUT);
      pinMode(RLY4,OUTPUT);
 LoRa.setPins(nss, rst, dio0);
  Serial.println("LoRa Duplex");

  if (!LoRa.begin(433E6)) {             // initialize ratio at 915 MHz
    Serial.println("LoRa init failed. Check your connections.");
    while (true);                       // if failed, do nothing
  }

  Serial.println("LoRa init succeeded.");
}

void loop() {

  if (millis() - lastSendTime > interval) {
  relay1Status = digitalRead(RLY1);
       relay2Status = digitalRead(RLY2);
        relay3Status = digitalRead(RLY3);
         relay4Status = digitalRead(RLY4);
        statusmessage = statusmessage + relay1Status + "," + relay2Status + "," + relay3Status + "," + relay4Status;
        sendMessage(statusmessage); 
delay(1);
statusmessage = "";
    lastSendTime = millis();            // timestamp the message
    interval = random(50) + 100;  
  }
  

  // parse for a packet, and call onReceive with the result:
  onReceive(LoRa.parsePacket());
}

void sendMessage(String outgoing) {
  LoRa.beginPacket();                   // start packet
  LoRa.write(destination);              // add destination address
  LoRa.write(localAddress);             // add sender address
  LoRa.write(msgCount);                 // add message ID
  LoRa.write(outgoing.length());        // add payload length
  LoRa.print(outgoing);                 // add payload
  LoRa.endPacket();                     // finish packet and send it
  msgCount++;                           // increment message ID
}

void onReceive(int packetSize) {
  if (packetSize == 0) return;          // if there's no packet, return

  // read packet header bytes:
  int recipient = LoRa.read();          // recipient address
  byte sender = LoRa.read();            // sender address
  byte incomingMsgId = LoRa.read();     // incoming msg ID
  byte incomingLength = LoRa.read();    // incoming msg length

  String incoming = "";

  while (LoRa.available()) {
    incoming += (char)LoRa.read();
  }

  if (incomingLength != incoming.length()) {   // check length for error
    Serial.println("error: message length does not match length");
   ;
    return;                             // skip rest of function
  }

  // if the recipient isn't this device or broadcast,
  if (recipient != localAddress && recipient != 0xFF) {
    Serial.println("This message is not for me.");
    ;
    return;                             // skip rest of function
  }

  // if message is for this device, or broadcast, print details:
  Serial.println("Received from: 0x" + String(sender, HEX));
  Serial.println("Sent to: 0x" + String(recipient, HEX));
  Serial.println("Message ID: " + String(incomingMsgId));
  Serial.println("Message length: " + String(incomingLength));
  Serial.println("Message: " + incoming);
  Serial.println("RSSI: " + String(LoRa.packetRssi()));
  Serial.println("Snr: " + String(LoRa.packetSnr()));
  Serial.println();
   String q = getValue(incoming, ',', 0); 
String r = getValue(incoming, ',', 1); 
String s = getValue(incoming, ',', 2); 
String t = getValue(incoming, ',', 3); 
Sensor1 = q.toInt();
Sensor2 = r.toInt();
Sensor3 = s.toInt();
Sensor4 = t.toInt();
if((Sensor1 == 0)&&(flag1==true))
{
 
  digitalWrite(RLY1,HIGH);
   relay1Status = 1;
  Serial.println("Relay 1 is turned on");
  flag1=false;
}

if((Sensor1 == 1)&&(flag1 ==false))
{

  digitalWrite(RLY1,LOW);
   relay1Status = 0;
  Serial.println("Relay 1 is turned off");
  flag1=true;
}
if((Sensor2 == 0)&&(flag2==true))
{
 
  digitalWrite(RLY2,HIGH);
   relay2Status = 0;
  Serial.println("Relay 2 is turned on");
  flag2=false;
}

if((Sensor2 == 1)&&(flag2 ==false))
{

  digitalWrite(RLY2,LOW);
  relay2Status = 0;
  Serial.println("Relay 2 is turned off");
  flag2=true;
}
if((Sensor3 == 0)&&(flag3==true))
{
 
  digitalWrite(RLY3,HIGH);
  relay3Status = 1;
  Serial.println("Relay 3 is turned on");
  flag3=false;
}

if((Sensor3 == 1)&&(flag3 ==false))
{

  digitalWrite(RLY3,LOW);
  relay3Status = 0;
  Serial.println("Relay 3 is turned off");
  flag3=true;
}

if((Sensor4 == 0)&&(flag4==true))
{
 
  digitalWrite(RLY4,HIGH);
  relay4Status = 1;
  Serial.println("Relay 4 is turned on");
  flag4=false;
}

if((Sensor4 == 1)&&(flag4 ==false))
{

  digitalWrite(RLY4,LOW);
  relay4Status = 0;
  Serial.println("Relay 4 is turned off");
  flag4=true;
}

incoming = "";
  
}
String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;
 
    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

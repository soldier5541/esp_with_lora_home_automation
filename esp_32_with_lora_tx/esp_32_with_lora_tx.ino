/*
  Transmitter code
  
*/
#include <SPI.h>              // include libraries
#include <LoRa.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define nss 5
#define rst 34
#define dio0 2


int sw1 = 33; 
int sw2 = 13; 
int sw3 = 14; 
int sw4 = 26;
int Sensor1 = 0; 
int Sensor2 = 0; 
int Sensor3 = 0;  
int Sensor4 = 0;  
boolean bflag = false;
String outgoing;              // outgoing message

byte msgCount = 0;            // count of outgoing messages
byte localAddress = 0xBB;     // address of this device
byte destination = 0xFF;      // destination to send to
long lastSendTime = 0;        // last send time
int interval = 100;          // interval between sends

// For Oled display
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
 
String Mymessage = "";
void setup() {
  Serial.begin(9600);                   // initialize serial
   LoRa.setPins(nss, rst, dio0);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(WHITE);

 
    pinMode(sw1, INPUT_PULLUP);
  pinMode(sw2, INPUT_PULLUP); 
  pinMode(sw3, INPUT_PULLUP); 
 pinMode(sw4, INPUT_PULLUP);

  Serial.println("LoRa Duplex");

  if (!LoRa.begin(433E6)) {             // initialize ratio at 915 MHz
    Serial.println("LoRa init failed. Check your connections.");
    while (true);                       // if failed, do nothing
  }

  Serial.println("LoRa init succeeded.");
}

void loop() {
  
  if (millis() - lastSendTime > interval) {
   Sensor1 = digitalRead(sw1);
    delay(1);
    Sensor2 = digitalRead(sw2); 
    delay(1);
    Sensor3 = digitalRead(sw3);
    delay(1);
       Sensor4 = digitalRead(sw4);
    delay(1);
    Mymessage = Mymessage + Sensor1 +"," + Sensor2 + "," + Sensor3 +"," + Sensor4;  
    sendMessage(Mymessage);
    delay(1);
    Mymessage = "";
    
    Serial.println("Sending " + Mymessage);
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

    //clear display
  display.clearDisplay();

  display.setTextSize(2);
  display.setCursor(0,0);
  display.print("Status:");

  display.setTextSize(3);
  display.setCursor(0, 28);
  display.print(incoming);

display.display(); 
}

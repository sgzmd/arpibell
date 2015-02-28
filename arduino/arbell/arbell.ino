#include <EtherCard.h>

// ethernet interface mac address, must be unique on the LAN
static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };

byte Ethernet::buffer[700];
static uint32_t timer;

const char website[] PROGMEM = "www.google.com";

// #include <Wire.h>

// #define SLAVE_ADDRESS 0x05
// int number = 0;
// int state = 0;

void setup() {
  // pinMode(13, OUTPUT);
  Serial.begin(9600);         // start serial for output
  // // initialize i2c as slave
  // Wire.begin(SLAVE_ADDRESS);

  // // define callbacks for i2c communication
  // Wire.onReceive(receiveData);
  // Wire.onRequest(sendData);

  if (ether.begin(sizeof Ethernet::buffer, mymac) == 0) 
    Serial.println(F("Failed to access Ethernet controller"));
  if (!ether.dhcpSetup())
    Serial.println(F("DHCP failed"));

  ether.printIp("IP:  ", ether.myip);
  ether.printIp("GW:  ", ether.gwip);  
  ether.printIp("DNS: ", ether.dnsip);  

  if (!ether.dnsLookup(website))
    Serial.println("DNS failed");
    
  ether.printIp("SRV: ", ether.hisip);

  Serial.println("Ready!");
}

// called when the client request is complete
static void my_callback (byte status, word off, word len) {
  Serial.println(">>>");
  Ethernet::buffer[off+300] = 0;
  Serial.print((const char*) Ethernet::buffer + off);
  Serial.println("...");
}

void loop() {
  ether.packetLoop(ether.packetReceive());
  int sensorValue = analogRead(A3);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):

  if (sensorValue > 500) {
    Serial.println("Ding-dong!!");
    Serial.println(sensorValue);

    Serial.println();
    Serial.print("<<< REQ ");
    ether.browseUrl(PSTR("/foo/"), "bar", website, my_callback);

    delay(5000);
  } else {
    delay(100);
  }
}


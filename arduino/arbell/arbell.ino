#include <EtherCard.h>

// ethernet interface mac address, must be unique on the LAN
static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };

byte Ethernet::buffer[700];
static uint32_t timer;

const char website[] PROGMEM = "rkdoorbell.appspot.com";

void setup() {
  Serial.begin(9600);         // start serial for output

  if (ether.begin(sizeof Ethernet::buffer, mymac) == 0) {
    Serial.println(F("Failed to access Ethernet controller"));
  }
  
  if (!ether.dhcpSetup()) {
    Serial.println(F("DHCP failed"));
  }

  ether.printIp("IP:  ", ether.myip);
  ether.printIp("GW:  ", ether.gwip);  
  ether.printIp("DNS: ", ether.dnsip);  

  if (!ether.dnsLookup(website)) {
    Serial.println("DNS failed");
  }
    
  ether.printIp("SRV: ", ether.hisip);

  Serial.println("Initialization completed");
}

// called when the client request is complete 
static void my_callback (byte status, word off, word len) {
  Serial.println(">>>");
  Ethernet::buffer[off+300] = 0;
  Serial.print((const char*) Ethernet::buffer + off);
  Serial.println("...");
}

void loop() {
  // Process ethernet packet
  ether.packetLoop(ether.packetReceive());
  int sensorValue = analogRead(A3);

  // generally anything above 0 is good, but 500 just to be sure
  // as this should correspond to ~ 1.5V
  if (sensorValue > 500) {
    Serial.println("Ding-dong!!");
    Serial.println(sensorValue);

    Serial.println();
    Serial.print("<<< REQ ");
    ether.browseUrl(PSTR("/doorbell"), "", website, my_callback);

    // If there was a callout, we can sleep safely for bell 
    // to finish working and only wake up in about 5 seconds
    delay(5000);
  } 
}


#include <EtherCard.h>
#include "settings.h"

// ethernet interface mac address, must be unique on the LAN
static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };
static byte udp_broadcast[] = {0xFF, 0xFF, 0xFF, 0xFF};

// Choosed by a fair dice roll, guaranteed to be random
static uint16_t udp_port = 31715;

byte Ethernet::buffer[700];
static uint32_t timer;

const char website[] PROGMEM = "rkdoorbell.appspot.com";
const char udp_msg[] = "Ding-dong!";

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

void send_udp_broadcast() {
  ether.sendUdp(udp_msg, strlen(udp_msg), udp_port, udp_broadcast, udp_port+1);
}

void loop() {
  // Process ethernet packet
  ether.packetLoop(ether.packetReceive());
  int sensorValue = analogRead(A3);

  // generally anything above 0 is good, but 500 just to be sure
  // as this should correspond to ~ 1.5V
  if (sensorValue > 500) {
    send_udp_broadcast();

    Serial.println("Ding-dong!!");
    Serial.println(sensorValue);

    Serial.println();
    Serial.print("<<< REQ ");
    ether.browseUrl(PSTR(URL), "", website, my_callback);

    // If there was a callout, we can sleep safely for bell 
    // to finish working and only wake up in about 5 seconds
    delay(5000);
  } 
}


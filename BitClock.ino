#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

#if !defined(EPD4IN2)
#define EPD4IN2
#endif

#include "epd.h"
#include <epdpaint.h>

#include "Config.hpp"
#include "Mempool.hpp"
#include "Banner.hpp"
#include "Bisq.hpp"
#include "Screen.hpp"
#include "Pannel.hpp"
#include "Carousel.hpp"

using namespace BitClock;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_SERVER, UTC_OFFSET, NTP_UPDATE_INTERVAL);
Epd epd;
Screen screen(ScreenLayout::TYPE1);

void connectWifi() {
  Serial.print("Connecting to ");
  Serial.println(SSID);

  WiFi.setAutoReconnect(true);
  WiFi.enableIpV6();
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }

  Serial.print("\nWiFi connected!\nIPv4 address: ");
  Serial.println(WiFi.localIP());
  Serial.print("IPv6 address: ");
  Serial.println(WiFi.localIPv6());
}

void setup()
{
  Serial.begin(9600);

  if (epd.Init() != 0)
  {
    Serial.print("e-Paper init failed");
    return;
  }
  epd.ClearFrame();

  connectWifi();
  screen.Init();

  //configure screen
  auto cx = new Carousel({new Banner(), new Mempool()});
  
  auto slot0 = screen.GetSlot(0);
  slot0->SetContent(cx);

  auto slot1 = screen.GetSlot(1);
  slot1->SetContent(new Mempool());

  auto slot2 = screen.GetSlot(2);
  slot2->SetContent(new Bisq(BisqDisplayMode::PriceAndCandle, BisqGraphInterval::Day));

  timeClient.begin();
}

void loop()
{
  Serial.println("[LOOP START]");
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Wifi connection lost!\rReconnecting...");
    WiFi.reconnect();
    return;
  }
  
  timeClient.update();
  screen.Update(epd, timeClient.getEpochTime());
  Serial.println("[LOOP END]");
  delay(REFRESH_RATE);
}

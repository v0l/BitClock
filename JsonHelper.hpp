#pragma once

#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>

namespace BitClock {
class JsonHelper
{

  public:
    static auto GetJsonDoc(WiFiClientSecure *client, const char *url) -> DynamicJsonDocument
    {
      constexpr auto JsonBufferSize = 8192;

      HTTPClient https;
      https.setUserAgent("BitClock/1.0 (https://github.com/v0l/BitClock)");
      if (https.begin(*client, url))
      {
        int httpCode = https.GET();
        if (httpCode == HTTP_CODE_OK)
        {
          DynamicJsonDocument doc(JsonBufferSize);
          deserializeJson(doc, https.getStream());

          return doc;
        } else {
          Serial.print("[GET=");
          Serial.print(httpCode);
          Serial.println("]");
        }
      }

      return DynamicJsonDocument(0);
    }
};
}

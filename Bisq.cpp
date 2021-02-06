#include "Bisq.hpp"
#include "JsonHelper.hpp"
#include "Pannel.hpp"

#include <fonts.h>
#include <WiFiClientSecure.h>

using namespace BitClock;

Bisq::Bisq(const BisqDisplayMode &mode, const BisqGraphInterval &interval) : mode(mode), interval(interval) {

}

auto Bisq::GetTicketPrice(const char* fiat) const -> float {
  constexpr auto PriceUrl = "https://bisq.markets/api/ticker?market=btc_%s";
  auto client = new WiFiClientSecure();
  if (client) {
    char url[255];
    sprintf(url, PriceUrl, fiat);
    Serial.println(url);

    auto doc = JsonHelper::GetJsonDoc(client, url);
    if (!doc.isNull()) {
      return doc["last"].as<float>();
    }
    client->stop();
    delete client;
  }
  return 0.0f;
}

auto Bisq::GetPriceHistory(const char* fiat, const unsigned long &time) const -> std::vector<PriceHistory> {
  constexpr auto PriceHistoryUrl = "https://bisq.markets/api/hloc?market=btc_%s&interval=%s&timestamp_from=%d";
  std::vector<PriceHistory> ret;

  constexpr auto Hour = 60 * 60;
  constexpr auto Day = Hour * 24;

  auto client = new WiFiClientSecure();
  if (client) {
    char url[255];
    auto tsFrom = time - (Day * 30);
    char *int_str = nullptr;
    switch (interval) {
      case BisqGraphInterval::Day: {
          int_str = "day";
          tsFrom -= tsFrom % Day;
          break;
        }
      case BisqGraphInterval::Hour: {
          int_str = "hour";
          tsFrom -= tsFrom % Hour;
          break;
        }
      default: {
          int_str = "day";
        }
    }
    sprintf(url, PriceHistoryUrl, fiat, int_str, tsFrom);
    auto doc = JsonHelper::GetJsonDoc(client, url);
    if (!doc.isNull()) {
      for (auto x : doc.as<JsonArray>()) {
        auto px = PriceHistory {
          x["open"].as<float>(),
          x["high"].as<float>(),
          x["low"].as<float>(),
          x["close"].as<float>(),
          x["avg"].as<float>(),
          x["period_start"].as<long>()
        };

        ret.push_back(px);
      }
    }
    client->stop();
    delete client;
  }

  return ret;
}

auto Bisq::Update(Pannel *p, const unsigned long &time) -> bool {
  switch (mode) {
    case BisqDisplayMode::PriceOnly: {
        auto price = GetTicketPrice("eur");

        if (price != lastPrice) {
          char msg[128];
          sprintf(msg, "EUR %.0f", price);

          p->Clear();
          p->DrawCenterString(0, 0, p->rect.w, p->rect.h, msg, &Font24, Color::BLACK);
          lastPrice = price;
          return true;
        } else {
          return false;
        }
      }
    case BisqDisplayMode::PriceAndGraph: {
        auto graph = GetPriceHistory("eur", time);

        if (graph.size() > 0) {
          /*float min, max;
            unsigned long start, end;

            GetGraphMinMax(graph, min, max, start, end);
            Serial.println(min);
            Serial.println(max);

            auto n = 0;
            auto yPix = p->rect.h / (max - min); // FIAT per PIX, Ie. 1EUR = 2 Pixel
            auto xPix = p->rect.w / graph.size() - 1;

            p->Clear();
            for (auto gn = graph.begin(); gn != graph.end() - 1; gn++) {
            auto next = gn + 1;
            auto y0 = (max - (*gn).avg);
            auto y1 = (max - (*next).avg);
            p->DrawLine(xPix * n, y0 * yPix, xPix * (n + 1), y1 * yPix, Color::BLACK);
            n++;
            }

            return true;*/
        }
        break;
      }
    case BisqDisplayMode::PriceAndCandle: {
        auto graph = GetPriceHistory("eur", time);

        if (graph.size() > 0) {

          auto now = (graph.end() - 1);
          if (now->avg != lastPrice) {

            constexpr auto Padding = 5;
            auto padTop = std::max(BisqLogoHeight, (int)Font16.Height) + Padding;
            auto graphH = p->rect.h - padTop - Padding;
            auto graphW = p->rect.w - (Padding * 2);

            auto price = (*(graph.end() - 1)).avg;
            char msg[128];
            sprintf(msg, "%.2f bits/EUR", 1e6 / price);

            p->Clear();
            p->DrawString(Padding, Padding, msg, &Font16, Color::BLACK);

            PriceUtil::DrawCandleStick(graph, p, Padding, padTop, graphW, graphH);

            p->DrawImage(BisqLogo, p->rect.w - BisqLogoWidth - Padding, Padding, BisqLogoWidth, BisqLogoHeight);
            lastPrice = now->avg; //use high/low
            return true;
          }
        }
        break;
      }
  }
  return false;
}

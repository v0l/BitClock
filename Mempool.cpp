#include "Mempool.hpp"
#include "Pannel.hpp"
#include "JsonHelper.hpp"

#include <fonts.h>
using namespace BitClock;

auto Mempool::GetFees() -> RecommendedFees {
  constexpr auto FeesUrl = "https://mempool.space/api/v1/fees/recommended";

  auto doc = JsonHelper::GetJsonDoc(FeesUrl);
  if (!doc.isNull()) {
    return {
      doc["fastestFee"].as<int>(),
      doc["halfHourFee"].as<int>(),
      doc["hourFee"].as<int>()
    };
  }
  return {};
}

auto Mempool::Update(Pannel *p, const unsigned long &time) -> bool {
  auto rates = Mempool::GetFees();

  if (rates.hour != lastFees.hour
  || rates.halfHour != lastFees.halfHour
  || rates.fastest != lastFees.fastest) {
    p->Clear();
    p->DrawRect(false, Color::BLACK, 0, 0, p->rect.w, p->rect.h);
    DrawRate(rates.hour, p, 0);
    DrawRate(rates.halfHour, p, 1);
    DrawRate(rates.fastest, p, 2);
    lastFees = rates;
    return true;
  } else {
    return false;
  }
}

auto Mempool::DrawRate(int rate, Pannel *p, int slot) const -> bool {
  auto Font = Font12;

  auto w = p->rect.w / 3.0f;
  auto h = p->rect.h - 10;
  auto h3 = h / 3.0f;
  auto x = slot * w;
  auto fontY = (p->rect.h - Font.Height) / 2;
  auto barY = (p->rect.h - h) / 2;

  p->DrawRect(true, Color::BLACK, x + 5, barY + (h3 * 2), h3 - 2, h3);
  p->DrawRect(slot > 0, Color::BLACK, x + 5 + h3, barY + h3, h3 - 2, h3 * 2);
  p->DrawRect(slot > 1, Color::BLACK, x + 5 + (h3 * 2), barY, h3 - 2, h3 * 3);

  char rateStr[25];
  sprintf(rateStr, "%d sat/vB", rate);
  auto rateW = Font.Width * strlen(rateStr);

  p->DrawString(x + (w - rateW) - 5, fontY, rateStr, &Font, Color::BLACK);
}

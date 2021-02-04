#include "Price.hpp"
#include "Pannel.hpp"

using namespace BitClock;

auto PriceUtil::DrawCandleStick(const std::vector<PriceHistory> &graph, Pannel *p, int x, int y, int w, int h) -> void {
  float min, max;
  unsigned long start, end;
  GetGraphMinMax(graph, min, max, start, end);

  constexpr auto CandleWidth = 2; //Half the width (either side of high/low line)
  constexpr auto MinCandleHeight = 1.0f;

  auto yPix = h / (max - min); // FIAT per PIX, Ie. 1EUR = 2 Pixel
  auto xPix = w / (float)(end - start); //Seconds per PIX

  for (auto gn = graph.begin(); gn != graph.end(); gn++) {
    auto yHigh = y + (max - gn->high) * yPix;
    auto yLow = y + (max - gn->low) * yPix;
    auto yOpen = y + (max - gn->open) * yPix;
    auto yClose = y + (max - gn->close) * yPix;
    auto xTime = (float)(gn->time - start);
    auto xPos = x + (xPix * xTime);
    p->DrawLine(xPos, yHigh, xPos, yLow, Color::BLACK);
    if (yOpen > yClose) {
      //price went up
      auto ch = std::max(MinCandleHeight, (yOpen - yClose));
      p->DrawRect(true, Color::BLACK, xPos - CandleWidth, yClose, (CandleWidth * 2) + 1, ch);
    } else {
      auto ch = std::max(MinCandleHeight, (yClose - yOpen));
      p->DrawRect(false, Color::BLACK, xPos - CandleWidth, yOpen, (CandleWidth * 2) + 1, ch);
    }
  }
}

auto PriceUtil::GetGraphMinMax(const std::vector<PriceHistory> &graph, float &low, float &high, unsigned long &time_low, unsigned long &time_high) -> void {
  auto first = graph.begin();
  low = (*first).avg;
  high = (*first).avg;
  time_low = (*first).time;
  time_high = (*first).time;

  for (const auto &gx : graph) {
    if (low > gx.low) {
      low = gx.low;
    }
    if (high < gx.high) {
      high = gx.high;
    }
    if (time_low > gx.time) {
      time_low = gx.time;
    }
    if (time_high < gx.time) {
      time_high = gx.time;
    }
  }
}

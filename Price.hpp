#pragma once

#include <vector>

namespace BitClock {

struct PriceHistory {
  float open;
  float high;
  float low;
  float close;
  float avg;
  unsigned long time; //period start in unix seconds
};

class Pannel;
class PriceUtil {
  public:
    static auto DrawCandleStick(const std::vector<PriceHistory> &graph, Pannel *p, int x, int y, int w, int h) -> void;
    static auto GetGraphMinMax(const std::vector<PriceHistory> &graph, float &low, float &high, unsigned long &time_low, unsigned long &time_high) -> void;
};
}

#pragma once

#include "PannelContent.hpp"

namespace BitClock {
struct RecommendedFees {
  int fastest;
  int halfHour;
  int hour;
};

class Mempool : public PannelContent {
  public:
    static auto GetFees() -> RecommendedFees;
    auto Update(Pannel *pannel, const unsigned long &) -> bool override;
  private:
    auto DrawRate(int rate, Pannel *p, int slot) const -> bool;
    RecommendedFees lastFees;
    bool hasUpdate;
};
}

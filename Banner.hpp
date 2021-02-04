#pragma once

#include "PannelContent.hpp"

namespace BitClock {
class Banner : public PannelContent {
  public:
    Banner();
    auto Update(Pannel *pannel, const unsigned long &) -> bool override;
  private:
    auto GetBannerText(const unsigned long &time) const -> char*;
    char* lastBanner;
};
}

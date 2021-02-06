#pragma once

#include "PannelContent.hpp"
#include <vector>

namespace BitClock {
class Pannel;
class Carousel : public PannelContent {
  public:
    Carousel(const std::vector<PannelContent*> &content);
    auto Update(Pannel *pannel, const unsigned long &time) -> bool override;
  private:
    std::vector<PannelContent*> content;
    std::vector<PannelContent*>::iterator pos;
};
}

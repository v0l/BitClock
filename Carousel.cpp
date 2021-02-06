#include "Carousel.hpp"
#include "Pannel.hpp"

using namespace BitClock;

Carousel::Carousel(const std::vector<PannelContent*> &c) : content(c), pos(content.begin()) {

}

auto Carousel::Update(Pannel *pannel, const unsigned long &time) -> bool {
  if (pos == content.end()) {
    pos = content.begin();
  }
  (*pos)->Update(pannel, time);
  pos++;
  //always updated because we changed content
  return true;
}

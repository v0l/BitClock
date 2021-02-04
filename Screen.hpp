#pragma once

#include <vector>

class Epd;

namespace BitClock {
enum ScreenLayout
{
  /*
     Type0 Layout:
     ----------------------------------------
     |                SLOT 0                |
     |--------------------------------------|
     |                                      |
     |                                      |
     |                                      |
     |                SLOT 1                |
     |                                      |
     |                                      |
     |                                      |
     ----------------------------------------
  */
  TYPE0 = 0,
  /*
     Type1 Layout:
     ----------------------------------------
     |                SLOT 0                |
     |--------------------------------------|
     |                SLOT 1                |
     |--------------------------------------|
     |                                      |
     |                                      |
     |                SLOT 2                |
     |                                      |
     |                                      |
     ----------------------------------------
  */
  TYPE1 = 1,
  /*
     Type2 Layout:
     ----------------------------------------
     |                SLOT 0                |
     |--------------------------------------|
     |                SLOT 1                |
     |--------------------------------------|
     |                                      |
     |                SLOT 2                |
     |                                      |
     |--------------------------------------|
     |       SLOT 3     |      SLOT 4       |
     ----------------------------------------
  */
  TYPE2 = 2,
  TYPE3 = 3
};

class Pannel;
class Screen
{
  public:
    Screen(const ScreenLayout & layout);

    auto Init() -> void;
    auto Update(Epd &epd, const unsigned long&) -> bool;
    auto GetLayout() const -> const ScreenLayout&;
    auto GetSlot(const int &slot) const -> Pannel*;
    auto GetSlots() const -> const std::vector<Pannel*>&;
  private:
    ScreenLayout layout;
    std::vector<Pannel*> pannels;
};
}

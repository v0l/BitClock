#include "Screen.hpp"
#include "Pannel.hpp"

#include "epd.h"

using namespace BitClock;

Screen::Screen(const ScreenLayout &layout) : layout(layout)
{ }

auto Screen::Init() -> void {
  //create the layout
  switch (layout)
  {
    case ScreenLayout::TYPE0:
      {
        constexpr auto Slot0Height = 40;

        auto p0 = new Pannel(0, Rect{0, 0, EPD_WIDTH, Slot0Height});
        auto p1 = new Pannel(1, Rect{0, Slot0Height, EPD_WIDTH, EPD_HEIGHT - Slot0Height});

        pannels.push_back(p0);
        pannels.push_back(p1);
        break;
      }
    case ScreenLayout::TYPE1:
      {
        constexpr auto Slot0Height = 40;

        auto p0 = new Pannel(0, Rect{0, 0, EPD_WIDTH, Slot0Height});
        auto p1 = new Pannel(1, Rect{0, Slot0Height, EPD_WIDTH, Slot0Height});
        auto p2 = new Pannel(2, Rect{0, (Slot0Height * 2), EPD_WIDTH, EPD_HEIGHT - (Slot0Height * 2)});

        pannels.push_back(p0);
        pannels.push_back(p1);
        pannels.push_back(p2);
        break;
      }
    case ScreenLayout::TYPE2:
      {
        constexpr auto Slot0Height = 40;

        auto fillHeight = EPD_HEIGHT - (Slot0Height * 3);
        auto p0 = new Pannel(0, Rect{0, 0, EPD_WIDTH, Slot0Height});
        auto p1 = new Pannel(1, Rect{0, Slot0Height, EPD_WIDTH, Slot0Height});
        auto p2 = new Pannel(2, Rect{0, (Slot0Height * 2), EPD_WIDTH, fillHeight});
        auto p3 = new Pannel(3, Rect{0, (Slot0Height * 2) + fillHeight, EPD_WIDTH / 2, Slot0Height});
        auto p4 = new Pannel(4, Rect{EPD_WIDTH / 2, (Slot0Height * 2) + fillHeight, EPD_WIDTH / 2, Slot0Height});

        pannels.push_back(p0);
        pannels.push_back(p1);
        pannels.push_back(p2);
        pannels.push_back(p3);
        pannels.push_back(p4);
        break;
      }
  }
}

auto Screen::Update(Epd &epd, const unsigned long &time) -> bool {
  auto anyUpdate = false;
  for (auto p : pannels) {
    if (p->Update(time)) {
      anyUpdate = true;
    }
  }

  if (anyUpdate) {
    for (auto p : pannels) {
      epd.SetPartialWindow(p->buffer, p->rect.x, p->rect.y, p->rect.w, p->rect.h);
    }
    epd.DisplayFrame();
  } else {
    Serial.println("No updates..");
  }
}

auto Screen::GetLayout() const -> const ScreenLayout&
{
  return layout;
}

auto Screen::GetSlot(const int &slot) const -> Pannel*
{
  return pannels[slot];
}

auto Screen::GetSlots() const -> const std::vector<Pannel*>& {
  return pannels;
}

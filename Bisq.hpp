#pragma once

#include "PannelContent.hpp"
#include "Price.hpp"
#include <vector>

namespace BitClock {
enum class BisqDisplayMode : uint8_t {
  PriceOnly = 0,
  PriceAndGraph = 1,
  PriceAndCandle = 2
};

enum class BisqGraphInterval : uint8_t {
  None = 0, //only needed for price only mod
  Day = 1,
  Hour = 2
};

class Bisq : public PannelContent {
  public:
    Bisq(const BisqDisplayMode &, const BisqGraphInterval &);
    auto Update(Pannel *pannel, const unsigned long &) -> bool override;

    const BisqDisplayMode mode;
    const BisqGraphInterval interval;
  private:
    auto GetTicketPrice(const char* fiat) const -> float;
    auto GetPriceHistory(const char* fiat, const unsigned long &) const -> std::vector<PriceHistory>;
    float lastPrice;

    static const auto BisqLogoWidth = 64;
    static const auto BisqLogoHeight = 22;
    static const auto BisqLogoSize = 176;
    const unsigned char BisqLogo[BisqLogoSize] = {
      0xFC, 0x1F, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x0F, 0xFE, 0x3F,
      0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0x07, 0xFE, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF,
      0xC0, 0x0E, 0xFE, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xC6, 0x04, 0xFE, 0x3D,
      0xFD, 0xFD, 0xFF, 0xDF, 0x8F, 0xA8, 0xFE, 0x20, 0xF8, 0xE0, 0xBA, 0x0B,
      0x0F, 0xF0, 0x7E, 0x00, 0x30, 0xC0, 0x30, 0x03, 0x8F, 0xF8, 0x3E, 0x08,
      0x38, 0x8A, 0xA0, 0x80, 0x0F, 0xFC, 0x3E, 0x1E, 0x10, 0xC7, 0xE1, 0xE1,
      0x0F, 0xFE, 0xBE, 0x3F, 0x08, 0x82, 0xE3, 0xF0, 0x19, 0xF3, 0xFE, 0x3F,
      0x00, 0xC0, 0x63, 0xF0, 0x08, 0xE3, 0xFE, 0x3F, 0x88, 0xE0, 0x23, 0xF8,
      0x0D, 0xFF, 0xFE, 0x1F, 0x00, 0xFC, 0x01, 0xF0, 0x8F, 0xFF, 0xBE, 0x3E,
      0x08, 0xEE, 0x20, 0xE0, 0x87, 0x1E, 0x3F, 0x04, 0x10, 0xC4, 0x30, 0x40,
      0x83, 0xB8, 0x3F, 0x80, 0x38, 0x80, 0x38, 0x00, 0xC0, 0xF0, 0x7F, 0xC0,
      0x70, 0xC0, 0x7C, 0x00, 0xE0, 0x00, 0xFF, 0xEA, 0xFA, 0xEA, 0xFE, 0xA8,
      0xF0, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xFE, 0x8B, 0xFF, 0xFF,
      0xFF, 0xFF, 0xFF, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0,
      0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8
    };
};
}
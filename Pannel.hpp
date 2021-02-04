#pragma once

#include <stdint.h>

struct sFONT;
namespace BitClock {

enum class Color : uint8_t {
  WHITE = 1, // ffmpeg monow pixel format (use this one)
  BLACK = 0, // ffmpeg monob pixel format
};

struct Rect
{
  int x, y, w, h;
};

class PannelContent;
class Pannel
{
  public:
    Pannel(const int &slot, const Rect &r);
    ~Pannel();
    const int slot;
    const Rect rect;

    auto Clear() -> bool;
    auto Update(const unsigned long&) -> bool;
    auto HasUpdate() const -> bool;
    auto SetContent(PannelContent*) -> void;
    auto DrawImage(const unsigned char *data, int x, int y, int w, int h) -> bool;
    auto DrawRect(bool filled, Color color, int x, int y, int w, int h) -> bool;
    auto DrawString(int x, int y, const char* text, sFONT* font, Color colored) -> bool;
    auto DrawCenterString(int x, int y, int w, int h, const char* text, sFONT* font, Color colored) -> bool;
    auto DrawLine(int x0, int y0, int x1, int y1, Color color) -> bool;
  private:
    friend class Screen;
    unsigned char *buffer;
    bool emptyDrawn;
    PannelContent *content;

    auto AllocateBuffer(const int &size) -> void;
    auto GetBufferSize() const -> int;
};
}

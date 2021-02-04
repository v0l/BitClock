#include "Pannel.hpp"
#include "PannelContent.hpp"

#include "epd.h"
#include "epdpaint.h"
#include <stdlib.h>
#include <fonts.h>

using namespace BitClock;

Pannel::Pannel(const int &slot, const Rect &r) : rect(r), slot(slot), buffer(nullptr), content(nullptr), emptyDrawn(false)
{
  auto bufSize = GetBufferSize();
  AllocateBuffer(bufSize);
}

Pannel::~Pannel()
{
  if (buffer != nullptr)
  {
    free(buffer);
  }
}

auto Pannel::AllocateBuffer(const int &size) -> void
{
  buffer = (unsigned char *)malloc(size);
  Clear();
}

auto Pannel::GetBufferSize() const -> int
{
  return ((rect.w * rect.h) * BPP) / 8;
}

auto Pannel::Clear() -> bool
{
  memset(buffer, 0xff, GetBufferSize());
}

auto Pannel::Update(const unsigned long &time) -> bool {
  bool ret = false;
  if (content != nullptr) {
    ret = content->Update(this, time);
  } else if (!emptyDrawn) {
    DrawRect(false, Color::BLACK, 0, 0, rect.w, rect.h);
    DrawCenterString(0, 0, rect.w, rect.h, "EMPTY SLOT", &Font24, Color::BLACK);
    emptyDrawn = true;
    ret = true;
  }
  return ret;
}

auto Pannel::SetContent(PannelContent* c) -> void {
  content = c;
}

auto Pannel::DrawImage(const unsigned char *data, int x, int y, int w, int h) -> bool {
  auto srcWidthBytes = (w * BPP) / 8;
  auto dstWidthBytes = (rect.w * BPP) / 8;
  auto dstXOffset = (x * BPP) / 8;
  auto dstYOffset = (y * dstWidthBytes);
  auto dstOffset = dstXOffset + dstYOffset;

  //copy lines
  for (auto y = 0; y < h; y++) {
    memcpy(buffer + dstOffset + (y * dstWidthBytes), data + (y * srcWidthBytes), srcWidthBytes);
  }
  return true;
}

auto Pannel::DrawRect(bool filled, Color color, int x, int y, int w, int h) -> bool {
  Paint p(buffer, rect.w, rect.h);
  if (filled) {
    p.DrawFilledRectangle(x, y, x + w - 1 , y + h - 1, (int)color);
  } else {
    p.DrawRectangle(x, y, x + w - 1, y + h - 1, (int)color);
  }
  return true;
}

auto Pannel::DrawCenterString(int x, int y, int w, int h, const char* text, sFONT* font, Color colored) -> bool {
  auto slen = strlen(text);
  return DrawString((w - (font->Width * slen)) / 2, (h - font->Height) / 2, text, font, colored);
}

auto Pannel::DrawString(int x, int y, const char* text, sFONT* font, Color colored) -> bool {
  Paint p(buffer, rect.w, rect.h);
  p.DrawStringAt(x, y, text, font, (int)colored);
}

auto Pannel::DrawLine(int x0, int y0, int x1, int y1, Color color) -> bool {
  Paint p(buffer, rect.w, rect.h);
  if (x0 == x1) {
    p.DrawVerticalLine(x0, y0, abs(y0 - y1), (int)color);
  } else if (y0 == y1) {
    p.DrawHorizontalLine(x0, y0, abs(x0 - x1), (int)color);
  } else {
    p.DrawLine(x0, y0, x1, y1, (int)color);
  }
}

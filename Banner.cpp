#include "Banner.hpp"
#include "Time.hpp"
#include "Pannel.hpp"

#include <fonts.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace BitClock;

Banner::Banner() : lastBanner(nullptr) {

}

auto Banner::Update(Pannel *p, const unsigned long &time) -> bool {
  auto bannerText = GetBannerText(time);

  if (lastBanner == nullptr || strcmp(bannerText, lastBanner) != 0) {
    p->Clear();
    p->DrawRect(false, Color::BLACK, 0, 0, p->rect.w, p->rect.h);
    p->DrawCenterString(0, 0, p->rect.w, p->rect.h, bannerText, &Font16, Color::BLACK);

    auto bannerLen = strlen(bannerText);
    if (lastBanner == nullptr) {
      lastBanner = (char*)malloc(bannerLen + 1);
    } else if (bannerLen != strlen(lastBanner)) {
      lastBanner = (char*)realloc(lastBanner, bannerLen + 1);
    }
    strcpy(lastBanner, bannerText);

    free(bannerText);
    return true;
  } else {
    free(bannerText);
    return false;
  }
}

auto Banner::GetBannerText(const unsigned long &time) const -> char* {
  char currentTime[6] = "??:??";
  auto now = Time(time);
  sprintf(currentTime, "%02d:%02d", now.getHours(), now.getMinutes());

  char *bannerText = (char*)malloc(128);
  sprintf(bannerText, "BitClock %s", currentTime);
  //sprintf(bannerText, "BitClock");
  return bannerText;
}

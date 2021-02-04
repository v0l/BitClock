#pragma once

namespace BitClock {
class Time {
  public:
    Time(const unsigned long &time) : time(time) {

    }

    //From NTPClient.cpp
    int getDay() const {
      return (((time / 86400L) + 4 ) % 7); //0 is Sunday
    }

    int getHours() const {
      return ((time  % 86400L) / 3600);
    }

    int getMinutes() const {
      return ((time % 3600) / 60);
    }

    int getSeconds() const {
      return (time % 60);
    }
  private:
    const unsigned long time;
};
}

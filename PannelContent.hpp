#pragma once

namespace BitClock {
class Pannel;
class PannelContent {
  public:
    /**
       Update the pannel with the latest content,
       time is the current unix time
       Return true if there was an update
    */
    virtual auto Update(Pannel *pannel, const unsigned long &time) -> bool = 0;
};
}

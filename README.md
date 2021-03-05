# BitClock

E-Paper Bitcoin trading/stats display.

## Setup

### Hardware
ESP32 ([WEMOS LOLIN D32](https://www.wemos.cc/en/latest/d32/d32.html) in my case)

Waveshare E-Paper display ([4.2 Module](https://www.waveshare.com/wiki/4.2inch_e-Paper_Module))

Wiring (Set in `epdif.h` from Waveshare libs):
```c
#define RST_PIN         0
#define DC_PIN          4
#define CS_PIN          5
#define BUSY_PIN        2
```

Wire DIN/CLK to your SPI port, for me this is MOSI(23) and SCK(18)

I powered the display from the 3.3v rail of the board.

### Dependencies
Add [ESP32](https://github.com/espressif/arduino-esp32) board to Boards Manager

Download [Waveshare](https://github.com/waveshare/e-Paper) libs and copy `Arduino/EPD4in2` to `Arduino/libraries`

Install `NTPClient` and `ArduinoJSON` in "Library Manager"

## Config

Copy `Config.hpp.example` to `Config.hpp` and enter WiFi details and any other changes you like.

Open `BlockClock.ino` with Arduino IDE and select your board. 

Upload!

## TODO

- Add webserver for configuration
- Abstract Arduino specific code
- Make Linux version (Raspberry PI etc)
- Make display emulator 
- Add more content from multiple sources
- 3D printed case design
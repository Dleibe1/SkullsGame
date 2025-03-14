# Skulls Game
## A touchscreen game I made for my brother
### [Here's a video demonstration on Youtube](https://www.youtube.com/watch?v=m-HvHr4f4hM)

## This repository only includes the files I edited.  I created this a few years ago before I started using github.  The rest of the code is in my google drive, but you should be able to re-create the project using PlatformIO's board manager and library manager.  If you're not familiar with PlatformIO I reccommend it over the Arduino IDE if you like to use Visual Studio Code.

### If you want to try this project, the following instructions assume you are familiar with the [PlatformIO extension](https://platformio.org/) in VSCode with an [ESP32doit-Devkit-v1](https://www.amazon.com/ESP-WROOM-32-Development-Dual-Mode-Microcontroller-Integrated/dp/B07WCG1PLV/ref=asc_df_B07WCG1PLV?mcid=7cc24e50dc423e8e9f1039421f865b8a&hvocijid=13685703578232806137-B07WCG1PLV-&hvexpln=73&tag=hyprod-20&linkCode=df0&hvadid=730434204848&hvpos=&hvnetw=g&hvrand=13685703578232806137&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9007909&hvtargid=pla-2281435177138&th=1).

### These instructions also assume you can infer all wiring for the Touchscreen by reading through the LovyanGFXSetup.hpp file.  All wiring for the LED's can be inferred by reading the main.cpp file.  Good luck if you've read this far!

## Instructions:

Add LovyanGFX version 1.1.9 to your project using PlatformIO's library manager.  The repo can be found here: [https://github.com/lovyan03/LovyanGFX](https://github.com/lovyan03/LovyanGFX)

I created the LovyanGFXSetup.hpp file for my particular set of hardware and placed it in .pio/libdeps/esp32doit-devkit-v1/LovyanGFX/src.  Your setup may be different depending on which touchscreen and Micro Controller you use.  I then imported this file into my [main.cpp file](main.cpp) instead of LovyanGFX.hpp.

Also place [zombiePictures.hpp](zombiePictures.hpp) into the project's source folder (the same folder where main.cpp is found).

I used [This ESP32](https://www.amazon.com/ELEGOO-ESP-WROOM-32-Development-Bluetooth-Microcontroller/dp/B0D8T53CQ5/ref=sr_1_1_sspa?crid=21VY76RGN1WYD&dib=eyJ2IjoiMSJ9.is-SH_RLGHiZZUrqvTWU_DFFr6XAPKtIzbKWDMtYTKN6SsUR0ayjeWGt2ZUok58rOtvPfsNmfWe0jW06Oh7RydTyPSmqWLVNOp-bj20WjigHCx-0LZgdE9_itkFXiEW7IXpo8y9aHRT3g_otU8PSP5rvz0iln6A_a7L3Yy2svhfSxoSBWyAZmHW5-58L_3s8T39xdeGUrQ0mdhAYVdE0Inp8bTP2RSDszPH9_7paKQc._1qeK84n5A17zHQmcdWn3vqebx3pWIq-Ti65FU3HJP8&dib_tag=se&keywords=esp32+dev&qid=1739303542&sprefix=esp32+dev%2Caps%2C88&sr=8-1-spons&sp_csd=d2lkZ2V0TmFtZT1zcF9hdGY&psc=1) and [this touchscreen display.](https://www.amazon.com/gp/product/B0BWJHK4M6/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&th=1)

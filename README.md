# SkullsGame
## A touchscreen game I made for my brother

### This repository only includes the files I edited

### This guide assumes you know to use [PlatformIO](https://platformio.org/) with an ESP32doit-Devkit-v1

## Instructions:

### These instructions are a bit vague and you should only try this if you have a lot of familiarity with ESP32's and PlatformIO.  It's really just for anyone watching 

Install LovyanGFX version 1.1.9 using PlatformIO's library manager.  The repo can be found here: [https://github.com/lovyan03/LovyanGFX](https://github.com/lovyan03/LovyanGFX)

I created the LovyanGFXSetup.hpp file for my particular set of hardware and placed it in .pio/libdeps/esp32doit-devkit-v1/LovyanGFX/src.  Yours may be different depending on which touchscreen and Micro Controller you use.  I then imported this file into my [main.cpp file](main.cpp). 

Also place [zombiePictures.hpp](zombiePictures.hpp) into your project's source folder (the same folder where main.cpp is found).

I used [This ESP32](https://www.amazon.com/ELEGOO-ESP-WROOM-32-Development-Bluetooth-Microcontroller/dp/B0D8T53CQ5/ref=sr_1_1_sspa?crid=21VY76RGN1WYD&dib=eyJ2IjoiMSJ9.is-SH_RLGHiZZUrqvTWU_DFFr6XAPKtIzbKWDMtYTKN6SsUR0ayjeWGt2ZUok58rOtvPfsNmfWe0jW06Oh7RydTyPSmqWLVNOp-bj20WjigHCx-0LZgdE9_itkFXiEW7IXpo8y9aHRT3g_otU8PSP5rvz0iln6A_a7L3Yy2svhfSxoSBWyAZmHW5-58L_3s8T39xdeGUrQ0mdhAYVdE0Inp8bTP2RSDszPH9_7paKQc._1qeK84n5A17zHQmcdWn3vqebx3pWIq-Ti65FU3HJP8&dib_tag=se&keywords=esp32+dev&qid=1739303542&sprefix=esp32+dev%2Caps%2C88&sr=8-1-spons&sp_csd=d2lkZ2V0TmFtZT1zcF9hdGY&psc=1) and [this touchscreen display.](https://www.amazon.com/gp/product/B0BWJHK4M6/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&th=1)


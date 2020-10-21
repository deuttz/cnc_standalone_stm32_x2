# CNC Standalone Based on STM32F103C8 MCUs

This a fork project of firmware made for CNC based on single STM32F103VBT6 MCU.
Inspired by https://habr.com/ru/post/250677/, source code in forum topic starter http://www.cnczone.ru/forums/index.php?showtopic=3334.

Idea is to use one F103C8 for gcode parsing and executing and use second for I/O interface.
The plan is to display info on the TFT 240x320 display with 8080 parallel interface and get input from the kind of DIY matrix keyboard from old calculator.

Development is to be done in STM32CubeMX and STM32CubeIDE.

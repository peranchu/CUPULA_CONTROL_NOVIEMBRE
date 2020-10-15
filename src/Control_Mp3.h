#ifndef CONTROL_MP3_H
#define CONTROL_MP3_H

#include <Arduino.h>

//Control inicial mp3
void ConfigIni_mp3();

//envio de trama
void sendCommand(byte command, byte Param1, byte Param2);

#endif
#ifndef CONTROL_MP3_H
#define CONTROL_MP3_H

#include <Arduino.h>

//Control inicial mp3
void ConfigIni_mp3();

//envio de trama
void sendCommand(byte command, byte Param1, byte Param2);

//Recepción de datos desde el modulo mp3
int recibeDatos();

//int limpieza Buffer serial
void limpieza_Buffer();

/////Envios estado del módulo mp3 a la pantalla

//numero de pistas
byte numero_pistas();

//envio pista en reproducción
byte pista_reproduccion();

#endif
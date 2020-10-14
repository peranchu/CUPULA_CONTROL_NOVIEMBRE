#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <Arduino.h>
#include <Nextion.h>
#include "Control_MP3.h"
#include <nRF24L01.h>
#include <RF24_config.h>
#include <RF24.h>
#include <SPI.h>

//Configuración RADIO
RF24 radio(8, 53); // PINS CE, CSN
const uint64_t pipe = 0xF0F0F0F0E1LL;

byte OFFLED[1] = {255}; //Mensaje de Apagado LEDS
byte msg[1] = {0};      //almacena el boton pulsado

uint32_t volumenRepro = 10;
uint32_t umbral = 0;

extern int CurrentPage = 0;

//////////////////////////////////////////////////////////////////////

//Configuración inicial Módulo de RADIO
void configRadio()
{
    SPI.begin();
    radio.begin();
    radio.setPALevel(RF24_PA_LOW);
    radio.setDataRate(RF24_2MBPS);
    radio.setChannel(124);
    radio.openWritingPipe(pipe);
}
//===================== FIN CONFIGURACIÓN MÓDULO RADIO ===============

////FUNCIONES DE LLAMADAS A LOS ELEMENTOS DE LA PANTALLA/////////////
//página 0
void page0PushCallback(void *ptr)
{
    //Serial.println("entrando 0");
    CurrentPage = 0;
}

//Página 1 Menu
void page1PushCallback(void *ptr)
{
    //Serial.println("entrando 1");
    CurrentPage = 1;
}

//Página 2 repro
void page2PushCallback(void *ptr)
{
    //Serial.println("Entrando 2");
    CurrentPage = 2;
}

////////////////// Volumen Reproductor  página 2 ///////////////////
void h0_2PopCallback(void *ptr)
{
    h0_2.getValue(&volumenRepro);

    if (volumenRepro == 0)
    {
        h0_2.getValue(&volumenRepro);
    }

    if (volumenRepro == 0)
    {
        h0_2.getValue(&volumenRepro);
    }

    if (volumenRepro == 0)
    {
        h0_2.getValue(&volumenRepro);
    }

    if (volumenRepro == 0)
    {
        h0_2.getValue(&volumenRepro);
    }

    if (volumenRepro == 0)
    {
        h0_2.getValue(&volumenRepro);
    }

    if (volumenRepro == 0)
    {
        h0_2.getValue(&volumenRepro);
    }

    if (volumenRepro == 0)
    {
        h0_2.getValue(&volumenRepro);
    }

    if (volumenRepro == 0)
    {
        h0_2.getValue(&volumenRepro);
    }
    sendCommand(0x06, 0, volumenRepro);
}

/////////////////// Botones Reproductor página 2 ///////////////////////
//Boton 1
void b1_2PopCallBack(void *ptr)
{
    //Serial.println("boton1");
    sendCommand(0x0F, 1, 1);
    msg[0] = 1;
    radio.write(msg, sizeof(msg)); //Activa la secuencia LED
}

//Botón 2
void b2_2PopCallBack(void *ptr)
{
    //Serial.println("boton2");
    sendCommand(0x0F, 1, 2);
    msg[0] = 2;
    radio.write(msg, sizeof(msg));
}

//Botón 3
void b3_2PopCallBack(void *ptr)
{
    //Serial.println("boton3");
    sendCommand(0x0F, 1, 3);
    msg[0] = 3;
    radio.write(msg, sizeof(msg));
}

//Botón 4
void b4_2PopCallBack(void *ptr)
{
    //Serial.println("boton4");
    sendCommand(0x0F, 1, 4);
    msg[0] = 4;
    radio.write(msg, sizeof(msg));
}

//Botón 5
void b5_2PopCallBack(void *ptr)
{
    //Serial.println("boton5");
    sendCommand(0x0F, 1, 5);
    msg[0] = 5;
    radio.write(msg, sizeof(msg));
}

//Botón 6
void b6_2PopCallBack(void *ptr)
{
    //Serial.println("boton6");
    sendCommand(0x0F, 1, 6);
    msg[0] = 6;
    radio.write(msg, sizeof(msg));
}

//Botón STOP
void b7_2PopCallBack(void *ptr)
{
    //Serial.println("STOP");
    sendCommand(0x16, 0, 0);
    radio.write(OFFLED, sizeof(OFFLED)); //Apaga los LED
}

///////// FIN PÁGINA 2 //////////////////////////

//Pagina 3 Micrófono
void page3PushCallback(void *ptr)
{
    //Serial.println("entrando 3");
    CurrentPage = 3;
}

/////////////////FIN PÁGINA 3 ////////////////////

//Página 4 Umbral
void page4PushCallback(void *ptr)
{
    //Serial.println("entrando 4");
    CurrentPage = 4;
}

//SLIDER UMBRAL
void h0_4PopCallback(void *ptr)
{
    h0_4.getValue(&umbral);

    if (umbral == 0)
    {
        h0_4.getValue(&umbral);
    }

    if (umbral == 0)
    {
        h0_4.getValue(&umbral);
    }

    if (umbral == 0)
    {
        h0_4.getValue(&umbral);
    }

    if (umbral == 0)
    {
        h0_4.getValue(&umbral);
    }

    if (umbral == 0)
    {
        h0_4.getValue(&umbral);
    }

    if (umbral == 0)
    {
        h0_4.getValue(&umbral);
    }
}
/////////////// FIN PÁGINA 4 ///////////////////////

#endif

#include <Arduino.h>
#include "Control_MP3.h"

byte dato;
int vaciadoBuffer;
byte Total_Pistas;
byte pista_actual;

//Trama fija para el envio serial al módulo mp3
#define startByte 0x7E
#define endByte 0xEF
#define versionByte 0xFF
#define dataLength 0x06
#define infoReq 0x01
#define isDebug false

//Funciones módulo mp3

//envio
void sendCommand(byte Command, byte Param1, byte Param2)
{

    //calculate checksum
    unsigned int checkSum = -(versionByte + dataLength + Command + infoReq + Param1 + Param2);

    //Construct the command line
    byte commandBuffer[10] = {startByte, versionByte, dataLength, Command, infoReq, Param1, Param2,
                              highByte(checkSum), lowByte(checkSum), endByte};

    for (int cnt = 0; cnt < 10; cnt++)
    {
        Serial3.write(commandBuffer[cnt]);
    }

    //Delay entre comandos
    delay(30);
}

//Configuracion Inicial módulo mp3
void ConfigIni_mp3()
{
    sendCommand(0x3F, 0x00, 0x00); //inicialización de parámetros(necesario para la recepción desde el mp3)
    delay(30);

    sendCommand(0x06, 0, 10); //Ajuste de Volumen
    delay(30);

    sendCommand(0x07, 0, 5); //Ecualizador 5 Base
    delay(30);

    //Ajuste de slider Volumen pantalla
    Serial2.print("EstadoVol.val=");
    Serial2.print(10);
    Serial2.write(0xff);
    Serial2.write(0xff);
    Serial2.write(0xff);

    Serial2.print("h0.val=");
    Serial2.print(10);
    Serial2.write(0xff);
    Serial2.write(0xff);
    Serial2.write(0xff);
}

//Recepcion de datos desde el módulo mp3
int recibeDatos()
{
    //Serial.println("entrando");
    if (Serial3.available() >= 10)
    {
        byte returned[10];
        for (byte k = 0; k < 10; k++)
            returned[k] = Serial3.read();
        dato = returned[6];
        return dato;
    }
}

//Limpieza de Buffer serial en el módulo mp3 (usado cada vez que se pide una respuesta al mp3)
void limpieza_Buffer()
{
    while (Serial3.available() > 0)
    {
        vaciadoBuffer = Serial3.read();
    }
}

//Envio estado del módulo a la pantalla

//Envio número de pistas del módulo mp3
byte numero_pistas()
{
    limpieza_Buffer();
    sendCommand(0x48, 0, 0);
    while (Serial3.available() < 10)
        delay(30);
    Total_Pistas = recibeDatos();
    return Total_Pistas;
}

//Envio pista actual en reproducción
byte pista_reproducion()
{
    limpieza_Buffer();
    sendCommand(0x4c, 0, 0);
    while (Serial3.available() < 10)
        delay(30);
    pista_actual = recibeDatos();
    return pista_actual;
}

//////////////////////////////////////////////////////
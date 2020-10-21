#include <Arduino.h>
#include "Control_MP3.h"

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

    sendCommand(0x06, 0, 10); //Ajuste de Volumen

    sendCommand(0x07, 0, 5); //Ecualizador 5 Base

    //Ajuste de slider Volumen pantalla
    Serial2.print("EstadoVol.val=");
    Serial2.print(10);
    Serial2.write(0xff);
    Serial2.write(0xff);
    Serial2.write(0xff);

    Serial2.print("h0vol.val=");
    Serial2.print(10);
    Serial2.write(0xff);
    Serial2.write(0xff);
    Serial2.write(0xff);
}

//////////////////////////////////////////////////////
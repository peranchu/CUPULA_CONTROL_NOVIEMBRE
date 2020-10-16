#include <Arduino.h>
#include <Nextion.h>
#include "declaraciones.h"
#include "funciones.h"
#include "Control_MP3.h"

#define PinBusy 20
#define PinMicro A0

#define TiempoEspera 5000

unsigned long tiempo = 0;

uint32_t lecturaMicro = 0;
int GaugeValue = 0;

bool playActual = true;
bool playanterior = true;

bool interrupcion = false;

void lecturaMicrofono();
void estadoRepro();

void setup()
{
  delay(500); //Espera inicio Pantalla

  nexInit(115200); //Puerto Comunicación Pantalla (Rx-amarillo 16, Tx-azul 17)

  Serial.begin(9600); //puerto depuración
  //Serial.println("hola");
  pinMode(PinBusy, INPUT);

  Serial3.begin(9600); //Puerto comunicación módulo mp3 Serial 3 (14, 15 TX, Rx)
  delay(300);

  ConfigIni_mp3(); //Configuracion inicial módulo mp3
  delay(300);

  configRadio(); //Configura la comunicación de Radio
  delay(300);

  // ===================== registros asociados a aventos ===============
  //Página 0
  page0.attachPush(page0PushCallback);

  //página 1 Menú
  page1.attachPush(page1PushCallback);

  //Página 2 reproductor
  page2.attachPush(page2PushCallback);

  //Volumen Reproductor
  h0_2.attachPop(h0_2PopCallback);

  //Botones Reproductor
  b1_2.attachPop(b1_2PopCallBack);
  b2_2.attachPop(b2_2PopCallBack);
  b3_2.attachPop(b3_2PopCallBack);
  b4_2.attachPop(b4_2PopCallBack);
  b5_2.attachPop(b5_2PopCallBack);
  b6_2.attachPop(b6_2PopCallBack);

  b7_2.attachPop(b7_2PopCallBack); //Boton STOP

  //página3 Micrófono
  page3.attachPush(page3PushCallback);

  //Página4 Umbral
  page4.attachPush(page4PushCallback);

  //Slider Umbral
  h0_4.attachPop(h0_4PopCallback);
}

void loop()
{
  nexLoop(nex_listen_list);

  estadoRepro();

  lecturaMicrofono();

  //Si se excede del umbral Produce interrupcion
  if (lecturaMicro > umbral && playActual == false && interrupcion == false)
  {
    sendCommand(0x16, 0, 0);             //Apaga el reproductor
    radio.write(OFFLED, sizeof(OFFLED)); //Apaga los LED
    interrupcion = true;

    //Espera 5 segundos despúes de la interrupción
    tiempo = millis();
    while (millis() < tiempo + TiempoEspera)
    {
      lecturaMicrofono();
    }
  }

  //Vuelve a poner en play y enciende los LED
  if (lecturaMicro < umbral && playActual == true && interrupcion == true)
  {
    //Serial.println("autoplay");
    int numPista;
    sendCommand(0x0F, 1, numPista = random(1, 6)); //Envía una pista aleatoria al reproductor
    msg[0] = numPista;
    radio.write(msg, sizeof(msg)); //Enciende LED
    interrupcion = false;
  }
}

//Estado Reproductor
void estadoRepro()
{
  playActual = digitalRead(PinBusy);
  if (playActual == false && playanterior == true)
  {
    //Reproduciendo
    Serial.println("Reproduciendo");
    playanterior = playActual;
  }
  if (playActual == true && playanterior == false)
  {
    //No reproduciendo
    Serial.println("PARADO");
    playanterior = playActual;
    radio.write(OFFLED, sizeof(OFFLED)); //Apaga los LED
  }
}

//Lectura Micrófono
void lecturaMicrofono()
{
  lecturaMicro = analogRead(PinMicro);

  //Dibuja en pantalla la entrada del micrófono
  if (CurrentPage == 3)
  {
    //envio a la caja de número
    Serial2.print("n0.val=");
    Serial2.print(lecturaMicro);
    Serial2.write(0xff);
    Serial2.write(0xff);
    Serial2.write(0xff);

    //Evio al reloj
    GaugeValue = map(lecturaMicro, 0, 300, 0, 200);
    Serial2.print("va0.val=");
    Serial2.print(GaugeValue);
    Serial2.write(0xff);
    Serial2.write(0xff);
    Serial2.write(0xff);
  }
}
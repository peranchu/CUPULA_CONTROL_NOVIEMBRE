#include <Arduino.h>
#include <Nextion.h>
#include "Control_MP3.h"
#include "declaraciones.h"
#include "funciones.h"

#define PinBusy 20
#define PinMicro A0

float lecturaMicro = 0;
const int sampleWindow = 50;
unsigned int sample;

unsigned int UmbralAmbiente;
float microfoPantalla;

int GaugeValue = 0;

bool playActual = true;
bool playanterior = true;

void lecturaMicrofono();
void estadoRepro();

void setup()
{
  delay(500); //Espera inicio Pantalla

  nexInit(115200); //Puerto Comunicación Pantalla (Rx-amarillo 16, Tx-azul 17)

  Serial.begin(9600); //puerto deputación
  Serial.println("hola");
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
  b7_2.attachPop(b7_2PopCallBack);

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

  lecturaMicrofono();

  estadoRepro();
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
  unsigned long startMillis = millis();
  float peakToPeak = 0;
  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;

  while (millis() - startMillis < sampleWindow)
  {
    sample = analogRead(A0);
    if (sample < 1024)
    {
      if (sample > signalMax)
      {
        signalMax = sample;
      }
      else if (sample < signalMin)
      {
        signalMin = sample;
      }
    }
  }
  peakToPeak = signalMax - signalMin;
  double volts = ((peakToPeak * 3.3) / 1024) * 0.707;
  double first = log10(volts / 0.00631) * 20;
  double second = first + 94 - 44 - 25;
  //Serial.println(second);

  if (CurrentPage == 4)
  {
    Serial2.print("n0.val=");
    Serial2.print(int(second));
    Serial2.write(0xff);
    Serial2.write(0xff);
    Serial2.write(0xff);

    //Evio al reloj
    GaugeValue = map(int(second), 22, 100, 0, 200);
    Serial2.print("va0.val=");
    Serial2.print(GaugeValue);
    Serial2.write(0xff);
    Serial2.write(0xff);
    Serial2.write(0xff);
  }
}
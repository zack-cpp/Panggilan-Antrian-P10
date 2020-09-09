#include <SPI.h>        
#include <DMD.h>        
#include <TimerOne.h>   
#include "SystemFont5x7.h"
#include "Arial_black_16.h"

#define DISPLAYS_ACROSS 1
#define DISPLAYS_DOWN 1

DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);

struct elements{
  int textWidth = 0;
  char text0[19] = "ANTRIAN NO.   ";
  char jadi[4];
  String antrian;
  static void scanDMD();
  void convert();
  void readAntrian();
}elm;

void setup(void)
{
  Serial.begin(9600);
  Timer1.initialize(5000);
  Timer1.attachInterrupt(elm.scanDMD);
  dmd.clearScreen(true);
  while(!Serial.available()){
    delay(200);
//    Serial.println("waiting...");
  }
  elm.readAntrian();
  elm.convert();
}

void loop()
{ 
  dmd.clearScreen(true);
  dmd.selectFont(System5x7);
  for (int i = 0; i < sizeof(elm.text0)+1; i++) {
    elm.textWidth += dmd.charWidth(elm.text0[i]) + 1;
  }
  for (int i = 0; i<elm.textWidth; i++) {
    dmd.drawString(32-i, 1, elm.text0, sizeof(elm.text0), GRAPHICS_NORMAL);
    dmd.drawString(13, 9, elm.jadi, sizeof(elm.jadi),GRAPHICS_NORMAL);
    while(Serial.available()){
      elm.readAntrian();
      elm.convert();
    }
    delay(100);
  }
  elm.textWidth = 0;
}

static void elements::scanDMD(){
  dmd.scanDisplayBySPI();
}

void elements::convert(){
  elm.antrian.toCharArray(elm.jadi,4);
}

void elements::readAntrian(){
  antrian = "";
  while(Serial.available()){
    char s = Serial.read();
    antrian += s;
  }
}

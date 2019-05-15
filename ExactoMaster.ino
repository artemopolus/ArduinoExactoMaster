#include <Arduino.h>
#include "FS.h"
#include "SD.h"
//#include "SPI.h"
#include <Wire.h>
#include <SPI.h>
#include "HardwareSerial.h"
#define SERIAL1_BAUD  19200
#define SERIAL1_RXPIN 16
#define SERIAL1_TXPIN 17
//HardwareSerial Serial1(1);

char IncomingByte = 0;
char OutputByte = 0;

bool writing = false;

bool SDcheck = false;

volatile uint32_t logCounter = 0;
volatile uint32_t logMaxCounter = 100;

const size_t SerialPrintf (const char *szFormat, ...) {
  /*
 * SerialPrintf
 * Реализует функциональность printf в Serial.print
 * Применяется для отладочной печати
 * Параметры как у printf
 * Возвращает 
 *    0 - ошибка формата
 *    отрицательное чило - нехватка памяти, модуль числа равен запрашиваемой памяти
 *    положительное число - количество символов, выведенное в Serial
 */
  va_list argptr;
  va_start(argptr, szFormat);
  char *szBuffer = 0;
  const size_t nBufferLength = vsnprintf(szBuffer, 0, szFormat, argptr) + 1;
  if (nBufferLength == 1) return 0;
  szBuffer = (char *) malloc(nBufferLength);
  if (! szBuffer) return - nBufferLength;
  vsnprintf(szBuffer, nBufferLength, szFormat, argptr);
  if (Serial){
    /* льем в серийник */
    Serial.print(szBuffer);
  }
  free(szBuffer);
  return nBufferLength - 1;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  SerialPrintf("Establish!\r\n");
  Serial1.begin(SERIAL1_BAUD, SERIAL_8N1, SERIAL1_RXPIN, SERIAL1_TXPIN);
  if (Serial1)
  {
    SerialPrintf("Serial init OK\r\n");
  }
  if(setupSD())
  {
    SDcheck = true;
    setupFile();
    writing = true;
    data2log("Log establish\n");
  }
  else data2log("SD error\n"); 
}

void loop() {
  // put your main code here, to run repeatedly:
  if(writing)
  {
  if(Serial1.available() > 0)
  {
    IncomingByte = Serial1.read();
    smbl2log(IncomingByte);
  }
  if(Serial.available() > 0)
  {
    OutputByte = Serial.read();
    correctCommand(OutputByte);
    send2uart();
  }
  }
}


/******************************************************************
** Código creado en Electrónica 5Hz                              **
** www.5hz-electronica.com                                       **
** Por:                                                          **
** Basado en el código de:                                       **
** Descripción del código:                                       **
**                                                               **
** Ejemplo para el sensor de línea QRE1113 digital               **
** indica si ha detectado algo o no                              **
*******************************************************************

Conexiones para la comunicacion i2c usando el breakout de 5Hz con un Arduino Uno / Duemilanove:
Arduino <-> Breakout board
Gnd      -  GND
5v       -  VCC
Analog 5 -  VO
*/



int QRE1113_Pin = A5; //conectado a digital 2
int umbral = 2500; //variar segun pruebas
void setup()
{
  Serial.begin(9600);
  Serial.println("*****************************************************");
  Serial.println("***********  Electronica 5Hz presenta:  *************");
  Serial.println("*** Programa de ejemplo para el sensor QRE 1113  ****");
  Serial.println("*****************************************************");
}

void loop()
{
  if(readQD() < umbral) Serial.println("detecte algo :D");
  else Serial.println("No veo nada :(");
  delay(250);
}


//regresa valor del QRE1113, numeros pequeños indican mas reflejo, mas de 3000 indican que nada fue reflejado
int readQD()
{
  pinMode( QRE1113_Pin, OUTPUT );
  digitalWrite( QRE1113_Pin, HIGH );
  delayMicroseconds(10);
  pinMode( QRE1113_Pin, INPUT );

  long time = micros();

  //toma el tiempo que dura la entrada en alto, sale del ciclo si nada pasa despues de 3000 ms
  while (digitalRead(QRE1113_Pin) == HIGH && micros() - time < 3000);
  int diff = micros() - time;

  return diff;
}

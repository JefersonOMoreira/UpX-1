#include <Wire.h>
#include "HX711.h" 
#include <LiquidCrystal_I2C.h>
#define DOUT 3
#define CLK  2
HX711 bal;             /* instancia Balança HX711 */
float fator_calibracao = 22760.00;     /* fator de calibração aferido na Calibração */

LiquidCrystal_I2C lcd(0x27, 2,1,0,4,5,6,7,3, POSITIVE); 

void setup()
{
  Serial.begin(9600); 
  bal.begin(DOUT, CLK);      /* inicializa a balança  */
  bal.set_scale(fator_calibracao);             /* ajusta fator de calibração  */
  bal.tare();                                    /* zera a Balança  */
  lcd.begin(16,2);   
  lcd.backlight(); 
}
 
void loop()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Massa da Carga: ");
  lcd.setCursor(0,1);
  lcd.print(bal.get_units(), 2);         /* imprime peso na balança com duas casas decimais */
  lcd.print("   kg ");                             /* imprime no monitor serial */
  delay(500);

  if (Serial.available())                            /* se a serial estiver disponivel */
  {
    char temp = Serial.read();                       /* le caracter da serial  */
    if (temp == 't' || temp == 'T')                  /* se pressionar t ou T   */
    {
      bal.tare();                                    /* zera a balança   */
      Serial.println(" Balança zerada");             /* imprime no monitor serial  */
    }
  }
}

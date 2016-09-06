#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
unsigned long analogSignal = A15; //подключение аналогового сигнального пина
const int digitalSignal = 22; //подключение цифрового сигнального пина
boolean noLight ; //переменная для хранения значения о присутствии света
unsigned long lightness = 0; //переменная для хранения количества света
void setup () {
  pinMode (digitalSignal,INPUT); //установка режима пина
  Serial.begin(9600); //инициализация Serial порта
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
}
void loop() {
  noLight=digitalRead(digitalSignal);//
  lightness=analogRead(analogSignal); // и о его количестве
  // set the cursor to column 0, line 1
  lcd.setCursor(0, 0);
  //вывод сообщения
  Serial.print("There is ");
  
  lcd.clear();
  
  
  if (noLight) {
    Serial.println("1");
    lcd.print("1");
  }
  else { 
    Serial.println("0");
    lcd.print("0");
  }
  Serial.print("value: ");
  Serial.println(lightness);
   
  lcd.setCursor(0, 1);
   //clearLCD();
  lcd.print(lightness);
  
  delay(1000); //задержка 1 сек    
}

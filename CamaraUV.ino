
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <EEPROM.h>


int luz = A0;
int buzzer = A1;
int chave = A2;
int led = A3;

byte bar1[8] = 
{
        B11100,
        B11110,
        B11110,
        B11110,
        B11110,
        B11110,
        B11110,
        B11100
};
byte bar2[8] =
{
        B00111,
        B01111,
        B01111,
        B01111,
        B01111,
        B01111,
        B01111,
        B00111
};
byte bar3[8] =
{
        B11111,
        B11111,
        B00000,
        B00000,
        B00000,
        B00000,
        B11111,
        B11111
};
byte bar4[8] =
{
        B11110,
        B11100,
        B00000,
        B00000,
        B00000,
        B00000,
        B11000,
        B11100
};
byte bar5[8] =
{
        B01111,
        B00111,
        B00000,
        B00000,
        B00000,
        B00000,
        B00011,
        B00111
};
byte bar6[8] =
{
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B11111,
        B11111
};
byte bar7[8] =
{
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00111,
        B01111
};
byte bar8[8] =
{
        B11111,
        B11111,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000
};

void printNumber(int value, int col) {
  if (value == 0) {
    custom0(col);
  } if (value == 1) {
    custom1(col);
  } if (value == 2) {
    custom2(col);
  } if (value == 3) {
    custom3(col);
  } if (value == 4) {
    custom4(col);
  } if (value == 5) {
    custom5(col);
  } if (value == 6) {
    custom6(col);
  } if (value == 7) {
    custom7(col);
  } if (value == 8) {
    custom8(col);
  } if (value == 9) {
    custom9(col);
  }      
}

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {12,11,10,9}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8,7,6,5}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
int tempo = 0;
int contagem = 0;
LiquidCrystal_I2C lcd(0x27,16,2);

void setup(){


  pinMode(chave, INPUT_PULLUP);
  pinMode(luz, OUTPUT);
  digitalWrite(luz, LOW);
  pinMode(buzzer, OUTPUT);
  pinMode(led,OUTPUT);
  digitalWrite (led,LOW);
 
  lcd.begin();              
  lcd.backlight();
 
  lcd.createChar(1,bar1);
  lcd.createChar(2,bar2);
  lcd.createChar(3,bar3);
  lcd.createChar(4,bar4);
  lcd.createChar(5,bar5);
  lcd.createChar(6,bar6);
  lcd.createChar(7,bar7);
  lcd.createChar(8,bar8);

  
  
  leEeprom(0);
  
  keypad.addEventListener(keypadEvent);
}

  
void custom0(int col)
{ // uses segments to build the number 0
  lcd.setCursor(col, 0); 
  lcd.write(2);  
  lcd.write(8); 
  lcd.write(1);
  lcd.setCursor(col, 1); 
  lcd.write(2);  
  lcd.write(6);  
  lcd.write(1);
}

void custom1(int col)
{
  lcd.setCursor(col,0);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
  lcd.setCursor(col,1);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
}

void custom2(int col)
{
  lcd.setCursor(col,0);
  lcd.write(5);
  lcd.write(3);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(2);
  lcd.write(6);
  lcd.write(6);
}

void custom3(int col)
{
  lcd.setCursor(col,0);
  lcd.write(5);
  lcd.write(3);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(7);
  lcd.write(6);
  lcd.write(1); 
}

void custom4(int col)
{
  lcd.setCursor(col,0);
  lcd.write(2);
  lcd.write(6);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
}

void custom5(int col)
{
  lcd.setCursor(col,0);
  lcd.write(2);
  lcd.write(3);
  lcd.write(4);
  lcd.setCursor(col, 1);
  lcd.write(7);
  lcd.write(6);
  lcd.write(1);
}

void custom6(int col)
{
  lcd.setCursor(col,0);
  lcd.write(2);
  lcd.write(3);
  lcd.write(4);
  lcd.setCursor(col, 1);
  lcd.write(2);
  lcd.write(6);
  lcd.write(1);
}

void custom7(int col)
{
  lcd.setCursor(col,0);
  lcd.write(2);
  lcd.write(8);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
}

void custom8(int col)
{
  lcd.setCursor(col, 0); 
  lcd.write(2);  
  lcd.write(3); 
  lcd.write(1);
  lcd.setCursor(col, 1); 
  lcd.write(2);  
  lcd.write(6);  
  lcd.write(1);
}

void custom9(int col)
{
  lcd.setCursor(col, 0); 
  lcd.write(2);  
  lcd.write(3); 
  lcd.write(1);
  lcd.setCursor(col, 1); 
  lcd.write(7);  
  lcd.write(6);  
  lcd.write(1);
}

void customPP(int col)
{
  lcd.setCursor(col, 0); 
  lcd.write(B10100001); //B10100001 ou B10100101
  lcd.setCursor(col, 1); 
  lcd.write(B11011111); //B11011111 ou B10100101
}

long previousMillis = 0;
long previousMillis2 = 0;
int controleP = 0;
int tp = 600;

void loop(){
  char key = keypad.getKey();
  printTEMPO(tempo);
  while(contagem==1) {
    printTEMPO(tempo);
    unsigned long currentMillis = millis();
    
    if(currentMillis - previousMillis > 1000) { 
      previousMillis = currentMillis;
      contagemRegressiva(tempo);   
    }
    if(currentMillis - previousMillis2 > tp) { 
      previousMillis2 = currentMillis;
      if(controleP==1) {
        controleP=0;
        tp=700;
      } else {
        controleP=1;
        tp=300;
      }
    }

    char key = keypad.getKey();
  }
}

void contagemRegressiva(int temp) {
  int m , c, d, u, number;
  number = tempo;
  if (number > 999) {
    m = (number - (number % 1000)) / 1000;
    number = number % 1000;
  } else {
    m = 0;
  }  
  
  if (number > 99) {
    c = (number - (number % 100)) / 100;
    number = number % 100;
  } else {
    c = 0;
  }  

  if (number > 9) {
    d = (number - (number % 10)) / 10;
    number = number % 10;
  } else {
    d = 0;
  }
  
  u = number;

  if(u>0) {
    u--;
  } else {
    if(d>0) {
      d--;
      u=9;
    } else {
      if(c>0) {
        c--;
        d=5;
        u=9;
      } else {
        if(m>0) {
          m--;
          c=9;
          d=5;
          u=9;
        } else {
          digitalWrite(luz, LOW);
          contagem=0;
          leEeprom(0);
        }
      }
    }
  }
  if(contagem!=0) {
  tempo = m*1000+c*100+d*10+u;
  }
}

void keypadEvent(KeypadEvent key){
  switch (keypad.getState()){
    
    case PRESSED:
      if (key == '0' || key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key == '8' || key == '9') { if(contagem != 1) {
        int tecla;
        switch(key) {
          case '0':
            tecla = 0;
          break;
          case '1':
            tecla = 1;
          break;
          case '2':
            tecla = 2;
          break;
          case '3':
            tecla = 3;
          break;
          case '4':
            tecla = 4;
          break;
          case '5':
            tecla = 5;
          break;
          case '6':
            tecla = 6;
          break;
          case '7':
            tecla = 7;
          break;
          case '8':
            tecla = 8;
          break;
          case '9':
            tecla = 9;
          break;
        }
        if(tempo > 999) {
          tempo = 0;
        }
        tempo = (tempo*10)+tecla;
      }}
    break;
    
    case RELEASED:
        if (key == '*') {
          tempo = 0;
        }
        if(key == '#' && contagem != 1) {
          gravaEeprom(tempo, 0);
          digitalWrite(luz, HIGH);
          contagem = 1;
          previousMillis = millis();
        }
        if (key == 'A' && contagem != 1) {
          leEeprom(100);
        }
        if (key == 'B' && contagem != 1) {
          leEeprom(200);
        }
        if (key == 'C' && contagem != 1) {
          leEeprom(300);
        }
        if (key == 'D' && contagem != 1) {
          leEeprom(400);
        }

    break;
    case HOLD:
        if (key == 'A' && contagem != 1) {
          gravaEeprom(tempo, 100);
          beep(3);
        }
        if (key == 'B' && contagem != 1) {
          gravaEeprom(tempo, 200);
          beep(3);
        }
        if (key == 'C' && contagem != 1) {
          gravaEeprom(tempo, 300);
          beep(3);
        }
        if (key == 'D' && contagem != 1) {
          gravaEeprom(tempo, 400);
          beep(3);
        }
    break;
  }
}

void printTEMPO(int x) {
  int m , c, d, u, number;
  number = x;
  if (number > 999) {
    m = (number - (number % 1000)) / 1000;
    number = number % 1000;
  } else {
    m = 0;
  }  
  
  if (number > 99) {
    c = (number - (number % 100)) / 100;
    number = number % 100;
  } else {
    c = 0;
  }  

  if (number > 9) {
    d = (number - (number % 10)) / 10;
    number = number % 10;
  } else {
    d = 0;
  }
  
  u = number;
  
  printNumber(m, 1);
  printNumber(c, 4);
  if(controleP == 0) {
    customPP(7);
  } else {
    lcd.setCursor(7,0);
    lcd.print(" ");
    lcd.setCursor(7,1);
    lcd.print(" ");
  }
  printNumber(d, 8);
  printNumber(u, 11);
    
}

void gravaEeprom(int temp, int address) {
  int m , c, d, u, number;
  number = temp;
  if (number > 999) {
    m = (number - (number % 1000)) / 1000;
    number = number % 1000;
  } else {
    m = 0;
  }  
  
  if (number > 99) {
    c = (number - (number % 100)) / 100;
    number = number % 100;
  } else {
    c = 0;
  }  

  if (number > 9) {
    d = (number - (number % 10)) / 10;
    number = number % 10;
  } else {
    d = 0;
  }
  
  u = number;
  
  EEPROM.write(address, m);
  address++;
  EEPROM.write(address, c);
  address++;
  EEPROM.write(address, d);
  address++;
  EEPROM.write(address, u);
  
}
void leEeprom(int addr) {
  int m, c, d, u;

  m = EEPROM.read(addr);
  addr++;
  c = EEPROM.read(addr);
  addr++;
  d = EEPROM.read(addr);
  addr++;
  u = EEPROM.read(addr);
  
  tempo = m*1000+c*100+d*10+u;
}

void beep(int qtd) {

  for(int x=0; x<qtd; x++) {
          digitalWrite (buzzer, HIGH);
          delay (30);
          digitalWrite (buzzer, LOW);
          delay (30);
  }
  
}

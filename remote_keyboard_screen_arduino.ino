#include <LiquidCrystal.h>
#include <IRremote.h>

const int rs=2, en=8, d4=4, d5=5, d6=6, d7=7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int input_pin = A3;
IRrecv irrecv(input_pin);
decode_results signals;


struct cursorPosition {
  int column = 0;
  int row = 0;
};
struct cursorPosition cursorPos;

bool upperCasing = false;
bool editing = false;
int listNumber = 0;

bool newChar = false;

const char* list1[4] = {"A", "M", "0", "?"};
const char* list2[4] = {"B", "N", "Y", "!"};
const char* list3[4] = {"C", "O", "Z", " "};
const char* list4[4] = {"D", "P", "1", "."};
const char* list5[4] = {"E", "Q", "2", ","};
const char* list6[4] = {"F", "R", "3", ";"};
const char* list7[4] = {"G", "S", "4", ":"};
const char* list8[4] = {"H", "T", "5", "'"};
const char* list9[4] = {"I", "U", "6", "+"};
const char* list10[4] = {"J", "V", "7", "-"};
const char* list11[4] = {"K", "W", "8", "*"};
const char* list12[4] = {"L", "X", "9", "/"};


const char* smallist1[4] = {"a", "m", "0", "?"};
const char* smallist2[4] = {"b", "n", "y", "!"};
const char* smallist3[4] = {"c", "o", "z", " "};
const char* smallist4[4] = {"d", "p", "1", "."};
const char* smallist5[4] = {"e", "q", "2", ","};
const char* smallist6[4] = {"f", "r", "3", ";"};
const char* smallist7[4] = {"g", "s", "4", ":"};
const char* smallist8[4] = {"h", "t", "5", "'"};
const char* smallist9[4] = {"i", "u", "6", "+"};
const char* smallist10[4] = {"j", "v", "7", "-"};
const char* smallist11[4] = {"k", "w", "8", "*"};
const char* smallist12[4] = {"l", "x", "9", "/"};

byte happysmiley[8] = {
  B00000,
  B10001,
  B00000,
  B00000,
  B10001,
  B01110,
  B00000,
};
byte sadsmiley[8] = {
  B00000,
  B10001,
  B00000,
  B00000,
  B01110,
  B10001,
  B00000,
};
byte heart[8] = {
  B00000,
  B01010,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000,
};
byte neutralsmiley[8] = {
  B00000,
  B10001,
  B00000,
  B00000,
  B00000,
  B11111,
  B00000,
};

//Move cursor functions for multiple uses
void moveLeft() {
  cursorPos.column--;

  if (cursorPos.column == -1) {
    cursorPos.column = 15;
    cursorPos.row--;
  }

  if (cursorPos.row == -1) {
    cursorPos.row = 1;
  }

  lcd.setCursor(cursorPos.column, cursorPos.row);
}

void moveRight() {
  lcd.setCursor(cursorPos.column + 1, cursorPos.row);
  newChar = true;
}





void setup() {
  lcd.clear();
  
  
  lcd.createChar(0, happysmiley);
  lcd.createChar(1, sadsmiley);
  lcd.createChar(2, neutralsmiley);
  lcd.createChar(3, heart);
  lcd.begin(16, 2);


  irrecv.enableIRIn();

  lcd.display();
}





void loop() {

  if (irrecv.decode(&signals)) {
    irrecv.resume();

    newChar = false;

    //Edit mode
    if (signals.value == 0xFFC23D) {
      if (editing) {
        editing = false;
        lcd.noBlink();
        lcd.noCursor();
        lcd.noDisplay();
      } else {
        editing = true;
        lcd.blink();
        lcd.cursor();
        lcd.display();
      }
    }
    if (!editing) return;


    //Print characters on the screen
    if (signals.value == 0xFF6897) {
      lcd.print(upperCasing ? list1[listNumber] : smallist1[listNumber]);
      newChar = true;
    }
    if (signals.value == 0xFF9867) {
      lcd.print(upperCasing ? list2[listNumber] : smallist2[listNumber]);
      newChar = true;
    }
    if (signals.value == 0xFFB04F) {
      lcd.print(upperCasing ? list3[listNumber] : smallist3[listNumber]);
      newChar = true;
    }
    if (signals.value == 0xFF30CF) {
      lcd.print(upperCasing ? list4[listNumber] : smallist4[listNumber]);
      newChar = true;
    }
    if (signals.value == 0xFF18E7) {
      lcd.print(upperCasing ? list5[listNumber] : smallist5[listNumber]);
      newChar = true;
    }
    if (signals.value == 0xFF7A85) {
      lcd.print(upperCasing ? list6[listNumber] : smallist6[listNumber]);
      newChar = true;
    }
    if (signals.value == 0xFF10EF) {
      lcd.print(upperCasing ? list7[listNumber] : smallist7[listNumber]);
      newChar = true;
    }
    if (signals.value == 0xFF38C7) {
      lcd.print(upperCasing ? list8[listNumber] : smallist8[listNumber]);
      newChar = true;
    }
    if (signals.value == 0xFF5AA5) {
      lcd.print(upperCasing ? list9[listNumber] : smallist9[listNumber]);
      newChar = true;
    }
    if (signals.value == 0xFF42BD) {
      lcd.print(upperCasing ? list10[listNumber] : smallist10[listNumber]);
      newChar = true;
    }
    if (signals.value == 0xFF4AB5) {
      lcd.print(upperCasing ? list11[listNumber] : smallist11[listNumber]);
      newChar = true;
    }
    if (signals.value == 0xFF52AD) {
      lcd.print(upperCasing ? list12[listNumber] : smallist12[listNumber]);
      newChar = true;
    }
    if (signals.value == 0xFFE21D) {
      lcd.write(byte(listNumber));
      newChar = true;
    }


    //Toggle uppercasing or clear or change char list 
    if (signals.value == 0xFF629D) {
      lcd.clear();
    }
    if (signals.value == 0xFF906F) {
      upperCasing = !upperCasing;
    }
    if (signals.value == 0xFFE01F) {
      listNumber = (listNumber - 1) % 4;
    }
    if (signals.value == 0xFFA857) {
      listNumber = (listNumber + 1) % 4;
    }


    //Backspace
    if (signals.value == 0xFFA25D) {
      moveLeft();
      lcd.print(" ");
      newChar = true;
    }


    
    //Move cursor manually
    //Right
    if (signals.value == 0xFF02FD) {
      moveRight();
    }

    //Left
    if (signals.value == 0xFF22DD) {  
      moveLeft();
    }


    //Check if cursor is at end of screen
    if (newChar) {
      cursorPos.column++;
      if (cursorPos.column == 16) {
        cursorPos.column = 0;
        cursorPos.row++;
        lcd.setCursor(cursorPos.column, cursorPos.row);
      }
      if (cursorPos.row == 2) {
        cursorPos.row = 0;
        lcd.setCursor(cursorPos.column, cursorPos.row);
      }
    }
  }
}






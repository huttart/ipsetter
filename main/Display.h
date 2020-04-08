#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0); 

class Display {
  private:    
    int font_mode;
    int draw_color;
    int str_length;
  public:
    Display();
    ~Display();
    commitMessage(int, int, const char*);
    emptyScreen();
    prepareEnv();
    pushMessage();
    setCurrentCursor(int, int, int, int);
    int getStrLength();
    drawBtnBorder (int, int, int, int);
    drawBtnBox (int, int, int, int);
};

Display::Display() {
//  Serial.println("Constructor()");
  this->font_mode  =  1;
  this->draw_color =  0;
  this->str_length =  0;
  u8g2.setFont(u8g2_font_6x10_tr);
}

Display::commitMessage(int x, int y, const char* str) {
  this->prepareEnv();
  u8g2.setDrawColor(2);
  this->str_length = this->str_length + ( strlen(str) * 6 );  
  u8g2.drawStr(x,y,str);    
}

Display::emptyScreen() {
  u8g2.clearBuffer();
  this->str_length = 0;
}

Display::prepareEnv() {
//  u8g2.setFontMode(this->font_mode);  
//  u8g2.setDrawColor(this->draw_color); 
}

Display::pushMessage() {
  u8g2.sendBuffer();  
}

Display::setCurrentCursor (int x, int y, int width, int height) {
  u8g2.setFontMode(1);          /* activate transparent font mode */
  u8g2.setDrawColor(1);         /* color 1 for the box */
  u8g2.drawBox(x, y, width, height);
}

Display::getStrLength() {
  return str_length;
}

Display::drawBtnBorder(int x, int y, int width, int height) {
  u8g2.setFontMode(1);         
  u8g2.setDrawColor(1);         
  u8g2.drawFrame(x, y, width, height);
}

Display::drawBtnBox(int x, int y, int width, int height) {
  u8g2.setFontMode(1);         
  u8g2.setDrawColor(1);         
  u8g2.drawBox(x, y, width, height);
}

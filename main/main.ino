/*
|--------------------------------------------------------------------------
| GMC IP SETTER
|--------------------------------------------------------------------------
|
| Copyright (c) 2019, Group Maker Co.,Ltd. 
|
*/


#include <Arduino.h>
#include <U8g2lib.h>
#include <stdlib.h>
#include "env.h"
#include "Ip.h"
#include "Display.h"
#include "Button.h"


String c;
Ip     ip;
Ip     tmp_ip;
String ok_btn         =  "OK";
String setip_btn      =  "SET-IP";
String cancel_btn     =  "CANCEL";
Display* my_display   =  new Display();
Button*  button       =  new Button(my_display, 8, 9, 12, 11, 10);

void setup(void) {
   u8g2.begin();
   ip.setip("");
   tmp_ip.setip(ip.ip);
   Serial.begin(9600);
   Serial.setTimeout(200);
   onBtnPress(0,0);
}

void loop(void) {
  c = Serial.readString();
  if (c.length() > 0) {
    ip.setip(c.substring(c.length() - 15));    
    if (APP_STATE == 0) {
      onBtnPress(0,APP_STATE);
      tmp_ip.setip(ip.ip);
    }
    c = "";
  }  


  button->readStates();
  int pressed_btn = button->getBtnPressed();
  if ( pressed_btn >= 0 ) {
    onBtnPress (pressed_btn, APP_STATE);
  }
  
}


int onBtnPress (int btn, int app_state) {  
  APP_STATE = STATE_DIAGRAM[app_state][btn];
  if (ip.ip.length() < 15 && APP_STATE  == 1) {
      return 0;
  } 
  my_display->emptyScreen();
  
  if (APP_STATE == 0) {
    my_display->commitMessage(textCenter(ip.ip), 10, ip.ip.c_str());
    my_display->drawBtnBorder(textCenter(setip_btn) - 4, 19, setip_btn.length() * 6 + 7, 13);
    my_display->commitMessage(textCenter(setip_btn), 29, setip_btn.c_str());
    my_display->pushMessage();
  }
  else if (APP_STATE == 1) {    
    my_display->commitMessage(textCenter(ip.ip), 10, ip.ip.c_str());
    my_display->drawBtnBox(textCenter(setip_btn) - 4, 19, setip_btn.length() * 6 + 7, 13);
    my_display->commitMessage(textCenter(setip_btn), 29, setip_btn.c_str());   
    my_display->pushMessage();
  }
  else if (APP_STATE == 2) {
    if (app_state == 1) {
        tmp_ip.setip(ip.ip);
    }

    if ( APP_STATE == app_state && ( btn == UP_BTN || btn == DOWN_BTN ) ) {
      if (btn == UP_BTN) {
        tmp_ip.plus(0);
      } else {
        tmp_ip.minus(0);
      } 
    }
       
    my_display->drawBtnBox(textCenter(tmp_ip.ip) - 1, 2, FONT_SIZE, 10);
    my_display->commitMessage(textCenter(tmp_ip.ip), 10, tmp_ip.ip.c_str());
    
    drawConfirmBtn();    
    my_display->pushMessage();
  }
  else if (APP_STATE >= 3 && APP_STATE <= 13) {        
    int addition = ( FONT_SIZE * (APP_STATE-2) );
    if (APP_STATE >= 5) {
      addition = addition + FONT_SIZE;
      if (APP_STATE >= 8) {
        addition = addition + FONT_SIZE;
      }
      if (APP_STATE >= 11) {
        addition = addition + FONT_SIZE;
      }
    }

    if ( APP_STATE == app_state && ( btn == UP_BTN || btn == DOWN_BTN ) ) {
      if (btn == UP_BTN) {
         tmp_ip.plus(addition/6);
      } else {
         tmp_ip.minus(addition/6);
      }
    }   
    my_display->drawBtnBox( (textCenter(tmp_ip.ip) + addition) - 1, 2, FONT_SIZE + 1, 10);
    my_display->commitMessage(textCenter(tmp_ip.ip), 10, tmp_ip.ip.c_str());

    drawConfirmBtn();
    
    my_display->pushMessage();
  }
  else if (APP_STATE == 14) {
    my_display->commitMessage(textCenter(tmp_ip.ip), 10, tmp_ip.ip.c_str());
    my_display->drawBtnBorder(60 + (64 - (ok_btn.length() * 6))/2, 19, ok_btn.length() * 6 + 7, 13);
    my_display->drawBtnBox((59 - (cancel_btn.length() * 6))/2, 19, cancel_btn.length() * 6 + 7, 13);
    my_display->commitMessage(64 + (64 - (ok_btn.length() * 6))/2, 29, ok_btn.c_str());     /* OK BTN RENDERING */
    my_display->commitMessage((64 - (cancel_btn.length() * 6))/2, 29, cancel_btn.c_str());  /* CANCEL BTN RENDERING */
    my_display->pushMessage();
  }
  else if (APP_STATE == 15) {
    my_display->commitMessage(textCenter(tmp_ip.ip), 10, tmp_ip.ip.c_str());
    my_display->drawBtnBox(60 + (64 - (ok_btn.length() * 6))/2, 19, ok_btn.length() * 6 + 7, 13);
    my_display->drawBtnBorder((59 - (cancel_btn.length() * 6))/2, 19, cancel_btn.length() * 6 + 7, 13);
    my_display->commitMessage(64 + (64 - (ok_btn.length() * 6))/2, 29, ok_btn.c_str());     /* OK BTN RENDERING */
    my_display->commitMessage((64 - (cancel_btn.length() * 6))/2, 29, cancel_btn.c_str());  /* CANCEL BTN RENDERING */
    my_display->pushMessage();
    
  }
  else if (APP_STATE == 16) {
    Serial.println(tmp_ip.ip);
    String loading = "[               ]";
    for (int i = 1 ; i <= 15 ; i++) {
      my_display->emptyScreen();
      loading[i] = '#';
      my_display->commitMessage((128 - (17 * 6))/2, 16, loading.c_str());
      my_display->pushMessage();
      delay(100);
    }
    delay(500);
    c = Serial.readString();
    if (c.length() > 0) {  
      ip.setip(c.substring(c.length() - 15));         
      c = "";
    }  
    String complete_message = "Failed !!!";
    if (ip.ip == tmp_ip.ip) {
      complete_message = "Completed";
    } 

    my_display->emptyScreen();
    my_display->commitMessage(textCenter(complete_message), 16, complete_message.c_str());
    my_display->pushMessage();
    delay(500);
    APP_STATE = 0;
    onBtnPress(0,0);    
    
  }

}

void drawConfirmBtn () {
   my_display->drawBtnBorder(60 + (64 - (ok_btn.length() * 6))/2, 19, ok_btn.length() * 6 + 7, 13);
   my_display->drawBtnBorder((59 - (cancel_btn.length() * 6))/2, 19, cancel_btn.length() * 6 + 7, 13);
   my_display->commitMessage(64 + (64 - (ok_btn.length() * 6))/2, 29, ok_btn.c_str());     /* OK BTN RENDERING */
   my_display->commitMessage((64 - (cancel_btn.length() * 6))/2, 29, cancel_btn.c_str());  /* CANCEL BTN RENDERING */
}

int textCenter (String str) {
  int l = (str.length() * 6);
  return (128 - l)/2;
}

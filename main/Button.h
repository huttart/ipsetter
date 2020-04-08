struct btn {
  int pin;
  int state = 0;
};

class Button {
  private:
    btn up;
    btn right;
    btn down;
    btn left;    
    btn center;
    
    Display* display_interface;
  public:
    Button(Display *, int, int, int, int, int);
    setupPinMode();
    getBtnStates();
    readStates();
    int getBtnPressed();    
};

Button::Button (Display * display_interface, int up_pin, int right_pin, int down_pin, int left_pin, int center_pin) {  
  this->up.pin            =   up_pin;
  this->right.pin         =   right_pin;
  this->down.pin          =   down_pin;
  this->left.pin          =   left_pin;
  this->center.pin        =   center_pin;
  this->display_interface =   display_interface;
  this->setupPinMode();
}

Button::setupPinMode () {
  pinMode(this->up.pin,     INPUT_PULLUP);
  pinMode(this->right.pin,  INPUT_PULLUP);
  pinMode(this->down.pin,   INPUT_PULLUP);
  pinMode(this->left.pin,   INPUT_PULLUP);
  pinMode(this->center.pin, INPUT_PULLUP);
}

Button::getBtnStates () {
//  Serial.print(APP_STATE);
//  Serial.print("btn up state = ");
//  Serial.println(this->up.state);
//
//  Serial.print("btn right state = ");
//  Serial.println(this->right.state);
//
//  Serial.print("btn down state = ");
//  Serial.println(this->down.state);
//
//  Serial.print("btn left state = ");
//  Serial.println(this->left.state);
//
//  Serial.print("btn center state = ");
//  Serial.println(this->center.state);
//
//
//  Serial.println("-------------------------------");
}

Button::readStates () {
  this->up.state      = !digitalRead(this->up.pin);
  this->right.state   = !digitalRead(this->right.pin);
  this->down.state    = !digitalRead(this->down.pin);
  this->left.state    = !digitalRead(this->left.pin);
  this->center.state  = !digitalRead(this->center.pin);
}

int Button::getBtnPressed () {
  if (this->up.state == HIGH) {
    return 0;
  } else if (this->right.state == HIGH) {
    return 1;
  } else if (this->down.state == HIGH) {
    return 2;
  } else if (this->left.state == HIGH) {
    return 3;
  } else if (this->center.state == HIGH) {
    return 4;
  } else {
    return -1;
  }
}

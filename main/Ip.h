class Ip {
  private:
  public:
    String ip;
    
    Ip();
    setip (String);
    int plus (int);
    int minus (int);
    
};

Ip::Ip () {
  this->ip = "";
}

Ip::setip (String ip) {
  this->ip = ip;
}

int Ip::plus (int index) {
  char tmp = this->ip[index];
  if (index == 0 || index == 4 || index == 8 || index == 12) {
    if (tmp == '2') {
      this->ip[index] = '0';
      return 1;
    }    
  } else {
    if (tmp == '9') {
      this->ip[index] = '0';
      return 1;
    } 
  }

  int tmp_ip_value  =   int(tmp) - 48;
  tmp_ip_value      =   tmp_ip_value + 1;
  tmp_ip_value      =   tmp_ip_value + 48;
  this->ip[index]   =   (char)tmp_ip_value;     
}


int Ip::minus (int index) {
  char tmp = this->ip[index];

  if (index == 0 || index == 4 || index == 8 || index == 12) {
    if (tmp == '0') {
      this->ip[index] = '2';
      return 1;
    }    
  } else {
    if (tmp == '0') {
      this->ip[index] = '9';
      return 1;
    } 
  }
  
  int tmp_ip_value  =   int(tmp) - 48;
  tmp_ip_value      =   tmp_ip_value - 1; 
  tmp_ip_value      =   tmp_ip_value + 48;
  this->ip[index]   =   (char)tmp_ip_value;   
}

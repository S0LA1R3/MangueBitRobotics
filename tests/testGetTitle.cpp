#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::endl;

string getTitle(uint16_t, uint16_t, uint16_t);

int main(){
    uint16_t r = 139;
    uint16_t g = 39;
    uint16_t b = 255;

    cout << getTitle(r, g, b) << endl;
    return 0;
}

string getTitle(uint16_t r, uint16_t g, uint16_t b){
  
  uint16_t soma = r + g + b;
  string t;

  if(soma < 240)
  {
    t = "p\0";  
  } else if (b < g && b < r){
    t = "a\0";
  } else{
    t = "b\0";
  } 

  return t;

};

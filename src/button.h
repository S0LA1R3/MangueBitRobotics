bool buttonP(int button){
  if(digitalRead(button) == HIGH){
    return true;
  }else{
    return false;
  }
}

bool buttonC(int button){
  if(digitalRead(button) == HIGH){
    return true;
  }else{
    return false;
  }
}

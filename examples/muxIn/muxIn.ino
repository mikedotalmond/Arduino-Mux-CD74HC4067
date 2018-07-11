#include <Mux.h>

//Mux mux(2,3,4,5,A0); // initialise on construct... 
Mux mux; // ...or construct now, and call setup later

int counter=0;

void setup(){

  Serial.begin(9600);
  mux.setup(8,9,10,11,A0); // initialise on setup
  
}


void loop(){
  
  int val = mux.read(counter);
  
  if(counter==15){
    Serial.println(val); 
  }else{
    Serial.print(val);
    Serial.print(", "); 
  }
  
  counter = ++counter & 15;
  
  delay(50);
}

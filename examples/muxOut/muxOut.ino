#include <Mux.h>

//Mux mux(2,3,4,5,A0); // initialise on construct... 
Mux mux; // ...or construct now, and call setup later

int counter=0;

void setup(){

  Serial.begin(9600);
  
  mux.setup(8,9,10,11,A0); // initialise Mux
  
}

void loop(){
  
  mux.write(counter, HIGH);
  delay(50);
  mux.write(counter, LOW);
  
  if(counter==15){
    Serial.println(counter); 
  }else{
    Serial.print(counter);
    Serial.print(", "); 
  }
  
  counter = ++counter & 15;
  
}
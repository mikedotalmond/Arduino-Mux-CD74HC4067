#include "Arduino.h"
#include "Mux.h"


/**
* Construct - no setup
**/
Mux::Mux() {
	//
}


/**
* Construct + setup
**/
Mux::Mux(int dPin0, int dPin1, int dPin2, int dPin3, int signalPin, int enablePin) {
	setup(dPin0,dPin0,dPin0,dPin0,signalPin,enablePin);
}


/**
* @public
*/
void Mux::setup(int dPin0, int dPin1, int dPin2, int dPin3, int signalPin, int enablePin){
	
	this->dPin0 			= dPin0;
	this->dPin1 			= dPin1;
	this->dPin2 			= dPin2;
	this->dPin3 			= dPin3;
	this->signalPin 		= signalPin;
	this->enablePin			= enablePin;
	currentChannel 			= -1;
	lastIO					= -1;
	
	// using the EN pin?
	if(enablePin>-1) {
		pinMode(enablePin, OUTPUT);	
		digitalWrite(enablePin, LOW); // start enabled
	}
	
	int pins[4] = {dPin0,dPin1,dPin2,dPin3};
	int i 		= 0;
	
	for(i=0;i<4;i++){
		// set pinMode for the digital control pins 
		pinMode(pins[i], OUTPUT);
		// set all control pins LOW 
		digitalWrite(pins[i], LOW);
	}
}


/**
* @public
*/
void Mux::setEnabled(bool enabled){
	if(enablePin!=-1){
		digitalWrite(enablePin, enabled ? LOW : HIGH);
	}
}

	
/**
* @public
*
**/	
int Mux::read(int channel){
	if(lastIO != MUX_IO_READ) {
		pinMode(signalPin, INPUT);
		lastIO = MUX_IO_READ;
	}
	setChannel(channel);
	return analogRead(signalPin);
}


/**
* @public
*
**/
int Mux::dRead(int channel){
	return read(channel) < 512 ? LOW : HIGH;
}


/**
* @public
* 
**/
void Mux::write(int channel, int value){
	if(lastIO != MUX_IO_WRITE) {
		pinMode(signalPin, OUTPUT);
		lastIO = MUX_IO_WRITE;
	}
	setChannel(channel);
	digitalWrite(signalPin, value);
}


/**
* @private 
* set the current mux channel [0-15] using 4 digtal pins to write the 4 bit integer
*/
void Mux::setChannel(int channel){
	if(currentChannel != channel) {
		digitalWrite(dPin0, bitRead(channel,0));
		digitalWrite(dPin1, bitRead(channel,1));
		digitalWrite(dPin2, bitRead(channel,2));
		digitalWrite(dPin3, bitRead(channel,3));
		currentChannel = channel;
	}
}
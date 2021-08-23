#include <ArduinoJson.h>
int x=0;
volatile unsigned long cont = 0; //número volátil
int botao;
int Lx=0;
int Ly=60;
int TempAnt;
int TermistorPin = A3;
int v;
float R1 = 10000;
float logR2, R2, T, Tc, Tf, temp;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
float ValLumin;
float Alpha;
float Resist;
float Lumin;
float ResLumin;
 
void setup() {
  Serial.begin(9600);
  pinMode(2,INPUT_PULLUP);
  pinMode(TermistorPin, INPUT);
  pinMode(A2, INPUT);
 //-----------  Configuração da Interrução ------------------- //                                 

  attachInterrupt(digitalPinToInterrupt(2),interrupcaoPino2,RISING);  //  Configura o pino2 como interrupção externa do tipo Rising (borda de LOW para HIGH)
}
void loop() {
	StaticJsonDocument<100> json;
	v = analogRead(A3);
	R2 = R1 * (1023.0 / (float)v - 1.0);
	logR2 = log(R2);
	T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
	Tc = T - 273.15;
	ValLumin =  analogRead(A2);
	Alpha = 1 / 0.858;
	ResLumin = 10000 / ((1023 / ValLumin) - 1); 
	Resist = 127410/ResLumin;
	Lumin = pow(Resist, Alpha);
	
	if (millis() - previousMillis >= intervalo){
	previousMillis = millis();
	cont = 0;
	}
	
	
	json["Luminosidade"] = Lumin;
	json["Temperatura"] = Tc;
	serializeJson(json, Serial);
	Serial.println();
	delay(7000);
}
void interrupcaoPino2(){
	cont = cont + 1;
}
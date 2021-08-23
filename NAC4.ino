#include <Adafruit_SSD1306.h>
#define OLED_Address 0x3C 
Adafruit_SSD1306 oled(128,64); 
#include <ArduinoJson.h>
int x=0;
int cont = 0;
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
  pinMode(2,INPUT);
  pinMode(TermistorPin, INPUT);
  pinMode(A2, INPUT);
  oled.begin(SSD1306_SWITCHCAPVCC, OLED_Address);
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
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

	botao = digitalRead(2);
  	if(botao == LOW){
		cont = cont + 1;
		json["Luminosidade"] = Lumin;
		json["Temperatura"] = Tc;
		serializeJson(json, Serial);
		Serial.println();
		delay(500);
		if(cont == 2){
			cont = 0;}
	 }
	if(cont == 0){
		oled.clearDisplay();
  		oled.setCursor(0,25);
  		oled.setTextColor(WHITE);
  		oled.print("Temperatura:");
 		oled.print(Tc);
  		oled.display();
	}
	if(cont == 1){
		oled.clearDisplay();
		oled.setCursor(0,25);
		oled.setTextColor(WHITE);
		oled.print("Luz:");
		oled.print(Lumin);
		oled.display();
	}
}
#include <Adafruit_SSD1306.h> // biblioteca do display oled
#define OLED_Address 0x3C 
Adafruit_SSD1306 oled(128,64); 

#include <ArduinoJson.h>

int x=0;
int lastx=0;
int lasty=60;

int estadobotao;
int contador = 0;
int templast;
int TermistorPin = A3;
int Vo;
float R1 = 10000;
float logR2, R2, T, Tc, Tf, temp;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07; //valores constante para calculo

float valor_ldr;
float alpha;
float resistencia;
float ldr;
float rldr;
 
void setup() {
  Serial.begin(9600);

  //variaveis
  pinMode(2,INPUT);
  pinMode(TermistorPin, INPUT);
  pinMode(A2, INPUT);

  oled.begin(SSD1306_SWITCHCAPVCC, OLED_Address);
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
}

void loop() {

	StaticJsonDocument<100> json; //cria o objeto Json

	// Lendo a temperatura
	Vo = analogRead(A3);
  	R2 = R1 * (1023.0 / (float)Vo - 1.0); //calculo R2, demonstração no arquivo pdf da aula
  	logR2 = log(R2);
  	T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));// Equação de Steinhart–Hart 
  	Tc = T - 273.15; //temp em Graus celcius

	// Leitura do sensor LDR
	 valor_ldr =  analogRead(A2);
	 alpha = 1 / 0.858;
	 rldr = 10000 / ((1023 / valor_ldr) - 1); 
	 resistencia = 127410/rldr;
	 ldr = pow(resistencia, alpha);
	
	
	// Configurando o botao
	estadobotao = digitalRead(2);
  	if(estadobotao == LOW){
		contador = contador + 1;
		// mostrando valores no serial
  		//Serial.print("Intensidade luminosa: "); 
  		//Serial.println(ldr);
  		//Serial.print("Temperatura corporal: "); 
  		//Serial.println(Tc);

		//formato de leitura no node-red
		json["luminosidade"] = ldr;
		json["temperatura"] = Tc;
		serializeJson(json, Serial);
		Serial.println();
		
		delay(500);
		if(contador == 2){
			contador = 0;}
	 }
	
	// Exibir temperatura no display OLED
	if(contador == 0){
		oled.clearDisplay();
  		oled.setCursor(0,25);
  		oled.setTextColor(WHITE);
  		oled.print("Temperatura Corporal:");
 		oled.print(Tc);
  		oled.display();
	}
	
	// Exibir Lux no display OLED
	if(contador == 1){
		oled.clearDisplay();
		oled.setCursor(0,25);
		oled.setTextColor(WHITE);
		oled.print("Intensidade luminosa:");
		oled.print(ldr);
		oled.display();
	}
	
}
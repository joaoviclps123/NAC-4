#include <ArduinoJson.h> // Biblioteca

// Variáveis necessárias para o leitor de Temperatura
int Vo;
float R1 = 10000;
float logR2, R2, T, Tc, Tf, temp;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07; //Valores para o calculo

// Variáveis para leitor de luminosidade
float valor_ldr;
float alpha;
float resistencia;
float ldr;
float rldr;

// Variáveis necessárias para o leitor da velocidade do vento
float valor_anemometro;
volatile unsigned long cont = 0;
unsigned long tempo = 0;
bool alerta = false;
int timer = 0;
 
void setup() {
  Serial.begin(9600);

  pinMode(2,INPUT);
  attachInterrupt(digitalPinToInterrupt(2), interrupcao, RISING);
  pinMode(A3, INPUT); // Termistor
  pinMode(A2, INPUT); // LDR

}

void loop() {

	StaticJsonDocument<100> json; //Cria um objeto Json
		
	bool alerta = false; // Alerta falso

	// Lendo a temperatura
	Vo = analogRead(A3);
  	R2 = R1 * (1023.0 / (float)Vo - 1.0); //Cálculo R2
  	logR2 = log(R2);
  	T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2)); // Cálculo
  	Tc = T - 273.15; //Temperatura em Cº

	// Sensor LDR
	 valor_ldr =  analogRead(A2);
	 alpha = 1 / 0.858;
	 rldr = 10000 / ((1023 / valor_ldr) - 1); 
	 resistencia = 127410/rldr;
	 ldr = pow(resistencia, alpha);
	
	// Leitura do Anemômetro
	if( (millis() - tempo) > 999){
    	tempo = millis();
	valor_anemometro = (cont/5) * 6.154;
    	cont = 0;
  	}

	// 1 alerta a cada 3 minutos caso esteja acima de 80km/h
	if(valor_anemometro >= 80 && timer == 0){ 
	alerta = true;
	timer = 180;
	} else if(timer != 0){
	timer -= 5;
	}
	
	// NODE-RED
	json["luminosidade"] = ldr;
	json["temperatura"] = Tc;
	json["vento"] = valor_anemometro;
	json["alerta"] = alerta;
	serializeJson(json, Serial);
	Serial.println();
	
	delay(5000);
	
}

void interrupcao(){ 
  cont++;
}

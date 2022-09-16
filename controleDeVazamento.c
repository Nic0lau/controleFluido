#include <Wire.h> /* Incluindo a biblioteca do I2C */
#include <NewPing.h> /* Incluindo a biblioteca do sensor ultrassonico */
#include <LiquidCrystal_I2C.h> /* Incluindo a biblioteca do display LCD */
/* Definindo os pinos do sensor ultrassonico */
#define TRIGGER_PINO 7
#define ECHO_PINO 6
#define ALTURA_TOTAL 10 /* Altura total do tanque em centimetros [MAXIMO: 400 cm] */
#define AREA_DA_BASE 123 /* Area da base do tanque em centimetros quadrados */
#define INTERVALO 10000 /* Tempo esperado entre as medicoes em milisegundos [ATUAL: 5 minutos] */
#define ENDERECO_LCD 0x3F/* Endereco hexadecimal do display LCD */
#define LINHAS_LCD 2 /* Numero de linhas que o display LCD tem */
#define COLUNAS_LCD 16 /* Numero de colunas que o display LCD tem */

NewPing sensorUltrassonico(TRIGGER_PINO, ECHO_PINO, ALTURA_TOTAL); /* Configurando o sensor */
LiquidCrystal_I2C lcd(ENDERECO_LCD, COLUNAS_LCD, LINHAS_LCD); /* Configurando o display LCD */

unsigned long distanciaMedia; /* Tempo medio de ping do sensor na altura do fluido em microsegundos */
unsigned int distanciaConvertidaCm; /* Distancia do sensor para o fluido em centimetros */
unsigned int fluidoAltura; /* Altura do fluido em centimetros */
unsigned int fluidoQuantidade; /* Volume atual de fluido no tanque em centimetros cubicos */
float fluidoLitros; /* Volume atual de fluido no tanque em litros */

void iniciarLcd(){
	lcd.init();
	lcd.backlight();
        lcd.setCursor(0,0);
        lcd.print("Controle de vaza");
        lcd.setCursor(0,1);
        lcd.print("mento");
        delay(3000);
        lcd.clear();
        lcd.print("Feito por:");
        lcd.setCursor(0,1);
        lcd.print("Nicolas Dias");
        delay(3000);
}

void setup() {
        iniciarLcd();
}

void loop() {
        distanciaMedia = sensorUltrassonico.ping_median(100, ALTURA_TOTAL);
        distanciaConvertidaCm = sensorUltrassonico.convert_cm(distanciaMedia); /* converte microsegundos para cm */
        fluidoAltura = ALTURA_TOTAL - distanciaConvertidaCm; /* Calculando altura do fluido */
        fluidoQuantidade = AREA_DA_BASE*fluidoAltura; /* Calculando o volume atual em cm3 */
        /* Descomente a linha abaixo se quiser converter para litros */
        /*  fluidoLitros = fluidoQuantidade/1000; */ /* Convertendo cm3 para L */
        fluidoLitros = fluidoQuantidade; /* Convertendo cm3 para mL */
        lcd.print("Volume cm3:");
        lcd.print(fluidoQuantidade);
        lcd.setCursor(0,1);
        lcd.print("Volume mL:");
        lcd.print(fluidoLitros);
        delay(INTERVALO);
        lcd.clear();
}

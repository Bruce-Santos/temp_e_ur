#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // Criando um LCD de 20x4 no endereço 0x27


byte simboloGraus[8] = {
	0b00010,
	0b00101,
	0b00010,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000
};


#define DHTPIN A2
#define DHTTYPE DHT11
#define tv 50 //total de valores
DHT dht(DHTPIN,DHTTYPE);
float u,t; //declaração de umidade(id: 0) e temperatura(id: 1)
float sv[2][tv]; //declaração da temperatura e umidade salvas para media
float mu,mt; //declaração de valores de media

float mediamovel(float alvo, int idalvo);


void setup() {
  u = dht.readHumidity();
  t = dht.readTemperature();
  dht.begin();
  lcd.init();                 // Inicializando o LCD
  lcd.backlight();            // Ligando o BackLight do LCD
  Serial.begin(9600);
  lcd.createChar(0, simboloGraus);
}

void loop() {
    u = dht.readHumidity() +8;
    t = dht.readTemperature();
    mu = mediamovel(u,0);
    mt = mediamovel(t,1);
    Serial.println(mu);
    Serial.println(mt);
    lcd.setCursor(0,0);
    lcd.print("Umidade: ");
    lcd.setCursor(9,0);
    lcd.print(mu,1);
    lcd.print(" %");
    lcd.setCursor(0,1);
    lcd.print("Temperatura: ");
    lcd.setCursor(13,1);
    lcd.print(mt,1);
    //lcd.print(" ");
    lcd.write(byte(0));
    lcd.print("C");
}

float mediamovel(float alvo, int idalvo){

  float soma = 0, media;
  for(int i = tv-1;i>0;i--){
      sv[idalvo][i] = sv[idalvo][i-1];
    }
    sv[idalvo][0] = alvo;
    for(int i = 0;i<tv;i++){
      
      soma += sv[idalvo][i];
      
    }
   
    media = soma/tv;
    return media;


}

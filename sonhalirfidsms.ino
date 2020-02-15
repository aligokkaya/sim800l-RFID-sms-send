#include <SPI.h>                          //SPI kütüphanemizi tanımlıyoruz.
#include <MFRC522.h>                      //MFRC522 kütüphanemizi tanımlıyoruz.
#include <Servo.h>                        //Servo kütüphanemizi tanımlıyoruz.
#include <Sim800l.h>
#include <SoftwareSerial.h>               //is necesary for the library!! 
Sim800l Sim800l;
int RST_PIN = 9;                          //RC522 modülü reset pinini tanımlıyoruz.
int SS_PIN = 10;                          //RC522 modülü chip select pinini tanımlıyoruz.
int servoPin = 8;                         //Servo motor pinini tanımlıyoruz.
char* text;
char* number;
bool error;
Servo motor;                              //Servo motor için değişken oluşturuyoruz.
MFRC522 rfid(SS_PIN, RST_PIN);            //RC522 modülü ayarlarını yapıyoruz.
byte ID[4] = {41, 235, 170, 43};          //Yetkili kart ID'sini tanımlıyoruz. 
byte iID[4]={107, 131, 76, 99};
void setup() { 
  motor.attach(servoPin);                 //Servo motor pinini motor değişkeni ile ilişkilendiriyoruz.
  Serial.begin(9600);                     //Seri haberleşmeyi başlatıyoruz.
  SPI.begin();                            //SPI iletişimini başlatıyoruz.
  rfid.PCD_Init();      //RC522 modülünü başlatıyoruz.

                                            
}
 
void loop() {

  if ( ! rfid.PICC_IsNewCardPresent())    //Yeni kartın okunmasını bekliyoruz.
    return;

  if ( ! rfid.PICC_ReadCardSerial())      //Kart okunmadığı zaman bekliyoruz.
    return;

  if (rfid.uid.uidByte[0] == ID[0] &&     //Okunan kart ID'si ile ID değişkenini karşılaştırıyoruz.
    rfid.uid.uidByte[1] == ID[1] && 
    rfid.uid.uidByte[2] == ID[2] && 
    rfid.uid.uidByte[3] == ID[3] ) {  
      
    
        Serial.println("Kapi acildi");
        ekranaYazdir();
        motor.write(0);                 //Servo motoru 180 dereceye getiriyoruz.
        delay(3000);
        motor.write(100);                   //Servo motoru 0 dereceye getiriyoruz.
         

    }
    else  if (rfid.uid.uidByte[0] == iID[0] &&     //Okunan kart ID'si ile ID değişkenini karşılaştırıyoruz.
    rfid.uid.uidByte[1] == iID[1] && 
    rfid.uid.uidByte[2] == iID[2] && 
    rfid.uid.uidByte[3] == iID[3] ) {  
      
    
        Serial.println("Kapi acildi");
        ekranaYazdir();
        motor.write(0);                 //Servo motoru 180 dereceye getiriyoruz.
        delay(3000);
        motor.write(100);                   //Servo motoru 0 dereceye getiriyoruz.
    
 
    }
    
    else{                                 //Yetkisiz girişte içerideki komutlar çalıştırılır.
      Serial.println("Yetkisiz Kart");
      ekranaYazdir();
  
    
    }
  rfid.PICC_HaltA();
}
void ekranaYazdir(){
  Serial.print("ID Numarasi: ");
  for(int sayac = 0; sayac < 4; sayac++){
    Serial.print(rfid.uid.uidByte[sayac]);
    Serial.print(" ");
  }
  Serial.println("");
}


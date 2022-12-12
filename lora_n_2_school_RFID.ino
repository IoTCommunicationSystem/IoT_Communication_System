#include <SoftwareSerial.h>
#include "SNIPE.h"

#define TXpin 6
#define RXpin 5
#define ATSerial Serial


#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
 
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

#define PICC_0 0x09 
#define PICC_1 0x53
#define PICC_2 0xB8
#define PICC_3 0xC1

#define PICC_4 0xEC 
#define PICC_5 0x71
#define PICC_6 0xEE
#define PICC_7 0x37

#define PICC_8 0x23 
#define PICC_9 0xAF
#define PICC_10 0x41
#define PICC_11 0x03

#define PICC_12 0xAB 
#define PICC_13 0x52
#define PICC_14 0xCA
#define PICC_15 0x22

MFRC522::MIFARE_Key key; 

// Init array that will store new NUID 
byte nuidPICC[4][4];
char *msg=0;


SoftwareSerial DebugSerial(RXpin,TXpin);
SNIPE SNIPE(ATSerial);

//16byte hex key
String lora_app_key = "44 55 66 77 88 99 aa bb cc dd ee ff 00 11 22 33";  


void setup() {
  ATSerial.begin(115200);

  // put your setup code here, to run once:
  while(ATSerial.read()>= 0) {}
  while(!ATSerial);

  DebugSerial.begin(115200);

  /* SNIPE LoRa Initialization */
  if (!SNIPE.lora_init()) {
    DebugSerial.println("SNIPE LoRa Initialization Fail!");
    while (1);
  }

  /* SNIPE LoRa Set Appkey */
  if (!SNIPE.lora_setAppKey(lora_app_key)) {
    DebugSerial.println("SNIPE LoRa app key value has not been changed");
  }
  
  /* SNIPE LoRa Set Frequency */
  if (!SNIPE.lora_setFreq(LORA_CH_1)) {
    DebugSerial.println("SNIPE LoRa Frequency value has not been changed");
  }

  /* SNIPE LoRa Set Spreading Factor */
  if (!SNIPE.lora_setSf(LORA_SF_7)) {
    DebugSerial.println("SNIPE LoRa Sf value has not been changed");
  }

  if (!SNIPE.lora_setRxtout(5000)) {
    DebugSerial.println("SNIPE LoRa Rx Timout value has not been changed");
  }  
    
  DebugSerial.println("check N");

  Serial.begin(115200);
  SPI.begin(); // Init SPI bus, SPI 시작
  rfid.PCD_Init(); // Init MFRC522  RF 모듈 시작
  rfid.PCD_DumpVersionToSerial();
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  Serial.println(F("This code scan the MIFARE Classsic NUID."));
  Serial.print(F("Using the following key:"));
  printHex(key.keyByte, MFRC522::MF_KEY_SIZE);

}

void loop(){



// Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! rfid.PICC_IsNewCardPresent())
    return;

  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial())
    return;

  Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  Serial.println(rfid.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type
 if (rfid.uid.uidByte[0] == PICC_0 && 
      rfid.uid.uidByte[1] == PICC_1 && 
      rfid.uid.uidByte[2] == PICC_2 && 
      rfid.uid.uidByte[3] == PICC_3 ) {
        
        if(nuidPICC[0][0] != PICC_0 && 
            nuidPICC[0][1] != PICC_1 && 
            nuidPICC[0][2] != PICC_2 && 
            nuidPICC[0][3] != PICC_3 ){
          msg = "DongHyun";
          Serial.println(F("Hello DongHyun !"));
          for (byte i = 0; i < 4; i++){
            nuidPICC[0][i] = rfid.uid.uidByte[i];
          }
          SNIPE.lora_send(msg);
        }else{
          Serial.println(F("Card read previously."));
        }
        

    }
    else if(rfid.uid.uidByte[0] == PICC_4 && 
      rfid.uid.uidByte[1] == PICC_5 && 
      rfid.uid.uidByte[2] == PICC_6 && 
      rfid.uid.uidByte[3] == PICC_7 ){

        if(nuidPICC[1][0] != PICC_4 && 
            nuidPICC[1][1] != PICC_5 && 
            nuidPICC[1][2] != PICC_6 && 
            nuidPICC[1][3] != PICC_7 ){
          msg = "GunWo";
          Serial.println(F("Hello GunWo !"));
          for (byte i = 0; i < 4; i++){
            nuidPICC[1][i] = rfid.uid.uidByte[i];
          }
          SNIPE.lora_send(msg);
        }else{
          Serial.println(F("Card read previously."));
        }
    }
    else if(rfid.uid.uidByte[0] == PICC_8 && 
      rfid.uid.uidByte[1] == PICC_9 && 
      rfid.uid.uidByte[2] == PICC_10 && 
      rfid.uid.uidByte[3] == PICC_11 ){

        if(nuidPICC[2][0] != PICC_8 && 
            nuidPICC[2][1] != PICC_9 && 
            nuidPICC[2][2] != PICC_10 && 
            nuidPICC[2][3] != PICC_11 ){
          msg = "MinJi";
          Serial.println(F("Hello MinJi !"));
          for (byte i = 0; i < 4; i++){
            nuidPICC[2][i] = rfid.uid.uidByte[i];
          }
          SNIPE.lora_send(msg);
        }else{
          Serial.println(F("Card read previously."));
        }

    }
    else if(rfid.uid.uidByte[0] == PICC_12 && 
      rfid.uid.uidByte[1] == PICC_13 && 
      rfid.uid.uidByte[2] == PICC_14 && 
      rfid.uid.uidByte[3] == PICC_15 ){

        if(nuidPICC[3][0] != PICC_12 && 
            nuidPICC[3][1] != PICC_13 && 
            nuidPICC[3][2] != PICC_14 && 
            nuidPICC[3][3] != PICC_15 ){
          msg = "DaHyun";
          Serial.println(F("Hello Dahyun !"));
          for (byte i = 0; i < 4; i++){
            nuidPICC[3][i] = rfid.uid.uidByte[i];
          }
          SNIPE.lora_send(msg);
        }else{
          Serial.println(F("Card read previously."));
        }
    }
    else{
    //등록된 카드가 아니라면 시리얼 모니터로 ID 표시
    msg = " ";
    Serial.println(F("This is an unconfirmed Card."));
    Serial.print(F("In hex: "));
    printHex(rfid.uid.uidByte, rfid.uid.size);    
  }
  

/*
  if (rfid.uid.uidByte[0] != nuidPICC[0] || 
    rfid.uid.uidByte[1] != nuidPICC[1] || 
    rfid.uid.uidByte[2] != nuidPICC[2] || 
    rfid.uid.uidByte[3] != nuidPICC[3] ) {
    Serial.println(F("This is an unconfirmed Card."));

    // Store NUID into nuidPICC array
    for (byte i = 0; i < 4; i++) {
      nuidPICC[i] = rfid.uid.uidByte[i];
    }
   
    Serial.println(F("The NUID tag is:"));
    Serial.print(F("In hex: "));
    printHex(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();
    Serial.print(F("In dec: "));
    printDec(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();
  }
  else Serial.println(F("Card read previously."));
  */

  // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();


/*

  if (SNIPE.lora_send("2"))
        {
          DebugSerial.println("send success");
          
          String ver = SNIPE.lora_recv();
          DebugSerial.println(ver);

          if (ver == "Ack 2")
          {
            
            DebugSerial.println(SNIPE.lora_getRssi());
            DebugSerial.println(SNIPE.lora_getSnr());            
          }
          else
          {
            DebugSerial.println("recv fail");
            delay(500);
          }
        }
       delay(1000);
       */
}
void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

/**
 * Helper routine to dump a byte array as dec values to Serial.
 */
void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }
}

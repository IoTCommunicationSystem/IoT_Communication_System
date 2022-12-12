// 학생, 진동감지ㆍ버튼 -> 부저
#include <SoftwareSerial.h>
#include "SNIPE.h"

#define TXpin 11
#define RXpin 10
#define ATSerial Serial

//16byte hex key
String lora_app_key = "44 55 66 77 88 99 aa bb cc dd ee ff 00 11 22 33";  

SoftwareSerial DebugSerial(RXpin,TXpin);
SNIPE SNIPE(ATSerial);

int status = 1;
int Shock = 2; // 진동감지센서
int button = 3; // 버튼
int buzzer = 5; // 부저

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

  pinMode(Shock, INPUT);
  pinMode(button, INPUT);
  pinMode(buzzer, OUTPUT);
}

void loop(){
  String ver;
  
  if(digitalRead(Shock) == HIGH) {
    status = 0;
  }
  else if(digitalRead(Shock) == LOW) {
    status = 1;
  }
  else if(digitalRead(button) == HIGH) {
    status = 2;
  }

  if (status == 0){
     //Send Command : Shocked
     if (SNIPE.lora_send("0")) {
        DebugSerial.println("Ack0");
        ver = SNIPE.lora_recv();
      }
        else {
        DebugSerial.println("send fail");
        delay(500);
      }
     } else if (status == 1) {
     //Send Command : Not Shocked            
      if (SNIPE.lora_send("1"))
        {
          DebugSerial.println("Ack1");
          ver = SNIPE.lora_recv();
        }    
      else
        {
          DebugSerial.println("send fail");
          delay(500);
        }  
      }
      else if (status == 2) {
        //Send Command : button pushed
        digitalWrite(buzzer, HIGH);
        if(SNIPE.lora_send("2"))
        {
          DebugSerial.println("Ack2");
          ver = SNIPE.lora_recv();
        }
      }
  delay(1000);
}

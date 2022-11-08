//pin번호들
int Shock = 2; // INPUT PIN
int pushButton = 3; // push
int buzzer = 5;

// 프로그램 시작 - 초기화 작업
void setup()
{
 //설정
 pinMode(Shock, INPUT);
 pinMode(pushButton,INPUT);
 pinMode(buzzer,OUTPUT);
 digitalWrite(Shock, HIGH);

//실행 확인할 시리얼 통신 초기화
 Serial.begin(9600);
 Serial.println("Arduino Examples - Shock Sensor");
 Serial.println(" https://docs.whiteat.com/?p=1258");
}
 
void loop()
{
  //충격감지 센서 통한 위험 감지
 if (LOW == digitalRead(Shock))
    Serial.println("아이가 위험합니다!");
 else
  Serial.print("."); // 없음
 
 delay(30);
 if(digitalRead(pushButton)==HIGH){
  //부저 울리기 + 부모님 기기에 알림띄우기
  digitalWrite(buzzer,HIGH);
  
  
 }
}

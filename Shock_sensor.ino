int Shock = 2; // INPUT PIN
 
// 프로그램 시작 - 초기화 작업
void setup()
{
 Serial.begin(9600); // 시리얼 통신 초기화
 Serial.println("Arduino Examples - Shock Sensor");
 Serial.println(" https://docs.whiteat.com/?p=1258");
 pinMode(Shock, INPUT);
 digitalWrite(Shock, HIGH);
}
 
void loop()
{
 if (LOW == digitalRead(Shock))
    Serial.println("아이가 위험합니다!"); // 감지
 else
  Serial.print("."); // 없음
 
 delay(30);
}

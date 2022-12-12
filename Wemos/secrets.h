/*
1. aws에서 사물을 생성한다.
2. '이름없는 섀도우'를 선택한다.
3. '새 인증서 자동 생성'을 선택한다.
4. 정책과 연결한다.
5. certificate.pem.crt, AmazonRootCA1, private.pem.key 파일을 다운받는다.
*/
#include <pgmspace.h> 
#define SECRET
 
const char WIFI_SSID[] = " ";               //와이파이 이름
const char WIFI_PASSWORD[] = " ";           //와이파이 비밀번호
 
#define THINGNAME " " //사물이름
 
int8_t TIME_ZONE = -5; //NYC(USA): -5 UTC
 
const char MQTT_HOST[] = " "; //endpoint주소
 
// AmazonRootCA1▼
static const char cacert[] PROGMEM = R"EOF( 
-----BEGIN CERTIFICATE-----
 
-----END CERTIFICATE-----
)EOF";
 
 
// Copy contents from XXXXXXXX-certificate.pem.crt here ▼
static const char client_cert[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----

-----END CERTIFICATE-----
 
)KEY";
 
 
// Copy contents from  XXXXXXXX-private.pem.key here ▼
static const char privkey[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----

-----END RSA PRIVATE KEY-----
 
)KEY";

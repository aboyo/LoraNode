#include <SoftwareSerial.h>

#define TX_Pin 7
#define RX_Pin 8
SoftwareSerial LoRa(RX_Pin, TX_Pin);  // 傳送腳,接收腳
#define LoRaBaud 115200

String SendString = "";    // string to hold input

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  LoRa_init();
  LoRa_parameter();
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:

  //  SendString = "mac tx ucnf 15 1234";
  //  Serial.println(SendString);
  //  Serial.print(sendLoRacmd(SendString , 300));
  //  delay(3000);

}

void LoRa_init() {
  LoRa.begin(LoRaBaud);
}

void LoRa_parameter() {

  SendString = "mac set_deveui 00a451b5xxxxxxxx";
  Serial.print("set_deveui>");
  Serial.print(sendLoRacmd(SendString , 300));

  SendString = "mac set_appeui 70b3d57exxxxxxxx";
  Serial.print("set_appeui>");
  Serial.print(sendLoRacmd(SendString , 300));

  SendString = "mac set_appkey 45d21689238a44e4339b813bxxxxxxxx";
  Serial.print("set_appkey>");
  Serial.print(sendLoRacmd(SendString , 300));

    SendString = "mac join otaa";
    Serial.print("join otaa:");
    Serial.print(sendLoRacmd(SendString ,300));

}

String sendLoRacmd(String cmd, unsigned int Dutytime) {
  String response = "";  // 接收LoRa回應值的變數
  LoRa.print(cmd); // 送出LoRa命令到LoRa模組
  unsigned long timeout = Dutytime + millis();
  while (LoRa.available() || millis() < timeout) {
    while (LoRa.available()) {
      //  if(millis() > timeout) break;
      char c = LoRa.read(); // 接收LoRa傳入的字元
      response += c;
    }
  }

  //Serial.print(response);  // 顯示LoRa的回應
  return (response);
}

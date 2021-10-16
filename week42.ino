#include <Servo.h>  //匯入函式庫
#define lED_PIN 27
Servo myservo;  // 建立伺服馬達控制
const int servoPin = 13;  //用常態變數設定pin腳位，與之前define方式差不
int pos = 90; //角度初始在中間，設定為90度
const int Button1_Pin = 26, Button2_Pin = 14; //紀錄兩按鈕腳位
bool btn1_Pressed = false, btn2_Pressed = false;  //紀錄兩按鈕按壓狀態
bool game = 0;//false=遊戲中 true=結束
void setup() {
  Serial.begin(115200);//序列阜連線速率(鮑率)
  
  myservo.attach(servoPin);  // 將伺服馬達連接的GPIO pin連接伺服物件
  myservo.write(90);  //角度初始在中間，設定為90度

   pinMode(Button1_Pin, INPUT);
   pinMode(Button2_Pin, INPUT);
   pinMode(lED_PIN,OUTPUT);
   
}

void loop() {
  if(game == 0){
     //Player 1
     if(digitalRead(Button1_Pin) == HIGH && btn1_Pressed == false){
       btn1_Pressed = true;
       pos += 5; //角度加五度
     }
     else if(digitalRead(Button1_Pin) == LOW && btn1_Pressed == true){
       btn1_Pressed = false;
     }
     //Player 2
     if(digitalRead(Button2_Pin) == HIGH && btn2_Pressed == false){
        btn2_Pressed = true;
       pos -= 5; //角度減五度
     }
     else if(digitalRead(Button2_Pin) == LOW && btn2_Pressed == true){
        btn2_Pressed = false;
     }
     Serial.println(pos);
     myservo.write(pos);
     if(pos==0 || pos==180){
        digitalWrite(lED_PIN,HIGH);
        game = 1;
     }
   }
  else {
    if(digitalRead(Button1_Pin) == HIGH && digitalRead(Button2_Pin) == HIGH){
      digitalWrite(lED_PIN,LOW);
      game = 0;
      pos = 90;
     }
 }
}

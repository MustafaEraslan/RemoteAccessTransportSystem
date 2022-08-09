#include <SoftwareSerial.h>
#include <SerialESP8266wifi.h>
#define ag_ismi "TURKCELL T50"
#define ag_sifresi "mustafa123"

const int in1 = 11;
const int in2 = 10;
const int in3 = 9;
const int in4 = 8;

//const int enA = 5;  
//const int enB = 6;

void setup() {
  Serial.begin(115200); //Seriport'u açıyoruz. Güncellediğimiz 
                        //ESP modülünün baudRate değeri 115200 olduğu için bizde Seriport'u 115200 şeklinde seçiyoruz
  Serial.println("AT"); //ESP modülümüz ile bağlantı kurulup kurulmadığını kontrol ediyoruz.
  delay(5000);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  //pinMode(enA, OUTPUT);
 // pinMode(enB, OUTPUT);

   delay(3000); //ESP ile iletişim için 3 saniye bekliyoruz.

   if(Serial.find("OK")){         //esp modülü ile bağlantıyı kurabilmişsek modül "AT" komutuna "OK" komutu ile geri dönüş yapıyor.
     Serial.println("AT+CWMODE=1"); //esp modülümüzün WiFi modunu STA şekline getiriyoruz. Bu mod ile modülümüz başka ağlara bağlanabilecek.
     delay(2000);
     String baglantiKomutu=String("AT+CWJAP=\"")+ag_ismi+"\",\""+ag_sifresi+"\"";
     Serial.println(baglantiKomutu);
     delay(5000);
   }
      Serial.print("AT+CIPMUX=1\r\n");
      delay(2000);
      Serial.print("AT+CIPSERVER=1,80\r\n");
      delay(1000);

}

void loop(){
  if(Serial.available()>0){
    if(Serial.find("+IPD,")){
      String metin = "<head> Uzaktan Erisimli Tasima Sistemi </head>";
      metin += "<br><a href=\" ?pin=ileri\"><button type='button'>ILERI</button></a>"; 
      metin += "<br><a href=\" ?pin=geri\"><button type='button'>GERI</button></a>";      
      metin += "<br><a href=\" ?pin=dur\"><button type='button'>DUR</button></a>";
      metin += "<br><a href=\" ?pin=sag\"><button type='button'>SAG</button></a>";      
      metin += "<br><a href=\" ?pin=sol\"><button type='button'>SOL</button></a>";
      String cipsend = "AT+CIPSEND=";
      cipsend +="0";
      cipsend +=",";
      cipsend += metin.length();
      cipsend += "\r\n";
      Serial.print(cipsend);
      delay(500);
      Serial.println(metin);
      dc_motor_hareketi();
     Serial.println("AT+CIPCLOSE=0");
    }
  }
}

void dc_motor_hareketi(){
 String gelen ="";
 char serialdenokunan;
 while(Serial.available()>0){
 serialdenokunan = Serial.read();
 gelen +=serialdenokunan;
 }
 Serial.println(gelen);
 if((gelen.indexOf(":GET /?pin=ileri")>1)){  //ileri butonuna basıldığında server adresinde /?pin=ileri var ise
  //analogWrite(enA,  60);
  //analogWrite(enB,  40);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
} 
if((gelen.indexOf(":GET /?pin=geri")>1)){ // geri butonuna basıldığında server adresinde /?pin=geri var ise
  //analogWrite(enA,  60);
//  analogWrite(enB,  40);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);              
}
if((gelen.indexOf(":GET /?pin=dur")>1)){ // dur butonuna basıldığında server adresinde /?pin=dur var ise
  //analogWrite(enA,  60);
  //analogWrite(enB,  40);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
if((gelen.indexOf(":GET /?pin=sag")>1)){ // sag butonuna basıldığında server adresinde /?pin=sag var ise
 //analogWrite(enA,  60);
 // analogWrite(enB,  40);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);       
  delay(2000);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
if((gelen.indexOf(":GET /?pin=sol")>1)){ // sol butonuna basıldığında server adresinde /?pin=sol var ise
  //analogWrite(enA,  60);
 // analogWrite(enB,  40);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(2000);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
}

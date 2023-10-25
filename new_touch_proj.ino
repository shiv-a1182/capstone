#include <WiFi.h>         //Including wifi.h library it will take care of all wifi related task
#include <HTTPClient.h>  //Including HTTPClient.h library to use all api 
#include "mp3tf16p.h"
MP3Player mp3(16, 17);
#define touchPin1    21

#define touchPin2    19

#define touchPin3    05

#define touchPin4    18



int capacitiveValue1 = 100;
int threshold1 = 20; //Threshold to adjust
int capacitiveValue2 = 100;
int threshold2 = 20; //Threshold to adjust
int capacitiveValue3 = 100;
int threshold3 = 20; //Threshold to adjust
int capacitiveValue4 = 100;
int threshold4 = 20; //Threshold to adjust

const char* ssid = "sss";            // WiFi ssid
const char* password = "12341234";    // WiFi password

String apiKey = "395215";              //Token number that bot has sent you on signal messenger
String phone_number = "+917993065188   "; // signal app registered phone number (same number that bot send you in url)

String url;                            //url String will be used to store the final generated URL


void setup() {
      Serial.begin(115200);
    WiFi.begin(ssid, password);               // Try to connect with the given SSID and PSS

  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED)    // Wait until WiFi is connected
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to the WiFi network"); // Print wifi connect message
  pinMode(21,INPUT);
  pinMode(19,INPUT);
  pinMode(05,INPUT);
  pinMode(18,INPUT);
 mp3.initialize();
   
}

void loop() {
    capacitiveValue1 = digitalRead(21);
    Serial.println( touchRead(touchPin1));
    delay(500);
    capacitiveValue2 = digitalRead(19);
    Serial.println( touchRead(touchPin2));
     delay(500);
    capacitiveValue3 = digitalRead(05);
    Serial.println( touchRead(touchPin3));
     delay(500);
    capacitiveValue4 = digitalRead(18);
    Serial.println( touchRead(touchPin4));
     delay(500);
    
    String out1 = " I NEED WATER" ;
    String out2 = " I NEED FOOD " ;
    String out3 = " I NEED WASHROOM" ;
    String out4 = " I NEED EMERGENCY" ;
    if(capacitiveValue1 == 1 ){
        Serial.println("Wire touched--1");
         message_to_signal(out1);
         mp3.playTrackNumber(001, 100);
        }
    delay(100);
    if(capacitiveValue2 == 1 ){
        Serial.println("Wire touched--2");
         message_to_signal(out2);
         mp3.playTrackNumber(002, 100);
        }
    delay(100);
       if(capacitiveValue3 == 1 ){
        Serial.println("Wire touched--3");
         message_to_signal(out3);
         mp3.playTrackNumber(003, 100);
        }
    delay(100);
      if(capacitiveValue4 == 1 ){
        Serial.println("Wire touched--4");
         message_to_signal(out4);
         mp3.playTrackNumber(004, 100);
        }
    delay(100);
    
}

void  message_to_signal(String message)       // user define function to send meassage to Signal app
{
  //adding all number, your api key, your message into one complete url
  url = "https://api.callmebot.com/signal/send.php?phone=" + phone_number + "&apikey=" + apiKey + "&text=" + urlencode(message);

  postData(); // calling postData to run the above-generated url once so that you will receive a message.
}

void postData()     //userDefine function used to call api(POST data)
{
  int httpCode;     // variable used to get the responce http code after calling api
  HTTPClient http;  // Declare object of class HTTPClient
  http.begin(url);  // begin the HTTPClient object with generated url
  httpCode = http.POST(url); // Finaly Post the URL with this function and it will store the http code
  if (httpCode == 200)      // Check if the responce http code is 200
  {
    Serial.println("Sent ok."); // print message sent ok message
  }
  else                      // if response HTTP code is not 200 it means there is some error.
  {
    Serial.println("Error."); // print error message.
  }
  http.end();         // After calling API end the HTTP client object.
}

String urlencode(String str)  // Function used for encoding the url
{
  String encodedString = "";
  char c;
  char code0;
  char code1;
  char code2;
  for (int i = 0; i < str.length(); i++) {
    c = str.charAt(i);
    if (c == ' ') {
      encodedString += '+';
    } else if (isalnum(c)) {
      encodedString += c;
    } else {
      code1 = (c & 0xf) + '0';
      if ((c & 0xf) > 9) {
        code1 = (c & 0xf) - 10 + 'A';
      }
      c = (c >> 4) & 0xf;
      code0 = c + '0';
      if (c > 9) {
        code0 = c - 10 + 'A';
      }
      code2 = '\0';
      encodedString += '%';
      encodedString += code0;
      encodedString += code1;
      //encodedString+=code2;
    }
    yield();
  }
  return encodedString;
}

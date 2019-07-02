#include <HCSR04.h>
#include <ESP8266WiFi.h> 
#include  <FirebaseArduino.h>

#define FIREBASE_HOST "Your_FIREBASE_HOST"  
#define FIREBASE_AUTH "Your_FIREBASE_AUTH"  

const char*WIFI_SSID = "Your_WIFI_SSID" ;  // ชื่อ WiFi
const char*WIFI_PASSWORD = "Your_WIFI_PASSWORD" ; // รหัส WiFi

HCSR04 hc(D1,D2);
HCSR04 hc2(D3,D6);




void setup() {
  
  
  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
 
  while (WiFi.status() != WL_CONNECTED) {
  
    Serial.print(".");
    delay(500);
   
  }
 
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
 
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
 
 
}

void loop() {
 
  double a1 = hc.dist();
  double a2 = hc2.dist();
  Serial.print( "a1 = ");
  Serial.print( hc.dist() ); Serial.println("   CM");
   Serial.print( "a2 = ");
  Serial.print( hc2.dist()); Serial.println("   CM"); 
   delay(500);
  
  
  if(a1<10){
  
  Firebase.setInt("/ParkingInfo/-LdULjKjdsI17-T-LLMp/a1Status",1 );

  
  
  }else{
    
    Firebase.setInt("/ParkingInfo/-LdULjKjdsI17-T-LLMp/a1Status",0);
  
  }

  if(a2<10){
      
      Firebase.setInt("/ParkingInfo/-LdULjKjdsI17-T-LLMp/a2Status",1 );
      
    }else{
      
    
    Firebase.setInt("/ParkingInfo/-LdULjKjdsI17-T-LLMp/a2Status",0);
  }

  
   int parkoneSlot = Firebase.getInt("/ParkingInfo/-LdULjKjdsI17-T-LLMp/nSlot");
   int a1Status = Firebase.getInt("/ParkingInfo/-LdULjKjdsI17-T-LLMp/a1Status");
   int a2Status = Firebase.getInt("/ParkingInfo/-LdULjKjdsI17-T-LLMp/a2Status");
   
   int parkOneTotal = parkoneSlot-(a1Status+a2Status);
   
   

   if(parkOneTotal>0){
       Firebase.setInt("/ParkingInfo/-LdULjKjdsI17-T-LLMp/empSlot",parkOneTotal );
      
      
    }else if (parkOneTotal==0){
     Firebase.setString("/ParkingInfo/-LdULjKjdsI17-T-LLMp/empSlot","เต็ม");
    }
   
   
   
   
  
    
  

}

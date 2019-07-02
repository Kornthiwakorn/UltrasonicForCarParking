#include <HCSR04.h>
#include <ESP8266WiFi.h> 
#include <FirebaseArduino.h>
#include <ArduinoJson.h>

#define FIREBASE_HOST "Your_FIREBASE_HOST"  
#define FIREBASE_AUTH "Your_FIREBASE_AUTH"  

const char*WIFI_SSID = "Your_WIFI_SSID" ;  // ชื่อ WiFi
const char*WIFI_PASSWORD = "Your_WIFI_PASSWORD" ; // รหัส WiFi


HCSR04 hc(D1,D2);
HCSR04 hc2(D5,D6);




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
  double b1 = hc.dist();
  double b2 = hc2.dist();
  Serial.print( hc.dist() ); Serial.println("   CM");
  Serial.print( hc2.dist()); Serial.println("   CM"); 
  
  
  if(b1<10){
  
  Firebase.setInt("ParkingTwo/B1_Status", 1 );

  
  
  }else{
    
    Firebase.setInt("ParkingTwo/B1_Status", 0 );
  
  }

  if(b2<10){
      
      Firebase.setInt("ParkingTwo/B2_Status", 1 );
      
    }else{
      
    
    Firebase.setInt("ParkingTwo/B2_Status", 0 );
  }

  

   int b1Status = Firebase.getInt("ParkingTwo/B1_Status");
   int b2Status = Firebase.getInt("ParkingTwo/B2_Status");
   int parkTwoTotal = 2-(b1Status+b2Status);
   
   

   if(parkTwoTotal>0){
       Firebase.setInt("ParkingInfo/ParkingTwo/SlotTotal",parkTwoTotal );
      
      
    }else if (parkTwoTotal==0){
     Firebase.setInt("ParkingInfo/ParkingTwo/SlotTotal",0 );
    }
   
   
   
   
   
    
  delay(500);

}

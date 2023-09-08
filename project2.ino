#include <ESP8266WiFi.h>
 
const char* ssid = "Hadis";
const char* password = "hghghghg";
int OnTime=0;
int OffTime=0;

WiFiServer server(8888);
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("if you are in LOCAL NETWORK Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

  Serial.print("if you want to use this web server from anywhere; chnage port numer to:8888 and Use ngrok's URL ");
  Serial.println("/");
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();


 
  // Match the request
 
  int value = LOW;

  //On Order = On LED
  if (request.indexOf("/OnOrder") != -1) {
     digitalWrite(LED_BUILTIN, LOW);
     while(request.indexOf("/favicon.ico") != -1) {
      OnTime = 1 ;
      OffTime = 0 ;   
     }
     value = LOW;
  }

  // Off Order = Off LED
  else if (request.indexOf("/OffOrder") != -1) {   
     digitalWrite(LED_BUILTIN, HIGH);
     while(request.indexOf("/favicon.ico") != -1) {
      OffTime = 1 ;
      OnTime = 0 ; 
     }
     value = HIGH;
  }

  //Flashing LED
  else 
    {
      //set On time
    if (request.indexOf("On=") != -1) {
      digitalWrite(LED_BUILTIN, LOW);
      String req1 = request.substring(9,12);
      Serial.println(req1);
      OnTime = (request.substring(9,12)).toInt();
      value = LOW;  
      } 

    //set Off time
    if (request.indexOf("off=") != -1){
     digitalWrite(LED_BUILTIN, HIGH);
     String req2 = request.substring(17,20);  
     Serial.println(req2);
     OffTime = (request.substring(17,20)).toInt();
     value = HIGH;
     }
   }
  

 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println("<style>");
  client.println("html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
  client.println(".button { background-color: green; border: none; color: white; padding: 14px 38px;");
  client.println("text-decoration: none; font-size: 20px; margin: 2px; cursor: pointer;}");
  client.println(".button2 {background-color: red;}");
  client.println(".submit {background-color: #195B6A;}");
  client.println("</style>");
  client.println("</head>");
  client.println("<body>");
  client.println("<h2>Wellcome to </h2>");
  client.println("<h1><q>wemoc mini ESP8266 Web Server </q></h1>");
  client.println("<br><br>");
  client.println("<br><br>");
  client.println("<form style=\"align: center;\" action=\"\" method=\"get\" class=\"form-example\">");
  client.println("<label for=\"ON\">Time(ms) on: </label>");
  client.println("<input type=\"text\" name=\"On\" id=\"On\" required>");
  client.println("<br><br>");
  client.println("<label for=\"OFF\">Time(ms) off: </label>");
  client.println("<input type=\"text\" name=\"off\" id=\"off\" required>");
  client.println("<br><br>");
  client.println("&nbsp &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp ");
  client.println("<input type=\"submit\" value=\"Send\" input class=\"button submit\">");
  client.println("</form>");
  client.println("<br><br>");
  client.println("<br><br>");
  client.println("<br><br>");
  client.println("<a href=\"/OnOrder\"\"><button class=\"button\">LED ON</button></a>");
  client.println("<a href=\"/OffOrder\"\"><button class=\"button button2\">LED OFF</button></a>");
  client.println("</body>");
  client.println("</html>");


  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");

  while(OnTime+ OffTime)
{
digitalWrite(LED_BUILTIN, LOW);
delay(OnTime);
digitalWrite(LED_BUILTIN, HIGH);
delay(OffTime);
}

}

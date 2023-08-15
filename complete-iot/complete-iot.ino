#include <ESP8266WiFi.h>
#include<Servo.h>
// Replace with your network credentials
const char* ssid     = "YourSSID";
const char* password = "********";

WiFiServer server(80);
String header;

// Auxiliar variables to store the current output state
Servo Smotor;
String pin0 = "off";
String pin2 = "off";
String pin3 = "off";
String pin4 = "off";
String pin5 = "off";

// Assign output variables to GPIO pins
#define O_PIN0 0
#define O_PIN2 2
#define O_PIN3 3
#define O_PIN4 4
#define O_PIN5 5

unsigned long currentTime = millis();
unsigned long previousTime = 0; 
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(O_PIN2, OUTPUT);
  pinMode(O_PIN4, OUTPUT);
  pinMode(O_PIN5, OUTPUT);
  pinMode(O_PIN0, OUTPUT);
  pinMode(O_PIN3, OUTPUT);
  // Set outputs to LOW
  digitalWrite(O_PIN0, LOW);
  digitalWrite(O_PIN2, LOW);
  digitalWrite(O_PIN4, LOW);
  digitalWrite(O_PIN5, LOW);
  digitalWrite(O_PIN3, LOW);
  Smotor.attach(O_PIN0);

  // For Establishing Connection With WIFI Module
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}


void loop(){
  WiFiClient client = server.available();   

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();         
      if (client.available()) {             
        char c = client.read();             
        Serial.write(c);                    
        header += c;
        if (c == '\n') {                    
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            
            if (header.indexOf("GET /4/on") >= 0) {
              Serial.println("PIN4 on");
              pin4 = "on";
              digitalWrite(O_PIN4, HIGH);
            } else if (header.indexOf("GET /4/off") >= 0) {
              Serial.println("PIN4 off");
              pin4 = "off";
              digitalWrite(O_PIN4, LOW);
            } else if (header.indexOf("GET /5/on") >= 0) {
              Serial.println("PIN5 on");
              pin5 = "on";
              digitalWrite(O_PIN5, HIGH);
            } else if (header.indexOf("GET /5/off") >= 0) {
              Serial.println("PIN5 off");
              pin5 = "off";
              digitalWrite(O_PIN5, LOW);
            } else if (header.indexOf("GET /0/on") >= 0) {
              Serial.println("PIN0 on");
              pin0 = "on";
              Smotor.write(90);
              //digitalWrite(O_PIN0, HIGH);
            } else if (header.indexOf("GET /0/off") >= 0) {
              Serial.println("PIN0 off");
              pin0 = "off";
              Smotor.write(0);
              //digitalWrite(O_PIN0, LOW);
            } else if (header.indexOf("GET /2/on") >= 0) {
              Serial.println("PIN2 on");
              pin2 = "on";
              digitalWrite(O_PIN2, HIGH);
            } else if (header.indexOf("GET /2/off") >= 0) {
              Serial.println("PIN2 off");
              pin2 = "off";
              digitalWrite(O_PIN2, LOW);
            } else if (header.indexOf("GET /3/on") >= 0) {
              Serial.println("PIN3 on");
              pin3 = "on";
              digitalWrite(O_PIN3,HIGH);
            } else if (header.indexOf("GET /3/off") >= 0) {
              Serial.println("PIN3 off");
              pin3 = "off";
              digitalWrite(O_PIN3, LOW);
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: light red; border: none; color: gray; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: light red;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>SmartHomeAutomation</h1>");


            //Display States of Pins Start Here
            client.println("<p>PIN2</p>");
            if (pin2=="off") {
              client.println("<p><a href=\"/2/on\"><button class=\"button\">OFF</button></a></p>");
            } else {
              client.println("<p><a href=\"/2/off\"><button class=\"button button2\">ON</button></a></p>");
            } 
            client.println("<p>PIN4</p>");
            if (pin4=="off") {
              client.println("<p><a href=\"/4/on\"><button class=\"button\">OFF</button></a></p>");
            } else {
              client.println("<p><a href=\"/4/off\"><button class=\"button button2\">ON</button></a></p>");
            } 
            client.println("<p>PIN5</p>");
            if (pin5=="off") {
              client.println("<p><a href=\"/5/on\"><button class=\"button\">OFF</button></a></p>");
            } else {
              client.println("<p><a href=\"/5/off\"><button class=\"button button2\">ON</button></a></p>");
            } 
            client.println("<p>PIN0</p>");
            if (pin0=="off") {
              client.println("<p><a href=\"/0/on\"><button class=\"button\">OFF</button></a></p>");
            } else {
              client.println("<p><a href=\"/0/off\"><button class=\"button button2\">ON</button></a></p>");
            } 
            client.println("<p>PIN3</p>");
            // If the output4State is off, it displays the ON button       
            if (pin3=="off") {
              client.println("<p><a href=\"/3/on\"><button class=\"button\">OFF</button></a></p>");
            } else {
              client.println("<p><a href=\"/3/off\"><button class=\"button button2\">ON</button></a></p>");
            }
            client.println("</body></html>");
            
            client.println();
            // While Loop Breaks Here
            break;
          } else { 
            currentLine = "";
          }
        } else if (c != '\r') {  
          currentLine += c;      
        }
      }
    }
    header = "";
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}

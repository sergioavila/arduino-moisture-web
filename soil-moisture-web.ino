#include <ESP8266WiFi.h>

// Replace these with your WiFi network settings
const char* ssid = "ssid-wifi"; //replace this with your WiFi network name
const char* password = "pass-wifi"; //replace this with your WiFi network password
int MoistureLevel = 0;
int Porcentaje = 0;
WiFiServer server(80);

void setup()
{
  delay(1000);
  Serial.begin(9600);
 
  WiFi.begin(ssid, password);

  Serial.println();
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("success!");
  Serial.print("IP Address is: ");
  Serial.println(WiFi.localIP());
  server.begin();
  Serial.println("Server started");
}

void loop() {
  MoistureLevel = int(analogRead(A0));
  Serial.println(MoistureLevel);
  WiFiClient client = server.available();
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println("Refresh: 5");
  client.println();
  client.println("<!DOCTYPE html>");
  client.println("<html xmlns='http://www.w3.org/1999/xhtml'>");
  client.println("<head>\n<meta charset='UTF-8'>");
  client.println("<meta name='viewport' content='width=device-width, initial-scale=1'>");
  client.println("<title>Arduinito</title>");
  client.println("<link href='https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha3/dist/css/bootstrap.min.css' rel='stylesheet' crossorigin='anonymous'>");
  client.println("<style>body{background-color:#42b288;color:#ffffff;font-size: 20px;font-family:sans-serif;}</style>");
  client.println("</head>\n<body class='text-center'>");
  client.println("<h2>Soil Moisture</h2>");
  client.println("<svg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' width='120' height='120'><path d='M5.99805 2C8.68733 2 11.0224 3.51653 12.1947 5.74104C13.372 4.08252 15.3086 3 17.498 3H20.998V5.5C20.998 9.08985 18.0879 12 14.498 12H12.998V13H17.998V20C17.998 21.1046 17.1026 22 15.998 22H7.99805C6.89348 22 5.99805 21.1046 5.99805 20V13H10.998V11H8.99805C5.13205 11 1.99805 7.86599 1.99805 4V2H5.99805ZM15.998 15H7.99805V20H15.998V15ZM18.998 5H17.498C15.0128 5 12.998 7.01472 12.998 9.5V10H14.498C16.9833 10 18.998 7.98528 18.998 5.5V5ZM5.99805 4H3.99805C3.99805 6.76142 6.23662 9 8.99805 9H10.998C10.998 6.23858 8.75947 4 5.99805 4Z' fill='rgba(255,255,255,1)'></path></svg>");
  client.println("<h1>");
  //630 min, 260 max
  Porcentaje = map(MoistureLevel, 630, 260, 0, 100);
  client.println(Porcentaje);
  client.println("%</h1>");
  client.print("</body>\n</html>");
  delay(2000);
}

#include <WiFi.h>
#include <WebServer.h>

#include <BlynkSimpleEsp32.h>

const char auth[] = "8E-fM2CEOxMkhiteQlEhQvx42K7O4XkY";

WebServer server(80);

const char* ssid = "SFR_ED9F";
const char* pass =  "";

void setup()
{
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  Blynk.begin(auth, ssid, pass, "Blynk.cloud", 80);

  Serial.print("Tentativie de connexion...");

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(100);
  }

  Serial.println("\n");
  Serial.println("Connexion etablie !!");
  Serial.print("Adresse IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", handle_root);

  server.begin();
  Serial.println("HTTP server started");
  delay(100);

}

void loop()
{
  server.handleClient();
  Blynk.run();
}

// HTML & CSS contents which display on web server


// Handle root url (/)
void handle_root() {
  String page = "<!DOCTYPE html>";
page += "<html>";
page += "<body>";
page +=    "<title> Etat Button led </title>";
page +=   "<head>";
//page +=       "<meta charset="utf - 8">";
//page +=        "<link rel="stylesheet" href="style_led.css">";
page +=    "</head>";
page += "<h1>Salut</h1>";
page += "<button type="button">TEST</button>";
//page +=    "<button style=" background-color: green; " class="favorite styled" type="button"> ON </button>";
//page +=    "<button style=" background-color: red; " class="favorite styled" type="button"> OFF </button>";
page += "</body>";
page += "</html>";

  server.send(200, "text / html", page);
}

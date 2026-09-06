#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <LittleFS.h> // Required to pull the GIF from memory

const byte DNS_PORT = 53;
// keeping your IP address since it successfully triggered your phone!
IPAddress apIP(172, 217, 28, 1); 
DNSServer dnsServer;
ESP8266WebServer webServer(80);

String responseHTML = ""
                      "<!DOCTYPE html><html lang='en'><head>"
                      "<meta name='viewport' content='width=device-width'>"
                      "<title>CaptivePortal</title></head><body style='text-align:center; margin-top:50px;'>"
                      ""
                      "<img src='/animation.gif' style='max-width: 90%; border-radius: 10px;'>"
                      "</body></html>";

void setup() {
  // Start LittleFS to access the GIF file
  LittleFS.begin();

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP("Free WiFi"); // The name of the network broadcasted

  // Reply with the provided IP to all DNS requests
  dnsServer.start(DNS_PORT, "*", apIP);

  // The master handler for all web traffic
  webServer.onNotFound([]() {
    String path = webServer.uri();
    
    // 1. If the phone is explicitly asking for the GIF to render the page, serve it from LittleFS
    if (path.endsWith(".gif")) {
      if (LittleFS.exists(path)) {
        File file = LittleFS.open(path, "r");
        webServer.streamFile(file, "image/gif");
        file.close();
        return; // Stop here so it doesn't send the HTML
      }
    }
    
    // 2. For all other requests (like the background internet check), send your working HTML
    webServer.send(200, "text/html", responseHTML);
  });
  
  webServer.begin();
}

void loop() {
  dnsServer.processNextRequest();
  webServer.handleClient();
}

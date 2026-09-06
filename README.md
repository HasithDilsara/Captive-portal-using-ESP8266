# ESP8266 Captive Portal with Wi-Fi Access Point & GIF

A learning project using an **ESP8266 NodeMCU** to explore Wi-Fi networking, network configuration, DNS handling, captive portals, embedded web servers, and flash-based file storage.

The ESP8266 creates its own Wi-Fi network. When a device connects to the network, DNS requests are handled by the ESP8266 and the device is directed to a locally hosted web page. The page displays an animated GIF stored in the ESP8266's flash memory using **LittleFS**.

---

## 🎯 Project Objective

The main objective of this project is to understand how **network configuration and networking concepts can be implemented on a microcontroller**.

The project provides practical experience with:

* Wi-Fi Access Point configuration
* SSID and password configuration
* IP addressing
* Captive portal concepts
* HTTP web servers
* HTTP request routing
* Embedded web pages
* ESP8266 flash storage
* LittleFS file management
* Serving media files from a microcontroller

---

## ✨ Features

### 📡 Wi-Fi Access Point

The ESP8266 operates in **Access Point (AP) mode**, allowing nearby devices to connect directly to it without requiring an existing Wi-Fi router.

### 🌐 Local Web Server

An HTTP web server runs directly on the ESP8266.

The server listens for HTTP requests and provides the required web content to connected devices.

### 🔀 DNS-Based Captive Portal

This causes domain requests from connected devices to resolve to the ESP8266's Access Point IP.

### 📱 Captive Portal Detection

Different operating systems use different URLs to test whether a Wi-Fi network has Internet access.

> Captive portal behavior depends on the operating system and device. Some devices may automatically display the portal, while others may require the user to open a browser manually.

---

### 🖥️ Web Interface

The project displays a custom web interface containing an animated GIF.

The page uses:

* HTML
* CSS
* Responsive viewport settings
* Full-screen layout
* GIF animation

The interface is designed to adapt to mobile device screens.

---

### 🎞️ Animated GIF

An animated GIF can be served by the ESP8266 and displayed in the browser.
The GIF is stored in the ESP8266's flash filesystem and served through an HTTP endpoint.

---

## 💾 LittleFS File System

The project uses **LittleFS** to store files in the ESP8266's flash memory.
The ESP8266 reads the GIF from LittleFS and streams it to the connected device.
This allows the ESP8266 to act as a small standalone web-content server.

---

# 🧩 Why Use HTML as a String Instead of `index.html`?
When using stored html file, It refuced to open portal automatically many times on some devices. Then the HTML page embedded directly inside the ESP8266 program as a C++ `String`, instead of storing `html file` in LittleFS. In most of devices, portal opens automatically when connected to wifi. 


## 📁 Why Use LittleFS for the GIF Then?

Although the HTML can be stored as a String, a GIF is much more suitable for LittleFS.

A GIF can be relatively large compared with a small HTML page.

Instead of putting a large binary file inside the C++ source code, LittleFS allows the ESP8266 to store the GIF as a normal file:

```text
animation.gif
```

This keeps the program code cleaner and avoids unnecessarily embedding binary data into the source code.

---

# 🔧 Main Libraries

## ESP8266WiFi

Used to configure the ESP8266's wireless networking functionality.

```cpp
#include <ESP8266WiFi.h>
```

Used for:

* Access Point creation
* Wi-Fi configuration
* IP address information

---

## DNSServer

Used to implement DNS request handling for the captive portal.

```cpp
#include <DNSServer.h>
```

Main functionality:

```text
DNS Request → ESP8266 IP Address
```

---

## ESP8266WebServer

Used to create the HTTP server.

```cpp
#include <ESP8266WebServer.h>
```

It handles:

* HTTP requests
* URL routes
* HTTP responses
* File serving

---

## LittleFS

Used as the flash-based filesystem.

```cpp
#include <LittleFS.h>
```

It provides:

* File storage
* File reading
* File management
* Serving web assets

---

# 🔄 System Workflow

The complete process is:

```text
                ESP8266
                   │
                   ▼
          Create Wi-Fi AP
                   │
                   ▼
            Device connects
                   │
                   ▼
          Device sends DNS request
                   │
                   ▼
          ESP8266 DNS Server
                   │
                   ▼
          Resolve to ESP8266 IP
                   │
                   ▼
          Captive Portal Request
                   │
                   ▼
          ESP8266 Web Server
                   │
                   ▼
             HTML Response
                   │
                   ▼
             Browser Page
                   │
                   ▼
          Request animation.gif
                   │
                   ▼
               LittleFS
                   │
                   ▼
             GIF is streamed
                   │
                   ▼
             GIF displayed
```

---

# 📂 Project Structure

If the HTML is embedded directly in the Arduino sketch:

```text
ESP8266-Captive-Portal/
│
├── ESP8266-Captive-Portal.ino
│
└── data/
    └── animation.gif
```

The `data` folder is used by LittleFS for files that need to be stored in the ESP8266's flash filesystem.

---

# ⚙️ Configuration

The Wi-Fi credentials can be changed in the source code:

```cpp
const char* ssid = "ESP8266_GIF";
const char* password = "12345678";
```

The portal can also be customized by modifying the embedded HTML String.

---

# 🚀 Setup

### 1. Install ESP8266 Support

Install the ESP8266 board package through the Arduino IDE Board Manager.

Select:

```text
NodeMCU 1.0 (ESP-12E Module)
```

### 2. Prepare LittleFS

Place the GIF inside:

```text
data/
```

For example:

```text
data/animation.gif
```

### 3. Upload the Filesystem

Upload the `data` directory to the ESP8266 using the appropriate **LittleFS Data Upload** tool.

### 4. Upload the Firmware

Upload the `.ino` program to the ESP8266.

### 5. Connect to the Network

Search for the configured SSID from a phone or computer.

Example:

```text
ESP8266_GIF
```

### 6. Open the Portal

If the device does not automatically open the captive portal, open:

```text
192.168.4.1
```

in a browser.

---

# ⚠️ Limitations

The ESP8266 has limited processing power, RAM, flash storage, and Wi-Fi bandwidth.

Therefore:

* Keep GIF files reasonably small.
* Large GIFs may load slowly.
* Captive portal behavior varies between operating systems.
* Automatic portal popups cannot be guaranteed on every device.
* The ESP8266 Access Point does not automatically provide Internet access.
* Multiple simultaneous users can increase memory and bandwidth usage.

---

# 🔬 What I Learned

This project provided practical experience with:

**Embedded Systems**

* ESP8266 programming
* Flash storage
* LittleFS

**Networking**

* Wi-Fi Access Points
* IP addressing
* DNS
* DNS redirection
* HTTP
* Captive portal concepts

**Web Technologies**

* HTML
* CSS
* HTTP routing
* Serving media from an embedded device

The project was developed primarily as a **hands-on learning experiment to understand networking configuration on ESP8266 and how embedded hardware can provide network services without a traditional server.**


## 📜 License

This project is intended for educational and experimental purposes.

Feel free to modify and build upon it for your own learning and embedded networking experiments.

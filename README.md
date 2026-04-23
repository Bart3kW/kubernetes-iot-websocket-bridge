# 🕸️ Kubernetes IoT WebSocket Bridge
*Wersja polska poniżej*

## About The Project
This project is a custom HomeLab distributed real-time communication system. It actively bridges the world of microcontrollers (IoT) with modern cloud infrastructure deployed on a Kubernetes cluster. The system facilitates bi-directional messaging between an isolated hardware endpoint (ESP8266) and web clients via an asynchronous WebSocket server.

From a security architecture standpoint, the IoT endpoint operates on a dedicated, isolated VLAN (`samba-iot`). This segmentation prevents unauthorized lateral movement within the HomeLab network. Communication with the Kubernetes control plane is strictly governed by targeted OpenWrt firewall rules, ensuring the IoT device remains segregated from the primary local area network (LAN).

## System Architecture

### 1. Cloud & Server Side (Kubernetes K3s / Python)
A lightweight container orchestration environment running on Kali Linux.
* **K3s Cluster:** Manages the deployment and lifecycle of the backend application.
* **WebSocket Server:** An asynchronous Python application (using `websockets` and `asyncio`) running inside a Docker container. It handles client handshakes, session state management, and message broadcasting.
* **NodePort Service:** Exposes the internal container port (8765) to the host network on port 30000, acting as the ingress gateway for external traffic.

### 2. Network Routing (OpenWrt / Firewall)
The network backbone ensuring strict isolation and secure routing.
* **VLAN Segmentation:** IoT devices and the K8s server reside in separate subnets.
* **Traffic Rules:** Implements a specific firewall rule allowing only TCP traffic from the IoT zone to the LAN zone, exclusively targeting the K8s NodePort (30000).

### 3. Client Side (Wemos D1 Mini ESP8266 / C++)
The hardware execution unit written in C++ (Arduino core).
* **WebSocket Client:** Maintains a persistent, low-latency connection with the K8s cluster, implementing auto-reconnect logic.
* **JSON Parsing:** Uses `ArduinoJson` to serialize and deserialize chat payloads.
* **Real-time OLED Dashboard:** Uses an I2C SSD1306 screen to display live network status, active server connection, and incoming broadcast messages.
* **Hardware Triggering:** Drives an LED notification system upon receiving new payloads.

## Tech Stack & Hardware
* **Software:** Python 3.9, C++, HTML/JS.
* **DevOps & Cloud:** Kubernetes (K3s), Docker, containerd, YAML.
* **Networking:** WebSockets, VLAN Segmentation, OpenWrt Firewall, TCP/IP.
* **Hardware:** Wemos D1 Mini (ESP8266), SSD1306 OLED Display (I2C).

---

## Wersja Polska

## O Projekcie
Projekt autorskiego, rozproszonego systemu komunikacji czasu rzeczywistego dla środowiska HomeLab. Łączy on świat mikrokontrolerów (IoT) z nowoczesną infrastrukturą chmurową wdrożoną w klastrze Kubernetes. System umożliwia dwukierunkową wymianę wiadomości między sprzętowym punktem końcowym (ESP8266) a klientami webowymi za pomocą asynchronicznego serwera WebSocket.

Z perspektywy bezpieczeństwa, urządzenie IoT pracuje w izolowanej podsieci VLAN (`samba-iot`). Segmentacja ta zapobiega potencjalnym atakom i ruchom poprzecznym (lateral movement) w sieci domowej. Komunikacja z serwerem K8s jest ściśle kontrolowana przez dedykowane reguły zapory sieciowej OpenWrt, odcinając segment IoT od głównej infrastruktury LAN.

## Architektura Systemu

### 1. Strona Serwera i Chmury (Kubernetes K3s / Python)
Lekkie środowisko orkiestracji kontenerów działające na systemie Kali Linux.
* **Klaster K3s:** Zarządza wdrożeniem i cyklem życia aplikacji backendowej.
* **Serwer WebSocket:** Asynchroniczna aplikacja w Pythonie (korzystająca z `websockets` i `asyncio`) uruchomiona w kontenerze Docker. Zarządza sesjami klientów i rozgłaszaniem (broadcasting) wiadomości.
* **Usługa NodePort:** Wystawia wewnętrzny port kontenera (8765) na zewnątrz hosta (port 30000), pełniąc rolę bramy wejściowej dla ruchu sieciowego.

### 2. Sieć i Routing (OpenWrt / Firewall)
Szkielet sieciowy zapewniający ścisłą izolację i bezpieczny routing.
* **Segmentacja VLAN:** Urządzenia IoT oraz serwer K8s znajdują się w osobnych podsieciach.
* **Reguły zapory (Traffic Rules):** Implementacja celowanej reguły firewalla zezwalającej wyłącznie na ruch TCP ze strefy IoT do strefy LAN, ukierunkowanej dokładnie na port usługi K8s (30000).

### 3. Strona Klienta (Wemos D1 Mini ESP8266 / C++)
Jednostka sprzętowa zaprogramowana w C++ (Arduino core).
* **Klient WebSocket:** Utrzymuje stałe połączenie z klastrem K8s o niskim opóźnieniu, realizując logikę automatycznego wznawiania połączeń (auto-reconnect).
* **Parsowanie JSON:** Wykorzystuje bibliotekę `ArduinoJson` do serializacji i deserializacji pakietów z czatu.
* **Panel OLED:** Wyświetla na żywo za pomocą magistrali I2C (ekran SSD1306) status sieci, stan połączenia z serwerem oraz przychodzące wiadomości.
* **Powiadomienia Sprzętowe:** Steruje diodą LED sygnalizującą nadejście nowych danych.

## Technologie i Sprzęt
* **Oprogramowanie:** Python 3.9, C++, HTML/JS.
* **DevOps i Chmura:** Kubernetes (K3s), Docker, containerd, YAML.
* **Sieci:** WebSockets, Segmentacja VLAN, OpenWrt Firewall, TCP/IP.
* **Sprzęt:** Wemos D1 Mini (ESP8266), wyświetlacz OLED SSD1306 (I2C).

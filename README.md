# Kubernetes IoT WebSocket Bridge

A real-time communication system bridging a web browser and an ESP8266 microcontroller, running inside a local Kubernetes cluster. Built to explore cross-VLAN routing and container orchestration in a HomeLab environment.

## The Challenge: Network Isolation and Security

The core of this project focused on networking architecture and security. IoT devices are managed with the following constraints:
1. VLAN Segmentation: The Wemos D1 Mini operates in a dedicated, isolated VLAN (samba-iot) on a ZTE MF286D router running OpenWrt.
2. Firewall Policy: The firewall blocks all traffic from the IoT zone to the LAN by default.
3. Targeted Routing: Specific firewall traffic rules were configured to permit only TCP packets targeting port 30000 (NodePort) on the Kali Linux node where the K3s cluster resides.

## System Components

### Kubernetes (K3s) and Docker
* Backend: Python-based server using websockets and asyncio for handling concurrent connections.
* Deployment: YAML manifests manage the pod lifecycle and expose the application via NodePort 30000.
* Image Management: Built with Docker, then manually imported into the containerd runtime of the K3s cluster.

### Hardware (Wemos D1 Mini)
* OLED Display: I2C-connected SSD1306 screen for real-time network telemetry and message preview.
* JSON Processing: Implementation of ArduinoJson for structured data exchange.
* Resilience: Auto-reconnect logic to ensure session recovery after server restarts or network timeouts.

### Frontend
* Vanilla JS implementation to maintain minimal latency and avoid unnecessary framework overhead.

## Project Structure
```text
.
├── k8s-mesh-sentinel
│   ├── client/       # Web client (HTML/JS)
│   ├── firmware/     # C++ code for ESP8266
│   ├── k8s/          # Kubernetes YAML manifests
│   └── server/       # Python backend and Dockerfile

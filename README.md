Opis Projektu (Polish)

System komunikacji w czasie rzeczywistym integrujący rozproszoną infrastrukturę sieciową z urządzeniami IoT. Sercem projektu jest serwer WebSocket obsługujący dwukierunkową wymianę danych, asynchroniczne wiadomości oraz zarządzanie sesjami użytkowników.

Aplikacja została skonteneryzowana i wdrożona w klastrze Kubernetes (K3s) na systemie Linux, co zapewnia wysoką dostępność i skalowalność. Komunikacja odbywa się wewnątrz bezpiecznej sieci mesh Tailscale, łącząc laptopa (węzeł kontrolny), PC oraz mikrokontroler Wemos D1 Mini (klient fizyczny).

Kluczowe cechy:

    Orkiestracja Kubernetes: Zarządzanie cyklem życia kontenera serwera i automatyzacja wdrożenia.

    Real-time IoT: Odbiór powiadomień przez Wemos D1 Mini i renderowanie treści na wyświetlaczu OLED.

    Niezależność platformowa: Integracja systemów Linux, Windows oraz mikrokontrolerów w jednej architekturze.

Project Description (English)

A real-time communication system integrating distributed network infrastructure with IoT devices. The core of the project is a WebSocket server supporting full-duplex data exchange, asynchronous messaging, and user session management.

The application is containerized and deployed within a Kubernetes (K3s) cluster on Linux, ensuring high availability and scalability. Communication flows through a secure Tailscale mesh network, linking a laptop (control node), a desktop PC, and a Wemos D1 Mini microcontroller (physical client).

Key Features:

    Kubernetes Orchestration: Managing server container lifecycle and deployment automation.

    Real-time IoT: Wemos D1 Mini receiving and rendering notifications on an OLED display in real-time.

    Platform Independence: Seamless integration between Linux, Windows, and MCU-based systems.

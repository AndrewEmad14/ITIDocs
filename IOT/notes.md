# SpimeSense
an IoT solution provider established in 2013

more than 11 years of IoT experience

# Hot jobs
	•	Big Data Specialists
	•	FinTech Engineers
	•	AI and Machine Learning Specialists
	•	Software Application Developer
	•	Security Management Specialists
	•	Data Warehousing Specialists
	•	Autonomous and Electric Vehicle Specialists
	•	UI and UX Designers
	•	Light Truck or Delivery Services Drivers
	•	Internet of Things Specialist
	•	Data Analysts and Scientists
	•	Environmental Engineers
	•	Information Security Analysts
	•	DevOps Engineer
	•	Renewable Energy Engineers

# IoT fields of implementation

  1.	Smart City — 23%
	2.	Connected Industry — 17%
	3.	Connected Building — 12%
	4.	Connected Car — 11%
	5.	Smart Energy — 10%
	6.	Other — 8%
	7.	Connected Health — 6%
	8.	Smart Supply Chain — 5%
	9.	Smart Agriculture — 4%
	10.	Smart Retail — 4%

# main categories
  home
  transport
  health
  buildings
  cities

# IoT value chain
	1.	Sensors / Devices
	2.	Wireless Sensor Networks
	3.	Gateways
	4.	Carrier Networks
	5.	Application Enablement Platforms
	6.	Analytics platforms
  7. device and gateway management
  8.End to end system integrators

# Master of things platform

1. Platform & Application Layer
	•	All SW applications managed by & running on top of MoT platform (Operating System).
	•	All SW applications gain controlled access to physical HW devices in the city/campus (computer).

2. Development Environment
	•	MoT platform (Operating System) provides a visual IDE to faster and standardize applications development for both web & Mobile.

3. Device Integration & Security
	•	All IoT devices are connected once and used in many applications according to device authentication, data encryption, etc.

4. User Access & Roles
	•	SW Developers, Help desk and End-users access each of the applications according their users’ groups access rights.


# Multi Tenancy
  MasterOfThings is a multi-tenant horizontal platform and that enables our customers to scale to manage multiple
corporate customers or facilities with each corporate/facility having its own users, applications, devices and sub-
systems managed and operated from a dedicated tenant by a tenant administrator.
Deployment Super Admin creates tenants where each tenant has its own administrator(s).
Tenant Admins manages everything in the domain/tenant including users’ groups and their access rights, sensors
permissions, application data tables access right, Events/SOPs (Standard Operating Procedures)

# the trade offs in connectivity

graph TD
    A([⚡ Power]) --- B([📶 Throughput])
    A --- C([📡 Distance])
    B --- C

# Connectivity 

## Network Range Layers

The slide shows 4 range layers at the bottom right:

| Network | Standard | Coverage | Example |
|---|---|---|---|
| **PAN** - Personal Area Network | 802.15 | ~10 meters | Bluetooth, Zigbee |
| **LAN** - Local Area Network | 802.11 | ~100 meters | WiFi |
| **MAN** - Metropolitan Area Network | 802.16 | ~50 km | WiMAX |
| **WAN** - Wide Area Network | 802.20 | Countrywide | 4G/5G, LoRa |

---

## 📡 TECHNOLOGY 1: LPWAN (Low Power Wide Area Networks)

These are designed for IoT — **long range, low power, low data.**

---

### 🔶 LoRa / LoRaWAN
| Attribute | Detail |
|---|---|
| **Frequency** | 868 MHz (Europe), 915 MHz (US), 433 MHz (Asia) |
| **Range** | 2–15 km urban, up to 45 km rural |
| **Data Rate** | Very low — 0.3 to 50 kbps |
| **Power** | Extremely low — battery can last 10+ years |

✅ **Advantages:**
- Extremely long battery life
- Great for remote areas
- Free to use (unlicensed spectrum)
- Low cost hardware

❌ **Disadvantages:**
- Very low data throughput
- Not suitable for video or voice
- Limited message frequency

🎯 **Use Cases:**
- Smart agriculture (soil sensors)
- Smart metering (water, electricity)
- Asset tracking in remote areas
- Forest fire detection

---

### 🔶 Sigfox (now Unabiz)
| Attribute | Detail |
|---|---|
| **Frequency** | 868 MHz (Europe), 902 MHz (US) |
| **Range** | Up to 50 km rural, 10 km urban |
| **Data Rate** | Ultra low — 100 bps |
| **Power** | Extremely low |

✅ **Advantages:**
- Longest range of all LPWAN
- Cheapest per-device cost
- Very simple integration

❌ **Disadvantages:**
- Extremely limited data (only 140 messages/day, 12 bytes each)
- Proprietary network — dependent on Sigfox coverage
- Company had financial difficulties (acquired by Unabiz)

🎯 **Use Cases:**
- Smart parking sensors
- Waste bin monitoring
- Supply chain tracking
- Simple environmental sensors

---

### 🔶 NB-IoT (Narrowband IoT)
| Attribute | Detail |
|---|---|
| **Frequency** | Licensed cellular bands (700 MHz – 2.1 GHz) |
| **Range** | 10–15 km |
| **Data Rate** | 20–250 kbps |
| **Power** | Very low |

✅ **Advantages:**
- Uses existing cellular infrastructure
- Better indoor penetration than LoRa
- Carrier-grade security and reliability
- Supports many devices per cell

❌ **Disadvantages:**
- Requires SIM card and carrier subscription
- Higher cost than LoRa/Sigfox
- Not suitable for roaming easily

🎯 **Use Cases:**
- Smart city infrastructure
- Underground sensors (parking, pipes)
- Utility metering
- Healthcare wearables

---

### 🔶 Mioty
| Attribute | Detail |
|---|---|
| **Frequency** | Sub-GHz (868/915 MHz) |
| **Range** | Up to 15 km |
| **Data Rate** | Low but more reliable than LoRa |
| **Power** | Very low |

✅ **Advantages:**
- More robust against interference than LoRa
- Better in dense urban environments
- Open standard (ETSI)

❌ **Disadvantages:**
- Newer technology, smaller ecosystem
- Less hardware availability

🎯 **Use Cases:**
- Industrial IoT monitoring
- Smart factories
- Dense urban deployments

---

### 🔶 5G mMTC (Massive Machine Type Communications)
| Attribute | Detail |
|---|---|
| **Frequency** | Sub-6 GHz and mmWave |
| **Range** | Varies — km scale |
| **Data Rate** | Flexible |
| **Power** | Optimized for IoT devices |

✅ **Advantages:**
- Supports up to **1 million devices per km²**
- Part of 5G ecosystem
- Future-proof

❌ **Disadvantages:**
- Still being deployed globally
- Infrastructure cost is high

🎯 **Use Cases:**
- Smart cities with massive sensor networks
- Industrial automation
- Connected vehicles

---

## 📶 TECHNOLOGY 2: Short Range / PAN Technologies

---

### 🔷 Bluetooth / BLE
| Attribute | Detail |
|---|---|
| **Frequency** | 2.4 GHz |
| **Range** | 10–100 meters |
| **Data Rate** | 1–3 Mbps (Classic), 125 kbps–2 Mbps (BLE) |
| **Power** | Very low (BLE) |

✅ **Advantages:**
- Universal — in every smartphone
- Very mature technology
- BLE is extremely energy efficient

❌ **Disadvantages:**
- Short range
- Interference with WiFi (same 2.4 GHz band)
- Mesh networking is complex

🎯 **Use Cases:**
- Fitness trackers, smartwatches
- Smart home devices
- Medical devices
- Beacon/location tracking in retail

---

### 🔷 Zigbee
| Attribute | Detail |
|---|---|
| **Frequency** | 2.4 GHz (global), 868/915 MHz |
| **Range** | 10–100 meters (mesh extends this) |
| **Data Rate** | 250 kbps |
| **Power** | Very low |

✅ **Advantages:**
- Excellent mesh networking — devices relay signals
- Low power consumption
- Very reliable for home automation
-Unlicensed
❌ **Disadvantages:**
- Not compatible with WiFi natively
- Needs a hub/coordinator
- Competes with other 2.4 GHz devices

🎯 **Use Cases:**
- Smart lighting (Philips Hue)
- Smart home sensors
- Building automation
- Industrial control systems

---

### 🔷 Z-Wave
| Attribute | Detail |
|---|---|
| **Frequency** | 800–900 MHz (sub-GHz, varies by region) |
| **Range** | 30–100 meters |
| **Data Rate** | 9.6–100 kbps |
| **Power** | Low |

✅ **Advantages:**
- Dedicated frequency = no WiFi interference
- Great mesh networking
- Very reliable for home automation

❌ **Disadvantages:**
- Proprietary standard (Silicon Labs)
- More expensive hardware
- Max 232 devices per network

🎯 **Use Cases:**
- Smart door locks
- Home security systems
- Smart thermostats
- Lighting control

---

### 🔷 NFC (Near Field Communication)
| Attribute | Detail |
|---|---|
| **Frequency** | 13.56 MHz |
| **Range** | Up to 20 cm |
| **Data Rate** | 106–424 kbps |
| **Power** | Passive (no battery needed on tag) |

✅ **Advantages:**
- No power needed on the tag side
- Extremely secure (must be physically close)
- Instant connection

❌ **Disadvantages:**
- Very short range — must almost touch
- Low data rate

🎯 **Use Cases:**
- Contactless payments (Apple Pay)
- Access cards
- Product authentication
- Medical device pairing

---

### 🔷 UWB (Ultra-Wideband)
| Attribute | Detail |
|---|---|
| **Frequency** | 3.1–10.6 GHz |
| **Range** | 10–100 meters |
| **Data Rate** | Up to 27 Mbps |
| **Power** | Low |

✅ **Advantages:**
- **Centimeter-level precision** location tracking
- Very secure
- Minimal interference

❌ **Disadvantages:**
- Short range
- Still emerging ecosystem

🎯 **Use Cases:**
- Precise indoor positioning
- Apple AirTags
- Automotive (car key)
- Warehouse asset tracking

---

## 📱 TECHNOLOGY 3: WiFi

### 🔷 WiFi (802.11)
| Attribute | Detail |
|---|---|
| **Frequency** | 2.4 GHz, 5 GHz, 6 GHz (WiFi 6E) |
| **Range** | 50–100 meters indoors |
| **Data Rate** | Up to 9.6 Gbps (WiFi 6) |
| **Power** | Medium–High |

✅ **Advantages:**
- Very high data rate
- Universal infrastructure already exists
- Good for video streaming devices

❌ **Disadvantages:**
- High power consumption — bad for battery IoT
- Congested spectrum
- Limited range

🎯 **Use Cases:**
- Smart TVs, cameras
- Home routers
- IoT devices near power sources
- Industrial WiFi sensors

---

## 🌐 TECHNOLOGY 4: Cellular (2G → 5G)

### Evolution of Cellular for IoT:

| Generation | Speed | IoT Relevance |
|---|---|---|
| **2G/GSM/GPRS** | ~50 kbps | Legacy IoT, SMS-based devices |
| **3G/UMTS** | ~2 Mbps | Basic data IoT |
| **4G/LTE** | ~100 Mbps | Connected vehicles, cameras |
| **LTE Advanced** | ~300 Mbps | High-bandwidth IoT |
| **5G NTN** | ~10 Gbps | Next-gen everything |

### 🔶 5G NTN (Non-Terrestrial Network)
| Attribute | Detail |
|---|---|
| **Coverage** | Global — via satellites |
| **Range** | Unlimited (space-based) |
| **Latency** | LEO: ~20ms, GEO: ~600ms |

✅ **Advantages:**
- Covers oceans, deserts, polar regions
- No terrestrial infrastructure needed
- Connects truly remote devices

❌ **Disadvantages:**
- Expensive
- Higher latency (especially GEO satellites)
- Specialized hardware needed

🎯 **Use Cases:**
- Maritime tracking
- Remote oil & gas monitoring
- Aviation connectivity
- Global logistics tracking

---

## 🔌 TECHNOLOGY 5: Wired Technologies

### Powerline / Ethernet / Printed
| Type | Description | Use Case |
|---|---|---|
| **Ethernet** | Wired LAN, up to 10 Gbps | Industrial, fixed installations |
| **Powerline** | Data over electrical wiring | Smart grid, home networking |
| **Printed** | Printed electronics/antennas | Disposable IoT tags, packaging |

---

## 🔵 Protocol Layer (Bottom of Slide)
These are the **software protocols** that run on top of all these networks:

| Protocol | Purpose |
|---|---|
| **MQTT** | Lightweight messaging for IoT |
| **CoAP** | Web protocol for constrained devices |
| **HTTP/REST API** | Standard web communication |
| **DTLS** | Security for IoT |
| **IPv6** | Addressing for billions of IoT devices |
| **XMPP** | Real-time messaging |

---

## 🎯 Key Takeaway from the Slide

> The IoT connectivity landscape is **extremely fragmented** — no single technology wins everywhere. The right choice depends on:
> - **Range needed** (cm vs global)
> - **Data volume** (bytes vs gigabytes)
> - **Power budget** (battery vs plugged in)
> - **Cost constraints**
> - **Deployment environment** (indoor vs remote)

This is exactly why platforms like **SpimeSenseLabs** exist — to manage devices across **all these different connectivity types** from a single platform.


# Embedded Esims
  mbedded SIMs (eSIMs) or embedded Universal Integrated Circuit Cards (eUICCs) are physical SIMs that are
soldered into the device and enable storage and remote management of multiple network operator profiles
(remote SIM provisioning). The form factor of eSIM is known as MFF2.
The integrated SIMs (iSIMs) moves the SIM from a separate chip into a secure enclave alongside the application
processor and cellular radio on a purpose-built system on a chip (SoC).

# Master of things IoT vision

❖ A complete End-to-End approach from sensors to end user
applications.
❖ Sensor's installation & connectivity becomes Plug & Play.
❖ Programing & application development becomes drag & drop.
❖ Launch new applications and manage its performance.
❖ Group users and manage their access rights towards the devices
and towards the applications.

# MOT core modules

1. User Definition & Administration (top)
Manages access control for two audiences:

Application developers who build on the platform
End users who consume the applications
It handles authentication, roles, and rights management across the system.


2. Monitoring, Enrichment & Orchestration (left)
The operational backbone of the platform. It:

Monitors live sensor data streams
Enriches raw data (adding context, filtering, transforming)
Orchestrates actions — triggering responses or automations based on sensor events or rules


3. Sensors Definition (bottom)
The data ingestion layer. It allows you to define:

Sensors and their associated drivers
Sensor readings and their formats
Data types for readings (numeric, boolean, string, etc.)
Additional metadata and configuration


4. Visual Application Development Environment (right)
A no-code/low-code UI builder for:

Creating data input pages (forms, controls)
Building visualization dashboards (charts, maps, tables)
Presenting IoT data to end users in meaningful ways

Here's the organized breakdown:

---

# IoT Ecosystem — Companies & Services by Category



## 1. Sensors / Devices

**Embedded Software**
- Witekio Emb SW

**Hardware Vendors**
- Libelium, Eurotech, Telit, Yanzi

**Operating Systems / Firmware**
- Contiki-OS, FreeRTOS, Riot-OS, Zephyr, TinyOS, OpenWrt

**Dev Boards & Kits**
- Raspberry Pi, Arduino, Tilet, Intel Edison, MasterOfThings IoT Kit

---

## 2. Wireless Sensor Networks

**Short Range**
- RFID, NFC, Bluetooth, BLE, Bluetooth Smart

**Long Range / LPWAN**
- LoRa, LoRaWan, MioTy, MyThings Weightless, Z-wav, ZigBee, Xbee, Ingenu, Platinus M2C, RIIM2

**Alliances & Standards**
- MulteFire 1.1, Wi-Sun, Thread, 6lowpan, IQRF

---

## 3. Gateways

**Hardware Vendors**
- Intel, Cisco, Dell, KerLink, TEKTELIC, Minew

**Integration Middleware**
- FaltCom, Alleantia

**Network Servers**
- TTN, Loriot, ChirpStack, LoRaServer, MyThings

---

## 4. Carrier Networks

**Sigfox**
- SigFox Unabiz

**LEO Satellites**
- Lacuna provides lol LoRaWan satellite connectivity.,
FossaSat 1u,
Angels,
Hello,
Kineis 16U, 
Swarm

**MVNOs / Connectivity Providers**
- KORE, OnoMondo, Velos, ARKESSA (Wireless Logic), Emnify, THALES Adaptive Connect, eseye

**Connectivity Management Platforms**
- Jasper CC (Cisco), Ericsson DCP/Accelerator (Aries), Vodafone GDSP, Verizon ThingSpace, Nokia WING, IoTM (Israel)

**Cellular Standards**
- GPRS, 3G, 4G LTE (LTE-M, NB LTE, LTE Lite, Cellular IoT, MulteFire LTE), 5G Massive IoT (mMTC)

---

## 5. Application Enablement Platforms (AEP)

**Tier 1 — Major Platforms**
- MasterOfThings (MoT)
- VoT / B-Scada
- PTC ThingWorx IIoT
- Xively (Google GCP)
- Cisco Kinetic

**Tier 2 — Open & Mid-Market**
- ThingsBoard, FiWare, CityOS, Gimalto

**Tier 3 — Enterprise / Industrial**
- Siemens Mindsphere
- Schneider WonderWare
- Cumulocity IIoT
- GE Predix IIoT

**ERP-Integrated**
- PlatOne (SAP Leonardo)

**Telecom-Backed**
- Carriots (Altair)

---

## 6. Analytics Platforms

**Cloud & Big Data**
- Splunk, Grok, Hadoop

**AI / ML Focused**
- Watson IoT (IBM), OneMind

**Other**
- OverOTT

---
## 🔵 Layer 7 — Device & Gateway Remote Management
- Balena
- Kaa
- Bosch IoT Suite
- Nokia IMPACT

---
## 🔵 Layer 8 — End-to-End System Integrators
*(Full-stack integrators covering the entire IoT value chain)*

---



# MQTT
MQTT (Message Queuing Telemetry Transport) is a lightweight, open-source publish-subscribe network protocol designed for machine-to-machine (M2M) and Internet of Things (IoT) communication. It enables efficient, low-bandwidth, and low-power messaging between devices, making it ideal for unstable networks or constrained environments. It is widely used for real-time monitoring and automation across various industries, including smart homes, manufacturing, and automotive

# Roaming Service in IoT / Telecom

## Basic Definition
Roaming is the ability of a connected device to **automatically switch and use a network other than its home network** when it moves outside the home network's coverage area — without losing connectivity.

---

## How It Works
1. Device leaves its **home network** coverage
2. It detects a **visited/foreign network**
3. A **roaming agreement** between the two operators allows the device to connect
4. The visited network authenticates the device through the home network
5. Data is tunneled back, often billed at roaming rates

---

## Why It Matters for IoT
IoT devices are often deployed **globally or in remote areas**, so roaming is critical for:
- **Asset tracking** (vehicles, shipping containers crossing borders)
- **Fleet management** across countries
- **Smart meters** in areas with weak home-network coverage
- **Wearables** traveling internationally

---

## Types of IoT Roaming

| Type | Description |
|------|-------------|
| **Standard Roaming** | Device uses a visited network under a bilateral agreement |
| **Permanent Roaming** | Device always operates on a foreign network (common in IoT) |
| **Multi-IMSI** | SIM holds multiple operator identities to switch networks |
| **eUICC / eSIM** | SIM profile is updated remotely to switch operators |

---

## In the Context of the Diagram
**Nokia WING** (Worldwide IoT Network Grid) mentioned in the Carrier Networks layer is specifically a **managed IoT roaming and connectivity service** — it enables IoT devices to roam across multiple carrier networks globally under a single managed platform.

---

## Key Takeaway
Roaming ensures **seamless, uninterrupted IoT connectivity** regardless of geographic boundaries, which is essential for globally deployed IoT solutions.

# COAP
CoAP uses a request/response model. It mirrors HTTP's client-server architecture but strips the overhead that makes HTTP unsuitable for constrained devices. CoAP runs over UDP by default, supports multicast discovery, and operates peer-to-peer without centralized infrastructure. Resources are addressed using URIs. Clients request data. Servers respond.

# IoT Device OS Categories
1. 🔴 No OS (Bare Metal)
Many simple IoT devices run no OS at all:

Code runs directly on the hardware
Used for ultra-constrained devices
Examples: simple sensors, basic actuators, Arduino (typically bare metal)
When resources are too limited even for an RTOS

2. 🟡 RTOS
Used when timing and multitasking are needed but resources are still limited:

FreeRTOS, Zephyr, Contiki-OS, Riot-OS, TinyOS
Used in mid-range microcontrollers
Provides task scheduling with real-time guarantees

3. 🟢 General Purpose OS (GPOS)
More powerful IoT devices run full operating systems:

Linux, OpenWrt, Windows IoT
Used in gateways, edge devices
Example: Raspberry Pi runs Linux, not an RTOS
# SpimeSense IoT Study Guide

---

## Table of Contents

1. [Company Overview](#1-company-overview)
2. [Hot Jobs in IoT](#2-hot-jobs-in-iot)
3. [IoT Fields of Implementation](#3-iot-fields-of-implementation)
4. [Main IoT Categories](#4-main-iot-categories)
5. [IoT Value Chain](#5-iot-value-chain)
6. [Master of Things (MoT) Platform](#6-master-of-things-mot-platform)
   - 6.1 [Platform Overview](#61-platform-overview)
   - 6.2 [Multi-Tenancy](#62-multi-tenancy)
   - 6.3 [IoT Vision](#63-iot-vision)
   - 6.4 [Core Modules](#64-core-modules)
7. [IoT Connectivity](#7-iot-connectivity)
   - 7.1 [Connectivity Trade-offs](#71-connectivity-trade-offs)
   - 7.2 [Network Range Layers](#72-network-range-layers)
   - 7.3 [LPWAN Technologies](#73-lpwan-technologies)
     - LoRa / LoRaWAN
     - Sigfox (Unabiz)
     - NB-IoT
     - Mioty
     - 5G mMTC
   - 7.4 [Short Range / PAN Technologies](#74-short-range--pan-technologies)
     - Bluetooth / BLE
     - Zigbee
     - Z-Wave
     - NFC
     - UWB
   - 7.5 [WiFi](#75-wifi)
   - 7.6 [Cellular (2G → 5G)](#76-cellular-2g--5g)
   - 7.7 [Wired Technologies](#77-wired-technologies)
8. [IoT Protocols](#8-iot-protocols)
   - 8.1 [MQTT](#81-mqtt)
   - 8.2 [CoAP](#82-coap)
   - 8.3 [Other Protocols](#83-other-protocols)
9. [Embedded SIMs (eSIM / iSIM)](#9-embedded-sims-esim--isim)
10. [Roaming in IoT](#10-roaming-in-iot)
11. [IoT Device Operating Systems](#11-iot-device-operating-systems)
12. [IoT Ecosystem — Companies by Layer](#12-iot-ecosystem--companies-by-layer)
13. [IoT Value Chain — Deep Dive (Exam Notes)](#13-iot-value-chain--deep-dive-exam-notes)
    - 13.1 [The 8 Components — Overview](#131-the-8-components--overview)
    - 13.2 [Component #1 — Sensors / Devices](#132-component-1--sensors--devices)
    - 13.3 [Component #2 — Wireless Sensor Networks](#133-component-2--wireless-sensor-networks)
    - 13.4 [Component #3 — Gateways & Network Servers](#134-component-3--gateways--network-servers)
    - 13.5 [Component #4 — Carrier Networks](#135-component-4--carrier-networks)
    - 13.6 [Component #5 — Application Enablement Platforms (AEP)](#136-component-5--application-enablement-platforms-aep)
    - 13.7 [Component #6 — Analytics Platforms](#137-component-6--analytics-platforms)
    - 13.8 [Component #7 — Device & Gateway Remote Management](#138-component-7--device--gateway-remote-management)
    - 13.9 [Component #8 — End-to-End System Integrators](#139-component-8--end-to-end-system-integrators)
14. [Master Platform Classification Table](#14-master-platform-classification-table)
15. [SigFox — The Most Tested Topic](#15-sigfox--the-most-tested-topic)
16. [IoT Job Roles](#16-iot-job-roles)
17. [Exam Traps — Last-Minute Reference](#17-exam-traps--last-minute-reference)
    - 17.1 [Platform Classification Traps](#171-platform-classification-traps)
    - 17.2 [Wireless Technology Traps](#172-wireless-technology-traps)
    - 17.3 [Architecture & Role Traps](#173-architecture--role-traps)

---

## 1. Company Overview

**SpimeSense** is an IoT solution provider established in **2013** with more than **11 years of IoT experience**.

---

## 2. Hot Jobs in IoT

- Big Data Specialists
- FinTech Engineers
- AI and Machine Learning Specialists
- Software Application Developer
- Security Management Specialists
- Data Warehousing Specialists
- Autonomous and Electric Vehicle Specialists
- UI and UX Designers
- Light Truck or Delivery Services Drivers
- Internet of Things Specialist
- Data Analysts and Scientists
- Environmental Engineers
- Information Security Analysts
- DevOps Engineer
- Renewable Energy Engineers

---

## 3. IoT Fields of Implementation

| Rank | Field | Share |
|------|-------|-------|
| 1 | Smart City | 23% |
| 2 | Connected Industry | 17% |
| 3 | Connected Building | 12% |
| 4 | Connected Car | 11% |
| 5 | Smart Energy | 10% |
| 6 | Other | 8% |
| 7 | Connected Health | 6% |
| 8 | Smart Supply Chain | 5% |
| 9 | Smart Agriculture | 4% |
| 10 | Smart Retail | 4% |

---

## 4. Main IoT Categories

- Home
- Transport
- Health
- Buildings
- Cities

---

## 5. IoT Value Chain

1. Sensors / Devices
2. Wireless Sensor Networks
3. Gateways
4. Carrier Networks
5. Application Enablement Platforms
6. Analytics Platforms
7. Device and Gateway Management
8. End-to-End System Integrators

---

## 6. Master of Things (MoT) Platform

### 6.1 Platform Overview

| Layer | Description |
|-------|-------------|
| **Platform & Application Layer** | All SW applications managed by & running on top of MoT (the OS). Applications gain controlled access to physical HW devices. |
| **Development Environment** | Visual IDE for faster and standardized web & mobile application development. |
| **Device Integration & Security** | IoT devices connected once, used across many applications with authentication & data encryption. |
| **User Access & Roles** | SW Developers, Help Desk, and End-users access applications according to user group access rights. |

### 6.2 Multi-Tenancy

MasterOfThings is a **multi-tenant horizontal platform** enabling customers to manage multiple corporate customers or facilities. Each tenant has its own:
- Users & user groups
- Applications
- Devices & sub-systems
- Tenant administrator

**Hierarchy:**
- **Deployment Super Admin** → creates tenants
- **Tenant Admins** → manage users, access rights, sensors, application data, Events/SOPs

### 6.3 IoT Vision

- Complete End-to-End approach from sensors to end-user applications
- Sensor installation & connectivity: **Plug & Play**
- Programming & application development: **Drag & Drop**
- Launch new applications and manage performance
- Group users and manage their access rights

### 6.4 Core Modules

| Module | Role |
|--------|------|
| **User Definition & Administration** | Manages authentication, roles, and access rights for developers and end users |
| **Monitoring, Enrichment & Orchestration** | Monitors live sensor data, enriches raw data, orchestrates automations |
| **Sensors Definition** | Defines sensors, drivers, readings, formats, and metadata |
| **Visual Application Development Environment** | No-code/low-code UI builder for dashboards and data visualization |

---

## 7. IoT Connectivity

### 7.1 Connectivity Trade-offs

The three core trade-offs in IoT connectivity:

```
⚡ Power  ←→  📶 Throughput  ←→  📡 Distance
```

Optimizing one often compromises the others.

### 7.2 Network Range Layers

| Network | Standard | Coverage | Example |
|---------|----------|----------|---------|
| **PAN** — Personal Area Network | 802.15 | ~10 meters | Bluetooth, Zigbee |
| **LAN** — Local Area Network | 802.11 | ~100 meters | WiFi |
| **MAN** — Metropolitan Area Network | 802.16 | ~50 km | WiMAX |
| **WAN** — Wide Area Network | 802.20 | Countrywide | 4G/5G, LoRa |

---

### 7.3 LPWAN Technologies

> Long range · Low power · Low data — designed for IoT

#### LoRa / LoRaWAN

| Attribute | Detail |
|-----------|--------|
| Frequency | 868 MHz (EU), 915 MHz (US), 433 MHz (Asia) |
| Range | 2–15 km urban; up to 45 km rural |
| Data Rate | 0.3–50 kbps |
| Power | Extremely low — 10+ year battery life |

**✅ Advantages:** Long battery life · Remote area coverage · Unlicensed spectrum · Low cost  
**❌ Disadvantages:** Very low throughput · Not for video/voice · Limited message frequency  
**🎯 Use Cases:** Smart agriculture · Smart metering · Asset tracking · Forest fire detection

---

#### Sigfox (now Unabiz)

| Attribute | Detail |
|-----------|--------|
| Frequency | 868 MHz (EU), 902 MHz (US) |
| Range | Up to 50 km rural, 10 km urban |
| Data Rate | 100 bps |
| Power | Extremely low |

**✅ Advantages:** Longest LPWAN range · Cheapest per-device cost · Simple integration  
**❌ Disadvantages:** Max 140 messages/day (12 bytes each) · Proprietary network · Financial instability  
**🎯 Use Cases:** Smart parking · Waste bin monitoring · Supply chain · Environmental sensors

---

#### NB-IoT (Narrowband IoT)

| Attribute | Detail |
|-----------|--------|
| Frequency | Licensed cellular bands (700 MHz – 2.1 GHz) |
| Range | 10–15 km |
| Data Rate | 20–250 kbps |
| Power | Very low |

**✅ Advantages:** Uses existing cellular infrastructure · Better indoor penetration · Carrier-grade security  
**❌ Disadvantages:** Requires SIM + carrier subscription · Higher cost · Limited roaming  
**🎯 Use Cases:** Smart city infrastructure · Underground sensors · Utility metering · Healthcare wearables

---

#### Mioty

| Attribute | Detail |
|-----------|--------|
| Frequency | Sub-GHz (868/915 MHz) |
| Range | Up to 15 km |
| Data Rate | Low but more reliable than LoRa |
| Power | Very low |

**✅ Advantages:** More robust against interference · Better in dense urban areas · Open ETSI standard  
**❌ Disadvantages:** Newer ecosystem · Less hardware availability  
**🎯 Use Cases:** Industrial IoT · Smart factories · Dense urban deployments

---

#### 5G mMTC (Massive Machine Type Communications)

| Attribute | Detail |
|-----------|--------|
| Frequency | Sub-6 GHz and mmWave |
| Range | km scale |
| Capacity | Up to 1 million devices/km² |

**✅ Advantages:** Massive device density · Part of 5G ecosystem · Future-proof  
**❌ Disadvantages:** Still being deployed · High infrastructure cost  
**🎯 Use Cases:** Smart cities · Industrial automation · Connected vehicles

---

### 7.4 Short Range / PAN Technologies

#### Bluetooth / BLE

| Attribute | Detail |
|-----------|--------|
| Frequency | 2.4 GHz |
| Range | 10–100 meters |
| Data Rate | 1–3 Mbps (Classic), 125 kbps–2 Mbps (BLE) |
| Power | Very low (BLE) |

**✅ Advantages:** Universal in smartphones · Mature technology · BLE is very energy efficient  
**❌ Disadvantages:** Short range · 2.4 GHz interference with WiFi · Complex mesh networking  
**🎯 Use Cases:** Fitness trackers · Smart home · Medical devices · Retail beacons

---

#### Zigbee

| Attribute | Detail |
|-----------|--------|
| Frequency | 2.4 GHz (global), 868/915 MHz |
| Range | 10–100 m (mesh extends range) |
| Data Rate | 250 kbps |
| Power | Very low |

**✅ Advantages:** Excellent mesh networking · Low power · Reliable for home automation · Unlicensed  
**❌ Disadvantages:** Not natively WiFi-compatible · Needs hub · 2.4 GHz congestion  
**🎯 Use Cases:** Smart lighting (Philips Hue) · Smart home sensors · Building automation

---

#### Z-Wave

| Attribute | Detail |
|-----------|--------|
| Frequency | 800–900 MHz (sub-GHz) |
| Range | 30–100 meters |
| Data Rate | 9.6–100 kbps |
| Power | Low |

**✅ Advantages:** Dedicated frequency (no WiFi interference) · Great mesh networking · Very reliable  
**❌ Disadvantages:** Proprietary (Silicon Labs) · More expensive · Max 232 devices/network  
**🎯 Use Cases:** Smart door locks · Home security · Smart thermostats · Lighting control

---

#### NFC (Near Field Communication)

| Attribute | Detail |
|-----------|--------|
| Frequency | 13.56 MHz |
| Range | Up to 20 cm |
| Data Rate | 106–424 kbps |
| Power | Passive (no battery on tag) |

**✅ Advantages:** No power needed on tag · Extremely secure · Instant connection  
**❌ Disadvantages:** Very short range · Low data rate  
**🎯 Use Cases:** Contactless payments · Access cards · Product authentication · Medical device pairing

---

#### UWB (Ultra-Wideband)

| Attribute | Detail |
|-----------|--------|
| Frequency | 3.1–10.6 GHz |
| Range | 10–100 meters |
| Data Rate | Up to 27 Mbps |
| Power | Low |

**✅ Advantages:** Centimeter-level precision · Very secure · Minimal interference  
**❌ Disadvantages:** Short range · Emerging ecosystem  
**🎯 Use Cases:** Indoor positioning · Apple AirTags · Automotive (car keys) · Warehouse tracking

---

### 7.5 WiFi

| Attribute | Detail |
|-----------|--------|
| Frequency | 2.4 GHz, 5 GHz, 6 GHz (WiFi 6E) |
| Range | 50–100 meters indoors |
| Data Rate | Up to 9.6 Gbps (WiFi 6) |
| Power | Medium–High |

**✅ Advantages:** Very high data rate · Universal infrastructure · Good for streaming  
**❌ Disadvantages:** High power (bad for battery IoT) · Congested spectrum · Limited range  
**🎯 Use Cases:** Smart TVs & cameras · Home routers · Plugged-in IoT devices

---

### 7.6 Cellular (2G → 5G)

| Generation | Speed | IoT Relevance |
|------------|-------|---------------|
| 2G/GSM/GPRS | ~50 kbps | Legacy IoT, SMS-based devices |
| 3G/UMTS | ~2 Mbps | Basic data IoT |
| 4G/LTE | ~100 Mbps | Connected vehicles, cameras |
| LTE Advanced | ~300 Mbps | High-bandwidth IoT |
| 5G NTN | ~10 Gbps | Next-gen everything |

#### 5G NTN (Non-Terrestrial Network)

| Attribute | Detail |
|-----------|--------|
| Coverage | Global — via satellites |
| Latency | LEO: ~20ms · GEO: ~600ms |

**✅ Advantages:** Covers oceans, deserts, polar regions · No terrestrial infrastructure needed  
**❌ Disadvantages:** Expensive · Higher latency · Specialized hardware required  
**🎯 Use Cases:** Maritime tracking · Remote oil & gas · Aviation connectivity · Global logistics

---

### 7.7 Wired Technologies

| Type | Description | Use Case |
|------|-------------|----------|
| **Ethernet** | Wired LAN, up to 10 Gbps | Industrial, fixed installations |
| **Powerline** | Data over electrical wiring | Smart grid, home networking |
| **Printed** | Printed electronics/antennas | Disposable IoT tags, packaging |

---

## 8. IoT Protocols

### 8.1 MQTT

**MQTT** (Message Queuing Telemetry Transport) is a **lightweight, open-source publish-subscribe protocol** for M2M and IoT communication.

- Enables efficient, low-bandwidth, low-power messaging
- Ideal for unstable networks or constrained environments
- Widely used in smart homes, manufacturing, and automotive

### 8.2 CoAP

**CoAP** uses a **request/response model** mirroring HTTP's client-server architecture but strips overhead for constrained devices.

- Runs over **UDP** by default
- Supports multicast discovery
- Operates peer-to-peer (no centralized infrastructure)
- Resources addressed using URIs

### 8.3 Other Protocols

| Protocol | Purpose |
|----------|---------|
| **MQTT** | Lightweight messaging for IoT |
| **CoAP** | Web protocol for constrained devices |
| **HTTP/REST API** | Standard web communication |
| **DTLS** | Security for IoT |
| **IPv6** | Addressing for billions of IoT devices |
| **XMPP** | Real-time messaging |

---

## 9. Embedded SIMs (eSIM / iSIM)

| Type | Description |
|------|-------------|
| **eSIM / eUICC** | Physical SIM soldered into device; enables remote management of multiple operator profiles (MFF2 form factor) |
| **iSIM** | Moves SIM function into a secure enclave on the application processor SoC — fully integrated |

Both support **remote SIM provisioning** — switching operators without physical SIM replacement.

---

## 10. Roaming in IoT

Roaming allows a connected device to **automatically switch to a visited network** when outside home network coverage.

### How It Works
1. Device leaves home network coverage
2. Detects a visited/foreign network
3. Roaming agreement between operators allows connection
4. Device authenticated through home network
5. Data tunneled back, billed at roaming rates

### Types of IoT Roaming

| Type | Description |
|------|-------------|
| **Standard Roaming** | Uses visited network under a bilateral agreement |
| **Permanent Roaming** | Device always operates on a foreign network (common in IoT) |
| **Multi-IMSI** | SIM holds multiple operator identities |
| **eUICC / eSIM** | SIM profile updated remotely to switch operators |

> **Nokia WING** (Worldwide IoT Network Grid) is a managed IoT roaming service enabling devices to roam across multiple carriers globally under a single platform.

---

## 11. IoT Device Operating Systems

| Category | Description | Examples |
|----------|-------------|---------|
| 🔴 **No OS (Bare Metal)** | Code runs directly on hardware; for ultra-constrained devices | Arduino, simple sensors |
| 🟡 **RTOS** | Task scheduling with real-time guarantees; for mid-range microcontrollers | FreeRTOS, Zephyr, Contiki-OS, Riot-OS, TinyOS |
| 🟢 **GPOS (General Purpose OS)** | Full OS for powerful IoT devices, gateways, and edge devices | Linux, OpenWrt, Windows IoT, Raspberry Pi |

---

## 12. IoT Ecosystem — Companies by Layer

### Layer 1 — Sensors / Devices

| Sub-category | Companies |
|--------------|-----------|
| Embedded Software | Witekio |
| Hardware Vendors | Libelium, Eurotech, Telit, Yanzi |
| Operating Systems | Contiki-OS, FreeRTOS, Riot-OS, Zephyr, TinyOS, OpenWrt |
| Dev Boards & Kits | Raspberry Pi, Arduino, Intel Edison, MasterOfThings IoT Kit |

### Layer 2 — Wireless Sensor Networks

| Sub-category | Technologies |
|--------------|-------------|
| Short Range | RFID, NFC, Bluetooth, BLE, Bluetooth Smart |
| Long Range / LPWAN | LoRa, LoRaWAN, MioTy, Weightless, Z-Wave, ZigBee, Ingenu |
| Alliances & Standards | MulteFire 1.1, Wi-Sun, Thread, 6LoWPAN, IQRF |

### Layer 3 — Gateways

| Sub-category | Companies |
|--------------|-----------|
| Hardware Vendors | Intel, Cisco, Dell, KerLink, TEKTELIC, Minew |
| Integration Middleware | FaltCom, Alleantia |
| Network Servers | TTN, Loriot, ChirpStack, LoRaServer |

### Layer 4 — Carrier Networks

| Sub-category | Companies |
|--------------|-----------|
| LPWAN | SigFox / Unabiz |
| LEO Satellites | Lacuna, FossaSat, Angels, Hello, Kineis, Swarm |
| MVNOs / Connectivity | KORE, OnoMondo, Velos, ARKESSA, Emnify, THALES, eseye |
| Connectivity Management | Jasper CC (Cisco), Ericsson DCP, Vodafone GDSP, Nokia WING |
| Cellular Standards | GPRS, 3G, 4G LTE, 5G mMTC |

### Layer 5 — Application Enablement Platforms (AEP)

| Tier | Platforms |
|------|-----------|
| Tier 1 — Major | MasterOfThings, PTC ThingWorx, Xively (Google GCP), Cisco Kinetic |
| Tier 2 — Open/Mid | ThingsBoard, FiWare, CityOS, Gemalto |
| Tier 3 — Enterprise | Siemens Mindsphere, Schneider WonderWare, Cumulocity, GE Predix |
| ERP-Integrated | PlatOne (SAP Leonardo) |
| Telecom-Backed | Carriots (Altair) |

### Layer 6 — Analytics Platforms

| Sub-category | Platforms |
|--------------|-----------|
| Cloud & Big Data | Splunk, Grok, Hadoop |
| AI / ML Focused | Watson IoT (IBM), OneMind |

### Layer 7 — Device & Gateway Remote Management

- Balena · Kaa · Bosch IoT Suite · Nokia IMPACT

### Layer 8 — End-to-End System Integrators

Full-stack integrators covering the entire IoT value chain.

---

---

## 13. IoT Value Chain — Deep Dive (Exam Notes)

> 100% based on the Professor's slide. Every platform name, every category, all exam traps.

### 13.1 The 8 Components — Overview

| # | Component Name | Role in One Line |
|---|----------------|-----------------|
| 1 | Sensors / Devices | Physical things that sense and send data |
| 2 | Wireless Sensor Networks (WSN) | Short-range wireless to move data to the gateway |
| 3 | Gateways + Network Servers | Bridge from short-range WSN to long-range carrier |
| 4 | Carrier Networks | Long-distance transport of data to the AEP |
| 5 | Application Enablement Platforms (AEP) | IoT middleware — where applications are built and run |
| 6 | Analytics Platforms | Over-the-top analytics on top of the AEP data |
| 7 | Device & Gateway Remote Management | Remote config and firmware updates (FOTA) |
| 8 | End-to-End System Integrators | Span the entire chain — deliver complete solutions |

> ★ Value chain has **8 components**. #5 = AEP, #6 = Analytics, #7 = Device Mgmt, #8 = SI.  
> ⚠ **TRAP:** Standard web server is NOT one of the 8 components.  
> ⚠ **TRAP:** Connectivity Management Platforms (CMPs) are INSIDE Component #4, not a separate top-level component.

---

### 13.2 Component #1 — Sensors / Devices

#### Device Makers (Hardware)

- **Libelium** — complete IoT devices
- **Eurotech** — complete IoT devices
- **Telit** — complete IoT devices
- **Yanzi** — complete IoT devices
- **Witekio** — embedded software ONLY (writes firmware; does NOT manufacture complete devices)

> ★ **Witekio**: Firmware development company only — they write embedded SW, they do NOT manufacture complete IoT devices.

#### RTOS — from the slide

| RTOS | Type | Best For | MQTT Support? |
|------|------|----------|--------------|
| Contiki-OS | Open Source | Resource-constrained IoT, IPv6, low power | Yes (MQTT-SN) |
| FreeRTOS | Open Source | Real-time embedded, microcontrollers | Yes (external lib) |
| Riot-OS | Open Source | Low-power IoT, modular, WSN | Yes (lightweight) |
| Zephyr | Open Source | Security-focused, multi-core, scalable | Yes (native) |
| TinyOS | Open Source | Wireless sensor networks (WSN) only | **NO** (no native MQTT) |
| OpenWrt | Open Source | **Gateways and routers — NOT small sensors** | Yes (installable) |

> ★ All 6 RTOS are **open source**. All support MQTT directly or via library **EXCEPT TinyOS**.  
> ⚠ **TRAP:** OpenWrt is designed for GATEWAYS/routers, NOT for small IoT sensor devices.  
> ⚠ **TRAP:** TinyOS has NO native MQTT support — only for wireless sensor networks.  
> ⚠ **TRAP:** Not all IoT devices include RTOS — simple sensors may run bare-metal firmware.

#### Prototyping / Innovation Boards — from the slide

- Raspberry Pi · Arduino · Tilet · Intel Edison · MasterOfThings IoT Kit

> ★ **Purpose:** Proof of concept, testing an idea, verifying/approving a project concept.  
> ⚠ **TRAP:** Arduino and Raspberry Pi are NOT suitable for commercial IoT solutions — prototyping only!  
> ⚠ **TRAP:** All IoT devices include a CPU/MCU chip — TRUE. All include RTOS — FALSE.

---

### 13.3 Component #2 — Wireless Sensor Networks

All technologies in this column are short/medium-range and mostly **UNLICENSED** (ISM bands).

| Technology | Key Facts | Licensed? |
|------------|-----------|-----------|
| RFID | Passive tags powered by reader. Static data. | Unlicensed |
| NFC | ~1–10 cm. Passive, static data, powered by reader. | Unlicensed (13.56 MHz) |
| Bluetooth / BLE | BLE up to 300 m (BLE 5). Low power. 2.4 GHz ISM. | Unlicensed |
| Bluetooth Smart | Marketing name for BLE 4.0+ | Unlicensed |
| LoRa | Physical layer only. Up to 15 km. Cannot transfer video. | Unlicensed (868/915 MHz) |
| LoRaWAN | Network protocol over LoRa. NOT one global network. Roaming needed. | Unlicensed |
| MioTy | Low power, high reliability. Used in industry. | Unlicensed |
| MyThings (Behrtech) | Network platform for MIOTY, similar to LoRaWAN network server. | Unlicensed |
| Weightless (-P) | LPWAN standard. | Unlicensed |
| Z-Wave | Smart home. Up to 100 m only. | Unlicensed |
| ZigBee | Mesh network. Up to 100 m. 2.4 GHz ISM. | Unlicensed |
| Xbee | ZigBee/802.15.4 module family. | Unlicensed |
| Ingenu (RPMA) | 2.4 GHz ISM. Long range low power. | Unlicensed |
| PlatinusM2C | IoT connectivity solution. | Unlicensed |
| RIIM2 | Radio in Infrastructure & Industry Mesh. | Unlicensed |
| MulteFire 1.1 | LTE in unlicensed spectrum (Listen-Before-Talk). | Unlicensed |
| Wi-Sun | Smart utility metering mesh. IEEE 802.15.4g. | Unlicensed |
| Thread | IPv6 mesh for smart home. Based on 802.15.4. | Unlicensed |
| 6LoWPAN | IPv6 over low-power wireless. Adapts IPv6 for 802.15.4. | Unlicensed |
| IQRF | Low power mesh, 868/916 MHz. | Unlicensed |

> ★ ISM bands: **UNLICENSED** — free to use. 868 MHz = Europe/ME/Africa · 915 MHz = Americas · 2.4 GHz = Worldwide.  
> ⚠ **TRAP:** ZigBee, Ingenu, Z-Wave, Wi-Sun are ALL unlicensed.  
> ⚠ **TRAP:** LoRa and LoRaWAN CANNOT transfer video — far too low data rate.  
> ⚠ **TRAP:** LoRaWAN is NOT one single global network — multiple independent networks, roaming IS needed.

---

### 13.4 Component #3 — Gateways & Network Servers

#### Gateway Hardware Makers — on the slide

Intel · Cisco · Dell · KerLink · TEKTELIC · Minew · FaltCom (now Telia IoT Edge) · Alleantia (now Industrial Edge Platform)

> ★ **Gateway role:** Take data from short-range WSN and pass it to a long-range carrier network.  
> ★ **Gateway CPU/RAM sizing** depends on ALL THREE: number of devices + messages per device + offline disconnection time.  
> ⚠ **TRAP:** Gateways are the EDGE of the network — edge applications run ON the gateway.

#### LoRaWAN Network Servers — on the slide

| Server | Notes |
|--------|-------|
| TTN (The Things Network) | Open-source, community-driven, global public network |
| Loriot | Open-source, supports public/private/hybrid |
| ChirpStack | Formerly LoRa Server, written in Go, open-source |
| LoRaServer | Open-source, Go, supports LoRaWAN 1.0 and 1.1 |
| MyThings (Behrtech) | MIOTY central network platform |

> ★ **Network Server role:** Central authority for all gateways — decides which device can join which gateway. Gateways cannot decide alone.  
> ⚠ **TRAP:** Cisco Jasper is NOT a LoRaWAN network server — it is a Connectivity Management Platform (CMP).

---

### 13.5 Component #4 — Carrier Networks

#### LPWAN Operators

- **SigFox UnaBiz** — one global network, acquired by UnaBiz

#### LEO Satellite Carriers

- Lacuna · FossaSat 1u · Angels · Hello · Kineis 16U · Swarm

> ⚠ **TRAP:** ISS is NOT listed and is NOT an IoT carrier — it is a research station.  
> ⚠ **TRAP:** FossaSat is LEO, NOT GEO.  
> ⚠ **TRAP:** Swarm is a satellite carrier — NOT a global SIM provider.

#### Global SIM / eSIM Providers

KORE · OnoMondo · Velos · ARKESSA (Wireless Logic) · Emnify · THALES Adaptive Connect · eseye

> ★ **Global SIM:** A SIM card with roaming pre-granted in most countries — solves the NB-IoT roaming problem for traveling devices.  
> ⚠ **TRAP:** Emnify is a global SIM provider, NOT a LEO satellite carrier.  
> ⚠ **TRAP:** Lacuna is a satellite LoRaWAN provider, NOT a global SIM provider.

#### Connectivity Management Platforms (CMPs)

| CMP Platform | Notes |
|--------------|-------|
| Jasper CC (Cisco Control Center) | Originally Jasper Wireless — **first CMP ever built**, acquired by Cisco |
| Ericsson DCP / Accelerator (Aries) | Built by Ericsson with billing capabilities, later sold to Aeris |
| Vodafone GDSP | 2024: moved to joint venture with Microsoft |
| Verizon ThingSpace | Verizon's own CMP, US-based |
| Nokia WING | Nokia Worldwide IoT Network Grid, started 2017 |
| IoTM (Israel) | Over-the-top (OTT) CMP solution |

> ★ **CMP purpose:** Enable OR disable each device's connectivity based on defined conditions. Handles billing and SIM management.  
> ★ **First CMP ever:** Jasper Wireless — now Cisco Control Center.  
> ⚠ **TRAP:** CMP does NOT monitor the content of the data — only the connectivity itself.  
> ⚠ **TRAP:** Nokia WING = CMP (#4). Nokia IMPACT = Device Mgmt (#7). These are different products!

#### Cellular Network Technologies

- GPRS (2G) · 3G · 4G LTE variants: LTE-M, NB-IoT, LTE Lite, Cellular IoT, MulteFire LTE · 5G mMTC

> ★ **NB-IoT:** Bidirectional. Supports TCP/IP AND UDP. MQTT IS supported. Main challenge = roaming.  
> ★ **3G / 4G:** Drain IoT device battery — too power-hungry for most LPWAN IoT use cases.  
> ⚠ **TRAP:** NB-IoT IS bidirectional — it IS both upload and download.

---

### 13.6 Component #5 — Application Enablement Platforms (AEP)

> This is the **most tested component**. Learn all platform names and classify them correctly.

#### Every AEP Platform on the Slide

| Platform | Owner / Notes | Sub-category |
|----------|--------------|--------------|
| MasterOfThings | SpimeSenseLabs — professor's own platform | Licensed AEP |
| VoT / B-Scada | Slide: AEP — **Exam answer: Analytics** | AEP (slide) / Analytics (exam) |
| ThingWorx IIoT | PTC — industrial IoT AEP | Licensed IIoT AEP |
| Xively | Google GCP — one of the first IoT AEPs | Licensed AEP |
| Cisco Kinetic | Cisco's IoT AEP offering | Licensed AEP |
| ThingsBoard | Open-source, Ukrainian company | Open Source AEP |
| FiWare | Open-source — EU initiative | Open Source AEP |
| CityOS | Smart city focused AEP | Open Source AEP |
| Gimalto / Gemalto | Context dependent: AEP or connectivity | AEP / Connectivity |
| Siemens Mindsphere | Siemens industrial IoT AEP | IIoT AEP |
| Schneider WonderWare | Schneider Electric industrial SCADA/AEP | IIoT AEP |
| Cumulocity IIoT | Software AG — horizontal IoT AEP | Licensed AEP |
| GE Predix IIoT | General Electric industrial IoT AEP | IIoT AEP |
| PlatOne (SAP Leonardo) | SAP's IoT platform | Licensed IIoT AEP |
| Carriots (Altair) | IoT AEP, acquired by Altair | Licensed AEP |

> ⚠ **TRAP:** B-Scada: slide says AEP, but **exam answer = Analytics**.  
> ⚠ **TRAP:** FiWare is an open-source AEP — NOT a device management platform.  
> ⚠ **TRAP:** Cisco Kinetic = AEP (#5). Cisco Jasper = CMP (#4). Know the difference!

#### The 4 Mandatory AEP Modules

| Module | Name | Key Functions | Common Trap |
|--------|------|--------------|-------------|
| A | Sensor / Device Profile Definition | Define sensors, drivers, data types, protocols, import/export devices | Does NOT collect data |
| B | Monitoring, Enrichment & Orchestration | Real-time monitoring, rule-based engine, missing data alarms, data correlation, trigger actions | Includes rule engine + alarms |
| C | Users Access Rights Management | Manage developers AND end-users access to BOTH apps AND devices | Manages device access too, not just apps |
| D | Visual IDE (Development Environment) | Drag-and-drop, code window, frontend+backend, real-time preview | MOST IMPORTANT module for developers |

> ★ AEP module count: Exactly **4 mandatory modules** — no more, no less.  
> ★ **80% rule:** ~80% of every IoT solution is pre-built common functionality provided by the AEP.  
> ⚠ **TRAP:** Device Profile Definition does NOT collect data — that is Module B.  
> ⚠ **TRAP:** AEP is NOT a framework, NOT a software library, NOT a development stack.

#### Optional App Modules Built on top of AEP

- Alarm Management · Task Management · Asset Management · Global Calendar

> ⚠ **TRAP:** These are OPTIONAL APPLICATION MODULES, not mandatory AEP core modules.

---

### 13.7 Component #6 — Analytics Platforms

The slide labels this column **"OverOTT"** — all analytics platforms sit on top of the AEP as Over-The-Top solutions.

**Platforms on the slide:** Splunk · Grok · Hadoop · Watson IoT (IBM) · OneMind

> ★ **Hadoop:** An analytics/big data platform — NOT an IoT platform. Listed under Analytics (#6).  
> ⚠ **TRAP:** Hadoop is an Analytics platform, not an IoT AEP.  
> ⚠ **TRAP:** IBM Watson IoT is an Analytics platform in this slide's classification.

---

### 13.8 Component #7 — Device & Gateway Remote Management

Component #7 is a **horizontal layer** spanning from Component #1 to Component #4 on the slide.

**Platforms on the slide:** Balena · Kaa · **Bosch IoT Suite** · **Nokia IMPACT**

> ★ **Device Mgmt purpose:** Remote device CONFIGURATION + Remote FIRMWARE UPDATES (FOTA). That is ALL it does.  
> ⚠ **TRAP:** Device Management does NOT collect sensor data — that is the AEP's role.  
> ⚠ **TRAP:** Bosch IoT Suite = Device Management (#7), NOT an AEP (#5).  
> ⚠ **TRAP:** Nokia IMPACT = Device Management (#7), NOT a CMP and NOT an AEP.

---

### 13.9 Component #8 — End-to-End System Integrators

Component #8 is a long arrow spanning across all 6 main components (1–6). System Integrators design, build, and deliver complete IoT solutions end-to-end.

> ★ **Job title:** The **IoT Solution Architect** is the person who designs end-to-end IoT solutions. Embedded System Engineers only work on Component #1.  
> ⚠ **TRAP:** Embedded System Engineer = devices only. IoT Integration Engineer = integrates systems, does NOT develop devices.

---

## 14. Master Platform Classification Table

> Memorise every row — be able to classify each platform instantly in the exam.

| Platform Name | Component # | Category |
|---------------|-------------|----------|
| Libelium / Eurotech / Telit / Yanzi | #1 | Sensor/Device Makers |
| Witekio | #1 | Embedded SW (firmware only, NOT device maker) |
| Contiki-OS / FreeRTOS / Riot-OS / Zephyr / TinyOS / OpenWrt | #1 | RTOS for IoT devices |
| Raspberry Pi / Arduino / Intel Edison / MoT Kit / Tilet | #1 | Prototyping/Innovation Boards |
| RFID / NFC / BLE / LoRa / LoRaWAN / ZigBee / Z-Wave / Ingenu / Wi-Sun / Thread / 6LoWPAN / MioTy / Weightless / MulteFire / IQRF | #2 | Wireless Sensor Network Technologies |
| Intel / Cisco / Dell / KerLink / TEKTELIC / FaltCom / Alleantia / Minew | #3 | Gateway Hardware Makers |
| TTN / Loriot / ChirpStack / LoRaServer / MyThings | #3 | LoRaWAN Network Servers |
| SigFox UnaBiz | #4 | Carrier Network (LPWAN Operator) |
| Lacuna / FossaSat / Angels / Hello / Kineis / Swarm | #4 | Carrier Network (LEO Satellite) |
| KORE / OnoMondo / Velos / Arkessa / Emnify / THALES / eseye | #4 | Carrier Network (Global SIM Provider) |
| Jasper CC (Cisco) / Ericsson DCP / Vodafone GDSP / Verizon ThingSpace / Nokia WING / IoTM | #4 | Carrier Network (CMP) |
| GPRS / 3G / 4G LTE / NB-IoT / LTE-M / 5G mMTC | #4 | Carrier Network (Cellular Technology) |
| MasterOfThings | #5 | Application Enablement Platform (AEP) |
| VoT / B-Scada | #5 (slide) / #6 (exam) | AEP on slide BUT answer **Analytics** in exam |
| ThingWorx IIoT (PTC) | #5 | Application Enablement Platform (AEP) |
| Xively (Google GCP) | #5 | Application Enablement Platform (AEP) |
| Cisco Kinetic | #5 | Application Enablement Platform (AEP) |
| ThingsBoard | #5 | AEP — Open Source |
| FiWare | #5 | AEP — Open Source, NOT device mgmt |
| CityOS | #5 | Application Enablement Platform (AEP) |
| Gimalto / Gemalto | #5 / #4 | AEP or Global SIM — context dependent |
| Siemens Mindsphere | #5 | Application Enablement Platform (IIoT AEP) |
| Schneider WonderWare | #5 | Application Enablement Platform (IIoT AEP) |
| Cumulocity IIoT | #5 | Application Enablement Platform (AEP) |
| GE Predix IIoT | #5 | Application Enablement Platform (IIoT AEP) |
| PlatOne (SAP Leonardo) | #5 | Application Enablement Platform (AEP) |
| Carriots (Altair) | #5 | Application Enablement Platform (AEP) |
| Splunk / Grok / Hadoop / Watson IoT / OneMind | #6 | Analytics Platform (Over-OTT) |
| Balena / Kaa / Bosch IoT Suite / Nokia IMPACT | #7 | Device & Gateway Remote Management |
| End-to-End System Integrators | #8 | Cross-chain component spanning #1–#6 |

---

## 15. SigFox — The Most Tested Topic

> More exam questions come from SigFox than any other single technology.

| Fact | Value / Answer |
|------|---------------|
| Max bytes per uplink message | **12 bytes** |
| Max bytes per downlink message | **8 bytes** |
| Max uplink messages per day | **140 messages** |
| Max bytes per DAY (uplink) | 140 × 12 = **1,680 bytes** |
| Max bytes per DAY (downlink) | 4 × 8 = **32 bytes** |
| Is it one global network? | **YES** — no roaming subscription needed |
| Protocol stack | **NOT TCP/IP based** |
| MQTT support? | **NO** — MQTT needs TCP/IP, SigFox does not use it |
| Can it run as a private network? | **NO** — carrier infrastructure only |
| Can an individual buy a SigFox BTS? | **NO** — carrier infrastructure, not sold to individuals |
| Can it transfer video? | **NO** — far too low data rate |
| Frequency band | Unlicensed ISM — 868 MHz (Europe/ME/Africa) or 915 MHz (Americas) |
| Who acquired SigFox? | **UnaBiz** — now called SigFox UnaBiz |
| What did SigFox competition force? | Pushed 3GPP to develop NB-IoT as a low-power alternative |

---

## 16. IoT Job Roles

| Job Role | Works On | Common Exam Trap |
|----------|----------|-----------------|
| **IoT Solution Architect** | Designs the ENTIRE end-to-end IoT solution (all 8 components) | NOT responsible for developing devices — that is the embedded engineer |
| **Embedded System Engineer** | Component #1 ONLY — device HW design and firmware development | Does NOT design end-to-end solutions |
| **IoT Integration Engineer / SE** | Integrates platforms across the chain | Does NOT develop IoT devices |
| **IoT Platform Developer** | Works on Component #5 (AEP) | Develops the platform itself |
| **IoT Application Developer** | Builds apps running on top of Component #5 | Uses the AEP's Visual IDE |

---

## 17. Exam Traps — Last-Minute Reference

### 17.1 Platform Classification Traps

> ⚠ FiWare = AEP (#5) — NOT device management (#7).  
> ⚠ Hadoop = Analytics (#6) — NOT an IoT platform.  
> ⚠ Balena / Kaa = Device Mgmt (#7) — NOT AEP (#5).  
> ⚠ Bosch IoT Suite = Device Mgmt (#7) — NOT AEP (#5).  
> ⚠ Nokia IMPACT = Device Mgmt (#7) — NOT a CMP.  
> ⚠ B-Scada: slide says AEP, but **exam answer = Analytics**.  
> ⚠ Cisco Kinetic = AEP (#5). Cisco Jasper = CMP (#4). Know the difference!  
> ⚠ Nokia WING = CMP (#4). Nokia IMPACT = Device Mgmt (#7). Different products!  
> ⚠ THALES (Adaptive Connect) = Global SIM provider (#4). NOT an AEP.  
> ⚠ Swarm = LEO satellite carrier (#4). NOT a global SIM provider.  
> ⚠ Emnify = Global SIM provider (#4). NOT a satellite carrier.  
> ⚠ Lacuna = satellite LoRaWAN (#4). NOT a global SIM provider.  
> ⚠ ISS = NOT an IoT satellite. Not on the slide.  
> ⚠ FossaSat = LEO (not GEO).

### 17.2 Wireless Technology Traps

> ⚠ SigFox = **12 bytes/msg max**. NOT 24 bytes.  
> ⚠ SigFox = **1,680 bytes/day max** (uplink). NOT 'unlimited'.  
> ⚠ SigFox = NOT TCP/IP → **NO MQTT**.  
> ⚠ SigFox = ONE global network → **NO roaming needed**.  
> ⚠ SigFox CANNOT operate as a private network.  
> ⚠ LoRaWAN ≠ one global network → **roaming IS needed**.  
> ⚠ LoRa and LoRaWAN CANNOT transfer video.  
> ⚠ NB-IoT IS bidirectional (both upload and download).  
> ⚠ NB-IoT DOES support MQTT (TCP/IP + UDP).  
> ⚠ NB-IoT main challenge = **ROAMING**.  
> ⚠ 3G drains IoT device battery — use NB-IoT/LoRa instead.  
> ⚠ ISM band = UNLICENSED. Not exclusive to IoT.  
> ⚠ 868 MHz = Europe, ME, Africa. 915 MHz = Americas.  
> ⚠ WiFi and BLE both use **2.4 GHz** ISM band.  
> ⚠ WiFi is NOT an LPWAN technology.  
> ⚠ ZigBee, Ingenu, Z-Wave, Wi-Sun = ALL unlicensed (ISM).  
> ⚠ OpenWrt = for GATEWAYS, NOT for small IoT sensors.  
> ⚠ TinyOS = NO native MQTT support.

### 17.3 Architecture & Role Traps

> ⚠ Value chain = **8 components** (not 6).  
> ⚠ AEP = exactly **4 mandatory modules**.  
> ⚠ Applications CANNOT talk directly to devices — AEP is the mandatory middle layer.  
> ⚠ Carrier networks carry data from GATEWAY (or device) to AEP — NOT from device to gateway.  
> ⚠ Device-to-Gateway = WSN (Component #2). Gateway-to-AEP = Carrier (Component #4).  
> ⚠ Arduino/Raspberry Pi = prototyping ONLY, not commercial.  
> ⚠ Video cameras = NOT standard IoT devices (too much data for AEP).  
> ⚠ AEP cannot process video feeds.  
> ⚠ Solution Architect = end-to-end design. Embedded Engineer = devices only.  
> ⚠ IoT Integration Engineer does NOT develop IoT devices.  
> ⚠ Gateway CPU/RAM depends on ALL: device count + msg rate + disconnection time.  
> ⚠ MQTT = ISO/IEC 20922 standard. TCP/IP based. Lightweight + bidirectional + for constrained devices.  
> ⚠ CoAP = legacy protocol. No longer widely used.  
> ⚠ HTTP = NOT a good IoT protocol (too heavy).

---

*SpimeSense IoT Study Guide — compiled from SpimeSense course materials & exam study notes*

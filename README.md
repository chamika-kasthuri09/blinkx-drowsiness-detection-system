# Modular Sensor Fusion Driver Safety Headband

A hybrid edge-cloud wearable safety solution designed to detect driver drowsiness and distraction in real time using sensor fusion (Optical Infrared + 6-Axis Motion), local edge computing, and cloud AI context enhancement.

---

## 📌 Project Overview
Driver fatigue and micro-sleep are leading causes of severe road accidents worldwide. Traditional camera-based driver monitoring systems (DMS) are expensive, struggle in low-light/foggy conditions, and raise privacy concerns. 

This project introduces a low-cost (~LKR 4,500 / $15 USD), lightweight, non-invasive wearable headband that detects micro-sleeps ($>350\text{ ms}$ eyelid closure) and posture drops ($>-15^\circ$ head nod) using direct body-sensing. It operates under a **Fail-Safe Hybrid Edge-Cloud Architecture**:
1. **Edge Mode (Offline):** An onboard C algorithm runs locally on the ESP32 for sub-millisecond, latency-free haptic alerts even when cellular connectivity fails.
2. **Cloud AI Mode (Online):** When paired via Bluetooth Low Energy (BLE) to a smartphone gateway, telemetry is sent to an AI engine that dynamically adjusts risk thresholds based on real-time weather APIs, road conditions, and fatigue accumulation trends.

---

## 🎯 Key Features & Goals

### 🛠️ Hardware Goals
* **Sub-Millisecond Edge Response:** Instant temporal bone haptic feedback within $5\text{ ms}$ of fatigue detection.
* **Non-Invasive Wearable Form Factor:** Breathable sports headband housing sensors comfortably against skin/temple without obscuring vision.
* **Ultra-Low Power Consumption:** Operates on a single-cell $3.7\text{V}$ LiPo battery for continuous long-distance drives.
* **Low Cost BOM:** Built using readily available, cost-effective components (< LKR 5,000 unit cost).

### 💻 Software Goals
* **Deterministic Edge State Machine:** Zero-dependency embedded C firmware executing real-time sensor fusion logic.
* **Context-Aware Cloud AI:** API integration fetching ambient weather and environmental risk metrics to adjust sensitivity dynamically.
* **BLE Low-Latency Telemetry:** Asynchronous BLE communication between headband node and smartphone gateway.
* **Fail-Safe Redundancy:** Automatic seamless fallback to local rule-based processing if network connectivity drops.

---

## 🏗️ System Architecture

```text
                     ┌────────────────────────────────────────┐
                     │          ESP32 Wearable Edge           │
                     │  - Reads IMU (MPU6050) & IR (TCRT5000) │
                     │  - Runs Offline Embedded Algorithm     │
                     └───────────────────┬────────────────────┘
                                         │
                         Is Network Connected? (BLE / 4G)
                                         │
                   ┌─────────────────────┴─────────────────────┐
                   ▼                                           ▼
             [ YES / ONLINE ]                            [ NO / OFFLINE ]
                   │                                           │
  ┌─────────────────────────────────┐         ┌─────────────────────────────────┐
  │         Cloud AI Engine         │         │     Local ESP32 Fallback Logic  │
  │  - Weather API & Road Context   │         │  - Pure Sensor Fusion Matrix    │
  │  - Predictive Fatigue Models    │         │  - Hardcoded Dynamic Thresholds │
  │  - Risk Score Calculation       │         │  - Immediate Haptic Response    │
  └─────────────────────────────────┘         └─────────────────────────────────┘

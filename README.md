Counterfeit Drug Detection Using RFID & Blockchain

📌 Overview
This project aims to combat the problem of counterfeit medicines by integrating RFID technology with Blockchain for secure, transparent, and tamper-proof drug verification. Each legitimate drug package is tagged with an RFID tag containing a unique ID, which is stored on the blockchain at the time of manufacturing. Pharmacies and customers can verify the authenticity of the drug by scanning the RFID tag using an ESP32 + RC522 module.

🚀 Features
RFID Tagging – Each drug package is embedded with a unique RFID tag.

Blockchain-Based Verification – Tamper-proof record of drugs for authenticity checks.

Real-Time Detection – Instantly verify whether a scanned drug is genuine or counterfeit.

ESP32 Hardware Integration – Portable, low-cost, and IoT-ready device.

User-Friendly Interface – Web app for verification results and transaction details.

🛠 Tech Stack
Hardware: ESP32, RC522 RFID Module

Backend: Node.js, Express.js

Blockchain: Ethereum / Hardhat

Frontend: React.js (optional for visualization)

Database: MongoDB (for logs & history)

🔄 Workflow
Manufacturer registers a drug on the blockchain with its unique RFID ID.

RFID tag is attached to the drug package.

At any point in the supply chain, the RFID tag can be scanned using the ESP32 device.

The scanned ID is checked against blockchain records.

Verification result is displayed – Genuine ✅ or Counterfeit ❌.

⚙️ Hardware Connections
(Use the uploaded image for wiring diagram)

RC522 SDA → ESP32 D21

RC522 SCK → ESP32 D18

RC522 MOSI → ESP32 D23

RC522 MISO → ESP32 D19

RC522 RST → ESP32 D22

VCC → 3.3V, GND → GND

📅 Implementation Plan
Phase 1: Prototype Development (Hardware + Smart Contract) – 2 weeks

Phase 2: Backend & Blockchain Integration – 2 weeks

Phase 3: Frontend & UI – 1 week

Phase 4: Testing & Deployment – 1 week

Phase 5: Pilot Launch – Ongoing

🎯 Impact & Future Scope
Reduces counterfeit drugs in supply chains.

Increases transparency in pharmaceutical distribution.

Can be scaled to other industries like luxury goods, electronics, and food products.

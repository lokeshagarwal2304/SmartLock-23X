<h1 align="center">🔐 SmartLock_23X</h1>
<h3 align="center">Minimal, Visual & PIN-Based Smart Lock GUI in C</h3>

<p align="center">
  <img src="https://img.shields.io/badge/Made%20in-C%20Lang-blue?style=flat-square" />
  <img src="https://img.shields.io/badge/Type-Desktop_GUI-green?style=flat-square" />
  <img src="https://img.shields.io/badge/UI-graphics.h%20(WINBGI)-ff69b4?style=flat-square" />
  <img src="https://img.shields.io/badge/Sound-Buzzer_Beep-orange?style=flat-square" />
  <img src="https://img.shields.io/badge/Mode-Offline_Local-yellow?style=flat-square" />
</p>

---

## 🧠 Project Overview

SmartLock_23X is a **PIN-based lock simulation system** designed using **C Language** and `graphics.h` on Windows. It features animated GUI visuals, beeping sound for incorrect attempts, and strong logical structure with future-scope adaptability for **IoT, AI, and Security Systems**.

Perfect for:
- C beginners exploring real-time applications  
- Developers testing image-based GUI in C  
- Mini/academic project lovers who want depth

---

## ✨ Key Features

<table>
  <thead>
    <tr>
      <th>🚀 Feature</th>
      <th>🧩 Description</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>PIN Entry</td>
      <td>User types 4-digit PIN via keyboard input</td>
    </tr>
    <tr>
      <td>Image-Based UI</td>
      <td>Lock and Unlock states shown using BMP visuals</td>
    </tr>
    <tr>
      <td>Animated Feedback</td>
      <td>Transition between lock/unlock screens</td>
    </tr>
    <tr>
      <td>Buzzer Alert</td>
      <td>PC Speaker beeps on wrong attempt</td>
    </tr>
    <tr>
      <td>3 Attempts</td>
      <td>Failsafe lock after 3 wrong tries</td>
    </tr>
  </tbody>
</table>

---

## 🧱 The Dome of Tools

| 🧩 Component | Description | Role |
|-------------|-------------|------|
| C Language | Core logic & structure | Fast & Efficient |
| graphics.h | GUI rendering (WinBGI) | Lock/Unlock UI |
| windows.h | Delay + Beep | System-level sound |
| conio.h | Console I/O | Key detection |
| libbgi.a | Graphics linker | Draws UI in runtime |

---

## 🔧 Setup Guide

### 🗃 Requirements
- Windows system (Dev-C++ / Code::Blocks)
- `graphics.h`, `libbgi.a` (WinBGI setup)

### 🧪 Steps to Run
1. Clone/download the project  
2. Ensure `lock.bmp` and `unlock.bmp` are in same folder  
3. Link these libs under `Project → Options → Parameters`:
```

-lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32

````
4. Press `F9` to run → enter 4-digit PIN → see result

---

## 🧩 Smart Enhancements Possible

| Idea 💡 | What's Possible? |
|--------|------------------|
| 🎙️ Voice Integration | Use TTS or Voice PIN |
| 🔐 Face/Fingerprint Sim | Image-based unlock |
| 📊 Attempt Logs | Create CSV log files |
| 🌐 Connect via Serial | Unlock real doors via UART |
| 🧠 Learn & Adapt | Add AI-PIN guessing (C-rand-based) |

---

## 📸 UI Preview

| Locked 🛑 | Unlocked ✅ |
|----------|-------------|
| ![Locked](./assets/preview-lock.png) | ![Unlocked](./assets/preview-unlock.png) |

---

## 📁 Folder Structure

```bash
SmartLock_23X/
├── SmartLock.c
├── lock.bmp
├── unlock.bmp
├── SmartLock_23X.dev
├── README.md
└── assets/
    ├── preview-lock.png
    ├── preview-unlock.png
    └── smartlock_dome_diagram.png
````

---

## 🙌 Credits

**Built with ❤️ by Lokesh Agarwal**

| Platform     | Link                                                              |
| ------------ | ----------------------------------------------------------------- |
| 💼 LinkedIn  | [lokeshagarwal2304](https://linkedin.com/in/lokeshagarwal2304)    |
| 🐦 Twitter   | [@lokeshagarwal2304](https://twitter.com/lokeshagarwal2304)       |
| 📸 Instagram | [@*lokesh._*.agarwal\_](https://instagram.com/_lokesh._.agarwal_)  |
| 👻 Snapchat  | `lagarwal.23`                                                     |
| 📬 Email     | [lokeshagarwal2304@gmail.com](mailto:lokeshagarwal2304@gmail.com) |

---

## 🌟 Final Touch – Aesthetic Snap

<p align="center">
  <img src="https://raw.githubusercontent.com/lokeshagarwal2304/assets/main/startup_ending_card_smartlock.png" width="650"/>
</p>

> *“Simplest logic becomes smartest when you add intention, design and execution.”*

---

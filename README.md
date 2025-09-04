# 🛞 Tire Trouble

**Tire Trouble** is a fast-paced arcade game where you play as a runaway **car tire** bouncing around an arena, desperately avoiding a vicious bat that wants to shred your rubber.  
Your mission? **Build speed, outmaneuver the bat, and rack up points**!

---

## 🎮 Gameplay Overview

- **You are the Tire**  
  Roll and bounce off walls to build momentum and keep moving fast.

- **Beware the Bat**  
  - ⚡ **High-speed hit** → Defeat the bat for **100 points**.  
  - 💥 **Low-speed hit** → The bat tears at your rubber, costing you 1 life.  

- **Collect Coins**  
  - Coins **spawn randomly over time** throughout the level.  
  - Each coin gives **50 points** when collected.  
  - Dynamic spawning encourages movement and timing to maximize your score.  

- **Lives & Scoring**  
  - You start with **3 lives**.  
  - Lose all lives → **Game Over**.  
  - The objective is to survive and score as much as possible.

---

## 🕹️ Controls

| Action | Key |
|--------|-----|
| Move Left | ← / A |
| Move Right | → / D |
| Jump / Bounce | Spacebar |
| Quit | Esc |

---

## 🏆 Scoring System

- **Bat hit (fast)** → +100 points  
- **Coin collected** → +50 points  
- **Bat hit (slow)** → -1 Life  

---

## 🚧 Features

- Physics-based gameplay powered by **Box2D**.  
- Coins **spawn dynamically over time** to keep gameplay unpredictable.  
- Responsive audio using **FMOD**.  
- JSON-driven level and object definitions with **rapidjson**.  
- Rendering and input with **SDL3**.  
- Score and life tracking displayed on-screen.  
- Game Over state with restart option.


---

## 💻 Tech Stack

This project is built with the following libraries:

- [Box2D](https://github.com/erincatto/box2d) – 2D physics engine for bouncing and collisions.  
- [FMOD](https://www.fmod.com/) – Audio engine for music and sound effects.  
- [rapidjson](https://rapidjson.org/) – Fast JSON parser for loading levels and configs.  
- [SDL3](https://github.com/libsdl-org/SDL) – Handles rendering, input, and window management.  

---

## 📥 Installation

1. Clone this repository:
   ```bash
   git clone https://github.com/yourname/tire-trouble.git
   cd tire-trouble

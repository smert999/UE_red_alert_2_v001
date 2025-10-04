# 🎮 Red Alert 2 Remake - UE5

> Modern remake of Command & Conquer: Red Alert 2 built in Unreal Engine 5 with AI-assisted asset pipeline

[![Unreal Engine](https://img.shields.io/badge/Unreal%20Engine-5.4-blue)](https://www.unrealengine.com/)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE)
[![Status](https://img.shields.io/badge/status-in%20development-yellow.svg)](docs/UE_RTS_Course/01_Planning/ROADMAP.md)

---

## 🎯 Project Vision

**Goal:** Create a faithful Red Alert 2 clone with modern enhancements and expansion content

- **Base Game:** Recreate RA2 mechanics with IP-safe naming and AI-generated assets
- **Expansion:** New factions, units, and modern RTS mechanics
- **Legal Approach:** Original RA2 maps + UI layouts (legal), new 3D assets via AI generation
- **Tech Stack:** UE5 + Blueprint-first architecture + AI asset pipeline

---

## ✨ Features

### ✅ Implemented (Week 2 Complete!)

**RTS Camera System:**
- 🎥 Orthographic isometric view (45° angle)
- ⌨️ WASD panning (screen-space movement)
- 🖱️ Edge panning (all 4 screen edges)
  - EdgePanSpeed: 180,000 units/sec
  - EdgePanBorderPx: 450px activation zone
- 🔄 Q/E rotation
- 🔍 Mouse wheel zoom (OrthoWidth: 8000-40000)
- ⚡ Shift fast-pan with acceleration
- 🗺️ Map bounds clamping
- 🎯 Frame-rate independent movement

### 🚧 In Progress (Week 2.5)

**Map & UI Foundation:**
- 🗺️ RA2 map conversion (FinalAlert2 → UE5 Landscape)
- 🎮 Main Menu (RA2 style with modern enhancements)
- 🖱️ Custom cursor system (6 states: Default/Move/Attack/Select/Build/NoGo)
- 🎨 Skirmish setup menu

### 📅 Planned

**Week 3:** Base Buildings (5 types) + Building Placement System  
**Week 4:** Basic Units (4 types) + Selection & Orders  
**Week 5:** Economy System (Harvester, Ore, Refinery)  
**Week 6:** Combat System (Weapons, Damage, Projectiles)  
**Week 7:** Fog of War  
**Week 8:** Full UI (Sidebar, Minimap, Command Card)  
**Week 9:** Skirmish AI  
**Week 10+:** Polish, additional content, multiplayer

See [ROADMAP.md](docs/UE_RTS_Course/01_Planning/ROADMAP.md) for full development plan.

---

## 🤖 AI Asset Pipeline

**Modern AI-powered workflow for asset creation:**

### Tech Stack:
- **Concepts:** Flux.1-dev (via ComfyUI)
- **3D Generation:** Hunyuan 3D 2.5 (Tencent) + Hitem3D
- **Cleanup:** Blender + Quad Remesher
- **Import:** Unreal Engine 5

### Hardware:
- RTX 4090 24GB (local AI generation)
- i9-14900 CPU
- 128GB RAM

### Workflow:
```
Flux Concept → Hunyuan 3D → Blender Cleanup → UE5 Import
  (2-4h)        (10-20min)      (30-60min)      (20-30min)
```

See [AI_ASSET_PIPELINE_RA2.md](docs/UE_RTS_Course/02_AI_Pipeline/AI_ASSET_PIPELINE_RA2.md) for details.

---

## 🏗️ Project Structure

```
UE_red_alert_2_v001/
├── docs/                           📚 Documentation (40+ files, 10k+ lines)
│   ├── MASTER_INDEX.md            ← Start here!
│   └── UE_RTS_Course/
│       ├── 01_Planning/           Planning & Tracking
│       ├── 02_AI_Pipeline/        AI Generation Workflows
│       ├── 03_Maps_Environment/   Map Conversion & Environment
│       ├── 04_UI_Design/          Menu & UI Design
│       ├── 05_Week_Plans/         Weekly Action Plans
│       ├── 06_Assets_Lists/       Units & Buildings Database
│       ├── 07_Utilities/          Helper Scripts & Tools
│       └── UE_KB/                 Knowledge Base (UE5/Blueprint guides)
│
└── UE_RTS_Course/                 🎮 Unreal Engine Project
    ├── Content/
    │   ├── Blueprints/            BP_RTS_CameraPawn, GameMode, PlayerController
    │   ├── Maps/                  Main.umap (test map)
    │   ├── Art/                   (будущие 3D assets)
    │   ├── UI/                    (будущие widgets)
    │   └── Data/                  (будущие DataTables)
    ├── Config/                    Project settings
    └── Saved/                     Autosaves, logs
```

---

## 🚀 Getting Started

### Prerequisites:
- Unreal Engine 5.4+
- Windows 10/11
- Git

### Installation:

```bash
# Clone repository
git clone https://github.com/YOUR_USERNAME/UE_red_alert_2_v001.git
cd UE_red_alert_2_v001

# Open UE project
# Double-click: UE_RTS_Course/UE_RTS_Course.uproject
```

### First Launch:
1. UE5 will compile shaders (first time ~5-10 min)
2. Main map will load automatically
3. Press **Play (Alt+P)** to test camera
4. Use **WASD** + **Edge panning** + **Q/E rotation** + **Mouse wheel zoom**

---

## 📖 Documentation

**Start here:** [`docs/MASTER_INDEX.md`](docs/MASTER_INDEX.md)

**Key Documents:**
- 🗺️ **Roadmap:** [`01_Planning/ROADMAP.md`](docs/UE_RTS_Course/01_Planning/ROADMAP.md)
- 📝 **Progress Log:** [`01_Planning/PROGRESS.md`](docs/UE_RTS_Course/01_Planning/PROGRESS.md)
- 📋 **Tech Spec:** [`01_Planning/TECH_SPEC.md`](docs/UE_RTS_Course/01_Planning/TECH_SPEC.md)
- 🎨 **AI Pipeline:** [`02_AI_Pipeline/AI_ASSET_PIPELINE_RA2.md`](docs/UE_RTS_Course/02_AI_Pipeline/AI_ASSET_PIPELINE_RA2.md)

**Current Week:** [`05_Week_Plans/WEEK_2_5_ACTION_PLAN.md`](docs/UE_RTS_Course/05_Week_Plans/WEEK_2_5_ACTION_PLAN.md)

---

## 🛠️ Development

### Current Status (Week 2.5):

**Completed:**
- ✅ Week 1: Project & Inputs
- ✅ Week 2: RTS Camera (full edge panning on all 4 edges)

**In Progress:**
- 🔄 Week 2.5: RA2 Map Conversion + Main Menu + Cursor

**Next:**
- ⏳ Week 3: Base Buildings (5 types via AI)
- ⏳ Week 4: Basic Units + Selection

### Technology:

**Engine:** Unreal Engine 5.4  
**Language:** Blueprints (C++ only where performance-critical)  
**AI Tools:** Flux.1-dev, Hunyuan 3D 2.5, Hitem3D  
**3D Tools:** Blender, Quad Remesher  

---

## 🎨 AI-Generated Assets

**Approach:** All 3D assets generated via AI to avoid copyright issues

**Units & Buildings:**
- 👥 Infantry: 14 types (Rifleman, Engineer, Sniper, etc.)
- 🚗 Vehicles: 12 types (Tanks, Harvesters, APCs, etc.)
- ✈️ Aircraft: 5 types (Fighters, Helicopters, Bombers)
- 🏭 Buildings: 25+ types (Base, Production, Defense)
- 🌳 Props: Trees, Rocks, Decorations

See [`RA2_UNITS_BUILDINGS_LIST.md`](docs/UE_RTS_Course/06_Assets_Lists/RA2_UNITS_BUILDINGS_LIST.md) for complete list.

---

## 🗺️ Maps

**Strategy:** Convert original RA2 maps to UE5 (legal via reverse engineering)

**Process:**
1. Export from RA2 using FinalAlert2
2. Import heightmap to UE5 Landscape
3. Place Ore nodes based on original positions
4. Setup NavMesh and lighting

**Recommended Maps:**
- Heck Freezes Over (2 players)
- Tour of Egypt (4 players)

See [`RA2_MAP_CONVERSION_GUIDE.md`](docs/UE_RTS_Course/03_Maps_Environment/RA2_MAP_CONVERSION_GUIDE.md) for detailed guide.

---

## 🎮 Design Philosophy

> **"Preserve the spirit of RA2, enhance everything else"**

**Core Principles:**
- ✅ Faithful recreation of RA2 gameplay
- ✅ Modern graphics and UI/UX
- ✅ IP-safe (original assets, generic naming)
- ✅ Extensible (ready for new content)
- ✅ Performance-optimized (60 FPS target)

---

## 🤝 Contributing

This is a personal learning project, but feedback and suggestions are welcome!

**Useful Contributions:**
- 🐛 Bug reports
- 💡 Feature suggestions
- 📝 Documentation improvements
- 🎨 Asset creation tips

---

## 📜 Legal / IP Safety

**This project:**
- ✅ Uses **generic military naming** (no EA/Westwood trademarks)
- ✅ **AI-generated 3D models** (no copyright infringement)
- ✅ **Original RA2 maps** used via reverse engineering (legal)
- ✅ **No copyrighted audio/logos** (will create original)

**Not affiliated with Electronic Arts or Westwood Studios.**

**Inspiration:** Command & Conquer: Red Alert 2 (2000)  
**Assets:** 100% original via AI generation  
**Purpose:** Educational and portfolio project  

---

## 📊 Progress Tracking

**Development Speed:** ~2 weeks of roadmap per ~3 weeks of work (good pace!)

**Weekly Updates:** See [`PROGRESS.md`](docs/UE_RTS_Course/01_Planning/PROGRESS.md)

**Current Milestone:** Playable game skeleton (Week 2.5)
- Can launch via menu ✅ (coming soon)
- Can fly camera over RA2 map ✅ (coming soon)
- RA2-style cursor working ✅ (coming soon)

---

## 🔧 Technical Details

**Camera Implementation:**
- YawPivot/PitchPivot architecture
- FloatingPawnMovement component
- Blueprint-only (no C++ for camera)
- Configurable parameters

**Edge Panning:**
- All 4 edges: Left, Right, Top, Bottom
- Diagonal movement in corners
- Uses `Get Mouse Position` (not DPI-scaled)
- Movement vectors: RightVector (L/R), ForwardVector (T/B)

**Map Bounds:**
- Configurable MinX/MaxX/MinY/MaxY
- Tick-based clamping (preserves Z coordinate)

See [`UE_KB/`](docs/UE_RTS_Course/UE_KB/) for detailed technical documentation.

---

## 📸 Screenshots

_Coming soon! (after Week 2.5 - first playable build)_

---

## 🎯 Roadmap Summary

| Week | Feature | Status |
|------|---------|--------|
| 1 | Project Setup & Inputs | ✅ Complete |
| 2 | RTS Camera (WASD, Edge Pan, Zoom, Rotation) | ✅ Complete |
| 2.5 | Map Conversion + Main Menu + Cursor | 🔄 In Progress |
| 3 | Base Buildings (5 types) + Placement | ⏳ Planned |
| 4 | Basic Units (4 types) + Selection | ⏳ Planned |
| 5 | Economy System | ⏳ Planned |
| 6 | Combat System | ⏳ Planned |
| 7 | Fog of War | ⏳ Planned |
| 8 | Full UI (Sidebar, Minimap) | ⏳ Planned |
| 9 | Skirmish AI | ⏳ Planned |
| 10-12 | Polish, Additional Content, Multiplayer | ⏳ Planned |

**Full Roadmap:** [`ROADMAP.md`](docs/UE_RTS_Course/01_Planning/ROADMAP.md)

---

## 🌟 Highlights

### AI-Powered Development:
- 🤖 **Hunyuan 3D 2.5** for 3D model generation
- 🎨 **Flux.1-dev** for concept art
- 🖌️ **ComfyUI** for workflow automation
- 💻 **Local generation** on RTX 4090 (no cloud dependency)

### Original RA2 Integration:
- 🗺️ Convert and use original campaign/skirmish maps
- 🎨 Inspired by original UI design (enhanced for modern UX)
- 🎵 Similar military aesthetic and atmosphere

### Modern Enhancements:
- 📐 HD graphics (1920x1080+, 4K ready)
- 🎨 Modern UI/UX with animations and tooltips
- ⚡ Optimized for 60+ FPS
- 🎮 Accessibility features (color-blind mode, remappable keys)

---

## 📚 Documentation

**40+ documents, 10,000+ lines of planning and technical specs**

Browse all documentation: [`docs/MASTER_INDEX.md`](docs/MASTER_INDEX.md)

**Quick Links:**
- 📖 [Master Index](docs/MASTER_INDEX.md) - Complete documentation index
- 🎯 [Roadmap](docs/UE_RTS_Course/01_Planning/ROADMAP.md) - 12-week development plan
- 📝 [Progress Log](docs/UE_RTS_Course/01_Planning/PROGRESS.md) - Daily updates
- 🛠️ [Tech Spec](docs/UE_RTS_Course/01_Planning/TECH_SPEC.md) - Technical specifications
- 🤖 [AI Pipeline](docs/UE_RTS_Course/02_AI_Pipeline/AI_ASSET_PIPELINE_RA2.md) - Asset generation workflow

---

## 💻 System Requirements

### Development:
- **OS:** Windows 10/11 (64-bit)
- **CPU:** i5-8400 or better
- **RAM:** 16GB minimum, 32GB+ recommended
- **GPU:** GTX 1060 6GB or better (RTX recommended for AI)
- **Storage:** 50GB+ SSD

### AI Generation (Optional):
- **GPU:** RTX 3060 12GB minimum (RTX 4090 ideal)
- **VRAM:** 12GB+ for Flux.1-dev, 16GB+ for Hunyuan 3D 2.5
- **Storage:** 50GB+ for AI models

---

## 🎓 Learning Resources

This project serves as a comprehensive UE5 RTS development course.

**Knowledge Base includes:**
- 📷 Camera system implementation
- 🖱️ Edge panning (complete guide with debugging)
- 🎮 Blueprint basics
- 🎨 AI asset generation pipeline
- 🗺️ Map conversion techniques
- 🎨 UI/UX design for RTS games

All documentation in Russian with English glossary.

---

## 🔗 Links

**Project:**
- 📂 [Documentation Index](docs/MASTER_INDEX.md)
- 📅 [Development Roadmap](docs/UE_RTS_Course/01_Planning/ROADMAP.md)
- 📝 [Latest Progress](docs/UE_RTS_Course/01_Planning/PROGRESS.md)

**External:**
- 🎮 [Original Red Alert 2](https://cnc.fandom.com/wiki/Command_%26_Conquer:_Red_Alert_2) (inspiration)
- 🔧 [Unreal Engine](https://www.unrealengine.com/)
- 🤖 [Hunyuan 3D 2.5](https://github.com/Tencent/Hunyuan3D-2)

---

## 📝 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

**Note:** This is a fan remake for educational purposes. Not affiliated with or endorsed by Electronic Arts or Westwood Studios. Command & Conquer and Red Alert are trademarks of Electronic Arts Inc.

---

## 👨‍💻 Author

**Developer:** nfspr  
**Start Date:** September 2025  
**Tech:** UE5 + AI Pipeline + Blueprint  

---

## 🙏 Acknowledgments

- Original game by Westwood Studios
- Unreal Engine by Epic Games
- Hunyuan 3D 2.5 by Tencent
- Flux by Black Forest Labs
- ComfyUI community

---

## 📊 Stats

**Development Time:** ~3 weeks  
**Features Completed:** 2/12 weeks  
**Documentation:** 40+ docs  
**Lines of Code/Docs:** 10,000+  
**Commit Activity:** Active daily development  

**Last Updated:** October 4, 2025

---

<p align="center">
  <b>⚡ Built with Unreal Engine 5 + AI Pipeline ⚡</b><br>
  <i>From concept to playable in weeks, not months!</i>
</p>

---

## 🎯 Quick Start for Developers

1. **Read:** [`docs/MASTER_INDEX.md`](docs/MASTER_INDEX.md) - Complete overview
2. **Understand:** [`docs/UE_RTS_Course/01_Planning/ROADMAP.md`](docs/UE_RTS_Course/01_Planning/ROADMAP.md) - Development plan
3. **Execute:** [`docs/UE_RTS_Course/05_Week_Plans/WEEK_2_5_ACTION_PLAN.md`](docs/UE_RTS_Course/05_Week_Plans/WEEK_2_5_ACTION_PLAN.md) - Current week tasks
4. **Play:** Open UE project and test camera system!

**Total setup time:** < 10 minutes to first playable build! 🚀

---

**⭐ Star this repo if you find it useful for learning UE5 RTS development!**


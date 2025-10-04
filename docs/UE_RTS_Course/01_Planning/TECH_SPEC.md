## Technical Specification (UE RTS, RA2 Clone + Expansion)

### 1. Scope and Constraints
**Project Goal:** Create faithful Red Alert 2 clone + expansion content
- **Base Game:** RA2 mechanics, units, buildings (IP-safe naming)
- **Expansion:** New factions, units, modern mechanics
- **Original Assets:** Can use RA2 maps, UI layouts (legal per reverse engineering)
- **New Assets:** AI-generated 3D models, enhanced graphics
- PC Windows target; single-player skirmish initially; multiplayer deferred.
- Blueprint-first architecture; C++ only where performance-critical.

### 2. Game Pillars
- Clarity-first readability (orthographic/isometric view, crisp silhouettes).
- Snappy orders and responsive pathing.
- Data-driven balance with fast iteration.

### 3. Camera & Input
- Projection: Orthographic (isometric angle).
- Controls: WASD pan, edge panning, wheel zoom (ortho width), Q/E rotate (optional).
- Map bounds clamping; configurable speeds and zoom range.

### 4. World, Tiles, and Grid
- World: heightmap or modular tiles; logical grid for building placement (e.g., 1 cell = 2m).
- Building footprints snapped to grid; no-overlap checks; terrain blocking rules.

### 5. Units System
- Unit data via DataTables/PrimaryDataAssets (cost, speed, armor, weapon refs).
- Selection (single/multi, groups 1–9), rally points, stances (hold/attack-move).
- Movement: NavMesh-based; queued orders; simple formation keep.

### 6. Buildings and Production
- Placement ghost, valid/invalid feedback, power/resource connections (optional).
- Production queues; build times; rally targets.

### 7. Resources and Economy
- Resource nodes (ore/energy); harvesters with carry capacity; refineries/depots.
- Income on offload; visible resource count and spending.

### 8. Combat Model
- Weapons: projectile/hitscan; ROF, damage types, armor tags.
- Targeting: acquisition radius, priorities; attack-move.
- Damage handling with tags; death, debris/VFX hooks.

### 9. Fog of War
- Shroud + explored state; vision per-team; render-target or tile-mask approach.

### 10. UI / UX
**Design Philosophy:** RA2 original + modern enhancements
- **Menu System:** Based on RA2 layouts, improved with UE5 UMG
  - Main Menu: Animated backgrounds, modern buttons
  - Skirmish Setup: 3-column layout, HD map previews
  - In-Game HUD: Sidebar, command card, minimap (all RA2-style but HD)
- **Features:** Sidebar production, command card, tooltips, health bars, minimap, alerts
- **Tech:** CommonUI/UMG; hotkeys; rebindable input
- **Reference:** See `RA2_MENU_UI_DESIGN.md` for detailed specifications

### 11. AI (Skirmish)
- Simple build order, scouting, harassment, attack waves; difficulty scalars.

### 12. Data & Save
- Tuning via DataTables; JSON/SaveGame for options and replays (later).

### 13. Performance Targets
- 60 FPS on mid-range PC at 1080p; LOD/Nanite for static meshes; Mass for crowds.

### 14. Tools & AI-Assisted Pipeline (UPDATED 2025-10-04)

**Confirmed Stack:**
- **Concepts:** Flux.1-dev (ComfyUI) - any version works
- **3D Generation:** Hunyuan 3D 2.5 (Tencent) + Hitem3D (backup)
- **Cleanup:** Blender + Quad Remesher addon
- **Texturing:** Substance Painter / Quixel Mixer
- **RA2 Assets:** FinalAlert2 (map conversion), XCC Mixer (sprites extraction)

**Hardware:**
- RTX 4090 24GB (local AI generation)
- i9-14900 CPU
- 128GB RAM
- ComfyUI + Hunyuan 3D 2.5 local setup

**Alternative Tools:**
- Hitem3D (web-based, simple)
- TripoSR (local, free backup)
- Quixel Megascans (environment props)

### 15. Folder Conventions (UE)
- `/Content/Blueprints`, `/Content/Art/Characters`, `/Content/Art/Props`, `/Content/UI`, `/Content/Data`, `/Content/Maps`.

### 16. Legal/IP Safety
- New naming, original art and audio; avoid derivative logos and voice lines.





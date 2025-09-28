## Technical Specification (UE RTS, RA2-like)

### 1. Scope and Constraints
- Create an original RTS inspired by RA2 camera/mechanics; avoid copyrighted names, UI, audio, and art.
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
- Sidebar production, command card, tooltips, health bars, minimap, alerts.
- CommonUI/UMG; hotkeys; rebindable input.

### 11. AI (Skirmish)
- Simple build order, scouting, harassment, attack waves; difficulty scalars.

### 12. Data & Save
- Tuning via DataTables; JSON/SaveGame for options and replays (later).

### 13. Performance Targets
- 60 FPS on mid-range PC at 1080p; LOD/Nanite for static meshes; Mass for crowds.

### 14. Tools & AI-Assisted Pipeline
- Concept: SDXL/Midjourney for references.
- 3D gen: Meshy/TripoSR/Luma → cleanup in Blender.
- Retopo: Instant Meshes/Quad Remesher; UV: Rizom/Blender.
- Texturing: Substance Painter/Quixel Mixer.
- Rig/Animation: AccuRig/Mixamo → UE Control Rig; Rokoko/Video mocap, Cascadeur assist.

### 15. Folder Conventions (UE)
- `/Content/Blueprints`, `/Content/Art/Characters`, `/Content/Art/Props`, `/Content/UI`, `/Content/Data`, `/Content/Maps`.

### 16. Legal/IP Safety
- New naming, original art and audio; avoid derivative logos and voice lines.





## Progress Log

Use this file to record daily progress, decisions, and checkpoints. Add newest entries at the top.

### Template
- Date: YYYY-MM-DD
  - Work:
  - Decisions:
  - Next:

---

### 2025-09-28 (Factory AI Droid)
- Work: Created Blueprint-only edge panning implementation guide for left screen edge. Documented exact Blueprint variables (EdgePanEnabled, EdgePanBorderPx=15, EdgePanSpeed=12000) and complete Event Tick node chain. Mouse position detection via GetMousePositionScaledByDPI, left boundary check (X ≤ 15px), YawPivot-based movement using negated Right Vector with Z=0 normalization. Frame-rate independent movement with EdgePanSpeed × DeltaTime. No C++ or Source folder changes required.
- Decisions: Blueprint-only approach per request. Integration with existing YawPivot/PitchPivot architecture. Non-destructive implementation preserving WASD/Zoom/Rotation functionality. Minimal diff focused on BP_RTS_CameraPawn only.
- Next: Manual Blueprint implementation in UE Editor following exact node specifications, test edge panning functionality, extend to all screen edges (right/top/bottom).

### 2025-09-15
- Work: Rebuilt camera rig with `YawPivot`/`PitchPivot` → `SpringArm` → `Camera`. Moved WASD to screen-space via `YawPivot` Forward/Right (Z=0, Normalize). Implemented Zoom (OrthoWidth clamp) and Q/E rotation using `CameraYaw` + `SetRelativeRotation(Target=YawPivot)`. Added FastPan (Shift) with dynamic `Max Speed/Acceleration/Deceleration`. Fixed issues: `YawPivot` None on BeginPlay (relinked component), one-way rotation (used Add for both), docs updated (`CameraRig_RTS_Rebuild.md`).

### 2025-09-16
- Work: Added map bounds clamp on Tick (Clamp X/Y, preserve Z) to prevent camera leaving the world; created test Landscape as large ground to visualize borders. Fixed black screen from Z=0 and from positive `MinX/MinY` by wiring Z from `GetActorLocation` and using negative mins (e.g., MinX/MinY = −50000). Tuned FastPan speeds; verified clamping with orthographic camera.
- Decisions: Keep clamp via Tick for simplicity; later move to post-input if needed. Landscape used only for visualization; world extents controlled by `MinX/MaxX/MinY/MaxY` variables.
- Next: Implement left-side edge panning (10–20 px) and then expand to all edges; disable when over UI.
- Decisions: Actor Rotation stays (0,0,0); Pitch is fixed on `PitchPivot` (−50); Yaw only on `YawPivot`. Keep orthographic camera.
- Next: Add edge panning (mouse near screen borders) and map bounds clamp; then tidy input values and speeds.

### 2025-09-14
- Work: UE project created and set as default map; GameMode/PlayerController hooked; built `BP_RTS_CameraPawn` (SpringArm→Camera, Orthographic). Fixed black screen (floor + lights), corrected SpringArm rotation mapping (X=Roll, Y=Pitch, Z=Yaw). Implemented WASD pan using SpringArm Forward/Right vectors (screen-space movement). Verified movement works.
- Decisions: Keep actor Rotation = (0,0,0); control view only via SpringArm (Pitch −50, Yaw 45). Defer Zoom and Edge Panning to next session.
- Next: Add Zoom (Mouse Wheel → OrthoWidth clamp), Q/E rotate, optional FastPan; then Edge Panning.

### 2025-09-13 (Planning)
- Work: Defined today as planning-only; scheduled ADHD-friendly micro-steps for tomorrow.
- Decisions: Start with smallest vertical slice: camera pawn + basic pan/zoom.
- Next (ADHD-friendly micro-steps for 2025-09-14):
  1) Open Unreal Project Browser → create Blank Blueprint project (10 min).
  2) Enable plugins: Enhanced Input, CommonUI, GAS, Mass, Navigation, Editor Utility Widgets (5 min).
  3) Create Content folders: Blueprints, UI, Data, Art, Maps (5 min).
  4) Add `BP_RTS_CameraPawn` with SpringArm + Camera (Orthographic); set OrthoWidth clamps only (15 min).
  5) Project Settings → Input: map WASD, Zoom (wheel), FastPan (Shift) (10 min).
  6) Implement simple pan + zoom; PIE test for 2 minutes; note issues (15 min).
  7) Write notes in `PROGRESS.md`, stop for the day (5 min).
- Notes: Use 25/5 Pomodoro; one step at a time; stop after step 7.

### 2025-09-13
- Work: Created `docs/UE_RTS_Course` with `README.md`, `TECH_SPEC.md`, `ROADMAP.md`, `PROGRESS.md` to persist scope/plan/progress.
- Decisions: Adopt IP-safe RA2-like approach; Blueprint-first with selective C++.
- Next: Finalize scope (mechanics list), set up UE project and plugins, build RA2 camera.



## Progress Log

Use this file to record daily progress, decisions, and checkpoints. Add newest entries at the top.

### Template
- Date: YYYY-MM-DD
  - Work:
  - Decisions:
  - Next:

---

### 2025-10-04 (Documentation Reorganization ✅)
- Work: Полная реорганизация структуры документации. Создано 7 логических папок с числовой префиксацией (01-07). Все 20+ документов перемещены по категориям. Создан README_FOLDER.md для каждой папки. PowerShell скрипт reorganize_docs.ps1 для автоматизации. Обновлён MASTER_INDEX.md со всеми новыми путями и cross-references.
- Decisions:
  - **Структура:** 7 папок (Planning, AI_Pipeline, Maps_Environment, UI_Design, Week_Plans, Assets_Lists, Utilities)
  - **Числовая префиксация:** 01-07 для правильной сортировки
  - **README в папках:** Описание содержимого каждой категории
  - **UE_KB unchanged:** Knowledge Base остаётся как есть (уже хорошо организована)
- Result:
  - ✅ Легко найти нужный документ
  - ✅ Логическая группировка
  - ✅ Готовность к расширению
  - ✅ MASTER_INDEX как centralizedточка входа
- Docs Created:
  - `REORGANIZATION_SUMMARY.md` - отчёт о реорганизации
  - `README_FOLDER.md` x7 - описания для каждой папки
  - `reorganize_docs.ps1` - automation script
- Next: Начать Week 2.5 execution с новой организованной документацией

### 2025-10-04 (Documentation Audit & Menu Design 📚)
- Work: Полный аудит всей документации проекта. Создан RA2_MENU_UI_DESIGN.md (660 строк) с детальным описанием улучшенного меню RA2 - современный дизайн сохраняющий дух оригинала. Создан MASTER_INDEX.md - централизованный указатель всех 35+ документов с категоризацией и quick links. Обновлены TECH_SPEC, PROJECT_STATUS с подтверждёнными AI tools (Hunyuan 3D 2.5, Hitem3D, Flux). Проект официально определён как "RA2 Clone + Expansion".
- Decisions:
  - **Меню:** Базироваться на оригинальном RA2 layout но улучшить с UE5 UMG
  - **UI Design:** Сохранить military aesthetic, добавить modern UX (animations, tooltips, HD graphics)
  - **Scope:** Clone (base game) + Expansion (new content) - два продукта в одном
  - **AI Tools Confirmed:** Flux.1-dev + Hunyuan 3D 2.5 (primary) + Hitem3D (backup)
  - **Legal:** Можно использовать RA2 карты и UI layouts (reverse engineering)
- Docs Created/Updated:
  - `RA2_MENU_UI_DESIGN.md` - 660 строк (Main Menu, Skirmish, HUD, design system)
  - `MASTER_INDEX.md` - Полный указатель документации (35+ docs categorized)
  - Updated `TECH_SPEC.md` - AI tools stack, scope clarification
  - Updated `PROJECT_STATUS.md` - Tools confirmation, project goal
- Next:
  - Week 2.5 execution: Map conversion, Menu creation, Cursor setup
  - Ждём начала работы по action plan

### 2025-10-04 (ROADMAP Reorganization - Gameplay-First Approach 🎯)
- Work: Полная реорганизация roadmap под "gameplay-first" подход. Решение использовать карты из оригинальной RA2 (легально!) для быстрого старта. Новый приоритет: сначала играбельный скелет (карта + меню + курсор), потом наполнение контентом (здания/юниты). Создан детальный action plan для Week 2.5.
- Decisions:
  - **Использовать RA2 карты:** Конвертация через FinalAlert2 → UE5 Landscape
  - **Меню сначала:** Main Menu → Skirmish Setup → Game (можно запустить с первых дней!)
  - **RA2 Cursor:** Извлечь/воссоздать все состояния (Default/Move/Attack/Select/Build/NoGo)
  - **Итеративное наполнение:** Week 3 = здания, Week 4 = юниты, Week 5 = экономика
  - Отложен AI Asset Pipeline до Week 3 (сначала структура, потом контент)
- Next:
  - Выбрать и конвертировать 1 карту из RA2 (Heck Freezes Over или Tour of Egypt)
  - Создать Main Menu + Skirmish Setup (UMG Widgets)
  - Setup RA2 cursor system (6 состояний)
  - Ожидаем совета знакомого про ComfyUI (для Week 3 assets)
- Docs Created:
  - `RA2_MAP_CONVERSION_GUIDE.md` - полный гайд по конвертации карт
  - `WEEK_2_5_ACTION_PLAN.md` - детальный план на 11-17 часов работы
  - Updated `ROADMAP.md` - новая структура phases
  - Updated `MAPS_ENVIRONMENT_PLAN.md` - интеграция с RA2 картами

### 2025-10-04 (Edge Panning - ALL 4 EDGES COMPLETED ✅)
- Work: Завершена полная реализация Edge Panning для всех 4 краёв экрана в `BP_RTS_CameraPawn`. Использован `Get Mouse Position` (без DPI scaling) для корректной работы на всех разрешениях. Реализованы:
  - LEFT edge: `MouseX <= 15` → `-YawPivot.RightVector` (Z=0, normalized)
  - RIGHT edge: `MouseX >= (ViewportWidth - 15)` → `YawPivot.RightVector` (Z=0, normalized)
  - TOP edge: `MouseY >= (ViewportHeight - 15)` → `YawPivot.ForwardVector` (Z=0, normalized)
  - BOTTOM edge: `MouseY <= 15` → `-YawPivot.ForwardVector` (Z=0, normalized)
  - Все движения frame-rate independent через `EdgePanSpeed × DeltaSeconds`
  - Сохранён порядок выполнения: Then1 (edge pan) → Then2 (map clamps)
- Decisions: 
  - Отказались от `Get Mouse Position Scaled by DPI` в пользу обычного `Get Mouse Position` из-за проблем с DPI scaling
  - Для вертикального движения используется `ForwardVector`, для горизонтального - `RightVector`
  - Создана детальная документация `EdgePanning_TopBottom_Detailed_RU.md` с пошаговыми инструкциями
  - Диагональное движение (углы экрана) работает автоматически благодаря параллельным проверкам всех краёв
- Next: 
  - Донастроить параметры камеры (EdgePanSpeed, EdgePanBorderPx) под комфортное управление ✅
    - EdgePanSpeed: 12000 → 180000 (увеличено в 15x для быстрого движения)
    - EdgePanBorderPx: 15 → 450 (увеличена зона реакции в 30x)
  - Начать AI Asset Pipeline для создания графики в стиле Red Alert 2
  - Составить список юнитов/зданий для воссоздания (IP-safe версии)

### 2025-09-28
- Work: Implemented left edge‑panning in `BP_RTS_CameraPawn` (Blueprint‑only). Added variables `EdgePanEnabled=true`, `EdgePanBorderPx=15`, `EdgePanSpeed=12000`. On Tick: `GetMousePositionScaledByDPI` → branches (`Enabled` ∧ `ReturnValue` ∧ `LocationX <= Border`) → move left using `-YawPivot.RightVector` flattened (Z=0) and normalized; scale = `EdgePanSpeed * DeltaSeconds`. Ensured clamp order: edge‑pan (Then1) → map clamps X/Y (Then2).
- Decisions: Keep BP‑only approach; expand to right/top/bottom edges next. Keep clamps on Tick after all motion.
- Next: Add right‑edge panning; then top/bottom; disable edge‑pan over UI areas.

### 2025-09-28 (Edge Panning Expansion)
- Work: Authored UE_KB docs for all remaining edges:
  - `UE_KB/EdgePanning_RightEdge_Implementation.md`
  - `UE_KB/EdgePanning_TopBottom_Implementation.md`
  - Updated `UE_KB/Blueprint_EdgePanning_Diagram.md` to reflect all edges and execution order (Then1 edge‑pan → Then2 clamps).
- Decisions: Use `ViewportSize` for right/top thresholds: compare `MouseX ≥ (ViewX - Border)`, `MouseY ≥ (ViewY - Border)`; bottom uses `MouseY ≤ Border`. Movement vectors: Right = `YawPivot.Right (Z=0)`, Left = `-Right`, Top = `YawPivot.Forward (Z=0)`, Bottom = `-Forward`. All scaled by `EdgePanSpeed × DeltaSeconds`.
- Next: Implement right/top/bottom in `BP_RTS_CameraPawn` Event Tick following docs; then add UI hover‑lock (skip edge‑pan when cursor over UI widgets).

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



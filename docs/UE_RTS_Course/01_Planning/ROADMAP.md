## Roadmap (12 Weeks) - Updated 2025-10-04

### ✅ Week 1 — Project & Inputs (ЗАВЕРШЕНО)
- UE 5.4 project, plugins: Enhanced Input, CommonUI, GAS, Mass, Nav.
- Input mappings; folder conventions; DataTables scaffold.

### ✅ Week 2 — RA2 Camera (ЗАВЕРШЕНО 2025-10-04)
- Orthographic iso camera pawn; WASD, edge pan (ВСЕ 4 КРАЯ), zoom; clamps.
- EdgePanSpeed: 180000, EdgePanBorderPx: 450
- Полностью функциональная камера готова к использованию!

### 🔄 Week 2.5 — Map Conversion + Core UI (В ПРОЦЕССЕ) 
**НОВОЕ: Создаём играбельный скелет игры!**

**Приоритет 1: Карта из RA2** 🗺️
- Выбрать 1 скирмиш карту из RA2 (небольшую, 2-4 игрока)
- Конвертировать .map файл через FinalSun/FinalAlert2
- Импорт heightmap в UE5 Landscape
- Разместить ресурсные точки (Ore)
- NavMesh setup
- Lighting (изометрия 45°)

**Приоритет 2: Меню и UI** 🎮
- Main Menu (стартовый экран)
  - Background (видео или статичный из RA2)
  - Buttons: Skirmish, Settings, Exit
  - RA2 UI стиль!
- Skirmish Setup Menu
  - Map selection (1 карта пока)
  - Player slots (2-4)
  - Start Game button
- In-Game UI Shell (пустой пока)
  - Sidebar placeholder
  - Top bar (resources placeholder)

**Приоритет 3: Курсор** 🖱️
- RA2 cursor sprites (из игры или редизайн)
- Animated cursor states:
  - Default (стрелка)
  - Move (зелёная стрелка)
  - Attack (красный прицел)
  - Select (рамка)
  - Build (молоток)
  - No-go (красный X)
- Hardware cursor setup в UE5

**Цель:** 
✅ Можно запустить игру через меню!
✅ Выбрать карту и начать скирмиш!
✅ Летать камерой по реальной RA2 карте!
✅ RA2 курсор работает!

### ⏳ Week 3 — Base Buildings (СЛЕДУЮЩЕЕ)
**Требует:** Работающее меню + карта
**Создаём базовые здания для скирмиша:**

**3D Assets (AI Generation или из RA2):**
- Construction Yard (главное здание)
- Power Plant (электростанция)
- Barracks (казарма)
- War Factory (завод)
- Ore Refinery (переработка)

**Gameplay:**
- Building placement system (сетка)
- Valid/Invalid placement feedback
- Construction animation (build-up)
- Power system (basic)
- Building selection

**Цель:** Можно построить базу!

### ⏳ Week 4 — Basic Units + Selection
**Требует:** Здания готовы
**Создаём первых юнитов:**

**3D Assets:**
- Rifleman (пехота)
- Engineer (инженер)
- Harvester (харвестер)
- Light Tank (танк)

**Gameplay:**
- Unit production через Barracks/War Factory
- Marquee selection (рамка выделения)
- Groups (1-9)
- Right-click move
- Unit healthbars
- Rally points для зданий

**Цель:** Можно производить юниты и управлять ими!

### Week 5 — Economy System
**Требует:** Harvester юнит готов
- Ore nodes на карте (уже есть из Week 2.5!)
- Harvester AI:
  - Find nearest ore
  - Gather animation
  - Return to Refinery
  - Offload resources
- Resource counter UI (деньги)
- Building costs (тратим деньги)
- Income visualization

**Цель:** Полная экономическая система работает!

### Week 6 — Combat
- Weapons/projectiles; damage; stances; basic VFX/audio.

### Week 7 — Fog of War
- Shroud/explored; team vision; perf checks.

### Week 8 — Full UI (Sidebar, Minimap, etc)
**Требует:** Базовый геймплей работает
- Sidebar (RA2 стиль):
  - Building tabs
  - Unit production queue
  - Powers/Superweapons
- Command Card (bottom):
  - Unit portrait
  - Actions/abilities
  - Health/veteran status
- Minimap:
  - SceneCapture2D
  - Unit blips
  - Revealed areas
  - Click-to-move
- Hotkeys system (Q-E-R для вкладок)

**Цель:** Полноценный RA2 UI!

### Week 9 — Skirmish AI
- Build orders; scouting; attack waves; difficulty tuning.

### Week 10 — AI Asset Pipeline Expansion (перенесено на Week 2.5-6)
**ИЗМЕНЕНИЕ:** AI Pipeline запущен РАНЬШЕ для лучшей визуализации
- ~~Text/Image→3D; retopo/UV; materials import; common presets.~~
- **ВМЕСТО:** Batch-генерация оставшихся ассетов (Phase 2-3)
- Advanced техника, авиация, спецюниты
- Декорации и props
- Вариации и эффекты

### Week 11 — Polish & Perf
- LODs/Nanite; Mass for crowds; profiling; data balance pass.

### Week 12 — Build & Docs
- Menus/options/saves; packaging; course write-up and handoff.

### Acceptance Criteria
- Playable skirmish: build base, harvest, produce, fight vs AI, win/lose.
- FPS >= 60 on target hardware; clean content structure; editable data.

---

## 📊 Текущий прогресс (2025-10-04)

**Завершено:**
- ✅ Week 1: Project & Inputs
- ✅ Week 2: RA2 Camera (включая все 4 края Edge Panning)

**В работе:**
- 🔄 Week 2.5: Map Conversion + Core UI
  - 🗺️ Конвертация 1 карты из RA2 (см. RA2_MAP_CONVERSION_GUIDE.md)
  - 🎮 Main Menu + Skirmish Setup
  - 🖱️ RA2 Cursor (все состояния)
  - ComfyUI setup (ждём совета знакомого для Week 3)

**Следующее:**
- ⏳ Week 3: Base Buildings (5 зданий через AI Generation)
- ⏳ Week 4: Basic Units (4 юнита) + Selection system

**Отклонение от плана:**
- ✅ **ПОЛОЖИТЕЛЬНОЕ:** Полная реорганизация под "gameplay-first" подход
- ✅ **Изменение:** Сначала карта + меню + UI, потом ассеты
- ✅ **Причина:** Создать играбельный скелет сразу, наполнять постепенно
- ✅ **Эффект:** Можно "играть" с первых недель, добавляя фичи итеративно
- ✅ **Использование оригинала:** Карты и UI ресурсы из RA2 (легально!)

**Общая скорость:**
- 📈 **Хорошая!** 2 недели плана за ~3 недели реальной работы
- 🎯 Движемся в правильном направлении

---

## 🔄 Обновлённая стратегия

### Параллельная разработка:

**НОВАЯ СТРАТЕГИЯ: Gameplay-First Approach**

**Phase 1: Игровой скелет (Week 2.5)**
- ✅ Карта из RA2
- ✅ Меню и UI shell
- ✅ Курсор RA2 стиль
- = Можно запустить и полетать!

**Phase 2: База (Week 3)**
- 5 базовых зданий (AI Generation)
- Building placement system
- = Можно построить базу!

**Phase 3: Юниты (Week 4)**
- 4 базовых юнита (AI Generation)
- Selection + Movement
- = Можно производить и управлять!

**Phase 4: Экономика (Week 5)**
- Harvester AI
- Resource gathering
- = Полный gameplay loop!

**Phase 5: Бой (Week 6)**
- Weapon systems
- Combat mechanics
- = Можно воевать!

**Phase 6+: Expansion**
- Больше юнитов/зданий
- AI противник
- Доп. механики

**Преимущества нового подхода:**
- ✅ **Играбельно с Week 2.5** - можно запустить через меню!
- ✅ **Реальная RA2 карта** - правильный масштаб и layout
- ✅ **RA2 флейвор сразу** - меню и курсор создают атмосферу
- ✅ **Итеративное наполнение** - каждую неделю добавляется gameplay
- ✅ **Легальное использование** - карты и UI из оригинала можно!
- ✅ **Меньше рисков** - базовая структура работает, остальное - контент





# Week 2.5 - Детальный Action Plan

## 🎯 Цель Week 2.5
Создать **играбельный скелет игры**: можно запустить через меню, выбрать карту, полетать камерой по реальной RA2 карте с RA2 курсором!

---

## 📋 3 ГЛАВНЫХ ЗАДАЧИ

### ✅ Задача 1: Конвертировать карту из RA2
### ✅ Задача 2: Создать меню (Main + Skirmish Setup)
### ✅ Задача 3: RA2 Cursor с анимациями

---

## 🗺️ ЗАДАЧА 1: Конвертация карты из RA2

### Шаг 1.1: Выбор карты (15 мин)

**Критерии выбора:**
- Небольшая (2-4 игрока)
- Разнообразный terrain
- Хорошо сбалансирована
- Популярная в мультиплеере

**Рекомендуемые карты:**
- **"Tour of Egypt"** - 4 игрока, симметричная, разнообразная
- **"Heck Freezes Over"** - 2 игрока, простая, отличная для теста
- **"Dust Devil"** - 4 игрока, пустыня
- **"Country Swing"** - 2 игрока, temperate

**Где взять карты:**
1. Из установленной RA2 (папка Maps)
2. Скачать с https://www.ppmforums.com/ (community maps)
3. Из Mental Omega mod (улучшенные карты)

**Действие:**
```
1. Найти папку: C:\Program Files\Red Alert 2\Maps\
2. Выбрать .map файл (например: toureg01.map)
3. Скопировать в: E:\VFX_AI_Dev\RA2_Maps\
```

---

### Шаг 1.2: Установка FinalAlert 2 (30 мин)

**FinalAlert 2** - официальный редактор карт RA2

**Скачать:**
- https://www.moddb.com/games/cc-red-alert-2/downloads/finalalert-2
- Или: https://cnc.fandom.com/wiki/FinalAlert_2

**Установка:**
```
1. Скачать FinalAlert2.exe
2. Установить в: C:\FinalAlert2\
3. Настроить пути к RA2 (при первом запуске)
4. Проверить - открывается ли карта
```

**Альтернатива - FinalSun (для Tiberian Sun формата):**
Если нужен FinalSun: https://www.ppmforums.com/viewtopic.php?t=38989

---

### Шаг 1.3: Экспорт heightmap (30 мин)

**Цель:** Получить heightmap (карту высот) для UE5 Landscape

**Метод A: Через FinalAlert2** (рекомендую)

```
1. Открыть карту в FinalAlert2
2. File → Export → Heightmap
3. Format: 16-bit RAW или PNG
4. Resolution: 1017x1017 (RA2 карты обычно 64x64 клетки)
5. Save as: TourEgypt_Height.raw
```

**Метод B: Вручную через скрипт** (если export не работает)

Python скрипт для парсинга .map файла:
```python
# E:\VFX_AI_Dev\scripts\ra2_map_parser.py
# (Создам отдельный скрипт если нужно)
```

**Что делать с heightmap:**
```
Сохранить в: E:\UE_red_alert_2_v001\UE_RTS_Course\Content\Maps\Heightmaps\
```

---

### Шаг 1.4: Извлечение информации о ресурсах (30 мин)

**Из .map файла нам нужно:**
- Ore/Gem locations (координаты месторождений)
- Starting positions (точки старта игроков)
- Water bodies (водоёмы)
- Cliffs (обрывы)

**Метод:**
```
1. Открыть .map файл в текстовом редакторе
2. Найти секции:
   [Ore]
   [Gems]
   [StartingLocations]
   
3. Записать координаты в таблицу:
   Ore1: X=50, Y=30
   Ore2: X=120, Y=80
   ...
```

**Или через FinalAlert2:**
```
1. View → Show Ore
2. View → Show Gems
3. View → Starting Positions
4. Скриншот или ручная запись координат
```

---

### Шаг 1.5: Импорт в UE5 Landscape (1-2 часа)

**Создание Landscape:**

```
1. В UE5 Editor:
   Landscape Mode (Shift+2)

2. Import from File:
   - Heightmap File: TourEgypt_Height.raw
   - Width: 1017 (или автоопределение)
   - Height: 1017
   - Scale: Z: 100 (начальное значение, потом tweaking)

3. Material:
   - Пока используй простой M_Ground материал
   - Или импортируй текстуры из RA2 (см. ниже)

4. Location:
   - X: 0, Y: 0, Z: 0 (центр мира)

5. Create Landscape
```

**Tweaking высоты:**
```
Если landscape слишком плоский или слишком гористый:
1. Landscape Mode → Sculpt
2. Flatten tool - выровнять базу
3. Smooth tool - сгладить резкие перепады
```

---

### Шаг 1.6: Размещение Ore Nodes (1 час)

**Создать Blueprint: BP_OreNode**

```
Components:
- Static Mesh (кристалл/руда)
- Sphere Collision (для detection)
- Variables:
  - OreAmount (Integer) = 3000
  - OreType (Enum: Ore, Gem)

Визуализация (временно):
- Cube с оранжевым material (для Ore)
- Cube с синим material (для Gem)
```

**Разместить на карте:**
```
1. По координатам из .map файла
2. Конвертировать координаты RA2 → UE5:
   UE_X = (RA2_X - MapWidth/2) * CellSize * 100
   UE_Y = (RA2_Y - MapHeight/2) * CellSize * 100
   
   Где CellSize = 256 (стандарт RA2)
   
3. Ручная расстановка по скриншоту из FinalAlert2
```

---

### Шаг 1.7: NavMesh Setup (30 мин)

```
1. Place → Volumes → Nav Mesh Bounds Volume

2. Resize to cover всю карту:
   Scale: (MapSize/2, MapSize/2, 500)

3. Press 'P' для визуализации NavMesh

4. Проверить walkable areas (зелёные)

5. Adjust settings если нужно:
   Project Settings → Navigation Mesh
   - Agent Radius: 50 (для юнитов)
   - Agent Height: 200
```

---

### Шаг 1.8: Lighting Setup (30 мин)

**Directional Light (солнце):**
```
1. World Outliner → Light Source (уже есть)

2. Details:
   - Mobility: Stationary
   - Intensity: 3.0-5.0
   - Light Color: slight warm (255, 250, 240)
   
3. Rotation (для изометрии):
   - Yaw: 315° (северо-запад)
   - Pitch: -45° (сверху под углом)
   - Roll: 0°
   
   Это даёт освещение как в RA2!
```

**Sky Light:**
```
1. Place → Lights → Sky Light

2. Details:
   - Source Type: Captured Scene
   - Intensity: 1.0
   - Recapture Scene (кнопка)
```

**Post Process Volume:**
```
1. Place → Visual Effects → Post Process Volume

2. Details:
   - Infinite Extent: Checked
   - Exposure:
     - Method: Manual
     - Exposure Compensation: 0.0
   - Bloom:
     - Intensity: 0.5 (subtle)
```

---

### Шаг 1.9: Тестирование карты (15 мин)

```
1. Place BP_RTS_CameraPawn на карту
2. Set as Player Start
3. PIE (Play)

Проверить:
✅ Камера летает нормально
✅ Edge panning работает
✅ Landscape выглядит хорошо
✅ Ore nodes видны
✅ NavMesh покрывает карту (Press 'P')
✅ Освещение хорошее
```

**Готово! Карта работает!** 🗺️✅

---

## 🎮 ЗАДАЧА 2: Создать меню

### Шаг 2.1: Main Menu UI (2-3 часа)

**Создать Widget: WBP_MainMenu**

```
1. Content Browser → Right-click → User Interface → Widget Blueprint
2. Name: WBP_MainMenu

3. Canvas Panel (root)
   ├─ Image (Background)
   │   └─ (RA2 menu background или простой градиент)
   │
   ├─ Vertical Box (Buttons)
   │   ├─ Button (Skirmish)
   │   ├─ Button (Settings)
   │   └─ Button (Exit)
   │
   └─ Text Block (Game Title)
       └─ "Red Alert 2 Remake" (или твоё название)
```

**Styling (RA2 стиль):**

```
Fonts:
- Title: Bold, 72pt, красный/оранжевый
- Buttons: Bold, 36pt, жёлтый

Button Style:
- Normal: Серая рамка
- Hovered: Жёлтая рамка
- Pressed: Оранжевая рамка

Colors:
- Background: Dark (черный/серый градиент)
- Accent: RA2 red/orange (#FF6600)
```

**Blueprint Logic:**

```
Event Graph:

On Skirmish Button Clicked:
  → Open Level "SkirmishSetup"

On Settings Button Clicked:
  → Open Widget WBP_Settings (создашь позже)

On Exit Button Clicked:
  → Quit Game
```

---

### Шаг 2.2: Skirmish Setup Menu (2-3 часа)

**Создать Widget: WBP_SkirmishSetup**

```
Canvas Panel (root)
├─ Image (Background)
│
├─ Horizontal Box (Main Layout)
│   ├─ Vertical Box (Left - Map Preview)
│   │   ├─ Image (Map Thumbnail)
│   │   └─ Text Block (Map Name)
│   │
│   └─ Vertical Box (Right - Settings)
│       ├─ Text Block ("Players:")
│       ├─ Player Slot 1 (ComboBox: Human/AI/Closed)
│       ├─ Player Slot 2
│       ├─ Player Slot 3
│       ├─ Player Slot 4
│       ├─ Text Block ("Starting Credits:")
│       ├─ Slider (5000 - 50000)
│       └─ Button (START GAME)
│
└─ Button (BACK to Main Menu)
```

**Blueprint Logic:**

```
On Start Game Clicked:
  1. Save game settings to GameInstance:
     - SelectedMap
     - PlayerSetups (array)
     - StartingCredits
  
  2. Open Level (selected map name)
     → e.g., "TourEgypt"

On Back Button Clicked:
  → Open Level "MainMenu"
```

---

### Шаг 2.3: In-Game UI Shell (1 час)

**Создать Widget: WBP_InGameHUD**

```
Canvas Panel (root)
├─ Horizontal Box (Top Bar)
│   ├─ Text Block (Credits: $10000)
│   ├─ Text Block (Power: 100/200)
│   └─ Text Block (Time: 00:00)
│
├─ Canvas Panel (Sidebar - Right side)
│   └─ Border (placeholder)
│       └─ Text Block ("Sidebar - Coming Soon")
│
└─ Canvas Panel (Command Card - Bottom)
    └─ Border (placeholder)
        └─ Text Block ("Command Card - Coming Soon")
```

**Blueprint Logic:**

```
Event Construct:
  1. Get Player Controller
  2. Hide hardware cursor (будем использовать custom)

Event Tick:
  1. Update Credits display
  2. Update Power display
  3. Update Time
```

**Добавить в GameMode:**

```
BP_RTS_GameMode → Event BeginPlay:
  1. Create Widget: WBP_InGameHUD
  2. Add to Viewport
```

---

### Шаг 2.4: Level Flow Setup (30 мин)

**Создать Level: MainMenu**

```
1. File → New Level → Empty Level
2. Save as: Content/Maps/MainMenu

3. Add:
   - Player Start
   - BP_MenuCameraPawn (статичная камера)

4. Level Blueprint:
   Event BeginPlay:
     1. Create Widget: WBP_MainMenu
     2. Add to Viewport
     3. Set Input Mode: UI Only
     4. Show Mouse Cursor
```

**Создать Level: SkirmishSetup**

```
1. File → New Level → Empty Level
2. Save as: Content/Maps/SkirmishSetup

3. Similar setup с WBP_SkirmishSetup
```

**Создать Game Level: TourEgypt**

```
1. Твоя конвертированная карта
2. Save as: Content/Maps/TourEgypt

3. Level Blueprint:
   Event BeginPlay:
     1. Create Widget: WBP_InGameHUD
     2. Add to Viewport
     3. Set Input Mode: Game and UI
     4. Hide Mouse Cursor (custom cursor вместо)
```

**Project Settings:**

```
Maps & Modes:
- Editor Startup Map: MainMenu
- Game Default Map: MainMenu
- Server Default Map: TourEgypt

This way игра всегда starts from Main Menu!
```

---

## 🖱️ ЗАДАЧА 3: RA2 Cursor

### Шаг 3.1: Извлечение cursor sprites из RA2 (1 час)

**Способ A: Из игры напрямую**

```
1. Найти папку RA2: C:\Program Files\Red Alert 2\

2. Cursor файлы в:
   - mouse.shp (основные курсоры)
   - Или в .mix архивах

3. Tool для извлечения: XCC Mixer
   - Download: https://xhp.xwis.net/
   - Open local.mix или mouse.mix
   - Extract cursor sprites
```

**Способ B: Скриншоты из игры**

```
1. Запустить RA2
2. Alt+Tab в Paint/Photoshop
3. Захватить курсор (специальный tool нужен)
4. Crop каждое состояние
```

**Способ C: Воссоздать в AI** (рекомендую!)

```
ComfyUI Prompt для курсора:

"game cursor icon, RTS style, green arrow pointer, 
Red Alert 2 aesthetic, isometric game cursor, 
crisp pixel art style, transparent background, 
64x64 pixels, professional game UI"

States:
1. Default - серая стрелка
2. Move - зелёная стрелка
3. Attack - красный прицел
4. Select - желтая рамка
5. Build - молоток/конструкция
6. No-Go - красный X
```

---

### Шаг 3.2: Импорт в UE5 (30 мин)

```
1. Folder: Content/UI/Cursors/

2. Import PNG files:
   - Cursor_Default.png
   - Cursor_Move.png
   - Cursor_Attack.png
   - Cursor_Select.png
   - Cursor_Build.png
   - Cursor_NoGo.png

3. Texture Settings для каждого:
   - Compression: UserInterface2D
   - MipMapGen: NoMipmaps
   - Never Stream: True
```

---

### Шаг 3.3: Hardware Cursor Setup (1 час)

**Создать C++ или Blueprint класс: CursorManager**

```
Variables:
- CurrentCursorState (Enum: Default, Move, Attack, Select, Build, NoGo)
- CursorTextures (Map: State → Texture2D)

Functions:
- SetCursorState(NewState)
  1. CurrentCursorState = NewState
  2. Get Texture from Map
  3. Set Hardware Cursor (Widget or Platform)

- UpdateCursorBasedOnHover()
  1. Raycast from mouse
  2. Hit Actor:
     - Unit (friendly) → Select
     - Unit (enemy) → Attack
     - Ground → Move
     - Invalid → NoGo
     - Building spot → Build
  3. SetCursorState(determined state)
```

**Интеграция в Player Controller:**

```
BP_RTS_PlayerController:

Event Tick:
  1. CursorManager → UpdateCursorBasedOnHover()

Event BeginPlay:
  1. Create CursorManager
  2. Load all cursor textures
  3. SetCursorState(Default)
```

---

### Шаг 3.4: Animated Cursor (опционально) (1-2 часа)

Если хочешь анимированный курсор как в RA2:

```
1. Create Flipbook из нескольких frames
2. Widget-based cursor вместо hardware
3. Update каждый frame

Или:
Use Hardware Cursor + Timer для смены frames
```

---

## 📊 Чеклист Week 2.5

### Карта:
- [ ] Выбрана карта из RA2
- [ ] FinalAlert2 установлен
- [ ] Heightmap экспортирован
- [ ] Landscape создан в UE5
- [ ] Ore nodes размещены
- [ ] NavMesh настроен
- [ ] Lighting setup (45° изометрия)
- [ ] Карта тестируется - камера летает

### Меню:
- [ ] WBP_MainMenu создан (Skirmish, Settings, Exit)
- [ ] WBP_SkirmishSetup создан (map selection, players)
- [ ] WBP_InGameHUD создан (top bar, sidebar placeholder)
- [ ] MainMenu level создан
- [ ] SkirmishSetup level создан
- [ ] Level flow работает (Main → Setup → Game)
- [ ] Project Settings: Default Map = MainMenu

### Курсор:
- [ ] Cursor sprites извлечены/созданы (6 states)
- [ ] Импортированы в UE5
- [ ] CursorManager реализован
- [ ] Hardware cursor работает
- [ ] Cursor меняется based on context
- [ ] Анимация (опционально)

---

## ⏱️ Оценка времени

**Карта:** 4-6 часов
- Выбор + setup tools: 1 час
- Экспорт + импорт: 2 часа
- Ore nodes + NavMesh: 1 час
- Lighting + tweaking: 1-2 часа

**Меню:** 5-7 часов
- Main Menu: 2-3 часа
- Skirmish Setup: 2-3 часа
- In-Game HUD shell: 1 час
- Level flow: 30 мин - 1 час

**Курсор:** 2-4 часа
- Извлечение/создание sprites: 1-2 часа
- Импорт + setup: 1 час
- CursorManager: 1-2 часа

**ИТОГО: 11-17 часов работы**

**Реально:** 
- 1 полный день (8-10 часов) - карта + базовое меню
- 1 день (6-8 часов) - доделка меню + курсор
- = **2-3 дня работы** (если по 6-8 часов в день)

---

## 🎯 Результат Week 2.5

После завершения у тебя будет:

✅ **Запускаемая игра!**
- Main Menu → Skirmish Setup → Game Level

✅ **Реальная RA2 карта**
- С правильным scale
- Ore nodes размещены
- NavMesh готов

✅ **RA2 UI флейвор**
- Меню в стиле RA2
- Курсор меняется contextually
- In-game HUD scaffold

✅ **Готовность к Week 3**
- Можно добавлять здания
- Building placement будет работать
- Механики можно тестировать

---

## 🚀 Что дальше (Week 3)

После Week 2.5 начинаем Week 3:
1. AI Generation: 5 базовых зданий
2. Building placement system
3. Construction визуализация

И уже **можно будет строить базу** в игре! 🏗️

---

## ❓ Вопросы?

1. **Какую карту выбрать?**
   - Рекомендую: "Heck Freezes Over" (простая 2v2)
   - Или: "Tour of Egypt" (4 игрока, разнообразная)

2. **Нужна помощь с FinalAlert2?**
   - Создам отдельный гайд если нужно

3. **Cursor - извлекать или генерить?**
   - Рекомендую: Генерить через AI (быстрее и легально)

4. **Сколько времени планируешь?**
   - Лучше растянуть на 2-3 дня по 6-8 часов
   - Не торопись - это foundation!

Готов начать! 🎮

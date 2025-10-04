# Week 3 - Buildings Generation Pipeline

## 🎯 Цель Week 3
Создать **5 базовых зданий** через AI Generation и реализовать **building placement system**

**Результат:** Можно построить базу в игре! 🏗️

---

## 🤖 AI Tools Stack (рекомендация знакомого)

### Для концептов: **FLUX (любая версия)**
- **Flux.1-dev** - лучшее качество (рекомендую для первых зданий)
- **Flux.1-schnell** - быстрее, для итераций

### Для 3D моделей: **Hunyuan 3D 2.5 + Hitem3D**

**Инструменты подтверждены! ✅**

#### Hunyuan 3D 2.5 (Tencent)
- **GitHub:** https://github.com/Tencent/Hunyuan3D-2
- **Paper:** https://arxiv.org/abs/2411.17788
- **Особенности:**
  - Text-to-3D и Image-to-3D
  - High-quality mesh generation
  - Open-source!
  - Локальный запуск (требует GPU)

#### Hitem3D
- **Сайт:** https://hitem3d.com/
- **Особенности:**
  - Image-to-3D специализация
  - AI-Powered generator
  - Web-based (онлайн)
  - Качественные game-ready модели

---

## 📋 5 ЗДАНИЙ ДЛЯ WEEK 3

### Priority List:
1. **Construction Yard** - главное здание (3x3)
2. **Power Plant** - электростанция (2x2)
3. **Barracks** - казарма для пехоты (2x2)
4. **War Factory** - завод для техники (3x3)
5. **Ore Refinery** - переработка ресурсов (3x2)

---

## 🎨 WORKFLOW: Concept → 3D → UE5

### ЭТАП 1: Генерация концептов (Flux)

#### Setup Flux в ComfyUI:

**Модели для скачивания:**

```
Flux.1-dev:
- URL: https://huggingface.co/black-forest-labs/FLUX.1-dev
- Размер: ~23GB
- Куда: E:\VFX_AI_Dev\repos\ComfyUI\models\unet\

Дополнительно:
- CLIP (T5-XXL): ~9GB
- VAE: ~335MB
Куда: E:\VFX_AI_Dev\repos\ComfyUI\models\clip\ и .../vae/
```

**Базовый workflow Flux в ComfyUI:**

```
Nodes:
1. Load Diffusion Model (UNETLoader)
   - unet_name: flux1-dev.safetensors

2. Load CLIP (DualCLIPLoader)  
   - clip_name1: t5xxl_fp16.safetensors
   - clip_name2: clip_l.safetensors

3. Load VAE (VAELoader)
   - vae_name: ae.safetensors

4. CLIP Text Encode (Positive Prompt)
5. CLIP Text Encode (Negative Prompt)

6. Empty Latent Image
   - width: 1024
   - height: 1024
   - batch_size: 4

7. KSampler
   - steps: 20-30
   - cfg: 3.5-4.5
   - sampler: euler
   - scheduler: simple

8. VAE Decode

9. Save Image
```

---

#### Промпты для зданий (RA2 стиль):

**1. Construction Yard (3x3):**
```
professional 3D game asset, military construction facility building,
large industrial structure with crane and construction equipment,
isometric view 45 degree angle, concrete and metal materials,
blue team color accents on doors and trim, realistic military base style,
Red Alert 2 game aesthetic, white background, detailed industrial facade,
pipes and vents, command center building, game-ready model,
HD render, clean edges, no terrain

Negative:
blurry, low quality, cartoon, multiple views, side view,
text, watermark, shadows on ground, people, vehicles
```

**2. Power Plant (2x2):**
```
industrial power plant building 3D model, large smokestacks emitting smoke,
cooling towers, electrical infrastructure, isometric 45 degree view,
concrete structure with metal accents, blue team color trim,
realistic power generation facility, Red Alert 2 aesthetic,
white background, detailed pipes and industrial equipment,
game asset, clean render, HD quality

Negative: Same as above
```

**3. Barracks (2x2):**
```
military barracks building 3D model, rectangular concrete structure,
training facility for soldiers, blue team color door and windows,
antenna on roof, military base aesthetic, isometric view 45 degrees,
realistic army barracks style, Red Alert 2 game look,
white background, detailed military architecture,
game-ready asset, clean edges, HD render

Negative: Same as above
```

**4. War Factory (3x3):**
```
heavy industrial war factory building 3D model, vehicle production facility,
large metal structure with big garage doors, industrial crane visible,
isometric 45 degree angle, steel and concrete construction,
blue team color industrial trim, realistic military factory aesthetic,
Red Alert 2 style, white background, detailed industrial design,
smoke stacks and ventilation, game asset, HD quality render

Negative: Same as above
```

**5. Ore Refinery (3x2):**
```
ore processing refinery building 3D model, resource refinement facility,
industrial structure with ore silos and processing equipment,
conveyor systems visible, large storage tanks, isometric view 45 degrees,
concrete and metal industrial aesthetic, blue team color accents,
realistic mining facility style, Red Alert 2 game look,
white background, detailed industrial machinery, game-ready model, HD render

Negative: Same as above
```

---

#### Generation Process:

```
Для каждого здания:

1. Generate 4-8 variants (batch_size: 4-8)
2. Review and select best 2-3
3. Refine selected (img2img if needed)
4. Remove background (BiRefNet у тебя есть!)
5. Save final concept in high res

Output folder:
E:\VFX_AI_Dev\outputs\RA2_Buildings\Concepts\
- ConYard_v1.png, ConYard_v2.png, etc.
- PowerPlant_v1.png, etc.
```

**Время:** 30-60 мин на здание = 2.5-5 часов на все 5

---

### ЭТАП 2: Image-to-3D (Hunyuan 3D 2.5 / Hitem3D)

**У тебя два отличных варианта!**

#### Вариант A: Hunyuan 3D 2.5 (Локально, Бесплатно) ⭐ рекомендую!

**GitHub:** https://github.com/Tencent/Hunyuan3D-2

**Установка:**
```bash
# В отдельной папке
cd E:\VFX_AI_Dev\repos\
git clone https://github.com/Tencent/Hunyuan3D-2.git
cd Hunyuan3D-2

# Создать venv
python -m venv venv
venv\Scripts\activate

# Установить зависимости
pip install -r requirements.txt
pip install torch torchvision --index-url https://download.pytorch.org/whl/cu121
```

**Скачать модели:**
```
Hugging Face: https://huggingface.co/tencent/Hunyuan3D-2

Modели (~8-12GB):
- hunyuan3d_v2_std.pt (standard)
- hunyuan3d_v2_lite.pt (быстрее, чуть хуже качество)

Куда: E:\VFX_AI_Dev\repos\Hunyuan3D-2\weights\
```

**Запуск:**
```bash
# Image-to-3D
python run_img23d.py \
  --image_path E:\VFX_AI_Dev\outputs\RA2_Buildings\Concepts\ConYard_v1.png \
  --output_dir E:\VFX_AI_Dev\outputs\RA2_Buildings\3D_Raw\ \
  --device cuda \
  --resolution 1024

# Результат: .obj + .mtl + textures
```

**Плюсы:**
- ✅ Бесплатный!
- ✅ Локальный (твоя 4090 справится отлично!)
- ✅ Open-source
- ✅ Высокое качество от Tencent

**Минусы:**
- ⚠️ Требует setup
- ⚠️ Генерация ~5-10 минут на модель

---

#### Вариант B: Hitem3D (Онлайн, Простой)

**Сайт:** https://hitem3d.com/

**Workflow:**
```
1. Зарегистрироваться на сайте
2. Upload concept image
3. Settings:
   - Quality: High
   - Style: Realistic/Game Asset
   - Output: OBJ or FBX

4. Generate (3-5 минут)
5. Download результат
```

**Pricing:** 
- Проверить на сайте (обычно freemium модель)
- Возможно credits/subscription

**Плюсы:**
- ✅ Очень простой (веб-интерфейс)
- ✅ Быстрая генерация
- ✅ Не требует локального setup

**Минусы:**
- ⚠️ Требует интернет
- ⚠️ Возможно платный (проверь pricing)

---

#### Вариант C: Комбинированный подход ⭐⭐ (рекомендую!)

**Стратегия:**
1. **Первое здание:** Hunyuan 3D 2.5 (проверить качество, setup)
2. **Если качество ОК:** Использовать Hunyuan для всех
3. **Если нужно лучше:** Hitem3D для важных зданий

**Output folder:**
```
E:\VFX_AI_Dev\outputs\RA2_Buildings\3D_Raw\
├── Hunyuan\
│   ├── ConYard_hunyuan.obj
│   ├── PowerPlant_hunyuan.obj
│   └── ...
└── Hitem\
    ├── ConYard_hitem.obj
    └── ...
```

---

#### ComfyUI Integration (опционально):

**Для Hunyuan 3D 2.5:**
```
Можно создать custom node для ComfyUI:
1. Load Image (concept) 
2. Run Python script (call Hunyuan)
3. Wait for generation
4. Save 3D Model

Или проще: запускать через command line
```

**Для Hitem3D:**
```
Если есть API (проверить на сайте):
- API key integration
- Batch processing
```

---

**Время:** 10-20 мин на модель = 1-2 часа на все 5

---

### ЭТАП 3: Cleanup в Blender

**Для каждой модели:**

```
1. Import GLB/FBX

2. Inspection:
   - Poly count (target: 2000-8000 triangles)
   - UV layout (должны быть!)
   - Materials check

3. Cleanup:
   - Remove artifacts
   - Fix normals (Shift+N)
   - Check for floating vertices
   - Merge close vertices

4. Scale Check:
   - Construction Yard: ~1500 UE units (15m)
   - Power Plant: ~1000 UE units (10m)
   - Barracks: ~1000 UE units
   - War Factory: ~1500 UE units
   - Refinery: ~1200 UE units

5. Pivot Point:
   - Set to bottom center (для placement)
   - Origin to 3D Cursor (Shift+Ctrl+Alt+C)

6. Export FBX:
   - Apply Transform: YES
   - Forward: -Y Forward
   - Up: Z Up
   - Scale: 1.0

Output:
E:\VFX_AI_Dev\outputs\RA2_Buildings\3D_Clean\
```

**Blender Addons помогут:**
- **Quad Remesher** (~$100) - если нужна retopology
- **UV Packmaster** (~$50) - оптимизация UV

**Время:** 30-60 мин на модель = 2.5-5 часов на все 5

---

### ЭТАП 4: Import в UE5

#### Import Settings:

```
Для каждой модели:

1. Drag & Drop FBX в Content/Art/Buildings/[BuildingName]/

2. Import Settings:
   - Import as: Static Mesh
   - Auto Generate Collision: NO (сделаем вручную)
   - Generate Lightmap UVs: YES (Channel 1)
   - Combine Meshes: NO
   - Import Materials: YES
   - Import Textures: YES

3. После импорта:
   - Check Scale (должен быть правильный)
   - Check Materials (применились ли текстуры)
   - Check UV Channels (0 = diffuse, 1 = lightmap)
```

**Folder Structure:**
```
Content/Art/Buildings/
├── ConstructionYard/
│   ├── SM_ConstructionYard.uasset
│   ├── M_ConstructionYard.uasset
│   └── T_ConstructionYard_*.uasset
├── PowerPlant/
├── Barracks/
├── WarFactory/
└── Refinery/
```

---

#### Collision Setup:

```
Для каждого Static Mesh:

1. Open Static Mesh Editor
2. Collision → Auto Convex Collision
   - Hull Count: 4-8
   - Max Hull Verts: 32
   - Hull Precision: 0.5

3. Test collision (Show → Simple Collision)
4. Adjust если нужно

Или вручную:
Collision → Add Box Simplified Collision
- Размер под footprint здания
```

---

#### Material Setup:

**Master Material: M_Building_Master**

```
Create Material:

Features:
- Base Color (texture)
- Normal Map
- Roughness/Metallic
- Team Color mask (для blue/red/yellow/green команд)
- Damage state (опционально, позже)

Parameters:
- TeamColorTint (Linear Color)
- MetallicValue (Scalar)
- RoughnessValue (Scalar)
- NormalStrength (Scalar)

Instances:
- MI_ConstructionYard
- MI_PowerPlant
- MI_Barracks
- MI_WarFactory  
- MI_Refinery

For each: Set TeamColorTint = Blue (0, 0.4, 1.0)
```

---

#### Building Blueprints:

**Base Class: BP_Building_Base**

```
Components:
- Static Mesh Component
- Box Collision (для selection)
- Health Component
- Team Component
- Widget Component (healthbar, опционально)

Variables:
- BuildingName (String)
- MaxHealth (Float) = 1000
- CurrentHealth (Float) = 1000
- TeamID (Integer) = 0
- BuildingType (Enum: Base, Production, Defense, Economy)
- GridFootprint (Vector2D) - e.g., (3, 3) for ConYard
- PowerConsumption (Float)
- PowerProduction (Float) - для Power Plant
- IsConstructed (Boolean) = false

Functions:
- TakeDamage(Amount)
- Repair(Amount)
- OnDestroyed()
- GetFootprint() → Array of grid cells
```

**Child Blueprints:**

```
BP_ConstructionYard (child of BP_Building_Base)
- GridFootprint: (3, 3)
- MaxHealth: 2000
- PowerConsumption: -50
- Can build other buildings

BP_PowerPlant
- GridFootprint: (2, 2)
- MaxHealth: 800
- PowerProduction: +100

BP_Barracks
- GridFootprint: (2, 2)
- MaxHealth: 1000
- PowerConsumption: -20
- Can train infantry units

BP_WarFactory
- GridFootprint: (3, 3)
- MaxHealth: 1500
- PowerConsumption: -30
- Can build vehicles

BP_Refinery
- GridFootprint: (3, 2)
- MaxHealth: 1200
- PowerConsumption: -40
- Harvester unload point
```

**Время импорта + setup:** 30-45 мин на здание = 2.5-4 часа на все 5

---

## 🏗️ BUILDING PLACEMENT SYSTEM

### Grid System:

**Create BP_GridManager:**

```
Variables:
- GridCellSize (Float) = 256.0 (2.56 meters)
- GridWidth (Integer) = 200
- GridHeight (Integer) = 200
- OccupiedCells (Map: Vector2D → BP_Building_Base)

Functions:
- WorldToGrid(Vector3 WorldPos) → Vector2D GridPos
- GridToWorld(Vector2D GridPos) → Vector3 WorldPos
- IsCellOccupied(Vector2D GridPos) → Boolean
- CanPlaceBuilding(Vector2D GridPos, Vector2D Footprint) → Boolean
- OccupyCells(Vector2D GridPos, Vector2D Footprint, Building)
- FreeCells(Vector2D GridPos, Vector2D Footprint)
```

---

### Placement Ghost System:

**Create BP_PlacementGhost:**

```
Components:
- Static Mesh (building preview)
- Material: Translucent (green = valid, red = invalid)

Variables:
- TargetBuilding (Class Reference)
- IsValidPlacement (Boolean)
- GridPosition (Vector2D)

Event Tick:
1. Get Mouse World Position (raycast from camera)
2. Convert to Grid Position
3. Snap to Grid
4. Check CanPlaceBuilding()
5. Update Material (green/red)
6. Update Transform

On Left Click (if IsValidPlacement):
1. Spawn TargetBuilding at GridPosition
2. GridManager → OccupyCells()
3. Destroy Ghost
4. Play construction animation/sound
```

---

### Construction Animation:

**Buildup Effect (RA2 style):**

```
Method A: Material Animation
- Dissolve shader from bottom to top
- Use Timeline + Material Parameter

Method B: Mesh Scaling
- Scale Z: 0.0 → 1.0 over 5-10 seconds
- Plus particle effects (sparks, dust)

Method C: Skeletal Mesh (advanced)
- Animated buildup in Blender
- Import as Skeletal Mesh
```

---

### UI Integration:

**Sidebar Building Selection:**

```
WBP_BuildingSidebar:

Components:
- Tab Buttons (Buildings, Defense, etc.)
- Grid of Building Icons
  - Icon: Building thumbnail
  - Cost: Display credits needed
  - Hotkey: Display key (Q, W, E, etc.)

On Building Icon Click:
1. Check if affordable (Credits >= Cost)
2. If YES:
   - Create Placement Ghost
   - Set Cursor to Build mode
3. If NO:
   - Play error sound
   - Show "Insufficient Credits" message
```

**Integration in WBP_InGameHUD:**
```
Add WBP_BuildingSidebar to right side
Position: X=1700, Y=200 (for 1920x1080)
```

---

## 📊 Чеклист Week 3

### Концепты (Flux):
- [ ] Flux.1-dev установлен в ComfyUI
- [ ] Workflow создан и протестирован
- [ ] Construction Yard: 2-3 концепта готовы
- [ ] Power Plant: 2-3 концепта
- [ ] Barracks: 2-3 концепта
- [ ] War Factory: 2-3 концепта
- [ ] Refinery: 2-3 концепта

### 3D Models (Hyn2.5/Hitem):
- [ ] Tools setup (нужна info от знакомого!)
- [ ] Construction Yard: 3D модель
- [ ] Power Plant: 3D модель
- [ ] Barracks: 3D модель
- [ ] War Factory: 3D модель
- [ ] Refinery: 3D модель

### Blender Cleanup:
- [ ] Все 5 моделей почищены
- [ ] Poly count оптимизирован (2k-8k)
- [ ] UV layout проверен
- [ ] Pivot points установлены
- [ ] Экспортированы в FBX

### UE5 Integration:
- [ ] Все 5 моделей импортированы
- [ ] Collision setup для всех
- [ ] Materials созданы (Master + 5 Instances)
- [ ] Team Color работает
- [ ] BP_Building_Base создан
- [ ] 5 Child Blueprints созданы

### Gameplay Systems:
- [ ] BP_GridManager создан и работает
- [ ] BP_PlacementGhost функционирует
- [ ] Valid/Invalid placement визуализация
- [ ] Construction animation (хотя бы простая)
- [ ] Building sidebar UI
- [ ] Hotkeys для зданий

### Testing:
- [ ] Можно выбрать здание в sidebar
- [ ] Placement ghost появляется
- [ ] Snap to grid работает
- [ ] Valid/invalid detection работает
- [ ] Building появляется после клика
- [ ] Collision работает правильно

---

## ⏱️ Оценка времени Week 3

**AI Generation:**
- Flux setup: 1-2 часа (если ещё не установлен)
- Концепты (5 зданий): 2.5-5 часов
- 3D generation setup: 1-2 часа (+ info от знакомого)
- 3D генерация: 1-2 часа

**Cleanup & Import:**
- Blender cleanup: 2.5-5 часов (30-60 мин каждое)
- UE5 import + materials: 2.5-4 часа

**Gameplay Systems:**
- BP_Building_Base: 1-2 часа
- Grid Manager: 2-3 часа
- Placement System: 3-4 часа
- UI Sidebar: 2-3 часа
- Construction animation: 1-2 часа

**Testing & Polish:**
- Integration testing: 2-3 часа
- Bug fixes: 1-3 часа

**ИТОГО: 21-36 часов работы**

**Реально:**
- 3-4 полных дня (по 8-10 часов)
- Или 5-6 дней (по 4-6 часов)

---

## 🚀 План действий

### День 1: AI Generation
- Утро: Setup Flux (если нужно)
- День: Генерация концептов всех 5 зданий
- Вечер: Review и selection лучших

### День 2: 3D Generation
- Утро: Setup Hyn2.5/Hitem (с помощью знакомого)
- День: Генерация 3D всех 5 зданий
- Вечер: Blender cleanup (начать)

### День 3: Import & Systems
- Утро: Finish Blender cleanup
- День: Import в UE5 + materials
- Вечер: Start Building Blueprints

### День 4: Gameplay Systems
- Утро: Grid Manager
- День: Placement System
- Вечер: UI Sidebar

### День 5: Polish & Testing
- Весь день: Testing + bug fixes + polish

---

## ✅ ИНСТРУМЕНТЫ ПОДТВЕРЖДЕНЫ!

**Hunyuan 3D 2.5:**
- ✅ GitHub: https://github.com/Tencent/Hunyuan3D-2
- ✅ Open-source, бесплатный
- ✅ Локальный запуск (4090 идеальна!)
- ✅ High quality mesh generation

**Hitem3D:**
- ✅ Сайт: https://hitem3d.com/
- ✅ Web-based, простой интерфейс
- ⚠️ Проверить pricing на сайте

**Рекомендация:**
- Начать с Hunyuan 3D 2.5 (бесплатно!)
- Hitem3D как запасной вариант
- Сравнить качество на первом здании

---

## 🎯 Результат Week 3

После завершения у тебя будет:

✅ **5 готовых 3D зданий в игре**
- Construction Yard
- Power Plant
- Barracks
- War Factory
- Refinery

✅ **Рабочий Building Placement System**
- Grid snapping
- Valid/invalid feedback
- Construction process

✅ **UI для строительства**
- Sidebar с иконками
- Hotkeys
- Cost display

✅ **Можно построить базу!** 🏗️

И готовность к Week 4: добавить юниты и производство! 🚀

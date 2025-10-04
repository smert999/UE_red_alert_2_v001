# Maps & Environment - Red Alert 2 Style

## 🗺️ Проблема
Мы спланировали юниты и здания, но **забыли про карты и окружение**!

RTS игре нужно:
- Terrain (местность)
- Props (деревья, камни, декорации)
- Resource nodes (месторождения руды)
- Water (вода)
- Textures (текстуры земли)
- Lighting (освещение)

---

## 🎨 Стиль окружения Red Alert 2

### Типы местности (Biomes):
1. **Temperate** (умеренный) - трава, деревья
2. **Snow** (снег) - заснеженные поля
3. **Desert** (пустыня) - песок, скалы
4. **Urban** (городской) - асфальт, разрушенные здания
5. **Lunar** (лунный) - опционально для космических миссий

### Ключевые элементы окружения:
- **Ore/Tiberium fields** (месторождения ресурсов)
- **Cliffs** (скалы, обрывы)
- **Trees** (деревья - хвойные, лиственные)
- **Rocks** (камни разных размеров)
- **Water** (реки, озёра)
- **Bridges** (мосты)
- **Destroyed vehicles/buildings** (обломки)
- **Props**: заборы, бочки, ящики

---

## 🛠️ UE5 Tools для создания карт

### 1. Landscape (основа местности)
**Что делает:**
- Создаёт terrain (холмы, равнины)
- Painting текстур (трава, песок, грязь)
- Sculpting (лепка рельефа)

**Для RA2:**
- Относительно плоская местность (изометрия!)
- Небольшие холмы для тактики
- Чёткие границы карты

---

### 2. Foliage System (растительность)
**Что делает:**
- Массовое размещение деревьев/кустов
- Автоматический LOD
- Performance-friendly

**Для RA2:**
- Деревья небольшими группами
- Камни и валуны
- Кусты для декора

---

### 3. Water System (вода)
**Опции в UE5:**
- **Water Plugin** (встроенный, отличное качество)
- Static water planes (для простых карт)

**Для RA2:**
- Реки и озёра
- Naval units могут там плавать (если добавим флот)

---

### 4. Lighting (освещение)
**Для RA2 изометрии:**
- Directional Light под углом ~45° (как камера)
- Мягкие тени
- Постоянное время суток (полдень обычно)

---

## 📋 Что нужно создать

### Приоритет 1: Базовый Temperate набор

#### Terrain Textures (4-6 текстур):
1. **Grass** (трава) - основная поверхность
2. **Dirt** (грязь) - дороги, тропинки
3. **Sand/Gravel** (песок/гравий) - вариации
4. **Rock** (камень) - скалы
5. **Mud** (грязь влажная) - возле воды
6. **Cliff** (обрыв) - вертикальные поверхности

#### Props (10-15 моделей):
1. **Pine Tree** (сосна) - 2-3 варианта высоты
2. **Oak Tree** (дуб) - 2-3 варианта
3. **Bush** (куст) - маленький, средний
4. **Rock Small** (камень малый) - 3 варианта
5. **Rock Large** (камень большой) - 2 варианта
6. **Boulder** (валун) - 2 варианта
7. **Grass Clump** (пучок травы) - для детализации
8. **Ore Node** (месторождение руды) - ресурсный узел!

#### Structures (опционально):
9. **Destroyed Tank** (обломки танка)
10. **Wooden Fence** (деревянный забор)
11. **Concrete Barrier** (бетонный барьер)
12. **Oil Drum** (бочка)
13. **Wooden Crate** (ящик)

---

### Приоритет 2: Дополнительные Biomes

После базового Temperate добавить:

#### Snow Biome:
- Snow texture (снег)
- Frozen water (лёд)
- Snow-covered trees (заснеженные деревья)
- Ice rocks

#### Desert Biome:
- Sand texture
- Cacti (кактусы)
- Desert rocks
- Dunes (дюны)

#### Urban Biome:
- Asphalt texture
- Concrete
- Destroyed buildings
- Street props

---

## 🤖 AI Generation для Props

### Workflow для деревьев/камней:

**Вариант A: AI Image-to-3D** (как юниты)
```
1. ComfyUI: Generate concept art
   Prompt: "game asset, pine tree, isometric view 45 degrees,
   realistic bark texture, detailed foliage, white background"

2. TripoSR/Tripo API: Convert to 3D

3. Blender: Cleanup, optimize

4. UE5: Import, setup LODs
```

**Вариант B: Procedural + AI Textures** (быстрее)
```
1. Blender: Простое дерево через Sapling addon

2. AI: Генерация bark/leaf текстур

3. Apply textures in Blender

4. Export to UE5
```

**Вариант C: Quixel Megascans** ⭐ (самое простое!)
```
- UE5 Bridge: Огромная библиотека бесплатных ассетов!
- Деревья, камни, трава уже готовы
- RA2 стиль: можно найти подходящие или слегка модифицировать
```

---

## 🗺️ Создание первой карты

### Test Map (для Week 3-4):

**Размер:** 2048x2048 units (маленькая карта)

**Состав:**
1. **Flat Landscape** базовая основа
2. **Grass texture** painting
3. **NavMesh** для движения юнитов
4. **Small hills** (2-3 холма для тактики)
5. **Trees** (10-20 деревьев группами)
6. **Rocks** (5-10 камней)
7. **Ore fields** (2-3 месторождения)
8. **Lighting setup** (солнце под 45°)

**Цель:** Тестировать Selection, Movement, Pathfinding

**Время создания:** 2-3 часа

---

### Production Map 1 (для Week 5-6):

**Размер:** 4096x4096 units (средняя карта)

**Состав:**
- Более детальный terrain
- Разнообразие текстур
- Water body (озеро или река)
- Больше props
- Starting positions (2-4 игрока)
- Resource distribution (сбалансированные месторождения)

**Время:** 6-10 часов

---

## 📊 Roadmap Integration

### Где добавить в существующий план:

**Week 2.5 (текущая):**
- ✅ Setup базового Landscape
- ✅ Import/Create 3-5 базовых props (деревья, камни)
- ✅ Создать Test Map

**Week 3:**
- Расширить Test Map
- Добавить NavMesh Bounds
- Ore nodes placement

**Week 4-5:**
- Production Map 1
- Больше props (10-15)
- Water system setup

**Week 6:**
- Environment VFX (листья, пыль)
- Ore mining visual feedback

**Week 7+:**
- Дополнительные biomes
- Bigger maps
- Environmental hazards

---

## 🎨 AI-Assisted Environment Creation

### Текстуры Terrain:

**Через AI:**
```
ComfyUI Workflow:
1. Generate seamless textures
   Prompt: "seamless grass texture, top-down view, game texture,
   realistic grass blades, 4k, tileable, PBR ready"

2. Generate matching Normal/Roughness maps

3. Import to UE5 as Material
```

**Или готовые источники:**
- **Quixel Megascans** (бесплатно для UE5)
- **Polyhaven** (бесплатные PBR текстуры)
- **TextureHaven** (бесплатно)

---

### Props (деревья, камни):

**AI Generation:**
```
Concept → TripoSR → Blender → UE5
(тот же workflow как для юнитов)
```

**Промпт для дерева:**
```
realistic pine tree 3d model, game asset, isometric view 45 degrees,
detailed bark texture, green needles, straight trunk, white background,
game-ready low-poly model, clean render
```

**Промпт для камня:**
```
large boulder rock 3d model, realistic stone texture, moss patches,
isometric 45 degree view, game asset, white background, detailed surface,
low-poly game-ready
```

---

### Ore/Resource Nodes:

**Специфично для RA2:**
```
Концепт:
"glowing ore crystal cluster, game asset, isometric view,
blue/green crystalline structure, sci-fi mineral deposit,
Red Alert 2 style, white background, game-ready model"

Вариации:
- Ore (золотая руда) - жёлто-оранжевый
- Gems (кристаллы) - синий/зелёный
- Rich deposit (богатое) - больше кристаллов
```

---

## 🛠️ Workflow: Создание Test Map

### Шаг 1: Landscape Setup (30 мин)

```
1. UE5 → Landscape Mode
2. Create New Landscape:
   - Section Size: 63x63
   - Sections Per Component: 1x1
   - Number of Components: 8x8
   - Overall Resolution: 505x505
   - Total Size: ~2km x 2km

3. Sculpt Mode:
   - Flatten большую часть (изометрия!)
   - 2-3 небольших холма

4. Paint Mode:
   - Base: Grass texture
   - Paths: Dirt texture
```

---

### Шаг 2: Material Setup (30 мин)

```
1. Create Landscape Material:
   M_Landscape_Temperate

2. Layers:
   - Grass (base)
   - Dirt (layer 1)
   - Rock (layer 2)
   - Gravel (layer 3)

3. Auto-landscape features:
   - Slope-based rock placement
   - Height-based transitions
```

---

### Шаг 3: Props Placement (1 час)

```
1. Foliage Mode

2. Add Static Meshes:
   - SM_Pine_Tree_01 (плотность: low)
   - SM_Rock_Medium (плотность: medium)
   - SM_Bush_01 (плотность: high)

3. Paint forests/rock clusters

4. Manual placement:
   - Ore nodes (resource spots)
   - Large boulders (tactical blockers)
```

---

### Шаг 4: NavMesh (15 мин)

```
1. Nav Mesh Bounds Volume
   - Покрыть всю карту
   - Exclude water areas

2. Press 'P' to visualize

3. Check walkable areas (green)
```

---

### Шаг 5: Lighting (30 мин)

```
1. Directional Light:
   - Rotation: (315°, -45°, 0°) [Yaw, Pitch, Roll]
   - Intensity: 3.0
   - Color: slight warm tint

2. Sky Light:
   - Intensity: 1.0
   - Real-time capture

3. Post Process Volume:
   - Exposure: Fixed at 1.0
   - Bloom: Subtle
```

---

## 📋 Asset List для окружения

### Минимальный набор (Phase 1):

**Terrain Textures (готовые или AI):**
- [ ] Grass (трава) - 2048x2048
- [ ] Dirt (грязь) - 2048x2048
- [ ] Rock (камень) - 2048x2048

**Props (3D models):**
- [ ] Pine Tree (сосна) - 1 вариант
- [ ] Rock Medium (камень средний) - 1 вариант
- [ ] Bush (куст) - 1 вариант
- [ ] Ore Node (руда) - ВАЖНО для экономики!

**Total: 7 ассетов** (3 текстуры + 4 модели)

---

### Расширенный набор (Phase 2):

**Добавить:**
- [ ] Oak Tree (дуб) - 2 варианта
- [ ] Rock Small (камень малый) - 2 варианта
- [ ] Rock Large (валун) - 1 вариант
- [ ] Grass Clumps (пучки травы)
- [ ] Sand texture
- [ ] Water material

**Total: +8 ассетов**

---

## 🎯 Рекомендации

### Вариант A: Quixel Megascans ⭐ (самый быстрый)

**Плюсы:**
- ✅ Бесплатно для UE5
- ✅ Огромная библиотека готовых ассетов
- ✅ Высокое качество
- ✅ Прямая интеграция в UE5

**Минусы:**
- ⚠️ Реалистичный стиль (может не совсем RA2)
- ⚠️ Тяжёлые модели (нужна оптимизация)

**Время:** Test Map за 2-3 часа!

---

### Вариант B: AI Generation (уникальный стиль)

**Плюсы:**
- ✅ Точный RA2 стиль
- ✅ Уникальные ассеты
- ✅ Полный контроль

**Минусы:**
- ⚠️ Дольше (как и с юнитами)
- ⚠️ Quality control нужен

**Время:** Test Map за 6-8 часов (с генерацией props)

---

### Вариант C: Гибрид ⭐⭐ (рекомендую!)

**План:**
1. **Базовые props**: Quixel Megascans (деревья, камни)
2. **Уникальные ассеты**: AI Generation (Ore nodes, special props)
3. **Текстуры**: Mix (базовые из Polyhaven, детальные через AI)

**Плюсы:**
- ✅ Быстро получить рабочую карту
- ✅ Уникальные элементы для RA2 флейва
- ✅ Оптимальный баланс времени/качества

**Время:** Test Map за 3-4 часа

---

## ❓ Вопросы для обсуждения

1. **Какой подход выбираешь?**
   - [ ] A: Quixel Megascans (быстро)
   - [ ] B: AI Generation (уникально)
   - [ ] C: Гибрид (баланс)

2. **Приоритет карт:**
   - [ ] Создать Test Map прямо сейчас (параллельно с первым юнитом)
   - [ ] Подождать пока будет 2-3 юнита готовы

3. **Biomes:**
   - [ ] Только Temperate (зелёный) сначала
   - [ ] Сразу 2-3 biome (больше разнообразия)

4. **Water:**
   - [ ] Нужна вода на первой карте?
   - [ ] Пока без воды (добавим позже)

5. **Флот (Naval units):**
   - [ ] Планируешь добавлять корабли/подлодки?
   - [ ] Только наземные + авиация

---

## 📅 Интеграция в Timeline

**Обновлённый Week 2.5:**
```
Asset Creation Track:
- Rifleman concept/3D (юнит)
- Test Map creation (карта!) ← НОВОЕ
- 3-5 basic props (окружение) ← НОВОЕ

Result: Можем тестировать движение юнита по реальной карте!
```

**Week 3:**
```
- Selection механика
- На Test Map с деревьями/камнями!
```

**Week 5:**
```
- Economy механика
- Ore nodes на карте
- Harvester собирает ресурсы
```

---

## ✅ Action Items

Жду твоего решения по:
1. Какой подход к окружению (A/B/C)?
2. Когда создавать Test Map?
3. Нужен ли флот (влияет на water system)?

После этого обновлю ROADMAP с окружением! 🗺️

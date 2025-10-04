# AI Asset Pipeline для Red Alert 2 стиля

## 🎯 Цель
Создать графику в стиле Red Alert 2 используя AI-инструменты:
- Сохранить дух и стиль RA2
- Освежить графику современными технологиями
- Избежать нарушения авторских прав (IP-safe)

---

## 🎨 СТИЛЬ RED ALERT 2 - Ключевые особенности

### Визуальный стиль:
- **Изометрический вид** (под 45°)
- **Реалистичный militaristic стиль** (не cartoon)
- **Детализированные модели** с чёткими силуэтами
- **Яркие цветовые маркеры команд** (синий/красный/желтый)
- **Индустриальная эстетика** - металл, бетон, камуфляж
- **Эффекты:**
  - Дым от техники
  - Вспышки выстрелов
  - Взрывы с огнём
  - След от гусениц

### Технические параметры RA2:
- **Масштаб юнитов:** ~128-256 юнитов UE (2-4 метра высота)
- **Масштаб зданий:** ~512-2048 юнитов UE (8-32 метра)
- **Полигональность:** Low-poly подход (1000-5000 полигонов)
- **Текстуры:** 512-1024px (для ретро стиля)

---

## 📋 СПИСОК АССЕТОВ ДЛЯ СОЗДАНИЯ

### ПРИОРИТЕТ 1: Базовые юниты (для Week 3-4)

#### Пехота:
1. **Basic Soldier** (аналог GI/Conscript)
   - Soldier с винтовкой
   - ~128 UE units высота
   - Камуфляж + цвет команды
   
2. **Engineer** (аналог Engineer)
   - Гражданский в каске с инструментами
   - Wrench или ящик с инструментами

#### Лёгкая техника:
3. **Light Tank** (аналог Grizzly/Rhino Tank)
   - Средний танк с башней
   - Гусеницы
   - ~256 UE units длина

4. **Harvester** (аналог Ore Miner)
   - Промышленная машина с ковшом
   - Большой кузов для ресурсов

#### Базовые здания:
5. **Construction Yard** (аналог Construction Yard)
   - Индустриальное здание с краном
   - Footprint: 3x3 клетки

6. **Power Plant** (аналог Power Plant)
   - Электростанция с трубами
   - Дым из труб
   - Footprint: 2x2 клетки

7. **Barracks** (аналог Barracks)
   - Военная казарма
   - Дверь для выхода юнитов
   - Footprint: 2x2 клетки

8. **Refinery** (аналог Ore Refinery)
   - Завод для переработки
   - Площадка для harvestor'а
   - Footprint: 3x2 клетки

9. **War Factory** (аналог War Factory)
   - Завод для техники
   - Большие ворота
   - Footprint: 3x3 клетки

---

### ПРИОРИТЕТ 2: Расширенные юниты (для Week 6 - Combat)

#### Тяжёлая техника:
10. **Heavy Tank** (аналог Apocalypse/Prism Tank)
11. **Artillery** (аналог V3 Launcher)
12. **Anti-Air Vehicle** (аналог Flak Track/IFV)

#### Авиация:
13. **Attack Helicopter** (аналог Harrier/Hind)
14. **Transport Aircraft** (аналог Nighthawk)

#### Специальные юниты:
15. **Spy/Infiltrator**
16. **Sniper**
17. **Medic/Mechanic**

---

### ПРИОРИТЕТ 3: Расширенные здания

#### Оборона:
18. **Pillbox** (лёгкий бункер)
19. **Gun Turret** (башня)
20. **Tesla Coil/Prism Tower** (мощная оборона)
21. **Walls** (стены секциями)

#### Продвинутые:
22. **Radar** (радар)
23. **Tech Center** (исследовательский центр)
24. **Superweapon** (суперорудие)
25. **Airfield** (аэродром)
26. **Naval Yard** (верфь - опционально)

---

### ПРИОРИТЕТ 4: Окружение и декорации

27. **Trees** (деревья - несколько типов)
28. **Rocks** (камни/валуны)
29. **Destroyed Buildings** (руины)
30. **Props**: заборы, бочки, ящики
31. **Terrain textures**: трава, песок, снег, грязь

---

## 🤖 AI WORKFLOW: Пошаговый процесс

### ЭТАП 1: Генерация Концепт-Арта

#### Инструменты:
- **Stable Diffusion XL** (SDXL)
- **Midjourney** (если есть доступ)
- **Leonardo.ai** (альтернатива)

#### Промпты для RA2 стиля:

**Для юнитов:**
```
[UNIT TYPE], isometric view, 45 degree angle, military realistic style, 
Red Alert 2 aesthetic, detailed model, crisp silhouette, 
[COLOR] team colors, white background, concept art, game asset, 
HD, octane render, 4k
```

**Примеры:**

*Soldier:*
```
Modern military soldier with assault rifle, isometric view, 45 degree angle, 
military realistic style, Red Alert 2 aesthetic, detailed uniform, 
blue team color accents, white background, concept art, game asset, 
HD, octane render, 4k, professional lighting
```

*Light Tank:*
```
Medium battle tank with rotating turret, tracked vehicle, isometric view, 
45 degree angle, military realistic style, Red Alert 2 aesthetic, 
detailed armor plating, blue team color markings, white background, 
concept art, game asset, HD, octane render, 4k
```

*Power Plant:*
```
Industrial power plant building, large smokestacks, isometric view, 
45 degree angle, military base aesthetic, Red Alert 2 style, 
concrete and metal materials, blue team color accents, white background, 
building concept art, game asset, HD, octane render, 4k
```

#### Настройки:
- **Resolution:** 1024x1024 минимум
- **Steps:** 30-50
- **CFG Scale:** 7-12
- **Sampler:** DPM++ 2M Karras / Euler a

---

### ЭТАП 2: Image-to-3D Генерация

#### Инструменты (выбрать один):

**Вариант A: Meshy.ai** ⭐ (рекомендую)
- **Сайт:** https://www.meshy.ai/
- **Плюсы:** 
  - Отличное качество
  - Автоматическая UV развёртка
  - PBR текстуры
  - Контроль полигональности
- **Минусы:** Платная подписка (~$20/мес)

**Вариант B: TripoSR** 🆓
- **GitHub:** https://github.com/VAST-AI-Research/TripoSR
- **Плюсы:**
  - Бесплатный
  - Локальный запуск
  - Open-source
- **Минусы:**
  - Нужна GPU (8GB+ VRAM)
  - Качество хуже Meshy
  - Требует ручной UV развёртки

**Вариант C: Luma AI Genie**
- **Сайт:** https://lumalabs.ai/genie
- **Плюсы:**
  - Очень быстрая генерация
  - Хорошее качество
- **Минусы:** Платная

**Вариант D: Rodin (by Hyperhuman)**
- **Сайт:** https://hyperhuman.deemos.com/rodin
- **Плюсы:**
  - Специализация на game-ready ассетах
- **Минусы:** Платная

#### Процесс Meshy.ai:

1. **Upload концепт-арт**
2. **Настройки:**
   - Style: Realistic/Stylized (зависит от желаемого стиля)
   - Poly Count: Low (5k-10k triangles)
   - Generate PBR Textures: YES
   - Texture Resolution: 1024px
3. **Generate** (5-15 минут)
4. **Download:**
   - GLB/FBX формат
   - Включая текстуры (Albedo, Normal, Roughness, Metallic)

---

### ЭТАП 3: Чистка в Blender

#### Задачи:
1. **Импорт модели** (File → Import → FBX/GLB)
2. **Cleanup:**
   - Удалить артефакты
   - Проверить нормали (Shift+N - recalculate outside)
   - Убрать floating vertices
3. **Retopology** (если нужно):
   - Quad Remesher addon (платный)
   - Instant Meshes (бесплатный)
   - Ручная retopo (для важных ассетов)
4. **UV Check:**
   - Развернуть UV Layout
   - Убрать overlaps
   - Optimize packing
5. **LODs** (опционально):
   - Decimate modifier для LOD1, LOD2, LOD3
6. **Export:**
   - FBX для UE5
   - Apply Transform: YES
   - Scale: 1.0 (UE uses centimeters)

---

### ЭТАП 4: Импорт в Unreal Engine 5

#### Import Settings:

**Skeletal Mesh (для юнитов с анимацией):**
```
- Import Mesh: YES
- Import Textures: YES
- Import Materials: YES
- Material Import Method: Create New Materials
- Normal Import Method: Import Normals
- Auto Generate Collision: NO (сделаем вручную)
```

**Static Mesh (для зданий):**
```
- Import as Static Mesh: YES
- Auto Generate Collision: NO
- Generate Lightmap UVs: YES (Channel 1)
- Combine Meshes: NO
```

#### Папки:
```
Content/Art/
├── Units/
│   ├── Infantry/
│   │   ├── Soldier/
│   │   │   ├── SM_Soldier.uasset
│   │   │   ├── M_Soldier.uasset
│   │   │   └── T_Soldier_*.uasset
│   ├── Vehicles/
│   └── Aircraft/
├── Buildings/
│   ├── Base/
│   ├── Defense/
│   └── Production/
├── Props/
└── Environment/
```

---

### ЭТАП 5: Material Setup в UE5

#### Создание Master Material:

**M_Unit_Master:**
```
Features:
- Team Color mask (separate texture channel)
- Metallic/Roughness control
- Normal map
- Emissive для огней/экранов
- Parameters для быстрой настройки
```

**M_Building_Master:**
```
Features:
- Team Color decals
- Damage states (через blend)
- Emissive для окон/огней
- Vertex painting support
```

#### Team Colors:
```
Blue Team:   RGB(0, 100, 255)
Red Team:    RGB(255, 50, 50)
Yellow Team: RGB(255, 200, 0)
Green Team:  RGB(0, 200, 100)
```

---

### ЭТАП 6: Blueprints Setup

#### BP_Unit_Base (базовый класс юнита):
```
Components:
- Static/Skeletal Mesh
- Selection Component
- Health Component
- Team Component (ID команды)
- Movement Component (FloatingPawn или AIController)
- Audio Component (звуки юнита)

Variables:
- TeamID (Integer)
- MaxHealth (Float)
- CurrentHealth (Float)
- SelectionRadius (Float)
- MovementSpeed (Float)
```

#### BP_Building_Base (базовый класс здания):
```
Components:
- Static Mesh
- Selection Component
- Health Component
- Team Component
- Production Queue Component (опционально)
- Rally Point Component (опционально)

Variables:
- TeamID (Integer)
- MaxHealth (Float)
- CurrentHealth (Float)
- GridFootprint (Integer X, Integer Y)
- PowerConsumption (Float)
```

---

## 📊 ОЦЕНКА ВРЕМЕНИ

### На один ассет (полный цикл):

**Простой юнит** (пехота):
- Концепт-арт: 30-60 мин (итерации)
- Image-to-3D: 10-20 мин (ожидание)
- Чистка Blender: 30-60 мин
- Импорт UE5: 10 мин
- Material setup: 20-30 мин
- Blueprint setup: 30-60 мин
**ИТОГО: 2-4 часа**

**Техника** (танк, харвестер):
- Концепт-арт: 60-90 мин
- Image-to-3D: 15-30 мин
- Чистка Blender: 60-120 мин (сложнее)
- Импорт UE5: 15 мин
- Material setup: 30-60 мин
- Blueprint setup: 60-90 мин
**ИТОГО: 4-7 часов**

**Здание:**
- Концепт-арт: 60-90 мин
- Image-to-3D: 15-30 мин
- Чистка Blender: 45-90 мин
- Импорт UE5: 15 мин
- Material setup: 30-45 мин
- Blueprint setup: 45-90 мин
**ИТОГО: 3-6 часов**

### Полный комплект базовых ассетов (9 штук):
**Оптимистично:** 30-40 часов  
**Реалистично:** 50-70 часов  
**С учётом переделок:** 70-100 часов

---

## 🎯 РЕКОМЕНДУЕМАЯ СТРАТЕГИЯ

### ПЛАН A: Постепенный (рекомендую)

**Неделя 1-2: Минимальный набор**
1. Basic Soldier (2-4 часа)
2. Light Tank (4-7 часов)
3. Power Plant (3-6 часов)
4. Barracks (3-6 часов)

**Результат:** Можно тестировать Selection + Movement с визуально приятными ассетами

**Неделя 3-4: Расширение**
5. Engineer (2-4 часа)
6. Harvester (4-7 часов)
7. Refinery (4-6 часов)
8. Construction Yard (4-6 часов)

**Результат:** Добавляется экономика

**Неделя 5+: Дальнейшее развитие**
- Боевые юниты
- Оборонительные здания
- Специальные юниты

---

### ПЛАН B: Batch-генерация

**Концепт-арты всех базовых ассетов (1-2 дня):**
- Генерируем сразу 20-30 концептов
- Отбираем лучшие
- Сохраняем для последующей генерации

**3D генерация батчем:**
- Отправляем все в Meshy одновременно
- Ждём завершения (параллельно)
- Начинаем чистку

**Плюсы:** Экономия времени на переключение контекста  
**Минусы:** Дольше до первого результата

---

## 🛠️ ИНСТРУМЕНТЫ И РЕСУРСЫ

### Обязательные:
- ✅ **Stable Diffusion** (локально или онлайн)
- ✅ **Meshy.ai** или **TripoSR**
- ✅ **Blender** (бесплатный)
- ✅ **Unreal Engine 5** (уже есть)

### Опциональные:
- **Substance Painter** (для ручной доработки текстур)
- **Quixel Mixer** (бесплатный, текстуры)
- **Marmoset Toolbag** (запекание карт)

### Полезные Blender Addons:
- **Quad Remesher** (платный, $100 - отличная retopo)
- **Hard Ops / Boxcutter** (моделирование)
- **UV Packmaster** (оптимизация UV)

---

## 🚀 С ЧЕГО НАЧАТЬ ПРЯМО СЕЙЧАС

### Шаг 1: Setup AI инструментов (1-2 часа)

**Вариант A: Meshy.ai (проще)**
1. Зарегистрироваться на https://www.meshy.ai/
2. Купить подписку ($20-30/мес)
3. Протестировать на одном ассете

**Вариант B: TripoSR (бесплатно)**
1. Установить Python + CUDA
2. Клонировать GitHub repo
3. Установить зависимости
4. Протестировать

**Stable Diffusion:**
- Онлайн: https://huggingface.co/spaces/stabilityai/stable-diffusion
- Локально: Automatic1111 WebUI или ComfyUI

### Шаг 2: Первый тестовый ассет (2-4 часа)

**Выбрать простой юнит:** Basic Soldier

1. **Сгенерировать концепт** (30-60 мин):
   - 5-10 вариантов с разными промптами
   - Выбрать лучший
   
2. **Image-to-3D** (10-20 мин):
   - Загрузить в Meshy/TripoSR
   - Подождать генерации
   
3. **Blender cleanup** (30-60 мин):
   - Импорт, чистка, UV check
   
4. **Импорт в UE5** (30 мин):
   - Import, material setup
   - Разместить на карте
   - Проверить масштаб

**Результат:** Один полноценный ассет в проекте!

### Шаг 3: Оценка качества

После первого ассета:
- ✅ Устраивает качество?
- ✅ Вписывается в стиль RA2?
- ✅ Сколько времени заняло?

Корректируем workflow и продолжаем!

---

## 📋 ЧЕКЛИСТ ПЕРВОГО АССЕТА

### Подготовка:
- [ ] Установлен Stable Diffusion (онлайн или локально)
- [ ] Доступ к Meshy.ai или TripoSR setup
- [ ] Blender установлен
- [ ] Prompts для RA2 стиля подготовлены

### Генерация:
- [ ] Сгенерирован концепт-арт солдата
- [ ] Отобран лучший вариант
- [ ] Создана 3D модель через AI
- [ ] Скачан FBX/GLB файл

### Обработка:
- [ ] Импортирован в Blender
- [ ] Почищены артефакты
- [ ] Проверены нормали
- [ ] UV развёртка корректна
- [ ] Экспортирован FBX для UE5

### Интеграция:
- [ ] Импортирован в UE5
- [ ] Material применен
- [ ] Team color работает
- [ ] Масштаб корректный (~128 UE units)
- [ ] Размещён на карте для теста

### Проверка:
- [ ] Видно с камеры под изометрическим углом
- [ ] Silhouette читаемый
- [ ] Стиль соответствует RA2
- [ ] Производительность OK

---

## ❓ ВОПРОСЫ ДЛЯ УТОЧНЕНИЯ

1. **Бюджет на AI инструменты:**
   - Готов платить за Meshy.ai ($20-30/мес)?
   - Или предпочитаешь бесплатный TripoSR (сложнее, но бесплатно)?

2. **Компьютер:**
   - Есть GPU для локального Stable Diffusion?
   - Видеокарта и VRAM?

3. **Опыт с Blender:**
   - Есть базовые навыки?
   - Или нужна детальная инструкция?

4. **Приоритет:**
   - Начать с солдата (проще всего)?
   - Или с танка (более эффектно)?

---

## 🎯 ИТОГ

**План действий:**
1. Setup AI инструментов (1-2 часа)
2. Первый тестовый ассет - Basic Soldier (2-4 часа)
3. Оценка результата
4. Batch-генерация остальных базовых ассетов (30-50 часов)
5. Параллельно - разработка механик Week 3-4

**Ожидаемый результат через 2-3 недели:**
- ✅ 5-10 ассетов в стиле RA2
- ✅ Рабочий Selection + Movement
- ✅ Визуально приятный прототип

Готов начать! 🚀

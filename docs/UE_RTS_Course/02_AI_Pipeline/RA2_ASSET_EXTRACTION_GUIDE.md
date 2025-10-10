# Red Alert 2 Asset Extraction Guide

## 🎯 Цель
Извлечь оригинальные текстуры/спрайты/анимации из RA2 для использования как референсы и базы для AI апгрейда

**Дата:** 2025-10-04  
**Статус:** ✅ Работает (с синим фоном, убираем в UE5/ComfyUI)

---

## 🛠️ Инструменты

### XCC Mixer
**Назначение:** Извлечение файлов из .mix архивов  
**Download:** http://xhp.xwis.net/  
**Формат:** Извлекает .shp (Westwood SHP format)

### OS SHP Builder 3.36
**Назначение:** Конвертация .shp → PNG  
**Download:** Community sites / ModDB  
**Формат:** Экспорт кадров в PNG (с/без прозрачности)

---

## 📋 Процесс извлечения (Пошагово)

### Шаг 1: Извлечение .shp из .mix архивов

**XCC Mixer:**
```
1. Запуск: XCC Mixer.exe

2. Открыть .mix файл:
   File → Open → выбери .mix из папки RA2:
   
   Путь (пример):
   C:\Tolyak26 RePack\Command and Conquer Red Alert 2\
   
   Файлы:
   - conquer.mix (16MB) - главная графика
   - temperat.mix - terrain текстуры (temperate)
   - snow.mix - terrain (snow)
   - urban.mix - terrain (urban)
   - generic.mix - общие объекты
   - local.mix - локализация

3. Найти нужный .shp:
   Ctrl+F → поиск по имени
   
   Примеры имён:
   - mouse.shp - курсор
   - gacnst.shp - Allied Construction Yard
   - naweap.shp - Soviet War Factory
   - gaweap.shp - Allied War Factory
   - napowr.shp - Soviet Power Plant
   - gapowr.shp - Allied Power Plant
   - nahand.shp - Soviet Barracks
   - gahand.shp - Allied Barracks
   - narefn.shp - Soviet Refinery
   - garefn.shp - Allied Refinery

4. Extract:
   Select файл → правый клик → Extract
   
   Сохранить в:
   E:\VFX_AI_Dev\RA2_Extracted\SHP_Raw\
```

---

### Шаг 2: Конвертация .shp → PNG

**OS SHP Builder:**
```
1. Запуск: OS SHP Builder.exe

2. Открыть .shp:
   File → Open → выбери извлечённый .shp
   (например: mouse.shp)

3. Загрузить палитру:
   Palette → Red Alert 2 → выбери подходящую:
   
   Для курсора: mousepal.pal
   Для юнитов: unittem.pal (temperate) / unitsno.pal (snow)
   Для зданий: isotem.pal (temperate) / isosno.pal (snow)
   Для интерфейса: mousepal.pal или general UI palette

4. Экспорт в PNG:
   File → Export → SHP -> Images
   
   Настройки (автоматические в текущей версии):
   - Format: PNG (выбирается автоматом)
   - Frames: All frames
   - Use Offsets: ON (чекбокс)
   - Transparent: (недоступно в некоторых билдах)
   - Shadows: OFF для курсора/UI, ON для units/buildings

5. Выбрать папку экспорта:
   E:\VFX_AI_Dev\RA2_Extracted\PNG_WithBackground\Cursors\
   (или Buildings, Units в зависимости от типа)

6. Результат:
   Получишь PNG кадры:
   - mouse_0000.png
   - mouse_0001.png
   - mouse_0002.png
   - etc.
   
   ⚠️ С СИНИМ ФОНОМ (это нормально!)
```

---

## ⚠️ Известная проблема: Синий фон

### Почему появляется:
- OS SHP Builder не всегда корректно делает прозрачность
- Палитра RA2 использует индекс 0 (синий) как chroma key
- Экспортированные PNG имеют solid синий фон

### Решение:
**Убираем фон в следующем этапе!**
- В ComfyUI (через BiRefNet или chroma key)
- В UE5 (через Material с Masked blend)
- В Photoshop batch (Color to Alpha)

**Это не проблема - работаем с ним!** ✅

---

## 📦 Что извлекать для проекта

### Приоритет 1: Курсоры (Week 2.5)
```
File: mouse.shp
Palette: mousepal.pal
Output: ~20-30 PNG кадров (различные состояния курсора)
Размер: 64x64 или меньше
Использование: UE5 cursor system
```

### Приоритет 2: Здания (Week 3)
```
Allied Buildings:
- gacnst.shp - Construction Yard (palette: isotem.pal)
- gapowr.shp - Power Plant
- gaweap.shp - War Factory
- gahand.shp - Barracks
- garefn.shp - Refinery

Soviet Buildings:
- nacnst.shp - Construction Yard
- napowr.shp - Power Plant
- naweap.shp - War Factory
- nahand.shp - Barracks
- narefn.shp - Refinery

Output: Все кадры анимации (construction states!)
Использование: Референс для AI generation + апгрейд
```

### Приоритет 3: Юниты (Week 4)
```
Infantry:
- e1.shp - Allied Rifleman (unittem.pal)
- e2.shp - Soviet Conscript
- engineer.shp - Engineer

Vehicles:
- htnk.shp - Allied Medium Tank
- hind.shp - Soviet Attack Heli
- harv.shp - Harvester

Output: Все направления движения (8 directions × frames)
Использование: Референс для 3D generation
```

### Приоритет 4: Terrain (Week 2.5-3)
```
From temperat.mix:
- clear1.tem - grass tiles
- rough01.tem - dirt
- cliff textures
- water textures

Palette: isotem.pal

Использование: Texture reference для Landscape materials
```

### Приоритет 5: UI Elements
```
- sidebar backgrounds
- button frames
- icons
- health bars
- minimap frames

Palette: mousepal.pal or UI specific

Использование: UI design reference
```

---

## 📊 Что имеем после извлечения

### Структура папок:
```
E:\VFX_AI_Dev\RA2_Extracted\
├── SHP_Raw/                    (.shp files из XCC Mixer)
│   ├── mouse.shp
│   ├── gacnst.shp
│   └── ...
│
├── PNG_WithBackground/         (PNG с синим фоном из OS SHP Builder)
│   ├── Cursors/
│   │   ├── mouse_0000.png
│   │   ├── mouse_0001.png
│   │   └── ...
│   ├── Buildings/
│   │   ├── Allied/
│   │   │   ├── gacnst_0000.png
│   │   │   └── ...
│   │   └── Soviet/
│   │       ├── nacnst_0000.png
│   │       └── ...
│   └── Units/
│       └── ...
│
└── Palettes/                   (.pal files для референса)
    ├── mousepal.pal
    ├── unittem.pal
    ├── isotem.pal
    └── ...
```

---

## ✅ Текущий статус

**Извлечено:**
- ✅ mouse.shp → PNG кадры (с синим фоном)

**Следующее:**
- ⏳ Здания (gacnst, naweap, etc.)
- ⏳ Юниты (e1, htnk, harv, etc.)
- ⏳ Terrain tiles
- ⏳ UI elements

---

## 🔄 Следующий этап: ComfyUI Upgrade

**После извлечения PNG (с синим фоном):**
1. ComfyUI workflow для удаления фона
2. AI upscale (2x-4x)
3. Для анимаций: Frame interpolation (увеличить FPS)
4. Generate улучшенные версии

**См. следующий документ:** `COMFYUI_RA2_UPGRADE_WORKFLOW.md` (создаётся)

---

## 📝 Notes

**Legal:**
- Используем только для личного проекта
- Extracted assets как reference для AI generation
- Final assets = AI-generated (IP-safe)

**Quality:**
- Оригинальные sprites: 64x64 до 128x128
- После AI upscale: 256x256 или 512x512
- Сохраняем pixel art стиль или апгрейдим в realistic

**Format:**
- .shp (Westwood) → PNG (standard)
- Frames numbered: 0000, 0001, 0002...
- Синий фон (#0000AA/#0000FF) - ключ для chroma key

---

## 🎯 Результат

**После полного извлечения:**
- ✅ Все оригинальные RA2 ассеты в PNG
- ✅ Готовы для ComfyUI upgrade
- ✅ Референс для AI 3D generation
- ✅ База для создания улучшенной графики

**Estimated time:**
- Курсоры: 30 мин
- 10 зданий: 2-3 часа
- 20 юнитов: 3-4 часа
- Terrain/UI: 1-2 часа
**ИТОГО: 7-10 часов извлечения**

Но можно делать по мере необходимости (неделя за неделей)!

---

**Status:** В процессе (mouse.shp извлечён ✅)  
**Next:** ComfyUI upgrade workflow

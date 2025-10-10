# ComfyUI Workflow - RA2 Assets Upgrade

## 🎯 Цель
Апгрейдить извлечённые RA2 спрайты/текстуры в HD качество с сохранением стиля

**Input:** PNG с синим фоном (64x64 - 128x128)  
**Output:** HD PNG с альфой (256x256 - 512x512)

---

## 🤖 Доступные модели в твоём ComfyUI

### Проверено (установлено):
- ✅ **Wan2.1/2.2** (T2V, I2V) - для видео/анимации
- ✅ **Florence2** - captions/analysis
- ✅ **SAM2** - segmentation
- ✅ **BiRefNet** - background removal ⭐
- ✅ ControlNet (auxiliary)
- ✅ Impact Pack, KJNodes, LayerStyle

### Нужно установить:
- ⏳ **Flux.1-dev** - для upscale/enhancement
- ⏳ **ESRGAN/RealESRGAN** - для upscale (альтернатива)

---

## 🎨 WORKFLOW 1: Курсор Upgrade (Static Frames)

### Задача:
Взять mouse_0000.png (с синим фоном) → HD версия (без фона)

### ComfyUI Nodes:

```
1. Load Image
   └─► mouse_0000.png (64x64, синий фон)

2. BiRefNet Remove Background ⭐ (у тебя установлен!)
   └─► Убирает синий фон автоматически
   └─► Output: PNG с альфой

3. Upscale (выбери один):
   
   Option A: Image Upscale (встроенный)
   - Method: Lanczos/Bicubic
   - Scale: 4x (64→256)
   
   Option B: RealESRGAN (если установишь)
   - Model: RealESRGAN_x4plus
   - Scale: 4x
   
   Option C: Flux Image-to-Image (лучшее качество!)
   - Denoise: 0.3-0.5 (лёгкая переработка)
   - Prompt: "HD game cursor, crisp edges, RA2 style"
   - Scale предварительно через Upscale Node

4. Sharpen (опционально)
   └─► Для crisp edges

5. Save Image
   └─► E:\VFX_AI_Dev\RA2_Upgraded\Cursors\mouse_HD_0000.png
```

**Время на кадр:** 10-30 секунд  
**Batch:** Можно загрузить все кадры разом (Image Batch)

---

## 🎬 WORKFLOW 2: Курсор Animation (Wan2.2 I2V) ⭐

### Задача:
Создать плавную анимацию курсора из статичного кадра

### Wan2.2 Analysis:

**У тебя установлено:**
- `Wan2.2-I2V-A14B-HIGH` (Image-to-Video, high quality)
- `Wan2.2-I2V-A14B-LOW` (Image-to-Video, low noise)
- LoRAs для Wan2.2

**Можно использовать! ✅**

**Применение:**
```
Wan2.2 идеален для:
- Создание плавных переходов между кадрами курсора
- Генерация промежуточных frames (interpolation)
- Smooth animation из discrete sprites

Пример:
Input: mouse_default.png (static)
Prompt: "smooth cursor animation, subtle glow pulse, professional UI"
Output: 24-60 frames smooth animation
```

### ComfyUI Workflow (Wan2.2 I2V):

```
1. Load Image
   └─► mouse_0000.png (upgraded, без фона)

2. BiRefNet (если фон ещё есть)
   └─► Remove background

3. Wan2.2 Image-to-Video Node
   Settings:
   - Model: Wan2.2-I2V-A14B-HIGH_fp8
   - Prompt: "smooth cursor hover animation, subtle glow, 
              professional game UI, Red Alert 2 style, 
              30 frames loop, seamless"
   - Motion: Low (для курсора - минимум движения)
   - Duration: 1-2 seconds (30-60 frames @ 30fps)
   - Seed: Random or fixed

4. Video to Frames
   └─► Разбить на отдельные PNG
   └─► 30-60 кадров smooth animation!

5. Save Images (batch)
   └─► mouse_HD_anim_0000.png ... mouse_HD_anim_0059.png
```

**Преимущество Wan2.2:**
- ✅ Уже установлен!
- ✅ Создаёт плавную анимацию из 1 кадра
- ✅ Можно контролировать через промпт
- ✅ Smooth transitions

**Время:** 30-60 секунд на анимацию (30-60 frames)

---

## 🎨 WORKFLOW 3: Здания Upgrade (Multi-Frame)

### Задача:
Апгрейдить все кадры анимации постройки здания

### Подход А: Frame-by-Frame Upscale

```
1. Load Images (folder)
   └─► gacnst_0000.png ... gacnst_0050.png
   └─► Все кадры постройки

2. BiRefNet Remove Background (batch)
   └─► Убрать синий фон со всех

3. Image Upscale (batch 4x)
   └─► 64x64 → 256x256

4. (Optional) Flux img2img Enhancement
   Prompt: "HD military building construction, 
            detailed texture, Red Alert 2 aesthetic,
            isometric view, crisp edges"
   Denoise: 0.3-0.4 (сохраняем оригинал, улучшаем детали)

5. Save Images (batch)
   └─► gacnst_HD_0000.png ... gacnst_HD_0050.png
```

---

### Подход B: Video Enhancement (Wan2.2)

```
1. Frames to Video
   └─► Собрать кадры в видео (30fps)

2. Wan2.2 Video Enhancement (если есть такой режим)
   OR:
   Wan2.2 I2V для генерации промежуточных кадров
   - Input: Key frames (каждый 5-й кадр)
   - Output: Interpolated smooth animation

3. Upscale Video (через VideoHelperSuite у тебя установлен!)
   
4. Video to Frames
   └─► HD frames с smooth transitions

5. Save
```

**Wan2.2 польза:**
- Создаёт smooth transitions между кадрами
- Увеличивает FPS (30 → 60 кадров)
- Улучшает качество анимации

---

## 🔧 WORKFLOW 4: Remove Blue Background

### Специальный workflow для chroma key:

**Method A: BiRefNet** ⭐ (самый простой)
```
Load Image → BiRefNet Remove Background → Save

Плюсы:
- Автоматический (не нужен цвет ключа)
- Работает с любым фоном
- У тебя установлен!

Минусы:
- Может удалить синие детали на объекте
```

---

**Method B: Chroma Key (Custom Node)**
```
Load Image → Chroma Key Node → Save

Settings:
- Key Color: #0000FF (синий RA2)
- Tolerance: 10-20
- Edge Feather: 1-2px

Плюсы:
- Точный контроль
- Сохраняет синие детали объекта

Минусы:
- Нужен custom node (или через LayerStyle)
```

**У тебя есть LayerStyle!** Там должен быть Chroma Key.

---

**Method C: Color to Alpha (LayerStyle)**
```
Load Image → LayerStyle: Color to Alpha → Save

Settings:
- Target Color: #0000FF
- Threshold: 10-30

Самый точный для RA2 sprites!
```

---

## 📋 Рекомендуемый Pipeline

### Для курсора:

**Day 1: Static Upgrade**
```
1. BiRefNet remove bg (batch все кадры)
2. Upscale 4x (64→256)
3. Light enhancement (Flux img2img, denoise 0.3)
Time: 10-20 мин на весь курсор
```

**Day 2: Animation (optional)**
```
4. Wan2.2 I2V для smooth transitions
5. Interpolation между состояниями
Time: 30-60 мин
```

---

### Для зданий:

**Для каждого здания:**
```
1. Extract all frames (OS SHP Builder)
2. BiRefNet batch remove bg
3. Upscale 4x (64-128 → 256-512)
4. Flux img2img enhance (опционально)
5. Use как reference для 3D generation!

Time: 30-60 мин на здание
```

---

## 🎯 Wan2.2 - Стоит ли использовать?

### ДА, если:
- ✅ Хочешь smooth анимации курсора
- ✅ Нужны промежуточные кадры (interpolation)
- ✅ Upgrade видео-like последовательностей

### НЕТ, если:
- ❌ Просто upscale статичных кадров (достаточно Flux/ESRGAN)
- ❌ Нужны точные pixel-perfect sprites (Wan2.2 генерирует, может изменить детали)

### Рекомендация:
**Hybrid подход:**
- Static frames: BiRefNet + Upscale + Flux img2img
- Animations: Wan2.2 I2V для smooth transitions
- Best of both worlds! ⭐

---

## 🚀 Action Plan

### Сегодня (Курсор):
```
1. Batch export mouse.shp (все кадры)
2. ComfyUI:
   - BiRefNet remove bg
   - Upscale 4x
   - Save HD versions
3. Import в UE5 (Content/UI/Cursors/)
4. Setup hardware cursor

Time: 1-2 часа
Result: HD RA2 cursor в игре! ✅
```

### Week 3 (Здания):
```
1. Extract 5 зданий (все frames)
2. ComfyUI upgrade (batch)
3. Use как reference для Hunyuan 3D
4. Generate 3D models

Time: 3-5 часов extraction + upgrade
```

---

## 💡 Альтернатива для анимации

**Вместо Wan2.2 можно:**
- Frame interpolation (RIFE/DAIN)
- AnimateDiff (если установить)
- Или просто use оригинальные кадры (они и так хороши!)

---

## ✅ Summary

**Extraction:** XCC Mixer + OS SHP Builder ✅  
**Background Removal:** BiRefNet ⭐ или LayerStyle Chroma Key  
**Upscale:** Image Upscale или Flux img2img  
**Animation:** Wan2.2 I2V (опционально) ✅  

**Готово к созданию workflow!** 🚀

---

**Next:** Создать конкретный .json workflow для ComfyUI?

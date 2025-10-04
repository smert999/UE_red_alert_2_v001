# ComfyUI Workflow для Red Alert 2 Assets

## 🎯 Цель
Создать полный workflow в ComfyUI для генерации концепт-артов RA2 юнитов/зданий в стиле изометрии.

---

## 💻 Твой Setup

**Железо:**
- RTX 4090 24GB VRAM ⭐
- i9-14900
- 128GB RAM

**ComfyUI Path:**
- `E:\VFX_AI_Dev\repos\ComfyUI`

**Установленные Custom Nodes:**
- Florence2 (captions/analysis)
- SAM2 (segmentation)
- ControlNet
- Impact Pack
- KJNodes
- LayerStyle
- И многое другое!

---

## 📦 ЧТО НУЖНО УСТАНОВИТЬ

### 1. Checkpoint модели (выбрать один)

#### Вариант A: Flux.1-dev ⭐ (рекомендую)
```
Модель: black-forest-labs/FLUX.1-dev
Размер: ~23GB
Download: https://huggingface.co/black-forest-labs/FLUX.1-dev

Куда поместить:
E:\VFX_AI_Dev\repos\ComfyUI\models\unet\
- flux1-dev.safetensors
```

**Дополнительно для Flux:**
```
Text Encoder (CLIP):
E:\VFX_AI_Dev\repos\ComfyUI\models\clip\
- clip_l.safetensors
- t5xxl_fp16.safetensors

VAE:
E:\VFX_AI_Dev\repos\ComfyUI\models\vae\
- ae.safetensors
```

#### Вариант B: SDXL 1.0
```
Модель: stabilityai/stable-diffusion-xl-base-1.0
Размер: ~6.5GB
Download: https://huggingface.co/stabilityai/stable-diffusion-xl-base-1.0

Куда поместить:
E:\VFX_AI_Dev\repos\ComfyUI\models\checkpoints\
- sd_xl_base_1.0.safetensors
```

---

### 2. LoRA для улучшения качества (опционально)

**Для концепт-арта:**
```
Isometric LoRA:
https://civitai.com/models/83391/isometric-lora-for-sdxl

3D Render Style LoRA:
https://civitai.com/models/121121/3d-render-style-sdxl

Куда: E:\VFX_AI_Dev\repos\ComfyUI\models\loras\
```

---

### 3. TripoSR для 3D генерации

#### Установка через pip:
```powershell
# В отдельной папке (не в ComfyUI)
cd E:\VFX_AI_Dev\repos\
git clone https://github.com/VAST-AI-Research/TripoSR.git
cd TripoSR
pip install -r requirements.txt
pip install torch torchvision torchaudio --index-url https://download.pytorch.org/whl/cu121
```

#### Или используй Tripo API через ComfyUI:
```
У тебя уже установлен nodes_tripo.py в comfyui_api_nodes!
Нужен только API key от https://www.tripo3d.ai/
```

---

## 🎨 COMFYUI WORKFLOW #1: Концепт-арт юнита

### Простой Workflow (Flux.1-dev):

```
Nodes:
1. Load Checkpoint (UNETLoader)
   - unet_name: flux1-dev.safetensors

2. Load CLIP (DualCLIPLoader)
   - clip_name1: t5xxl_fp16.safetensors
   - clip_name2: clip_l.safetensors

3. Load VAE (VAELoader)
   - vae_name: ae.safetensors

4. CLIP Text Encode (Prompt) - POSITIVE
   Prompt:
   "Modern military soldier with assault rifle, isometric view, 45 degree angle,
   professional 3D render, game asset, Red Alert 2 aesthetic, detailed uniform,
   blue team color accents, white background, HD, octane render, crisp edges,
   professional studio lighting, no shadows on ground"

5. CLIP Text Encode (Prompt) - NEGATIVE
   Prompt:
   "blurry, low quality, distorted, deformed, multiple angles, side view,
   text, watermark, signature, cartoon style, anime"

6. Empty Latent Image
   - width: 1024
   - height: 1024
   - batch_size: 4 (генерим 4 варианта сразу)

7. KSampler
   - seed: random
   - steps: 20-30
   - cfg: 3.5-4.5
   - sampler_name: euler
   - scheduler: simple
   - denoise: 1.0

8. VAE Decode
   
9. Save Image
   - filename_prefix: RA2_Rifleman_
```

---

### Продвинутый Workflow с ControlNet:

**Для точного контроля позы/угла:**

```
Дополнительно:
1. Load Image (референсpose)
2. ControlNet Preprocessor (OpenPose/Depth)
3. Apply ControlNet
   - strength: 0.7-0.8
```

---

## 🎨 COMFYUI WORKFLOW #2: Batch генерация

### Для создания множества вариантов одного юнита:

```
Используй:
- Image Batch (создаём 8-16 вариантов)
- Grid Image (компилируем в сетку для выбора)
- Florence2 (автоописание лучших вариантов)
```

---

## 🤖 3D GENERATION WORKFLOW

### Вариант A: TripoSR (локальный)

**Python скрипт для batch обработки:**

```python
# E:\VFX_AI_Dev\repos\TripoSR\batch_convert.py

import os
from tsr.system import TSR
from tsr.utils import remove_background, resize_foreground, save_obj

# Paths
input_dir = "E:/VFX_AI_Dev/outputs/concepts/"
output_dir = "E:/VFX_AI_Dev/outputs/3d_models/"

# Initialize TripoSR
device = "cuda"
model = TSR.from_pretrained("stabilityai/TripoSR", device=device)

# Process all images
for img_file in os.listdir(input_dir):
    if img_file.endswith(('.png', '.jpg')):
        print(f"Processing {img_file}...")
        
        # Load and preprocess
        image = Image.open(os.path.join(input_dir, img_file))
        image = remove_background(image)
        image = resize_foreground(image, 0.85)
        
        # Generate 3D
        result = model(image)
        
        # Save mesh
        output_path = os.path.join(output_dir, img_file.replace('.png', '.obj'))
        save_obj(result, output_path)
        
        print(f"Saved: {output_path}")
```

---

### Вариант B: Tripo API через ComfyUI

**В ComfyUI добавь ноды:**

```
1. Load Image (концепт-арт)

2. Tripo API Node (из comfyui_api_nodes)
   - api_key: [твой ключ]
   - mode: image-to-3d
   - style: realistic
   - topology: quad (лучше для игр)
   - texture_resolution: 1024

3. Save 3D Model
   - format: GLB или FBX
```

---

## 📐 ПРОМПТЫ ДЛЯ RA2 АССЕТОВ

### Infantry (Пехота):

**Rifleman (Allied):**
```
professional 3d game asset, modern military soldier standing at attention,
holding assault rifle, isometric view 45 degree angle, blue uniform with
blue team color patches, realistic military style, Red Alert 2 aesthetic,
detailed texture, clean silhouette, white background, studio lighting,
HD render, game-ready model, no base, straight posture
```

**Militiaman (Soviet):**
```
professional 3d game asset, soviet military conscript soldier standing,
AK-47 rifle, red uniform accents, military cap, isometric view 45 degrees,
realistic military style, Red Alert 2 game aesthetic, detailed gear,
white background, clean edges, HD, game character model
```

---

### Vehicles (Техника):

**Medium Tank (Allied):**
```
modern battle tank 3d model, medium tank with rotating turret,
isometric view 45 degree angle, blue military color scheme with
blue team markings, realistic metal texture, tracks visible,
Red Alert 2 game style, white background, clean render,
game asset, HD, professional lighting, detailed armor plating
```

**Heavy Tank (Soviet):**
```
heavy soviet battle tank 3d model, large twin-barrel turret,
red army star marking, red team color accents, thick armor plating,
isometric 45 degree view, realistic military style, Red Alert 2 aesthetic,
white background, detailed tracks and rivets, game asset render
```

---

### Buildings (Здания):

**Power Generator:**
```
industrial power plant building, 3d game asset, large smokestacks,
concrete structure, isometric view 45 degrees, blue team color accents,
realistic industrial style, Red Alert 2 building aesthetic,
white background, detailed pipes and vents, game-ready model,
no terrain, clean render, HD
```

**Infantry Barracks:**
```
military barracks building 3d model, rectangular concrete structure,
blue team color door and trim, windows, antenna on roof,
isometric 45 degree angle, realistic military base style,
Red Alert 2 game aesthetic, white background, detailed facade,
game asset, clean edges, professional render
```

---

## 🎯 ОПТИМАЛЬНЫЕ НАСТРОЙКИ

### Для Flux.1-dev:

**Концепт-арт (высокое качество):**
```
Steps: 25-30
CFG Scale: 3.5-4.5
Sampler: euler или dpmpp_2m
Scheduler: simple
Resolution: 1024x1024
Batch: 4
```

**Быстрая генерация (итерации):**
```
Steps: 15-20
CFG Scale: 3.0
Sampler: euler
Resolution: 768x768
Batch: 8
```

---

### Для SDXL 1.0:

**Концепт-арт:**
```
Steps: 30-40
CFG Scale: 7-9
Sampler: dpmpp_2m_sde_gpu
Scheduler: karras
Resolution: 1024x1024
```

---

## 🔄 WORKFLOW ПРОЦЕСС

### День 1: Setup и тестирование

**Шаг 1: Установка моделей (1-2 часа)**
1. Скачать Flux.1-dev (~23GB) или SDXL (~6.5GB)
2. Разместить в правильные папки
3. Перезапустить ComfyUI
4. Проверить что модели загружаются

**Шаг 2: Тестовая генерация (30-60 мин)**
1. Создать простой workflow
2. Сгенерировать первый концепт (Rifleman)
3. Проверить качество
4. Tweaking промптов

---

### День 2-3: Batch генерация концептов

**Цель: 10-15 концепт-артов**

**Утро (3-4 часа):**
- Rifleman (4-8 вариантов)
- Medium Tank (4-8 вариантов)
- Power Generator (4-8 вариантов)

**Вечер (2-3 часа):**
- Выбор лучших вариантов
- Refinement (улучшение деталей)
- Подготовка для 3D конверсии

---

### День 4-5: 3D конверсия

**Вариант A: TripoSR**
```
Setup: 1-2 часа
Batch конверсия: 10-15 минут на модель
Cleanup: 30-60 минут на модель
ИТОГО: ~8-12 часов на 6 моделей
```

**Вариант B: Tripo API**
```
Setup: 15 минут
Конверсия: 5-10 минут на модель (параллельно)
Cleanup: 20-30 минут на модель
ИТОГО: ~3-5 часов на 6 моделей
```

---

## 📋 ЧЕКЛИСТ ПЕРВОЙ ГЕНЕРАЦИИ

### Подготовка:
- [ ] Flux.1-dev или SDXL установлен
- [ ] ComfyUI запускается без ошибок
- [ ] Простой workflow создан
- [ ] Промпты для Rifleman готовы

### Генерация:
- [ ] Сгенерировано 4-8 вариантов Rifleman
- [ ] Выбран лучший вариант
- [ ] Background удалён (SAM2 или BiRefNet у тебя есть!)
- [ ] Изображение сохранено в высоком разрешении

### 3D Конверсия:
- [ ] TripoSR настроен ИЛИ Tripo API ключ получен
- [ ] Концепт конвертирован в 3D
- [ ] Модель экспортирована в GLB/FBX

### Blender:
- [ ] Модель импортирована
- [ ] Артефакты почищены
- [ ] Масштаб корректный
- [ ] UV развёртка проверена

### UE5:
- [ ] Импортирован в UE5
- [ ] Material настроен
- [ ] Размещён на карте
- [ ] Тест пройден ✅

---

## 💡 СОВЕТЫ И TRICKS

### 1. Background Removal в ComfyUI

Используй BiRefNet (у тебя установлен!):
```
1. Load Image
2. BiRefNet Remove Background
3. Add White Background (или прозрачный)
4. Save Image
```

### 2. Batch Processing

Используй Image Batch ноды:
```
1. Load Images (folder)
2. Batch Processing Node
3. Save Images (auto numbering)
```

### 3. Quality Control с Florence2

После генерации используй Florence2 для автоанализа:
```
1. Load Generated Images
2. Florence2 Caption
3. Filter by quality keywords
4. Save best variants
```

---

## 🎯 ОЖИДАЕМЫЕ РЕЗУЛЬТАТЫ

### После 1 недели работы:
- ✅ Workflow отлажен
- ✅ 6-10 концепт-артов высокого качества
- ✅ 3-5 готовых 3D моделей
- ✅ 1-2 модели в UE5 готовы к тестированию

### После 2 недель:
- ✅ 15-20 концепт-артов
- ✅ 10-15 3D моделей
- ✅ 5-8 моделей в UE5
- ✅ Тестирование Selection + Movement

---

## ❓ ВОПРОСЫ ДЛЯ УТОЧНЕНИЯ

1. **Какую модель выбираешь:**
   - [ ] Flux.1-dev (лучшее качество, 23GB)
   - [ ] SDXL 1.0 (быстрее, 6.5GB)

2. **3D генерация:**
   - [ ] TripoSR (бесплатно, локально)
   - [ ] Tripo API (платно, ~$0.10-0.20 за модель)

3. **Есть опыт с созданием workflows в ComfyUI?**
   - [ ] Да, создавал раньше
   - [ ] Нет, нужна помощь

4. **Сколько времени планируешь на первую сессию?**
   - [ ] 2-3 часа (setup + первая генерация)
   - [ ] 4-6 часов (полный цикл до 3D)
   - [ ] Целый день (от концепта до UE5)

---

## 🚀 СЛЕДУЮЩИЙ ШАГ

После ответа на вопросы я создам:
1. **Готовый ComfyUI workflow** (.json файл)
2. **Детальную инструкцию** по установке моделей
3. **Batch скрипт** для TripoSR (если выберешь локальную генерацию)
4. **Список промптов** для первых 10 ассетов

Готов начать! 🎨

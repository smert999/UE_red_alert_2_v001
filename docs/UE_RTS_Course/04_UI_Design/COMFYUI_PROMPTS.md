# 🎨 ComfyUI ПРОМТЫ ДЛЯ МЕНЮ RED ALERT 2

## 📌 КАК ИСПОЛЬЗОВАТЬ

1. Открыть **ComfyUI** интерфейс
2. Выбрать **Stable Diffusion XL** или **Flux.1-dev**
3. Скопировать **PROMPT** в поле
4. Настроить **NEGATIVE PROMPT**
5. Запустить генерацию
6. Сохранить результат в `Content/UI/`

---

## 🎬 1. ФОНОВОЕ ВИДЕО/ИЗОБРАЖЕНИЕ

### Prompt: РА2 Военный фон
```
A dramatic military themed background for Red Alert 2 game menu, 
featuring futuristic Soviet and Allied soldiers marching with tanks and helicopters, 
dark red and blue color scheme, cinematic, atmospheric smoke and dust, 
industrial military aesthetic, brutalist architecture,
perfect for a modern game UI, 1920x1080, high quality, detailed
```

### Negative Prompt
```
low quality, blurry, distorted, cartoon, anime, chibi, 
text, watermark, distorted faces, deformed characters,
bright colors, cute, feminine, soft, pastel colors
```

### Параметры
```
Steps: 30-40
Sampler: DPM++ 2M Karras или Euler
CFG Scale: 7-9
Seed: random
Size: 1920x1080 (или нужное разрешение)
```

---

## 🔘 2. ТЕКСТУРА КНОПКИ (Normal state)

### Prompt: Металическая кнопка
```
A sleek dark metal button texture for UI, 
brushed steel surface with subtle reflections and beveled edges, 
professional dark gray with silver highlights,
high quality glossy finish, perfect for game interface buttons,
square shape, suitable for 300x60 pixels, photorealistic
```

### Negative Prompt
```
plastic, cartoon, low poly, pixelated, blurry, 
distorted, colorful, bright, matte, rough texture,
text, watermark, glowing, neon
```

### Параметры
```
Steps: 25-30
Sampler: DPM++ 2M Karras
CFG Scale: 8
Size: 512x256 (потом масштабировать)
```

---

## ✨ 3. СВЕЧЕНИЕ ДЛЯ HOVER (Glow effect)

### Prompt: Оранжевое свечение
```
A glowing orange radial gradient texture, 
bright neon orange (#FF8800) fading to transparent at edges,
perfect for button hover effects and UI elements,
soft glow with no harsh edges, smooth gradient,
suitable for particle effects and UI overlays, 512x512
```

### Negative Prompt
```
sharp, hard edges, blocky, pixelated, cartoon, 
text, watermark, distorted, realistic, photorealistic,
dark, blue, red, green colors
```

### Параметры
```
Steps: 20-25
Sampler: Euler
CFG Scale: 6-7
Size: 512x512
```

---

## 🖱️ 4. КУРСОР

### Prompt: Военный научно-фантастический курсор
```
A futuristic military sci-fi cursor arrow, 
glowing golden with angular design, clean and sharp pointed arrow,
Red Alert 2 style, metallic appearance with blue accents,
perfect for tactical RTS game cursor, transparent background,
isolated on white, 256x256 pixels, high quality
```

### Negative Prompt
```
cartoon, anime, soft, rounded, blurry, distorted,
colorful, plain, simple, low quality, text, watermark,
realistic, photorealistic, matte finish
```

### Параметры
```
Steps: 25-30
Sampler: DPM++ 2M Karras
CFG Scale: 8-10
Size: 256x256
```

---

## 📛 5. ЛОГОТИП RED ALERT 2

### Prompt: RA2 Логотип современный
```
Red Alert 2 official logo redesign, 
modern sleek lettering with military aesthetic,
bold futuristic font, metallic red and blue color scheme,
perfect for game menu, professional gaming logo,
high quality vector style artwork, isolated on transparent background,
400x150 pixels minimum, clean edges, no distortion
```

### Negative Prompt
```
low quality, blurry, pixelated, cartoon, anime,
distorted, deformed text, watermark, background objects,
cute, soft, rounded, playful, matte finish
```

### Параметры
```
Steps: 30-40
Sampler: DPM++ 2M Karras
CFG Scale: 9-10
Size: 800x300 (потом масштабировать)
```

---

## 🎨 6. КНОПКА HOVER STATE (Оранжевая)

### Prompt: Оранжевая металическая кнопка
```
A sleek metallic button with orange gradient overlay (#FF8800),
glowing effect with golden highlights and beveled edges,
professional dark gray with bright orange at center,
glossy finish with light reflections, button highlights,
perfect for game UI hover state, 300x60 pixels, high quality
```

### Negative Prompt
```
low quality, blurry, plastic, matte, dull,
gray, red, blue, neon, cartoon, pixelated,
distorted, text, watermark
```

### Параметры
```
Steps: 25-30
Sampler: DPM++ 2M Karras
CFG Scale: 8
Size: 512x256
```

---

## 🌟 7. БОЕВЫЙ ЗНАЧОК ДЛЯ КНОПОК

### Prompt: Боевой иконки набор
```
Four separate military game icons in retro futuristic style:
1. Skirmish icon - crossed swords/tactical symbol
2. Campaign icon - map/scroll
3. Multiplayer icon - team of soldiers
4. Settings icon - gear/cogs
Red Alert 2 style, metallic appearance, golden/red color,
perfect for 32x32 game UI buttons, isolated on transparent,
professional quality, clear details
```

### Negative Prompt
```
blurry, low quality, cartoon, anime, colorful, bright,
matte, distorted, deformed, text, watermark, 3D realistic,
complex background, cluttered
```

### Параметры
```
Steps: 30-35
Sampler: DPM++ 2M Karras
CFG Scale: 9
Size: 256x256 (потом нарезать на 4)
```

---

## 🎥 8. ФОНОВАЯ ВИДЕО АНИМАЦИЯ (для движения)

### Prompt: Анимированный фон войсков
```
Animated cinematic background of Soviet and Allied military forces,
soldiers marching with tanks and helicopters in formation,
dust and smoke effects, dramatic lighting,
dark red and blue military color scheme, brutalist scenery,
1920x1080, suitable for game menu background loop,
cinematic quality, 3-5 seconds loop animation
```

### Negative Prompt
```
cartoon, anime, chibi, low quality, pixelated,
bright colors, cute, soft, pastel, watermark, text,
person faces, realistic skin, photorealistic humans
```

### Параметры
```
Steps: 40-50 (для лучшего качества)
Sampler: Euler
CFG Scale: 7-8
Size: 1920x1080
Video frames: 24-32 (зависит от GPU)
```

---

## 📊 ТАБЛИЦА ВСЕХ ПРОМТОВ

| Элемент | Размер | Формат | Приоритет |
|---------|--------|--------|-----------|
| Фоновое видео | 1920x1080 | MP4/WebM | ⭐⭐⭐ |
| Текстура кнопки | 512x256 → 300x60 | PNG | ⭐⭐⭐ |
| Свечение (гвоу) | 512x512 | PNG | ⭐⭐⭐ |
| Курсор | 256x256 | PNG | ⭐⭐ |
| Логотип | 800x300 | PNG | ⭐⭐⭐ |
| Кнопка hover | 512x256 → 300x60 | PNG | ⭐⭐ |
| Иконки кнопок | 256x256 | PNG | ⭐⭐ |

---

## 🎯 ПОРЯДОК ГЕНЕРАЦИИ

### 1️⃣ Первоочередные (необходимые)
```
1. Фоновое видео (основной визуал)
2. Текстура кнопки (базовая кнопка)
3. Логотип (узнаваемость)
4. Свечение (hover эффект)
```

### 2️⃣ Дополнительные (улучшение)
```
5. Кнопка hover (визуальная обратная связь)
6. Иконки кнопок (удобство)
7. Курсор (профессиональность)
```

### 3️⃣ Продвинутые (полировка)
```
8. Анимированный фон (если нужно видео)
9. Particle эффекты (если есть ComfyUI VHS)
10. Дополнительные варианты
```

---

## 💡 СОВЕТЫ ДЛЯ ЛУЧШЕГО РЕЗУЛЬТАТА

1. **Использовать правильную модель**
   - SDXL лучше для деталей
   - Flux.1 лучше для реализма
   - Juggernaut для игровой графики

2. **Регулировать CFG Scale**
   - 7-9: балансовое качество
   - 10-12: больше деталей (может быть странно)
   - 5-6: более творческие результаты

3. **Экспериментировать с Samplers**
   - DPM++ 2M: стабильный результат
   - Euler: быстрее, менее стабильный
   - Karras: хорошее качество

4. **Сохранять варианты**
   - Генерировать 3-5 вариантов
   - Выбрать лучший
   - Потом редактировать в Photoshop/GIMP

5. **Масштабировать правильно**
   - Генерировать в 2x размере
   - Потом масштабировать вниз (лучше качество)
   - Использовать Lanczos3 при масштабировании

---

## 🚀 СЛЕДУЮЩИЙ ШАГ

1. Выбрать **2-3 лучших промта**
2. Запустить генерацию в ComfyUI
3. Сохранить результаты
4. Импортировать в UE5
5. Создавать UI элементы с графикой

# Edge Panning - Быстрое исправление ошибок

## 🚨 Проблема: Камера движется не в ту сторону

### Симптомы и решения:

---

## ❌ ПРОБЛЕМА 1: Нижний край → камера движется ВПРАВО (не вверх/вниз)

### Причина:
Использован **Get Right Vector** вместо **Get Forward Vector**

### Исправление:
1. Найди ноду **Get Right Vector** в логике BOTTOM edge
2. Удали её
3. Добавь ноду **Get Forward Vector**
4. Подключи:
   ```
   YawPivot → Get Forward Vector → Negate → Break Vector → ...
   ```

---

## 🎯 ПРАВИЛЬНЫЕ ВЕКТОРЫ ДЛЯ КАЖДОГО КРАЯ:

### Горизонтальное движение (Left/Right):
```
LEFT Edge:
YawPivot → Get RIGHT Vector → Negate → Break Vector → Make(Z=0) → Normalize → Add Movement

RIGHT Edge:
YawPivot → Get RIGHT Vector (без Negate) → Break Vector → Make(Z=0) → Normalize → Add Movement
```

### Вертикальное движение (Top/Bottom):
```
TOP Edge:
YawPivot → Get FORWARD Vector (без Negate) → Break Vector → Make(Z=0) → Normalize → Add Movement

BOTTOM Edge:
YawPivot → Get FORWARD Vector → Negate → Break Vector → Make(Z=0) → Normalize → Add Movement
```

---

## 📋 ТАБЛИЦА: Какой вектор использовать

| Край экрана | Вектор | Negate? | Направление камеры |
|-------------|--------|---------|-------------------|
| **LEFT** | Right Vector | ✅ ДА | Влево ← |
| **RIGHT** | Right Vector | ❌ НЕТ | Вправо → |
| **TOP** | Forward Vector | ❌ НЕТ | Вперёд ↑ |
| **BOTTOM** | Forward Vector | ✅ ДА | Назад ↓ |

---

## 🔍 КАК ПРОВЕРИТЬ ЧТО У ТЕБЯ СЕЙЧАС:

### Добавь Print String после получения вектора:

#### Для BOTTOM edge (после Get Vector):
```
Get Forward Vector → Print String("🔽 BOTTOM: Using FORWARD vector")
```

или

```
Get Right Vector → Print String("❌ BOTTOM: ERROR! Using RIGHT vector")
```

### При запуске игры:
- Подведи курсор к нижнему краю
- Посмотри какое сообщение появится
- Если видишь "ERROR! Using RIGHT" → меняй на Forward!

---

## 🛠️ ПОШАГОВОЕ ИСПРАВЛЕНИЕ BOTTOM EDGE:

### ШАГ 1: Найди проблемную ноду
В твоём Blueprint для BOTTOM edge найди ноду:
```
Get Right Vector ← ЭТА НОДА НЕПРАВИЛЬНАЯ!
```

### ШАГ 2: Удали Get Right Vector
- Кликни на неё
- Delete

### ШАГ 3: Добавь Get Forward Vector
- Потяни из **YawPivot** переменной
- В поиске пиши: "Get Forward Vector"
- Выбери **Get Forward Vector**

### ШАГ 4: Подключи Negate
```
YawPivot → Get Forward Vector → Negate (Vector)
                                    ↓
                              [дальше Break Vector...]
```

### ШАГ 5: Compile и Test
- Compile Blueprint
- Запусти PIE
- Подведи курсор к нижнему краю
- Камера должна двигаться НАЗАД (вниз по экрану)

---

## 🧪 ТЕСТИРОВАНИЕ ВСЕХ КРАЁВ:

После исправления проверь каждый край:

### LEFT край (X ≤ 15):
✅ Камера движется ВЛЕВО

### RIGHT край (X ≥ ScreenWidth - 15):
✅ Камера движется ВПРАВО

### TOP край (Y ≥ ScreenHeight - 15):
✅ Камера движется ВВЕРХ (вперёд)

### BOTTOM край (Y ≤ 15):
✅ Камера движется ВНИЗ (назад)

---

## 📊 ВИЗУАЛЬНАЯ ШПАРГАЛКА:

```
                    TOP EDGE (Y ≥ Height - 15)
                    Forward Vector (no negate)
                            ↑ камера идёт вперёд
                            │
                            │
    LEFT ←──────────────────┼──────────────────→ RIGHT
    (X ≤ 15)                │              (X ≥ Width - 15)
    Right Vec               │               Right Vector
    + Negate                │               (no negate)
                            │
                            ↓ камера идёт назад
                    BOTTOM EDGE (Y ≤ 15)
                    Forward Vector + Negate
```

---

## 🎯 ИТОГ:

### Запомни:
- **Left/Right** используют **Right Vector**
- **Top/Bottom** используют **Forward Vector**

### Negate нужен для:
- **LEFT** (Right Vector + Negate)
- **BOTTOM** (Forward Vector + Negate)

---

## ❓ Если всё равно не работает:

Напиши какие из этих сообщений видишь при тесте:

```
Print String после TOP Branch True: "🔼 TOP using Forward"
Print String после BOTTOM Branch True: "🔽 BOTTOM using Forward"
Print String после LEFT Branch True: "⬅️ LEFT using Right"
Print String после RIGHT Branch True: "➡️ RIGHT using Right"
```

И скажи **в какую сторону реально движется камера** для каждого края!

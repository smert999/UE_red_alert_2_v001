# Edge Panning - TOP и BOTTOM края (Детальная схема на русском)

## 📌 Обозначения типов пинов

```
⚪ EXEC     - белая линия (execution flow)
🔴 BOOL     - красная линия (true/false)
🟢 FLOAT    - зелёная линия (числа с точкой)
🔵 OBJECT   - синяя линия (ссылки на объекты)
🟣 INTEGER  - бирюзовая линия (целые числа)
🟡 VECTOR   - жёлтая линия (X, Y, Z координаты)
```

## 📦 Переменные (уже созданы для Left/Right):

- **EdgePanEnabled** (Boolean) = `true`
- **EdgePanBorderPx** (Integer) = `15`
- **EdgePanSpeed** (Float) = `12000.0`
- **YawPivot** (Scene Component) - ссылка на компонент

---

## 🔼 TOP EDGE - Движение камеры ВВЕРХ (Forward)

### 📍 Когда срабатывает:
Курсор мыши в верхних 15 пикселях экрана

### 📍 Как проверяем:
`MouseY >= (ViewportHeight - 15)`

---

### 🔧 ШАГЫ РЕАЛИЗАЦИИ (TOP EDGE):

#### ШАГ 1: Получить Player Controller
```
Нода: Get Player Controller
├─ Вход: Player Index = 0 🟣
└─ Выход: Return Value 🔵 (ссылка на контроллер)
```

#### ШАГ 2: Получить позицию мыши
```
Нода: Get Mouse Position
├─ Вход: Target = [ШАГ 1: Return Value] 🔵
├─ Выход: Location X 🟢 (не используем для TOP)
├─ Выход: Location Y 🟢 (ИСПОЛЬЗУЕМ!)
└─ Выход: Return Value 🔴 (успешно ли получили позицию)
```

#### ШАГ 3: Получить размер окна
```
Нода: Get Viewport Size
├─ Вход: Target = [ШАГ 1: Return Value] 🔵
├─ Выход: Size X 🟢 (не используем для TOP)
└─ Выход: Size Y 🟢 (ИСПОЛЬЗУЕМ - высота экрана!)
```

#### ШАГ 4: Конвертировать EdgePanBorderPx в Float
```
Нода: Cast To Float
├─ Вход: Input = [EdgePanBorderPx переменная] 🟣
└─ Выход: Float 🟢 (результат = 15.0)
```

#### ШАГ 5: Вычислить порог TOP края
```
Нода: - (Float Subtract)
├─ Вход A: = [ШАГ 3: Size Y] 🟢 (высота экрана, например 1080)
├─ Вход B: = [ШАГ 4: Float] 🟢 (15.0)
└─ Выход: Result 🟢 (например: 1080 - 15 = 1065)
```
💡 Это порог: если MouseY >= 1065, значит курсор у верхнего края!

#### ШАГ 6: Сравнить позицию мыши с порогом
```
Нода: >= (Float Greater or Equal)
├─ Вход A: = [ШАГ 2: Location Y] 🟢 (позиция мыши по Y)
├─ Вход B: = [ШАГ 5: Result] 🟢 (порог TOP края)
└─ Выход: Result 🔴 (true если курсор у TOP края)
```

#### ШАГ 7: Проверка - курсор у TOP края?
```
Нода: Branch
├─ Вход EXEC: ⚪ (от EdgePanEnabled Branch True)
├─ Вход: Condition = [ШАГ 6: Result] 🔴
├─ Выход: True ⚪ (ИДЁМ ДАЛЬШЕ - делаем движение!)
└─ Выход: False ⚪ (стоп, ничего не делаем)
```

---

### 🎯 ДВИЖЕНИЕ КАМЕРЫ (если Branch True):

#### ШАГ 8: Получить Forward Vector от YawPivot
```
Нода: Get Forward Vector
├─ Вход: Target = [YawPivot переменная] 🔵
└─ Выход: Return Value 🟡 (вектор направления "вперёд")
```
💡 Этот вектор показывает куда "смотрит" камера по горизонтали

#### ШАГ 9: Разобрать вектор на компоненты
```
Нода: Break Vector
├─ Вход: In Vec = [ШАГ 8: Return Value] 🟡
├─ Выход: X 🟢 (координата X)
├─ Выход: Y 🟢 (координата Y)
└─ Выход: Z 🟢 (координата Z - НЕ ИСПОЛЬЗУЕМ!)
```

#### ШАГ 10: Создать плоский вектор (Z=0)
```
Нода: Make Vector
├─ Вход: X = [ШАГ 9: X] 🟢
├─ Вход: Y = [ШАГ 9: Y] 🟢
├─ Вход: Z = вручную пиши 0.0 🟢 (ВАЖНО! Обнуляем вертикаль)
└─ Выход: Return Value 🟡 (плоский вектор направления)
```
💡 Зачем Z=0? Чтобы камера двигалась только горизонтально, не вверх-вниз!

#### ШАГ 11: Нормализовать вектор
```
Нода: Normalize
├─ Вход: A = [ШАГ 10: Return Value] 🟡
└─ Выход: Return Value 🟡 (единичный вектор длиной 1.0)
```
💡 Нормализация делает вектор единичной длины для стабильной скорости

#### ШАГ 12: Получить Delta Time
```
Нода: Get World Delta Seconds
└─ Выход: Return Value 🟢 (время между кадрами, ~0.016)
```

#### ШАГ 13: Вычислить скорость движения
```
Нода: * (Float Multiply)
├─ Вход: A = [EdgePanSpeed переменная] 🟢 (12000.0)
├─ Вход: B = [ШАГ 12: Return Value] 🟢 (Delta Time)
└─ Выход: Result 🟢 (скорость для этого кадра)
```
💡 Формула: 12000 × 0.016 ≈ 192 единицы за кадр

#### ШАГ 14: ПРИМЕНИТЬ ДВИЖЕНИЕ!
```
Нода: Add Movement Input
├─ Вход EXEC: ⚪ [ШАГ 7: Branch True]
├─ Вход: World Direction = [ШАГ 11: Return Value] 🟡
├─ Вход: Scale Value = [ШАГ 13: Result] 🟢
└─ Выход EXEC: ⚪ (продолжение выполнения)
```

---

## 🔽 BOTTOM EDGE - Движение камеры ВНИЗ (-Forward)

### 📍 Когда срабатывает:
Курсор мыши в нижних 15 пикселях экрана

### 📍 Как проверяем:
`MouseY <= 15`

---

### 🔧 ШАГИ РЕАЛИЗАЦИИ (BOTTOM EDGE):

#### ШАГ 1-4: ТОЧНО КАК В TOP
(Те же ноды: Get Player Controller, Get Mouse Position, Get Viewport Size, Cast To Float)

#### ШАГ 5: Сравнить позицию мыши с границей
```
Нода: <= (Float Less or Equal)
├─ Вход A: = [Location Y из Get Mouse Position] 🟢
├─ Вход B: = [Cast To Float результат] 🟢 (15.0)
└─ Выход: Result 🔴 (true если курсор у BOTTOM края)
```
💡 Проще чем TOP! Просто: MouseY <= 15?

#### ШАГ 6: Проверка - курсор у BOTTOM края?
```
Нода: Branch
├─ Вход EXEC: ⚪ (от EdgePanEnabled Branch True)
├─ Вход: Condition = [ШАГ 5: Result] 🔴
├─ Выход: True ⚪ (ИДЁМ ДАЛЬШЕ!)
└─ Выход: False ⚪ (стоп)
```

---

### 🎯 ДВИЖЕНИЕ КАМЕРЫ (если Branch True):

#### ШАГ 7: Получить Forward Vector
```
Нода: Get Forward Vector
├─ Вход: Target = [YawPivot переменная] 🔵
└─ Выход: Return Value 🟡
```

#### ШАГ 8: ИНВЕРТИРОВАТЬ направление!
```
Нода: Negate (Vector)
├─ Вход: A = [ШАГ 7: Return Value] 🟡
└─ Выход: Return Value 🟡 (противоположное направление!)
```
💡 ЭТО КЛЮЧЕВОЕ ОТЛИЧИЕ! Negate переворачивает вектор: Forward → Backward

#### ШАГ 9-14: ТОЧНО КАК В TOP
(Break Vector, Make Vector Z=0, Normalize, Delta Time, Multiply, Add Movement Input)

---

## 📊 СРАВНИТЕЛЬНАЯ ТАБЛИЦА:

| Параметр | TOP Edge | BOTTOM Edge |
|----------|----------|-------------|
| **Проверка мыши** | `MouseY >= (ScreenHeight - 15)` | `MouseY <= 15` |
| **Сложность проверки** | 3 ноды (subtract + compare) | 1 нода (compare) |
| **Forward Vector** | Get Forward Vector | Get Forward Vector + **Negate** |
| **Направление** | Вперёд ↑ | Назад ↓ |
| **Количество нод** | 14 штук | 15 штук (+ Negate) |

---

## 🔗 ОБЩАЯ СТРУКТУРА Event Tick:

```
Event Tick
    ⚪
    ▼
Sequence
    ├─ Then0: (пусто)
    │
    ├─ Then1: EDGE PANNING LOGIC
    │   ⚪
    │   ▼
    │   Branch (EdgePanEnabled?)
    │       ├─ False: ⚪ → (конец)
    │       └─ True: ⚪ → [ВСЕ ПРОВЕРКИ КРАЁВ]
    │           │
    │           ├─ LEFT edge logic (уже работает ✅)
    │           ├─ RIGHT edge logic (уже работает ✅)
    │           ├─ TOP edge logic (ДОБАВЛЯЕМ 🆕)
    │           └─ BOTTOM edge logic (ДОБАВЛЯЕМ 🆕)
    │
    └─ Then2: MAP BOUNDS CLAMPING
        ⚪
        (Clamp X/Y координат)
```

---

## ⚠️ КРИТИЧЕСКИ ВАЖНЫЕ МОМЕНТЫ:

### 1. Get Mouse Position vs Get Mouse Position Scaled by DPI
```
❌ НЕ ИСПОЛЬЗУЙ: Get Mouse Position Scaled by DPI
✅ ИСПОЛЬЗУЙ: Get Mouse Position

Почему? DPI scaling даёт неправильные координаты на разных мониторах!
```

### 2. Make Vector Z=0
```
❌ ОШИБКА: Использовать Break Vector.Z
✅ ПРАВИЛЬНО: Вручную поставить Z = 0.0

Почему? Forward Vector имеет наклон по Z, нам нужно движение строго горизонтально!
```

### 3. TOP vs BOTTOM - где Negate?
```
TOP: Get Forward Vector → (БЕЗ Negate) → Break Vector
BOTTOM: Get Forward Vector → Negate → Break Vector

Почему? TOP = движение вперёд, BOTTOM = движение назад!
```

### 4. Порядок выполнения
```
Все 4 края (Left, Right, Top, Bottom) должны быть в ОДНОМ Then1!
Не создавай отдельные Sequence - всё в один Then1 пихай!
```

---

## 🧪 ТЕСТИРОВАНИЕ:

### Визуальные тесты:
1. **TOP край**: Курсор вверху → камера двигается вперёд (мир опускается вниз)
2. **BOTTOM край**: Курсор внизу → камера двигается назад (мир поднимается вверх)
3. **TOP-LEFT угол**: Курсор в углу → диагональное движение вперёд-влево
4. **BOTTOM-RIGHT угол**: Курсор в углу → диагональное движение назад-вправо

### Debug Print Strings:
```
После TOP Branch True: Print String("🔼 TOP EDGE ACTIVE!")
После BOTTOM Branch True: Print String("🔽 BOTTOM EDGE ACTIVE!")
```

---

## 📋 ЧЕКЛИСТ РЕАЛИЗАЦИИ:

### TOP Edge:
- [ ] Get Player Controller
- [ ] Get Mouse Position (Location Y)
- [ ] Get Viewport Size (Size Y)
- [ ] Cast EdgePanBorderPx to Float
- [ ] Subtract: Size Y - Border
- [ ] Compare: MouseY >= Result
- [ ] Branch (at TOP edge?)
- [ ] Get Forward Vector (YawPivot)
- [ ] Break Vector
- [ ] Make Vector (Z=0.0)
- [ ] Normalize
- [ ] Get World Delta Seconds
- [ ] Multiply: Speed × Delta
- [ ] Add Movement Input

### BOTTOM Edge:
- [ ] Get Player Controller (можно переиспользовать)
- [ ] Get Mouse Position (Location Y)
- [ ] Cast EdgePanBorderPx to Float (можно переиспользовать)
- [ ] Compare: MouseY <= 15
- [ ] Branch (at BOTTOM edge?)
- [ ] Get Forward Vector (YawPivot)
- [ ] **Negate Vector!** ← НЕ ЗАБУДЬ!
- [ ] Break Vector
- [ ] Make Vector (Z=0.0)
- [ ] Normalize
- [ ] Get World Delta Seconds (можно переиспользовать)
- [ ] Multiply: Speed × Delta
- [ ] Add Movement Input

---

## ✅ ГОТОВО!

После реализации обоих краёв у тебя будет полноценный Edge Panning на все 4 стороны экрана! 🎉

Если что-то непонятно - спрашивай конкретно по шагам!


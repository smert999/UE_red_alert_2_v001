## BP_RTS_CameraPawn — пошаговая схема Blueprint

Этот файл — минимальный рецепт, чтобы собрать камеру в стиле RA2.

### 1) Components (иерархия)
- `BP_RTS_CameraPawn`
  - `SpringArm`
    - `Camera`
  - `FloatingPawnMovement`

SpringArm (Details):
- Do Collision Test = Off
- Relative Rotation (порядок в UE: X=Roll, Y=Pitch, Z=Yaw): Roll = 0, Pitch = -50, Yaw = 45

Camera (Details):
- Projection Mode = Orthographic
- Ortho Width = 20000 (чуть позже будет меняться зумом)

### 2) Project Settings → Input (Bindings)
- Axis Mappings:
  - `MoveForward`: W = +1.0; S = -1.0
  - `MoveRight`  : D = +1.0; A = -1.0
  - `Zoom`       : Mouse Wheel Axis = +1.0 (Up = +1, Down = -1)
- Action Mappings:
  - `FastPan`     : Left Shift
  - `RotateLeft`  : Q
  - `RotateRight` : E

### 3) Переменные (Variables) в Pawn
- `BasePanSpeed` (Float) = 6000
- `FastPanMultiplier` (Float) = 2.0
- `ZoomStep` (Float) = 2000
- `MinOrthoWidth` (Float) = 8000
- `MaxOrthoWidth` (Float) = 40000
- `IsFastPan` (Boolean) = false

### 4) Event Graph — блоки

4.1 Панорамирование WASD (по экрану)
- Получите угол от `SpringArm`: `Get World Rotation` → `Break Rotator` → `Make Rotator` (Roll=0, Pitch=0, Yaw = из Break)
- От `Make Rotator` возьмите:
  - `Get Forward Vector` → это «вверх экрана»
  - `Get Right Vector` → это «вправо экрана»
- Узел `InputAxis MoveForward` → `Add Movement Input`
  - World Direction = Forward Vector (можно Z=0 и Normalize)
  - Scale Value = Axis Value
- Узел `InputAxis MoveRight` → второй `Add Movement Input`
  - World Direction = Right Vector (можно Z=0 и Normalize)
  - Scale Value = Axis Value
- В `FloatingPawnMovement` можно задать Max Speed = 6000.

### FastPan (Shift) — увеличение скорости
- Map Clamp (X/Y):
  - Variables: `MinX, MaxX, MinY, MaxY`.
  - Event Tick: `GetActorLocation` → `Clamp(float)` X/Y → `Make Vector` (Z из исходного) → `SetActorLocation(Sweep=false)`.
  - Частые ошибки: Z=0 (чёрный экран), MinX/MinY забыли со знаком «−».
- Переменные: `BasePanSpeed=6000`, `FastPanSpeed=16000`, `BaseAccel=12000`, `FastAccel=36000`, `BaseDecel=12000`, `FastDecel=36000`.
- BeginPlay: `Set Max Speed=BasePanSpeed` → `Set Acceleration=BaseAccel` → `Set Deceleration=BaseDecel` (Target = `FloatingPawnMovement`).
- Action `FastPan` (Left Shift):
  - Pressed: `Set Max Speed=FastPanSpeed` → `Set Acceleration=FastAccel` → `Set Deceleration=FastDecel`.
  - Released: `Set Max Speed=BasePanSpeed` → `Set Acceleration=BaseAccel` → `Set Deceleration=BaseDecel`.

4.2 Ускорение Shift
- `InputAction FastPan (Pressed)`  → `Set Max Speed` на компоненте `FloatingPawnMovement` = `BasePanSpeed * FastPanMultiplier` (пример: 12000)
- `InputAction FastPan (Released)` → `Set Max Speed` = `BasePanSpeed` (пример: 6000)

4.3 Зум колёсиком (Ortho Width)
- Перетащите компонент `Camera` в граф (Get)
- `InputAxis Zoom` → вычислите `NewWidth`:
  - Current = `Camera → Get Ortho Width`
  - NewWidth = `Clamp( Current - AxisValue * ZoomStep, MinOrthoWidth, MaxOrthoWidth )`
  - `Camera → Set Ortho Width` = NewWidth

4.4 Поворот Q/E
- `InputAction RotateLeft`  → `Add Actor Local Rotation` (Yaw = -15)
- `InputAction RotateRight` → `Add Actor Local Rotation` (Yaw = +15)

### 5) Размещение на карте
- Перетащите `BP_RTS_CameraPawn` на уровень `Main`.
- У выделённого актора: `Auto Possess Player = Player 0`.

### 6) Проверка
- PIE/Play: WASD двигают панораму; Shift ускоряет; колесо — зум; Q/E — поворот.

### 7) На будущее
- Edge panning (движение у краёв экрана) добавим отдельным шагом после базовой проверки.



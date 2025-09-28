## RTS Camera Rig (Orthographic) — Полная перестройка под поворот вокруг центра

Этот файл — детальный план: что удалить, как собрать заново камеру с опорными узлами `YawPivot`/`PitchPivot`, какие узлы поставить в Event Graph и как их соединить. Цель — поворот вокруг центра экрана без «завала», экранное панорамирование и ортографический зум.

### 0) Что удалить/сбросить в текущем блюпринте `BP_RTS_CameraPawn`
- Удалить узлы поворота: любые `AddActorLocalRotation`, `SetRelativeRotation` на `SpringArm` из InputAction `RotateLeft/Right`.
- Оставить блок зума (Get/Set Ortho Width) — он подходит как есть.
- Блок движения WASD позже переподключим (будем брать векторы от нового `YawPivot`).
- В Components ничего не удаляем, но перенесём в новую иерархию.

### 1) Компоненты — новая иерархия (rig)
Добавьте Scene-компоненты и расставьте так:

- `YawPivot` (Scene Component) — Set as Root Component
  - `PitchPivot` (Scene Component)
    - `SpringArm`
      - `Camera`

Как создать/назначить Root: Add Component → Scene → переименовать в `YawPivot` → ПКМ по нему → Set as Root Component.

Переместите существующие `SpringArm` и `Camera` под `PitchPivot` (перетаскиванием в дереве компонентов).

Настройки (Details):
- `YawPivot`
  - Relative Location = (0, 0, 0)
  - Relative Rotation = (Roll=0, Pitch=0, Yaw=0)
- `PitchPivot`
  - Relative Location = (0, 0, 0)
  - Relative Rotation = (Roll=0, Pitch=-50, Yaw=0)
- `SpringArm`
  - Relative Location = (0, 0, 0)
  - Relative Rotation = (0, 0, 0)
  - Target Arm Length = 0 (для ортогональной камеры длина не влияет)
  - Do Collision Test = Off
  - Use Pawn Control Rotation = Off
- `Camera`
  - Relative Location = (0, 0, 0)
  - Relative Rotation = (0, 0, 0)
  - Projection Mode = Orthographic
  - Ortho Width = 20000 (пример, у вас может быть своё)

На уровне у актора: Rotation = (0, 0, 0). Высоту выставляет не актор, а обзор (Pitch) на `PitchPivot`.

### 2) Переменные
- `ZoomStep: float = 2000`
- `MinOrthoWidth: float = 8000`
- `MaxOrthoWidth: float = 40000`
- `RotateStep: float = 15`
- `CameraYaw: float = 45`
- (опционально) `CameraRef: CameraComponent` — можно не использовать, если брать компонент `Camera` напрямую

### 3) Таблицы узлов и соединений (Event Graph)

#### 3.1 Инициализация угла (BeginPlay)
- Узлы:
  - Event BeginPlay → (Exec)
  - Get `YawPivot`
  - `Get Relative Rotation` (от YawPivot)
  - `Break Rotator`
  - `Set CameraYaw` (Value = Break.Yaw)
  - `Make Rotator` (Roll=0, Pitch=0, Yaw=`CameraYaw`)
  - `Set Relative Rotation` (Target = `YawPivot`, New Rotation = Make Rotator)
- Соединения (Exec):
  - BeginPlay → Set CameraYaw → Set Relative Rotation

#### 3.2 Панорамирование WASD (экранное)
- Для MoveForward:
  - InputAxis `MoveForward` → (Exec)
  - Get `YawPivot` → `Get Forward Vector` → `Break Vector` → `Make Vector` (Z=0) → `Normalize (Vector)` → `Add Movement Input`
  - Connections:
    - Exec: InputAxis → Add Movement Input
    - World Direction: Normalize → Add Movement Input.World Direction
    - Scale Value: InputAxis.Axis Value → Add Movement Input.Scale Value
- Для MoveRight:
  - InputAxis `MoveRight` → аналогично, но `Get Right Vector` от `YawPivot`

#### 3.3 Зум (как у вас уже сделано)
- InputAxis `Zoom` (Axis Value)
- `Camera` → `Get Ortho Width`
- (Axis Value × `ZoomStep`) → (Current − Result) → `Clamp (Float)` [Min=`MinOrthoWidth`, Max=`MaxOrthoWidth`] → `Camera` → `Set Ortho Width`
- Exec: InputAxis → Set Ortho Width

#### 3.4 Поворот Q/E вокруг центра (YawPivot)
- Для Q (RotateLeft):
  - InputAction `RotateLeft` (Pressed)
  - Явный узел: `Subtract (float)` — A = `Get CameraYaw`, B = `Get RotateStep`
  - Результат → `Set CameraYaw`
  - ВАЖНО: после `Set CameraYaw` возьмите НОВЫЙ `Get CameraYaw` и подайте в Z(Yaw) у `Make Rotator` (Roll=0, Pitch=0, Yaw=`CameraYaw`)
  - `Set Relative Rotation` (Target = `YawPivot`, New Rotation = Make Rotator)
  - Порядок Exec: RotateLeft.Pressed → Set CameraYaw → Set Relative Rotation
- Для E (RotateRight):
  - InputAction `RotateRight` (Pressed)
  - Явный узел: `Add (float)` — A = `Get CameraYaw`, B = `Get RotateStep`
  - Результат → `Set CameraYaw`
  - После `Set CameraYaw` — НОВЫЙ `Get CameraYaw` → в Z(Yaw) `Make Rotator(0,0,CameraYaw)`
  - `Set Relative Rotation` (Target = `YawPivot`)
  - Порядок Exec: RotateRight.Pressed → Set CameraYaw → Set Relative Rotation

Примечание: `Pitch=-50` хранится в `PitchPivot` (не меняем в повороте); `Yaw` хранится в `YawPivot`.

### 4) ASCII‑диаграмма (компоненты)
```
BP_RTS_CameraPawn (Actor)
└─ YawPivot : SceneComponent   (Root)   ← вращаем по Yaw
   └─ PitchPivot : SceneComponent       ← фиксируем Pitch = -50
      └─ SpringArm : SpringArmComponent (Length=0, CollisionTest=Off)
         └─ Camera : CameraComponent    (Orthographic)
```

### 5) ASCII‑диаграмма (поворот Q/E, упрощённо)
```
InputAction RotateLeft.Pressed ──▶ Set CameraYaw(Value = CameraYaw - RotateStep)
                                      │
                                      ▼
                               Make Rotator(0,0,CameraYaw)
                                      │
                                      ▼
                         SetRelativeRotation(Target = YawPivot)

InputAction RotateRight.Pressed ─▶ Set CameraYaw(Value = CameraYaw + RotateStep)
                                      │
                                      ▼
                               Make Rotator(0,0,CameraYaw)
                                      │
                                      ▼
                         SetRelativeRotation(Target = YawPivot)
```

### 6) Частые ошибки и диагностика
- Поворот только по часовой: для обеих клавиш стоит `Add` — для `RotateLeft` нужен `Subtract (float)`.
- Угол не меняется/скачет: в `Make Rotator` подаётся СТАРЫЙ `CameraYaw`. После `Set CameraYaw` используйте новый `Get CameraYaw`.
- Target у `SetRelativeRotation` = `self`, а не `YawPivot`. Должен быть `YawPivot` из Components.
- В `Make Rotator` в Z(Yaw) подают 0, а не `CameraYaw`.
- Движение берёт `World Direction = (1,0,0)/(0,1,0)` вместо Forward/Right от `YawPivot`.
- Pitch меняют в повороте — Pitch фиксируется в `PitchPivot` (−50), в повороте трогаем только Yaw у `YawPivot`.
- Runtime Error `Accessed None … YawPivot`: вы используете переменную, а не компонент. Перетащите `YawPivot` ИЗ Components, удалите лишние переменные `YawPivot`, Refresh All Nodes, заново подключите `Get/Set Relative Rotation`.

### 7) Клампы по карте (ограничение X/Y)
- Переменные: `MinX, MaxX, MinY, MaxY` (float). Начните с значений вроде −50000/50000.
- Event Tick:
  - `GetActorLocation` → `Break Vector` (X,Y,Z)
  - `Clamp (Float)` для X (MinX/MaxX) и Y (MinY/MaxY)
  - `Make Vector`: X=ClampX, Y=ClampY, Z=исходный Z
  - `SetActorLocation` (Sweep=false)
- Важно: Z берите из `GetActorLocation` (не 0), иначе камера «падает» и экран чернеет.
- Отладка: если края «теряются», убедитесь, что MinX/MinY — отрицательные, а MaxX/MaxY — положительные (или заданы под вашу карту).

### 8) Тестовый Landscape (для визуальных границ)
- Modes → Landscape → New Landscape → Create (8×8 компонентов достаточно для большой площадки).
- Освещение: Directional Light + Sky Light (Real Time Capture).
- Ландшафт — только для ориентира; реальный размер мира задают переменные клампа.

### 7) Ожидаемый результат
- Q/E вращают вокруг центра экрана (YawPivot).
- WASD двигает строго по экранным осям независимо от угла.
- Зум изменяет Ortho Width в заданных пределах.



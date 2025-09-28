## Blueprints: основы (RU)

### Создание и структура
- Content Browser → Add → Blueprint Class → `Actor`/`Pawn`/`PlayerController`.
- Components: добавляйте `StaticMesh`, `Camera`, `SpringArm`, `Widget`.

### Переменные и категории
- Variables: создавайте `Boolean`, `Float`, `Vector`, `FText` и т.д.
- Отмечайте `Instance Editable` для настройки в уровне.

### События и логика
- Event BeginPlay / Tick — жизненный цикл.
- Functions/Macros — повторно используемая логика.

### Коммуникация
- Get Player Controller / Get Controlled Pawn.
- Blueprint Interfaces — контракты между классами.
- Event Dispatchers — события «наружу» (подписка/вызов).

### Отладка
- Print String (временный) → заменяйте на `Message Log`/`Screen Messages`.
- Breakpoints, Watch, Visualize values в Blueprint Debugger.



## Enhanced Input: кратко (RU)

### Включение
- Edit → Plugins → Enabled: `Enhanced Input`.

### Настройка осей и действий
- Content Browser → Add → Input → `Input Action` (IA_Move, IA_Zoom), `Input Mapping Context` (IMC_Game).
- Project Settings → Input → Default Classes (если нужно), но главное — активировать IMC в рантайме.

### Активация IMC
- В `PlayerController` (BeginPlay): `Get Local Player Subsystem (Enhanced Input)` → `Add Mapping Context` (IMC_Game, Priority=0).

### Примеры биндов
- IA_Move (1D/2D Axis): WASD или стрелки.
- IA_Zoom (Axis 1D): Mouse Wheel Up/Down.
- IA_FastPan (Action): Left Shift (Pressed/Released).





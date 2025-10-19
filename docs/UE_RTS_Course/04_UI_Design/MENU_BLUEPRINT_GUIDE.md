# МЕНЮ В BLUEPRINTS - ПОШАГОВЫЙ ГАЙД

## 📋 БЫСТРЫЙ СТАРТ

Этот гайд показывает как создать Widget Blueprints в UE5.6 для главного меню Red Alert 2.

---

## 1️⃣ СОЗДАНИЕ WBP_MainMenu

### Шаг 1: Создать Widget Blueprint

```
Content/UI/Menus/
└─ WBP_MainMenu (Widget Blueprint)
   └─ Parent Class: UserWidget
```

### Шаг 2: Структура в Designer

**Иерархия компонентов:**

```
Canvas Panel (Root)
│
├─ BackgroundContainer (Panel)
│  ├─ BackgroundImage (Image) - видео фон
│  └─ BackgroundOverlay (Image) - полупрозрачный оверлей
│
├─ CenterContent (Overlay Panel)
│  ├─ LogoContainer (VerticalBox)
│  │  ├─ LogoImage (Image)
│  │  ├─ TitleText (TextBlock) - "RED ALERT 2"
│  │  └─ SubtitleText (TextBlock) - "Remastered"
│  │
│  └─ ButtonsContainer (VerticalBox)
│     ├─ Button_Skirmish (WBP_MenuButton)
│     ├─ Button_Campaign (WBP_MenuButton)
│     ├─ Button_Multiplayer (WBP_MenuButton)
│     ├─ Button_Settings (WBP_MenuButton)
│     └─ Button_Exit (WBP_MenuButton)
│
└─ BottomInfoPanel (HorizontalBox)
   ├─ VersionText (TextBlock) - "v1.0.0"
   ├─ Spacer
   └─ SocialLinks (HorizontalBox)
      ├─ DiscordIcon (Image)
      └─ GitHubIcon (Image)
```

### Шаг 3: Настройки Canvas Panel

```
Canvas Panel Slot:
├─ Size to Content: True
├─ Anchors: 0.0 to 1.0 (Full Screen)
└─ Offset: 0
```

### Шаг 4: Фоновое изображение

**BackgroundImage:**
```
Image Widget:
├─ Brush → Texture: RA2_MainMenu_Background (или видео)
├─ Appearance → Color and Opacity: White (255, 255, 255, 255)
├─ Image Size: 1920 × 1080
├─ Aspect Ratio: 16:9
└─ Canvas Panel Slot:
   ├─ Size to Content: False
   ├─ Anchors: 0.0, 0.0 to 1.0, 1.0 (Full)
   └─ Offset: 0
```

**BackgroundOverlay:**
```
Image Widget (поверх фона):
├─ Brush → Color: Black (0, 0, 0, 100)
├─ Opacity: 0.3 (для контраста с текстом)
└─ Canvas Panel Slot:
   ├─ Anchors: 0.0, 0.0 to 1.0, 1.0 (Full)
   └─ Offset: 0
```

### Шаг 5: Логотип и заголовок

**LogoImage:**
```
Image Widget:
├─ Brush → Texture: RA2_Logo_HD
├─ Size: 400 × 200
├─ Vertical Alignment: Center
├─ Horizontal Alignment: Center
```

**TitleText:**
```
TextBlock:
├─ Text: "RED ALERT 2"
├─ Font: Exo 2 Bold, Size 80
├─ Color: Gold (255, 215, 0)
├─ Horizontal Alignment: Center
├─ Shadow Offset: (2, 2)
├─ Shadow Color: Black
└─ Justification: Center
```

**SubtitleText:**
```
TextBlock:
├─ Text: "REMASTERED"
├─ Font: Exo 2 Regular, Size 36
├─ Color: Orange (255, 140, 0)
├─ Horizontal Alignment: Center
└─ Justification: Center
```

### Шаг 6: Контейнер кнопок

**ButtonsContainer (VerticalBox):**
```
Vertical Box:
├─ Size: 400 × 600
├─ Spacing: 15 (между кнопками)
├─ Horizontal Alignment: Center
├─ Vertical Alignment: Center
│
└─ Canvas Panel Slot:
   ├─ Anchors: 0.5, 0.5 (Center)
   └─ Offset: -200, -300 (Center меню)
```

---

## 2️⃣ СОЗДАНИЕ WBP_MenuButton

### Шаг 1: Создать Widget Blueprint

```
Content/UI/Menus/
└─ WBP_MenuButton (Widget Blueprint)
   └─ Parent Class: UserWidget
```

### Шаг 2: Структура кнопки

```
Canvas Panel (Root)
│
└─ ButtonContainer (Overlay)
   ├─ ButtonBackground (Image)
   ├─ ButtonGlow (Image) - свечение при hover
   ├─ ContentContainer (HorizontalBox)
   │  ├─ IconImage (Image)
   │  └─ ButtonText (TextBlock)
   └─ Button (Button) - для взаимодействия
```

### Шаг 3: Настройки Button Widget

```
Button:
├─ Color and Opacity: Normal (White)
├─ Hovered Color: Orange (255, 165, 0, 200)
├─ Pressed Color: Red (255, 0, 0, 200)
├─ Normal Thickness: 2
├─ Hovered Thickness: 3
├─ Pressed Thickness: 4
└─ Widget Style: Custom Button Style
```

### Шаг 4: Фон кнопки

**ButtonBackground (Image):**
```
Image Widget:
├─ Brush:
│  ├─ Image: Button_Background_Texture
│  ├─ Color: Dark Gray (64, 64, 64)
│  └─ Margin: 8 (закругленные углы)
├─ Appearance:
│  ├─ Color: Inherit (от Button)
│  └─ Opacity: 0.8
└─ Size: 300 × 60
```

**ButtonGlow (Image):**
```
Image Widget (на Button Hover):
├─ Brush:
│  ├─ Image: Glow_Texture (радиальный градиент)
│  └─ Color: Orange (255, 165, 0)
├─ Size: 320 × 80 (немного больше фона)
├─ Opacity: 0.0 (по умолчанию)
├─ Visibility: Visible
└─ Is Variable: True (для Tick анимации)
```

### Шаг 5: Текст кнопки

**ButtonText (TextBlock):**
```
TextBlock:
├─ Text: "SKIRMISH" (устанавливается динамически)
├─ Font: Roboto Condensed Bold, Size 24
├─ Color: White (255, 255, 255)
├─ Justification: Center
├─ Vertical Alignment: Center
├─ Shadow Offset: (1, 1)
└─ Shadow Color: Black
```

### Шаг 6: Icon кнопки

**IconImage (Image):**
```
Image Widget:
├─ Brush → Texture: Button_Icon (например, "IC_Skirmish.png")
├─ Size: 32 × 32
├─ Color: Inherit (от Button)
└─ Margin: 10 (слева от текста)
```

### Шаг 7: Event Graph кнопки

**Events to implement:**
```
1. OnButtonHovered
   ├─ Animate ButtonGlow from 0 to 1 (200ms)
   ├─ Scale Button from 1.0 to 1.1 (200ms)
   ├─ Call MenuManager→PlayButtonHoverSound()
   └─ Change ButtonText color to brighter

2. OnButtonUnhovered
   ├─ Animate ButtonGlow from 1 to 0 (200ms)
   ├─ Scale Button from 1.1 to 1.0 (200ms)
   └─ Change ButtonText color to normal

3. OnButtonClicked
   ├─ Call MenuManager→PlayButtonClickSound()
   ├─ Animate click pulse (scale 1.0 → 0.95 → 1.0)
   └─ Execute bound event (OnSkirmish, OnSettings, etc.)
```

---

## 3️⃣ СОЗДАНИЕ WBP_GameCursor

### Шаг 1: Создать Widget Blueprint

```
Content/UI/Cursor/
└─ WBP_GameCursor (Widget Blueprint)
   └─ Parent Class: UserWidget
```

### Шаг 2: Структура курсора

```
Canvas Panel (Root)
│
└─ CursorContainer (Canvas Panel)
   ├─ CursorImage (Image) - основная стрелка
   ├─ CursorGlow (Image) - свечение вокруг
   └─ CursorParticles (optional - для эффектов)
```

### Шаг 3: CursorImage

```
Image Widget:
├─ Brush → Texture: Cursor_Normal (красивая стрелка)
├─ Size: 32 × 32
├─ Color and Opacity:
│  ├─ R: 1.0 (Red)
│  ├─ G: 1.0 (Green)
│  ├─ B: 1.0 (Blue)
│  └─ A: 1.0 (Alpha)
├─ Visibility: Visible
└─ Is Variable: True
```

### Шаг 4: CursorGlow

```
Image Widget:
├─ Brush → Texture: Glow_Radial (радиальный градиент свечения)
├─ Size: 48 × 48 (больше основного курсора)
├─ Color and Opacity: Yellow (255, 255, 0, 1.0)
├─ Opacity: 0.3
├─ Visibility: Visible
└─ Is Variable: True
```

### Шаг 5: Event Graph

```
NativeConstruct():
├─ Set Current Cursor State to Normal
├─ Hide default OS cursor
└─ Start cursor animation Tick

NativeTick(DeltaTime):
├─ Update Glow Rotation
├─ Update Glow Pulse Animation
├─ Update Cursor Position (follow mouse)
└─ Check for state changes
```

### Шаг 6: Анимация курсора

```
Glow Pulse Animation:
├─ Use Sin(WorldTime * 2) for pulsing
├─ Opacity: 0.3 to 0.7 (pulsing)
├─ Scale: 1.0 to 1.2 (subtle breathing)

Rotation Animation:
├─ Rotate Glow by 45 degrees per second
├─ Use RenderTransformAngle

Click Animation:
├─ Scale: 1.0 → 0.8 → 1.0 (quick pulse)
├─ Duration: 0.2 seconds
├─ Easing: Ease Out
```

---

## 4️⃣ ГЛАВНЫЙ GAME MODE BLUEPRINT

### Шаг 1: Modify BP_RTS_GameMode

```
Details:
├─ User Interface
│  ├─ Main Menu Class: WBP_MainMenu
│  ├─ Settings Menu Class: WBP_SettingsMenu
│  ├─ Cursor Widget Class: WBP_GameCursor
│  └─ Load Screen Class: WBP_LoadingScreen
│
└─ Audio
   ├─ Menu Music: HellMarch2_Menu_loop
   ├─ Button Hover Sound: UI_Click_Metal.wav
   ├─ Button Click Sound: UI_Clunk_Heavy.wav
   └─ Menu Transition Sound: UI_Whoosh.wav
```

### Шаг 2: Event Graph

```
BeginPlay():
├─ Create Widget: WBP_MainMenu
├─ Add to Viewport (priority 0)
├─ Get PlayerController
├─ Set Input Mode: Game and UI
├─ Show Mouse Cursor: True
├─ Set Cursor: Default
└─ Play Menu Music

OnSkirmishClicked():
├─ Remove Main Menu from Viewport
├─ Create Widget: WBP_SkirmishMenu
├─ Add to Viewport
└─ Play Transition Sound

OnPlayClicked():
├─ Stop Menu Music (fade out 2s)
├─ Show Loading Screen
├─ Open Level: Main.umap
└─ [Loading happens...]

OnSettingsClicked():
├─ Remove Main Menu from Viewport
├─ Create Widget: WBP_SettingsMenu
├─ Add to Viewport
└─ Play Transition Sound

OnExitClicked():
├─ Stop Menu Music
├─ Quit Game
```

---

## 5️⃣ МАТЕРИАЛЫ ДЛЯ UI

### Material: M_UIButton (для кнопок)

```
Material Setup:
├─ Blend Mode: Translucent
├─ Two Sided: False
├─ Emissive for Dynamic: Yes

Node Setup:
├─ Base Color
│  └─ Input: Vertex Color (для командного цвета)
├─ Normal
│  └─ Input: TextCoord[0] + Noise
├─ Emissive
│  └─ Input: 1.0 (легкое свечение)
├─ Roughness
│  └─ Input: 0.5 (матовый металл)
└─ Opacity
   └─ Input: 1.0
```

### Material: M_CursorGlow (для курсора)

```
Material Setup:
├─ Blend Mode: Additive
├─ Emissive for Dynamic: Yes

Node Setup:
├─ Base Color
│  └─ Input: Dynamic Parameter (меняется в C++)
├─ Emissive
│  └─ Dynamic Parameter * 2.0
├─ Opacity
│  └─ Radial Gradient (центр ярче)
└─ Normal
   └─ Flat (for 2D appearance)
```

---

## ✅ ЧЕКЛИСТ

- [ ] WBP_MainMenu создан и выглядит хорошо
- [ ] WBP_MenuButton работает с hover и click эффектами
- [ ] WBP_GameCursor анимирован и красиво выглядит
- [ ] BP_RTS_GameMode интегрирован с меню
- [ ] Звуки проигрываются при взаимодействии
- [ ] Переходы между меню работают
- [ ] Musik loop проигрывается в меню
- [ ] Курсор работает и красиво выглядит
- [ ] Нажата кнопка Exit - выходит из игры
- [ ] Нажата кнопка Skirmish - переход на выбор карты

---

## 🎮 БЫСТРОЕ ТЕСТИРОВАНИЕ

### В Editor:

```
1. Открыть BP_RTS_GameMode
2. Выставить параметры меню
3. Play в Editor
4. Навести на кнопку → должна подсветиться
5. Кликнуть → должны пройти анимация и звук
6. Кликнуть Exit → закрыть игру
```

---

## 🎨 ДОПОЛНИТЕЛЬНЫЕ ЭФФЕКТЫ

### Фоновая анимация (опционально):

```
1. Создать простой Particle System
2. Эффект: дымок в углах, искры
3. Установить Looping: True
4. Size: 1920 × 1080 (full screen)
5. Opacity: 0.1 (слабо видно, фон)
```

### Видео-фон (если есть видео):

```
1. Импортировать .mp4 файл
2. Создать Media Player
3. Создать Media Texture
4. В Image сдвлать Material с медиа-текстурой
5. Play автоматически при BeginPlay
```

---

## 📚 ПОЛЕЗНЫЕ ССЫЛКИ

- [UE5 UMG Widgets Documentation](https://docs.unrealengine.com/5.6/en-US/umg-user-interface-designer-conceptual/)
- [UE5 Animations in UMG](https://docs.unrealengine.com/5.6/en-US/umg-animation-in-unreal-engine/)
- [Blueprint Casts and Conversions](https://docs.unrealengine.com/5.6/en-US/blueprint-types-in-unreal-engine/)

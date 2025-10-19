# РЕАЛИЗАЦИЯ МЕНЮ RED ALERT 2 В UE5.6

## 📁 АРХИТЕКТУРА

```
Content/
├── UI/
│   ├── Menus/
│   │   ├── WBP_MainMenu (главное меню)
│   │   ├── WBP_SkirmishMenu (выбор карты)
│   │   └── WBP_SettingsMenu (настройки)
│   ├── Cursor/
│   │   ├── WBP_GameCursor (основной курсор)
│   │   └── CursorTextures/ (текстуры для разных состояний)
│   ├── Effects/
│   │   ├── Particles/ (эффекты)
│   │   └── Materials/ (материалы для UI)
│   └── Styles/
│       ├── MenuButtons
│       └── FontStyles
├── Audio/
│   ├── UI/
│   │   ├── ButtonHover.wav
│   │   ├── ButtonClick.wav
│   │   └── MenuTransition.wav
│   └── Music/
│       └── HellMarch2_Menu.mp3
└── Data/
    └── MenuConfig.json
```

---

## 🎨 ГЛАВНОЕ МЕНЮ (WBP_MainMenu)

### Структура Widget'а:

```
Canvas Panel (Main)
├─ Background Video Player
│  ├─ Media Source: RA2_Menu_Background.mp4
│  └─ Material: M_VideoBackground
├─ Particle System (decorative)
│  └─ Spawned at: center
├─ Center Container
│  ├─ Title Text ("Red Alert 2")
│  ├─ Subtitle Text ("Remastered")
│  └─ Button Container
│     ├─ Button: Skirmish
│     ├─ Button: Campaign
│     ├─ Button: Multiplayer
│     ├─ Button: Settings
│     └─ Button: Exit
├─ Bottom Left (Version Info)
│  └─ Text: "v1.0.0"
└─ Bottom Right (Social Links)
   ├─ Discord Icon (click → open link)
   └─ GitHub Icon (click → open link)
```

### C++ Класс для Main Menu:

```cpp
// MenuSystem/Public/MenuManager.h
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMenuButtonClicked);

UENUM(BlueprintType)
enum class EMenuState : uint8 {
    MainMenu = 0,
    SkirmishMenu = 1,
    SettingsMenu = 2,
    LoadingScreen = 3
};

UCLASS()
class YOURPROJECT_API UMenuManager : public UObject {
    GENERATED_BODY()

public:
    // Инициализация менеджера
    UFUNCTION(BlueprintCallable, Category = "Menu")
    void Initialize();

    // Переключение между меню
    UFUNCTION(BlueprintCallable, Category = "Menu")
    void ChangeMenuState(EMenuState NewState);

    // События кнопок
    UPROPERTY(BlueprintAssignable)
    FOnMenuButtonClicked OnSkirmishClicked;

    UPROPERTY(BlueprintAssignable)
    FOnMenuButtonClicked OnCampaignClicked;

    UPROPERTY(BlueprintAssignable)
    FOnMenuButtonClicked OnMultiplayerClicked;

    UPROPERTY(BlueprintAssignable)
    FOnMenuButtonClicked OnSettingsClicked;

    UPROPERTY(BlueprintAssignable)
    FOnMenuButtonClicked OnExitClicked;

    // Управление звуком меню
    UFUNCTION(BlueprintCallable, Category = "Menu|Audio")
    void PlayButtonHoverSound();

    UFUNCTION(BlueprintCallable, Category = "Menu|Audio")
    void PlayButtonClickSound();

    UFUNCTION(BlueprintCallable, Category = "Menu|Audio")
    void PlayMenuTransitionSound();

    // Управление музыкой
    UFUNCTION(BlueprintCallable, Category = "Menu|Audio")
    void PlayMenuMusic();

    UFUNCTION(BlueprintCallable, Category = "Menu|Audio")
    void StopMenuMusic();

protected:
    UPROPERTY(EditAnywhere, Category = "Audio")
    class USoundBase* ButtonHoverSound;

    UPROPERTY(EditAnywhere, Category = "Audio")
    class USoundBase* ButtonClickSound;

    UPROPERTY(EditAnywhere, Category = "Audio")
    class USoundBase* TransitionSound;

    UPROPERTY(EditAnywhere, Category = "Audio")
    class USoundBase* MenuMusic;

private:
    EMenuState CurrentMenuState;
    UPROPERTY()
    class UAudioComponent* MusicComponent;
};
```

### Реализация C++:

```cpp
// MenuSystem/Private/MenuManager.cpp
#include "MenuManager.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"

void UMenuManager::Initialize() {
    // Загрузка звуков
    static ConstructorHelpers::FObjectFinder<USoundBase> ButtonHover(
        TEXT("/Game/Audio/UI/ButtonHover")
    );
    if (ButtonHover.Succeeded()) {
        ButtonHoverSound = ButtonHover.Object;
    }

    // Загрузка музыки
    static ConstructorHelpers::FObjectFinder<USoundBase> Music(
        TEXT("/Game/Audio/Music/HellMarch2_Menu")
    );
    if (Music.Succeeded()) {
        MenuMusic = Music.Object;
    }

    CurrentMenuState = EMenuState::MainMenu;
    PlayMenuMusic();
}

void UMenuManager::PlayButtonHoverSound() {
    if (ButtonHoverSound) {
        UGameplayStatics::PlaySound2D(GetWorld(), ButtonHoverSound, 0.5f);
    }
}

void UMenuManager::PlayButtonClickSound() {
    if (ButtonClickSound) {
        UGameplayStatics::PlaySound2D(GetWorld(), ButtonClickSound, 0.8f);
    }
}

void UMenuManager::ChangeMenuState(EMenuState NewState) {
    if (CurrentMenuState != NewState) {
        PlayMenuTransitionSound();
        CurrentMenuState = NewState;
    }
}

void UMenuManager::PlayMenuMusic() {
    if (MenuMusic) {
        UGameplayStatics::PlaySound2D(GetWorld(), MenuMusic, 1.0f, 1.0f, 0.0f, nullptr, true);
    }
}

void UMenuManager::StopMenuMusic() {
    // Плавное затухание музыки
    if (MusicComponent) {
        MusicComponent->FadeOut(2.0f, 0.0f);
    }
}
```

---

## 🖱️ СИСТЕМА КУРСОРА (WBP_GameCursor)

### Widget для курсора:

```cpp
// UI/Public/GameCursor.h
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameCursor.generated.h"

UENUM(BlueprintType)
enum class ECursorState : uint8 {
    Normal = 0,       // Обычный указатель
    Hover = 1,        // Наведение на кнопку
    Click = 2,        // Клик
    Move = 3,         // Движение по карте
    Attack = 4,       // Атака
    Unavailable = 5   // Действие недоступно
};

UCLASS()
class YOURPROJECT_API UGameCursor : public UUserWidget {
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

    // Управление состоянием курсора
    UFUNCTION(BlueprintCallable, Category = "Cursor")
    void SetCursorState(ECursorState NewState);

    // Обновить позицию курсора
    UFUNCTION(BlueprintCallable, Category = "Cursor")
    void UpdateCursorPosition(FVector2D NewPosition);

    // Анимация клика
    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Cursor")
    void PlayClickAnimation();

protected:
    UPROPERTY(meta = (BindWidget))
    class UImage* CursorImage;

    UPROPERTY(meta = (BindWidget))
    class UImage* CursorGlow;

    UPROPERTY(EditAnywhere, Category = "Cursor|Visual")
    float GlowIntensity = 1.5f;

    UPROPERTY(EditAnywhere, Category = "Cursor|Visual")
    float RotationSpeed = 45.0f;

private:
    ECursorState CurrentCursorState;
    float GlowAlpha;
    float RotationAngle;

    void UpdateCursorVisuals();
};
```

### Material для glowing курсора:

```
Создать материал M_CursorGlow с параметрами:
- BaseColor: Динамический (меняется в зависимости от состояния)
- Emissive: Яркий свет с пульсацией
- Opacity: Анимированная прозрачность (0.5 - 1.0)
- Roughness: 0.2 (блеск)

Примеры цветов:
- Normal: #FFD700 (золотой)
- Hover: #FF8800 (оранжевый)
- Click: #FF0000 (красный)
- Attack: #FF0000 (красный, более яркий)
- Move: #00FF00 (зелёный)
- Unavailable: #666666 (серый, тусклый)
```

---

## 🔘 ИНТЕРАКТИВНЫЕ КНОПКИ (WBP_MenuButton)

### Button Widget с эффектами:

```cpp
// UI/Public/MenuButton.h
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "MenuButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_One(FOnButtonStateChanged, bool, bIsHovered);

UCLASS()
class YOURPROJECT_API UMenuButton : public UUserWidget {
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

    // Установить текст кнопки
    UFUNCTION(BlueprintCallable, Category = "Button")
    void SetButtonText(const FString& NewText);

    // Установить icon кнопки
    UFUNCTION(BlueprintCallable, Category = "Button")
    void SetButtonIcon(UTexture2D* NewIcon);

    // События кнопки
    UPROPERTY(BlueprintAssignable, Category = "Button")
    FOnButtonStateChanged OnHoverStateChanged;

protected:
    UPROPERTY(meta = (BindWidget))
    class UButton* MainButton;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* ButtonText;

    UPROPERTY(meta = (BindWidget))
    class UImage* ButtonIcon;

    UPROPERTY(meta = (BindWidget))
    class UImage* HoverGlow;

    UPROPERTY(EditAnywhere, Category = "Button|Effects")
    float HoverScaleAmount = 1.1f;

    UPROPERTY(EditAnywhere, Category = "Button|Effects")
    float HoverGlowIntensity = 1.5f;

    UPROPERTY(EditAnywhere, Category = "Button|Effects")
    float TransitionDuration = 0.2f;

private:
    UFUNCTION()
    void OnButtonHovered();

    UFUNCTION()
    void OnButtonUnhovered();

    UFUNCTION()
    void OnButtonClicked();

    void PlayHoverAnimation();
    void PlayClickAnimation();
};
```

### Реализация C++:

```cpp
// UI/Private/MenuButton.cpp
#include "MenuButton.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/CanvasPanelSlot.h"
#include "Kismet/GameplayStatics.h"

void UMenuButton::NativeConstruct() {
    Super::NativeConstruct();

    if (MainButton) {
        MainButton->OnHovered.AddDynamic(this, &UMenuButton::OnButtonHovered);
        MainButton->OnUnhovered.AddDynamic(this, &UMenuButton::OnButtonUnhovered);
        MainButton->OnClicked.AddDynamic(this, &UMenuButton::OnButtonClicked);
    }
}

void UMenuButton::OnButtonHovered() {
    OnHoverStateChanged.Broadcast(true);
    PlayHoverAnimation();

    // Проиграть звук наведения
    if (UMenuManager* MenuMgr = Cast<UMenuManager>(UGameplayStatics::GetGameMode(GetWorld()))) {
        MenuMgr->PlayButtonHoverSound();
    }
}

void UMenuButton::OnButtonUnhovered() {
    OnHoverStateChanged.Broadcast(false);
}

void UMenuButton::OnButtonClicked() {
    PlayClickAnimation();

    if (UMenuManager* MenuMgr = Cast<UMenuManager>(UGameplayStatics::GetGameMode(GetWorld()))) {
        MenuMgr->PlayButtonClickSound();
    }
}

void UMenuButton::PlayHoverAnimation() {
    // Используем UMG animations
    // Масштабирование + Glow эффект
}

void UMenuButton::PlayClickAnimation() {
    // Анимация клика (пульс, звук)
}

void UMenuButton::SetButtonText(const FString& NewText) {
    if (ButtonText) {
        ButtonText->SetText(FText::FromString(NewText));
    }
}

void UMenuButton::SetButtonIcon(UTexture2D* NewIcon) {
    if (ButtonIcon) {
        ButtonIcon->SetBrushFromTexture(NewIcon);
    }
}
```

---

## 🎬 ФОНОВЫЕ ВИДЕО И АНИМАЦИИ

### Material для видео-фона (M_VideoBackground):

```
Material Setup:
├─ Media Texture (video playback)
├─ Distortion (слабая волна эффект)
├─ Color Overlay (темный оверлей для контраста)
├─ Scanlines (RA2 эстетика)
└─ Emissive (слабое свечение)

Параметры:
- VideoIntensity: 0.7 (яркость видео)
- OverlayAlpha: 0.3 (темнота оверлея)
- ScanlinesIntensity: 0.1 (едва заметные линии)
- DistortionAmount: 0.02 (слабое искажение)
```

### Материал для эффектов частиц:

```
M_ParticleEffect:
├─ Base Color: Динамический (меняется с временем)
├─ Emissive: Пульсирующий
├─ Opacity: Маска с noise для реалистичности
└─ Normal Map: Для объема

Используется для:
- Дыма в фоне
- Искр
- Пыли
- Энергетических эффектов
```

---

## 🔊 ЗВУКОВОЙ ДИЗАЙН

### Структура звуков:

```
Audio/
├─ UI/
│  ├─ ButtonHover.wav (50ms, -12dB, metal click)
│  ├─ ButtonClick.wav (100ms, -8dB, heavy clunk)
│  ├─ MenuTransition.wav (200ms, -15dB, whoosh)
│  └─ ErrorBeep.wav (200ms, -10dB, alert)
└─ Music/
   ├─ HellMarch2_Menu.mp3 (loop)
   ├─ HellMarch2_Game.mp3 (intensity: low)
   └─ HellMarch2_Combat.mp3 (intensity: high)
```

### Sound Cues:

```cpp
// Создать Sound Cue для каждого звука
// Параметры:
// - Volume: -12 to -8 dB
// - Pitch: 1.0 (normal)
// - Attenuation: None (UI звуки)
// - Loop: false для effects, true для музыки
```

---

## 🎯 INTEGRATION: Game Mode & Player Controller

### Модифицированный BP_RTS_GameMode:

```cpp
// Game/Public/RTSGameMode.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RTSGameMode.generated.h"

UCLASS()
class YOURPROJECT_API ARTSGameMode : public AGameModeBase {
    GENERATED_BODY()

public:
    ARTSGameMode();

    virtual void BeginPlay() override;

    // Отобразить главное меню
    UFUNCTION(BlueprintCallable, Category = "Menu")
    void ShowMainMenu();

    // Отобразить меню настроек
    UFUNCTION(BlueprintCallable, Category = "Menu")
    void ShowSettingsMenu();

    // Начать игру (скрыть меню)
    UFUNCTION(BlueprintCallable, Category = "Menu")
    void StartGame();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> MainMenuClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> SettingsMenuClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> CursorWidgetClass;

private:
    UPROPERTY()
    class UUserWidget* CurrentMenu;

    UPROPERTY()
    class UGameCursor* CursorWidget;
};
```

---

## ✅ ЧЕКЛИСТ РЕАЛИЗАЦИИ

### Фаза 1: Структура (текущая)
- [ ] Создать папки структуры
- [ ] Создать C++ классы (MenuManager, GameCursor, MenuButton)
- [ ] Создать Widget Blueprints

### Фаза 2: Визуализация
- [ ] Материалы для UI
- [ ] Видео-фон
- [ ] Particle системы
- [ ] Текстуры

### Фаза 3: Интерактивность
- [ ] Hover эффекты
- [ ] Click анимации
- [ ] Звуки
- [ ] Transitions

### Фаза 4: Полировка
- [ ] Оптимизация производительности
- [ ] Тестирование на разных разрешениях
- [ ] Локализация (RU/EN)
- [ ] Полный playtest

---

## 📚 ССЫЛКИ

- UE5 UMG Documentation: https://docs.unrealengine.com/5.6/en-US/umg-user-interface-designer-conceptual/
- RA2 Original UI: https://cnc.fandom.com/wiki/Red_Alert_2
- Material Editor: https://docs.unrealengine.com/5.6/en-US/materials/

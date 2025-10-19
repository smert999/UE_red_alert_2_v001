#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuManager.generated.h"

// Forward declarations
class UUserWidget;
class USoundBase;
class UAudioComponent;

// Перечисление для состояний меню
UENUM(BlueprintType)
enum class EMenuState : uint8 {
    MainMenu = 0 UMETA(DisplayName = "Main Menu"),
    SkirmishMenu = 1 UMETA(DisplayName = "Skirmish"),
    SettingsMenu = 2 UMETA(DisplayName = "Settings"),
    LoadingScreen = 3 UMETA(DisplayName = "Loading")
};

// Делегат для событий кнопок
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMenuStateChanged);

/**
 * MenuManager - управляет состоянием меню и звуками
 */
UCLASS(Blueprintable, BlueprintType)
class UE_RTS_COURSE_API UMenuManager : public UActorComponent {
    GENERATED_BODY()

public:
    UMenuManager();

    // Инициализация менеджера
    UFUNCTION(BlueprintCallable, Category = "Menu")
    void Initialize();

    // Переключение между меню
    UFUNCTION(BlueprintCallable, Category = "Menu")
    void ChangeMenuState(EMenuState NewState);

    // Получить текущее состояние
    UFUNCTION(BlueprintCallable, Category = "Menu")
    EMenuState GetCurrentMenuState() const { return CurrentMenuState; }

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

    // События
    UPROPERTY(BlueprintAssignable, Category = "Menu")
    FOnMenuStateChanged OnMenuStateChanged;

    UPROPERTY(BlueprintAssignable, Category = "Menu")
    FOnMenuStateChanged OnSkirmishClicked;

    UPROPERTY(BlueprintAssignable, Category = "Menu")
    FOnMenuStateChanged OnCampaignClicked;

    UPROPERTY(BlueprintAssignable, Category = "Menu")
    FOnMenuStateChanged OnMultiplayerClicked;

    UPROPERTY(BlueprintAssignable, Category = "Menu")
    FOnMenuStateChanged OnSettingsClicked;

    UPROPERTY(BlueprintAssignable, Category = "Menu")
    FOnMenuStateChanged OnExitClicked;

protected:
    virtual void BeginPlay() override;

    // Звуки UI
    UPROPERTY(EditAnywhere, Category = "Audio|Effects")
    TSoftObjectPtr<USoundBase> ButtonHoverSound;

    UPROPERTY(EditAnywhere, Category = "Audio|Effects")
    TSoftObjectPtr<USoundBase> ButtonClickSound;

    UPROPERTY(EditAnywhere, Category = "Audio|Effects")
    TSoftObjectPtr<USoundBase> TransitionSound;

    // Музыка
    UPROPERTY(EditAnywhere, Category = "Audio|Music")
    TSoftObjectPtr<USoundBase> MenuMusic;

    UPROPERTY(EditAnywhere, Category = "Audio|Music")
    float MusicVolume = 0.7f;

private:
    EMenuState CurrentMenuState;

    // Загруженные звуки (кешированные)
    UPROPERTY()
    USoundBase* CachedButtonHoverSound;

    UPROPERTY()
    USoundBase* CachedButtonClickSound;

    UPROPERTY()
    USoundBase* CachedTransitionSound;

    UPROPERTY()
    USoundBase* CachedMenuMusic;

    // Компонент для воспроизведения музыки (для контроля)
    UPROPERTY()
    UAudioComponent* MusicComponent;

    // Вспомогательные функции
    void LoadAudioAssets();
};

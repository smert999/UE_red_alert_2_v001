#include "UI/MenuManager.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
#include "AudioComponent.h"

UMenuManager::UMenuManager()
    : CurrentMenuState(EMenuState::MainMenu)
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UMenuManager::BeginPlay() {
    Super::BeginPlay();
    Initialize();
}

void UMenuManager::Initialize() {
    LoadAudioAssets();
    PlayMenuMusic();

    UE_LOG(LogTemp, Warning, TEXT("MenuManager initialized"));
}

void UMenuManager::LoadAudioAssets() {
    // Загрузка звуков из мягких ссылок
    if (ButtonHoverSound.IsValid()) {
        CachedButtonHoverSound = ButtonHoverSound.LoadSynchronous();
    }

    if (ButtonClickSound.IsValid()) {
        CachedButtonClickSound = ButtonClickSound.LoadSynchronous();
    }

    if (TransitionSound.IsValid()) {
        CachedTransitionSound = TransitionSound.LoadSynchronous();
    }

    if (MenuMusic.IsValid()) {
        CachedMenuMusic = MenuMusic.LoadSynchronous();
    }
}

void UMenuManager::ChangeMenuState(EMenuState NewState) {
    if (CurrentMenuState != NewState) {
        PlayMenuTransitionSound();
        CurrentMenuState = NewState;
        OnMenuStateChanged.Broadcast();

        UE_LOG(LogTemp, Warning, TEXT("Menu state changed to: %d"), (int32)NewState);
    }
}

void UMenuManager::PlayButtonHoverSound() {
    if (CachedButtonHoverSound) {
        UGameplayStatics::PlaySound2D(GetWorld(), CachedButtonHoverSound, 0.5f);
    }
}

void UMenuManager::PlayButtonClickSound() {
    if (CachedButtonClickSound) {
        UGameplayStatics::PlaySound2D(GetWorld(), CachedButtonClickSound, 0.8f);
    }
}

void UMenuManager::PlayMenuTransitionSound() {
    if (CachedTransitionSound) {
        UGameplayStatics::PlaySound2D(GetWorld(), CachedTransitionSound, 1.0f);
    }
}

void UMenuManager::PlayMenuMusic() {
    if (CachedMenuMusic) {
        UGameplayStatics::PlaySound2D(
            GetWorld(),
            CachedMenuMusic,
            MusicVolume,
            1.0f,
            0.0f,
            nullptr,
            false
        );
    }
}

void UMenuManager::StopMenuMusic() {
    // Плавное затухание музыки
    if (MusicComponent) {
        MusicComponent->FadeOut(2.0f, 0.0f);
    }
}

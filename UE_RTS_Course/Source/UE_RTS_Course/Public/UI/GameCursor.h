#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameCursor.generated.h"

// Forward declarations
class UImage;
class UCanvasPanel;

// Перечисление для состояний курсора
UENUM(BlueprintType)
enum class ECursorState : uint8 {
    Normal = 0 UMETA(DisplayName = "Normal"),
    Hover = 1 UMETA(DisplayName = "Hover/Select"),
    Click = 2 UMETA(DisplayName = "Click"),
    Move = 3 UMETA(DisplayName = "Move"),
    Attack = 4 UMETA(DisplayName = "Attack"),
    Unavailable = 5 UMETA(DisplayName = "Unavailable")
};

/**
 * GameCursor - управляет отображением и поведением курсора
 * 
 * Может использоваться в меню и в игре
 * Поддерживает разные состояния (наведение, клик, атака, движение)
 */
UCLASS()
class UE_RTS_COURSE_API UGameCursor : public UUserWidget {
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

    // Установить состояние курсора
    UFUNCTION(BlueprintCallable, Category = "Cursor")
    void SetCursorState(ECursorState NewState);

    // Получить текущее состояние
    UFUNCTION(BlueprintCallable, Category = "Cursor")
    ECursorState GetCursorState() const { return CurrentCursorState; }

    // Обновить позицию курсора
    UFUNCTION(BlueprintCallable, Category = "Cursor")
    void UpdateCursorPosition(FVector2D NewPosition);

    // Проиграть анимацию клика
    UFUNCTION(BlueprintCallable, Category = "Cursor")
    void PlayClickAnimation();

    // Показать/скрыть курсор
    UFUNCTION(BlueprintCallable, Category = "Cursor")
    void ShowCursor(bool bShow);

protected:
    // UI компоненты
    UPROPERTY(meta = (BindWidget))
    UImage* CursorImage;

    UPROPERTY(meta = (BindWidget))
    UImage* CursorGlow;

    UPROPERTY(meta = (BindWidgetOptional))
    UCanvasPanel* MainCanvas;

    // Параметры визуализации
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor|Visual")
    float GlowIntensity = 1.5f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor|Visual")
    float RotationSpeed = 45.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor|Visual")
    float PulseSpeed = 2.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor|Visual")
    float MinGlowAlpha = 0.3f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor|Visual")
    float MaxGlowAlpha = 1.0f;

    // Текстуры курсора для разных состояний
    UPROPERTY(EditAnywhere, Category = "Cursor|Textures")
    UTexture2D* NormalCursorTexture;

    UPROPERTY(EditAnywhere, Category = "Cursor|Textures")
    UTexture2D* HoverCursorTexture;

    UPROPERTY(EditAnywhere, Category = "Cursor|Textures")
    UTexture2D* MoveCursorTexture;

    UPROPERTY(EditAnywhere, Category = "Cursor|Textures")
    UTexture2D* AttackCursorTexture;

    UPROPERTY(EditAnywhere, Category = "Cursor|Textures")
    UTexture2D* UnavailableCursorTexture;

    // Цвета для разных состояний
    UPROPERTY(EditAnywhere, Category = "Cursor|Colors")
    FLinearColor NormalColor = FLinearColor::Yellow;

    UPROPERTY(EditAnywhere, Category = "Cursor|Colors")
    FLinearColor HoverColor = FLinearColor(1.0f, 0.6f, 0.0f, 1.0f);  // Оранжевый

    UPROPERTY(EditAnywhere, Category = "Cursor|Colors")
    FLinearColor MoveColor = FLinearColor::Green;

    UPROPERTY(EditAnywhere, Category = "Cursor|Colors")
    FLinearColor AttackColor = FLinearColor::Red;

    UPROPERTY(EditAnywhere, Category = "Cursor|Colors")
    FLinearColor UnavailableColor = FLinearColor(0.5f, 0.5f, 0.5f, 1.0f);  // Серый

private:
    ECursorState CurrentCursorState;
    FVector2D CurrentPosition;
    float GlowAlpha;
    float RotationAngle;
    bool bIsClickAnimating;
    float ClickAnimationProgress;

    // Вспомогательные функции
    void UpdateCursorVisuals();
    void UpdateGlowEffect(float DeltaTime);
    void UpdateClickAnimation(float DeltaTime);
    void SetCursorTexture(UTexture2D* NewTexture);
    void SetCursorColor(FLinearColor NewColor);
};

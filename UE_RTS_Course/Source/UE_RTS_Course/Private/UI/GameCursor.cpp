#include "UI/GameCursor.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Kismet/GameplayStatics.h"

void UGameCursor::NativeConstruct() {
    Super::NativeConstruct();

    CurrentCursorState = ECursorState::Normal;
    GlowAlpha = MinGlowAlpha;
    RotationAngle = 0.0f;
    bIsClickAnimating = false;
    ClickAnimationProgress = 0.0f;

    // Установить начальную текстуру и цвет
    SetCursorTexture(NormalCursorTexture);
    SetCursorColor(NormalColor);

    // Включить Tick для анимаций
    if (CursorImage) {
        CursorImage->SetVisibility(ESlateVisibility::HitTestInvisible);
    }

    if (CursorGlow) {
        CursorGlow->SetVisibility(ESlateVisibility::HitTestInvisible);
    }

    UE_LOG(LogTemp, Warning, TEXT("GameCursor initialized"));
}

void UGameCursor::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
    Super::NativeTick(MyGeometry, InDeltaTime);

    // Обновить эффект свечения
    UpdateGlowEffect(InDeltaTime);

    // Обновить анимацию клика если она активна
    if (bIsClickAnimating) {
        UpdateClickAnimation(InDeltaTime);
    }
}

void UGameCursor::SetCursorState(ECursorState NewState) {
    if (CurrentCursorState != NewState) {
        CurrentCursorState = NewState;

        // Смена текстуры в зависимости от состояния
        switch (NewState) {
            case ECursorState::Normal:
                SetCursorTexture(NormalCursorTexture);
                SetCursorColor(NormalColor);
                break;

            case ECursorState::Hover:
                SetCursorTexture(HoverCursorTexture ? HoverCursorTexture : NormalCursorTexture);
                SetCursorColor(HoverColor);
                break;

            case ECursorState::Move:
                SetCursorTexture(MoveCursorTexture ? MoveCursorTexture : NormalCursorTexture);
                SetCursorColor(MoveColor);
                break;

            case ECursorState::Attack:
                SetCursorTexture(AttackCursorTexture ? AttackCursorTexture : NormalCursorTexture);
                SetCursorColor(AttackColor);
                break;

            case ECursorState::Unavailable:
                SetCursorTexture(UnavailableCursorTexture ? UnavailableCursorTexture : NormalCursorTexture);
                SetCursorColor(UnavailableColor);
                break;

            case ECursorState::Click:
                PlayClickAnimation();
                break;

            default:
                break;
        }

        UE_LOG(LogTemp, Warning, TEXT("Cursor state changed to: %d"), (int32)NewState);
    }
}

void UGameCursor::UpdateCursorPosition(FVector2D NewPosition) {
    CurrentPosition = NewPosition;

    // Обновить позицию главного канваса если он существует
    if (MainCanvas) {
        if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(MainCanvas->Slot)) {
            CanvasSlot->SetPosition(NewPosition);
        }
    }
}

void UGameCursor::PlayClickAnimation() {
    bIsClickAnimating = true;
    ClickAnimationProgress = 0.0f;
}

void UGameCursor::ShowCursor(bool bShow) {
    ESlateVisibility Visibility = bShow ? ESlateVisibility::Visible : ESlateVisibility::Hidden;

    if (CursorImage) {
        CursorImage->SetVisibility(Visibility);
    }

    if (CursorGlow) {
        CursorGlow->SetVisibility(Visibility);
    }
}

void UGameCursor::UpdateGlowEffect(float DeltaTime) {
    if (!CursorGlow) {
        return;
    }

    // Пульсирующий эффект свечения
    float PulseValue = FMath::Sin(GetWorld()->GetTimeSeconds() * PulseSpeed);
    GlowAlpha = FMath::Lerp(MinGlowAlpha, MaxGlowAlpha, (PulseValue + 1.0f) * 0.5f);

    // Обновить альфа канал и масштаб
    FLinearColor GlowColor = CursorGlow->GetColorAndOpacity();
    GlowColor.A = GlowAlpha;
    CursorGlow->SetColorAndOpacity(GlowColor);

    // Вращение курсора
    RotationAngle += RotationSpeed * DeltaTime;
    if (RotationAngle >= 360.0f) {
        RotationAngle -= 360.0f;
    }

    CursorGlow->SetRenderTransformAngle(RotationAngle);
}

void UGameCursor::UpdateClickAnimation(float DeltaTime) {
    const float AnimationDuration = 0.2f;

    ClickAnimationProgress += DeltaTime;

    if (ClickAnimationProgress >= AnimationDuration) {
        bIsClickAnimating = false;
        ClickAnimationProgress = 0.0f;
        // Вернуться в нормальное состояние
        SetCursorState(ECursorState::Normal);
        return;
    }

    // Анимация: масштабирование (сжатие и расширение)
    float Progress = ClickAnimationProgress / AnimationDuration;
    float Scale = 1.0f - (FMath::Abs(FMath::Sin(Progress * PI)) * 0.3f);

    if (CursorImage) {
        CursorImage->SetRenderScale(FVector2D(Scale, Scale));
    }

    if (CursorGlow) {
        CursorGlow->SetRenderScale(FVector2D(Scale * 1.2f, Scale * 1.2f));
    }
}

void UGameCursor::SetCursorTexture(UTexture2D* NewTexture) {
    if (CursorImage && NewTexture) {
        CursorImage->SetBrushFromTexture(NewTexture);
    }
}

void UGameCursor::SetCursorColor(FLinearColor NewColor) {
    if (CursorImage) {
        CursorImage->SetColorAndOpacity(NewColor);
    }

    if (CursorGlow) {
        FLinearColor GlowColor = NewColor;
        GlowColor.A = GlowAlpha;
        CursorGlow->SetColorAndOpacity(GlowColor);
    }
}

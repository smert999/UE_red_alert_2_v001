// C++ Reference for Edge Panning Implementation
// This is REFERENCE ONLY - implement in Blueprint as specified

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/SceneComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/Engine.h"
#include "RTSCameraPawn.generated.h"

UCLASS()
class UE_RTS_COURSE_API ARTSCameraPawn : public APawn
{
    GENERATED_BODY()

public:
    ARTSCameraPawn();

protected:
    // Edge Panning Variables (ADD THESE TO BLUEPRINT)
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Edge Panning", 
              meta = (Tooltip = "Enable/disable edge panning functionality"))
    bool EdgePanEnabled = true;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Edge Panning",
              meta = (Tooltip = "Distance in pixels from screen edge to trigger panning", ClampMin = "5", ClampMax = "50"))
    int32 EdgePanBorderPx = 15;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Edge Panning",
              meta = (Tooltip = "Speed of edge panning movement", ClampMin = "1000.0", ClampMax = "25000.0"))
    float EdgePanSpeed = 12000.0f;

    // Existing Components (Reference)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    USceneComponent* YawPivot;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    USceneComponent* PitchPivot;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    class USpringArmComponent* SpringArm;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    UCameraComponent* Camera;

public:
    virtual void Tick(float DeltaTime) override;

private:
    // Edge Panning Logic (IMPLEMENT THIS IN BLUEPRINT EVENT TICK)
    void HandleEdgePanning(float DeltaTime);
};

// Implementation Reference (BLUEPRINT EQUIVALENT)
void ARTSCameraPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    // Call existing tick logic first
    // Then add edge panning
    HandleEdgePanning(DeltaTime);
}

void ARTSCameraPawn::HandleEdgePanning(float DeltaTime)
{
    // BLUEPRINT IMPLEMENTATION:
    // 1. Branch: if (!EdgePanEnabled) return;
    if (!EdgePanEnabled)
        return;
    
    // 2. Get Player Controller 0
    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (!PC)
        return;
    
    // 3. Get Viewport Size
    int32 ViewportSizeX, ViewportSizeY;
    PC->GetViewportSize(ViewportSizeX, ViewportSizeY);
    
    // 4. Get Mouse Position Scaled by DPI
    float MouseX, MouseY;
    PC->GetMousePositionScaledByDPI(MouseX, MouseY);
    
    // 5. Check Left Edge (Mouse X <= EdgePanBorderPx)
    if (MouseX <= static_cast<float>(EdgePanBorderPx))
    {
        // 6. Get YawPivot Right Vector
        FVector RightVector = YawPivot->GetRightVector();
        
        // 7. Negate to get Left Vector
        FVector LeftVector = -RightVector;
        
        // 8. Set Z=0 for horizontal movement
        LeftVector.Z = 0.0f;
        
        // 9. Normalize for consistent direction
        LeftVector.Normalize();
        
        // 10. Apply Movement Input with Speed and DeltaTime
        float MovementScale = EdgePanSpeed * DeltaTime;
        AddMovementInput(LeftVector, MovementScale);
    }
}

/*
BLUEPRINT NODE CHAIN EQUIVALENT:

Event Tick
└── Branch (EdgePanEnabled)
    └── True:
        ├── Get Player Controller (Index: 0)
        ├── Get Viewport Size (from Player Controller)
        ├── Get Mouse Position Scaled by DPI (from Player Controller)
        ├── Break Vector2D (Mouse Position) → MouseX, MouseY
        ├── <= (Float): MouseX <= Cast(EdgePanBorderPx)
        └── Branch (Mouse at left edge)
            └── True:
                ├── YawPivot → Get Right Vector
                ├── Negate (Vector)
                ├── Make Vector (X, Y, Z=0.0)
                ├── Vector Normalize
                ├── Get World Delta Seconds
                ├── * (Float): EdgePanSpeed × DeltaTime
                └── Add Movement Input (Direction: LeftVector, Scale: Speed×DeltaTime)

TESTING BLUEPRINT:
1. Set EdgePanEnabled = true, EdgePanBorderPx = 15, EdgePanSpeed = 12000
2. Play in Selected Viewport
3. Move mouse to left edge (X ≤ 15px)
4. Camera should pan left smoothly
5. Move mouse away from edge - panning stops
6. Set EdgePanEnabled = false - no panning occurs
*/
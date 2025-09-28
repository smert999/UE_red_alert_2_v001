#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/SceneComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/Engine.h"
#include "RTSCameraPawn.generated.h"

UCLASS(BlueprintType, Blueprintable)
class UE_RTS_COURSE_API ARTSCameraPawn : public APawn
{
    GENERATED_BODY()

public:
    ARTSCameraPawn();

protected:
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

public:
    virtual void Tick(float DeltaTime) override;

protected:
    // ===== CAMERA COMPONENTS =====
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
    USceneComponent* YawPivot;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
    USceneComponent* PitchPivot;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
    USpringArmComponent* SpringArm;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
    UCameraComponent* Camera;

    // ===== EDGE PANNING VARIABLES =====
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Edge Panning", 
              meta = (Tooltip = "Enable/disable edge panning functionality"))
    bool EdgePanEnabled = true;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Edge Panning",
              meta = (Tooltip = "Distance in pixels from screen edge to trigger panning", ClampMin = "5", ClampMax = "50"))
    int32 EdgePanBorderPx = 15;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Edge Panning",
              meta = (Tooltip = "Speed of edge panning movement", ClampMin = "1000.0", ClampMax = "25000.0"))
    float EdgePanSpeed = 12000.0f;

    // ===== CAMERA MOVEMENT VARIABLES =====
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Movement",
              meta = (Tooltip = "Base movement speed for WASD controls"))
    float MovementSpeed = 10000.0f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Movement",
              meta = (Tooltip = "Fast pan speed multiplier when holding Shift"))
    float FastPanMultiplier = 2.5f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Movement",
              meta = (Tooltip = "Camera rotation speed for Q/E controls"))
    float RotationSpeed = 45.0f;

    // ===== ZOOM VARIABLES =====
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Zoom",
              meta = (Tooltip = "Minimum orthographic width (max zoom in)"))
    float MinOrthoWidth = 1000.0f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Zoom",
              meta = (Tooltip = "Maximum orthographic width (max zoom out)"))
    float MaxOrthoWidth = 8000.0f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Zoom",
              meta = (Tooltip = "Zoom speed multiplier"))
    float ZoomSpeed = 500.0f;

    // ===== MAP BOUNDS VARIABLES =====
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Bounds",
              meta = (Tooltip = "Minimum X coordinate for camera movement"))
    float MinX = -50000.0f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Bounds",
              meta = (Tooltip = "Maximum X coordinate for camera movement"))
    float MaxX = 50000.0f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Bounds",
              meta = (Tooltip = "Minimum Y coordinate for camera movement"))
    float MinY = -50000.0f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Bounds",
              meta = (Tooltip = "Maximum Y coordinate for camera movement"))
    float MaxY = 50000.0f;

    // ===== PRIVATE VARIABLES =====
    
    UPROPERTY()
    float CurrentCameraYaw = 45.0f;
    
    UPROPERTY()
    bool bIsFastPanning = false;

public:
    // ===== INPUT FUNCTIONS =====
    
    UFUNCTION()
    void MoveForward(float Value);
    
    UFUNCTION()
    void MoveRight(float Value);
    
    UFUNCTION()
    void RotateLeft();
    
    UFUNCTION()
    void RotateRight();
    
    UFUNCTION()
    void ZoomIn();
    
    UFUNCTION()
    void ZoomOut();
    
    UFUNCTION()
    void StartFastPan();
    
    UFUNCTION()
    void StopFastPan();

private:
    // ===== PRIVATE FUNCTIONS =====
    
    void HandleEdgePanning(float DeltaTime);
    void ClampCameraPosition();
    void UpdateCameraRotation();
    
    // ===== COMPONENT GETTERS =====
    
public:
    FORCEINLINE USceneComponent* GetYawPivot() const { return YawPivot; }
    FORCEINLINE USceneComponent* GetPitchPivot() const { return PitchPivot; }
    FORCEINLINE USpringArmComponent* GetSpringArm() const { return SpringArm; }
    FORCEINLINE UCameraComponent* GetCamera() const { return Camera; }
};
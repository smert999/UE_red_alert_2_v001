#include "RTSCameraPawn.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

ARTSCameraPawn::ARTSCameraPawn()
{
    PrimaryActorTick.bCanEverTick = true;

    // Create camera rig components - YawPivot/PitchPivot architecture
    YawPivot = CreateDefaultSubobject<USceneComponent>(TEXT("YawPivot"));
    RootComponent = YawPivot;

    PitchPivot = CreateDefaultSubobject<USceneComponent>(TEXT("PitchPivot"));
    PitchPivot->SetupAttachment(YawPivot);
    PitchPivot->SetRelativeRotation(FRotator(-50.0f, 0.0f, 0.0f)); // Isometric pitch

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(PitchPivot);
    SpringArm->TargetArmLength = 0.0f; // No distance, camera directly on pivot
    SpringArm->bDoCollisionTest = false;

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
    Camera->SetProjectionMode(ECameraProjectionMode::Orthographic);
    Camera->SetOrthoWidth(4000.0f); // Default zoom level
}

void ARTSCameraPawn::BeginPlay()
{
    Super::BeginPlay();
    
    // Set initial camera rotation for isometric view
    UpdateCameraRotation();
}

void ARTSCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Bind movement inputs
    PlayerInputComponent->BindAxis("MoveForward", this, &ARTSCameraPawn::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ARTSCameraPawn::MoveRight);

    // Bind action inputs
    PlayerInputComponent->BindAction("RotateLeft", IE_Pressed, this, &ARTSCameraPawn::RotateLeft);
    PlayerInputComponent->BindAction("RotateRight", IE_Pressed, this, &ARTSCameraPawn::RotateRight);
    PlayerInputComponent->BindAction("ZoomIn", IE_Pressed, this, &ARTSCameraPawn::ZoomIn);
    PlayerInputComponent->BindAction("ZoomOut", IE_Pressed, this, &ARTSCameraPawn::ZoomOut);
    PlayerInputComponent->BindAction("FastPan", IE_Pressed, this, &ARTSCameraPawn::StartFastPan);
    PlayerInputComponent->BindAction("FastPan", IE_Released, this, &ARTSCameraPawn::StopFastPan);
}

void ARTSCameraPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Handle edge panning (EXACTLY as specified by Cursor)
    HandleEdgePanning(DeltaTime);
    
    // Apply map bounds clamping
    ClampCameraPosition();
}

void ARTSCameraPawn::HandleEdgePanning(float DeltaTime)
{
    // Early exit if edge panning disabled
    if (!EdgePanEnabled)
        return;

    // Get player controller
    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (!PC)
        return;

    // Get viewport size
    int32 ViewportSizeX, ViewportSizeY;
    PC->GetViewportSize(ViewportSizeX, ViewportSizeY);

    // Get mouse position scaled by DPI
    float MouseX, MouseY;
    PC->GetMousePositionScaledByDPI(MouseX, MouseY);

    // Check left edge (Mouse X <= EdgePanBorderPx) - EXACTLY as specified
    if (MouseX <= static_cast<float>(EdgePanBorderPx))
    {
        // Get YawPivot Right Vector
        FVector RightVector = YawPivot->GetRightVector();
        
        // Negate to get Left Vector
        FVector LeftVector = -RightVector;
        
        // Set Z=0 for horizontal movement only
        LeftVector.Z = 0.0f;
        
        // Normalize for consistent direction
        LeftVector.Normalize();
        
        // Apply Movement Input with Speed and DeltaTime
        float MovementScale = EdgePanSpeed * DeltaTime;
        AddMovementInput(LeftVector, MovementScale);
    }
    
    // TODO: Add right, top, bottom edge detection in future PR
    // Right edge: MouseX >= (ViewportSizeX - EdgePanBorderPx)
    // Top edge: MouseY <= EdgePanBorderPx
    // Bottom edge: MouseY >= (ViewportSizeY - EdgePanBorderPx)
}

void ARTSCameraPawn::MoveForward(float Value)
{
    if (Value != 0.0f)
    {
        // Screen-space movement using YawPivot Forward Vector (Z=0)
        FVector ForwardVector = YawPivot->GetForwardVector();
        ForwardVector.Z = 0.0f;
        ForwardVector.Normalize();
        
        float Speed = bIsFastPanning ? MovementSpeed * FastPanMultiplier : MovementSpeed;
        AddMovementInput(ForwardVector, Value * Speed);
    }
}

void ARTSCameraPawn::MoveRight(float Value)
{
    if (Value != 0.0f)
    {
        // Screen-space movement using YawPivot Right Vector (Z=0)
        FVector RightVector = YawPivot->GetRightVector();
        RightVector.Z = 0.0f;
        RightVector.Normalize();
        
        float Speed = bIsFastPanning ? MovementSpeed * FastPanMultiplier : MovementSpeed;
        AddMovementInput(RightVector, Value * Speed);
    }
}

void ARTSCameraPawn::RotateLeft()
{
    CurrentCameraYaw -= RotationSpeed;
    UpdateCameraRotation();
}

void ARTSCameraPawn::RotateRight()
{
    CurrentCameraYaw += RotationSpeed;
    UpdateCameraRotation();
}

void ARTSCameraPawn::ZoomIn()
{
    float CurrentWidth = Camera->OrthoWidth;
    float NewWidth = FMath::Clamp(CurrentWidth - ZoomSpeed, MinOrthoWidth, MaxOrthoWidth);
    Camera->SetOrthoWidth(NewWidth);
}

void ARTSCameraPawn::ZoomOut()
{
    float CurrentWidth = Camera->OrthoWidth;
    float NewWidth = FMath::Clamp(CurrentWidth + ZoomSpeed, MinOrthoWidth, MaxOrthoWidth);
    Camera->SetOrthoWidth(NewWidth);
}

void ARTSCameraPawn::StartFastPan()
{
    bIsFastPanning = true;
}

void ARTSCameraPawn::StopFastPan()
{
    bIsFastPanning = false;
}

void ARTSCameraPawn::ClampCameraPosition()
{
    FVector CurrentLocation = GetActorLocation();
    FVector ClampedLocation = FVector(
        FMath::Clamp(CurrentLocation.X, MinX, MaxX),
        FMath::Clamp(CurrentLocation.Y, MinY, MaxY),
        CurrentLocation.Z // Preserve Z coordinate
    );
    SetActorLocation(ClampedLocation);
}

void ARTSCameraPawn::UpdateCameraRotation()
{
    // Set YawPivot rotation for camera angle
    YawPivot->SetRelativeRotation(FRotator(0.0f, CurrentCameraYaw, 0.0f));
}
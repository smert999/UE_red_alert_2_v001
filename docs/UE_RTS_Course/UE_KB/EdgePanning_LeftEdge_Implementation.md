# Edge Panning (Left Edge) - Implementation Guide

## Overview
Implementing left edge panning for RTS camera when mouse cursor is within 15px of left screen border.

## Target Blueprint: BP_RTS_CameraPawn

### Variables to Add

#### 1. EdgePanEnabled
- **Type**: Boolean
- **Default Value**: true
- **Category**: Edge Panning
- **Tooltip**: Enable/disable edge panning functionality

#### 2. EdgePanBorderPx  
- **Type**: Integer
- **Default Value**: 15
- **Category**: Edge Panning
- **Tooltip**: Distance in pixels from screen edge to trigger panning

#### 3. EdgePanSpeed
- **Type**: Float
- **Default Value**: 12000.0
- **Category**: Edge Panning  
- **Tooltip**: Speed of edge panning movement

### Event Tick Implementation

#### Node Chain for Left Edge Detection:

```
Event Tick
├── Branch (Condition: EdgePanEnabled)
    ├── True:
        ├── Get Viewport Size (Player Controller 0)
        │   └── Break Vector2D (Viewport Size) → X, Y
        ├── Get Mouse Position Scaled by DPI (Player Controller 0)
        │   └── Break Vector2D (Mouse Position) → X, Y  
        ├── <= (Float) 
        │   ├── A: Mouse Position X
        │   └── B: EdgePanBorderPx (Cast to Float)
        └── Branch (Condition: Mouse X <= Border)
            ├── True: LEFT EDGE PANNING
            │   ├── YawPivot → Get Right Vector
            │   ├── Negate (Vector) → Inverted Right Vector
            │   ├── Make Vector (X, Y, Z=0) → Set Z to 0
            │   ├── Normalize (Vector) → Normalized Direction
            │   ├── Get World Delta Seconds
            │   ├── * (Float) → EdgePanSpeed × DeltaTime
            │   └── Add Movement Input
            │       ├── World Direction: Normalized Left Vector
            │       └── Scale Value: Speed × DeltaTime
            └── False: (No action)
    └── False: (No action)
```

### Detailed Node Setup:

#### Variables Access:
- **EdgePanEnabled**: Variable → Get EdgePanEnabled
- **EdgePanBorderPx**: Variable → Get EdgePanBorderPx  
- **EdgePanSpeed**: Variable → Get EdgePanSpeed

#### Input Detection:
- **Get Player Controller** (Index 0)
- **Get Viewport Size** (from Player Controller)
- **Get Mouse Position Scaled by DPI** (from Player Controller)

#### Movement Logic:
- **YawPivot Component** → Get Right Vector
- **Negate Vector** → Convert Right to Left direction
- **Make Vector** → Set Z=0 for horizontal movement only
- **Vector Normalize** → Ensure consistent movement speed
- **Add Movement Input** → Apply movement to pawn

#### Timing:
- **Get World Delta Seconds** → Frame-rate independent movement
- **Multiply** → EdgePanSpeed × DeltaTime for smooth movement

### Integration Points:

#### Event Graph Location:
- Add nodes to **Event Tick** in BP_RTS_CameraPawn
- Place after existing tick logic (if any)
- Before any existing clamp/bounds checking

#### Component References:
- **YawPivot**: Existing scene component in camera rig
- **PlayerController**: Get Player Controller (Index 0)
- **Add Movement Input**: Built-in Pawn function

### Testing Criteria:

1. **Functionality**:
   - Mouse at X ≤ 15px → Camera pans left
   - Mouse at X > 15px → No edge panning
   - EdgePanEnabled = false → No panning regardless of position

2. **Integration**:  
   - WASD movement still works
   - Zoom (mouse wheel) still works
   - Q/E rotation still works
   - Map bounds clamping still works

3. **Performance**:
   - Smooth movement at consistent speed
   - No stuttering or frame drops
   - Frame-rate independent movement

### Commit Strategy:

#### Commit 1: "Add edge panning variables"
- Add EdgePanEnabled (bool, default true)
- Add EdgePanBorderPx (int, default 15)  
- Add EdgePanSpeed (float, default 12000)

#### Commit 2: "Implement left edge panning logic"
- Add Event Tick mouse position detection
- Add left edge boundary check
- Add YawPivot-based left movement
- Connect all nodes with proper data flow

## Implementation Notes:

### Blueprint Execution Order:
1. Event Tick fires every frame
2. Check EdgePanEnabled first (early exit if disabled)
3. Get mouse position and viewport size
4. Compare mouse X with border threshold  
5. If within border, calculate left movement vector
6. Apply movement using Add Movement Input

### Vector Math:
- **YawPivot Right Vector**: Points right relative to camera
- **Negate Right Vector**: Points left relative to camera  
- **Z=0**: Ensures horizontal-only movement
- **Normalize**: Provides consistent direction regardless of camera rotation

### Performance Considerations:
- Mouse position checked every tick (necessary for responsiveness)
- Early exit when EdgePanEnabled = false
- Vector operations are lightweight
- Add Movement Input is optimized by UE5

This implementation follows the exact specifications provided and integrates with the existing YawPivot/PitchPivot camera architecture.
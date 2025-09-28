# Blueprint Implementation: Edge Panning (Right Edge)

## Target Blueprint: Content/Blueprints/BP_RTS_CameraPawn.uasset

### Variables (reuse existing)

- EdgePanEnabled (Boolean) = true
- EdgePanBorderPx (Integer) = 15
- EdgePanSpeed (Float) = 12000.0

### Event Graph Modification

Add logic to `Event Tick` (Then1 in Sequence), before map clamps (Then2).

#### Node Chain (Right Edge Detection and Movement)

```
Event Tick
├── Sequence
    ├── Then0: (empty)
    ├── Then1: EDGE PANNING LOGIC
    │   ├── Branch (Condition: EdgePanEnabled)
    │   │   └── True:
    │   │       ├── Get Player Controller (Index: 0)
    │   │       ├── Get Mouse Position Scaled by DPI (Target: PC)
    │   │       │   └── Break Vector2D → MouseX, MouseY
    │   │       ├── Get Viewport Size (Target: PC)
    │   │       │   └── Break Vector2D → ViewX, ViewY
    │   │       ├── - (Float) (A: ViewX, B: CastToFloat(EdgePanBorderPx)) → RightThresholdX
    │   │       ├── >= (Float) (A: MouseX, B: RightThresholdX)
    │   │       └── Branch (Condition: Mouse at Right Edge)
    │   │           └── True:
    │   │               ├── YawPivot → Get Right Vector
    │   │               ├── Make Vector (X: Right.X, Y: Right.Y, Z: 0.0)
    │   │               ├── Normalize (Vector)
    │   │               ├── Get World Delta Seconds
    │   │               ├── * (Float) → EdgePanSpeed × DeltaSeconds
    │   │               └── Add Movement Input
    │   │                   ├── World Direction: Normalized Vector
    │   │                   └── Scale Value: Speed × Delta
    └── Then2: MAP CLAMPS (X/Y)
```

### Detailed Notes

- Right-edge detection compares `MouseX` against `ViewportWidth - EdgePanBorderPx`.
- Movement direction for right edge uses `YawPivot.GetRightVector` flattened to Z=0 and normalized.
- Scale movement by `EdgePanSpeed * GetWorldDeltaSeconds` for frame-rate independence.
- Keep execution order: Then1 (edge panning) → Then2 (map bounds clamp).

### Testing

1. PIE → move cursor to the rightmost ~15 px of the screen.
2. Camera should pan right smoothly.
3. Move cursor away → panning stops.
4. Toggle `EdgePanEnabled` off → no panning occurs.

### Integration

- Works alongside WASD/Zoom/Rotation.
- No C++ required; Blueprint-only.



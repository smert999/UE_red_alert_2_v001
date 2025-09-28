# Blueprint Implementation: Edge Panning (Top & Bottom Edges)

## Target Blueprint: Content/Blueprints/BP_RTS_CameraPawn.uasset

### Variables (reuse existing)

- EdgePanEnabled (Boolean) = true
- EdgePanBorderPx (Integer) = 15
- EdgePanSpeed (Float) = 12000.0

### Event Graph Placement

Add to `Event Tick` → `Sequence` → `Then1` (Edge Panning), before `Then2` map clamps.

### Top Edge Detection and Movement

```
Get Player Controller (Index 0)
Get Mouse Position Scaled by DPI → Break Vector2D → MouseX, MouseY
Get Viewport Size → Break Vector2D → ViewX, ViewY
- (Float) (A: ViewY, B: CastToFloat(EdgePanBorderPx)) → TopThresholdY
>= (Float) (A: MouseY, B: TopThresholdY)
Branch (Mouse at Top Edge)
  True:
    YawPivot → Get Forward Vector
    Make Vector (X: Fwd.X, Y: Fwd.Y, Z: 0.0)
    Normalize (Vector)
    Get World Delta Seconds
    * (Float) → EdgePanSpeed × DeltaSeconds
    Add Movement Input (Direction: Normalized, Scale: Speed × Delta)
```

### Bottom Edge Detection and Movement

```
<= (Float) (A: MouseY, B: CastToFloat(EdgePanBorderPx))
Branch (Mouse at Bottom Edge)
  True:
    YawPivot → Get Forward Vector
    Negate (Vector) → Inverted Forward
    Make Vector (X: -Fwd.X, Y: -Fwd.Y, Z: 0.0)
    Normalize (Vector)
    Get World Delta Seconds
    * (Float) → EdgePanSpeed × DeltaSeconds
    Add Movement Input (Direction: Normalized, Scale: Speed × Delta)
```

### Notes

- Top edge uses `YawPivot.GetForwardVector` (Z=0, normalized).
- Bottom edge uses the negated forward vector (Z=0, normalized).
- Use separate branches so top and bottom do not conflict in one frame.
- Keep this block in the same `Then1` sequence as left/right logic.

### Testing

1. Move cursor to the top ~15 px → camera pans forward (screen up).
2. Move cursor to the bottom ~15 px → camera pans backward (screen down).
3. Confirm correct behavior when cursor is in corners (vector sums feel natural).
4. Toggle `EdgePanEnabled` to verify enable/disable.



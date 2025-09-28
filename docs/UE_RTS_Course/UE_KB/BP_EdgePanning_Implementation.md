# Blueprint Implementation: Edge Panning (Left Edge Only)

## Target Blueprint: Content/Blueprints/BP_RTS_CameraPawn.uasset

### Variables to Add

Open BP_RTS_CameraPawn → Variables Tab → Add New:

#### 1. EdgePanEnabled
- **Variable Type**: Boolean
- **Default Value**: ✅ true (checked)
- **Category**: Edge Panning
- **Tooltip**: "Enable/disable edge panning functionality"

#### 2. EdgePanBorderPx  
- **Variable Type**: Integer
- **Default Value**: 15
- **Category**: Edge Panning
- **Tooltip**: "Distance in pixels from screen edge to trigger panning"

#### 3. EdgePanSpeed
- **Variable Type**: Float
- **Default Value**: 12000.0
- **Category**: Edge Panning
- **Tooltip**: "Speed of edge panning movement"

### Event Graph Modification

Open BP_RTS_CameraPawn → Event Graph → Find **Event Tick**

#### Node Chain to Add (after existing Event Tick logic):

```
Event Tick
├── Branch (Condition: EdgePanEnabled)
    └── True Pin:
        ├── Get Player Controller (Player Index: 0)
        ├── Get Mouse Position Scaled by DPI (Target: Player Controller)
        ├── Break Vector 2D (Input: Mouse Position) → X, Y outputs
        ├── Get Viewport Size (Target: Player Controller)  
        ├── <= (Float) (A: Mouse X, B: Cast To Float(EdgePanBorderPx))
        └── Branch (Condition: Mouse X <= Border)
            └── True Pin:
                ├── YawPivot → Get Right Vector
                ├── Negate (Vector) → Inverted Right Vector
                ├── Make Vector (X: -Right.X, Y: -Right.Y, Z: 0.0)
                ├── Vector Normalize
                ├── Get World Delta Seconds
                ├── Multiply (Float) (A: EdgePanSpeed, B: Delta Seconds)
                └── Add Movement Input (World Direction: Normalized Vector, Scale Value: Speed×Delta)
```

### Detailed Node Setup

#### 1. Edge Panning Enabled Check
- **Node**: Branch
- **Condition**: EdgePanEnabled (variable)
- **Location**: Connect to Event Tick after existing logic

#### 2. Get Mouse Position ⚠️ IMPORTANT FIX
- **Node**: Get Player Controller (Player Index: 0)
- **Node**: Get Mouse Position (Target: Player Controller output) ⚠️ NOT "Scaled by DPI"!
- **Node**: Break Vector 2D (Input: Mouse Position output)
- **Use**: X output for edge detection
- **Note**: DPI scaling can cause coordinate issues - use regular Get Mouse Position

#### 3. Get Viewport Size (for reference)
- **Node**: Get Viewport Size (Target: Player Controller output)
- **Purpose**: Available for future edge implementations

#### 4. Left Edge Detection
- **Node**: <= (Float)
- **A Input**: Mouse Position X (from Break Vector 2D)
- **B Input**: Cast To Float → EdgePanBorderPx (variable)
- **Node**: Branch (Condition: <= output)

#### 5. Calculate Left Movement Vector
- **Node**: YawPivot (Component Reference) → Get Right Vector
- **Node**: Negate (Vector) (Input: Right Vector)
- **Node**: Make Vector (X: Negate.X, Y: Negate.Y, Z: 0.0)
- **Node**: Vector Normalize (Input: Make Vector output)

#### 6. Apply Movement
- **Node**: Get World Delta Seconds
- **Node**: Multiply (Float) (A: EdgePanSpeed, B: Delta Seconds)
- **Node**: Add Movement Input
  - **World Direction**: Normalized Vector
  - **Scale Value**: Multiply output

### Pin Connections

```
Event Tick → [existing logic] → Branch(EdgePanEnabled)
                                    ├─ False → (no action)
                                    └─ True → Get Player Controller
                                              └─ Get Mouse Position Scaled by DPI
                                                 └─ Break Vector 2D → X
                                                    └─ <= (X, Cast(EdgePanBorderPx))
                                                       └─ Branch(mouse at edge)
                                                          ├─ False → (no action)
                                                          └─ True → YawPivot.GetRightVector
                                                                   └─ Negate
                                                                      └─ Make Vector(X,Y,0)
                                                                         └─ Normalize
                                                                            └─ Add Movement Input
                                                                               ├─ Direction: Normalized Vector
                                                                               └─ Scale: EdgePanSpeed × DeltaSeconds
```

### Component References

- **YawPivot**: Use existing YawPivot component reference
- **Player Controller**: Get Player Controller (Index 0)
- **Add Movement Input**: Built-in Pawn function

### Testing Verification

After implementation:
1. **Play in Editor** (PIE)
2. **Move mouse to left edge** (X ≤ 15px)
3. **Camera should pan left** smoothly
4. **Move mouse away** → panning stops
5. **Disable EdgePanEnabled** → no panning occurs

### Integration Notes

- **Preserve existing logic**: Add after current Event Tick nodes
- **No conflicts**: Edge panning works alongside WASD/Zoom/Rotation
- **Frame-rate independent**: Uses Get World Delta Seconds
- **Configurable**: All parameters exposed as Blueprint variables

### Performance

- **Lightweight**: Mouse position checked once per tick
- **Optimized**: Early exit when EdgePanEnabled = false
- **Efficient**: Vector operations are hardware-accelerated
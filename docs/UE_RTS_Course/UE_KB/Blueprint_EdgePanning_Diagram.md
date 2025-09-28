# Edge Panning Blueprint Diagram (ASCII)

## Node Connection Flow

```
Event Tick
    ║
    ╠══► Get Actor Location ─► Break Vector ─► Clamp(X) ──┐
    ║                                      ├► Clamp(Y) ──┤
    ║                                                     ▼
    ║                                               Make Vector ─► Set Actor Location
    ║
    ╠══► Sequence
          ║
          ╠═► Then0: (empty)
          ║
          ╠═► Then1: EDGE PANNING LOGIC (ALL EDGES)
          ║    ║
          ║    ╠═► Branch(EdgePanEnabled) ─── True ──► Get Player Controller
          ║    ║                                         ║
          ║    ║                                         ▼
          ║    ║                                  Get Mouse Position Scaled by DPI
          ║    ║                                         ║
          ║    ║                                         ▼
          ║    ║                           ┌──────────── Left Edge (X ≤ Border)
          ║    ║                           │   YawPivot.Right → *(-1) → Z=0 → Normalize → Add Movement
          ║    ║                           │
          ║    ║                           ├──────────── Right Edge (X ≥ ViewX - Border)
          ║    ║                           │   YawPivot.Right → Z=0 → Normalize → Add Movement
          ║    ║                           │
          ║    ║                           ├──────────── Top Edge (Y ≥ ViewY - Border)
          ║    ║                           │   YawPivot.Forward → Z=0 → Normalize → Add Movement
          ║    ║                           │
          ║    ║                           └──────────── Bottom Edge (Y ≤ Border)
          ║    ║                               YawPivot.Forward → *(-1) → Z=0 → Normalize → Add Movement
          ║    ╚══════════════════════════════════════════════════════════╗
          ║                                                               ║
          ╚═► Then2: MAP CLAMPS ◄═══════════════════════════════════════════╝
               (X/Y boundary enforcement)
```

## Pin Connection Details

### Branch(EdgePanEnabled)
```
[EdgePanEnabled] ──────► [Condition]
                         ║
                    True ╠═► [Get Player Controller]
                         ║
                   False ╚═► (no action)
```

### Mouse Position Check
```
[Get Mouse Position] ──► [Break Vector 2D] ──► [Location X] ──► [<= Float]
                                                                    ║
[EdgePanBorderPx] ──────────────────────────────────────────────► [B]
                                                                    ║
                                                               [Result] ──► [Branch]
```

### YawPivot Movement Chain
```
[YawPivot] ──► [Get Right Vector] ──► [* (-1)] ──► [Break Vector] ──► [Make Vector]
                                                        ║                  ║
                                                   [X] ─┴─► [X]            ║
                                                   [Y] ───► [Y]            ║
                                                            [Z] = 0.0      ║
                                                                           ▼
                                                                   [Normalize]
                                                                           ║
[EdgePanSpeed] ──► [*] ◄── [Get World Delta Seconds]                     ║
                   ║                                                      ║
                   ▼                                                      ║
           [Add Movement Input] ◄─────────────────────────────────────────┘
           (World Direction, Scale Value)
```

## Variable References

```
📦 Edge Panning Variables:
├─ EdgePanEnabled (Boolean) = true
├─ EdgePanBorderPx (Integer) = 15  
└─ EdgePanSpeed (Float) = 12000.0

📦 Map Bounds Variables:
├─ MinX (Float) = -50000
├─ MaxX (Float) = +50000
├─ MinY (Float) = -50000  
└─ MaxY (Float) = +50000

📦 Components:
└─ YawPivot (Scene Component)
```

## Execution Order

```
1. Event Tick fires every frame
2. Then0: (reserved for future use)
3. Then1: Edge Panning Logic
   ├─ Check EdgePanEnabled
   ├─ Get mouse position  
   ├─ Check if at left edge (X ≤ 15px)
   └─ Apply left movement if true
4. Then2: Map Bounds Clamping
   ├─ Get current actor location
   ├─ Clamp X between MinX and MaxX
   ├─ Clamp Y between MinY and MaxY  
   └─ Set new clamped location
```

## Color Coding Reference

- 🔴 **Execution Pins** (white lines in Blueprint)
- 🟡 **Data Pins** (colored lines - Vector=yellow, Float=green, Boolean=red)
- 🟢 **Variable References** (green in diagram)
- 🔵 **Component References** (blue in diagram)

# Edge Panning Debug Guide

## 🔍 Right Edge Not Working - Systematic Debug

### Problem Description
Logic appears correct but right edge panning doesn't trigger movement.

### Debug Setup

#### Add Print String nodes at key points:

1. **After EdgePanEnabled Check:**
```
Branch(EdgePanEnabled) → True → Print String("✅ EdgePan enabled, checking right edge...")
```

2. **Mouse Position Debug:**
```
Get Mouse Position Scaled by DPI → Print String("🖱️ Mouse: X=" + ToString(LocationX) + " Y=" + ToString(LocationY))
```

3. **Viewport Size Debug:**
```
Get Viewport Size → Print String("📺 Screen: " + ToString(SizeX) + "x" + ToString(SizeY))
```

4. **Boundary Calculation Debug:**
```
SizeX - EdgePanBorderPx → Print String("📏 Right boundary: " + ToString(Result))
```

5. **Comparison Result Debug:**
```
>= (float) → Print String("🎯 At right edge: " + ToString(Result))
```

6. **Movement Trigger Debug:**
```
Branch(At Right Edge) → True → Print String("🚀 RIGHT MOVEMENT TRIGGERED!")
```

### Expected Debug Output

When moving mouse to right edge, you should see:
```
✅ EdgePan enabled, checking right edge...
🖱️ Mouse: X=1910 Y=540
📺 Screen: 1920x1080  
📏 Right boundary: 1905
🎯 At right edge: true
🚀 RIGHT MOVEMENT TRIGGERED!
```

### Common Issues & Solutions

#### Issue 1: No debug output at all
**Symptom:** No Print String messages appear
**Cause:** Right edge branch not connected to Event Tick
**Fix:** Check Sequence connections

#### Issue 2: EdgePan check fails
**Symptom:** Only see "EdgePan enabled" message on left edge, not right
**Fix:** Check EdgePanEnabled variable is true

#### Issue 3: Mouse position not detected
**Symptom:** No mouse coordinates shown
**Cause:** Get Mouse Position not working
**Fix:** 
- Check Player Controller connection
- Check Return Value from Get Mouse Position
- Try different player index (0 vs 1)

#### Issue 4: Wrong viewport size
**Symptom:** Screen shows 0x0 or wrong resolution
**Cause:** Get Viewport Size not connected properly
**Fix:** Use same Player Controller for both mouse and viewport

#### Issue 5: Boundary calculation wrong
**Symptom:** Right boundary shows 15 instead of (ScreenWidth - 15)
**Cause:** Subtraction pins reversed
**Fix:** Size X should go to first input, EdgePanBorderPx to second

#### Issue 6: Mouse never reaches boundary
**Symptom:** Mouse X never >= boundary value
**Cause:** DPI scaling or window/fullscreen mode
**Fix:** 
- Test in fullscreen mode
- Check if using Get Mouse Position instead of Scaled by DPI
- Lower EdgePanBorderPx temporarily (try 50 instead of 15)

#### Issue 7: Movement triggers but no motion
**Symptom:** "MOVEMENT TRIGGERED" appears but camera doesn't move
**Cause:** Movement logic issue
**Fix:**
- Check Add Movement Input is connected
- Check World Direction is valid (not zero vector)
- Check Scale Value > 0
- Check FloatingPawnMovement component exists

### Quick Test Values

For testing, temporarily change:
- **EdgePanBorderPx = 100** (larger area)
- **EdgePanSpeed = 50000** (faster movement)

### Advanced Debug: Manual Movement Test

Add temporary button to test movement without edge detection:
```
InputAction(TestRightMove) → Add Movement Input
    World Direction: YawPivot.RightVector(normalized, Z=0)
    Scale Value: 20000
```

If manual movement works, problem is in edge detection.
If manual movement fails, problem is in movement logic.

### Resolution Verification

Check your screen resolution matches expectations:
- 1920x1080 → Right edge at X ≥ 1905
- 1366x768 → Right edge at X ≥ 1351  
- 2560x1440 → Right edge at X ≥ 2545

### Final Checklist

✅ EdgePanEnabled = true  
✅ EdgePanBorderPx = 15 (or higher for testing)  
✅ Right edge branch connected to Event Tick  
✅ Same Player Controller used for mouse and viewport  
✅ Print String nodes added for debugging  
✅ Testing in PIE with mouse at actual right screen edge  
✅ YawPivot component reference is valid (not None)  
✅ Add Movement Input receives valid direction vector  

### Emergency Workaround

If still not working, try simplified version:
```
Event Tick → Get Mouse Position → Break Vector 2D → > (float) 1800 → Branch → Movement
```

This bypasses viewport calculation and uses fixed boundary for 1920px screens.
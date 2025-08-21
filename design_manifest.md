# Design Manifest – Rhythm Game

## 1. Coordinate System
- All positions, velocities, and sizes are expressed in **World Units (WU)**.
- 1 WU = 20 pixels.
- By convention:
  - Sprites use bottom-center as their origin (y=0 → sits on ground).
  - Cubes are centered on their origin (default raylib behavior).

## 2. Textures
- All block/atlas textures are multiples of 20px.
- Each block texture must include at least a **1px padding** around the top of the block
  to prevent upscaling artifacts resulting in flickering pixels when the world moves.
- Spritesheets:
  - Frame size: (currently) 16x32 px, may change later when not using placeholders anymore
  - Animation frames for **one** specific cycle are laid out horizontally
  - Stack each new animation cycle in a sprite sheet vertically
  - Example:
    walk cycle forwards = 4 frames → 64x32 px row  
    walk cycle left = 4 frames -> 64x32 px row
    => Whole spritsheet has height of 64 with the two animations stacked **on top** of each other
  - When drawing frames from a sprite sheet, subtract 1px from frame width to avoid bleeding into next frame.


## 3. Camera
- Perspective camera with fovy ~60°.
- Camera looks toward `z = -2.5` (center of lanes).

## 4. Entities
- Player sprite: **1x2 WU**.
- Lane width: 1 WU each, 5 lanes total = 5 WU.
- Obstacles must align to WU grid.
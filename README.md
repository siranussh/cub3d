# cub3D

*This project has been created as part of the 42 curriculum by anavagya, sihakoby.*

## Description

**cub3D** is a graphic design project inspired by the world-famous Wolfenstein 3D game, which was the first FPS ever. This project explores ray-casting techniques to create a dynamic view inside a maze from a first-person perspective.

The goal of cub3D is to create a realistic 3D graphical representation of the inside of a maze from a first-person perspective using the Ray-Casting principles. The project uses the miniLibX library for rendering graphics and implements essential game mechanics including:

- **Ray-casting engine**: Renders a 3D perspective from a 2D map
- **Texture mapping**: Applies different textures to walls based on cardinal direction (North, South, East, West)
- **Player movement**: WASD keys for forward/backward/strafe movement
- **Camera rotation**: Arrow keys for looking left and right
- **Map parsing and validation**: Robust validation ensuring maps are properly enclosed and formatted

The project reinforces understanding of:
- Mathematical concepts (trigonometry, vector mathematics)
- Graphics programming fundamentals
- Game loop architecture
- Memory management in C
- File parsing and validation

## Instructions

### Prerequisites

This project requires:
- GCC or compatible C compiler
- Make
- X11 development libraries (for Linux)
- MiniLibX library (included in the repository)

### Execution

Run the program with a valid map file:

```bash
./cub3D maps/map01.cub
```

**Map file format:**

The `.cub` file must contain:
1. Texture paths for each cardinal direction:
   - `NO ./path/to/north_texture.xpm`
   - `SO ./path/to/south_texture.xpm`
   - `WE ./path/to/west_texture.xpm`
   - `EA ./path/to/east_texture.xpm`

2. Floor and ceiling colors (RGB format):
   - `F 220,100,0` (Floor color)
   - `C 225,30,0` (Ceiling color)

3. The map itself composed of:
   - `1`: Walls
   - `0`: Empty space (walkable)
   - `N`, `S`, `E`, `W`: Player starting position and orientation
   - The map must be surrounded by walls (1s)

**Example map file** (`maps/map01.cub`):
```
NO ./textures/wall_1.xpm
SO ./textures/wall_1.xpm
WE ./textures/wall_2.xpm
EA ./textures/wall_2.xpm

C 0,0,0
F 20,20,20

111111111111111
1010000000000N1
101000000000001
111111111111111
```

### Controls

- **W**: Move forward
- **S**: Move backward
- **A**: Strafe left
- **D**: Strafe right
- **Left Arrow**: Rotate camera left
- **Right Arrow**: Rotate camera right
- **ESC**: Exit the program
- **X** (window close button): Exit the program

## Features

### Implemented Features

- ✅ Ray-casting rendering engine
- ✅ Textured walls with different textures per cardinal direction
- ✅ Smooth player movement (WASD)
- ✅ Camera rotation (arrow keys)
- ✅ Floor and ceiling coloring
- ✅ Comprehensive map validation:
  - Map enclosure verification
  - Valid character checking
  - Player position validation
  - Empty line detection
  - Flood fill algorithm for openness detection
- ✅ Robust error handling and memory management
- ✅ Support for spaces and tabs in map files

### Map Validation Details

The validation system ensures:
1. Map is surrounded by walls (1s)
2. Only one player starting position exists
3. No invalid characters in the map
4. No empty lines within the map
5. Player cannot escape the map boundaries
6. Spaces/tabs are properly handled as non-walkable areas

## Resources

### Classic References

**Ray-Casting Theory:**
- [Lode's Computer Graphics Tutorial - Raycasting](https://lodev.org/cgtutor/raycasting.html) - Comprehensive guide to ray-casting techniques
- [Permadi's  Ray-Casting Tutorial](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/) - Detailed explanation of ray-casting mathematics
- [Wikipedia: Ray casting](https://en.wikipedia.org/wiki/Ray_casting) - Fundamental concepts

**Graphics Programming:**
- [MiniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx) - Reference for the graphics library used
- [Wolfenstein 3D Source Code](https://github.com/id-Software/wolf3d) - Original inspiration

**Mathematics:**
- [Trigonometry in Game Development](https://www.mathopenref.com/trig.html) - Essential trigonometric concepts
- DDA (Digital Differential Analyzer) algorithm for line drawing

## Technical Choices

### Ray-Casting Implementation
The project uses a DDA-based ray-casting algorithm that:
1. Casts one ray per screen column (1280 rays for 1280px width)
2. Calculates wall distance using the DDA algorithm
3. Applies fish-eye correction to prevent distortion
4. Determines wall height based on distance
5. Samples the appropriate texture based on wall orientation

### Map Representation
Maps use a dual representation:
- **Original map**: As parsed from the file, preserving format
- **Rectangular map**: Normalized to a rectangle with '6' filling empty spaces for efficient validation

### Validation Strategy
Multi-layered validation approach:
1. File format validation
2. Texture and color parsing
3. Character validation
4. Edge enclosure checking
5. Adjacent space checking
6. Flood fill for complete enclosure verification

---

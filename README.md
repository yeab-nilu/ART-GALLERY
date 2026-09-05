# EMTY Gallery — 3D Interactive Art Gallery

A first-person 3D art gallery built with OpenGL / FreeGLUT. Walk through a
lobby and two side rooms, browse 24 paintings, and view each one's title
and description either by walking up to it or by clicking on it directly.

## Features

- First-person movement and mouse-look through a 3-room gallery (lobby +
  left room + right room), connected by doorways.
- A wooden entrance sign reading **"WELCOME TO EMTY GALLERY"**, built from
  real 3D geometry (vector/stroke-font text) so it sits fixed on the wall
  and scales naturally with distance, rather than floating like a flat
  screen overlay.
- 24 textured paintings, each with a name and a short description shown
  on an in-scene information panel.
- Two ways to view a painting's details:
  - Walk close to it and press **E**.
  - Click directly on it from anywhere in the room — a ray is cast from
    the clicked pixel into the 3D scene, so you don't need to walk up or
    aim a crosshair first.
- Paintings automatically scale to fit their frame while preserving each
  image's original aspect ratio.

## Controls

| Input             | Action                              |
|-------------------|--------------------------------------|
| `W` / `S`         | Move forward / backward              |
| `A` / `D`         | Strafe left / right                  |
| `←` / `→`         | Rotate view left / right             |
| `↑` / `↓`         | Move forward / backward              |
| Mouse             | Look around                          |
| Left click        | View details of the painting clicked |
| `E`               | Examine the nearest painting         |
| `Esc`             | Exit                                 |

## Gallery layout

```
                         BACK WALL
        ┌───────────────┬───────────────┐
        │   LEFT ROOM    │   RIGHT ROOM   │
        │  (paintings    │  (paintings    │
        │  1, 2, 17, 18, │  4, 5, 19, 20, │
        │  21, 22)       │  23, 24)       │
        └──────┐   │   ┌──────┘
               │ door │ door
        ┌──────┘   │   └──────┘
        │                        │
        │         LOBBY          │
        │  (entrance sign,       │
        │   paintings 7, 8,      │
        │   9-16 on the door     │
        │   partition walls)     │
        └────────────────────────┘
                        FRONT WALL
                    (entrance sign)
```

- **Lobby**: the entrance sign is on the front wall (the first thing you
  see when you spawn). Paintings 7 and 8 are on the lobby's back wall;
  paintings 9–16 are mounted on both faces of the two doorway partition
  walls (one side facing the lobby, the other facing into the room).
- **Left / right rooms**: each has paintings on its back wall (facing the
  lobby), its outer side wall, and its front wall.

## Requirements

- A C++ compiler with OpenGL / GLU support
- [FreeGLUT](http://freeglut.sourceforge.net/)
- [stb_image.h](https://github.com/nothings/stb) (single-header image
  loader — included in the project)

## Building

**Linux:**
```bash
g++ ArtGallery.cpp -o gallery -lglut -lGL -lGLU -lm
```

**Windows (MinGW):**
```bash
g++ ArtGallery.cpp -o ArtGallery.exe -lfreeglut -lopengl32 -lglu32
```

**Visual Studio:** create a new C++ console project, add `CGproject.cpp`
and `stb_image.h`, and link against `freeglut.lib`, `opengl32.lib`, and
`glu32.lib`.

## Required assets

Place 24 JPG images in a `textures/` folder next to the executable,
named `painting1.jpg` through `painting24.jpg`. Any resolution or aspect
ratio works — each image is automatically scaled to fit its frame while
keeping its proportions.

```
project/
├── CGproject.cpp
├── stb_image.h
└── textures/
    ├── painting1.jpg
    ├── painting2.jpg
    ├── ...
    └── painting24.jpg
```

## Customizing / adding more paintings

All painting data lives in a few parallel arrays near the top of the
file, plus a `paintingsInfo[]` array used for both the walk-up proximity
check and the click-to-view raycasting. To add a painting:

1. Increase `NUM_PAINTINGS`.
2. Add its filename to `paintingFiles[]`.
3. Add its title to `paintingNames[]`.
4. Add its description (up to 3 lines) to `paintingDescriptions[]`.
5. Add its wall, position, and size to `paintingsInfo[]`.
6. Call `drawBackPainting()`, `drawFrontPainting()`, `drawLeftPainting()`,
   or `drawRightPainting()` for it inside `drawPaintings()`, depending on
   which wall it's mounted on.

No other code needs to change — proximity detection, the info panel, and
mouse-click picking all read from these same arrays automatically.

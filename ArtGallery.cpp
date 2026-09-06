#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <GL/freeglut.h>
#include <cmath>
#include <cstdio>
#include <cstdlib>

// ============================================================
// WINDOW
// ============================================================

int windowWidth = 1280;
int windowHeight = 720;


// ============================================================
// CAMERA
// ============================================================

float camX = 0.0f;
float camY = 2.2f;
float camZ = 0.0f;

float yaw = 0.0f;
float pitch = 0.0f;

float moveSpeed = 0.12f;
float rotateSpeed = 2.5f;

bool keys[256] = {};

bool arrowUp = false;
bool arrowDown = false;
bool arrowLeft = false;
bool arrowRight = false;

int lastMouseX = 0;
int lastMouseY = 0;
bool firstMouse = true;


// ============================================================
// TEXTURES
// ============================================================

const int NUM_PAINTINGS = 24;

GLuint paintingTextures[NUM_PAINTINGS];

int paintingWidth[NUM_PAINTINGS];
int paintingHeight[NUM_PAINTINGS];

const char* paintingFiles[NUM_PAINTINGS] =
{
    "textures/painting1.jpg",
    "textures/painting2.jpg",
    "textures/painting3.jpg",
    "textures/painting4.jpg",
    "textures/painting5.jpg",
    "textures/painting6.jpg",
    "textures/painting7.jpg",
    "textures/painting8.jpg",
    "textures/painting9.jpg",
    "textures/painting10.jpg",
    "textures/painting11.jpg",
    "textures/painting12.jpg",
    "textures/painting13.jpg",
    "textures/painting14.jpg",
    "textures/painting15.jpg",
    "textures/painting16.jpg",
    "textures/painting17.jpg",
    "textures/painting18.jpg",
    "textures/painting19.jpg",
    "textures/painting20.jpg",
    "textures/painting21.jpg",
    "textures/painting22.jpg",
    "textures/painting23.jpg",
    "textures/painting24.jpg"
};

const char* paintingNames[NUM_PAINTINGS] =
{
    "The Starry Night",
    "Don't Peek",
    "Red or White",
    "Cosmic Iris",
    "The Fallen Angel",
    "The Pull",
    "The Crimson Tear",
    "The Smirking Jester",
    "The Reaching Hand",
    "Checkmate",
    "The Drained Soul",
    "Stormy Lighthouse",
    "Echoes of the Path",
    "The Show Must Go On",
    "The Unspent Self",
    "The Golden Pianist",
    "Autumn in the Deep Woods",
    "Voices in My Head",
    "Equestrian Elegance",
    "Abstract Contemplative Woman Portrait",
    "The Waterfall of Thoughts",
    "The Silent Weight of Regret",
    "The Blue Note",
    "Mdundiko"
};


// ============================================================
// PAINTING DESCRIPTIONS
//
// Each painting has up to 3 lines of description text,
// shown on the information panel when examined.
// ============================================================

const int MAX_DESC_LINES = 3;

const char* paintingDescriptions[NUM_PAINTINGS][MAX_DESC_LINES] =
{
   // 0 - The Starry Night
    {
        "electric blues and burning yellows blurring the cosmos",
        "the urgent brushstrokes transforming the village sky",
        "a symbol of new stories starting."
    },

    // 1 - Don't Peek
    {
        "A women blindfolded",
        "exploring themes mystery,sensuality, and the intensity of unspoken emotions,",
        "inviting the viewer to imagine what lies beyond the veil."
    },

    // 2 - Red or White
    {
        "A striking contrast between two bold colors,",
        "representing the duality of choice and",
        "the complexity of human nature."
    },

    // 3 - Cosmic Iris
    {
        "abstract artwork centers on a captivating eye",
        "a swirling kaleidoscope of deep purples and radiant oranges.",
        "The intricate geometric patterns mirroring the multifaceted layers of the human experience."
    },

    // 4 The Fallen Angel
    {
        "A profound collision of divinity and despair",
        "tracing the heavy burden of freedom and",
        "the raw ache of a fallen soul."
    },

    // 5 - The Pull
    {
        "An overwhelming entanglement of desire and restraint",
        "trapped in the desperate pull of outside forces",
        "yet completely anchored in the quiet center of each other."
    },

    // 6 - The Crimson Tear
    {
        "An overwhelming surge of heartbreak and burning resilience,",
        "illuminated by a desperate, fiery warmth,",
        "as the soul looks upward through its deepest pain."
    },

    // 7 - The Smirking Jester
    {
        "A haunting intersection of mockery and profound sorrow,",
        "masking a silent, hollow emptiness behind a frozen grin,",
        "where performance becomes the ultimate shield from reality."
    },

    // 8 - The Reaching Hand
    {
        "A desperate plea reaching out from the absolute void,",
        "shackled by a chorus of heavy, clinging anchors,",
        "yet straining fiercely toward an unseen beacon of hope."
    },

    // 9 - Checkmate
    {
        "A final surrender on a battlefield of squares,",
        "where the fallen crown yields to absolute defeat,",
        "leaving only the quiet triumph of the standing king."
    },

    // 10 - The Drained Soul
    {
        "A quiet dissolution of identity and strength,",
        "dissolving slowly under the weight of unseen exhaustion,",
        "where keeping it together gives way to beautifully falling apart."
    },

    // 11 - Stormy Lighthouse
    {
        "An unwavering anchor amid the howling chaos,",
        "cutting through the heavy, suffocating darkness,",
        "to cast a fierce, golden promise of safe passage."
    },

    // 12 - Echoes of the Path
    {
        "A solitary journey through a chaotic web of thoughts",
        "navigating the tangled, winding complexities of mind and time",
        "yet steadily moving forward toward a distant, clear horizon."
    },

    // 13 - The Show Must Go On
    {
        "A forced smile carving through a sea of neon agony,",
        "masking deep sorrow behind the bright suit of a card game,",
        "while completely severed from the safety of her own reality."
    },

    // 14 - The Unspent Self
    {
        "A gentle surrender into a sanctuary of quiet solace,",
        "sheltered beneath a heavy, textured canopy of snow-white peace,",
        "where the weary mind finally finds comfort in a warm, protective embrace."
    },

    // 15 - The Golden Pianist
    {
        "A soulful melody woven from threads of pure gold,",
        "pouring out raw emotion into the keys of a grand piano",
        "as the spotlight bathes her solitary grace in radiant amber warmth."
    },

    // 16 - Autumn in the Deep Woods
    {
        "A vibrant celebration of nature's final, blazing transition,",
        "igniting the quiet woods with an explosive crown of gold and crimson,",
        "while a soft, silver mist gently swallows the secrets of the deeper forest."
    },

    // 17 - Voices in My Head
    {
        "A fractured mind echoing with a chorus of inner voices,",
        "shattered across a landscape of cool blues and electric purples,",
        "while a cold, silent moon anchors the quiet storm within."
    },

    // 18 - Equestrian Elegance
    {
        "An explosive rush of untamed freedom and wild grace,",
        "igniting the white canvas with powerful sweeps of amber and crimson,",
        "as the spirit of the stallion charges through a storm of abstract energy."
    },

    // 19 - Abstract Contemplative Woman Portrait
    {
        "A melancholic gaze frozen within a puzzle of patterns,",
        "resting a heavy head upon a delicate, searching hand,",
        "while a churning sky of amber clouds mirrors her restless mind."
    },

    // 20 - The Waterfall of Thoughts.
    {
        "A solitary soul standing at the edge of consciousness,",
        "surrounded by fractured, whispering faces of the inner self,",
        "as the waterfall of time cascades through a vibrant, chaotic mind."
    },

    // 21 - The Silent Weight of Regret.
    {
        "A silent plea swallowed down by a trembling, sheltering hand,",
        "shielding the bright shock of a single, sorrowful blue gaze,",
        "as the heavy texture of regret carves deep lines into the soul."
    },

    // 22 - The Blue Note
    {
        "A smoky melody escaping into a sea of midnight blue,",
        "pouring out raw heartache through the brass of a saxophone,",
        "as the golden light of the stage catches his final, breathless note."
    },

    // 23 - Mdundiko
    {
        "An explosive rhythm sweeping through a canvas of fire",
        "igniting the dynamic, sharp curves of tribal dancers,",
        "as the deep beat of the drum commands the soul to move."
    }
};


// ============================================================
// INTERACTION
// ============================================================

int nearbyPainting = -1;
bool showInfo = false;


// ============================================================
// PAINTING GEOMETRY (for mouse-click picking)
//
// Mirrors the positions passed into drawPaintings() below, so
// a click can be tested against each painting's wall plane
// without needing to walk up to it first.
// ============================================================

enum WallType
{
    WALL_BACK,  // any wall perpendicular to Z (back OR front wall - the ray math is identical either way)
    WALL_LEFT,
    WALL_RIGHT
};

struct PaintingInfo
{
    WallType wall;
    float x, y, z;
    float width;
    float height;
};

PaintingInfo paintingsInfo[NUM_PAINTINGS] =
{
    { WALL_BACK,  -17.0f, 4.3f, 8.55f,  4.0f, 5.0f }, // 0
    { WALL_BACK,  -13.0f, 4.3f, 8.55f,  3.2f, 5.0f }, // 1
    { WALL_LEFT,  -23.55f, 4.3f, 0.0f,  4.0f, 5.0f }, // 2
    { WALL_BACK,   13.0f, 4.3f, 8.55f,  3.2f, 5.0f }, // 3
    { WALL_BACK,   17.0f, 4.3f, 8.55f,  4.0f, 5.0f }, // 4
    { WALL_RIGHT,  23.55f, 4.3f, 0.0f,  4.0f, 5.0f }, // 5
    { WALL_BACK,   -3.0f, 4.3f, 8.55f,  4.0f, 5.0f }, // 6
    { WALL_BACK,    3.0f, 4.3f, 8.55f,  4.0f, 5.0f }, // 7

    // Left partition wall (previously bare on both faces)
    { WALL_LEFT,   -9.75f, 4.3f, -5.8f,  3.0f, 3.5f }, // 8  - lobby-facing, front segment
    { WALL_RIGHT, -10.25f, 4.3f, -5.8f,  3.0f, 3.5f }, // 9  - left-room-facing, front segment
    { WALL_LEFT,   -9.75f, 4.3f,  5.8f,  3.0f, 3.5f }, // 10 - lobby-facing, back segment
    { WALL_RIGHT, -10.25f, 4.3f,  5.8f,  3.0f, 3.5f }, // 11 - left-room-facing, back segment

    // Right partition wall (previously bare on both faces)
    { WALL_LEFT,   10.25f, 4.3f, -5.8f,  3.0f, 3.5f }, // 12 - right-room-facing, front segment
    { WALL_RIGHT,   9.75f, 4.3f, -5.8f,  3.0f, 3.5f }, // 13 - lobby-facing, front segment
    { WALL_LEFT,   10.25f, 4.3f,  5.8f,  3.0f, 3.5f }, // 14 - right-room-facing, back segment
    { WALL_RIGHT,   9.75f, 4.3f,  5.8f,  3.0f, 3.5f }, // 15 - lobby-facing, back segment

    // Left/right room front walls (previously completely bare)
    { WALL_BACK,  -17.0f, 4.3f, -8.55f,  4.0f, 5.0f }, // 16
    { WALL_BACK,  -13.0f, 4.3f, -8.55f,  3.2f, 5.0f }, // 17
    { WALL_BACK,   13.0f, 4.3f, -8.55f,  3.2f, 5.0f }, // 18
    { WALL_BACK,   17.0f, 4.3f, -8.55f,  4.0f, 5.0f },  // 19

    // Extra spots flanking the existing center painting on each outer wall
    { WALL_LEFT,  -23.55f, 4.3f, -6.0f,  3.5f, 4.5f }, // 20
    { WALL_LEFT,  -23.55f, 4.3f,  6.0f,  3.5f, 4.5f }, // 21
    { WALL_RIGHT,  23.55f, 4.3f, -6.0f,  3.5f, 4.5f }, // 22
    { WALL_RIGHT,  23.55f, 4.3f,  6.0f,  3.5f, 4.5f }  // 23
};


// ============================================================
// TEXTURE LOADING
// ============================================================

bool loadPainting(
    int index,
    const char* filename)
{
    int width;
    int height;
    int channels;

    unsigned char* image =
        stbi_load(
            filename,
            &width,
            &height,
            &channels,
            3
        );

    if (!image)
    {
        printf(
            "FAILED TO LOAD: %s\n",
            filename
        );

        printf(
            "Reason: %s\n",
            stbi_failure_reason()
        );

        return false;
    }

    paintingWidth[index] = width;
    paintingHeight[index] = height;

    glGenTextures(
        1,
        &paintingTextures[index]
    );

    glBindTexture(
        GL_TEXTURE_2D,
        paintingTextures[index]
    );

    glPixelStorei(
        GL_UNPACK_ALIGNMENT,
        1
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MIN_FILTER,
        GL_LINEAR
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MAG_FILTER,
        GL_LINEAR
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_S,
        GL_CLAMP
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_T,
        GL_CLAMP
    );

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGB,
        width,
        height,
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        image
    );

    glBindTexture(
        GL_TEXTURE_2D,
        0
    );

    stbi_image_free(image);

    printf(
        "Loaded: %s (%d x %d)\n",
        filename,
        width,
        height
    );

    return true;
}


void loadAllPaintings()
{
    printf("\n");
    printf("====================================\n");
    printf("LOADING ARTWORK\n");
    printf("====================================\n");

    for (int i = 0; i < NUM_PAINTINGS; i++)
    {
        paintingTextures[i] = 0;

        loadPainting(
            i,
            paintingFiles[i]
        );
    }

    printf("====================================\n\n");
}


// ============================================================
// BASIC CUBE
// ============================================================

void drawCube(
    float x,
    float y,
    float z,
    float sx,
    float sy,
    float sz)
{
    glPushMatrix();

    glTranslatef(
        x,
        y,
        z
    );

    glScalef(
        sx,
        sy,
        sz
    );

    glutSolidCube(1.0);

    glPopMatrix();
}


// ============================================================
// FLOOR
// ============================================================

void drawFloor()
{
    glDisable(GL_TEXTURE_2D);

    glColor3f(
        0.22f,
        0.22f,
        0.24f
    );

    glBegin(GL_QUADS);

    glVertex3f(
        -24.0f,
        0.0f,
        -9.0f
    );

    glVertex3f(
        24.0f,
        0.0f,
        -9.0f
    );

    glVertex3f(
        24.0f,
        0.0f,
        9.0f
    );

    glVertex3f(
        -24.0f,
        0.0f,
        9.0f
    );

    glEnd();
}


// ============================================================
// CEILING
// ============================================================

void drawCeiling()
{
    glDisable(GL_TEXTURE_2D);

    glColor3f(
        0.75f,
        0.75f,
        0.78f
    );

    glBegin(GL_QUADS);

    glVertex3f(
        -24.0f,
        8.0f,
        -9.0f
    );

    glVertex3f(
        24.0f,
        8.0f,
        -9.0f
    );

    glVertex3f(
        24.0f,
        8.0f,
        9.0f
    );

    glVertex3f(
        -24.0f,
        8.0f,
        9.0f
    );

    glEnd();
}


// ============================================================
// WALL
// ============================================================

void drawWall(
    float x,
    float y,
    float z,
    float width,
    float height,
    float depth)
{
    glDisable(GL_TEXTURE_2D);

    glColor3f(
        0.82f,
        0.80f,
        0.76f
    );

    drawCube(
        x,
        y,
        z,
        width,
        height,
        depth
    );
}


// ============================================================
// GALLERY ROOMS
//
// Layout:
//
//                  BACK
//
//       ┌───────────┬───────────┐
//       │           │           │
//       │  LEFT     │   RIGHT   │
//       │  ROOM     │   ROOM    │
//       │           │           │
//       └─────┐     │     ┌─────┘
//             │ LOBBY│
//             │      │
//       ┌─────┘      └─────┐
//       │                  │
//       │      LOBBY       │
//       │                  │
//       └──────────────────┘
//
// ============================================================

void buildGallery()
{
    drawFloor();

    drawCeiling();


    // ========================================================
    // OUTER BACK WALL
    // ========================================================

    drawWall(
        0.0f,
        4.0f,
        8.8f,
        48.0f,
        8.0f,
        0.4f
    );


    // ========================================================
    // OUTER LEFT WALL
    // ========================================================

    drawWall(
        -23.8f,
        4.0f,
        0.0f,
        0.4f,
        8.0f,
        18.0f
    );


    // ========================================================
    // OUTER RIGHT WALL
    // ========================================================

    drawWall(
        23.8f,
        4.0f,
        0.0f,
        0.4f,
        8.0f,
        18.0f
    );


    // ========================================================
    // FRONT WALL
    // ========================================================

    drawWall(
        0.0f,
        4.0f,
        -8.8f,
        48.0f,
        8.0f,
        0.4f
    );


    // ========================================================
    // LEFT ROOM PARTITION
    //
    // Wall at x = -10
    //
    // Door opening between z = -2.5 and 2.5
    // ========================================================

    drawWall(
        -10.0f,
        4.0f,
        -5.8f,
        0.4f,
        8.0f,
        6.0f
    );

    drawWall(
        -10.0f,
        4.0f,
        5.8f,
        0.4f,
        8.0f,
        6.0f
    );


    // ========================================================
    // RIGHT ROOM PARTITION
    //
    // Door opening between z = -2.5 and 2.5
    // ========================================================

    drawWall(
        10.0f,
        4.0f,
        -5.8f,
        0.4f,
        8.0f,
        6.0f
    );

    drawWall(
        10.0f,
        4.0f,
        5.8f,
        0.4f,
        8.0f,
        6.0f
    );
}


// ============================================================
// DOOR FRAME
// ============================================================

void drawDoorFrame(
    float x)
{
    glDisable(GL_TEXTURE_2D);

    glColor3f(
        0.25f,
        0.12f,
        0.04f
    );

    // Left vertical frame

    drawCube(
        x,
        3.5f,
        -2.5f,
        0.5f,
        7.0f,
        0.35f
    );

    // Right vertical frame

    drawCube(
        x,
        3.5f,
        2.5f,
        0.5f,
        7.0f,
        0.35f
    );

    // Top

    drawCube(
        x,
        7.0f,
        0.0f,
        0.5f,
        0.5f,
        5.35f
    );
}


// ============================================================
// PAINTING FRAME - BACK WALL
// ============================================================

void drawBackPaintingFrame(
    float x,
    float y,
    float z,
    float width,
    float height)
{
    glDisable(GL_TEXTURE_2D);

    glColor3f(
        0.20f,
        0.10f,
        0.035f
    );

    float frameThickness = 0.18f;

    drawCube(
        x,
        y + height / 2,
        z,
        width + 0.3f,
        frameThickness,
        0.15f
    );

    drawCube(
        x,
        y - height / 2,
        z,
        width + 0.3f,
        frameThickness,
        0.15f
    );

    drawCube(
        x - width / 2,
        y,
        z,
        frameThickness,
        height,
        0.15f
    );

    drawCube(
        x + width / 2,
        y,
        z,
        frameThickness,
        height,
        0.15f
    );
}


// ============================================================
// PAINTING - BACK WALL
// ============================================================

void drawBackPainting(
    int index,
    float x,
    float y,
    float z,
    float maxWidth,
    float maxHeight)
{
    if (index < 0 ||
        index >= NUM_PAINTINGS)
        return;

    if (paintingTextures[index] == 0)
        return;

    float aspect =
        (float)paintingWidth[index] /
        (float)paintingHeight[index];

    float width =
        maxWidth;

    float height =
        width / aspect;

    if (height > maxHeight)
    {
        height = maxHeight;

        width =
            height * aspect;
    }

    drawBackPaintingFrame(
        x,
        y,
        z - 0.03f,
        width,
        height
    );

    // IMPORTANT:
    // No lighting is used on paintings.

    glDisable(GL_LIGHTING);

    glEnable(GL_TEXTURE_2D);

    glBindTexture(
        GL_TEXTURE_2D,
        paintingTextures[index]
    );

    glColor3f(
        1.0f,
        1.0f,
        1.0f
    );

    float frontZ =
        z - 0.12f;

    glBegin(GL_QUADS);

    glTexCoord2f(
        0.0f,
        1.0f
    );

    glVertex3f(
        x - width / 2,
        y - height / 2,
        frontZ
    );

    glTexCoord2f(
        1.0f,
        1.0f
    );

    glVertex3f(
        x + width / 2,
        y - height / 2,
        frontZ
    );

    glTexCoord2f(
        1.0f,
        0.0f
    );

    glVertex3f(
        x + width / 2,
        y + height / 2,
        frontZ
    );

    glTexCoord2f(
        0.0f,
        0.0f
    );

    glVertex3f(
        x - width / 2,
        y + height / 2,
        frontZ
    );

    glEnd();

    glBindTexture(
        GL_TEXTURE_2D,
        0
    );

    glDisable(GL_TEXTURE_2D);

    glEnable(GL_LIGHTING);
}


// ============================================================
// PAINTING - FRONT WALL
//
// Mirror of drawBackPainting for the opposite (front) wall.
// Reuses the same frame, just nudged the other way in Z, and
// mirrors the image's X mapping so it isn't seen backwards -
// the same trick used between drawLeftPainting/drawRightPainting.
// ============================================================

void drawFrontPainting(
    int index,
    float x,
    float y,
    float z,
    float maxWidth,
    float maxHeight)
{
    if (index < 0 ||
        index >= NUM_PAINTINGS)
        return;

    if (paintingTextures[index] == 0)
        return;

    float aspect =
        (float)paintingWidth[index] /
        (float)paintingHeight[index];

    float width =
        maxWidth;

    float height =
        width / aspect;

    if (height > maxHeight)
    {
        height = maxHeight;

        width =
            height * aspect;
    }

    drawBackPaintingFrame(
        x,
        y,
        z + 0.03f,
        width,
        height
    );

    glDisable(GL_LIGHTING);

    glEnable(GL_TEXTURE_2D);

    glBindTexture(
        GL_TEXTURE_2D,
        paintingTextures[index]
    );

    glColor3f(
        1.0f,
        1.0f,
        1.0f
    );

    float frontZ =
        z + 0.12f;

    glBegin(GL_QUADS);

    glTexCoord2f(
        0.0f,
        1.0f
    );

    glVertex3f(
        x + width / 2,
        y - height / 2,
        frontZ
    );

    glTexCoord2f(
        1.0f,
        1.0f
    );

    glVertex3f(
        x - width / 2,
        y - height / 2,
        frontZ
    );

    glTexCoord2f(
        1.0f,
        0.0f
    );

    glVertex3f(
        x - width / 2,
        y + height / 2,
        frontZ
    );

    glTexCoord2f(
        0.0f,
        0.0f
    );

    glVertex3f(
        x + width / 2,
        y + height / 2,
        frontZ
    );

    glEnd();

    glBindTexture(
        GL_TEXTURE_2D,
        0
    );

    glDisable(GL_TEXTURE_2D);

    glEnable(GL_LIGHTING);
}


// ============================================================
// PAINTING FRAME - SIDE WALL
// ============================================================

void drawSideFrame(
    float x,
    float y,
    float z,
    float width,
    float height)
{
    glDisable(GL_TEXTURE_2D);

    glColor3f(
        0.20f,
        0.10f,
        0.035f
    );

    float t = 0.18f;

    drawCube(
        x,
        y + height / 2,
        z,
        0.15f,
        t,
        width + 0.3f
    );

    drawCube(
        x,
        y - height / 2,
        z,
        0.15f,
        t,
        width + 0.3f
    );

    drawCube(
        x,
        y,
        z - width / 2,
        0.15f,
        height,
        t
    );

    drawCube(
        x,
        y,
        z + width / 2,
        0.15f,
        height,
        t
    );
}


// ============================================================
// PAINTING - LEFT WALL
// ============================================================

void drawLeftPainting(
    int index,
    float x,
    float y,
    float z,
    float maxWidth,
    float maxHeight)
{
    if (paintingTextures[index] == 0)
        return;

    float aspect =
        (float)paintingWidth[index] /
        (float)paintingHeight[index];

    float width =
        maxWidth;

    float height =
        width / aspect;

    if (height > maxHeight)
    {
        height = maxHeight;

        width =
            height * aspect;
    }

    drawSideFrame(
        x + 0.03f,
        y,
        z,
        width,
        height
    );

    glDisable(GL_LIGHTING);

    glEnable(GL_TEXTURE_2D);

    glBindTexture(
        GL_TEXTURE_2D,
        paintingTextures[index]
    );

    glColor3f(
        1,
        1,
        1
    );

    float frontX =
        x + 0.12f;

    glBegin(GL_QUADS);

    glTexCoord2f(
        0,
        1
    );

    glVertex3f(
        frontX,
        y - height / 2,
        z - width / 2
    );

    glTexCoord2f(
        1,
        1
    );

    glVertex3f(
        frontX,
        y - height / 2,
        z + width / 2
    );

    glTexCoord2f(
        1,
        0
    );

    glVertex3f(
        frontX,
        y + height / 2,
        z + width / 2
    );

    glTexCoord2f(
        0,
        0
    );

    glVertex3f(
        frontX,
        y + height / 2,
        z - width / 2
    );

    glEnd();

    glBindTexture(
        GL_TEXTURE_2D,
        0
    );

    glDisable(GL_TEXTURE_2D);

    glEnable(GL_LIGHTING);
}


// ============================================================
// PAINTING - RIGHT WALL
// ============================================================

void drawRightPainting(
    int index,
    float x,
    float y,
    float z,
    float maxWidth,
    float maxHeight)
{
    if (paintingTextures[index] == 0)
        return;

    float aspect =
        (float)paintingWidth[index] /
        (float)paintingHeight[index];

    float width =
        maxWidth;

    float height =
        width / aspect;

    if (height > maxHeight)
    {
        height = maxHeight;

        width =
            height * aspect;
    }

    drawSideFrame(
        x - 0.03f,
        y,
        z,
        width,
        height
    );

    glDisable(GL_LIGHTING);

    glEnable(GL_TEXTURE_2D);

    glBindTexture(
        GL_TEXTURE_2D,
        paintingTextures[index]
    );

    glColor3f(
        1,
        1,
        1
    );

    float frontX =
        x - 0.12f;

    glBegin(GL_QUADS);

    glTexCoord2f(
        0,
        1
    );

    glVertex3f(
        frontX,
        y - height / 2,
        z + width / 2
    );

    glTexCoord2f(
        1,
        1
    );

    glVertex3f(
        frontX,
        y - height / 2,
        z - width / 2
    );

    glTexCoord2f(
        1,
        0
    );

    glVertex3f(
        frontX,
        y + height / 2,
        z - width / 2
    );

    glTexCoord2f(
        0,
        0
    );

    glVertex3f(
        frontX,
        y + height / 2,
        z + width / 2
    );

    glEnd();

    glBindTexture(
        GL_TEXTURE_2D,
        0
    );

    glDisable(GL_TEXTURE_2D);

    glEnable(GL_LIGHTING);
}


// ============================================================
// ALL PAINTINGS
// ============================================================

void drawPaintings()
{
    // ========================================================
    // LEFT ROOM
    // ========================================================

    drawBackPainting(
        0,
        -17.0f,
        4.3f,
        8.55f,
        4.0f,
        5.0f
    );

    drawBackPainting(
        1,
        -13.0f,
        4.3f,
        8.55f,
        3.2f,
        5.0f
    );

    drawLeftPainting(
        2,
        -23.55f,
        4.3f,
        0.0f,
        4.0f,
        5.0f
    );


    // ========================================================
    // RIGHT ROOM
    // ========================================================

    drawBackPainting(
        3,
        13.0f,
        4.3f,
        8.55f,
        3.2f,
        5.0f
    );

    drawBackPainting(
        4,
        17.0f,
        4.3f,
        8.55f,
        4.0f,
        5.0f
    );

    drawRightPainting(
        5,
        23.55f,
        4.3f,
        0.0f,
        4.0f,
        5.0f
    );


    // ========================================================
    // LOBBY
    // ========================================================

    drawBackPainting(
        6,
        -3.0f,
        4.3f,
        8.55f,
        4.0f,
        5.0f
    );

    drawBackPainting(
        7,
        3.0f,
        4.3f,
        8.55f,
        4.0f,
        5.0f
    );


    // ========================================================
    // LEFT PARTITION - FRONT SEGMENT (z = -5.8)
    // ========================================================

    drawLeftPainting(
        8,
        -9.75f,
        4.3f,
        -5.8f,
        3.0f,
        3.5f
    );

    drawRightPainting(
        9,
        -10.25f,
        4.3f,
        -5.8f,
        3.0f,
        3.5f
    );


    // ========================================================
    // LEFT PARTITION - BACK SEGMENT (z = 5.8)
    // ========================================================

    drawLeftPainting(
        10,
        -9.75f,
        4.3f,
        5.8f,
        3.0f,
        3.5f
    );

    drawRightPainting(
        11,
        -10.25f,
        4.3f,
        5.8f,
        3.0f,
        3.5f
    );


    // ========================================================
    // RIGHT PARTITION - FRONT SEGMENT (z = -5.8)
    // ========================================================

    drawLeftPainting(
        12,
        10.25f,
        4.3f,
        -5.8f,
        3.0f,
        3.5f
    );

    drawRightPainting(
        13,
        9.75f,
        4.3f,
        -5.8f,
        3.0f,
        3.5f
    );


    // ========================================================
    // RIGHT PARTITION - BACK SEGMENT (z = 5.8)
    // ========================================================

    drawLeftPainting(
        14,
        10.25f,
        4.3f,
        5.8f,
        3.0f,
        3.5f
    );

    drawRightPainting(
        15,
        9.75f,
        4.3f,
        5.8f,
        3.0f,
        3.5f
    );


    // ========================================================
    // LEFT ROOM - FRONT WALL (previously bare)
    // ========================================================

    drawFrontPainting(
        16,
        -17.0f,
        4.3f,
        -8.55f,
        4.0f,
        5.0f
    );

    drawFrontPainting(
        17,
        -13.0f,
        4.3f,
        -8.55f,
        3.2f,
        5.0f
    );


    // ========================================================
    // RIGHT ROOM - FRONT WALL (previously bare)
    // ========================================================

    drawFrontPainting(
        18,
        13.0f,
        4.3f,
        -8.55f,
        3.2f,
        5.0f
    );

    drawFrontPainting(
        19,
        17.0f,
        4.3f,
        -8.55f,
        4.0f,
        5.0f
    );


    // ========================================================
    // LEFT ROOM - OUTER WALL (flanking painting 3 / index 2)
    // ========================================================

    drawLeftPainting(
        20,
        -23.55f,
        4.3f,
        -6.0f,
        3.5f,
        4.5f
    );

    drawLeftPainting(
        21,
        -23.55f,
        4.3f,
        6.0f,
        3.5f,
        4.5f
    );


    // ========================================================
    // RIGHT ROOM - OUTER WALL (flanking painting 6 / index 5)
    // ========================================================

    drawRightPainting(
        22,
        23.55f,
        4.3f,
        -6.0f,
        3.5f,
        4.5f
    );

    drawRightPainting(
        23,
        23.55f,
        4.3f,
        6.0f,
        3.5f,
        4.5f
    );
}


// ============================================================
// SCULPTURE
// ============================================================

void drawSculpture(
    float x,
    float z)
{
    glDisable(GL_TEXTURE_2D);

    glColor3f(
        0.55f,
        0.30f,
        0.10f
    );

    // Base

    drawCube(
        x,
        0.5f,
        z,
        1.8f,
        1.0f,
        1.8f
    );

    glPushMatrix();

    glTranslatef(
        x,
        1.5f,
        z
    );

    glutSolidSphere(
        0.75,
        24,
        24
    );

    glTranslatef(
        0,
        0.9f,
        0
    );

    glutSolidSphere(
        0.5,
        24,
        24
    );

    glTranslatef(
        0,
        0.7f,
        0
    );

    glutSolidSphere(
        0.3,
        24,
        24
    );

    glPopMatrix();
}


// ============================================================
// DECORATIONS
// ============================================================

void drawDecorations()
{
    // Lobby sculpture

    drawSculpture(
        0,
        -3
    );

    // Left room sculpture

    drawSculpture(
        -16,
        2
    );

    // Right room sculpture

    drawSculpture(
        16,
        2
    );
}


// ============================================================
// LIGHTING
//
// Simple lighting only for the 3D objects.
// Paintings are deliberately unlit.
// ============================================================

void setupLighting()
{
    glEnable(GL_LIGHTING);

    glEnable(GL_LIGHT0);

    GLfloat ambient[] =
    {
        0.65f,
        0.65f,
        0.65f,
        1.0f
    };

    GLfloat diffuse[] =
    {
        1.0f,
        1.0f,
        1.0f,
        1.0f
    };

    GLfloat position[] =
    {
        0.0f,
        7.0f,
        0.0f,
        1.0f
    };

    glLightModelfv(
        GL_LIGHT_MODEL_AMBIENT,
        ambient
    );

    glLightfv(
        GL_LIGHT0,
        GL_DIFFUSE,
        diffuse
    );

    glLightfv(
        GL_LIGHT0,
        GL_POSITION,
        position
    );

    glEnable(
        GL_COLOR_MATERIAL
    );

    glColorMaterial(
        GL_FRONT_AND_BACK,
        GL_AMBIENT_AND_DIFFUSE
    );
}


// ============================================================
// CAMERA
// ============================================================

void setupCamera()
{
    float yawRadians =
        yaw * 3.14159265f / 180.0f;

    float pitchRadians =
        pitch * 3.14159265f / 180.0f;

    float directionX =
        sin(yawRadians) *
        cos(pitchRadians);

    float directionY =
        sin(pitchRadians);

    float directionZ =
        -cos(yawRadians) *
        cos(pitchRadians);

    gluLookAt(
        camX,
        camY,
        camZ,

        camX + directionX,
        camY + directionY,
        camZ + directionZ,

        0,
        1,
        0
    );
}


// ============================================================
// MOVEMENT
// ============================================================

void updateMovement()
{
    // ========================================================
    // ROTATION
    // ========================================================

    if (arrowLeft)
    {
        yaw -= rotateSpeed;
    }

    if (arrowRight)
    {
        yaw += rotateSpeed;
    }

    // 360 DEGREE ROTATION

    if (yaw >= 360.0f)
    {
        yaw -= 360.0f;
    }

    if (yaw < 0.0f)
    {
        yaw += 360.0f;
    }


    // ========================================================
    // DIRECTION
    // ========================================================

    float angle =
        yaw * 3.14159265f / 180.0f;

    float forwardX =
        sin(angle);

    float forwardZ =
        -cos(angle);

    float rightX =
        cos(angle);

    float rightZ =
        sin(angle);


    float dx = 0.0f;
    float dz = 0.0f;


    // ========================================================
    // FORWARD
    // ========================================================

    if (
        keys['w'] ||
        keys['W'] ||
        arrowUp
    )
    {
        dx +=
            forwardX *
            moveSpeed;

        dz +=
            forwardZ *
            moveSpeed;
    }


    // ========================================================
    // BACKWARD
    // ========================================================

    if (
        keys['s'] ||
        keys['S'] ||
        arrowDown
    )
    {
        dx -=
            forwardX *
            moveSpeed;

        dz -=
            forwardZ *
            moveSpeed;
    }


    // ========================================================
    // STRAFE LEFT
    // ========================================================

    if (
        keys['a'] ||
        keys['A']
    )
    {
        dx -=
            rightX *
            moveSpeed;

        dz -=
            rightZ *
            moveSpeed;
    }


    // ========================================================
    // STRAFE RIGHT
    // ========================================================

    if (
        keys['d'] ||
        keys['D']
    )
    {
        dx +=
            rightX *
            moveSpeed;

        dz +=
            rightZ *
            moveSpeed;
    }


    // ========================================================
    // NEW POSITION
    // ========================================================

    float newX =
        camX + dx;

    float newZ =
        camZ + dz;


    // ========================================================
    // OUTER WALL LIMITS
    // ========================================================

    if (newX < -23.0f)
        newX = -23.0f;

    if (newX > 23.0f)
        newX = 23.0f;

    if (newZ < -8.0f)
        newZ = -8.0f;

    if (newZ > 8.0f)
        newZ = 8.0f;


    // ========================================================
    // LEFT ROOM WALL
    //
    // Opening at:
    //
    // -2.5 < Z < 2.5
    //
    // ========================================================

    if (
        newX < -9.5f &&
        newX > -10.5f &&
        fabs(newZ) > 2.5f
    )
    {
        newX = camX;
    }


    // ========================================================
    // RIGHT ROOM WALL
    // ========================================================

    if (
        newX > 9.5f &&
        newX < 10.5f &&
        fabs(newZ) > 2.5f
    )
    {
        newX = camX;
    }


    camX = newX;
    camZ = newZ;
}


// ============================================================
// DISTANCE
// ============================================================

float distance2D(
    float x1,
    float z1,
    float x2,
    float z2)
{
    float dx =
        x1 - x2;

    float dz =
        z1 - z2;

    return sqrt(
        dx * dx +
        dz * dz
    );
}


// ============================================================
// DETECT NEARBY PAINTING
// ============================================================

// ============================================================
// DETECT NEARBY PAINTING
//
// Loops over paintingsInfo (rather than hardcoding each
// painting) so this automatically covers however many
// paintings the gallery has - no manual updates needed
// when paintings are added or moved.
// ============================================================

void detectPainting()
{
    nearbyPainting = -1;

    float closestDistance =
        3.5f;

    for (
        int i = 0;
        i < NUM_PAINTINGS;
        i++)
    {
        float d =
            distance2D(
                camX,
                camZ,
                paintingsInfo[i].x,
                paintingsInfo[i].z
            );

        if (d < closestDistance)
        {
            closestDistance = d;
            nearbyPainting = i;
        }
    }
}


// ============================================================
// TEXT
// ============================================================

void drawText(
    const char* text,
    float x,
    float y,
    void* font = GLUT_BITMAP_HELVETICA_18)
{
    glMatrixMode(
        GL_PROJECTION
    );

    glPushMatrix();

    glLoadIdentity();

    gluOrtho2D(
        0,
        windowWidth,
        0,
        windowHeight
    );

    glMatrixMode(
        GL_MODELVIEW
    );

    glPushMatrix();

    glLoadIdentity();

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    glColor3f(
        1,
        1,
        1
    );

    glRasterPos2f(
        x,
        y
    );

    while (*text)
    {
        glutBitmapCharacter(
            font,
            *text
        );

        text++;
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);

    glPopMatrix();

    glMatrixMode(
        GL_PROJECTION
    );

    glPopMatrix();

    glMatrixMode(
        GL_MODELVIEW
    );
}


// ============================================================
// TEXT (3D / WORLD SPACE, VECTOR FONT)
//
// Draws GLUT stroke-font text as real 3D line geometry placed
// at a position in the world (e.g. on a wall). Unlike bitmap
// text, stroke text is actual geometry transformed by the
// normal modelview/projection pipeline, so it naturally gets
// smaller with distance, is properly depth-tested, and stays
// anchored to the wall exactly like everything else in the
// scene - it does not depend on / follow the camera.
// ============================================================

float strokeTextWidth(
    const char* text,
    void* font)
{
    float width = 0.0f;

    while (*text)
    {
        width += (float)glutStrokeWidth(
            font,
            *text
        );

        text++;
    }

    return width;
}


void drawStrokeText3D(
    const char* text,
    float x,
    float y,
    float z,
    float scale,
    void* font = GLUT_STROKE_ROMAN)
{
    glPushMatrix();

    glTranslatef(
        x,
        y,
        z
    );

    glScalef(
        scale,
        scale,
        scale
    );

    glLineWidth(2.5f);

    while (*text)
    {
        glutStrokeCharacter(
            font,
            *text
        );

        text++;
    }

    glLineWidth(1.0f);

    glPopMatrix();
}


// ============================================================
// ENTRANCE SIGN
//
// Mounted on the front wall, facing the camera's starting
// position, so it is the first thing a visitor sees. Built
// from real 3D geometry (board + stroke-font text), so it
// stays fixed in the world exactly like the walls around it.
// ============================================================

void drawEntranceSign()
{
    glDisable(GL_TEXTURE_2D);


    // Sign backing board (dark wood)

    glColor3f(
        0.28f,
        0.15f,
        0.06f
    );

    drawCube(
        0.0f,
        6.3f,
        -8.55f,
        11.0f,
        1.6f,
        0.12f
    );


    // Inner panel (cream / parchment)

    glColor3f(
        0.90f,
        0.84f,
        0.68f
    );

    drawCube(
        0.0f,
        6.3f,
        -8.50f,
        10.4f,
        1.1f,
        0.05f
    );


    // Text (real 3D geometry, centered on the panel)

    glDisable(GL_LIGHTING);

    glColor3f(
        0.35f,
        0.24f,
        0.10f
    );

    float scale1 = 0.0022f;

    float width1 =
        strokeTextWidth(
            "WELCOME TO",
            GLUT_STROKE_ROMAN
        ) * scale1;

    drawStrokeText3D(
        "WELCOME TO",
        -width1 / 2.0f,
        6.62f,
        -8.43f,
        scale1
    );

    glColor3f(
        0.55f,
        0.10f,
        0.08f
    );

    float scale2 = 0.0040f;

    float width2 =
        strokeTextWidth(
            "EMTY GALLERY",
            GLUT_STROKE_ROMAN
        ) * scale2;

    drawStrokeText3D(
        "EMTY GALLERY",
        -width2 / 2.0f,
        6.05f,
        -8.43f,
        scale2
    );

    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
}


// ============================================================
// PAINTING RAYCAST (click-to-view, no proximity required)
//
// Intersects a world-space ray against each painting's wall
// plane and returns the closest hit. This is what lets a
// player click a painting from anywhere in the room, not just
// when standing close to it.
// ============================================================

int raycastPaintings(
    float originX,
    float originY,
    float originZ,
    float dirX,
    float dirY,
    float dirZ)
{
    int hitIndex = -1;

    float closestT = 1e9f;

    for (
        int i = 0;
        i < NUM_PAINTINGS;
        i++)
    {
        PaintingInfo& p =
            paintingsInfo[i];

        float t;
        float hitY;
        float hitAcross;

        if (p.wall == WALL_BACK)
        {
            if (fabs(dirZ) < 0.0001f)
                continue;

            t = (p.z - originZ) / dirZ;

            if (t <= 0.0f)
                continue;

            hitY = originY + t * dirY;
            hitAcross = originX + t * dirX;

            if (fabs(hitAcross - p.x) > p.width / 2.0f)
                continue;
        }
        else
        {
            if (fabs(dirX) < 0.0001f)
                continue;

            t = (p.x - originX) / dirX;

            if (t <= 0.0f)
                continue;

            hitY = originY + t * dirY;
            hitAcross = originZ + t * dirZ;

            if (fabs(hitAcross - p.z) > p.width / 2.0f)
                continue;
        }

        if (fabs(hitY - p.y) > p.height / 2.0f)
            continue;

        if (t < closestT)
        {
            closestT = t;
            hitIndex = i;
        }
    }

    return hitIndex;
}


// ============================================================
// SCREEN POINT -> WORLD RAY
//
// Unprojects a clicked screen pixel into a ray in world space
// using the camera's current view/projection matrices.
// ============================================================

void screenToWorldRay(
    int mouseX,
    int mouseY,
    float& originX,
    float& originY,
    float& originZ,
    float& dirX,
    float& dirY,
    float& dirZ)
{
    GLint viewport[4];

    glGetIntegerv(
        GL_VIEWPORT,
        viewport
    );

    GLdouble modelview[16];

    glGetDoublev(
        GL_MODELVIEW_MATRIX,
        modelview
    );

    GLdouble projection[16];

    glGetDoublev(
        GL_PROJECTION_MATRIX,
        projection
    );

    double winX =
        (double)mouseX;

    double winY =
        (double)(viewport[3] - mouseY);

    double nearX, nearY, nearZ;
    double farX, farY, farZ;

    gluUnProject(
        winX, winY, 0.0,
        modelview, projection, viewport,
        &nearX, &nearY, &nearZ
    );

    gluUnProject(
        winX, winY, 1.0,
        modelview, projection, viewport,
        &farX, &farY, &farZ
    );

    originX = (float)nearX;
    originY = (float)nearY;
    originZ = (float)nearZ;

    float dx = (float)(farX - nearX);
    float dy = (float)(farY - nearY);
    float dz = (float)(farZ - nearZ);

    float len =
        sqrt(dx * dx + dy * dy + dz * dz);

    if (len < 0.0001f)
        len = 0.0001f;

    dirX = dx / len;
    dirY = dy / len;
    dirZ = dz / len;
}


// ============================================================
// INFORMATION PANEL
// ============================================================

void drawInformation()
{
    if (nearbyPainting < 0)
        return;


    glMatrixMode(
        GL_PROJECTION
    );

    glPushMatrix();

    glLoadIdentity();

    gluOrtho2D(
        0,
        windowWidth,
        0,
        windowHeight
    );

    glMatrixMode(
        GL_MODELVIEW
    );

    glPushMatrix();

    glLoadIdentity();

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);


    // Panel

    glColor3f(
        0.08f,
        0.08f,
        0.10f
    );

    glBegin(GL_QUADS);

    glVertex2f(
        180,
        130
    );

    glVertex2f(
        windowWidth - 180,
        130
    );

    glVertex2f(
        windowWidth - 180,
        windowHeight - 130
    );

    glVertex2f(
        180,
        windowHeight - 130
    );

    glEnd();


    // Border

    glColor3f(
        0.75f,
        0.55f,
        0.20f
    );

    glLineWidth(3);

    glBegin(GL_LINE_LOOP);

    glVertex2f(
        180,
        130
    );

    glVertex2f(
        windowWidth - 180,
        130
    );

    glVertex2f(
        windowWidth - 180,
        windowHeight - 130
    );

    glVertex2f(
        180,
        windowHeight - 130
    );

    glEnd();


    drawText(
        paintingNames[nearbyPainting],
        230,
        windowHeight - 190,
        GLUT_BITMAP_TIMES_ROMAN_24
    );

    drawText(
        "Artist: Gallery Collection",
        230,
        windowHeight - 240
    );

    drawText(
        "Medium: Digital Artwork",
        230,
        windowHeight - 275
    );


    // Description (up to MAX_DESC_LINES lines)

    for (
        int i = 0;
        i < MAX_DESC_LINES;
        i++)
    {
        drawText(
            paintingDescriptions[nearbyPainting][i],
            230,
            windowHeight - 330 - (i * 30)
        );
    }

    drawText(
        "Press E to close",
        230,
        160
    );


    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);

    glPopMatrix();

    glMatrixMode(
        GL_PROJECTION
    );

    glPopMatrix();

    glMatrixMode(
        GL_MODELVIEW
    );
}


// ============================================================
// USER INTERFACE
// ============================================================

void drawUI()
{
    if (showInfo)
        return;

    drawText(
        "3D INTERACTIVE ART GALLERY",
        25,
        windowHeight - 35,
        GLUT_BITMAP_TIMES_ROMAN_24
    );

    drawText(
        "W / S - Forward / Backward",
        25,
        75
    );

    drawText(
        "A / D - Strafe",
        25,
        50
    );

    drawText(
        "Arrow Left / Right - Rotate",
        25,
        25
    );

    drawText(
        "E - Examine Artwork",
        windowWidth - 210,
        55
    );

    drawText(
        "Click - View Artwork",
        windowWidth - 220,
        30
    );


    if (nearbyPainting >= 0)
    {
        drawText(
            "Press E to examine artwork",
            windowWidth / 2 - 120,
            35
        );
    }
}


// ============================================================
// DISPLAY
// ============================================================

void display()
{
    glClear(
        GL_COLOR_BUFFER_BIT |
        GL_DEPTH_BUFFER_BIT
    );

    glMatrixMode(
        GL_MODELVIEW
    );

    glLoadIdentity();


    setupCamera();


    // Draw gallery

    buildGallery();

    drawDoorFrame(-10.0f);

    drawDoorFrame(10.0f);

    drawPaintings();

    drawDecorations();

    drawEntranceSign();


    // UI

    if (showInfo)
    {
        drawInformation();
    }
    else
    {
        drawUI();
    }


    glutSwapBuffers();
}


// ============================================================
// UPDATE
// ============================================================

void update(
    int value)
{
    if (!showInfo)
    {
        updateMovement();

        detectPainting();
    }

    glutPostRedisplay();

    glutTimerFunc(
        16,
        update,
        0
    );
}


// ============================================================
// KEY DOWN
// ============================================================

void keyboardDown(
    unsigned char key,
    int x,
    int y)
{
    keys[key] = true;


    // ESC

    if (key == 27)
    {
        exit(0);
    }


    // E

    if (
        key == 'e' ||
        key == 'E'
    )
    {
        if (nearbyPainting >= 0)
        {
            showInfo =
                !showInfo;
        }
    }
}


// ============================================================
// KEY UP
// ============================================================

void keyboardUp(
    unsigned char key,
    int x,
    int y)
{
    keys[key] = false;
}


// ============================================================
// ARROW KEY DOWN
// ============================================================

void specialDown(
    int key,
    int x,
    int y)
{
    if (key == GLUT_KEY_UP)
    {
        arrowUp = true;
    }

    if (key == GLUT_KEY_DOWN)
    {
        arrowDown = true;
    }

    if (key == GLUT_KEY_LEFT)
    {
        arrowLeft = true;
    }

    if (key == GLUT_KEY_RIGHT)
    {
        arrowRight = true;
    }
}


// ============================================================
// ARROW KEY UP
// ============================================================

void specialUp(
    int key,
    int x,
    int y)
{
    if (key == GLUT_KEY_UP)
    {
        arrowUp = false;
    }

    if (key == GLUT_KEY_DOWN)
    {
        arrowDown = false;
    }

    if (key == GLUT_KEY_LEFT)
    {
        arrowLeft = false;
    }

    if (key == GLUT_KEY_RIGHT)
    {
        arrowRight = false;
    }
}


// ============================================================
// MOUSE LOOK
// ============================================================

void mouseMove(
    int x,
    int y)
{
    if (firstMouse)
    {
        lastMouseX = x;
        lastMouseY = y;

        firstMouse = false;

        return;
    }

    int dx =
        x - lastMouseX;

    int dy =
        y - lastMouseY;

    lastMouseX = x;
    lastMouseY = y;


    float sensitivity =
        0.15f;


    yaw +=
        dx * sensitivity;

    pitch -=
        dy * sensitivity;


    // 360 DEGREE HORIZONTAL LOOK

    if (yaw >= 360.0f)
        yaw -= 360.0f;

    if (yaw < 0.0f)
        yaw += 360.0f;


    // Vertical limit

    if (pitch > 85.0f)
        pitch = 85.0f;

    if (pitch < -85.0f)
        pitch = -85.0f;


    glutPostRedisplay();
}


// ============================================================
// MOUSE CLICK
//
// Lets the player click directly on a painting to view its
// description, from anywhere in the room - no need to walk
// up close first. Raycasts from the clicked screen pixel
// into the world and checks it against every painting.
// ============================================================

void mouseClick(
    int button,
    int state,
    int x,
    int y)
{
    if (button != GLUT_LEFT_BUTTON ||
        state != GLUT_DOWN)
        return;

    if (showInfo)
        return;

    float originX, originY, originZ;
    float dirX, dirY, dirZ;

    screenToWorldRay(
        x, y,
        originX, originY, originZ,
        dirX, dirY, dirZ
    );

    int hit =
        raycastPaintings(
            originX, originY, originZ,
            dirX, dirY, dirZ
        );

    if (hit >= 0)
    {
        nearbyPainting = hit;
        showInfo = true;

        glutPostRedisplay();
    }
}


// ============================================================
// RESHAPE
// ============================================================

void reshape(
    int width,
    int height)
{
    if (height == 0)
        height = 1;

    windowWidth = width;
    windowHeight = height;

    glViewport(
        0,
        0,
        width,
        height
    );

    glMatrixMode(
        GL_PROJECTION
    );

    glLoadIdentity();

    gluPerspective(
        70.0,
        (double)width /
        (double)height,
        0.1,
        100.0
    );

    glMatrixMode(
        GL_MODELVIEW
    );
}


// ============================================================
// INITIALIZATION
// ============================================================

void initialize()
{
    // Background

    glClearColor(
        0.12f,
        0.12f,
        0.14f,
        1.0f
    );


    // Depth

    glEnable(
        GL_DEPTH_TEST
    );


    // Smooth objects

    glShadeModel(
        GL_SMOOTH
    );


    // Do not use face culling

    glDisable(
        GL_CULL_FACE
    );


    // Texture

    glEnable(
        GL_TEXTURE_2D
    );


    // Lighting

    setupLighting();


    // Load images

    loadAllPaintings();
}


// ============================================================
// MAIN
// ============================================================

int main(
    int argc,
    char** argv)
{
    glutInit(
        &argc,
        argv
    );

    glutInitDisplayMode(
        GLUT_DOUBLE |
        GLUT_RGB |
        GLUT_DEPTH
    );

    glutInitWindowSize(
        1280,
        720
    );

    glutInitWindowPosition(
        100,
        50
    );

    glutCreateWindow(
        "3D Interactive Art Gallery"
    );


    initialize();


    glutDisplayFunc(
        display
    );

    glutReshapeFunc(
        reshape
    );

    glutKeyboardFunc(
        keyboardDown
    );

    glutKeyboardUpFunc(
        keyboardUp
    );

    glutSpecialFunc(
        specialDown
    );

    glutSpecialUpFunc(
        specialUp
    );

    glutPassiveMotionFunc(
        mouseMove
    );

    glutMouseFunc(
        mouseClick
    );

    glutTimerFunc(
        16,
        update,
        0
    );


    printf("\n");
    printf("============================================\n");
    printf("       3D INTERACTIVE ART GALLERY\n");
    printf("============================================\n");
    printf("W/S       : Forward / Backward\n");
    printf("A/D       : Strafe Left / Right\n");
    printf("LEFT/RIGHT: Rotate 360 degrees\n");
    printf("UP/DOWN   : Forward / Backward\n");
    printf("MOUSE     : Look Around\n");
    printf("E         : Examine Painting (when nearby)\n");
    printf("CLICK     : View Painting Details (from anywhere)\n");
    printf("ESC       : Exit\n");
    printf("============================================\n\n");


    glutMainLoop();

    return 0;
}
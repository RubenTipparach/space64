#include "meshes.h"

#define CUBE_VERTS 12  // 6 faces, 4 verts each, packed 2 per struct

T3DVertPacked* mesh_create_cube(int texWidth, int texHeight)
{
    T3DVertPacked* verts = malloc_uncached(sizeof(T3DVertPacked) * CUBE_VERTS);
    const int16_t S = CUBE_HALF_SIZE;

    // UV coordinates for texture
    int16_t u0 = UV(0), v0 = UV(0);
    int16_t u1 = UV(texWidth), v1 = UV(texHeight);

    uint16_t normFront  = t3d_vert_pack_normal(&(T3DVec3){{ 0,  0,  1}});
    uint16_t normBack   = t3d_vert_pack_normal(&(T3DVec3){{ 0,  0, -1}});
    uint16_t normTop    = t3d_vert_pack_normal(&(T3DVec3){{ 0,  1,  0}});
    uint16_t normBottom = t3d_vert_pack_normal(&(T3DVec3){{ 0, -1,  0}});
    uint16_t normRight  = t3d_vert_pack_normal(&(T3DVec3){{ 1,  0,  0}});
    uint16_t normLeft   = t3d_vert_pack_normal(&(T3DVec3){{-1,  0,  0}});

    uint32_t white = 0xFFFFFFFF;

    // Front face (+Z)
    verts[0] = (T3DVertPacked){
        .posA = {-S, -S,  S}, .rgbaA = white, .normA = normFront, .stA = {u0, v1},
        .posB = { S, -S,  S}, .rgbaB = white, .normB = normFront, .stB = {u1, v1},
    };
    verts[1] = (T3DVertPacked){
        .posA = { S,  S,  S}, .rgbaA = white, .normA = normFront, .stA = {u1, v0},
        .posB = {-S,  S,  S}, .rgbaB = white, .normB = normFront, .stB = {u0, v0},
    };

    // Back face (-Z)
    verts[2] = (T3DVertPacked){
        .posA = { S, -S, -S}, .rgbaA = white, .normA = normBack, .stA = {u0, v1},
        .posB = {-S, -S, -S}, .rgbaB = white, .normB = normBack, .stB = {u1, v1},
    };
    verts[3] = (T3DVertPacked){
        .posA = {-S,  S, -S}, .rgbaA = white, .normA = normBack, .stA = {u1, v0},
        .posB = { S,  S, -S}, .rgbaB = white, .normB = normBack, .stB = {u0, v0},
    };

    // Top face (+Y)
    verts[4] = (T3DVertPacked){
        .posA = {-S,  S,  S}, .rgbaA = white, .normA = normTop, .stA = {u0, v1},
        .posB = { S,  S,  S}, .rgbaB = white, .normB = normTop, .stB = {u1, v1},
    };
    verts[5] = (T3DVertPacked){
        .posA = { S,  S, -S}, .rgbaA = white, .normA = normTop, .stA = {u1, v0},
        .posB = {-S,  S, -S}, .rgbaB = white, .normB = normTop, .stB = {u0, v0},
    };

    // Bottom face (-Y)
    verts[6] = (T3DVertPacked){
        .posA = {-S, -S, -S}, .rgbaA = white, .normA = normBottom, .stA = {u0, v1},
        .posB = { S, -S, -S}, .rgbaB = white, .normB = normBottom, .stB = {u1, v1},
    };
    verts[7] = (T3DVertPacked){
        .posA = { S, -S,  S}, .rgbaA = white, .normA = normBottom, .stA = {u1, v0},
        .posB = {-S, -S,  S}, .rgbaB = white, .normB = normBottom, .stB = {u0, v0},
    };

    // Right face (+X)
    verts[8] = (T3DVertPacked){
        .posA = { S, -S,  S}, .rgbaA = white, .normA = normRight, .stA = {u0, v1},
        .posB = { S, -S, -S}, .rgbaB = white, .normB = normRight, .stB = {u1, v1},
    };
    verts[9] = (T3DVertPacked){
        .posA = { S,  S, -S}, .rgbaA = white, .normA = normRight, .stA = {u1, v0},
        .posB = { S,  S,  S}, .rgbaB = white, .normB = normRight, .stB = {u0, v0},
    };

    // Left face (-X)
    verts[10] = (T3DVertPacked){
        .posA = {-S, -S, -S}, .rgbaA = white, .normA = normLeft, .stA = {u0, v1},
        .posB = {-S, -S,  S}, .rgbaB = white, .normB = normLeft, .stB = {u1, v1},
    };
    verts[11] = (T3DVertPacked){
        .posA = {-S,  S,  S}, .rgbaA = white, .normA = normLeft, .stA = {u1, v0},
        .posB = {-S,  S, -S}, .rgbaB = white, .normB = normLeft, .stB = {u0, v0},
    };

    return verts;
}

T3DVertPacked* mesh_create_laser_cube(void)
{
    T3DVertPacked* verts = malloc_uncached(sizeof(T3DVertPacked) * CUBE_VERTS);
    const int16_t S = LASER_CUBE_HALF_SIZE;

    uint32_t yellow = 0xFFFF00FF;
    uint32_t white  = 0xFFFFFFFF;

    uint16_t normFront  = t3d_vert_pack_normal(&(T3DVec3){{ 0,  0,  1}});
    uint16_t normBack   = t3d_vert_pack_normal(&(T3DVec3){{ 0,  0, -1}});
    uint16_t normTop    = t3d_vert_pack_normal(&(T3DVec3){{ 0,  1,  0}});
    uint16_t normBottom = t3d_vert_pack_normal(&(T3DVec3){{ 0, -1,  0}});
    uint16_t normRight  = t3d_vert_pack_normal(&(T3DVec3){{ 1,  0,  0}});
    uint16_t normLeft   = t3d_vert_pack_normal(&(T3DVec3){{-1,  0,  0}});

    // Front (+Z)
    verts[0] = (T3DVertPacked){
        .posA = {-S, -S,  S}, .rgbaA = yellow, .normA = normFront,
        .posB = { S, -S,  S}, .rgbaB = white,  .normB = normFront,
    };
    verts[1] = (T3DVertPacked){
        .posA = { S,  S,  S}, .rgbaA = yellow, .normA = normFront,
        .posB = {-S,  S,  S}, .rgbaB = white,  .normB = normFront,
    };
    // Back (-Z)
    verts[2] = (T3DVertPacked){
        .posA = { S, -S, -S}, .rgbaA = white,  .normA = normBack,
        .posB = {-S, -S, -S}, .rgbaB = yellow, .normB = normBack,
    };
    verts[3] = (T3DVertPacked){
        .posA = {-S,  S, -S}, .rgbaA = white,  .normA = normBack,
        .posB = { S,  S, -S}, .rgbaB = yellow, .normB = normBack,
    };
    // Top (+Y)
    verts[4] = (T3DVertPacked){
        .posA = {-S,  S,  S}, .rgbaA = yellow, .normA = normTop,
        .posB = { S,  S,  S}, .rgbaB = white,  .normB = normTop,
    };
    verts[5] = (T3DVertPacked){
        .posA = { S,  S, -S}, .rgbaA = yellow, .normA = normTop,
        .posB = {-S,  S, -S}, .rgbaB = white,  .normB = normTop,
    };
    // Bottom (-Y)
    verts[6] = (T3DVertPacked){
        .posA = {-S, -S, -S}, .rgbaA = white,  .normA = normBottom,
        .posB = { S, -S, -S}, .rgbaB = yellow, .normB = normBottom,
    };
    verts[7] = (T3DVertPacked){
        .posA = { S, -S,  S}, .rgbaA = white,  .normA = normBottom,
        .posB = {-S, -S,  S}, .rgbaB = yellow, .normB = normBottom,
    };
    // Right (+X)
    verts[8] = (T3DVertPacked){
        .posA = { S, -S,  S}, .rgbaA = yellow, .normA = normRight,
        .posB = { S, -S, -S}, .rgbaB = white,  .normB = normRight,
    };
    verts[9] = (T3DVertPacked){
        .posA = { S,  S, -S}, .rgbaA = yellow, .normA = normRight,
        .posB = { S,  S,  S}, .rgbaB = white,  .normB = normRight,
    };
    // Left (-X)
    verts[10] = (T3DVertPacked){
        .posA = {-S, -S, -S}, .rgbaA = white,  .normA = normLeft,
        .posB = {-S, -S,  S}, .rgbaB = yellow, .normB = normLeft,
    };
    verts[11] = (T3DVertPacked){
        .posA = {-S,  S,  S}, .rgbaA = white,  .normA = normLeft,
        .posB = {-S,  S, -S}, .rgbaB = yellow, .normB = normLeft,
    };

    return verts;
}

void mesh_draw_cube(T3DVertPacked *verts)
{
    for (int face = 0; face < 6; face++) {
        t3d_vert_load(verts + face * 2, 0, 4);
        t3d_tri_draw(0, 1, 2);
        t3d_tri_draw(2, 3, 0);
        t3d_tri_sync();
    }
}

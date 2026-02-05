#include "camera.h"

Camera camera_create(void)
{
    Camera camera;
    camera.viewport = t3d_viewport_create_buffered(FB_COUNT);
    camera.position = (T3DVec3){{0, 0, -50}};
    camera.target = (T3DVec3){{0, 0, 0}};
    return camera;
}

void camera_update(Camera *camera)
{
    t3d_viewport_set_projection(&camera->viewport, T3D_DEG_TO_RAD(85.0f), 10.0f, 150.0f);
    t3d_viewport_look_at(&camera->viewport, &camera->position, &camera->target, &(T3DVec3){{0, 1, 0}});
}

void camera_attach(Camera *camera)
{
    t3d_viewport_attach(&camera->viewport);
}

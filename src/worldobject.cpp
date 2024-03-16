#include "worldobject.h"

void WorldObject::update() {
    // Update
}

RenderData WorldObject::getRenderData() {
    return {
        RenderType::Rectangle,
        coordType,
        locx,
        locy,
        width,
        height,
        { 255, 255, 255 },
        ""
    };
}

#include "worldobject.h"

WorldObject::WorldObject() {
    coordType = CoordType::World;
    locx = 0.0;
    locy = 0.0;
    width = 1.0;
    height = 1.0;
}

UpdateResult WorldObject::update() {
    // Update
    return UpdateResult::None;
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

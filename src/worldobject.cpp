#include "worldobject.h"

WorldObject::WorldObject() {
    coordType = CoordType::World;
    locx = 0.0;
    locy = 0.0;
    width = 1.0;
    height = 1.0;
    velx = 0.0;
    vely = 0.0;
}

UpdateResult WorldObject::update(WorldState& worldState, std::vector<WorldObject*>& objects) {
    // Update
    return UpdateResult::None;
}

double WorldObject::isPointInside(double x, double y) {
    return (x >= locx && x < locx + width && y > locy && y < locy + height);
}

double WorldObject::getLocx() {
    return locx;
}

double WorldObject::getLocy() {
    return locy;
}

double WorldObject::getWidth() {
    return width;
}

double WorldObject::getHeight() {
    return height;
}

double WorldObject::getVelx() {
    return velx;
}

double WorldObject::getVely() {
    return vely;
}

bool WorldObject::hasAttribute(ObjectAttribute attribute) {
    return objectAttributes.find(attribute) != objectAttributes.end();
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

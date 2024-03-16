#include "worldobject.h"

// Stores a red cube
class RedCube : WorldObject {
public:
    // Override rendering
    RenderData render() {
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
};

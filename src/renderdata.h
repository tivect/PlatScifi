#pragma once

#include <string>

// Type to render
enum class RenderType {
    Circle,
    Rectangle,
    Image
};

// Type of coordinates
enum class CoordType {
    Screen,
    World
};

// Color
struct Color {
    int r;
    int g;
    int b;
};

// Stores location, color, etc. for the renderer to display
struct RenderData {
    RenderType type;
    CoordType coordType;
    double locx;
    double locy;
    double width;
    double height;
    Color color;
    std::string imageSource;
};

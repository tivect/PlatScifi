#pragma once

#include <vector>
#include "worldobject.h"

class WorldCollisionMatrix {
private:
    std::vector<std::vector<std::vector<WorldObject*>>> matrix;
    std::vector<WorldObject*> outside;
    int matrixWidth = 100;
    int matrixHeight = 100;
    // Number of world units per cell
    int matrixCellSize = 2; 

public:
    // Create a default cleared collision matrix
    WorldCollisionMatrix() {
        for (int i = 0; i < matrixHeight; i++) {
            matrix.push_back(std::vector<std::vector<WorldObject*>>(matrixWidth));
        }
    }

    // Clear the matrix to a width x height grid; does not deallocate any objects
    void clear() {
        for (int i = 0; i < matrixHeight; i++) {
            for (int j = 0; j < matrixWidth; j++) {
                matrix[i][j].clear();
            }
        }
        outside.clear();
    }

    // Add an object to the correct location based on its collision rectangle
    void addObject(WorldObject* object) {
        // Determine which cells the object is in
        int x0 = object->getLocx() / matrixCellSize;
        int y0 = object->getLocy() / matrixCellSize;
        int x1 = (object->getLocx() + object->getWidth()) / matrixCellSize;
        int y1 = (object->getLocy() + object->getHeight()) / matrixCellSize;
        bool addedOutside = false;
        for (int y = y0; y <= y1; y++) {
            for (int x = x0; x <= x1; x++) {
                if (y < 0 || x < 0 || y >= matrixHeight || x >= matrixWidth) {
                    // Outside
                    if (!addedOutside) {
                        outside.push_back(object);
                        addedOutside = true;
                    }
                } else {
                    // In cell
                    matrix[y][x].push_back(object);
                }
            }
        }
    }

    // Get the saturation of a cell (number of items in it)
    int getCellSaturation(int x, int y) {
        if (y < 0 || x < 0 || y >= matrixHeight || x >= matrixWidth) return 0;
        return matrix[y][x].size();
    }

    // Get the size of the matrix cells (in world units)
    int getCellSize() {
        return matrixCellSize;
    }

    // Get all objects in the matrix potentially colliding with an object based on its collision rectangle
    std::set<WorldObject*> searchMatrix(WorldObject* object) {
        std::set<WorldObject*> res;
        // Determine which cells the object is in
        int x0 = object->getLocx() / matrixCellSize;
        int y0 = object->getLocy() / matrixCellSize;
        int x1 = (object->getLocx() + object->getWidth()) / matrixCellSize;
        int y1 = (object->getLocy() + object->getHeight()) / matrixCellSize;
        bool addedOutside = false;
        for (int y = y0; y <= y1; y++) {
            for (int x = x0; x <= x1; x++) {
                if (y < 0 || x < 0 || y >= matrixHeight || x >= matrixWidth) {
                    // Outside
                    if (!addedOutside) {
                        for (WorldObject* other : outside) res.insert(other);
                        addedOutside = true;
                    }
                } else {
                    // In cell
                    for (WorldObject* other : matrix[y][x]) res.insert(other);
                }
            }
        }
        return res;
    }
};

#ifndef _MAP_H_
#define _MAP_H_

#include <vector>
#include <string>

namespace Gameplay {
    struct Tile {
        Tile(void) {}
        Tile(std::string name) {this->name = name;}
        std::string name, path;
        Texture tex;
        Uint8 r, g, b;
    };
    
    struct Map {
        Map(void) {}
        std::vector<Tile> tiles;
        int **tileType;
        int w, h;
        float x, y;
        float bufR, bufL, bufT, bufD;
    };
};

#endif
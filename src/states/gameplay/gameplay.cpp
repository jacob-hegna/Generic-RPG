#include "gameplay.h"

std::vector<Gameplay::Tile> Gameplay::tiles;
int **Gameplay::mapTiles = nullptr;
int Gameplay::mapW = 0;
int Gameplay::mapH = 0;

Hero *Gameplay::hero = nullptr;
Zombie *Gameplay::zombie = nullptr;

Font Gameplay::arial;
Music Gameplay::music;

void Gameplay::init(Engine *engine) {
    hero = new Hero(0,0);
    hero->init(engine->getWindow());

    zombie = new Zombie(345, 500);
    zombie->init(engine->getWindow());

    arial.setRen(engine->getWindow());
    arial.loadTTF("media/images/etc/arial.ttf", 24);
    arial.setColor(0, 0, 0);

    music.init("media/audio/gameMusic.ogg");
    music.play();

    tiles.clear();

    rapidxml::file<> mapXml("media/map.xml");
    rapidxml::xml_document<> mapDoc;
    mapDoc.parse<0>(mapXml.data());
    rapidxml::xml_attribute<> *tileAttr;
    for (rapidxml::xml_node<> *node = mapDoc.first_node("tile"); node; node = node->next_sibling("tile")) {
        Tile tile;

        tileAttr = node->first_attribute("name");
        tile.name = tileAttr->value();

        tileAttr = tileAttr->next_attribute("r");
        tile.r = atoi(tileAttr->value());

        tileAttr = tileAttr->next_attribute("g");
        tile.g = atoi(tileAttr->value());

        tileAttr = tileAttr->next_attribute("b");
        tile.b = atoi(tileAttr->value());

        tileAttr = tileAttr->next_attribute("path");
        tile.tex = Texture(engine->getWindow()->getRen());
        tile.path = tileAttr->value();
        
        tiles.push_back(tile);
    }

    for(int i = 0; i < tiles.size(); ++i) {
        tiles.at(i).tex.loadIMG(tiles.at(i).path);
    }

    png::image<png::rgb_pixel> mapPng("media/map.png");
    mapW = mapPng.get_width();
    mapH = mapPng.get_height();
    mapTiles = new int*[mapH];
    for(int i = 0; i < mapH; ++i) {
        mapTiles[i] = new int[mapW];
        for(int j = 0; j < mapW; ++j) {
            png::rgb_pixel pixel = mapPng.get_pixel(j, i);
            for(int h = 0; h < tiles.size(); ++h) {
                if(pixel.red == tiles.at(h).r &&
                    pixel.green == tiles.at(h).g &&
                    pixel.blue == tiles.at(h).b) {
                    mapTiles[i][j] = h;
                }
            }
        }
    }
}

void Gameplay::logic(Engine *engine) {
    hero->move();
    zombie->autoMove(hero);
    zombie->hitDetect(hero);
}

void Gameplay::render(Engine *engine) {
    for(int i = 0; i < mapW; ++i) {
        for(int j = 0; j < mapH; ++j) {
            tiles.at(mapTiles[j][i]).tex.render(i*20, j*20);
        }
    }

    zombie->render();
    hero->render();

    arial.print(SSTR(floor(engine->getFps())), 5, 5);
}

void Gameplay::free(Engine *engine) {
    for(int i = 0; i < mapH; ++i) {
        delete [] mapTiles[i];
    }
    delete [] mapTiles;

    music.free();
    delete hero;
    delete zombie;
}
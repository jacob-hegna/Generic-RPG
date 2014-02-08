#include "gameplay.h"

Gameplay::Map Gameplay::map;

Hero *Gameplay::hero = nullptr;
std::vector<Zombie*> Gameplay::zombie;
std::vector<Skeleton*> Gameplay::skeleton;

Font Gameplay::arial;
Music Gameplay::music;

void Gameplay::init(Engine *engine) {
    hero = new Hero(120, 120);
    hero->init(engine->getWindow());

    for(int i = 0; i < zombieAmt; ++i) {
        zombie.push_back(new Zombie(345, 500));
        zombie.at(i)->init(engine->getWindow());
    }

    for(int i = 0; i < skeletonAmt; ++i) {
        skeleton.push_back(new Skeleton(345, 500));
        skeleton.at(i)->init(engine->getWindow());
    }

    arial.setRen(engine->getWindow());
    arial.loadTTF("media/images/etc/arial.ttf", 24);
    arial.setColor(0, 0, 0);

    music.init("media/audio/gameMusic.ogg");
    music.play();

    map.tiles.clear();
    map.w = 0;
    map.h = 0;
    map.x = 0.f;
    map.y = 0.f;
    map.bufL = 120.f;
    map.bufR = engine->getWindow()->getW() - 120.f;
    map.bufT = 120.f;
    map.bufD = engine->getWindow()->getH() - 120.f;

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
        
        map.tiles.push_back(tile);
    }

    for(int i = 0; i < map.tiles.size(); ++i) {
        map.tiles.at(i).tex.loadIMG(map.tiles.at(i).path);
    }

    png::image<png::rgb_pixel> mapPng("media/map.png");
    map.w = mapPng.get_width();
    map.h = mapPng.get_height();
    map.x = map.w*10 - engine->getWindow()->getW()/2;
    map.y = map.h*10 - engine->getWindow()->getH()/2;
    map.tileType = new int*[map.h];
    for(int i = 0; i < map.h; ++i) {
        map.tileType[i] = new int[map.w];
        for(int j = 0; j < map.w; ++j) {
            png::rgb_pixel pixel = mapPng.get_pixel(j, i);
            for(int h = 0; h < map.tiles.size(); ++h) {
                if(pixel.red == map.tiles.at(h).r &&
                    pixel.green == map.tiles.at(h).g &&
                    pixel.blue == map.tiles.at(h).b) {
                    map.tileType[i][j] = h;
                }
            }
        }
    }
}

void Gameplay::logic(Engine *engine) {
    hero->move(&map);
    for(int i = 0; i < zombie.size(); ++i)   {zombie.at(i)->move(hero, &map); zombie.at(i)->hitDetect(hero);}
    for(int i = 0; i < skeleton.size(); ++i) {skeleton.at(i)->move(hero, &map); skeleton.at(i)->hitDetect(hero);}
}

void Gameplay::render(Engine *engine) {
    for(int i = 0; i < map.w; ++i) {
        for(int j = 0; j < map.h; ++j) {
            map.tiles.at(map.tileType[j][i]).tex.render(i * 20 - map.x, j * 20 - map.y);
        }
    }

    hero->render();

    for(int i = 0; i < zombie.size(); ++i)   zombie.at(i)->render();
    for(int i = 0; i < skeleton.size(); ++i) skeleton.at(i)->render();

    arial.print(SSTR(floor(engine->getFps())), 5, 5);
}

void Gameplay::free(Engine *engine) {
    for(int i = 0; i < map.h; ++i) {
        delete [] map.tileType[i];
    }
    delete [] map.tileType;

    music.free();

    delete hero;
    for(int i = 0; i < zombie.size(); ++i)   delete zombie.at(i);
    for(int i = 0; i < skeleton.size(); ++i) delete skeleton.at(i);
}
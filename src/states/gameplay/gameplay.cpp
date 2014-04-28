#include "gameplay.h"

Gameplay::Map Gameplay::map;

Hero *Gameplay::hero = nullptr;
std::vector<Zombie*> Gameplay::zombie;
std::vector<Skeleton*> Gameplay::skeleton;
Portal Gameplay::portal;

Font Gameplay::arial;
Music Gameplay::music;

Gameplay::HUD Gameplay::hud;

char Gameplay::LevelData::currentLevel = 0;
bool Gameplay::LevelData::levelClear   = false;

void Gameplay::init(Engine *engine) {
    hero = new Hero(120, 120);
    hero->init(engine->getWindow());

    for(int i = 0; i < LevelData::zombieAmt[LevelData::levelAmt]; ++i) {
        zombie.push_back(new Zombie(345, 500));
        zombie.at(i)->init(engine->getWindow());
    }

    for(int i = 0; i < LevelData::skeletonAmt[LevelData::levelAmt]; ++i) {
        skeleton.push_back(new Skeleton(345, 500));
        skeleton.at(i)->init(engine->getWindow());
    }

    portal.init(engine->getWindow(), "media/images/items/portal.png");

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

    hud.bar.init(engine->getWindow()->getRen());
    hud.bar.loadIMG("media/images/hud/back.png");

    hud.healthTick.init(engine->getWindow()->getRen());
    hud.healthTick.loadIMG("media/images/hud/healthTick.png");

    hud.magicTick.init(engine->getWindow()->getRen());
    hud.magicTick.loadIMG("media/images/hud/magicTick.png");
}

void Gameplay::logic(Engine *engine) {
    hero->move(&map);
    portal.logic(hero, nextLevel, engine, map.x, map.y);
    int  clearedEnemies = 0;
    for(int i = 0; i < LevelData::zombieAmt[LevelData::currentLevel]; ++i) {
        if(zombie.at(i)->getDead()) clearedEnemies++;
        zombie.at(i)->move(hero, &map);
        zombie.at(i)->hitDetect(hero);
    }

    for(int i = 0; i < LevelData::skeletonAmt[LevelData::currentLevel]; ++i) {
        if(skeleton.at(i)->getDead()) clearedEnemies++;
        skeleton.at(i)->move(hero, &map);
        skeleton.at(i)->hitDetect(hero);
    }

    if(clearedEnemies == LevelData::zombieAmt[LevelData::currentLevel] + 
        LevelData::skeletonAmt[LevelData::currentLevel]) {
        LevelData::levelClear = true;
    } else {
        LevelData::levelClear = false;
    }

    if(hero->getHealth() <= 0) {
        loopQuit = true;
    }
}

void Gameplay::render(Engine *engine) {
    for(int i = 0; i < map.w; ++i) {
        for(int j = 0; j < map.h; ++j) {
            map.tiles.at(map.tileType[j][i]).tex.render(i * 20 - map.x, j * 20 - map.y);
        }
    }

    if (LevelData::levelClear) {
        portal.render();
    }

    hero->renderRel();
    hero->renderMagic();

    for(int i = 0; i < LevelData::zombieAmt[LevelData::currentLevel]; ++i)   zombie.at(i)->render();
    for(int i = 0; i < LevelData::skeletonAmt[LevelData::currentLevel]; ++i) skeleton.at(i)->render();

    renderHUD(engine);
}

void Gameplay::renderHUD(Engine *engine) {
    arial.print(std::to_string((int)engine->getFps()), 5, 5);

    // Magic
    hud.bar.render(10, engine->getWindow()->getH() - (hud.bar.getH() + 10)*2);
    for (int i = 0; i < (float)(hud.bar.getW() - 4) * ((float)hero->getMagic() / (float)hero->getMMagic()); ++i) {
        hud.magicTick.render(i + 10 + 2, engine->getWindow()->getH() - (hud.bar.getH() + 10 - 1) * 2);
    }

    // Health
    hud.bar.render(10, engine->getWindow()->getH() - (hud.bar.getH() + 10));
    for(int i = 0; i < (float)(hud.bar.getW() - 4) * ((float)hero->getHealth()/(float)hero->getMHealth()); ++i) {
        hud.healthTick.render(i + 10 + 2, engine->getWindow()->getH() - (hud.bar.getH() + 10 - 2));
    }

    arial.print(std::to_string((int)hero->getMapX()), 100, 100);
    arial.print(std::to_string((int)hero->getMapY()), 200, 100);
    arial.print(std::to_string((int)portal.getMapX()), 100, 200);
    arial.print(std::to_string((int)portal.getMapY()), 200, 200);
    arial.print(std::to_string((int)map.x), 100, 300);
    arial.print(std::to_string((int)map.y), 200, 300);
    arial.print(std::to_string((int)hero->getX()), 100, 400);
    arial.print(std::to_string((int)hero->getY()), 200, 400);
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

    hud.bar.free();
    hud.healthTick.free();
    hud.magicTick.free();
}

void Gameplay::nextLevel(Engine *engine) {
    if(LevelData::currentLevel != LevelData::levelAmt) {
        LevelData::levelClear = false;
        ++(LevelData::currentLevel);
        for(int i = 0; i < LevelData::zombieAmt[LevelData::currentLevel]; ++i) {
            zombie.at(i)->respawn(0, 0);
        }
        for (int i = 0; i < LevelData::skeletonAmt[LevelData::currentLevel]; ++i) {
            skeleton.at(i)->respawn(0, 0);
        }
    } else {
        engine->getWindow()->close();
    }
}
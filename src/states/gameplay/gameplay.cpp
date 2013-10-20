#include "gameplay.h"

Hero *Gameplay::hero = nullptr;
Zombie *Gameplay::zombie;

Font Gameplay::arial;
Music Gameplay::music;

void Gameplay::init(Engine *engine) {
	hero = new Hero(0,0);
	hero->init(engine->getWindow());

	zombie = new Zombie(500,500);
	zombie->init(engine->getWindow());

	arial.setRen(engine->getWindow());
	arial.loadTTF("media/images/etc/arial.ttf", 24);
	arial.setColor(0, 0, 0);

	music.init("media/audio/gameMusic.ogg");
	music.play();
}

void Gameplay::logic(Engine *engine) {
	hero->move();
	zombie->move(hero);
}

void Gameplay::render(Engine *engine) {
	hero->render();
	zombie->render();

	arial.print(SSTR(floor(engine->getFps())), 5, 5);
}

void Gameplay::free(Engine *engine) {
	music.free();
	delete hero;
	delete zombie;
}
#include "gameplay.h"

Hero *Gameplay::hero = nullptr;
Zombie *Gameplay::zombie;

Font test;

void Gameplay::init(Engine *engine) {
	hero = new Hero(0,0);
	hero->init(engine->getWindow());

	zombie = new Zombie(500,500);
	zombie->init(engine->getWindow());
	
	test.setRen(engine->getWindow());
	test.loadTTF("media/images/etc/arial.ttf", 28);
}

void Gameplay::logic(Engine *engine) {
	hero->move();
	zombie->move(hero);
}

void Gameplay::render(Engine *engine) {
	hero->render();
	zombie->render();

	test.setColor(0, 0, 0);
	test.print("Hello world!", 100, 100);
}

void Gameplay::free(Engine *engine) {
	delete hero;
	delete zombie;
}
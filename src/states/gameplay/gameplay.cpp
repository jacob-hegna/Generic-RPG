#include "gameplay.h"

Hero *Gameplay::hero = nullptr;
Zombie *Gameplay::zombie[2];

void Gameplay::init(Engine *engine) {
	hero = new Hero(0,0);
	hero->init(engine->getWindow());

	zombie[0] = new Zombie(500,500);
	zombie[0]->init(engine->getWindow());
	zombie[1] = new Zombie(-100,-100);
	zombie[1]->init(engine->getWindow());
}

void Gameplay::logic(Engine *engine) {
	hero->move();
	zombie[0]->move(hero);
	zombie[1]->move(hero);
}

void Gameplay::render(Engine *engine) {
	hero->render(engine->getWindow());
	zombie[0]->render(engine->getWindow());
	zombie[1]->render(engine->getWindow());
}
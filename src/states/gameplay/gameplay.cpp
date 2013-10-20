#include "gameplay.h"

Hero *Gameplay::hero = nullptr;
Zombie *Gameplay::zombie;

void Gameplay::init(Engine *engine) {
	hero = new Hero(0,0);
	hero->init(engine->getWindow());

	zombie = new Zombie(500,500);
	zombie->init(engine->getWindow());
}

void Gameplay::logic(Engine *engine) {
	hero->move();
	zombie->move(hero);
}

void Gameplay::render(Engine *engine) {
	hero->render(engine->getWindow());
	zombie->render(engine->getWindow());
}

void Gameplay::free(Engine *engine) {
	delete hero;
	delete zombie;
}
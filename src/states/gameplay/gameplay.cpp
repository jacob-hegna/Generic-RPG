#include "gameplay.h"

Hero *Gameplay::hero = nullptr;

void Gameplay::init(Engine *engine) {
	hero = new Hero();
	hero->init(engine->getWindow());
}

void Gameplay::logic(Engine *engine) {
	hero->move();
}

void Gameplay::render(Engine *engine) {
	hero->render(engine->getWindow());
}
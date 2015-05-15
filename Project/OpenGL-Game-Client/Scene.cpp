#include "Scene.h"


Scene::Scene()
{
}


Scene::~Scene()
{
}

void Scene::Init(void){}

void Scene::Update(float timeDelta){
	this->UpdateMembers(timeDelta);
}

void Scene::Render(void){
	this->RenderMembers();
}
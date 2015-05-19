#include "WallObject.h"
#include "GlutManager.h"

WallObject::WallObject()
{

}


void WallObject::Render(void){
	if (GlutManager::GetMainCamera()->InView(position)){
		Move(glm::vec3(0.0f, -4.0f, 0.0f));
		UpdateNetTransformations();
		MeshObject::Render();
		Move(glm::vec3(0.0f, 4.0f, 0.0f));
		UpdateNetTransformations();
	}
	else{
		MeshObject::Render();
	}




}
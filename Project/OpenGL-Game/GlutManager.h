#ifndef GLUTMANAGER_H
#define GLUTMANAGER_H

#include "IObject.h"
#include "Camera.h"
#include "GameScene.h"
#include <string>
#include <map>


class GlutManager 
{
public:
	GlutManager();
	~GlutManager();
	static void Init(bool editor);
	static void StartLoop(void);
	static void EndLoop(void);
	static void IdleFunc(void);

	static Camera *GetMainCamera(void);
	static void SetMainCamera(Camera *camera);


	static void AddMember(std::string name, IObject *object);


	static GLint mainWindow;


private:
	/**Initializes the Window**/
	static void RenderScene(void);
	static void CheckKeyInput(void);
	static void Reshape(int x, int y);
	static void UpdateMembers(float timeDelta);

	/*Members*/
	static std::map<std::string, IObject *> members;
	static Camera *mainCamera;
	static glm::vec3 position;
	static float lastTime;

	
};

#endif

#ifndef GLUTMANAGER_H
#define GLUTMANAGER_H

#include "IObject.h"
#include "Camera.h"
#include <string>
#include <map>


class GlutManager
{
public:
	GlutManager();
	~GlutManager();
	static void Init(void);
	static void StartLoop(void);
	static void EndLoop(void);

	static Camera *GetMainCamera(void);
	static void SetMainCamera(Camera *camera);


	static void AddMember(std::string name, IObject *object);

private:
	/**Initializes the Window**/
	static void Init(void);
	static void RenderScene(void);
	static void IdleFunc(void);
	static void CheckKeyInput(void);
	static void Reshape(int x, int y);

	/*Members*/
	static std::map<std::string, IObject *> members;
	static Camera *mainCamera;
	
};

#endif

#ifndef GLUTMANAGER_H
#define GLUTMANAGER_H

#include "IObject.h"
#include <string>
#include <map>

enum AllowedMembers{ Renderable, Updateable, };

class GlutManager
{
public:
	GlutManager();
	~GlutManager();
	static void StartLoop(void);
	static void EndLoop(void);

	static void AddMember(std::string name, IObject *object, AllowedMembers tags...);

private:
	/**Initializes the Window**/
	static void Init(void);
	static void RenderScene(void);
	static void IdleFunc(void);
	static void CheckKeyInput(void);

	/*Members*/
	static std::map<AllowedMembers, std::map<std::string, IObject *>> members;
	
	
};

#endif

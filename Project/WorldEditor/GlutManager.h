#ifndef GLUTMANAGER_H
#define GLUTMANAGER_H

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
	static GLint mainWindow;

private:
	/**Initializes the Window**/
	static void RenderScene(void);
	static void CheckKeyInput(void);
	static void Reshape(int x, int y);
	static void UpdateMembers(float timeDelta);

	/*Members*/
	static float lastTime;
};

#endif

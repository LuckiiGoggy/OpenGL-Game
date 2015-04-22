#pragma once



struct Point{
	int x = 0;
	int y = 0;
};

struct KeyInfo
{
	bool state = false;
	Point pressedPoint;
	Point releasedPoint;
};

struct MouseInfo
{
	bool isLeftButtonDown = false;
	bool isMiddleButtonDown = false;
	bool isRightButtonDown = false;
	Point currPos;
};


class InputManager
{
public:
	/* Note the x & y parameters are for the position of the mouse when the key was pressed 
		it might be usefull later, to check if something is "active" based on whether or not
		the mouse is currently on top of the object/graphic */

	/** 
		Handles Key Presses sets the specified keyInfo state to "true" state
		@param key - specified key that was pressed
		@param x   - the position of the mouse when the key was pressed
		@param y   - the position of the mouse when the key was pressed 
	**/
	static void KeyPress(unsigned char key, int x, int y);
	/**
		Handles Key releases sets the specified keyInfo state to "false" state
		@param key - specified key that was released
		@param x   - the position of the mouse when the key was pressed
		@param y   - the position of the mouse when the key was pressed
	**/
	static void KeyUp(unsigned char key, int x, int y);
	/** 
		Handles Key Presses sets the specified keyInfo state to "true" state
		@param key - specified key that was pressed
		@param x   - the position of the mouse when the key was pressed
		@param y   - the position of the mouse when the key was pressed 
	**/
	static void SpecialKeyPress(int key, int x, int y);
	/**
		Handles Special Key releases sets the specified keyInfo state to "false" state
		@param key - specified key that was released
		@param x   - the position of the mouse when the key was pressed
		@param y   - the position of the mouse when the key was pressed
	**/
	static void SpecialKeyUp(int key, int x, int y);

	/**
		Handles mouse input, when a mouse button is clicked or released.
		@param button - which mouse button is clicked or released.
		@param state  - specifies if the button was clicked or released.
		@param x      - the x position of the mouse during the event.
		@param y      - the y position of the mouse during the event.
	**/
	static void MouseInput(int button, int state, int x, int y);

	/**
		Handles mouse motion, when a mouse moves.
		@param x      - the x position of the mouse during the event.
		@param y      - the y position of the mouse during the event.
	**/
	static void MouseMotion(int x, int y);

	/**
		Checks if a specified key is currently pressed down.
		@param key - specified key.
	**/
	static bool isKeyDown(unsigned char key);
	/**
		Checks if a specified key is currently released.
		@param key - specified key.
	**/
	static bool isKeyUp(unsigned char key);
	/**
		Checks if a specified special key is currently pressed down.
		@param key - specified key.
	**/
	static bool isSpecialKeyDown(unsigned char key);
	/**
		Checks if a specified special key is currently released.
		@param key - specified key.
	**/
	static bool isSpecialKeyUp(unsigned char key);
	/**
		Returns the position of the mouse when the key was pressed.
		@param key - specified key.
	**/
	static Point GetMousePosOfKeyPress(unsigned char key);
	/**
		Returns the position of the mouse when the key was released.
		@param key - specified key.
	**/
	static Point GetMousePosOfKeyRelease(unsigned char key);
	/**
		Returns the position of the mouse when the special key was pressed.
		@param key - specified key.
	**/
	static Point GetMousePosOfSpecialKeyPress(unsigned char key);
	/**
		Returns the position of the mouse when the special key was released.
		@param key - specified key.
	**/
	static Point GetMousePosOfSpecialKeyRelease(unsigned char key);

	/** Checks if the left Mouse Button is currently pressed down **/
	static bool isLeftButtonDown();
	/** Checks if the left Mouse Button is currently released **/
	static bool isLeftButtonUp();
	/** Checks if the right Mouse Button is currently pressed down **/
	static bool isRightButtonDown();
	/** Checks if the right Mouse Button is currently released **/
	static bool isRightButtonUp();
	/** Checks if the middle Mouse Button is currently pressed down **/
	static bool isMiddleButtonDown();
	/** Checks if the middle Mouse Button is currently released **/
	static bool isMiddleButtonUp();

	/** Returns the current position of the mouse **/
	static Point GetMousePos();

private:
	static KeyInfo* keySpecialStates;
	static KeyInfo* keyStates;
	static MouseInfo mouseInfo;
};

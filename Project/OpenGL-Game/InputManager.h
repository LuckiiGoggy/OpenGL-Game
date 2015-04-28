#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

enum KeyCodes{
	F1 = 257, F7  = 263, 
	F2 = 258, F8  = 264,
	F3 = 259, F9  = 265,
	F4 = 260, F10 = 266,
	F5 = 261, F11 = 267,
	F6 = 262, F12 = 268,
	
	Left = 356, Up   = 357,
	Right= 358, Down = 359,

	PageUp   = 360, Home = 362,
	PageDown = 361, End  = 363,
	Insert   = 364,

	A = 65, a = 97,
	B = 66, b = 98,
	C = 67, c = 99,
	D = 68, d = 100,
	E = 69, e = 101,
	F = 70, f = 102,
	G = 71, g = 103,
	H = 72, h = 104,
	I = 73, i = 105,
	J = 74, j = 106,
	K = 75, k = 107,
	L = 76, l = 108,
	M = 77, m = 109,
	N = 78, n = 110,
	O = 79, o = 111,
	P = 80, p = 112,
	Q = 81, q = 113,
	R = 82, r = 114,
	S = 83, s = 115,
	T = 84, t = 116,
	U = 85, u = 117,
	V = 86, v = 118,
	W = 87, w = 119,
	X = 88, x = 120,
	Y = 89, y = 121,
	Z = 90, z = 122,

	ESC   = 27, 
	ENTER = 13,
	Space = 32, 
	
	Backspace = 9,

};

struct Point{
	Point();
	int x;
	int y;
};

struct KeyInfo
{
	KeyInfo();
	bool state;
	Point pressedPoint;
	Point releasedPoint;
};

struct MouseInfo
{
	MouseInfo();
	bool isLeftButtonDown;
	bool isMiddleButtonDown;
	bool isRightButtonDown;
	Point currPos;
};


class InputManager
{
public:
	static void Init();
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
	static bool isKeyDown(unsigned int key);
	/**
		Checks if a specified key is currently released.
		@param key - specified key.
	**/
	static bool isKeyUp(unsigned int key);
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

#endif
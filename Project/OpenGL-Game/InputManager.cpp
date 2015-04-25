#include "openGL.h"
#include "InputManager.h"
#include <iostream>
#define DEBUG


Point::Point(){
	x = 0;
	y = 0;
}


KeyInfo::KeyInfo(){
	state = false;
}


MouseInfo::MouseInfo(){
	isLeftButtonDown   = false;
	isMiddleButtonDown = false;
	isRightButtonDown  = false;
}

KeyInfo* InputManager::keySpecialStates = new KeyInfo[256];
KeyInfo* InputManager::keyStates = new KeyInfo[256];
MouseInfo InputManager::mouseInfo;


InputManager::InputManager(){
	glutKeyboardFunc(InputManager::KeyPress);
	glutKeyboardUpFunc(InputManager::KeyUp);
	glutSpecialFunc(InputManager::SpecialKeyPress);
	glutSpecialUpFunc(InputManager::SpecialKeyUp);

	glutMouseFunc(InputManager::MouseInput);

	glutMotionFunc(InputManager::MouseMotion);
	glutPassiveMotionFunc(InputManager::MouseMotion);
}

void InputManager::KeyPress(unsigned char key, int x, int y){
	keyStates[key].state = true;
	
#ifdef DEBUG
	std::cout << "\nKeyPress: " << key;
	std::cout << ", KeyCode: " << (int)key;
	std::cout << ", x: " << x;
	std::cout << ", y: " << y;
	std::cout << ", state: " << (keyStates[key].state) ? "true" : "false";
#endif
}

void InputManager::KeyUp(unsigned char key, int x, int y){
	keyStates[key].state = false;

#ifdef DEBUG
	std::cout << "\nKeyUp: " << key;
	std::cout << ", KeyCode: " << (int)key;
	std::cout << ", x: " << x;
	std::cout << ", y: " << y;
	std::cout << ", state: " << (keyStates[key].state) ? "true" : "false";
#endif
}

void InputManager::SpecialKeyPress(int key, int x, int y){
	keySpecialStates[key].state = true;

#ifdef DEBUG
	std::cout << "\nSpecialKeyPress: " << key;
	std::cout << ", SpecialKeyCode: " << (int)key;
	std::cout << ", x: " << x;
	std::cout << ", y: " << y;
	std::cout << ", state: " << (keySpecialStates[key].state) ? "true" : "false";
#endif
}

void InputManager::SpecialKeyUp(int key, int x, int y){
	keySpecialStates[key].state = false;

#ifdef DEBUG
	std::cout << "\nSpecialKeyUp: " << key;
	std::cout << ", SpecialKeyCode: " << (int)key;
	std::cout << ", x: " << x;
	std::cout << ", y: " << y;
	std::cout << ", state: " << (keySpecialStates[key].state) ? "true" : "false";
#endif
}

void InputManager::MouseInput(int button, int state, int x, int y){
	bool isDown = state == GLUT_DOWN ? true : false;


	mouseInfo.isLeftButtonDown   = button == GLUT_LEFT_BUTTON   ? isDown : mouseInfo.isLeftButtonDown;
	mouseInfo.isMiddleButtonDown = button == GLUT_MIDDLE_BUTTON ? isDown : mouseInfo.isMiddleButtonDown;
	mouseInfo.isRightButtonDown  = button == GLUT_RIGHT_BUTTON  ? isDown : mouseInfo.isRightButtonDown;

	mouseInfo.currPos.x = x;
	mouseInfo.currPos.y = y;

#ifdef DEBUG
	std::cout << "\nMouseInput: ";

	std::cout << "button: " << button;
	std::cout << ", state: " << (isDown) ? "true" : "false";
	std::cout << ", x: " << x;
	std::cout << ", y: " << y;
	std::cout << "\n\t isLeftDown: " << (mouseInfo.isLeftButtonDown)  ? "true" : "false";
	std::cout << "\n\t isMiddle: "   << (mouseInfo.isMiddleButtonDown)? "true" : "false";
	std::cout << "\n\t isRight: "    << (mouseInfo.isRightButtonDown) ? "true" : "false";
#endif
}


void InputManager::MouseMotion(int x, int y){
	mouseInfo.currPos.x = x;
	mouseInfo.currPos.y = y;

#ifdef DEBUG
	std::cout << "\nMouseMotion: ";
	std::cout << "x: " << x;
	std::cout << ", y: " << y;
	std::cout << ", currPosX: " << mouseInfo.currPos.x;
	std::cout << ", currPosY: " << mouseInfo.currPos.y;
#endif
}

bool InputManager::isKeyDown(unsigned char key){
	return keyStates[key].state;

#ifdef DEBUG
	std::cout << "\nisKeyDown: ";
	std::cout << "key: " << key;
	std::cout << ", state: " << (keyStates[key].state) ? "true" : "false";
#endif
}

bool InputManager::isKeyUp(unsigned char key){
	return !keyStates[key].state;

#ifdef DEBUG
	std::cout << "\nisKeyUp: ";
	std::cout << "key: " << key;
	std::cout << ", state: " << (!keyStates[key].state) ? "true" : "false";
#endif
}

bool InputManager::isSpecialKeyDown(unsigned char key){
	return keySpecialStates[key].state;

#ifdef DEBUG
	std::cout << "\nisSpecialKeyDown: ";
	std::cout << "key: " << key;
	std::cout << ", state: " << (keySpecialStates[key].state) ? "true" : "false";
#endif
}

bool InputManager::isSpecialKeyUp(unsigned char key){
	return !keySpecialStates[key].state;

#ifdef DEBUG
	std::cout << "\isSpecialKeyUp: ";
	std::cout << "key: " << key;
	std::cout << ", state: " << (!keySpecialStates[key].state) ? "true" : "false";
#endif
}


Point InputManager::GetMousePosOfKeyPress(unsigned char key){
	return keyStates[key].pressedPoint;

#ifdef DEBUG
	std::cout << "\GetMousePosOfKeyPress: ";
	std::cout << "key: " << key;
	std::cout << ", x: " << keyStates[key].pressedPoint.x;
	std::cout << ", y: " << keyStates[key].pressedPoint.y;
#endif
}

Point InputManager::GetMousePosOfKeyRelease(unsigned char key){
	return keyStates[key].releasedPoint;

#ifdef DEBUG
	std::cout << "\GetMousePosOfKeyRelease: ";
	std::cout << "key: " << key;
	std::cout << ", x: " << keyStates[key].releasedPoint.x;
	std::cout << ", y: " << keyStates[key].releasedPoint.y;
#endif
}

Point InputManager::GetMousePosOfSpecialKeyPress(unsigned char key){
	return keySpecialStates[key].pressedPoint;

#ifdef DEBUG
	std::cout << "\GetMousePosOfSpecialKeyPress: ";
	std::cout << "key: " << key;
	std::cout << ", x: " << keySpecialStates[key].pressedPoint.x;
	std::cout << ", y: " << keySpecialStates[key].pressedPoint.y;
#endif
}

Point InputManager::GetMousePosOfSpecialKeyRelease(unsigned char key){
	return keySpecialStates[key].releasedPoint;

#ifdef DEBUG
	std::cout << "\GetMousePosOfSpecialKeyRelease: ";
	std::cout << "key: " << key;
	std::cout << ", x: " << keySpecialStates[key].releasedPoint.x;
	std::cout << ", y: " << keySpecialStates[key].releasedPoint.y;
#endif
}

bool InputManager::isLeftButtonDown(){
	return mouseInfo.isLeftButtonDown;

#ifdef DEBUG
	std::cout << "\isLeftButtonDown: ";
	std::cout << (mouseInfo.isLeftButtonDown) ? "true" : "false";
#endif
}

bool InputManager::isLeftButtonUp(){
	return !mouseInfo.isLeftButtonDown;

#ifdef DEBUG
	std::cout << "\isLeftButtonUp: ";
	std::cout << (!mouseInfo.isLeftButtonDown) ? "true" : "false";
#endif
}

bool InputManager::isRightButtonDown(){
	return mouseInfo.isRightButtonDown;

#ifdef DEBUG
	std::cout << "\isRightButtonDown: ";
	std::cout << (mouseInfo.isRightButtonDown) ? "true" : "false";
#endif
}

bool InputManager::isRightButtonUp(){
	return !mouseInfo.isRightButtonDown;

#ifdef DEBUG
	std::cout << "\isRightButtonUp: ";
	std::cout << (!mouseInfo.isRightButtonDown) ? "true" : "false";
#endif
}

bool InputManager::isMiddleButtonDown(){
	return mouseInfo.isMiddleButtonDown;

#ifdef DEBUG
	std::cout << "\isMiddleButtonDown: ";
	std::cout << (mouseInfo.isMiddleButtonDown) ? "true" : "false";
#endif
}

bool InputManager::isMiddleButtonUp(){
	return !mouseInfo.isMiddleButtonDown;

#ifdef DEBUG
	std::cout << "\isMiddleButtonUp: ";
	std::cout << (!mouseInfo.isMiddleButtonDown) ? "true" : "false";
#endif
}

Point InputManager::GetMousePos(){
	return mouseInfo.currPos;

#ifdef DEBUG
	std::cout << "\GetMousePos: ";
	std::cout << ", x: " << mouseInfo.currPos.x;
	std::cout << ", y: " << mouseInfo.currPos.y;
#endif
}

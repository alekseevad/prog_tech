#include <iostream>
#include "shape.hpp"
#include "rectangle.hpp"

inline void printObject(Shape* obj);

int main()
{
	Shape* objS;
	Rectangle objR(5.0, 24.0, {1.0, 1.0});
	objS = &objR;
	printObject(objS);
}

inline void printObject(Shape* obj) 
{
	obj->move(13.0, 2.0);
	std::cout << "Move to (13.0, 2.0)\nFrame width: " << obj->getFrameRect().width <<
		"\nFrame height: " << obj->getFrameRect().height <<
		"\nFrame position: " << obj->getFrameRect().pos.x << ", " << obj->getFrameRect().pos.y;
}
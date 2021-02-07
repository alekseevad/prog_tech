#include <iostream>
#include "shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"

void printObject(Shape* obj);

int main()
{
	Shape* objS;
	Rectangle objR(5.0, 24.0, {1.0, 1.0});
	objS = &objR;
	printObject(objS);
	Circle objC(4.0, {0.0, 0.0});
	objS = &objC;
	printObject(objS);
	Triangle objT({ 1.0, 5.0 }, { 0.0, 0.0 }, {1.0, -5.0});
	objS = &objT;
	printObject(objS);
	return 0;
}

void printObject(Shape* obj) 
{
	obj->move(13.0, 2.0);
	std::cout << "Move to (13.0, 2.0)\nFrame width: " << obj->getFrameRect().width <<
		"\nFrame height: " << obj->getFrameRect().height <<
		"\nFrame position: " << obj->getFrameRect().pos.x << ", " << obj->getFrameRect().pos.y;
}
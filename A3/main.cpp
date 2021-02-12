#include <iostream>
#include "../common/shape.hpp"
#include "../common/circle.hpp"
#include "../common/triangle.hpp"
#include "../common/rectangle.hpp"

void printObject(alekseev::Shape* obj);

int main()
{
	alekseev::Shape *objS;
	alekseev::Triangle objT({ 0.0, 0.0 }, { 5.0, 0.0 }, { 0.0, 12.0 });
	objS = &objT;
	printObject(objS);
	return 0;
}

void printObject(alekseev::Shape* obj)
{
	obj->move(13.0, 2.0);
	obj->scale(2);
	obj->move({ 1.0, 1.0 });
	std::cout << "Move to (13.0, 2.0)\nFrame width: " << obj->getFrameRect().width <<
		"\nFrame height: " << obj->getFrameRect().height <<
		"\nFrame position: " << obj->getFrameRect().pos.x << ", " << obj->getFrameRect().pos.y;
}
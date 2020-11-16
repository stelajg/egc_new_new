#pragma once
#include <Core/Engine.h>

class Rectangle_bar
{
public:
	Rectangle_bar();
	~Rectangle_bar();
	Mesh* GetRectangleBorder();
	Mesh* GetRectangle();


private:
	Mesh* rectangle;
	Mesh* rectangle_form;
};

#pragma once
#include <Core/Engine.h>

class Balloon
{
public:
	Balloon(glm::vec3 color);
	~Balloon();
	Mesh* GetBallon();
	Mesh* GetBallon_Line();

private:
	Mesh* balloon_circle;
	Mesh* balloon_line;
};


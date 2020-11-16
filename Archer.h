#pragma once
#include <Core/Engine.h>
#include <Component/SimpleScene.h>

class Archer
{
public:
	Archer();
	~Archer();
	Mesh* GetArch();
	Mesh* GetArchLine();
	Mesh* GetArrow();


private:
	Mesh* arch;
	Mesh* line;
	Mesh* new_arrow;
//protected:
//	float translateX_player, translateY_player;
//	float translateX_arrow, translateY_arrow;
//	float angularStep_arrow;
};

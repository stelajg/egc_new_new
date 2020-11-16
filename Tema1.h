#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>
#include "Archer.h"
#include "Balloon.h"
#include "Rectangle.h"
#include "Shuriken.h"


class Tema1 : public SimpleScene
{
public:
	Tema1();
	~Tema1();

	void Init() override;

private:
	bool IsCollisionPointCircle(float pointX, float pointY, float circleX, float circleY, float circleRadius);
	bool IsCollisionCircleCircle(float circle1X, float circle1Y, float circle2X, float circle2Y, float circle1Radius, float circle2Radius);

	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;


protected:
	
	Archer* archer;
	Rectangle_bar* rectangle_speed_arrow;
	Rectangle_bar* rectangle_score;
	Shuriken* shuriken;
	Balloon* balloons;
	Balloon* player_lives_draw;
	glm::mat3 modelMatrix;
	float translateX_player, translateY_player;
	float translateX_arrow, translateY_arrow;
	float translateX_shuriken, translateY_shuriken;
	float scaleX, scaleY;
	float angularStep;
	float angularStep_arrow;
	float angularStep_shuriken;
	float arrow_mouse_y;
	int player_lives;
	int hold_time_mouse;
	bool mouse_pressed;
	bool mouse_released;
	int player_score;
	glm::ivec2 arrow_coord;
	glm::ivec2 arch_coord;
	glm::ivec2 resolution;
	glm::ivec2 collision_balloon;
	glm::ivec2 collision_arch;
};

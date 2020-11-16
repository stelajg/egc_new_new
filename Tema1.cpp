#include "Tema1.h"

#include <vector>
#include <iostream>
#include <math.h>

#include <Core/Engine.h>
#include "Transform2D.h"



using namespace std;

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}

void Tema1::Init()
{
	resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	glm::vec3 corner = glm::vec3(0, 0, 0);
	float squareSide = 100;

	// compute coordinates of square center
	float cx = corner.x + squareSide / 2;
	float cy = corner.y + squareSide / 2;

	// initialize tx and ty (the translation steps)
	translateX_player = 0;
	translateY_player = 0;
	arrow_mouse_y = 0;

	// initialize sx and sy (the scale factors)
	scaleX = 1;
	scaleY = 1;

	// initialize angularStep
	angularStep = 0;

	mouse_pressed = false;
	mouse_released = false;
	player_lives = 3;
	hold_time_mouse = 0;
	player_score = 0;

	archer = new Archer();
	rectangle_speed_arrow = new Rectangle_bar();
	rectangle_score = new Rectangle_bar();
	shuriken = new Shuriken();
	balloons = new Balloon(glm::vec3(1.f, 1.f, 1.f));
	player_lives_draw = new Balloon(glm::vec3(0.8f, 0.4f, 0.f));
}

bool Tema1::IsCollisionPointCircle(float pointX, float pointY, float circleX, float circleY, float circleRadius) {
	float collisionX = pointX - circleX;
	float collisionY = pointY - circleY;
	float distance = sqrt(collisionX * collisionX + collisionY * collisionY);
	if (distance < circleRadius) {
		return true;
	}
	else
	{
		return false;
	}
}

bool Tema1::IsCollisionCircleCircle(float circle1X, float circle1Y, float circle2X, float circle2Y, float circle1Radius, float circle2Radius) {
	float collisionX = circle1X - circle2X;
	float collisionY = circle1Y - circle2Y;
	float distance = sqrt(collisionX * collisionX + collisionY * collisionY);
	if (distance < (circle1Radius + circle2Radius)) {
		return true;
	}
	else
	{
		return false;
	}
}


void Tema1::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glLineWidth(3);
	glClearColor(0, 0, 0.4, 0.5);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds)
{
	glViewport(0, 0, resolution.x, resolution.y);

	arch_coord.x = 50;
	arch_coord.y = resolution.y / 2 - 100;

	modelMatrix = Transform2D::Translate(arch_coord.x, arch_coord.y + translateY_player);
	RenderMesh2D(archer->GetArchLine(), shaders["VertexColor"], modelMatrix);
	
	angularStep = 190.05;
	modelMatrix = Transform2D::Translate(arch_coord.x, arch_coord.y + 100 + translateY_player);
	modelMatrix *= Transform2D::Rotate(angularStep) * Transform2D::Scale(100, 100);
	RenderMesh2D(archer->GetArch(), shaders["VertexColor"], modelMatrix);

	if(arrow_coord.x > resolution.x){
		translateX_arrow = 0;
		mouse_released = false;
		mouse_pressed = false;
	}

	arrow_coord.x = 150 ;
	arrow_coord.y = resolution.y / 2;
	//if (mouse_pressed == false) {
	//	arrow_coord.y = resolution.y / 2;
	//	translateY_arrow = 0;
	//}
	//else {
	//	arrow_coord.y = resolution.y / 2;
	//	/*arrow_coord.y += cos(1.57 - angularStep_arrow) * 30;*/
	//	cout << translateY_arrow<<endl;
	//}
	
	modelMatrix = Transform2D::Translate(arrow_coord.x + translateX_arrow, arrow_coord.y + translateY_player + translateY_arrow) * Transform2D::Rotate(angularStep_arrow) * Transform2D::Scale(30, 30);
	RenderMesh2D(archer->GetArrow(), shaders["VertexColor"], modelMatrix);
	
	arrow_coord.x += translateX_arrow;

	if (IsCollisionPointCircle((arrow_coord.x+60), (arrow_coord.y - 30), 580.f, (resolution.y / 2 - 25), 50) == true) {
		player_score++;
		modelMatrix = Transform2D::Translate(600, resolution.y / 2 - 25) * Transform2D::Scale(50, 100) * Transform2D::Scale(0, 0);
		RenderMesh2D(balloons->GetBallon(), shaders["VertexColor"], modelMatrix);

		modelMatrix = Transform2D::Translate(580, resolution.y / 2 - 150) * Transform2D::Scale(25, 25) * Transform2D::Scale(0, 0);
		RenderMesh2D(balloons->GetBallon_Line(), shaders["VertexColor"], modelMatrix);
	}
	else {
		modelMatrix = Transform2D::Translate(600, resolution.y / 2 - 25) * Transform2D::Scale(50, 100);
		RenderMesh2D(balloons->GetBallon(), shaders["VertexColor"], modelMatrix);

		modelMatrix = Transform2D::Translate(580, resolution.y / 2 - 150) * Transform2D::Scale(25, 25);
		RenderMesh2D(balloons->GetBallon_Line(), shaders["VertexColor"], modelMatrix);
	}
	
	angularStep_shuriken += deltaTimeSeconds * 1000;
	translateX_shuriken -= deltaTimeSeconds * 50;

	

	if (IsCollisionCircleCircle((700 + translateX_shuriken), (resolution.y / 2), 50, ((resolution.y / 2) + translateY_player), 25, 50) && translateX_shuriken > -576) {
		player_lives--;
		cout << "here=" << translateX_shuriken << endl;
	}

	if (IsCollisionPointCircle((arrow_coord.x + 60), (arrow_coord.y - 30), (700 + translateX_shuriken), (resolution.y / 2), 40)) {
		cout << "hei" <<endl;
		modelMatrix = Transform2D::Translate(700, resolution.y / 2) * Transform2D::Translate(translateX_shuriken, 0) * Transform2D::Scale(0, 0) * Transform2D::Rotate(angularStep_shuriken);
		RenderMesh2D(shuriken->GetShuriken(), shaders["VertexColor"], modelMatrix);
	}
	else {
		modelMatrix = Transform2D::Translate(700, resolution.y / 2) * Transform2D::Translate(translateX_shuriken, 0) * Transform2D::Scale(50, 50) * Transform2D::Rotate(angularStep_shuriken);
		RenderMesh2D(shuriken->GetShuriken(), shaders["VertexColor"], modelMatrix);
	}

	
	

	for (int i = 0; i < player_lives; i++) {
		modelMatrix = Transform2D::Translate(10 + 30*i, 700) * Transform2D::Scale(10, 10);
		RenderMesh2D(player_lives_draw->GetBallon(), shaders["VertexColor"], modelMatrix);
	}
	
	
	modelMatrix = Transform2D::Translate(arch_coord.x - 10, arch_coord.y + translateY_player - 5) * Transform2D::Scale(125, 10);
	RenderMesh2D(rectangle_speed_arrow->GetRectangleBorder(), shaders["VertexColor"], modelMatrix);

	modelMatrix = Transform2D::Translate( arch_coord.x - 10, arch_coord.y + translateY_player - 15) * Transform2D::Scale(5 * std::min(hold_time_mouse, 25), 10);
	RenderMesh2D(rectangle_speed_arrow->GetRectangle(), shaders["VertexColor"], modelMatrix);


	modelMatrix = Transform2D::Translate(resolution.x - 130, resolution.y - 30) * Transform2D::Scale(125, 10);
	RenderMesh2D(rectangle_score->GetRectangleBorder(), shaders["VertexColor"], modelMatrix);

	modelMatrix = Transform2D::Translate(resolution.x - 130, resolution.y - 40) * Transform2D::Scale(5 * player_score, 10);
	RenderMesh2D(rectangle_score->GetRectangle(), shaders["VertexColor"], modelMatrix);
	
}

void Tema1::FrameEnd()
{
	DrawCoordinatSystem();
}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
	if (window->KeyHold(GLFW_KEY_W))
	{
		translateY_player += deltaTime * 50;
	}
	if (window->KeyHold(GLFW_KEY_S))
	{
		translateY_player -= deltaTime * 50;
	}
	if (mouse_pressed == true && mouse_released == false) {
		hold_time_mouse++;
	}

	if (mouse_released == true && mouse_pressed == true) {
		translateX_arrow += hold_time_mouse * cos(angularStep_arrow);
		translateY_arrow -= hold_time_mouse * sin(angularStep_arrow);
	}
}

void Tema1::OnKeyPress(int key, int mods)
{
	// add key press event
}

void Tema1::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
	if (mouse_pressed == false) {
		float aux = mouseX;
		float aux1 = mouseY;
		glm::ivec2 resolution = window->GetResolution();
		angularStep_arrow = atan((2 * arrow_coord.y - (arrow_coord.y + translateY_player) - aux1) / (arrow_coord.x - aux));
		arrow_mouse_y = atan((arrow_coord.x - aux)/(2 * arrow_coord.y - (arrow_coord.y + translateY_player) - aux1));
		/*cout << "atan =" << (2 * arrow_coord.y - (arrow_coord.y + translateY_player) - aux1) / (arrow_coord.x - aux) << endl;
		cout << "angularStep_arrow=" << angularStep_arrow << endl;*/
	}

}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
	cout << "button11 = " << mods << endl; 
	if (button == 1) {
		mouse_pressed = true;
		cout << "button11 = " << mods << endl;
	}
	
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
	if (button == 1) {
		mouse_released = true;
		cout << "button = " << button << endl;
	}
	
	
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}

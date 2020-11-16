#include "Balloon.h"

Balloon::Balloon(glm::vec3 color)
{
	balloonColor = color;
	{
		balloon_circle = new Mesh("balloon_circle");
		std::vector<VertexFormat> vertices;
		std::vector<GLushort> indices;
		GLfloat arg;

		vertices.emplace_back(glm::vec3(0, 0, 0), color);
		for (GLushort i = 0; i < 50; i++)
		{
			arg = 6.28318530718f * i / 50;

			vertices.emplace_back(glm::vec3(cos(arg), sin(arg), 0), glm::vec3(1.f, 1.f, 0.f));
			indices.push_back(i);
		}
		indices.push_back(50);
		indices.push_back(1);

		// Create a new mesh from buffer data
		balloon_circle->InitFromData(vertices, indices);
		balloon_circle->SetDrawMode(GL_TRIANGLE_FAN);


	}
	{
		balloon_line = new Mesh("balloon_line");
		std::vector<VertexFormat> vertices =
		{
			VertexFormat(glm::vec3(1, 1, 0), glm::vec3(1, 1, 1)),	//0
			VertexFormat(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)),	//0
			VertexFormat(glm::vec3(1, -1, 0), glm::vec3(1, 1, 1)),	//0
			VertexFormat(glm::vec3(0, -2, 0), glm::vec3(1, 1, 1)),	//0
			VertexFormat(glm::vec3(1, -3, 0), glm::vec3(1, 1, 1)),	//0
		};

		std::vector<unsigned short> indices =
		{
			0, 1, 2, 3, 4
		};
		balloon_line ->InitFromData( vertices, indices);
		balloon_line->SetDrawMode(GL_LINE_STRIP);
	}
}

Balloon::~Balloon()
{
}
Mesh* Balloon::GetBallon(){
	return balloon_circle;
}
Mesh* Balloon::GetBallon_Line(){
	return balloon_line;
}

glm::vec3 Balloon::GetBalloonColor() {
	return balloonColor;
}
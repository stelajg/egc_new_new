#include "Archer.h"

Archer::Archer(){
	{
		line = new Mesh("line");
		std::vector<VertexFormat> vertices =
		{
			VertexFormat(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)),	//0
			VertexFormat(glm::vec3(0, 200, 0), glm::vec3(1, 1, 1)),	//0

		};

		std::vector<unsigned short> indices =
		{
			0, 1
		};
		line->InitFromData(vertices, indices);
		line->SetDrawMode(GL_LINES);
		
	}
	{
		arch = new Mesh("arch");
		std::vector<VertexFormat> vertices;
		std::vector<GLushort> indices;
		GLfloat arg;

		for (GLushort i = 0; i < 100; i++)
		{
			arg = 6.28318530718f * i / 100 / 2;

			vertices.emplace_back(glm::vec3(cos(arg), sin(arg), 0), glm::vec3(1.f, 1.f, 0.f));
			indices.push_back(i);
		}

		// Create a new mesh from buffer data
		arch->InitFromData(vertices, indices);
		arch->SetDrawMode(GL_LINE_STRIP);
	}
	{
		new_arrow = new Mesh("new_arrow");
		std::vector<VertexFormat> vertices =
		{
			VertexFormat(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)),	//0
			VertexFormat(glm::vec3(1, 0, 0), glm::vec3(1, 1, 1)),	//0
			VertexFormat(glm::vec3(2, 0, 0), glm::vec3(1, 1, 1)),	//0
			VertexFormat(glm::vec3(3, 0, 0), glm::vec3(1, 1, 1)),	//0
			VertexFormat(glm::vec3(3, 1, 0), glm::vec3(1, 1, 1)),	//0
			VertexFormat(glm::vec3(4, 0, 0), glm::vec3(1, 1, 1)),	//0
			VertexFormat(glm::vec3(3, -1, 0), glm::vec3(1, 1, 1)),	//0
		};

		std::vector<unsigned short> indices =
		{
			0, 1, 2, 3, 4, 5, 6, 3
		};
		new_arrow->InitFromData(vertices, indices);
		new_arrow->SetDrawMode(GL_LINE_STRIP);
	}
}
Mesh* Archer::GetArch(){
	return arch;
}
Mesh* Archer::GetArchLine(){
	return line;
}
Mesh* Archer::GetArrow(){
	return new_arrow;
}
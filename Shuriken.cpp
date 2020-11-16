#include "Shuriken.h"

Shuriken::Shuriken()
{
	{
		shuriken = new Mesh("shuriken");
		std::vector<VertexFormat> vertices =
		{
			VertexFormat(glm::vec3(0, -1, 0), glm::vec3(1, 1, 1)),	//0
			VertexFormat(glm::vec3(1, -1, 0), glm::vec3(1, 1, 1)),	//1
			VertexFormat(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)),	//2

			VertexFormat(glm::vec3(1, 0, 0), glm::vec3(1, 1, 1)),	//3
			VertexFormat(glm::vec3(1, 1, 0), glm::vec3(1, 1, 1)),	//4

			VertexFormat(glm::vec3(0, 1, 0), glm::vec3(1, 1, 1)),	//6
			VertexFormat(glm::vec3(-1, 1, 0), glm::vec3(1, 1, 1)),	//7

			VertexFormat(glm::vec3(-1, 0, 0), glm::vec3(1, 1, 1)),	//0
			VertexFormat(glm::vec3(-1, -1, 0), glm::vec3(1, 1, 1)),	//0

		};

		std::vector<unsigned short> indices =
		{
			0,1,2,
			3,4,2,
			5,6,2,
			7,8,2

		};
		shuriken->InitFromData( vertices, indices);
		shuriken->SetDrawMode(GL_TRIANGLES);
	}
}

Shuriken::~Shuriken()
{
}

Mesh* Shuriken::GetShuriken() {
	return shuriken;
}
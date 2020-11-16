#include "Rectangle.h"
Rectangle_bar::Rectangle_bar(){
	{
		rectangle = new Mesh("rectangle");
		std::vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(0, 0, 0), glm::vec3(1, 0, 1)),	//0
			VertexFormat(glm::vec3(1, 0, 0), glm::vec3(1, 0, 1)),	//1
			VertexFormat(glm::vec3(1, 1, 0), glm::vec3(1, 0, 1)),	//2
			VertexFormat(glm::vec3(0, 1, 0), glm::vec3(1, 0, 1)),	//3

		};

		std::vector<unsigned short> indices =
		{
			1,0,3,
			1,2,3,
		};
		rectangle->InitFromData(vertices, indices);
	}
	{
		rectangle_form = new Mesh("rectangle_form");
		std::vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(0, 0, 0), glm::vec3(1, 0, 1)),	//0
			VertexFormat(glm::vec3(1, 0, 0), glm::vec3(1, 0, 1)),	//1
			VertexFormat(glm::vec3(1, -1, 0), glm::vec3(1, 0, 1)),	//2
			VertexFormat(glm::vec3(0, -1, 0), glm::vec3(1, 0, 1)),	//3

		};

		std::vector<unsigned short> indices =
		{
			0,1,2,3,0
		};
		rectangle_form->InitFromData(vertices, indices);
		rectangle_form->SetDrawMode(GL_LINE_STRIP);
	}
}
Mesh* Rectangle_bar::GetRectangleBorder() {
	return rectangle_form;
}
Mesh* Rectangle_bar::GetRectangle() {
	return rectangle;
}
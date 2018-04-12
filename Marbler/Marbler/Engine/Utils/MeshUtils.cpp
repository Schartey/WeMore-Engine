#include "MeshUtils.h"

#include "glm/gtc/constants.hpp"

MeshUtils::MeshUtils()
{
}


VMesh* MeshUtils::CreateCubeGeometry(float width, float height, float depth)
{
	VMesh* Mesh = new VMesh();


	std::vector<Vertex> Vertices = {
		// front
		Vertex(glm::vec3(-width / 2.0f, -height / 2.0f,  depth / 2.0f), glm::vec3(0, 0, 1), glm::vec2(0, 0)),
		Vertex(glm::vec3(width / 2.0f, -height / 2.0f,  depth / 2.0f), glm::vec3(0, 0, 1), glm::vec2(1, 0)),
		Vertex(glm::vec3(width / 2.0f, height / 2.0f,  depth / 2.0f), glm::vec3(0, 0, 1), glm::vec2(1, 1)),
		Vertex(glm::vec3(-width / 2.0f, height / 2.0f,  depth / 2.0f), glm::vec3(0, 0, 1), glm::vec2(0, 1)),
		// back
		Vertex(glm::vec3(width / 2.0f, -height / 2.0f,  -depth / 2.0f), glm::vec3(0, 0, -1), glm::vec2(0, 0)),
		Vertex(glm::vec3(-width / 2.0f, -height / 2.0f,  -depth / 2.0f), glm::vec3(0, 0, -1), glm::vec2(1, 0)),
		Vertex(glm::vec3(-width / 2.0f, height / 2.0f,  -depth / 2.0f), glm::vec3(0, 0, -1), glm::vec2(1, 1)),
		Vertex(glm::vec3(width / 2.0f, height / 2.0f,  -depth / 2.0f), glm::vec3(0, 0, -1), glm::vec2(0, 1)),
		// right
		Vertex(glm::vec3(width / 2.0f, -height / 2.0f,  depth / 2.0f), glm::vec3(1, 0, 0), glm::vec2(0, 0)),
		Vertex(glm::vec3(width / 2.0f, -height / 2.0f,  -depth / 2.0f), glm::vec3(1, 0, 0), glm::vec2(1, 0)),
		Vertex(glm::vec3(width / 2.0f, height / 2.0f,  -depth / 2.0f), glm::vec3(1, 0, 0), glm::vec2(1, 1)),
		Vertex(glm::vec3(width / 2.0f, height / 2.0f,  depth / 2.0f), glm::vec3(1, 0, 0), glm::vec2(0, 1)),
		// left
		Vertex(glm::vec3(-width / 2.0f, -height / 2.0f,  -depth / 2.0f), glm::vec3(-1, 0, 0), glm::vec2(0, 0)),
		Vertex(glm::vec3(-width / 2.0f, -height / 2.0f,  depth / 2.0f), glm::vec3(-1, 0, 0), glm::vec2(1, 0)),
		Vertex(glm::vec3(-width / 2.0f, height / 2.0f,  depth / 2.0f), glm::vec3(-1, 0, 0), glm::vec2(1, 1)),
		Vertex(glm::vec3(-width / 2.0f, height / 2.0f,  -depth / 2.0f), glm::vec3(-1, 0, 0), glm::vec2(0, 1)),
		// top
		Vertex(glm::vec3(-width / 2.0f, height / 2.0f,  -depth / 2.0f), glm::vec3(0, 1, 0), glm::vec2(0, 0)),
		Vertex(glm::vec3(-width / 2.0f, height / 2.0f,  depth / 2.0f), glm::vec3(0, 1, 0), glm::vec2(1, 0)),
		Vertex(glm::vec3(width / 2.0f, height / 2.0f,  depth / 2.0f), glm::vec3(0, 1, 0), glm::vec2(1, 1)),
		Vertex(glm::vec3(width / 2.0f, height / 2.0f,  -depth / 2.0f), glm::vec3(0, 1, 0), glm::vec2(0, 1)),
		// bottom
		Vertex(glm::vec3(-width / 2.0f, -height / 2.0f,  -depth / 2.0f), glm::vec3(0, -1, 0), glm::vec2(0, 0)),
		Vertex(glm::vec3(width / 2.0f, -height / 2.0f,  -depth / 2.0f), glm::vec3(0, -1, 0), glm::vec2(1, 0)),
		Vertex(glm::vec3(width / 2.0f, -height / 2.0f,  depth / 2.0f), glm::vec3(0, -1, 0), glm::vec2(1, 1)),
		Vertex(glm::vec3(-width / 2.0f, -height / 2.0f,  depth / 2.0f), glm::vec3(0, -1, 0), glm::vec2(0, 1))
	};

	std::vector<int> Indices = {
		// front
		0, 1, 2,
		2, 3, 0,
		// back
		4, 5, 6,
		6, 7, 4,
		// right
		8, 9, 10,
		10, 11, 8,
		// left
		12, 13, 14,
		14, 15, 12,
		// top
		16, 17, 18,
		18, 19, 16,
		// bottom
		20, 21, 22,
		22, 23, 20
	};

	BBox BoundingBox = BBox(glm::vec3(-width / 2.0f, -height / 2.0f, -depth / 2.0f), glm::vec3(width / 2.0f, height / 2.0f, depth  / 2.0f));
	
	Mesh->Setup(Vertices, Indices, BoundingBox);

	return Mesh;
}

VMesh* MeshUtils::CreateCylinderGeometry(unsigned int segments, float height, float radius)
{
	VMesh* Mesh = new VMesh();

	std::vector<Vertex> Vertices;
	std::vector<int> Indices;

	// center vertices
	Vertices.push_back(Vertex(glm::vec3(0, -height / 2.0f, 0), glm::vec3(0, -1, 0), glm::vec2(0.5, 0.5f)));
	Vertices.push_back(Vertex(glm::vec3(0, height / 2.0f, 0), glm::vec3(0, 1, 0), glm::vec2(0.5f, 0.5f)));

	// circle segments
	float angle_step = 2.0f * glm::pi<float>() / float(segments);
	for (unsigned int i = 0; i < segments; i++) {
		glm::vec3 circlePos = glm::vec3(
			glm::cos(i * angle_step) * radius,
			-height / 2.0f,
			glm::sin(i * angle_step) * radius
		);

		glm::vec2 squareToCirlceUV = glm::vec2(
			(circlePos.x / radius) * 0.5f + 0.5f,
			(circlePos.z / radius) * 0.5f + 0.5f
		);

		// bottom ring vertex
		Vertices.push_back(Vertex(circlePos, glm::vec3(0, -1, 0), squareToCirlceUV));
		Vertices.push_back(Vertex(circlePos, glm::normalize(circlePos - glm::vec3(0, -height / 2.0f, 0)), glm::vec2(i * angle_step / (2.0f * glm::pi<float>()), 0)));

		// top ring vertex
		circlePos.y = height / 2.0f;

		Vertices.push_back(Vertex(circlePos, glm::vec3(0, 1, 0), squareToCirlceUV));
		Vertices.push_back(Vertex(circlePos, glm::normalize(circlePos - glm::vec3(0, height / 2.0f, 0)), glm::vec2(i * angle_step / (2.0f * glm::pi<float>()), 1)));

		// bottom face
		Indices.push_back(0);
		Indices.push_back(2 + i * 4);
		Indices.push_back(i == segments - 1 ? 2 : 2 + (i + 1) * 4);

		// top face
		Indices.push_back(1);
		Indices.push_back(i == segments - 1 ? 4 : (i + 2) * 4);
		Indices.push_back((i + 1) * 4);

		// side faces
		Indices.push_back(3 + i * 4);
		Indices.push_back(i == segments - 1 ? 5 : 5 + (i + 1) * 4);
		Indices.push_back(i == segments - 1 ? 3 : 3 + (i + 1) * 4);

		Indices.push_back(i == segments - 1 ? 5 : 5 + (i + 1) * 4);
		Indices.push_back(3 + i * 4);
		Indices.push_back(5 + i * 4);
	}

	BBox BoundingBox = BBox(glm::vec3(-radius, -height / 2.0f, -radius), glm::vec3(radius, height / 2.0f, radius));

	Mesh->Setup(Vertices, Indices, BoundingBox);

	return Mesh;
}

VMesh* MeshUtils::CreateSphereGeometry(unsigned int longitudeSegments, unsigned int latitudeSegments, float radius)
{
	VMesh* Mesh = new VMesh();

	std::vector<Vertex> Vertices;
	std::vector<int> Indices;

	Vertices.push_back(Vertex(glm::vec3(0.0f, radius, 0.0f), glm::vec3(0.0f, radius, 0.0f), glm::vec2(0.5f, 1.0f)));
	Vertices.push_back(Vertex(glm::vec3(0.0f, -radius, 0.0f), glm::vec3(0.0f, -radius, 0.0f), glm::vec2(0.5f, 0.0f)));
	
	// first and last ring
	for (unsigned int j = 0; j < longitudeSegments; j++) {
		Indices.push_back(0);
		Indices.push_back(j == longitudeSegments - 1 ? 2 : (j + 3));
		Indices.push_back(2 + j);

		Indices.push_back(2 + (latitudeSegments - 2)*longitudeSegments + j);
		Indices.push_back(j == longitudeSegments - 1 ? 2 + (latitudeSegments - 2)*longitudeSegments : 2 + (latitudeSegments - 2)*longitudeSegments + j + 1);
		Indices.push_back(1);
	}

	// vertices and rings
	for (unsigned int i = 1; i < latitudeSegments; i++) {
		float verticalAngle = float(i) * glm::pi<float>() / float(latitudeSegments);
		for (unsigned int j = 0; j < longitudeSegments; j++) {
			float horizontalAngle = float(j) * 2.0f * glm::pi<float>() / float(longitudeSegments);
			glm::vec3 position = glm::vec3(
				radius * glm::sin(verticalAngle) * glm::cos(horizontalAngle),
				radius * glm::cos(verticalAngle),
				radius * glm::sin(verticalAngle) * glm::sin(horizontalAngle)
			);
			Vertices.push_back(Vertex(position, glm::normalize(position), glm::vec2(horizontalAngle / (2.0f * glm::pi<float>()), verticalAngle / glm::pi<float>())));
			
			if (i == 1) continue;

			Indices.push_back(2 + (i - 1)*longitudeSegments + j);
			Indices.push_back(j == longitudeSegments - 1 ? 2 + (i - 2)*longitudeSegments : 2 + (i - 2)*longitudeSegments + j + 1);
			Indices.push_back(j == longitudeSegments - 1 ? 2 + (i - 1)*longitudeSegments : 2 + (i - 1)*longitudeSegments + j + 1);

			Indices.push_back(j == longitudeSegments - 1 ? 2 + (i - 2)*longitudeSegments : 2 + (i - 2)*longitudeSegments + j + 1);
			Indices.push_back(2 + (i - 1)*longitudeSegments + j);
			Indices.push_back(2 + (i - 2)*longitudeSegments + j);
		}
	}

	BBox BoundingBox = BBox(glm::vec3(-radius, -radius / 2.0f, -radius), glm::vec3(radius, radius / 2.0f, radius));

	Mesh->Setup(Vertices, Indices, BoundingBox);

	return Mesh;
}

MeshUtils::~MeshUtils()
{
}


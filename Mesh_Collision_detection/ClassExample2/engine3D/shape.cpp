#include <iostream>

#include "shape.h"

#include "kdtree.h"


Mesh*  Shape::get_mesh() { return this->mesh; }


 Vertex* Shape::initcube(double centerx, double centery, double centerz, double widthx, double highty, double depthz) {

	Vertex* myCube = (Vertex*)malloc(24 * sizeof(Vertex)*44);
	myCube[0] = Vertex(glm::vec3(-widthx + centerx, -highty + centery, -depthz + centerz), glm::vec2(1, 0), glm::vec3(0, 0, -1), glm::vec3(0, 0, 1));
	myCube[1] = Vertex(glm::vec3(-widthx + centerx, highty + centery, -depthz + centerz), glm::vec2(0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 0, 1));
	myCube[2] = Vertex(glm::vec3(widthx + centerx, highty + centery, -depthz + centerz), glm::vec2(0, 1), glm::vec3(0, 0, -1), glm::vec3(0, 0, 1));
	myCube[3] = Vertex(glm::vec3(widthx + centerx, -highty + centery, -depthz + centerz), glm::vec2(1, 1), glm::vec3(0, 0, -1), glm::vec3(0, 0, 1));

	myCube[4] = Vertex(glm::vec3(-widthx + centerx, -highty + centery, depthz + centerz), glm::vec2(1, 0), glm::vec3(0, 0, 1), glm::vec3(0, 0, 1));
	myCube[5] = Vertex(glm::vec3(-widthx + centerx, highty + centery, depthz + centerz), glm::vec2(0, 0), glm::vec3(0, 0, 1), glm::vec3(0, 0, 1));
	myCube[6] = Vertex(glm::vec3(widthx + centerx, highty + centery, depthz + centerz), glm::vec2(0, 1), glm::vec3(0, 0, 1), glm::vec3(0, 0, 1));
	myCube[7] = Vertex(glm::vec3(widthx + centerx, -highty + centery, depthz + centerz), glm::vec2(1, 1), glm::vec3(0, 0, 1), glm::vec3(0, 0, 1));

	myCube[8] = Vertex(glm::vec3(-widthx + centerx, -highty + centery, -depthz + centerz), glm::vec2(0, 1), glm::vec3(0, -1, 0), glm::vec3(0, 1, 0));
	myCube[9] = Vertex(glm::vec3(-widthx + centerx, -highty + centery, depthz + centerz), glm::vec2(1, 1), glm::vec3(0, -1, 0), glm::vec3(0, 1, 0));
	myCube[10] = Vertex(glm::vec3(widthx + centerx, -highty + centery, depthz + centerz), glm::vec2(1, 0), glm::vec3(0, -1, 0), glm::vec3(0, 1, 0));
	myCube[11] = Vertex(glm::vec3(widthx + centerx, -highty + centery, -depthz + centerz), glm::vec2(0, 0), glm::vec3(0, -1, 0), glm::vec3(0, 1, 0));

	myCube[12] = Vertex(glm::vec3(-widthx + centerx, highty + centery, -depthz + centerz), glm::vec2(0, 1), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
	myCube[13] = Vertex(glm::vec3(-widthx + centerx, highty + centery, depthz + centerz), glm::vec2(1, 1), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
	myCube[14] = Vertex(glm::vec3(widthx + centerx, highty + centery, depthz + centerz), glm::vec2(1, 0), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
	myCube[15] = Vertex(glm::vec3(widthx + centerx, highty + centery, -depthz + centerz), glm::vec2(0, 0), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

	myCube[16] = Vertex(glm::vec3(-widthx + centerx, -highty + centery, -depthz + centerz), glm::vec2(1, 1), glm::vec3(-1, 0, 0), glm::vec3(1, 0, 0));
	myCube[17] = Vertex(glm::vec3(-widthx + centerx, -highty + centery, depthz + centerz), glm::vec2(1, 0), glm::vec3(-1, 0, 0), glm::vec3(1, 0, 0));
	myCube[18] = Vertex(glm::vec3(-widthx + centerx, highty + centery, depthz + centerz), glm::vec2(0, 0), glm::vec3(-1, 0, 0), glm::vec3(1, 0, 0));
	myCube[19] = Vertex(glm::vec3(-widthx + centerx, highty + centery, -depthz + centerz), glm::vec2(0, 1), glm::vec3(-1, 0, 0), glm::vec3(1, 0, 0));

	myCube[20] = Vertex(glm::vec3(widthx + centerx, -highty + centery, -depthz + centerz), glm::vec2(1, 1), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0));
	myCube[21] = Vertex(glm::vec3(widthx + centerx, -highty + centery, depthz + centerz), glm::vec2(1, 0), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0));
	myCube[22] = Vertex(glm::vec3(widthx + centerx, highty + centery, depthz + centerz), glm::vec2(0, 0), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0));
	myCube[23] = Vertex(glm::vec3(widthx + centerx, highty + centery, -depthz + centerz), glm::vec2(0, 1), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0));
	return myCube;
}


Shape::Shape(const Shape& shape)
{
	if(shape.mesh)
		mesh = shape.mesh;
	if(shape.lineMesh)
		lineMesh = shape.lineMesh;
	tex = shape.tex;
	isCopy = true;
}
Shape::Shape(const std::string& fileName) {
	mesh = new Mesh(fileName);
	tex = 0;
	isCopy = false;
}

Shape::Shape(const std::string & fileName, const unsigned maxFaces)
{
	mesh = new Mesh(fileName, maxFaces);
	tex = 0;
	isCopy = false;

	//Kdtree tree = mesh->get_kdtree();
	//Vertex* tmp = initcube(tree.getRoot()->center.x, tree.getRoot()->center.y, tree.getRoot()->center.z, tree.getRoot()->halfwidthX, tree.getRoot()->halfhightY, tree.getRoot()->halfdepthZ);
	//this->mycube = new Mesh(tmp, sizeof(tmp) * sizeof(Vertex) * 24 / sizeof(tmp[0]), indices, sizeof(indices) / sizeof(indices[0]));
	
}

Shape::Shape(const std::string& fileName,const std::string& textureFileName){
	mesh = new Mesh(fileName); 
	tex = new Texture(textureFileName);
	isCopy = false;

	Kdtree tree = mesh->kdtree;
	Vertex* tmp = initcube(tree.getRoot()->center.x, tree.getRoot()->center.y, tree.getRoot()->center.z, tree.getRoot()->halfwidthX, tree.getRoot()->halfhightY, tree.getRoot()->halfdepthZ);
	this->mycube = new Mesh(tmp, (sizeof(tmp) * 44 * 24) / sizeof(tmp[0]), indices, sizeof(indices) / sizeof(indices[0]));

}

Shape::Shape(const std::string & fileName, const std::string & textureFileName, const unsigned maxFaces)
{

	mesh = new Mesh(fileName, maxFaces);
	tex = new Texture(textureFileName);
	isCopy = false;

	Kdtree tree = mesh->kdtree;
	Vertex* tmp = initcube(tree.getRoot()->center.x, tree.getRoot()->center.y, tree.getRoot()->center.z, tree.getRoot()->halfwidthX, tree.getRoot()->halfhightY, tree.getRoot()->halfdepthZ);
	this->mycube = new Mesh(tmp, (sizeof(tmp) * 44 * 24) / sizeof(tmp[0]), indices, sizeof(indices) / sizeof(indices[0]));	

}

Shape::Shape(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{
	mesh = new Mesh(vertices,numVertices,indices,numIndices);
	tex = 0; 
	isCopy = false;


	Kdtree tree = mesh->kdtree;
	Vertex* tmp = initcube(tree.getRoot()->center.x, tree.getRoot()->center.y, tree.getRoot()->center.z, tree.getRoot()->halfwidthX, tree.getRoot()->halfhightY, tree.getRoot()->halfdepthZ);
	this->mycube = new Mesh(tmp, (sizeof(tmp) * 44 * 24) / sizeof(tmp[0]), indices, sizeof(indices) / sizeof(indices[0]));


}

Shape::Shape(LineVertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{

	lineMesh = new LineMesh(vertices,numVertices,indices,numIndices);
	tex = 0; 
	isCopy = false;
}


Shape::Shape(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices,const std::string& textureFileName)
{
	mesh = new Mesh(vertices,numVertices,indices,numIndices);
	tex = new Texture(textureFileName);
	isCopy = false;
}

void Shape::addMesh(Vertex* vertices, unsigned int numVertices,unsigned int* indices, unsigned int numIndices, const std::string& textureFileName)
{
	mesh = new Mesh(vertices,numVertices,indices,numIndices);
	tex = new Texture(textureFileName);
}

void Shape::addMesh(Vertex* vertices, unsigned int numVertices,unsigned int* indices, unsigned int numIndices)
{
	mesh = new Mesh(vertices,numVertices,indices,numIndices);
}

void Shape::addLineMesh(LineVertex* vertices, unsigned int numVertices,unsigned int* indices, unsigned int numIndices)
{
	lineMesh = new LineMesh(vertices,numVertices,indices,numIndices);
}

void Shape::draw(int mode)
{
	//transformations
	if (tex)
		tex->Bind();

	if (mesh)
	{
		mesh->Draw(mode);
		if (this->mycube != 0)
		{
			mycube->Draw(2);
		}
		else
		{
			//error
		}
	}
	
	if (lineMesh)
		lineMesh->Draw();
	
}

Shape::~Shape(void)
{
	if(!isCopy)
	{
		if(mesh)
 			delete mesh;
		if(lineMesh)
			delete lineMesh;
		if(tex)
			delete tex;
	}
}

void Shape::getPoints(std::list<glm::vec3> &pList)
{

}
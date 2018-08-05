#include <Windows.h>
#include <iostream>
#include "display.h"
#include "inputManager.h"
#include "Kdtree.h"
#include "Eigen/Dense"

float far1 = 1000.0f;
float near1 = 1.0f;
Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "OpenGL");
Scene scn(glm::vec3(0.0f, 0.0f, -15.0f), CAM_ANGLE, relation, near1, far1);
glm::vec3 YAxis = glm::vec3(0, 1, 0);
glm::vec3 TranslatePos = glm::vec3(5, 0, 0);

std::queue<std::pair<Node*, Node*>> queue;
using namespace Eigen;
/*
void ComputeCovarianceMatrix(const Eigen::VectorXd* pVertices, const int numVertices)
{
	MatrixXd 	covariance= MatrixXd::Identity(3, 3);


	// duplicate the vector array
	VectorXd* pVectors = new VectorXd[numVertices];

	// compute the average x, y, z values
	VectorXd avg(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < numVertices; ++i)
	{
		pVectors[i] = pVertices[i];
		avg += pVertices[i];
	}
	avg /= static_cast<float>(numVertices);

	for (int i = 0; i < numVertices; ++i)
	{
		pVectors[i] -= avg;
}
	MatrixXd Y = MatrixXd::Identity(3, numVertices);

	for (int i = 0; i <3; i++) {
		for (int j = 0; j <numVertices; j++) {
			Y(i,j) = pVertices[j][i];
		}
	}

	MatrixXd S = MatrixXd::Identity(3, 3);
	S = Y*Y.transpose();

	Eigen::JacobiSVD<Eigen::MatrixXd> svd(S, Eigen::ComputeFullU | Eigen::ComputeFullV);

}
*/
bool equ(Node* A, Node * B, glm::vec3 L, glm::mat4 trt1, glm::mat4 trt2) {

	float res = 0;

	glm::vec4 center1 = trt1*A->center;
	glm::vec4 center2 = trt2*B->center;

	glm::vec3 T = glm::vec3(center1.x - center2.x, center1.y - center2.y, center1.z - center2.z);
	float dotres = glm::dot(T, L);
	float absdot = glm::abs(dotres);

	glm::vec3 AxisAx = A->halfwidthX*glm::vec3(trt1*glm::vec4(A->axisX, 0));
	float fi = glm::dot(AxisAx, L);
	float fiabsdot = glm::abs(fi);

	glm::vec3 AxisAy = A->halfhightY*glm::vec3(trt1*glm::vec4(A->axisY, 0));
	float se = glm::dot(AxisAy, L);
	float seabsdot = glm::abs(se);

	glm::vec3 AxisAz = A->halfdepthZ*glm::vec3(trt1*glm::vec4(A->axisZ, 0));
	float th = glm::dot(AxisAz, L);
	float thabsdot = glm::abs(th);

	glm::vec3 AxisBx = B->halfwidthX*glm::vec3(trt1*glm::vec4(B->axisX, 0));
	float fiB = glm::dot(AxisBx, L);
	float fiBabsdot = glm::abs(fiB);

	glm::vec3 AxisBy = B->halfhightY*glm::vec3(trt1*glm::vec4(B->axisY, 0));
	float seB = glm::dot(AxisBy, L);
	float seBabsdot = glm::abs(seB);

	glm::vec3 AxisBz = B->halfdepthZ*glm::vec3(trt1*glm::vec4(B->axisZ, 0));
	float thB = glm::dot(AxisBz, L);
	float thBabsdot = glm::abs(thB);

	res = fiabsdot + seabsdot + thabsdot + fiBabsdot + seBabsdot + thBabsdot;


	return absdot > res;

}


bool collide(Node* A, Node* B, glm::mat4 trt1, glm::mat4 trt2)
{
	glm::vec3 L;
	L =glm::vec3(trt1*glm::vec4(A->axisX,0));

	if (equ(A, B, L, trt1, trt2)) {
		return false;
	}
	L = glm::vec3(trt1*glm::vec4(A->axisY, 0));

	if (equ(A, B, L, trt1, trt2)) {

		return false;
	}
	L = glm::vec3(trt1*glm::vec4(A->axisZ, 0));;

	if (equ(A, B, L, trt1, trt2)) {

		return false;
	}
	L = glm::vec3(trt1*glm::vec4(B->axisX, 0));;

	if (equ(A, B, L, trt1, trt2)) {

		return false;
	}
	L = glm::vec3(trt1*glm::vec4(A->axisY, 0));
	if (equ(A, B, L, trt1, trt2)) {

		return false;
	}
	L = glm::vec3(trt1*glm::vec4(A->axisZ, 0));

	if (equ(A, B, L, trt1, trt2)) {
		return false;
	}
	L = glm::vec3(trt1*glm::vec4(A->axisX, 0))*glm::vec3(trt1*glm::vec4(B->axisX, 0));
	if (equ(A, B, L, trt1, trt2)) {
		return false;
	}
	L = glm::vec3(trt1*glm::vec4(A->axisX, 0))*glm::vec3(trt1*glm::vec4(B->axisY, 0));
	if (equ(A, B, L, trt1, trt2)) {
		return false;
	}
	L = glm::vec3(trt1*glm::vec4(A->axisX, 0))*glm::vec3(trt1*glm::vec4(A->axisZ, 0));
		if (equ(A, B, L, trt1, trt2)) {
		return false;
	}
	L = glm::vec3(trt1*glm::vec4(A->axisY, 0))*glm::vec3(trt1*glm::vec4(B->axisX, 0));
		
	if (equ(A, B, L, trt1, trt2)) {
		return false;
	}
	L = glm::vec3(trt1*glm::vec4(A->axisY, 0))*glm::vec3(trt1*glm::vec4(B->axisY, 0));
	if (equ(A, B, L, trt1, trt2)) {
		return false;
	}
	L = glm::vec3(trt1*glm::vec4(A->axisY, 0))*glm::vec3(trt1*glm::vec4(B->axisZ, 0));
	if (equ(A, B, L, trt1, trt2)) {
		return false;
	}
	L = glm::vec3(trt1*glm::vec4(A->axisZ, 0))*glm::vec3(trt1*glm::vec4(B->axisX, 0));
	if (equ(A, B, L, trt1, trt2)) {
		return false;
	}
	L = glm::vec3(trt1*glm::vec4(A->axisZ, 0))*glm::vec3(trt1*glm::vec4(B->axisY, 0));
	if (equ(A, B, L, trt1, trt2)) {
		return false;
	}
	L = glm::vec3(trt1*glm::vec4(A->axisZ, 0))*glm::vec3(trt1*glm::vec4(B->axisZ, 0));
	if (equ(A, B, L, trt1, trt2)) {
		return false;
	}
	return true;
}


bool find_collision(Scene& scn, int index1, int index2) {
	queue.push(std::pair<Node*, Node*>(scn.shapes[index1]->mesh->get_kdtree().getRoot(), scn.shapes[index2]->mesh->get_kdtree().getRoot()));

	while (!queue.empty()) {
		std::pair<Node*, Node*> front = queue.front();
		queue.pop();

		if (collide(front.first, front.second, scn.shapes[index1]->makeTransScale(glm::mat4(1)), scn.shapes[index2]->makeTransScale(glm::mat4(1)))) {
			if (front.first->leaf_father() && front.second->leaf_father()) {
				*scn.speedx = 0;
				*scn.speedy = 0;
				scn.to_draw->push(std::pair<int,Node*>(index1, front.first));
				scn.to_draw->push(std::pair<int,Node*>(index2, front.second ));
		return true;
			}
			else if (front.second->leaf_father() && front.first != nullptr) {
				queue.push(std::pair<Node*, Node*>(front.first->left, front.second));
				queue.push(std::pair<Node*, Node*>(front.first->right, front.second));
			}
			else if (front.first->leaf_father() && front.second != nullptr) {
				queue.push(std::pair<Node*, Node*>(front.first, front.second->left));
				queue.push(std::pair<Node*, Node*>(front.first, front.second->right));
			}
			else {
				queue.push(std::pair<Node*, Node*>(front.first->left, front.second->left));
				queue.push(std::pair<Node*, Node*>(front.first->right, front.second->left));
				queue.push(std::pair<Node*, Node*>(front.first->left, front.second->right));
				queue.push(std::pair<Node*, Node*>(front.first->right, front.second->right));
			}
		}
	}
	return true;
}




int main(int argc, char** argv)
{

	initCallbacks(display);
	//scn.addShape("./res/objs/bigbox.obj","./res/textures/box0.bmp");
	//scn.addShape("./res/objs/testboxNoUV.obj");
	//scn.addShape("./res/objs/testboxNoUV.obj", 6);

	scn.addShape("./res/objs/monkey3.obj", "./res/textures/grass.bmp", 512U);
	scn.addShape("./res/objs/monkey3.obj", "./res/textures/grass.bmp", 512U);


	//scn.addShape("./res/objs/monkeyNoUV.obj", "./res/textures/grass.bmp", 1600U);
	//scn.addShape("./res/objs/monkeyNoUV.obj", "./res/textures/grass.bmp", 10000U);
	//scn.addShape("./res/objs/monkeyNoUV.obj", "./res/textures/grass.bmp");

	scn.addShader("./res/shaders/basicShader");
	scn.addShader("./res/shaders/pickingShader");

	// Each will rotate around its Y axis, and will be moved a predefined distance
	for (int i = 0; i < scn.shapes.size(); i++) {
		scn.shapes[i]->myTranslate((float)i * TranslatePos, 0);
		//scn.shapes[0]->myRotate(50.0f, glm::vec3(1,1,0));
		scn.shapes[i]->myRotate(180.0f, glm::vec3(0, 1, 0));


	}

	while (!display.toClose())
	{
		Sleep(3);
		display.Clear(0.7f, 0.7f, 0.7f, 1.0f);
		find_collision(scn, 0, 1);
		float p1 = *scn.speedx;
		float p2 = *scn.speedy;
		scn.shapes[1]->myTranslate(glm::vec3(p1, p2, 0), 0);

		scn.draw(0, 0, true, 0, nullptr);
		display.SwapBuffers();
		display.pullEvent();
	}

	return 0;
}
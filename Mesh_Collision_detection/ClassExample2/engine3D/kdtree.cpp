/**
*
* k-d tree implementation file
*
* author: Arvind Rao
* license: GNU
*
*
*/
#include "kdtree.h"
#include <iostream>

// implementation of Node Class

Node::Node(int _n) { left = 0; right = 0; }
Node::Node(int _n, vecType _data) : data(_data) { left = 0; right = 0; }

Node::~Node() {}

bool Node::is_leaf()
{
	if (this->right == NULL && this->left == NULL)
	{
		return true;
	}
	return false;
}

bool Node::leaf_father()
{
	if (this->is_leaf() == true)
		return false;
	if (this->left != NULL)
	{
		if (!this->left->is_leaf())
			return false;
	}
	if (this->right != NULL)
	{
		if (!this->right->is_leaf())
			return false;
	}
	return true;
}


// implementation of kdtree

Kdtree::Kdtree() {}
Kdtree::~Kdtree() {
}

/*
*
*
*/
Kdtree::vecType Kdtree::findMedian(int axis, std::list<Kdtree::vecType> &plist, std::list<Kdtree::vecType> &left,
	std::list<Kdtree::vecType> &right)
{
	Kdtree::vecType median;
	int size = plist.size();
	int med = ceil(float(size) / float(2));
	int count = 0;

	if (size == 1)
		return plist.front();

	// Using lambda function here, to define comparison function--parametrized by 'axis'
	plist.sort([&](Kdtree::vecType& a, Kdtree::vecType& b) {return a[axis] < b[axis]; });

	for (auto& x : plist)
	{
		if (count < med)
			left.push_back(x);
		else
			right.push_back(x);
		++count;
	}
	median = left.back();
	left.pop_back();
	return median;
}

void Kdtree::print_data(vecType pt)
{
	for (int i = 0; i < N; i++)
	{
		std::cout << pt[i] << ", ";
	}
	std::cout << "\n";
}

/*
*
*
*/
void Kdtree::printTree(Node* head)
{
	//find the tree depth 
	int maxdepth = 3;
	int spaces = pow(2, maxdepth + 1) - 1;
	int depth = 0;
	std::cout << "center, " << head->center.x << head->center.y << head->center.z << std::endl;
	std::cout << "\n**** Print of Tree **********\n";
	std::queue< Node* > current, next;
	Node * temp = head;
	current.push(temp);

	while (!current.empty())
	{
		temp = current.front();
		current.pop();

		if (temp == nullptr)
			std::cout << "NULL\n";
		else
		{
			Kdtree::print_data(temp->data);
			next.push(temp->left);
			next.push(temp->right);
		}
		if (current.empty())
		{
			depth++;
			std::cout << "level: " << depth << "\n";
			std::swap(current, next);
		}
	}
}

/*
*  algorithm is based on http://en.wikipedia.org/wiki/Kd_tree
*/
void Kdtree::makeTree(std::list<Kdtree::vecType>& plist)
{
	Node* head = new Node(3);
	Kdtree::_makeTree(head, plist, 0);
	Kdtree::root = head;
}

void Kdtree::findCenter(Node* head, std::list<Kdtree::vecType>& plist)

{
	double maxx = -INFINITY;
	double maxy = -INFINITY;
	double maxz = -INFINITY;
	double minx = INFINITY;
	double miny = INFINITY;
	double minz = INFINITY;
	for (auto& x : plist)
	{
		if (x.x <minx) {
			minx = x.x;
		}
		if (x.y < miny) {
			miny = x.y;
		}
		if (x.z < minz) {
			minz = x.z;
		}
		if (x.x >maxx) {
			maxx = x.x;
		}
		if (x.y > maxy) {
			maxy = x.y;
		}
		if (x.z > maxz) {
			maxz = x.z;
		}
	}
	head->center = (glm::vec4(maxx, maxy, maxz, 1) + glm::vec4(minx, miny, minz, 1)) / 2.0f;
	head->halfwidthX = maxx - head->center.x;
	head->halfhightY = maxy - head->center.y;
	head->halfdepthZ = maxz - head->center.z;
}

void Kdtree::_makeTree(Node* head, std::list<Kdtree::vecType>& plist, int depth)
{
	if (!plist.empty())
	{
		int k = N;
		int axis = depth % k;

		std::list<Kdtree::vecType> left_list;
		std::list<Kdtree::vecType> right_list;
		Kdtree::vecType median = Kdtree::findMedian(axis, plist, left_list, right_list);
		head->data = median;
		findCenter(head, plist);
		Node* left_node = new Node(k);
		Node* right_node = new Node(k);
		Kdtree::_makeTree(left_node, left_list, depth + 1);
		if (!left_list.empty()) head->left = left_node;

		Kdtree::_makeTree(right_node, right_list, depth + 1);
		if (!right_list.empty()) head->right = right_node;
	}
}
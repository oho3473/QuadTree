#pragma once

#include<memory>

struct Point
{
	int x;
	int y;

	Point() :x{ 0 }, y{ 0 }
	{
	};
	
	Point(int x, int y)
	{
		this->x = x;
		this->y = y;
	};
};

struct Node
{
	Point position;
	int data;

	Node() :position{}, data{ 0 }
	{
	};

	Node(Point p, int data)
	{
		this->position = p;
		this->data = data;
	}
};

class QuadTree
{
	//트리의 범위
	Point topLeft;
	Point bottomRight;

	//현재 노드
	Node* node;

	//하위 쿼드트리
	std::unique_ptr<QuadTree> nw;
	std::unique_ptr<QuadTree> ne;
	std::unique_ptr<QuadTree> sw;
	std::unique_ptr<QuadTree> se;

public:
	QuadTree();
	QuadTree(Point topLeft, Point bottomRight);
	void Insert(Node* node);
	Node* Search(Point pt);
	bool IsInBound(Point pt);
};


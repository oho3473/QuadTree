#include<iostream>
#include"QuadTree.h"

int main()
{
	QuadTree center1(Point(0, 0), Point(8, 8));
	
	std::unique_ptr<Node> a = std::make_unique<Node>(Point(1, 1), 1);
	std::unique_ptr<Node> b = std::make_unique<Node>(Point(2, 2), 2);
	std::unique_ptr<Node> c = std::make_unique<Node>(Point(3, 3), 3);
	std::unique_ptr<Node> d = std::make_unique<Node>(Point(4, 4),4);

	center1.Insert(a.get());
	center1.Insert(b.get());
	center1.Insert(c.get());
	center1.Insert(d.get());

	std::cout << "Node a : " << center1.Search(Point(1, 1))->data << std::endl;
	std::cout << "Node b : " << center1.Search(Point(2, 2))->data << std::endl;
	std::cout << "Node c : " << center1.Search(Point(3, 3))->data << std::endl;
	std::cout << "Node d : " << center1.Search(Point(4, 4))->data << std::endl;

	return 0;
}
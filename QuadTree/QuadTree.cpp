#include "QuadTree.h"
#include<cmath>

QuadTree::QuadTree() :
	topLeft{ Point() },
	bottomRight{ Point() },
	node{ nullptr },
	nw{ nullptr },
	ne{ nullptr },
	sw{ nullptr },
	se{nullptr}
{
}

QuadTree::QuadTree(Point topLeft, Point bottomRight) : QuadTree()
{
	this->topLeft = topLeft;
	this->bottomRight = bottomRight;
}

void QuadTree::Insert(Node* node)
{
	if (node == nullptr)
	{
		return;
	}

	//현재영역이 아니면 무시
	if (!IsInBound(node->position))
	{
		return;
	}

	//현재영역이 단위 영역 (1 * 1)이면 분할 불가능
	if (std::abs(topLeft.x - bottomRight.x) <= 1 &&
		std::abs(topLeft.y - bottomRight.y) <= 1)
	{
		if (this->node == nullptr)
		{
			this->node = node;
		}

		return;
	}

	//서쪽
	if ((topLeft.x + bottomRight.x) / 2 >= node->position.x)
	{
		if ((topLeft.y + bottomRight.y) / 2 >= node->position.y)
		{
			//북서
			if (nw == nullptr)
			{
				nw = std::make_unique<QuadTree>(Point(topLeft.x, topLeft.y),
					Point((topLeft.x + bottomRight.x) / 2, (topLeft.y + bottomRight.y) / 2));
			}
			nw->Insert(node);
		}
		else
		{
			//남서
			if (sw == nullptr)
			{
				sw = std::make_unique<QuadTree>(
					Point(topLeft.x, (topLeft.y + bottomRight.y) / 2),
					Point((topLeft.x + bottomRight.x) / 2, bottomRight.y)
					);
			}
			sw->Insert(node);
		}
	}
	//동쪽
	else
	{
		//북동
		if ((topLeft.y + bottomRight.y) / 2 >= node->position.y)
		{
			if (ne == nullptr)
			{
				ne = std::make_unique<QuadTree>(
					Point((topLeft.x + bottomRight.x) / 2, topLeft.y),
					Point(bottomRight.x, (topLeft.y + bottomRight.y)/2)
					);
			}
			ne->Insert(node);
		}
		else
		{
			//남동
			if (se == nullptr)
			{
				se = std::make_unique<QuadTree>(
					Point((topLeft.x + bottomRight.x) / 2, (topLeft.y + bottomRight.y) / 2),
					Point(bottomRight.x, bottomRight.y)
					);
			}
			se->Insert(node);
		}
	}
}

Node* QuadTree::Search(Point pt)
{
	//현재영역아니면무시
	if (!IsInBound(pt))
	{
		return nullptr;
	}

	//node 값이 있으면 더이상 분할불가능한 단위 영역
	if (node != nullptr)
	{
		return node;
	}

	//서쪽
	if ((topLeft.x + bottomRight.x) / 2 >= pt.x)
	{
		//북서
		if ((topLeft.y + bottomRight.y) / 2 >= pt.y)
		{
			if (nw == nullptr)
			{
				return nullptr;
			}
			return nw->Search(pt);
		}
		else
		{
			if (sw == nullptr)
			{
				return nullptr;
			}
			return sw->Search(pt);
		}
	}
	//동쪽
	else
	{
		//북동
		if ((topLeft.y + bottomRight.y) / 2 >= pt.y)
		{
			if (ne == nullptr)
			{
				return nullptr;
			}
			return ne->Search(pt);
		}
		else
		{
			if (se == nullptr)
			{
				return nullptr;
			}
			return se->Search(pt);
		}
	}
}

bool QuadTree::IsInBound(Point pt)
{
	return (pt.x >= topLeft.x && pt.x <= bottomRight.x 
		&& topLeft.y <= pt.y && bottomRight.y >= pt.y);
}

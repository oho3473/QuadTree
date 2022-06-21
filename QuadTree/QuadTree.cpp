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

	//���翵���� �ƴϸ� ����
	if (!IsInBound(node->position))
	{
		return;
	}

	//���翵���� ���� ���� (1 * 1)�̸� ���� �Ұ���
	if (std::abs(topLeft.x - bottomRight.x) <= 1 &&
		std::abs(topLeft.y - bottomRight.y) <= 1)
	{
		if (this->node == nullptr)
		{
			this->node = node;
		}

		return;
	}

	//����
	if ((topLeft.x + bottomRight.x) / 2 >= node->position.x)
	{
		if ((topLeft.y + bottomRight.y) / 2 >= node->position.y)
		{
			//�ϼ�
			if (nw == nullptr)
			{
				nw = std::make_unique<QuadTree>(Point(topLeft.x, topLeft.y),
					Point((topLeft.x + bottomRight.x) / 2, (topLeft.y + bottomRight.y) / 2));
			}
			nw->Insert(node);
		}
		else
		{
			//����
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
	//����
	else
	{
		//�ϵ�
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
			//����
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
	//���翵���ƴϸ鹫��
	if (!IsInBound(pt))
	{
		return nullptr;
	}

	//node ���� ������ ���̻� ���ҺҰ����� ���� ����
	if (node != nullptr)
	{
		return node;
	}

	//����
	if ((topLeft.x + bottomRight.x) / 2 >= pt.x)
	{
		//�ϼ�
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
	//����
	else
	{
		//�ϵ�
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

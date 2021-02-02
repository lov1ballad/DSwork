#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
typedef char BTDataType;

typedef struct BinaryTreeNode
{
	BTDataType _data;
	struct BinaryTreeNode* _left;
	struct BinaryTreeNode* _right;
}BTNode;

// 通过前序遍历的数组"ABD##E#H##CF##G##"构建二叉树
BTNode* BinaryTreeCreate(BTDataType* a, int n, int* pi);
// 二叉树销毁
void BinaryTreeDestory(BTNode** root);
// 二叉树节点个数
int BinaryTreeSize(BTNode* root);
// 二叉树叶子节点个数
int BinaryTreeLeafSize(BTNode* root);
// 二叉树第k层节点个数
int BinaryTreeLevelKSize(BTNode* root, int k);
// 二叉树查找值为x的节点
BTNode* BinaryTreeFind(BTNode* root, BTDataType x);
// 二叉树前序遍历 
void BinaryTreePrevOrder(BTNode* root);
// 二叉树中序遍历
void BinaryTreeInOrder(BTNode* root);
// 二叉树后序遍历
void BinaryTreePostOrder(BTNode* root);
// 层序遍历
void BinaryTreeLevelOrder(BTNode* root);
// 判断二叉树是否是完全二叉树
int BinaryTreeComplete(BTNode* root);


/////////////////////////////////////
BTNode *BinaryTreeCreate(BTDataType * a, int n, int* pi)
{
	if (a[*pi] == '#' || *pi >= n)
	{
		return NULL;
	}
	else
	{
		BTNode * s = (BTNode *)malloc(sizeof(BTNode));
		assert(s);
		s->_data = a[*pi];
		(*pi)++;
		s->_left = BinaryTreeCreate(a,n,pi);
		(*pi)++;
		s->_right = BinaryTreeCreate(a,n,pi);

		return s;
	}
}

void BinaryTreeDestory(BTNode** root)
{
	if (*root != NULL)
	{
		BinaryTreeDestory((*root)->_left);
		BinaryTreeDestory((*root)->_right);
		free(*root);
		*root = NULL;
	}
}

int BinaryTreeSize(BTNode* root)
{
	if (root == NULL)
		return 0;
	else
		return BinaryTreeSize(root->_left) + BinaryTreeSize(root->_right) + 1;
}

int BinaryTreeLeafSize(BTNode* root)
{
	if (root == NULL)
		return 0;
	if (root->_left == NULL && root->_right == NULL)
		return 1;

	return (BinaryTreeLeafSize(root->_left) + BinaryTreeLeafSize(root->_right));
}

int BinaryTreeLevelKSize(BTNode* root, int k)
{
	if (root == NULL || k<1) 
	{
		return 0;
	}
	if (k == 1) 
	{
		return 1;
	}
	return BinaryTreeLevelKSize(root->_left, k - 1) + BinaryTreeLevelKSize(root->_right, k - 1);
}

BTNode* BinaryTreeFind(BTNode* root, BTDataType x)
{
	BTNode* p;
	if (root == NULL || root->_data == x)
		return root;
	p = BinaryTreeFind(root->_left, x);
	if (p != NULL)
		return p;//左树找到
	return BinaryTreeFind(root->_right, x);
}

void BinaryTreePrevOrder(BTNode* root)
{
	if (root != NULL)
	{
		printf("%c ", root->_data);
		BinaryTreePrevOrder(root->_left);
		BinaryTreePrevOrder(root->_right);
	}
}

void BinaryTreeInOrder(BTNode* root)
{
	if (root != NULL)
	{
		BinaryTreeInOrder(root->_left);
		printf("%c ", root->_data);
		BinaryTreeInOrder(root->_right);
	}
}

void BinaryTreePostOrder(BTNode* root)
{
	if (root != NULL)
	{
		BinaryTreePostOrder(root->_left);
		BinaryTreePostOrder(root->_right);
		printf("%c ", root->_data);
	}
}

void BinaryTreeLevelOrder(BTNode* root)
{
	if (root != NULL)
	{
		LinkQueue Q;
		LinkQueueInit(&Q);

		LinkQueueEn(&Q, root);
		while (!LinkQueueIsEmpty(&Q))
		{
			BTNode* p = LinkQueuefront(&Q);
			LinkQueueDe(&Q);
			printf("%c ", p->_data);
			if (p->_left != NULL)
				LinkQueueEn(&Q, p->_left);
			if (p->_right != NULL)
				LinkQueueEn(&Q, p->_right);
		}
	}
}

int BinaryTreeComplete(BTNode* root)
{
	LinkQueue Q;
	BTNode * cur;
	int i = 0;

	LinkQueueInit(&Q);

	LinkQueuePush(&Q, root);

	while (!LinkQueueIsEmpty(&Q))
	{
		cur = LinkQueueTop(&Q);

		putchar(cur->_data);

		if (cur->_right && !cur->_left)
		{
			return 0;
		}

		if (i && (cur->_right || cur->_left))
		{
			return 0;
		}

		if (cur->_left)
		{
			LinkQueuePush(&Q, cur->_left);
		}

		if (cur->_right)
		{
			LinkQueuePush(&Q, cur->_right);
		}
		else
		{
			i = 1;
		}

		LinkQueuePop(&Q);
	}

	LinkQueueDestory(&Q);
	return 1;
}

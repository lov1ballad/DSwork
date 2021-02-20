#define _CRT_SECURE_NO_WARNINGS 1
//1、https://leetcode-cn.com/problems/binary-tree-preorder-traversal/ [二叉树的前序遍历]

Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};



/**
* Note: The returned array must be malloced, assume caller calls free().
*/
int size(struct TreeNode *t)
{
	if (t == NULL)
		return 0;
	else
		return size(t->left) + size(t->right) + 1;
}

void _preorderTraversal(struct TreeNode *root, int *preorder_array, int *i)
{
	if (root != NULL)
	{
		preorder_array[*i] = root->val;
		(*i)++;
		_preorderTraversal(root->left, preorder_array, i);
		_preorderTraversal(root->right, preorder_array, i);
	}
}

int* preorderTraversal(struct TreeNode* root, int* returnSize)
{
	int n = size(root); //
	int *preorder_array = (int*)malloc(sizeof(int)* n);
	*returnSize = n;

	// 遍历
	int index = 0;
	_preorderTraversal(root, preorder_array, &index);

	return preorder_array;
}

2、https://leetcode-cn.com/problems/binary-tree-inorder-traversal/ [二叉树的中序遍历]

/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     struct TreeNode *left;
*     struct TreeNode *right;
* };
*/


/**
* Note: The returned array must be malloced, assume caller calls free().
*/

int size(struct TreeNode *t)
{
	if (t == NULL)
		return 0;
	else
		return size(t->left) + size(t->right) + 1;
}

void _inorderTraversal(struct TreeNode *root, int *inorder_array, int *i)
{
	if (root != NULL)
	{
		_inorderTraversal(root->left, inorder_array, i);
		inorder_array[*i] = root->val;
		(*i)++;
		_inorderTraversal(root->right, inorder_array, i);
	}
}

int* inorderTraversal(struct TreeNode* root, int* returnSize)
{
	int n = size(root);
	int *inorder_array = (int*)malloc(sizeof(int)* n);
	*returnSize = n;

	int index = 0;
	_inorderTraversal(root, inorder_array, &index);
	return inorder_array;
}

3、https://leetcode-cn.com/problems/binary-tree-postorder-traversal/ [二叉树后序遍历]
/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     struct TreeNode *left;
*     struct TreeNode *right;
* };
*/


/**
* Note: The returned array must be malloced, assume caller calls free().
*/

int size(struct TreeNode *t)
{
	if (t == NULL)
		return 0;
	else
		return size(t->left) + size(t->right) + 1;
}

void _postorderTraversal(struct TreeNode *root, int *postorder_array, int *i)
{
	if (root != NULL)
	{
		_postorderTraversal(root->left, postorder_array, i);
		_postorderTraversal(root->right, postorder_array, i);

		postorder_array[*i] = root->val;
		(*i)++;
	}
}

int* postorderTraversal(struct TreeNode* root, int* returnSize)
{
	int n = size(root);
	int *postorder_array = (int*)malloc(sizeof(int)* n);
	*returnSize = n;

	int index = 0;
	_postorderTraversal(root, postorder_array, &index);
	return postorder_array;
}

4、https://leetcode-cn.com/problems/same-tree/ [相同的树]
/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     struct TreeNode *left;
*     struct TreeNode *right;
* };
*/


bool isSameTree(struct TreeNode* p, struct TreeNode* q)
{
	if (p == NULL && q == NULL)
		return true;
	if (p == NULL || q == NULL)
		return false;

	return p->val == q->val && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}

5、https://leetcode-cn.com/problems/subtree-of-another-tree/ [另一个树的子树]
/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     struct TreeNode *left;
*     struct TreeNode *right;
* };
*/

bool _isSametree(struct TreeNode *s, struct TreeNode *t)
{
	if (s == NULL && t == NULL)
		return true;
	if (s == NULL || t == NULL)
		return false;

	return s->val == t->val && _isSametree(s->left, t->left) && _isSametree(s->right, t->right);
}

bool isSubtree(struct TreeNode* s, struct TreeNode* t)
{
	if (t == NULL)
		return true;
	if (s == NULL)
		return false;

	if (_isSametree(s, t))
		return true;

	return isSubtree(s->left, t) || isSubtree(s->right, t);
}

6、https://leetcode-cn.com/problems/maximum-depth-of-binary-tree/ [二叉树的最大深度]
/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     struct TreeNode *left;
*     struct TreeNode *right;
* };
*/


int maxDepth(struct TreeNode* root)
{
	if (root == NULL)
		return 0;

	int left_h = maxDepth(root->left);
	int right_h = maxDepth(root->right);
	return (left_h>right_h ? left_h : right_h) + 1;
}

7、https://leetcode-cn.com/problems/balanced-binary-tree/ [平衡二叉树]
/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     struct TreeNode *left;
*     struct TreeNode *right;
* };
*/

int maxDepth(struct TreeNode* root)
{
	if (root == NULL)
		return 0;

	int left_h = maxDepth(root->left);
	int right_h = maxDepth(root->right);
	return (left_h>right_h ? left_h : right_h) + 1;
}

bool isBalanced(struct TreeNode* root)
{
	if (root == NULL)
		return true;

	int left_h = maxDepth(root->left);
	int right_h = maxDepth(root->right);

	return abs(left_h - right_h)<2 && isBalanced(root->left) && isBalanced(root->right);
}

8、https://leetcode-cn.com/problems/symmetric-tree/ [对称二叉树]
/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     struct TreeNode *left;
*     struct TreeNode *right;
* };
*/

bool _isSymmetric(struct TreeNode *t1, struct TreeNode *t2)
{
	if (t1 == NULL && t2 == NULL)
		return true;
	if (t1 == NULL || t2 == NULL)
		return false;

	return t1->val == t2->val && _isSymmetric(t1->left, t2->right) && _isSymmetric(t1->right, t2->left);
}

bool isSymmetric(struct TreeNode* root)
{
	if (root == NULL)
		return true;
	return _isSymmetric(root->left, root->right);
}

9、https://www.nowcoder.com/practice/4b91205483694f449f94c179883c1fef?tpId=60&&tqId=29483&rp=1&ru=/activity/oj&qru=/ta/tsing-kaoyan/question-ranking [二叉树的构建及遍历]
#include<stdio.h>
#include<assert.h>

typedef struct BinTreeNode
{
	char data;
	struct BinTreeNode *left;
	struct BinTreeNode *right;
}BinTreeNode;
typedef BinTreeNode* BinTree;

BinTree CreateBinTree(const char *str, int *i)
{
	if (str[*i] == '#' || str[*i] == '\0')
		return NULL;

	BinTreeNode *t = (BinTreeNode*)malloc(sizeof(BinTreeNode));
	assert(t != NULL);
	t->data = str[*i];

	(*i)++;
	t->left = CreateBinTree(str, i);

	(*i)++;
	t->right = CreateBinTree(str, i);

	return t;
}

void InOrder(BinTree t)
{
	if (t != NULL)
	{
		InOrder(t->left);
		printf("%c ", t->data);
		InOrder(t->right);
	}
}

void DestroyBinTree(BinTree *t)
{
	if (*t != NULL)
	{
		DestroyBinTree(&((*t)->left));
		DestroyBinTree(&((*t)->right));
		free(*t);
		*t = NULL;
	}
}

int main()
{
	BinTree bt = NULL;
	char ar[100] = { 0 };
	while (scanf("%s", ar) != EOF)
	{
		int index = 0;
		bt = CreateBinTree(ar, &index);
		InOrder(bt);
		printf("\n");
		DestroyBinTree(&bt);
	}
	return 0;
}

#define _CRT_SECURE_NO_WARNINGS 1
1、https://leetcode-cn.com/problems/construct-string-from-binary-tree/ [根据二叉树创建字符串]
/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     struct TreeNode *left;
*     struct TreeNode *right;
* };
*/

void _tree2str(struct TreeNode *t, char *str)
{
	if (t == NULL)
		return;

	char buf[10] = { 0 };
	sprintf(buf, "%d", t->val);
	strcat(str, buf);  //str="1"

	if (t->left == NULL)
	{
		if (t->right == NULL)
			return;
		else
			strcat(str, "()");
	}
	else
	{
		strcat(str, "(");
		_tree2str(t->left, str);
		strcat(str, ")");
	}

	if (t->right == NULL)
		return;
	else
	{
		strcat(str, "(");
		_tree2str(t->right, str);
		strcat(str, ")");
	}
}

char * tree2str(struct TreeNode* t)
{
	int n = 100000;
	char *str = (char*)malloc(sizeof(char)* n);
	//str[0] = '\0';
	memset(str, 0, n);

	_tree2str(t, str);

	return str;
}

2、https://leetcode-cn.com/problems/binary-tree-level-order-traversal/ [二叉树的层序遍历]
/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     struct TreeNode *left;
*     struct TreeNode *right;
* };
*/


/**
* Return an array of arrays of size *returnSize.
* The sizes of the arrays are returned as *returnColumnSizes array.
* Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
*/

int maxDepth(struct TreeNode* root)
{
	if (root == NULL)
		return 0;

	int left_h = maxDepth(root->left);
	int right_h = maxDepth(root->right);
	return (left_h>right_h ? left_h : right_h) + 1;
}

int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes)
{
	if (root == NULL)
	{
		*returnSize = 0;
		return NULL;
	}

	int max_level = maxDepth(root);
	*returnSize = max_level;
	int **levelOrder = (int**)malloc(sizeof(int*)* max_level);
	*returnColumnSizes = (int *)malloc(sizeof(int)* max_level);

	//层次遍历
	struct TreeNode *q1[1000], *q2[1000];  //队列
	int q1_size = 0, q2_size = 0;

	q1[0] = root;
	q1_size++;

	int level = 0;
	while (level < max_level)
	{
		levelOrder[level] = (int*)malloc(sizeof(int)* q1_size);
		for (int i = 0; i<q1_size; ++i)
			levelOrder[level][i] = q1[i]->val;
		(*returnColumnSizes)[level] = q1_size;

		for (int i = 0; i<q1_size; ++i)
		{
			if (q1[i]->left != NULL)
				q2[q2_size++] = q1[i]->left;
			if (q1[i]->right != NULL)
				q2[q2_size++] = q1[i]->right;
		}

		memcpy(q1, q2, sizeof(struct TreeNode*) * q2_size);
		q1_size = q2_size;
		q2_size = 0;

		level++;
	}

	return levelOrder;
}

3、https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree/ [二叉树的最近公共祖先]
/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     struct TreeNode *left;
*     struct TreeNode *right;
* };
*/

bool findNode(struct TreeNode *root, struct TreeNode *n)
{
	if (root == NULL)
		return false;
	if (root == n)
		return true;
	return findNode(root->left, n) || findNode(root->right, n);
}

struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q)
{
	if (root == NULL)
		return NULL;
	if (p == root || q == root)
		return root;

	bool pInleft, pInright, qInleft, qInright;
	if (findNode(root->left, p))
	{
		pInleft = true;
		pInright = false;
	}
	else
	{
		pInleft = false;
		pInright = true;
	}

	if (findNode(root->left, q))
	{
		qInleft = true;
		qInright = false;
	}
	else
	{
		qInleft = false;
		qInright = true;
	}

	if (pInleft && qInleft)
		return lowestCommonAncestor(root->left, p, q);
	if (pInright && qInright)
		return lowestCommonAncestor(root->right, p, q);

	return root;
}


4、https://www.nowcoder.com/practice/947f6eb80d944a84850b0538bf0ec3a5?tpId=13&&tqId=11179&rp=1&ru=/activity/oj&qru=/ta/coding-interviews/question-ranking [二叉树搜索树转换成排序双向链表]
/**
* struct TreeNode {
*	int val;
*	struct TreeNode *left;
*	struct TreeNode *right;
* };
*/

/**
*
* @param pRootOfTree TreeNode类
* @return TreeNode类
*/

void ConvertList(struct TreeNode *t, struct TreeNode **pre)
{
	if (t == NULL)
		return;
	ConvertList(t->left, pre);
	t->left = *pre;
	if (*pre != NULL)
		(*pre)->right = t;
	*pre = t;
	ConvertList(t->right, pre);
}

struct TreeNode* Convert(struct TreeNode* pRootOfTree)
{
	// write code here
	if (pRootOfTree == NULL)
		return NULL;

	struct TreeNode *pre = NULL;

	ConvertList(pRootOfTree, &pre);

	struct TreeNode *pHead = pre;
	while (pHead->left != NULL)
		pHead = pHead->left;

	return pHead;
}


5、https://leetcode-cn.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/ [根据一棵树的前序遍历与中序遍历构造二叉树]
/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     struct TreeNode *left;
*     struct TreeNode *right;
* };
*/


struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize)
{
	if (preorderSize == 0)
		return NULL;

	int k = 0;
	while (inorder[k] != preorder[0])
		k++;

	struct TreeNode *t = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	t->val = inorder[k];

	t->left = buildTree(preorder + 1, k, inorder, k);
	t->right = buildTree(preorder + k + 1, preorderSize - k - 1, inorder + k + 1, preorderSize - k - 1);
	return t;
}
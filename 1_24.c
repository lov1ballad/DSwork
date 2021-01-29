#define _CRT_SECURE_NO_WARNINGS 1
先序遍历void BTreePrevOrder(BTNode* root)
{
	if (root == NULL)
		return;
	printf("%d ", root->_data);
	BTreePrevOrder(root->_left);
	BTreePrevOrder(root->_right);
}
中序遍历void BTreeInOrder(BTNode* root)
{
	if (root == NULL)
		return;
	BTreeInOrder(root->_left);
	printf("%d ", root->_data);
	BTreeInOrder(root->_right);
}

后序遍历
void BTreePostOrder(BTNode* root)
{
	if (root == NULL)
	{
		return;
	}
	BTreePostOrder(root->_left);
	BTreePostOrder(root->_right);
	printf("%d ", root->_data);
}
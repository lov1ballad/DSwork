#define _CRT_SECURE_NO_WARNINGS 1
�������void BTreePrevOrder(BTNode* root)
{
	if (root == NULL)
		return;
	printf("%d ", root->_data);
	BTreePrevOrder(root->_left);
	BTreePrevOrder(root->_right);
}
�������void BTreeInOrder(BTNode* root)
{
	if (root == NULL)
		return;
	BTreeInOrder(root->_left);
	printf("%d ", root->_data);
	BTreeInOrder(root->_right);
}

�������
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
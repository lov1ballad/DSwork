#define _CRT_SECURE_NO_WARNINGS 1
//根据前序序列和中序序列来创建二叉树
/*char* vlr = "ABCDEFGH";
char* lvr = "CBEDFAGH";
char* lrv = "CEFDBHGA";
int n = strlen(vlr);
bt = BinTreeCreate_VLR_LVR(vlr, lvr, n)*/
BinTree BinTreeCreate_VLR_LVR(const char *vlr, const char* lvr, int n)
{
	if (n == 0)
		return NULL;
	int k = 0;
	while (lvr[k] != vlr[0])
		k++;
	BinTreeNode* t = (BinTreeNode*)malloc(sizeof(BinTreeNode));
	assert(t);
	t->data = lvr[k];

	t->leftChild = BinTreeCreate_VLR_LVR(vlr + 1, lvr, k);
	t->rightChild = BinTreeCreate_VLR_LVR(vlr + k + 1, lvr + k + 1, n - k - 1);

	return t;
}

//根据前序序列和中序序列来创建二叉树
BinTree BinTreeCreate_LVR_LRV(const char* lvr, const char* lrv, int n)
{
	if (n == 0)
		return NULL;
	int k = 0;
	while (lvr[k] != lrv[n - 1])
		k++;
	BinTreeNode* t = (BinTreeNode*)malloc(sizeof(BinTreeNode));
	assert(t);
	t->data = lvr[k];
	t->rightChild = BinTreeCreate_LVR_LRV(lvr + k + 1, lrv + k, n - k - 1);
	t->leftChild = BinTreeCreate_LVR_LRV(lvr, lrv, k);
	return t;
}

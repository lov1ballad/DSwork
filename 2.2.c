#define _CRT_SECURE_NO_WARNINGS 1
typedef int HPDataType;
typedef struct Heap
{
	HPDataType* _a;
	int _size;
	int _capacity;
}Heap;

// 堆的构建
void HeapCreate(Heap* hp, HPDataType* a, int n);
// 堆的销毁
void HeapDestory(Heap* hp);
// 堆的插入
void HeapPush(Heap* hp, HPDataType x);
// 堆的删除
void HeapPop(Heap* hp);
// 取堆顶的数据
HPDataType HeapTop(Heap* hp);
// 堆的数据个数
int HeapSize(Heap* hp);
// 堆的判空
int HeapEmpty(Heap* hp);

// 对数组进行堆排序
void HeapSort(int* a, int n);

// TopK问题：找出N个数里面最大/最小的前K个问题。
// 比如：未央区排名前10的泡馍，西安交通大学王者荣耀排名前10的韩信，全国排名前10的李白。等等问题都是Topk问题，
// 需要注意：
// 找最大的前K个，建立K个数的小堆
// 找最小的前K个，建立K个数的大堆
void PrintTopK(int* a, int n, int k);
void TestTopk();




#include "Heap.h"

void Swap(HPDataType* x1, HPDataType* x2)
{
	HPDataType x = *x1;
	*x1 = *x2;
	*x2 = x;
}

void AdjustDown(HPDataType* a, int n, int root)
{
	int parent = root;
	int child = parent * 2 + 1;
	while (child < n)
	{
		// 选左右孩纸中大的一个
		if (child + 1 < n
			&& a[child + 1] > a[child])
		{
			++child;
		}

		//如果孩子大于父亲，进行调整交换 
		if (a[child] > a[parent])
		{
			Swap(&a[child], &a[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

void AdjustUp(HPDataType* a, int n, int child)
{
	int parent;
	assert(a);
	parent = (child - 1) / 2;
	//while (parent >= 0)
	while (child > 0)
	{
		//如果孩子大于父亲，进行交换
		if (a[child] > a[parent])
		{
			Swap(&a[parent], &a[child]);
			child = parent;
			parent = (child - 1) / 2;
		}
		else
		{
			break;
		}
	}
}

void HeapInit(Heap* hp, HPDataType* a, int n)
{
	int i;
	assert(hp && a);
	hp->_a = (HPDataType*)malloc(sizeof(HPDataType)*n);
	hp->_size = n;
	hp->_capacity = n;

	for (i = 0; i < n; ++i)
	{
		hp->_a[i] = a[i];
	}

	// 建堆： 从最后一个非叶子节点开始进行调整
	// 最后一个非叶子节点，按照规则： （最后一个位置索引 - 1） / 2
	// 最后一个位置索引： n - 1
	// 故最后一个非叶子节点位置： (n - 2) / 2
	for (i = (n - 2) / 2; i >= 0; --i)
	{
		AdjustDown(hp->_a, hp->_size, i);
	}
}

void HeapDestory(Heap* hp)
{
	assert(hp);

	free(hp->_a);
	hp->_a = NULL;
	hp->_size = hp->_capacity = 0;
}

void HeapPush(Heap* hp, HPDataType x)
{
	assert(hp);
	//检查容量
	if (hp->_size == hp->_capacity)
	{
		hp->_capacity *= 2;
		hp->_a = (HPDataType*)realloc(hp->_a, sizeof(HPDataType)*hp->_capacity);
	}
	//尾插
	hp->_a[hp->_size] = x;
	hp->_size++;
	//向上调整
	AdjustUp(hp->_a, hp->_size, hp->_size - 1);
}

void HeapPop(Heap* hp)
{
	assert(hp);
	//交换
	Swap(&hp->_a[0], &hp->_a[hp->_size - 1]);
	hp->_size--;
	//向下调整
	AdjustDown(hp->_a, hp->_size, 0);
}

HPDataType HeapTop(Heap* hp)
{
	assert(hp);
	return hp->_a[0];
}

int HeapSize(Heap* hp)
{
	return hp->_size;
}

int HeapEmpty(Heap* hp)
{
	return hp->_size == 0 ? 0 : 1;
}

void HeapPrint(Heap* hp)
{
	int i;
	for (i = 0; i < hp->_size; ++i)
	{
		printf("%d ", hp->_a[i]);
	}
	printf("\n");
}

// 升序
void HeapSort(HPDataType* a, int n)
{
	// 排升序需要建大堆：
	// 因为每次都会把堆顶元素拿出来放到当前堆的最后一个位置
	// 相当于每次都会把剩余元素中的最大值（即堆顶元素）找出来
	// 放到它该有的位置（当前堆的最后一个位置）
	int i, end;
	for (i = (n - 2) / 2; i >= 0; --i)
	{
		AdjustDown(a, n, i);
	}

	// 
	end = n - 1;
	while (end > 0)
	{
		Swap(&a[0], &a[end]);
		// 调堆，选次大的数
		AdjustDown(a, end, 0);

		--end;
	}
}

//TopK问题： 找出N个数里面最大/最小的前K个问题。
//这里实现两个版本：
//1. 找最大的K个元素
//假设堆为小堆
void PrintTopK(int* a, int n, int k)
{
	Heap hp;
	//建立含有K个元素的堆
	HeapInit(&hp, a, k);

	for (size_t i = k; i < n; ++i)  // N
	{
		//每次和堆顶元素比较，大于堆顶元素，则删除堆顶元素，插入新的元素
		if (a[i] > HeapTop(&hp)) // LogK
		{
			HeapPop(&hp);
			HeapPush(&hp, a[i]);
		}
	}
	for (int i = 0; i < k; ++i){
		printf("%d ", HeapTop(&hp));
		HeapPop(&hp);
	}
}

//2. 找最小的K个元素
//假设堆为大堆
void PrintTopK(int* a, int n, int k)
{
	Heap hp;
	//建立含有K个元素的堆
	HeapInit(&hp, a, k);

	for (size_t i = k; i < n; ++i)  // N
	{
		//每次和堆顶元素比较，小于堆顶元素，则删除堆顶元素，插入新的元素
		if (a[i] < HeapTop(&hp)) // LogK
		{
			HeapPop(&hp);
			HeapPush(&hp, a[i]);
		}
	}
	for (int i = 0; i < k; ++i){
		printf("%d ", HeapTop(&hp));
		HeapPop(&hp);
	}
}
void TestTopk()
{
	int n = 10000;
	int* a = (int*)malloc(sizeof(int)*n);
	srand(time(0));
	//随机生成10000个数存入数组，保证元素都小于1000000
	for (size_t i = 0; i < n; ++i)
	{
		a[i] = rand() % 1000000;
	}
	//确定10个最大的数
	a[5] = 1000000 + 1;
	a[1231] = 1000000 + 2;
	a[531] = 1000000 + 3;
	a[5121] = 1000000 + 4;
	a[115] = 1000000 + 5;
	a[2335] = 1000000 + 6;
	a[9999] = 1000000 + 7;
	a[76] = 1000000 + 8;
	a[423] = 1000000 + 9;
	a[3144] = 1000000 + 10;

	PrintTopK(int* a, n, 10);
}
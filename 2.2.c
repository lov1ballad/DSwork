#define _CRT_SECURE_NO_WARNINGS 1
typedef int HPDataType;
typedef struct Heap
{
	HPDataType* _a;
	int _size;
	int _capacity;
}Heap;

// �ѵĹ���
void HeapCreate(Heap* hp, HPDataType* a, int n);
// �ѵ�����
void HeapDestory(Heap* hp);
// �ѵĲ���
void HeapPush(Heap* hp, HPDataType x);
// �ѵ�ɾ��
void HeapPop(Heap* hp);
// ȡ�Ѷ�������
HPDataType HeapTop(Heap* hp);
// �ѵ����ݸ���
int HeapSize(Heap* hp);
// �ѵ��п�
int HeapEmpty(Heap* hp);

// ��������ж�����
void HeapSort(int* a, int n);

// TopK���⣺�ҳ�N�����������/��С��ǰK�����⡣
// ���磺δ��������ǰ10�����ɣ�������ͨ��ѧ������ҫ����ǰ10�ĺ��ţ�ȫ������ǰ10����ס��ȵ����ⶼ��Topk���⣬
// ��Ҫע�⣺
// ������ǰK��������K������С��
// ����С��ǰK��������K�����Ĵ��
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
		// ѡ���Һ�ֽ�д��һ��
		if (child + 1 < n
			&& a[child + 1] > a[child])
		{
			++child;
		}

		//������Ӵ��ڸ��ף����е������� 
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
		//������Ӵ��ڸ��ף����н���
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

	// ���ѣ� �����һ����Ҷ�ӽڵ㿪ʼ���е���
	// ���һ����Ҷ�ӽڵ㣬���չ��� �����һ��λ������ - 1�� / 2
	// ���һ��λ�������� n - 1
	// �����һ����Ҷ�ӽڵ�λ�ã� (n - 2) / 2
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
	//�������
	if (hp->_size == hp->_capacity)
	{
		hp->_capacity *= 2;
		hp->_a = (HPDataType*)realloc(hp->_a, sizeof(HPDataType)*hp->_capacity);
	}
	//β��
	hp->_a[hp->_size] = x;
	hp->_size++;
	//���ϵ���
	AdjustUp(hp->_a, hp->_size, hp->_size - 1);
}

void HeapPop(Heap* hp)
{
	assert(hp);
	//����
	Swap(&hp->_a[0], &hp->_a[hp->_size - 1]);
	hp->_size--;
	//���µ���
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

// ����
void HeapSort(HPDataType* a, int n)
{
	// ��������Ҫ����ѣ�
	// ��Ϊÿ�ζ���ѶѶ�Ԫ���ó����ŵ���ǰ�ѵ����һ��λ��
	// �൱��ÿ�ζ����ʣ��Ԫ���е����ֵ�����Ѷ�Ԫ�أ��ҳ���
	// �ŵ������е�λ�ã���ǰ�ѵ����һ��λ�ã�
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
		// ���ѣ�ѡ�δ����
		AdjustDown(a, end, 0);

		--end;
	}
}

//TopK���⣺ �ҳ�N�����������/��С��ǰK�����⡣
//����ʵ�������汾��
//1. ������K��Ԫ��
//�����ΪС��
void PrintTopK(int* a, int n, int k)
{
	Heap hp;
	//��������K��Ԫ�صĶ�
	HeapInit(&hp, a, k);

	for (size_t i = k; i < n; ++i)  // N
	{
		//ÿ�κͶѶ�Ԫ�رȽϣ����ڶѶ�Ԫ�أ���ɾ���Ѷ�Ԫ�أ������µ�Ԫ��
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

//2. ����С��K��Ԫ��
//�����Ϊ���
void PrintTopK(int* a, int n, int k)
{
	Heap hp;
	//��������K��Ԫ�صĶ�
	HeapInit(&hp, a, k);

	for (size_t i = k; i < n; ++i)  // N
	{
		//ÿ�κͶѶ�Ԫ�رȽϣ�С�ڶѶ�Ԫ�أ���ɾ���Ѷ�Ԫ�أ������µ�Ԫ��
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
	//�������10000�����������飬��֤Ԫ�ض�С��1000000
	for (size_t i = 0; i < n; ++i)
	{
		a[i] = rand() % 1000000;
	}
	//ȷ��10��������
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
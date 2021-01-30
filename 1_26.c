#define _CRT_SECURE_NO_WARNINGS 1
//7.˫������ɾ���
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include<stdbool.h>
typedef int LTDataType;
typedef struct ListNode
{
	LTDataType data;
	struct ListNode* next;
	struct ListNode* prev;
}ListNode;

ListNode* _BuyNode(LTDataType x)
{
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	node->data = x;
	node->next = node->prev = NULL;
	return node;
}
// �������������ͷ���.
ListNode* ListCreate()
{
	ListNode* head = (ListNode*)malloc(sizeof(ListNode));
	head->next = head->prev = head;
	return head;
}
// ˫����������
void ListDestroy(ListNode* pHead)
{
	ListNode* cur = pHead->next;
	while (cur != pHead)//����ΪNULL
	{
		ListNode* next = cur->next;
		free(cur);
		cur = next;
	}
	free(pHead);
}
// ˫�������ӡ
void ListPrint(ListNode* pHead)
{
	assert(pHead);
	ListNode* cur = pHead->next;
	while (cur != pHead)
	{
		printf("%d->", cur->data);
		cur = cur->next;
	}
	printf("NIl\n");
}
// ˫������β��
void ListPushBack(ListNode* pHead, LTDataType x)
{
	assert(pHead);
	ListNode* newnode = _BuyNode(x);
	ListNode* tail = pHead->prev;
	tail->next = newnode;
	newnode->prev = tail;

	newnode->next = pHead;
	pHead->prev = newnode;
}
// ˫������ͷ��
void ListPushFront(ListNode* pHead, LTDataType x)
{
	assert(pHead);
	ListNode* newNode = _BuyNode(x);
	newNode->next = pHead->next;
	pHead->next->prev = newNode;

	pHead->next = newNode;
	newNode->prev = pHead;
}
// ˫������βɾ
void ListPopBack(ListNode* pHead)
{
	assert(pHead);
	ListNode* tail = pHead->prev;
	pHead->prev = tail->prev;
	tail->prev->next = pHead;
	free(tail);
}
// ˫������ͷɾ
void ListPopFront(ListNode* pHead)
{
	ListNode* first = pHead->next;
	pHead->next = first->next;
	first->next->prev = pHead;
	ListErase(pHead->next);
}
// ˫���������
ListNode* ListFind(ListNode* pHead, LTDataType x)
{
	ListNode* head = pHead;
	if (head == NULL)
	{
		return NULL;
	}
	while (head->next != NULL && head->data != x)
	{
		head = head->next;
	}
	if (head->next == NULL)
	{
		return NULL;
	}
	return head;
}
// ˫��������pos��ǰ����в���
void ListInsert(ListNode* pos, LTDataType x)
{
	assert(pos);
	ListNode* prev = pos->prev;
	ListNode* newnode = _BuyNode(x);
	prev->next = newnode;
	newnode->prev = prev;

	newnode->next = pos;
	pos->prev = newnode;
}
// ˫������ɾ��posλ�õĽڵ�
void ListErase(ListNode* pos)
{
	assert(pos);

	ListNode* prev = pos->prev;
	ListNode* next = pos->next;

	prev->next = next;
	next->prev = prev;
	free(pos);
}

//2.���ƴ����ָ�������
//https://leetcode-cn.com/problems/copy-list-with-random-pointer/description/
/*
*/


//3.����һ��������������ʼ�뻷�ĵ�һ���ڵ㡣 ��������޻����򷵻� NULL
//https://leetcode-cn.com/problems/linked-list-cycle-ii/description/
/*
Definition for singly-linked list.
struct ListNode {
    int val;
    struct ListNode *next;
};
struct ListNode *detectCycle(struct ListNode *head)
{
	if (head == NULL)
		return NULL;
	struct ListNode* fast, *slow;
	fast = slow = head;
	while (fast && fast->next != NULL)
	{
		fast = fast->next->next;
		slow = slow->next;
		if (fast == slow)
			break;

	}
	if (fast == NULL || fast->next == NULL)
		return NULL;
	fast = head;
	while (fast != slow)
	{
		fast = fast->next;
		slow = slow->next;
	}
	return fast;
}*/



//4.����һ�������ж��������Ƿ��л�
//https://leetcode-cn.com/problems/linked-list-cycle/description/
/*
Definition for singly-linked list.
struct ListNode {
    int val;
    struct ListNode *next;
};
bool hasCycle(struct ListNode *head)
{
	if (head == NULL)
		return false;
	struct ListNode* fast, *slow;
	fast = slow = head;
	while (fast && fast->next != NULL)
	{
		fast = fast->next->next;
		slow = slow->next;
		if (fast == slow)
			return true;
	}
	return false;
}*/

//5.�������������ҳ����ǵĵ�һ���������(������)
//https://leetcode-cn.com/problems/intersection-of-two-linked-lists/description/
/*
Definition for singly-linked list.
struct ListNode 
{
     int val;
     struct ListNode *next;
};
int GetLengthOfList(struct ListNode* head)
{
	int len = 0;
	while (head != NULL)
	{
		len++;
		head = head->next;
	}
	return len;
}
struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB)
{
	if (headA == NULL || headB == NULL)
		return NULL;
	int lenA = GetLengthOfList(headA);
	int lenB = GetLengthOfList(headB);
	struct ListNode* longList, *shortList;
	if (lenA > lenB)
	{
		longList = headA;
		shortList = headB;
	}
	else
	{
		longList = headB;
		shortList = headA;
	}
	int offset = abs(lenA - lenB);
	while (offset-->0)
		longList = longList->next;
	while (longList != NULL)
	{
		if (shortList == longList)
			return longList;
		shortList = shortList->next;
		longList = longList->next;
	}
	return NULL;
}
*/

//6.����Ļ��Ľṹ
//https://www.nowcoder.com/practice/d281619e4b3e4a60a2cc66ea32855bfa?tpId=49&&tqId=29370&rp=1&ru=/activity/oj&qru=/ta/2016test/question-ranking
/*
struct ListNode {
int val;
struct ListNode *next;
ListNode(int x) : val(x), next(NULL) {}
};
bool chkPalindrome(ListNode* A)
	{
		ListNode* fast = A;
		ListNode* slow = A;
		while (fast && fast->next) {
			slow = slow->next;
			fast = fast->next->next;
		}
		ListNode* p = slow->next;
		ListNode* q = p->next;
		p->next = NULL;
		while (q != NULL) {
			p = q->next;
			q->next = slow->next;
			slow->next = q;
			q = p;
		}
		p = A;
		q = slow->next;    //����������ż��
		while (q)
		{
			if (p->val != q->val) return false;
			p = p->next;
			q = q->next;
		}
		return true;
	}
*/

//7.��д���룬�Ը���ֵxΪ��׼������ָ�������֣�����С��x�Ľ�����ڴ��ڻ����x�Ľ��֮ǰ
//https://www.nowcoder.com/practice/0e27e0b064de4eacac178676ef9c9d70?tpId=8&&tqId=11004&rp=2&ru=/activity/oj&qru=/ta/cracking-the-coding-interview/question-ranking
/*
struct ListNode {
int val;
struct ListNode *next;
ListNode(int x) : val(x), next(NULL) {}
};*/
/*
	ListNode* partition(ListNode* pHead, int x)
	{//�ָ�
		if (pHead == NULL)
			return NULL;
		ListNode* less, *lessTail, *great, *greatTail;
		less = lessTail = (ListNode*)malloc(sizeof(ListNode));
		great = greatTail = (ListNode*)malloc(sizeof(ListNode));
		while (pHead != NULL)
		{
			if (pHead->val < x)
			{
				lessTail->next = pHead;
				lessTail = lessTail->next;
				pHead = pHead->next;
			}
			else
			{
				greatTail->next = pHead;
				greatTail = greatTail->next;
				pHead = pHead->next;
			}
		}
		//�ϲ�
		lessTail->next = great->next;
		greatTail->next = NULL;
		pHead = less->next;
		free(less);
		free(great);
		return pHead;
	}
*/
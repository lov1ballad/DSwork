#define _CRT_SECURE_NO_WARNINGS 1
//1.删除链表中等于给定值 val 的所有节点.https://leetcode-cn.com/problems/remove-linked-list-elements/submissions/
/**
* Definition for singly-linked list.
* struct ListNode {
*     int val;
*     struct ListNode *next;
* };
*/
/*struct ListNode* removeElements(struct ListNode* head, int val)
{
	if (head == NULL)
		return NULL;
	struct ListNode* p = head;
	struct ListNode* pre = NULL;
	while (p != NULL)
	{
		if (p->val == val)
		{
			if (pre == NULL)
			{
				head = p->next;
			}
			else
			{
				pre->next = p->next;
				free(p);
			}
		}
		else
			pre = p;
		if (pre == NULL)
			p = head;
		else
			p = pre->next;
	}
	return head;
}*/

2.
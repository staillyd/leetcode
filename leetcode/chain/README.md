# 链表
## [两数相加](2.py)
- [Link](https://leetcode-cn.com/problems/add-two-numbers/)
- 给你两个 非空 的链表，表示两个非负的整数。它们每位数字都是按照 逆序 的方式存储的，并且每个节点只能存储 一位 数字。
- 请你将两个数相加，并以相同形式返回一个表示和的链表。
- 你可以假设除了数字 0 之外，这两个数都不会以 0 开头。
```python
def addTwoNumbers(self, l1: ListNode, l2: ListNode) -> ListNode:
    '''两数相加'''
    ret=ListNode()
    last=ret#上一节点
    add=0#进位
    while l1 or l2 or add!=0:#在l1 l2 都为None并且进位(add)为0时退出, add不为0应对999+9999这种情况
        sum=(0 if l1 is None else l1.val)+(0 if l2 is None else l2.val)+add
        add,sum=divmod(sum,10)#整除与余数

        last.next=ListNode(sum)
        last=last.next#挪位

        l1=None if l1 is None else l1.next#挪位
        l2=None if l2 is None else l2.next#挪位
    return ret.next#舍弃初始的节点
```

## [两数相加II](445.py)
- [Link](https://leetcode-cn.com/problems/add-two-numbers-ii/)
- 给你两个 非空 链表来代表两个非负整数。数字最高位位于链表开始位置。它们的每个节点只存储一位数字。将这两数相加会返回一个新的链表。
- 你可以假设除了数字 0 之外，这两个数字都不会以零开头。
```python
def addTwoNumbers(self, l1: ListNode, l2: ListNode) -> ListNode:
        '''两数之和II,高位指向低位'''
        reverse_l1=[]#stack
        while l1 is not None:
            reverse_l1.append(l1.val)
            l1=l1.next
        
        reverse_l2=[]#stack
        while l2 is not None:
            reverse_l2.append(l2.val)
            l2=l2.next

        last=None
        add=0
        while len(reverse_l1)!=0 or len(reverse_l2)!=0 or add!=0:
            sum=(0 if len(reverse_l1)==0 else reverse_l1.pop()) + \
                (0 if len(reverse_l2)==0 else reverse_l2.pop()) + add# stack进行顺序翻转

            add,sum=divmod(sum,10)

            ret=ListNode(sum,last)
            last=ret
        return ret
```

## [从尾到头打印链表](6.py)
- [Link](https://leetcode-cn.com/problems/cong-wei-dao-tou-da-yin-lian-biao-lcof/)
- 输入一个链表的头节点，从尾到头反过来返回每个节点的值（用数组返回）
```python
def reversePrint(self, head: ListNode) -> List[int]:
    '''从尾到头打印链表'''
    ret=[]
    while head is not None:
        ret.append(head.val)
        head=head.next
    return ret[::-1]
```

## [删除链表中的节点](237.py)
- [Link](https://leetcode-cn.com/problems/delete-node-in-a-linked-list/)
- 请编写一个函数，使其可以删除某个链表中给定的（非末尾）节点。传入函数的唯一参数为 要被删除的节点 。
```python
def deleteNode(self, node):
    """删除传入的node节点"""
    node.val=node.next.val
    node.next=node.next.next
```

## [删除排序链表中的重复值](83.py)
- [Link](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list/)
- 存在一个按升序排列的链表，给你这个链表的头节点 head ，请你删除所有重复的元素，使每个元素 只出现一次 。
- 返回同样按升序排列的结果链表。
```python
def deleteDuplicates(self, head: ListNode) -> ListNode:
    '''删除排序链表中的重复值'''
    ret=head
    while head is not None:
        if head.next is not None and head.val==head.next.val:
            head.next=head.next.next
        else:
            head=head.next
    return ret
```

## [删除排序链表中的重复元素 II](82.py)
- [Link](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list-ii/)
- 存在一个按升序排列的链表，给你这个链表的头节点 head ，请你删除链表中所有存在数字重复情况的节点，只保留原始链表中 **没有重复出现** 的数字。
- 返回同样按升序排列的结果链表。
```python
def deleteDuplicates(self, head: ListNode) -> ListNode:
    '''删除排序链表中的重复元素 II'''
    ret=ListNode()
    last=ret
    while head is not None:
        flag=False#当前位置是否删除了相同节点
        while head.next is not None and head.val==head.next.val:#删除相同的节点
            head.next=head.next.next
            flag=True
        if flag:
            head=head.next
            last.next=head
        else:
            last.next=head
            last=last.next#挪位，只有此处进行last的挪位
            head=head.next
    return ret.next
```

## [移除链表元素](203.py)
- [Link](https://leetcode-cn.com/problems/remove-linked-list-elements/)
- 给你一个链表的头节点 head 和一个整数 val ，请你删除链表中所有满足 Node.val == val 的节点，并返回 新的头节点 。
- 链表移除元素
  - ```python
        if flag:
            head=head.next#旧挪位
            last.next=head#新指向
        else:
            last.next=head#新指向
            last=last.next#新挪位，只有此处进行last的挪位
            head=head.next#旧挪位
    ```
```python
def removeElements(self, head: ListNode, val: int) -> ListNode:
    '''移除链表元素'''
    ret=ListNode()
    last=ret
    while head is not None:
        if head.val==val:#满足删除条件
            head=head.next
            last.next=head#指向
        else:
            last.next=head
            last=last.next#挪位
            head=head.next
    return ret.next
```

## [返回倒数第 k 个节点]
- [Link](https://leetcode-cn.com/problems/kth-node-from-end-of-list-lcci/)
- 实现一种算法，找出单向链表中倒数第 k 个节点。返回该节点的值。
```python
def kthToLast(self, head: ListNode, k: int) -> int:
    '''返回倒数第 k 个节点
    
    @Note:
        p,q都指向head,p先走k步,然后pq都往前走,直到p为None
        快慢指针
    '''
    p,q=head,head
    for i in range(k):
        p=p.next
    while p is not None:
        p=p.next
        q=q.next
    return q.val
```

## [两两交换链表中的节点](24.py)
- [Link](https://leetcode-cn.com/problems/swap-nodes-in-pairs/)
- 给定一个链表，两两交换其中相邻的节点，并返回交换后的链表。你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。
```python
def swapPairs(self, head: ListNode) -> ListNode:
    '''两两交换链表中的节点
    
    @Note:
        新增虚拟节点
    '''
    ret=ListNode()
    ret.next=head
    last=ret
    while head is not None:
        tmp=head.next
        if tmp is not None:
            head.next=tmp.next
            tmp.next=head
            last.next=tmp
            last=head# 挪位
            head=head.next#挪位
        else:
            break
    return ret.next
```


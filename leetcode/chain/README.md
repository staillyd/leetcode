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

## [合并两个有序链表](21.py)
- [Link](https://leetcode-cn.com/problems/merge-two-sorted-lists/)
- 将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。 
```python
def mergeTwoLists(self, l1: ListNode, l2: ListNode) -> ListNode:
    '''合并两个有序链表'''
    ret=ListNode()
    last=ret
    while l1 is not None and l2 is not None:
        if l1.val<=l2.val:
            last.next=l1
            l1=l1.next#挪位
        else:
            last.next=l2
            l2=l2.next#挪位
        last=last.next
    last.next=l1 if l1 is not None else l2#剩余长度
    return ret.next
```

## [合并K个升序链表](23.py)
- [Link](https://leetcode-cn.com/problems/merge-k-sorted-lists/)
- 给你一个链表数组，每个链表都已经按升序排列。请你将所有链表合并到一个升序链表中，返回合并后的链表
- 思路:合并前后两个链表，结果放在后一个链表位置上，依次循环下去。$O(k^2n)$
  - $k$:lists长度
  - $n$:lists元素的平均长度
- 思路:归并排序变种  $O(klog(k)n)$
```python
def merge2Lists(self,l1:ListNode,l2:ListNode) -> ListNode:
    ret=ListNode()
    last=ret
    while l1 and l2:
        if l1.val<=l2.val:
            last.next=l1
            l1=l1.next
        else:
            last.next=l2
            l2=l2.next
        last=last.next
    last.next=l1 if l1 is not None else l2
    return ret.next

def mergeKLists_all(self, lists: List[ListNode]) -> ListNode:
    '''合并K个有序链表'''
    if len(lists)==0 or lists is None:
        return None
    for i in range(1,len(lists)):
        lists[i]=self.merge2Lists(lists[i-1],lists[i])
    return lists[len(lists)-1]

def mergeKLists(self, lists: List[ListNode]) -> ListNode:
    '''合并K个有序链表
    
    @Note:
        归并排序
    '''
    if len(lists)==0 or lists is None:
        return None
    return self.mergeKLists_sort(lists,0,len(lists)-1)

def mergeKLists_sort(self,lists: List[ListNode],l,r) -> ListNode:
    if l==r:
        return lists[l]#注意返回值,merge2Lists会更改原链表
    m=(l+r)//2
    l1=self.mergeKLists_sort(lists,l,m)
    l2=self.mergeKLists_sort(lists,m+1,r)
    return self.merge2Lists(l1,l2)
```

## [插入排序](147.py)
- [Link](https://leetcode-cn.com/problems/insertion-sort-list/)
- 对链表进行插入排序。
- **链表题记得画图**
```python
def insertionSortList(self, head: ListNode) -> ListNode:
    '''插入排序
    
    @Note:
        画图!!!
    '''
    ret=ListNode(0,head)
    last_sorted=head
    cur=head.next
    while cur:
        if last_sorted.val<=cur.val:
            cur=cur.next
            last_sorted=last_sorted.next
            continue
        
        find=ret.next
        last_find=ret
        while find.val<=cur.val:
            find=find.next
            last_find=last_find.next
        
        last_sorted.next=cur.next
        cur.next=find
        last_find.next=cur
        cur=last_sorted.next
    return ret.next
```

## [排序链表](148.py)
- [Link](https://leetcode-cn.com/problems/sort-list/)
- 给你链表的头结点 head ，请将其按 升序 排列并返回 排序后的链表 。
- 归并排序(特别注意**快慢指针求中间位置**)
```python
def merge2List(self,l1:ListNode,l2:ListNode)->ListNode:
    ret=ListNode()
    last=ret
    while l1 and l2:
        if l1.val<=l2.val:
            last.next=l1
            l1=l1.next
        else:
            last.next=l2
            l2=l2.next
        last=last.next
    last.next=l1 if l2 is None else l2
    return ret.next        

def sortList(self, head: ListNode) -> ListNode:
    if head is None or head.next is None:
        return head
    
    # 快慢指针求中间位置
    slow=head
    fast=head.next#!!!很关键
    while fast is not None and fast.next is not None:
        slow=slow.next
        fast=fast.next.next
    m=slow.next
    slow.next=None#关键

    l1=self.sortList(head)
    l2=self.sortList(m)
    return self.merge2List(l1,l2)
```

## [反转链表](206.py)
- [Link](https://leetcode-cn.com/problems/reverse-linked-list/)
- 给你单链表的头节点 head ，请你反转链表，并返回反转后的链表。
- 画图!!!
```python
def reverseList(self, head: ListNode) -> ListNode:
    '''反转链表'''
    ret=None#虚节点
    while head:
        tmp=head.next
        head.next=ret
        ret=head
        head=tmp
    return ret#返回自身
```

## [反转链表II](92.py)
- [Link](https://leetcode-cn.com/problems/reverse-linked-list-ii/)
- 给你单链表的头指针 head 和两个整数 left 和 right ，其中 left <= right 。请你反转从位置 left 到位置 right 的链表节点，返回 反转后的链表 。
```python
def reverse(self,head:ListNode)->ListNode:
    '''反转链表'''
    ret=None
    while head:
        tmp=head.next
        head.next=ret
        ret=head
        head=tmp
    return ret

def reverseBetween(self, head: ListNode, left: int, right: int) -> ListNode:
    ret=ListNode(0,head)
    i=0
    last=ret
    start,end=None,None
    while head:#画图!!!
        i+=1
        if i<left:
            last=last.next
        if i==left:
            start=head
        if i==right:
            end=head.next
            head.next=None
            break
        head=head.next
    
    l=self.reverse(start)
    last.next=l
    start.next=end

    return ret.next
```

## [重排链表](143.py)
- [Link](https://leetcode-cn.com/problems/reorder-list/)
- 给定一个单链表 L 的头节点 head ，单链表 L 表示为：
- L0 → L1 → … → Ln-1 → Ln 
- 请将其重新排列后变为：
- L0 → Ln → L1 → Ln-1 → L2 → Ln-2 → …
- 不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。
- 思路:快慢指针分两半;反转右半部分;左右两链表依次相连
```python
def reverse(self,head:ListNode)->None:
    ret=None
    while head:
        tmp=head.next
        head.next=ret
        ret=head
        head=tmp
    return ret#返回自身

def reorderList(self, head: ListNode) -> None:
    l=head

    slow,fast=head,head.next#右半部分比左半部分更短，快慢指针求中间位置
    while fast and fast.next:
        slow=slow.next
        fast=fast.next.next
    m=slow.next
    slow.next=None

    m=self.reverse(m)
    while l and m:
        l_tmp=l.next
        m_tmp=m.next

        l.next=m
        m.next=l_tmp

        l=l_tmp
        m=m_tmp
```

## [旋转链表](61.py)
- [Link](https://leetcode-cn.com/problems/rotate-list/)
- 给你一个链表的头节点 head ，旋转链表，将链表每个节点向右移动 k 个位置。
- 将链表右半部分的 k 的节点拼接到 head 即可。
- 注：k 对链表长度 n 取余，即 k %= n。
```python
def rotateRight(self, head: ListNode, k: int) -> ListNode:
    cur=head#取余
    n=0
    while cur:
        cur=cur.next
        n+=1
    if n==1 or n==0:
        return head#特判
    k=k%n
    if k==0:
        return head#特判

    # 快位置
    ret=ListNode(0,head)
    last_fast=ret
    fast=head
    while k!=0:
        k-=1
        fast=fast.next
        last_fast=last_fast.next
    
    # 快慢位置同时跑
    last_find=ret
    find=head
    while fast:
        last_fast=last_fast.next
        fast=fast.next

        find=find.next
        last_find=last_find.next
    # 拼接
    last_fast.next=head
    last_find.next=None
    head=find
    return head
```

## [回文链表](234.py)
- [Link](https://leetcode-cn.com/problems/palindrome-linked-list/)
- 请判断一个链表是否为回文链表。
```python
def reverse(self,head:ListNode)->ListNode:
    ret=None
    while head:
        tmp=head.next
        head.next=ret
        ret=head
        head=tmp
    return ret

def isPalindrome(self, head: ListNode) -> bool:
    '''快慢指针求中间,反转右半,进行顺序判断'''
    slow,fast=head,head.next
    while fast and fast.next:
        slow=slow.next
        fast=fast.next.next
    m=slow.next
    slow.next=None

    m=self.reverse(m)
    while head and m:
        if head.val!=m.val:
            return False
        head=head.next
        m=m.next
    return True
```

## [相交链表](160.py)
- [Link](https://leetcode-cn.com/problems/intersection-of-two-linked-lists/)
- 给你两个单链表的头节点 headA 和 headB ，请你找出并返回两个单链表相交的起始节点。如果两个链表没有交点，返回 null 。
```python
def getIntersectionNode(self, headA: ListNode, headB: ListNode) -> ListNode:
    '''判断链表是否相交
    
    @Note:
        a1->a2->...None->b1->b2->...None
        b1->b2->...None->a1->a2->...None
        这样的总长一样,且末尾都为None.注意要有None!!
    '''
    cur_A=headA
    cur_B=headB
    while cur_A or cur_B:
        if cur_A==cur_B:
            return cur_B
        cur_A=cur_A.next if cur_A else headB
        cur_B=cur_B.next if cur_B else headA
    return None
```
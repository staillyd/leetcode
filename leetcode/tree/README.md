# 二叉树
## [前序遍历](144.py)
```python
def preorderTraversal(self, root: TreeNode) -> List[int]:
    '''前序 
    
    @Note:
        非递归  stack [根]->  [左右]
    '''
    if root is None:
        return []
    ret=[]
    s=[root]#stack!!
    while s:
        node=s.pop()
        ret.append(node.val)
        if node.right:#注意  先入后出
            s.append(node.right)
        if node.left:
            s.append(node.left)
    return ret

def preorderTraversal_1(self, root: TreeNode) -> List[int]:
    '''前序  [根、左、右]
    
    @Note:
        看成只有三个节点（根节点，左子树，右子树）的树，不需要展开，直接调用
    '''
    if root is None:
        return []
    l=self.preorderTraversal(root.left)
    r=self.preorderTraversal(root.right)

    ret=[]
    ret.append(root.val)
    ret.extend(l)
    ret.extend(r)

    return ret
```

## [后序遍历](145.py)
- [Link](https://leetcode-cn.com/problems/binary-tree-postorder-traversal/)
```python
def postorderTraversal(self, root: TreeNode) -> List[int]:
    '''非递归,看成只有三个节点（根节点，左子树，右子树）的树

    @Note:
        根右左->左右根    stack [根]->  [右左]   反序
    '''
    if root is None:
        return []
    s=[root]
    ret=[]
    while s:
        node=s.pop()
        ret.append(node.val)
        if node.left:#注意  先入后出
            s.append(node.left)
        if node.right:
            s.append(node.right)
    return ret[::-1]

def postorderTraversal_1(self, root: TreeNode) -> List[int]:
    '''后序遍历
    
    @Note:
        递归
    '''
    if root is None:
        return []
    l=self.postorderTraversal(root.left)
    r=self.postorderTraversal(root.right)

    res=[]
    res.extend(l)
    res.extend(r)
    res.append(root.val)
    return res
```

## [中序遍历](94.py)
- [Link](https://leetcode-cn.com/problems/binary-tree-inorder-traversal/)
```python
def inorderTraversal(self, root: TreeNode) -> List[int]:
    '''中序遍历,左根右   []   [左根] -> [右]'''
    if root is None:
        return []
    
    ret=[]
    s=[]
    while root or s:#注意和前序后序不同!!!
        if root:
            s.append(root)
            root=root.left
        else:
            root=s.pop()
            ret.append(root.val)
            root=root.right
    return ret

def inorderTraversal_1(self, root: TreeNode) -> List[int]:
    if root is None:
        return []
    
    l=self.inorderTraversal(root.left)
    r=self.inorderTraversal(root.right)

    ret=[]
    ret.extend(l)
    ret.append(root.val)
    ret.extend(r)
    return ret
```

**前序、中序、后序非递归:树从根开始，栈存到根，然后开始弹出，然后再存剩余的。**

## [对称二叉树](101.py)
- [Link](https://leetcode-cn.com/problems/symmetric-tree/)
- 给定一个二叉树，检查它是否是镜像对称的
- **非递归,从root开始,把比较顺序写下,然后考虑如何用队列或栈实现这个顺序**
```python
def isSymmetric(self, root: TreeNode) -> bool:
    '''非递归,从root开始,把比较顺序写下,然后考虑如何用队列或栈实现这个顺序'''
    if root is None:
        return True
    s=[root.left,root.right]
    while s:
        node1=s.pop()
        node2=s.pop()
        if node1 is None and node2 is None:
            pass
        elif (node1 and node2 is None) or (node2 and node1 is None):
            return False
        else:
            if node1.val !=node2.val:
                return False
            s.append(node1.left)
            s.append(node2.right)
            s.append(node1.right)
            s.append(node2.left)
    return True

def is_symmetric(self, left:TreeNode ,right:TreeNode)->bool:
    '''左树是否镜像于右树'''
    if left is None and right is None:
        return True
    
    if left is not None and right is not None and left.val ==right.val and \
        self.is_symmetric(left.left,right.right) and self.is_symmetric(left.right,right.left):
        return True
    
    return False

def isSymmetric_1(self, root: TreeNode) -> bool:
    '''递归'''
    if root is None:
        return True
    return self.is_symmetric(root.left,root.right)
```

## [树的子结构](26.py)
- [Link](https://leetcode-cn.com/problems/shu-de-zi-jie-gou-lcof/)
- 输入两棵二叉树A和B，判断B是不是A的子结构。(约定空树不是任意一个树的子结构)
- B是A的子结构， 即 A中有出现和B相同的结构和节点值。
```python
def is_contain(self,A:TreeNode,B:TreeNode)->bool:
    '''B是否为A根节点相同的子树'''
    if B is None:#特别注意
        return True
    if A and B and A.val==B.val and\
        self.is_contain(A.left,B.left) and self.is_contain(A.right,B.right):
        return True
    return False

def isSubStructure(self, A: TreeNode, B: TreeNode) -> bool:
    if B is None:#None不是任何树的子树
        return False
    return self.is_contain(A,B) or (A is not None and (self.isSubStructure(A.left,B) or self.isSubStructure(A.right,B)))
```

## [翻转二叉树](226.py)
- [Link](https://leetcode-cn.com/problems/invert-binary-tree/)
```python
def invertTree(self, root: TreeNode) -> TreeNode:
    '''翻转二叉树'''
    if root is None:
        return root
    root.left,root.right=root.right,root.left
    self.invertTree(root.left)
    self.invertTree(root.right)
    return root
```

## [层序遍历](102.py)
- [Link](https://leetcode-cn.com/problems/binary-tree-level-order-traversal/)
```python
def levelOrder(self, root: TreeNode) -> List[List[int]]:
    '''队列'''
    if root is None:
        return []
    q=[root]
    ret=[]
    while q:
        size=len(q)#当前层的个数!!!
        t=[]
        for _ in range(size):
            node=q.pop(0)
            t.append(node.val)

            if node.left:
                q.append(node.left)
            if node.right:
                q.append(node.right)
        ret.append(t)
    return ret
```

## [层序遍历II](107.py)
- [Link](https://leetcode-cn.com/problems/binary-tree-level-order-traversal-ii/)
- 从底向上的层序
```python
def levelOrderBottom(self, root: TreeNode) -> List[List[int]]:
    '''层次遍历的逆序'''
    if root is None:
        return []
    q=[root]
    ret=[]
    while q:
        size=len(q)# 当前层节点的个数
        t=[]
        for _ in range(size):
            node=q.pop(0)
            t.append(node.val)

            if node.left:
                q.append(node.left)
            if node.right:
                q.append(node.right)
        ret.append(t)
    return ret[::-1]
```

## [二叉树的右视图](199.py)
- [Link](https://leetcode-cn.com/problems/binary-tree-right-side-view/)
- 给定一个二叉树的 根节点 root，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值。
```python
def rightSideView(self, root: TreeNode) -> List[int]:
    '''层序遍历的最右侧'''
    if root is None:
        return []
    q=[root]#队列
    ret=[]
    while q:
        size=len(q)
        for i in range(size):
            node=q.pop(0)

            if i==size-1:
                ret.append(node.val)

            if node.left:
                q.append(node.left)
            if node.right:
                q.append(node.right)
    return ret
```
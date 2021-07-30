# 回溯
## 模板
```python
res = []
path = []

def backtrack(未探索区域, res, path):
    if path 满足条件:
        res.add(path) # 深度拷贝
        # return  # 如果不用继续搜索需要 return
    for 选择 in 未探索区域当前可能的选择:
        if 当前选择符合要求:
            path.add(当前选择)
            backtrack(新的未探索区域, res, path)
            path.pop()
```

## 思想、步骤
- **画递归树**!!!

## 二叉树路径记录
![](imgs/二叉树递归树.jpg)
```python
def binaryTreePaths(self, root: TreeNode) -> List[str]:
    '''深度优先+路径记录'''
    path=[]#路径记录  全局变量，然后在dfs后pop最后一位
    ret=[]
    def dfs(root:TreeNode):
        if root is None:
            return
        path.append(str(root.val))# 前序
        if root.left is None and root.right is None:#输出  画1～3层的树
            ret.append('->'.join(path))

        dfs(root.left)
        dfs(root.right)
        path.pop()# 不pop的话path其实是前序遍历
    
    dfs(root)
    return ret
```

**子集、组合类问题，关键是用一个 start 参数来控制选择列表！！**

## [子集](78.py)
- [Link](https://leetcode-cn.com/problems/subsets/)
- 给你一个整数数组 nums ，数组中的元素 互不相同 。返回该数组所有可能的子集（幂集）。解集 不能 包含重复的子集。你可以按 任意顺序 返回解集。
- ![](imgs/子集问题递归树.png)
```python
def subsets(self, nums: List[int]) -> List[List[int]]:
    path=[]
    ret=[[]]
    
    def back_track(nums,i_start):
        for i in range(i_start,len(nums)):
            path.append(nums[i])
            ret.append(path.copy())
            back_track(nums,i+1)
            path.pop()
    
    back_track(nums,0)
    return ret
```

## [子集II](90.py)
- [Link](https://leetcode-cn.com/problems/subsets-ii/)
- 给你一个整数数组 nums ，其中可能包含重复元素，请你返回该数组所有可能的子集（幂集）。解集 不能 包含重复的子集。返回的解集中，子集可以按 任意顺序 排列。
- ![](imgs/子集问题递归树.png)
- 先排序
- 再剪枝(选择哪些不进行输出)
- ![](imgs/子集II剪枝.png)
- 去除当前选择列表中，与上一个数重复的那个数，引出的分支
```python
def subsetsWithDup(self, nums: List[int]) -> List[List[int]]:
    def back_track(nums,i_start):
        for i in range(i_start,len(nums)):
            if i>i_start and nums[i]==nums[i-1]:#剪枝
                continue
                
            path.append(nums[i])
            ret.append(path.copy())
            back_track(nums,i+1)
            path.pop()
    
    nums=sorted(nums)
    ret=[[]]
    path=[]
    back_track(nums,0)
    return ret
```

## [组合总和](39.py)
- [Link](https://leetcode-cn.com/problems/combination-sum/)
- 给定一个无重复元素的正整数数组 candidates 和一个正整数 target ，找出 candidates 中所有可以使数字和为目标数 target 的唯一组合。
- ![](imgs/组合之和.png)
```python
def combinationSum(self, candidates: List[int], target: int) -> List[List[int]]:
    ret=[]
    path=[]

    def back_track(nums,i_start,sum_):
        for i in range(i_start,len(nums)):
            if sum_+nums[i]>target:#剪枝
                continue

            sum_+=nums[i]
            path.append(nums[i])
            if sum_==target:#如果满足条件,则append
                ret.append(path.copy())
            
            back_track(nums,i,sum_)#可以重复利用,i
            sum_-=nums[i]#回退状态
            path.pop()
    
    back_track(candidates,0,0)
    return ret
```
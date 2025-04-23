class Binary_Search_4(object):

    def __init__(self) -> None:
        super().__init__()

    def search(self, arr, item):
        '''查找最后一个小于等于给定值的元素'''
        l = 0
        r = len(arr) - 1
        while True:
            m = (l + r) // 2
            if arr[m] > item:
                r = m - 1
            else:
                if m == len(arr) - 1 or arr[m + 1] > item:  # 终止条件
                    return m
                l = m + 1
            if l > r:  #注意二分查找可以相等,与排序的递归退出条件不同
                return -1


if __name__ == '__main__':
    arr = [int(x) for x in input().strip().split(' ')]
    item = int(input().strip())
    binary_search = Binary_Search_4()
    idx = binary_search.search(arr, item)
    print(idx)

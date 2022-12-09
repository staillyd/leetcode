class PrioQueue:
    '''优先队列'''

    def __init__(self, l) -> None:
        self.arr = l
        if l:
            self.build_heap()

    def enqueue(self, num):
        '''入队'''
        self.arr.append(num)
        # 类似插入排序   最后一位上浮
        j = (len(self.arr) - 1 - 1) // 2  #注意
        last_j = len(self.arr) - 1
        while j > 0 and self.arr[j] > num:
            self.arr[last_j] = self.arr[j]
            last_j = j
            j = (j - 1) // 2
        self.arr[last_j] = num

    def sift_down(self, select, num):
        '''类似插入排序  下沉
        
        @Note:
            select: 当前堆顶的索引
            num:    堆顶元素看成的数值，实际堆顶是什么无关紧要
        '''
        last_j = select
        j = 2 * select + 1  #堆的左侧
        while j < len(self.arr):
            if j + 1 < len(self.arr) and self.arr[j + 1] < self.arr[j]:
                j += 1  # 取堆左右侧更小的一侧作为当前位置
            if num < self.arr[j]:
                break  #num<堆的左右两侧
            self.arr[last_j] = self.arr[j]
            last_j = j
            j = 2 * last_j + 1
        self.arr[last_j] = num

    def dequeue(self):
        '''出队,返回堆顶(select),取出最后一个数,把他当成堆顶
        第一位下沉到合适位置'''
        ret = self.arr[0]
        num = self.arr.pop()
        if len(self.arr) > 0:
            self.sift_down(0, num)
        return ret

    def build_heap(self):
        '''对一个列表进行堆的初始化,从非叶子节点开始(end//2往0排)'''
        for i in range(len(self.arr) // 2, -1, -1):
            self.sift_down(i, self.arr[i])


if __name__ == '__main__':
    # heap_sort: 构建堆(sift_down)->出列
    solution = PrioQueue([1, 3, 4, 2, 1, 5, 4])
    while len(solution.arr) > 0:
        print(solution.dequeue())

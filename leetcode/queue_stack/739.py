class Solution:

    def dailyTemperatures(self, temperatures: List[int]) -> List[int]:
        '''栈递减,类似滑动窗口,满足条件弹出,不然往里加'''
        ret = [0 for _ in range(len(temperatures))]
        s = []
        for j in range(len(temperatures)):
            while s and temperatures[j] > temperatures[s[-1]]:  #满足条件弹出,直到不满足
                i = s.pop()
                ret[i] = j - i
            s.append(j)
        return ret

    def dailyTemperatures_all(self, temperatures: List[int]) -> List[int]:
        res = [0 for _ in range(len(temperatures))]
        for i in range(len(temperatures)):
            for j in range(i + 1, len(temperatures)):
                if temperatures[j] > temperatures[i]:
                    res[i] = j - i
                    break
        return res

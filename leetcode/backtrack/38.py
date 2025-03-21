from typing import List


class Solution:

    def permutation(self, s: str) -> List[str]:
        ret = []
        path = []
        used = [False for i in range(len(s))]

        s = sorted(s)  #排序!!!

        def back_track():
            if len(path) == len(s):
                ret.append(''.join(path))
                return
            for i in range(len(s)):
                if used[i]:
                    continue

                if i > 0 and s[i] == s[i - 1] and not used[i - 1]:  #剪枝
                    continue
                used[i] = True
                path.append(s[i])
                back_track()
                used[i] = False
                path.pop()

        back_track()
        return ret


if __name__ == '__main__':
    solution = Solution()
    solution.permutation('aba')

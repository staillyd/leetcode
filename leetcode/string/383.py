class Solution:

    def canConstruct(self, ransomNote: str, magazine: str) -> bool:
        '''赎金信
        
        @Note:
            类似滑动窗口中定义一个满足条件的变量
        '''
        all_len = len(ransomNote)
        char_count = {}
        for char in magazine:
            if char not in char_count:
                char_count[char] = 0
            char_count[char] += 1
        for r in range(len(ransomNote)):
            if ransomNote[r] in char_count:
                char_count[ransomNote[r]] -= 1
                if char_count[ransomNote[r]] < 0:
                    return False
                all_len -= 1
            else:
                break
        return all_len == 0

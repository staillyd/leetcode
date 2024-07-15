class Solution:

    def reverseVowels(self, s: str) -> str:
        '''反转该字符串中的元音字母
        
        @Note:
            类似快排，左右指针
        '''
        vowels = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'}
        i, j = 0, len(s) - 1
        s = list(s)
        while i < j:
            while i < j and s[i] not in vowels:
                i += 1
            while i < j and s[j] not in vowels:
                j -= 1
            if i < j:
                s[i], s[j] = s[j], s[i]
            else:
                break
        return ''.join(s)

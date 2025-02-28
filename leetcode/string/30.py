from typing import List


class Solution:

    def findSubstring(self, s: str, words: List[str]) -> List[int]:
        '''串联所有单词的子串，单词长度一致
        
        @Note:
            滑动窗口法,单词当作一个元素
        '''
        ret = []
        word_len = len(words[0])
        for i in range(word_len):  #单词长度内每位往后 单词长度
            all_need_cnt = len(words)  #仍需要的个数才能满足条件
            word_count = {}  #滑动窗口还需要的次数
            for word in words:
                if word not in word_count:
                    word_count[word] = 0
                word_count[word] += 1
            l, r = i, i
            for r in range(i, len(s), word_len):
                this_word = s[r:r + word_len]
                if this_word in word_count:
                    if word_count[this_word] > 0:
                        all_need_cnt -= 1
                        word_count[this_word] -= 1

                        if all_need_cnt == 0:  #满足条件
                            ret.append(l)
                            old_word = s[l:l + word_len]  #l往右平移
                            word_count[old_word] += 1
                            all_need_cnt += 1
                            l = l + word_len
                    else:  #当前单词出现次数过多
                        while s[l:l + word_len] != this_word:  #l往右平移
                            word_count[s[l:l + word_len]] += 1
                            all_need_cnt += 1
                            l += word_len
                        l = l + word_len

                else:  #当前单词不满足
                    while l != r:  #之前的单词  #l往右平移
                        old_word = s[l:l + word_len]
                        word_count[old_word] += 1
                        all_need_cnt += 1
                        l += word_len
                    l += word_len
        return ret

    def findSubstring_all(self, s: str, words: List[str]) -> List[int]:
        '''串联所有单词的子串，单词长度一致
        
        @Note:
            滑动窗口法,单词当作一个元素  穷举
        '''
        l, r = 0, 0
        ret = []
        word_len = len(words[0])
        for r in range(len(s)):
            all_need_cnt = len(words)  #仍需要的个数才能满足条件
            word_count = {}  #滑动窗口需要的次数
            for word in words:
                if word not in word_count:
                    word_count[word] = 0
                word_count[word] += 1
            for this_r in range(r, len(s), word_len):
                this_word = s[this_r:this_r + word_len]
                if this_word in word_count:
                    if word_count[this_word] > 0:
                        all_need_cnt -= 1
                    word_count[this_word] -= 1
                    if word_count[this_word] < 0:
                        word_count[this_word] += 1
                        break
                    if all_need_cnt == 0:
                        ret.append(r)
                else:
                    break
        return ret


if __name__ == '__main__':
    # string=input()
    # word=[tmp for tmp in input().split(',')]
    string = "barfoofoobarthefoobarman"
    word = ["bar", "foo", "the"]
    solution = Solution()
    print(solution.findSubstring(string, word))

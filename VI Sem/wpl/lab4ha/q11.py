#Write a Python class to find validity of a string of parentheses, '(', ')', '{', '}', '['
#and ']. These brackets must be close in the correct order, for example "()" and
#"()[]{}" are valid but "[)", "({[)]" and "{{{" are invalid.

class parantheses:
    def __init__(self):
        self.m = {')': '(', '}': '{', ']': '['}

    def validity(self, s):
        st = []
        for c in s:
            if c in self.m.values():
                st.append(c)
            elif c in self.m:
                if not st or st[-1] != self.m[c]:
                    return False
                st.pop()
        return not st


p = parantheses()
t = ["()", "()[]{}", "[)", "({[)]", "{{{"]
for s in t:
    print(s, p.validity(s))

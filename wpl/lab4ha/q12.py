#Write a Python class to reverse a string word by word.

class Reverse:
    def r_words(self, s: str) -> str:
        words = s.split()
        words.reverse()
        return ' '.join(words)

reverser = Reverse()
inp = "I'm not an owl!"
print("Original string:", inp)
print("Reversed string:", reverser.r_words(inp))

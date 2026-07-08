#Write a python program to sort words in alphabetical order.
def sort_words(s):
words = s.split()
words.sort()
return words
def main():
s = "Princita Zina Miranda Elveera Peter Babush"
result = sort_words(s)
print(" ".join(result))
if __name__ == "__main__":
main()

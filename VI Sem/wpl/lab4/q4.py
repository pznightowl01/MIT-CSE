#Write a Python class to get all possible unique subsets from a set of distinct
#integers Input:[4,5,6]
#Output : [[], [6], [5], [5, 6], [4], [4, 6], [4, 5], [4, 5, 6]]
from itertools import chain, combinations
class SubsetGenerator:
def __init__(self, inp_set):
self.inp_set = inp_set
def new_subsets(self):
return [list(s) for s in chain.from_iterable(
combinations(self.inp_set, i) for i in range(len(self.inp_set) + 1)
)]
def main():
inp_set = [1, 2]
print("\ninput:[1, 2]")
generator = SubsetGenerator(inp_set)
print("output:")
print(generator.new_subsets())
if __name__ == "__main__":
main()

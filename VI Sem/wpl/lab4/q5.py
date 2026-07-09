# Write a Python class to find a pair of elements (indices of the two numbers)
# from a given array whose sum equals a specific target number.
# Input: numbers= [10,20,10,40,50,60,70], target=50
# Output: 3, 4.
class PairFinder:
def __init__(self, nos, target):
self.nos = nos
self.target = target
def f_pair(self):
indices = {}
for i, num in enumerate(self.nos):
comp = self.target - num
if comp in indices:
return indices[comp] + 1, i + 1
indices[num] = i
return None
def main():
nos = [10, 20, 10, 40, 50, 60, 70]
target = 50
finder = PairFinder(nos, target)
r = finder.f_pair()
if r:
print(r[0], r[1])
else:
print("no pair found")
if __name__ == "__main__":
main()

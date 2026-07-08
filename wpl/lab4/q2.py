#Write a python program to implement binary search with recursion.
def binary_search(arr, tar, low, high):
if low > high:
return -1
mid = (low + high) // 2
if arr[mid] == tar:Name : Princita Zina Miranda, Section : SCE-C, Reg no. 220905115 (roll no. 17)
return mid
if tar < arr[mid]:
return binary_search(arr, tar, low, mid - 1)
return binary_search(arr, tar, mid + 1, high)
def main():
arr = [12, 27, 38, 43, 76, 99]
tar = int(input("searching: "))
result = binary_search(arr, tar, 0, len(arr) - 1)
print("found at index:", result)
if __name__ == "__main__":
main()

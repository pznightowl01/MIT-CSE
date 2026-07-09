#Write a python program to implement bubble sort.

def bubble_sort(a):
    n = len(a)
    for i in range(n):
        s = False
        for j in range(n - i - 1):
            if a[j] > a[j + 1]:
                a[j], a[j + 1] = a[j + 1], a[j]
                s = True
        if not s:
            break
    return a

u = [25, 12, 23, 90, 104, 74, 45, 56]
print(bubble_sort(u))
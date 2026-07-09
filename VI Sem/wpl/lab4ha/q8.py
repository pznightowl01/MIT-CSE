# Write a python program to select smallest element from a list in an expected
# linear time.

def f(a):
    if not a:
        return None
    m = a[0]
    for x in a[1:]:
        if x < m:
            m = x
    return m

n = [23, 90, 104, 74, 45, 89, 17, 56]
print(f(n))
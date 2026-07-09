# Write a python program to multiply two matrices

def matrix_multiply(a, b):
    m = len(a)
    n = len(a[0])
    if n != len(b):
        raise ValueError
    p = len(b[0])
    r = [[0]*p for _ in range(m)]
    for i in range(m):
        for j in range(p):
            for k in range(n):
                r[i][j] += a[i][k] * b[k][j]
    return r

a = [
    [2, 4, 6],
    [8, 10, 11]
]

b = [
    [1, 3],
    [5, 7],
    [9, 11]
]

x = matrix_multiply(a, b)
for i in x:
    print(i)
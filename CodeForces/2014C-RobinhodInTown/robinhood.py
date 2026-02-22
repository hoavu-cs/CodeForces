
num_tests = int(input())
i = 1

for _ in range(num_tests):
    n = int(input())

    a = input().split()
    a = [int(i) for i in a]   
    a.sort() 

    if n < 3:
        print("-1")
        continue

    m = n // 2
    total = sum(a)

    x = 2 * n * a[m] - total + 1
    print(max(0, x))


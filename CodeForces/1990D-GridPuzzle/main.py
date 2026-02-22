num_tests = int(input())

for _ in range(num_tests):
    n = int(input())
    a = list(map(int, input().split()))

    start, end = 1, a[0]
    ans = 0
    i = 0

    while i < n:
        if end - start >= 0 and i == n - 1: # last row with black squares
            ans += 1
            break
        elif i ==  n - 1: # last row with no black squares
            break

        if start > end: # 0 black square on current row
            i += 1
            start, end = 1, a[i]
            continue

        if end - start + 1 > 2: # more than 2 black squares on current row
            i += 1
            ans += 1
            start, end = 1, a[i]
            continue
        
        if start > a[i + 1]: # current row black squares start after next row black squares end
            i += 1
            ans += 1
            start, end = 1, a[i]
        
        elif start > 1 and end < a[i + 1]: 
            # current row black squares start after next row black squares start and end before next row black squares end
            if end == a[i + 1] - 1:
                ans += 1
                i += 1
                start, end = 1, a[i] - 2
            else:
                i += 2
                ans += 2
                if i < n:
                    start, end = 1, a[i]

        elif start > 1 and end >= a[i + 1]:
            # current row black squares start after next row black squares start and end after or at the same time next row black squares end
            ans += 1
            i += 1
            end -= 2
            start = 1

        elif start == 1 and end < a[i + 1]:
            # current row black squares start at the beginning and end before next row black squares end
            ans += 1
            i += 1
            start, end = 3, a[i]

        elif start == 1 and end >= a[i + 1]:
            # current row black squares start at the beginning and end after or at the same time next row black squares end
            i += 2
            ans += 1
            if i < n:
                start, end = 1, a[i]

    print(ans)
        

            
        
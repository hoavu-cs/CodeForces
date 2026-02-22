from math import inf

def binary_search(t, i, period):
    # return the index of the last trip so that the time difference, between the last trip to t[i] is more than period
    left = 1
    right = i - 1
    ans = -1
    while left <= right:
        mid = (left + right) // 2
        if t[i] - t[mid] + 1 > period:
            if mid > ans:
                ans = mid
            left = mid + 1
        else:
            right = mid - 1
    return ans

n = int(input())
dp = [0] * (n + 1)
t = [0] * (n + 1)
dp[0] = 0

t[1] = int(input())
dp[1] = 20 

# 1 trip: $20, 90 min: $50, 1440 min: $120

for i in range(2, n + 1):
    t[i] = int(input())
    
    x = binary_search(t, i, 90)
    y = binary_search(t, i, 1440)

    choice1 = inf
    choice2 = inf
    choice3 = inf
    
    if x > -1:
        choice1 = dp[x] + 50 
    else:
        choice1 = 50

    if y > -1:
        choice2 = dp[y] + 120
    else:
        choice2 = 120
    
    choice3 = dp[i - 1] + 20
    dp[i] = min(choice1, choice2, choice3)

for i in range(1, n + 1):
    print(dp[i] - dp[i - 1])

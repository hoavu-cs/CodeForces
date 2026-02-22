"""
Solution sketch:
Let m be the final equal value. Let x_i be the number of times we decrease 2 from a_i.
Then, we have the following equations:
a_0 - 2 x_0 + x_{n - 1} = m
a_1 - 2 x_1 + x_0 = m
...
a_{n - 1} - 2 x_{n - 1} + x_{n - 2} = m

Def: if there is a solution where x_i are all non-negative integers, then m is feasible.
Note that the number of steps is sum(x).
From the above, sum(x) = sum(a) - n m.
So we want to maximize m such that m is feasible.
Note that if m is feasible, then m - 1 is feasible by adding 1 to each x_i. 
Thus, we can do binary search on m. The remaining goal is how to efficiently check if m is feasible.
Fix m, we can solve n equations in n variables x_i; but I don't know how to do it efficiently.

One approach is to start with a guess of x_{n - 1} from the top equation, and then solve the rest of the equations.
In the end, if in the last equation, x_{n - 1} > guess, then we need to reduce the guess. 
This gives us a way to binary search for x_{n - 1}.
"""

def is_feasible(a, m):
    n = len(a)
    x = [0] * n
    max_value = max(a)

    left, right = 0, max_value
    flag = False

    while left <= right:
        mid = (left + right) // 2

        for i in range(n):
            y = mid if i == 0 else x[i - 1]
            x[i] = (a[i] - m + y) / 2
       
        if x[n - 1] == mid:
            flag = True # found a feasible solution but not necessarily non-negative integers
            break
        elif mid > x[n - 1]:
            right = mid - 1
        else:
            left = mid + 1
    
    if not flag:
        return []
    else:
        for i in range(n):
            if x[i] < 0 or x[i] != int(x[i]): # return an empty list if x[i] is not a non-negative integer
                return []
        return x


if __name__ == "__main__":

    T = int(input())
    
    for _ in range(T):
        n = int(input())
        a = list(map(int, input().split()))

        left, right = 0, max(a)
        ans = -1
        
        # binary search for m
        while left <= right:
            mid = (left + right) // 2
            x = is_feasible(a, mid)
            
            if len(x) > 0:
                ans = sum(x)
                left = mid + 1
            else:
                right = mid - 1

        print(int(ans))


import math

def solution(x, y):
    # Your code here
    i = int(x)
    j = int(y)

    # set infinity in python 2.7
    infinity = float('inf')

    if i == 0 or j == 0: # base case
        return "impossible"

    if i == 1: # base case
        return str(j//i-1)
    elif j == 1: # base case
        return str(i//j-1)
    else: # non-base case
        r = 0
        q = 0
        z = 0
        if i < j:
            r = j % i
            q = j // i
            z = solution(str(i), str(r))
        else:
            r = i % j
            q = i // j
            z = solution(str(r), str(j))
        if z == "impossible":
            return z
        else:
            return str(int(float(z)) + q) 



assert(solution('4', '7') == '4')
assert(solution('2', '1') == '1')
assert(solution('1', '1') == '0')
assert(solution('2', '4') == 'impossible')

import math
import fractions

def generate_perms(n, m):
    # generate a list of possible cycle lengths (called configurations) 
    # of S_n such that the maximum cycle length is m in non-decreasing order 
    configs = []
    if n == 0:
        return [[]]
    elif n > 0 and m == 0:
        return None
    else:
        for i in range(1, min(m+1, n+1)):
            L = generate_perms(n-i, i)
            if L != None:
                for l in L:
                    l.append(i)
                    configs.append(l)
    return configs


def num_perms(n, configs):
    # count the number of permutations given a configuration
    result = math.factorial(n)
    p = 1
    for k in range(1, n+1):
        a_k = configs.count(k)
        p *= math.factorial(a_k)*math.pow(k, a_k)

    return int(result//p)


def gcd(x, y):
    # return the GCD
    if y == 0:
        return x
    r = int(x % y)
    return gcd(y , r)


def fix(r, c, s):
    # compute the number of fix points given row permutation r
    # and column permutation c (in cycle notations)
    result = 1
    for i in range(len(r)):
        for j in range(len(c)):
            result *= int(math.pow(s, gcd(r[i], c[j])))
    return result


def solution(w, h, s):
    # we solve this using Burnside lemma
    P = generate_perms(w, w)
    Q = generate_perms(h, h)
    result = 0
    for p in P:
        for q in Q:
            result += fix(p, q, s)*num_perms(w, p)*num_perms(h, q)
    result = result//(math.factorial(w)*math.factorial(h))
    return str(int(result))

#print(num_perms(5, [1, 1, 3]))
#print(solution(5, 5, 20))
#print(num_perms(4, [1, 1, 1, 1]))
#print(generate_perms(4, 4))
#print(mult_polynomials([1, 2, 3], [2, 3, 5]))  
#print(solution(2,3,4))
#print(generate_perms(5, 5))
#print(num_perms(5, [2, 2, 1]))
#print(fix([4, 2], [2, 2], 2))
#print(solution(4,4,20))
#print(solution(4,4,20))
assert(solution(4, 4, 20) == str(1137863754106723400))
assert(solution(5, 5, 20) == str(23301834615661488487765745000))
assert(solution(6, 6, 20) == str(132560781153101038829213988789736592649360))
print(solution(4, 6, 10))
#(6,6,20) -> 132560781153101038829213988789736592649360
#(7,7,20) -> 221619886894198821201872678876163305792210161226545392840
#(8,8,20) -> 113469378614817897312718329989374518983724697432844009920312263602471667640
#print(gcd(125, 25))
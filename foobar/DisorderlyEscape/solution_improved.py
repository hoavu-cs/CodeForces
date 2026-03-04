import math


def generate_perms(n):
    # generate a list of possible cycle lengths (called configurations) of S_n
    perms = [[] for i in range(n+1)]
    perms[0].append([])
    for i in range(1, n+1):
        for j in range(1, i+1):
            for x in perms[i-j]:
                p = [y for y in x]
                p.append(j)
                if j >= max(p):
                    perms[i].append(p)
    return perms[n]


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
    P = generate_perms(w)
    Q = generate_perms(h)
    result = 0
    for p in P:
        for q in Q:
            result += fix(p, q, s)*num_perms(w, p)*num_perms(h, q)
    result = result//(math.factorial(w)*math.factorial(h))
    return str(int(result))


assert(solution(2, 2, 2) == str(7))
assert(solution(2, 3, 4) == str(430))
assert(solution(4, 4, 20) == str(1137863754106723400))
assert(solution(5, 5, 20) == str(23301834615661488487765745000))
assert(solution(6, 6, 20) == str(132560781153101038829213988789736592649360))
assert(solution(4, 6, 10) == str(57957626030575864330))

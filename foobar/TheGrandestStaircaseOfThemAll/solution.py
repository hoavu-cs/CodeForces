def solution(n):
    # dynamic programming solution
    # DP[i][j] = number of choices to build a staircase using i bricks 
    # in which the maximum step-height is j 
    DP = [[0 for i in range(n+1)] for j in range(n+1)]

    # base cases 
    for i in range(0, n+1): 
        DP[0][i] = 1 # if we have 0 brick, then there is 1 choice 
    for i in range(1, n+1):
        DP[i][0] = 0 # if we have >0 bricks, but max height = 0, there is 0 choice

    # compute the dynamic programing table
    for i in range(1, n+1):
        for j in range(1, n+1):
            for k in range(1, j+1):
                DP[i][j] += DP[i-k][k-1]

    # return DP[n][n] -1  to not count 
    # the case we build 1 step with n bricks
    return DP[n][n] - 1




assert(solution(3) == 1)
assert(solution(4) == 1)
assert(solution(5) == 2)
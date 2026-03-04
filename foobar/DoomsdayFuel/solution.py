from fractions import Fraction


def swap_rows(M,i,j):
    # swap rows i and j of M
    for k in range(len(M[i])):
        x = M[i][k]
        M[i][k] = M[j][k]
        M[j][k] = x


def gaussian_elm(M, b):
    # perform Gaussian elimination on matrix M
    # require M to be invertible
    n = len(M)
    if n >= 2:
        # swap rows if necessary
        if M[0][0] == 0:
            for i in range(1, n):
                if M[i][0] != 0:
                    swap_rows(M, 0, i)
                    swap_rows(b, 0, i)

        for i in range(1, n):
            c = Fraction(M[i][0],M[0][0])
            for j in range(n):
                M[i][j] = M[i][j] - M[0][j]*c 
            b[i] = b[i] - b[0]*c

        #  recurse
        N = [r[1:] for r in M[1:]]
        r = gaussian_elm(N, b[1:])
        
        for i in range(1, n):
            for j in range(1,n):
                M[i][j] = r[0][i-1][j-1] 
            b[i] = r[1][i-1]
    return (M, b)


def solve_sys_ln_eqs(A, b):
    # solve the system of linear equations Ax = b 
    # require A to be invertible
    r = gaussian_elm(A, b)
    A = r[0]
    b = r[1]
    n = len(A)
    x = [0 for i in range(n)]

    for i in range(n-1,-1,-1):
        z = 0
        for j in range(i+1,n):
            z += A[i][j]*x[j]
        x[i] = (b[i]-z)/A[i][i]
    return x


def lcm(u, v):
    if u > v:
        z = u
    else:
        z = v
    while True:
        if((z % u == 0) and (z % v == 0)):
            lcm = z
            break
        z += 1
    return lcm


def solution(m):
    n = len(m)
    p = [[Fraction(0,1) for i in range(n)] for j in range(n)]
    term_st = set()
    T = []
    R = []
    
    # create probability transition matrix
    for i in range(n):
        row_sum = sum(m[i])-m[i][i]
        if row_sum == 0:
            p[i][i] = Fraction(1,1)
            term_st.add(i)
        else:
            for j in range(n):
                p[i][j] = Fraction(m[i][j], row_sum)

    # solve for probability of reaching each terminal state
    for i in range(n):
        if i in term_st:
            A = [[Fraction(0,1) for l in range(n)] for j in range(n)]
            b = [0 for l in range(n)]
            b[i] = 1

            for j in range(n):
                for k in range(n):
                    if k == j:
                        A[j][k] = 1
                    else:
                        A[j][k] = -p[j][k]

            x = solve_sys_ln_eqs(A, b)
            T.append(x[0])

    # format output 
    d = 1
    for i in T:
        d = lcm(i.denominator, d)
    for i in T:
        scale = d/i.denominator
        R.append(i.numerator*scale)
    R.append(d)
    return R


assert(solution(
   [[1, 2, 3, 0, 0, 0], [4, 5, 6, 0, 0, 0], [7, 8, 9, 1, 0, 0], [0, 0, 0, 0, 1, 2], [0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0]]
)) == [1, 2, 3]    



    
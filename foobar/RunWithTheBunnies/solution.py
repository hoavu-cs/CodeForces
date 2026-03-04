import itertools 

infinity = float('inf')

def FloydWarshall(A):
    '''
    A: adjacency matrix. 
    Compute all pair shortest paths and return the distance matrix and 
    whether the graph has a negative cycle.
    Note that we might need to use Bellman-Ford to check for negative cycles
    that are *reachable* from "start". But since this graph is complete, all
    cycles are reachable.
    '''    
    n = len(A)
    D = A
    negative_cycle = False
    for k in range(n):
        for i in range(n):
            for j in range(n):
                D[i][j] = min(D[i][j], D[i][k]+D[k][j])
    for i in range(n):
        if D[i][i] < 0:
            negative_cycle = True
    return D, negative_cycle


def solution(times, times_limit):
    n = len(times)
    fw = FloydWarshall(times)
    distance = fw[0]
    negative_cycle = fw[1]

    if negative_cycle: # if there is a negative cycle, output all bunnies
        return [i for i in range(n-2)]
    else:
        best_solution = []
        bunny_ids = [j for j in range(1, n-1)]

        for k in range(1, n-1):
            for S in itertools.permutations(bunny_ids, k):
                cost = distance[0][S[0]] + distance[S[k-1]][n-1]
                for i in range(k-1):
                    cost += distance[S[i]][S[i+1]]
                if cost <= times_limit and len(S) > len(best_solution):
                    best_solution = S

        best_solution = [i-1 for i in best_solution]
        best_solution.sort()
        return best_solution


case1 = [[0, 1, 1, 1, 1], 
             [1, 0, 1, 1, 1], 
             [1, 1, 0, 1, 1], 
             [1, 1, 1, 0, 1], 
             [1, 1, 1, 1, 0]]
assert(solution(case1, 3) == [0, 1])

case2 = [[0, 2, 2, 2, -1], 
         [9, 0, 2, 2, -1], 
         [9, 3, 0, 2, -1], 
         [9, 3, 2, 0, -1], 
         [9, 3, 2, 2, 0]]
assert(solution(case2, 1) == [1, 2])

case3 = [[0, 2, 2, 2, -1], 
         [9, 0, 2, 2, 0], 
         [9, 3, 0, 2, 0], 
         [9, 3, 2, 0, 0], 
         [-1, 3, 2, 2, 0]]
assert(solution(case3, -500) == [0, 1, 2])    


case4 = [[1, 1, 1, 1, 1, 1, 1], 
         [1, 1, 1, 1, 1, 1, 1], 
         [1, 1, 1, 1, 1, 1, 1], 
         [1, 1, 1, 1, 1, 1, 1], 
         [1, 1, 1, 1, 1, 1, 1], 
         [1, 1, 1, 1, 1, 1, 1], 
         [1, 1, 1, 1, 1, 1, 1]] 
assert(solution(case4, 1) == [])   

case5 = [[1, 1, 1], 
         [1, 1, 1], 
         [1, 1, 1]]  
assert(solution(case5, 2) == [0])        


case6 = [[0, 5, 11, 11, 1], 
         [10, 0, 1, 5, 1], 
         [10, 1, 0, 4, 0], 
         [10, 1, 5, 0, 1], 
         [10, 10, 10, 10, 0]]
assert(solution(case6, 10) == [0, 1])   

case7 = [[0, 10, 10, 10, 1], 
         [0, 0, 10, 10, 10], 
         [0, 10, 0, 10, 10], 
         [0, 10, 10, 0, 10], 
         [1, 1, 1, 1, 0]]
assert(solution(case7, 5) == [0, 1])   

case8 = [[0, 0, 0, 0, 0], 
        [0, 0, 0, 0, 0], 
        [0, 0, 0, 0, 0], 
        [0, 0, 0, 0, 0], 
        [0, 0, 0, 0, 0]]
assert(solution(case8, 1) == [0, 1, 2])   

case9 = [[2, 2], 
         [2, 2]]
assert(solution(case9, 1) == [])   


case10 = [[0, 10, 10, 1, 10], 
          [10, 0, 10, 10, 1], 
          [10, 1, 0, 10, 10], 
          [10, 10, 1, 0, 10], 
          [1, 10, 10, 10, 0]]
assert(solution(case10, 6) == [0, 1, 2])   


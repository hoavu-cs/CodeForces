import itertools


def solution(num_buns, num_required):
    ''' Let num_buns = x, and num_required = y.
    The idea here is that we want to construct a set of n elements [n]={0,1,...,n-1} (key types) such that:
    Each bunny i is a set S_i that contains some elements in [n]
    1) Every y sets have their union equals to [n].
    2) No y-1 sets have their union equals to [n].
    How do we construct such a set system? 
    What should be the smallest value of n and what are the set sizes in that case?

    Key observation: an element must belong at least x-y+1 sets. If not, then there are y sets that do not contain
    that element which contradicts (1).

    Here is a construction:
    We let n = (x choose x-y+1) = (x choose y-1). Let C_1, C_2,..., C_n be the collection of
    sets of size x-y+1 in lexicographic order.
    We let element j in [n] belongs to the sets in C_j. We will prove that this set system satisfies what we need.
    1) For any y sets, if it does not contain some element j, then j belongs to at most x-y sets which is a contradiction.
    2) For any y-1 sets,  there is some element that does not belong to these y-1 sets by construction.
    The minimalism of this system is not hard to prove (pigeonhole principle) and is left as an exercise.
    Exercise: show that the set size is (x choose y-1)(x-y+1)/x

    '''
    x = num_buns
    y = num_required
    bunny_ids = [i for i in range(x)]
    output = [[] for i in range(x)]

    j = 0
    for C in itertools.combinations(bunny_ids, x-y+1):
        for c in C:
            output[c].append(j)
        j += 1

    return output


A = [[0, 1, 2, 3, 4, 5], [0, 1, 2, 6, 7, 8], [0, 3, 4, 6, 7, 9], [1, 3, 5, 6, 8, 9], [2, 4, 5, 7, 8, 9]]
assert(solution(5,3) == A)

A = [[0], [0]]
assert(solution(2,1) == A)





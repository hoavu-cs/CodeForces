def solution(s):
    # Your code here
    # A divide and conquer solution
    if len(s) <= 1: # base case
        return 0
    else:
        m = len(s)/2
        num_salutes = 0
        left = s[:m]
        right = s[m:]
        
        # recurse on the left and right halves
        count = solution(left)
        count += solution(right)
        
        # add (number of > on the left) x (number of < on the right) to the answer
        count += 2*left.count('>')*right.count('<')
        
        return count
        
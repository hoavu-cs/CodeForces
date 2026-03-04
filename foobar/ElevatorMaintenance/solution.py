import functools

def ver_comp(a,b):

    if len(a) == 0 and len(b) == 0:
        return 0
    elif len(a) == 0 and len(b) > 0:
        return -1
    elif len(a) > 0 and len(b) == 0:
        return 1
    else: # non-base case
        if a[0] > b[0]:
            return 1
        elif a[0] < b[0]:
            return -1
        else: # recursive call
            x = a[1:]
            y = b[1:]
            return ver_comp(x,y)

def solution(l):
    # Your code here
    output = []
    l_parsed = []
    m = len(l)
    
    # convert string-versions to list-versions
    for i in l:
        j = i.split('.')
        j = [int(k) for k in j]
        l_parsed.append(j)
    
    # sort
    s = sorted(l_parsed, key=functools.cmp_to_key(ver_comp))
    
    # convert list-versions to string-versions
    for i in range(m):
        s[i] = [str(j) for j in s[i]]
        j = '.'.join(s[i])
        output.append(j)

    return output
    
    
    
print(solution(["1.1.2", "1.0", "1.3.3", "1.0.12", "1.0.2"]))
    

            
    
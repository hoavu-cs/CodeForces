
def get_first_different_char(s1, s2):
    # find the first different character in s1 and s2
    # here, assume that s1 is before s2 in the author list
    n, m = len(s1), len(s2)

    for i in range(min(n, m)):
        if s1[i] != s2[i]:
            return s1[i], s2[i]

# standard DFS where we keep track of post-order traversal
# the topological sort of the graph is the reverse of the post-order traversal
def explore(u, adj, visited, sorted_list):
    visited.add(u)
    for v in adj[u]:
        if v not in visited:
            explore(v, adj, visited, sorted_list)

    sorted_list.append(u)

def dfs(adj, visited, sorted_list):
    for u in adj:
        if u not in visited:
            explore(u, adj, visited, sorted_list)
    
def main():
    n = int(input())
    arr = []

    lower_case_latin = [chr(i) for i in range(97, 123)]
    adj = {letter: [] for letter in lower_case_latin}

    for _ in range(n):
        arr.append(input())
    
    for i in range(n):
        for j in range(i + 1, n):
            if arr[i] == arr[j] or arr[j].startswith(arr[i]):
                continue
            elif len(arr[i]) > len(arr[j]) and arr[i].startswith(arr[j]):
                print("Impossible")
                return

            a, b = get_first_different_char(arr[i], arr[j])
            
            if a is None:
                print("Impossible")
                return
            else:    
                adj[a].append(b)
    
    visited = set()
    sorted_list = []

    dfs(adj, visited, sorted_list)
    sorted_list = sorted_list[::-1]

    # Go through the adjacency list and check if the topological sort is valid
    for a in adj:
        for b in adj[a]:
            if sorted_list.index(a) > sorted_list.index(b):
                print("Impossible")
                return

    print("".join(sorted_list))

if __name__ == "__main__":
    main()
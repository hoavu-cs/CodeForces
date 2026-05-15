/*
	We want to construct q such that
	for every i, # {j > i: p_j > p_i, q_j > q_i } = d_i.
	Solution idea:
		- Let's go through indices in P of numbers in the permutation in decreasing order.
		- That is find idx(n), idx(n-1),..., idx(1)
		- For every such idx(k), we check that d[idx(k)] must be at least the number of elements larger
		than k to the right of idx(k) in P. If not, output -1 (FAIL).
		- Assume we never FAIL: start at idx(n), we put it in an array perm = [idx(n)]
		- Perm stores the ordering of the output for the indices in q
		- For example, if q =  [2, 3, 1, 5, 4], then perm = [idx(1), idx(2),idx(3),idx(4),idx(5)]
														= [3, 1, 2, 5, 4]
		- When we process element at idx(k), we need to make sure that element at idx(k) is smaller than exactly d[idx(k)]
		elements in perms that are to the right of it in p.
		We can insert into perm d[idx(k)] from the right.
		- For example:
		p = 2 3 1 4 5
		d = 2 2 1 1 0
		first, idx(5) = 5
		so we put 5 into perm; perm = [5]
		then, go to idx(4) = 4; since d[idx(4)] = 1, we put it to the left of 5 (which happens to be to the right of 4 in p); perm = [4, 5]
		then, go to idx(3) = 2; since d[idx(3)] = 2, we put it to the left of 4 (since 4, 5 are larger than it in p); perm = [2, 4, 5]
		then, go to idx(2) = 1; since d[idx(2)] = 2, we insert it to the right place in perm; perm = [2, 1, 4, 5]
		then, go to idx(1) = 3; since d[idx(1)] = 1, we insert it to the right place in perm; perm = [2, 1, 4, 3, 5]
		Think of perm as the correct ordering of the indices in q based on the values it holds.
		That is number at index 5 should be largest, number at index 3 should be second largest,...
*/

package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	scanner.Scan()
	T, _ := strconv.Atoi(scanner.Text())
	for T > 0 {
		scanner.Scan()
		scanner.Scan()
		line := scanner.Text()
		parts := strings.Fields(line)
		n := len(parts)
		p := make([]int, n)
		d := make([]int, n)

		// read in array p
		for idx, token := range parts {
			p[idx], _ = strconv.Atoi(token)
		}

		scanner.Scan()
		line = scanner.Text()
		parts = strings.Fields(line)
		// read in array d
		for idx, token := range parts {
			d[idx], _ = strconv.Atoi(token)
		}

		// Go through elements in p, map value to positions
		pos := make([]int, n+1)
		for i := 0; i < n; i++ {
			pos[p[i]] = i // index of value p[i] is i
		}

		// For through each value k = n, n-1,..., 1, compute the numbers of
		// elements to the right of k in p and count how many of them are greater than k
		impossible := false
		for k := n; k >= 1; k-- {
			count := 0
			for j := pos[k] + 1; j < n; j++ {
				if p[j] > k {
					count += 1
				}
			}
			if count < d[pos[k]] {
				// if the number of elements > k to the righ to of it is smaller than d[pos[k]]
				// no solution exists
				impossible = true
			}
		}

		if impossible {
			fmt.Println("-1")
		} else {
			var perm []int
			for k := n; k >= 1; k-- {
				i := pos[k] // index of value k
				count := 0  // find the right position to insert, we want to insert i so that i is to the left of t larger elements in p
				insert_position := len(perm)
				if d[i] > 0 {
					for k2 := len(perm) - 1; k2 >= 0; k2-- {
						if perm[k2] > i {
							count++
						}
						if count == d[i] {
							insert_position = k2
							break
						}
					}
				}

				perm = append(perm, 0)
				copy(perm[insert_position+1:], perm[insert_position:])
				perm[insert_position] = i
			}

			output := make([]int, n)
			for i, v := range perm {
				output[v] = i
			}
			for i := range output {
				fmt.Print(output[i]+1, " ")
			}
			fmt.Println()

		}

		T--
	}
}

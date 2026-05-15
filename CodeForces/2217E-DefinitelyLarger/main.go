/*
   We are given a permutation p[1..n] and an array d[1..n].
   We want to construct a permutation q[1..n] such that for every index i,

       #{ j : j > i, p[j] > p[i], q[j] > q[i] } = d[i].

   Let pos[x] be the index where p[pos[x]] = x.

   We process values of p in decreasing order: n, n - 1, ..., 1.
   Suppose we are currently processing value k, and let

       i = pos[k].

   At this moment, all indices already inserted correspond exactly to values
   larger than k in p. Let A be the current list of inserted indices, ordered
   by increasing q-value.

   For the current index i, the only indices that can contribute to d[i] are

       S_i = { j in A : j > i }.

   These are exactly the indices j such that

       j > i and p[j] > p[i].

   Therefore, it is necessary that

       d[i] <= |S_i|.

   If d[i] > |S_i|, then no valid q exists.

   Otherwise, we insert i into A so that exactly d[i] elements of S_i appear
   after i in A.

   More explicitly, let the positions of the elements of S_i inside A be

       r_1 < r_2 < ... < r_m,

   where m = |S_i|.

   We insert i immediately before r_{m - d[i] + 1}.
   If d[i] = 0, we insert i after r_m.

   After this insertion, exactly d[i] indices j with j > i and p[j] > p[i]
   are placed after i in A, which means exactly d[i] of them will satisfy
   q[j] > q[i].

   Since future inserted elements have smaller p-values, they can never affect
   the already fixed condition for any processed index.

   After all indices are inserted, A gives the increasing order of q-values.
   That is, if

       A = [a_1, a_2, ..., a_n],

   then we assign

       q[a_t] = t.

   Example:

       p = [2, 3, 1, 4, 5]
       d = [2, 2, 1, 1, 0]

       Process values in order 5, 4, 3, 2, 1.

       pos[5] = 5:
           A = [5]

       pos[4] = 4:
           S_4 = {5}, d[4] = 1
           Insert 4 before 5:
           A = [4, 5]

       pos[3] = 2:
           S_2 = {4, 5}, d[2] = 2
           Insert 2 before both:
           A = [2, 4, 5]

       pos[2] = 1:
           S_1 = {2, 4, 5}, d[1] = 2
           Insert 1 so exactly two of them are after it:
           A = [2, 1, 4, 5]

       pos[1] = 3:
           S_3 = {4, 5}, d[3] = 1
           Insert 3 so exactly one of them is after it:
           A = [2, 1, 4, 3, 5]

       Therefore:
           q[2] = 1
           q[1] = 2
           q[4] = 3
           q[3] = 4
           q[5] = 5

       So q = [2, 1, 4, 3, 5].
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

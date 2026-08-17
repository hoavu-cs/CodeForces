package main

import (
	"bufio"
	"fmt"
	"os"
	"slices"
)

type SuccessorDSU struct {
	parent []int
}

func NewSuccessorDSU(n int) *SuccessorDSU {
	parent := make([]int, n+1)

	for i := 0; i <= n; i++ {
		parent[i] = i
	}

	return &SuccessorDSU{
		parent: parent,
	}
}

func (d *SuccessorDSU) Find(x int) int {
	if d.parent[x] != x {
		d.parent[x] = d.Find(d.parent[x])
	}
	return d.parent[x]
}

// Remove marks index x as used.
func (d *SuccessorDSU) Remove(x int) {
	d.parent[x] = d.Find(x + 1)
}

func main() {
	reader := bufio.NewReader(os.Stdin)
	writer := bufio.NewWriter(os.Stdout)

	var T int
	fmt.Fscan(reader, &T)

	for T > 0 {
		var n int
		fmt.Fscan(reader, &n)

		b := make([]int, n)
		a := make([]int, n)
		impossible := false

		for i := 0; i < n; i++ {
			fmt.Fscan(reader, &b[i])
		}

		// since b_i = a_i - a_(i-1), we have a_i = b_i + a_(i-1)
		// Greedy approach: find smallest remaining b_i such that a_(i-1) + b_i > 0
		slices.Sort(b)
		prefixSum := 0
		dsu := NewSuccessorDSU(n)

		for i := 0; i < n; i++ {
			left := 0
			right := n - 1
			idx := n

			for left <= right {
				mid := (left + right) / 2
				if prefixSum+b[mid] > 0 {
					right = mid - 1
					idx = mid
				} else {
					left = mid + 1
				}
			}

			if idx == n {
				impossible = true
				break
			} else {
				idx = dsu.Find(idx)
				if idx == n {
					impossible = true
					break
				}
				prefixSum += b[idx]
				dsu.Remove(idx)
				a[i] = prefixSum
			}
		}

		if impossible {
			fmt.Fprintln(writer, -1)
		} else {
			for i := 0; i < n; i++ {
				fmt.Fprint(writer, a[i], " ")
			}
			fmt.Fprintln(writer)
		}
		writer.Flush()
		T--
	}

}

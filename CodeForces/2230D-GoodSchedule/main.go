package main

import (
	"bufio"
	"fmt"
	"os"
)

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}

func main() {
	reader := bufio.NewReader(os.Stdin)
	writer := bufio.NewWriter(os.Stdout)
	defer writer.Flush()

	var T int
	fmt.Fscan(reader, &T)

	for T > 0 {
		var n int
		fmt.Fscan(reader, &n)
		a := make([]int, n)
		b := make([]int, n)
		nextA := make([]int, n)
		nextB := make([]int, n)
		nextOneA := make([]int, n+1)
		nextOneB := make([]int, n+1)
		lastOccurenceA := make([]int, n+2)
		lastOccurenceB := make([]int, n+2)

		for i := 0; i <= n+1; i++ {
			lastOccurenceA[i] = -1
			lastOccurenceB[i] = -1
		}

		for i := 0; i < n; i++ {
			fmt.Fscan(reader, &a[i])
		}
		for i := 0; i < n; i++ {
			fmt.Fscan(reader, &b[i])
		}

		nextOneA[n] = n
		nextOneB[n] = n

		for i := n - 1; i >= 0; i-- {
			nextA[i] = lastOccurenceA[a[i]+1]
			nextB[i] = lastOccurenceB[b[i]+1]
			lastOccurenceA[a[i]] = i
			lastOccurenceB[b[i]] = i

			if a[i] == 1 {
				nextOneA[i] = i
			} else {
				nextOneA[i] = nextOneA[i+1]
			}

			if b[i] == 1 {
				nextOneB[i] = i
			} else {
				nextOneB[i] = nextOneB[i+1]
			}
		}

		bad := make([]int, n+1)
		bad[n] = n
		for i := n - 1; i >= 0; i-- {
			if a[i] != b[i] {
				bad[i] = i
			} else {
				nA := nextA[i]
				nB := nextB[i]
				if nA == -1 && nB == -1 {
					bad[i] = n
				} else if nA == -1 {
					bad[i] = nB
				} else if nB == -1 {
					bad[i] = nA
				} else if nA == nB {
					bad[i] = bad[nA]
				} else {
					bad[i] = min(nA, nB)
				}
			}
		}

		ans := 0
		for i := n - 1; i >= 0; i-- {
			n1a := nextOneA[i]
			n1b := nextOneB[i]
			if n1a == n1b {
				ans += bad[n1a] - i
			} else {
				ans += min(n1a, n1b) - i
			}
		}

		fmt.Fprintln(writer, ans)
		T--
	}
}

package main

import "fmt"

var nodes = [17][17]int{
	/*      00  01  02  03  04  05  06  07  08  09  10  11  12  13  14  15  16*/
	/*00*/ {00, 01, 00, 00, 00, 00, 00, 00, 01, 00, 00, 00, 00, 00, 00, 00, 00},
	/*01*/ {01, 00, 02, 00, 00, 00, 00, 01, 00, 00, 00, 00, 00, 00, 00, 00, 00},
	/*02*/ {00, 02, 00, 01, 00, 01, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00},
	/*03*/ {00, 00, 01, 00, 01, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00},
	/*04*/ {00, 00, 00, 01, 00, 01, 00, 00, 00, 00, 00, 00, 00, 00, 00, 01, 00},
	/*05*/ {00, 00, 01, 00, 01, 00, 01, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00},
	/*06*/ {00, 00, 00, 00, 00, 01, 00, 01, 00, 00, 00, 00, 00, 00, 02, 00, 00},
	/*07*/ {00, 01, 00, 00, 00, 00, 01, 00, 01, 00, 00, 00, 00, 00, 00, 00, 00},
	/*08*/ {01, 00, 00, 00, 00, 00, 00, 01, 00, 01, 00, 00, 00, 00, 00, 00, 00},
	/*09*/ {00, 00, 00, 00, 00, 00, 00, 00, 01, 00, 02, 03, 00, 00, 00, 00, 00},
	/*10*/ {00, 00, 00, 00, 00, 00, 00, 00, 00, 02, 00, 01, 00, 00, 01, 00, 00},
	/*11*/ {00, 00, 00, 00, 00, 00, 00, 00, 00, 03, 01, 00, 02, 00, 00, 00, 00},
	/*12*/ {00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 02, 00, 01, 00, 00, 01},
	/*13*/ {00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 01, 00, 01, 02, 00},
	/*14*/ {00, 00, 00, 00, 00, 00, 02, 00, 00, 00, 01, 00, 00, 01, 00, 00, 00},
	/*15*/ {00, 00, 00, 00, 01, 00, 00, 00, 00, 00, 00, 00, 00, 02, 00, 00, 02},
	/*16*/ {00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 01, 00, 00, 02, 00},
}

const (
	istart = 0
	iend   = 16
)

func max(x int, y int) int {
	if x > y {
		return x
	} else {
		return y
	}
}

func getMaxPathLength(n [17][17]int, start int, end int, c int) (int, []int) {
	if start == end {
		return c, []int{end}
	}
	var retpath []int
	max_cost := c
	for j := range n[start] {
		if n[start][j] != 0 {
			s := n
			s[start][j] = 0
			s[j][start] = 0
			tmp, pth := getMaxPathLength(s, j, end, c+n[start][j])
			if tmp > max_cost {
				retpath = pth
				max_cost = tmp
			}
		}
	}
	return max_cost, append(retpath, start)
}

func main() {
	fmt.Println(getMaxPathLength(nodes, istart, iend, 0))
}
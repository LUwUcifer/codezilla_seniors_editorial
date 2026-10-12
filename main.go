package main

import "fmt"

func main() {
	//n, arr := generatePattern()
	//
	//fmt.Println(n)
	//for i := 0; i < n; i++ {
	//	fmt.Println(len(arr[i]))
	//	for _, d := range arr[i] {
	//		fmt.Print(d, " ")
	//	}
	//	fmt.Println()
	//}

	grid := make([][]int, 12)
	grid[0] = []int{1, 3, 5, 8}
	grid[1] = []int{0, 10}
	grid[2] = []int{4}
	grid[3] = []int{0, 8}
	grid[4] = []int{2, 6}
	grid[5] = []int{0, 11}
	grid[6] = []int{4, 7}
	grid[7] = []int{6, 9}
	grid[8] = []int{0, 3, 9}
	grid[9] = []int{7, 8}
	grid[10] = []int{1}
	grid[11] = []int{5}

	fmt.Println(shortestPathLength(grid))
}

package main

import "fmt"

func main() {
	_, r1Values, r2Values := gridGenerator()
	grid := [][]int{r1Values, r2Values}
	fmt.Println()
	fmt.Println(gridGeneratorAnswer(grid))
}

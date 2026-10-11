package main

import (
	"fmt"
	"math"
	"math/rand/v2"
)

func gridGenerator() (int, []int, []int) {
	var gridSize = rand.IntN(100)
	gridSize++

	value := func() []int {
		array := make([]int, gridSize)
		for i := 0; i < gridSize; i++ {
			array[i] = rand.IntN(1000)
		}
		return array
	}

	row1Value := value()
	row2Value := value()

	fmt.Println(gridSize)
	for i := 0; i < gridSize; i++ {
		fmt.Print(row1Value[i], " ")
	}
	fmt.Println()
	for i := 0; i < gridSize; i++ {
		fmt.Print(row2Value[i], " ")
	}

	return gridSize, row1Value, row2Value
}

func gridGeneratorAnswer(grid [][]int) int64 {
	var topSum, bottomSum int64
	for _, v := range grid[0] {
		topSum += int64(v)
	}
	ans := int64(math.MaxInt64)
	for i := range grid[0] {
		topSum -= int64(grid[0][i])
		ans = min(ans, max(topSum, bottomSum)) // Go 1.21+ builtins
		bottomSum += int64(grid[1][i])
	}
	return ans
}

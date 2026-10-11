package main

import "fmt"

func main() {
	n, k := boardGenerator()
	fmt.Printf("%d %d\n", n, k)
	fmt.Println(bishopPlacements(n, k))
}

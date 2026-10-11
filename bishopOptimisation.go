package main

import "math/rand/v2"

const mod = 1000000007

func boardGenerator() (N, K int) {
	n := rand.IntN(150)
	n += 50

	k := rand.IntN(100)

	return n, k
}

// squares returns the number of squares on diagonal band i.
func squares(i int) int {
	if i&1 == 1 {
		return i/4*2 + 1
	}
	return (i-1)/4*2 + 2
}

func bishopPlacements(N, K int) int {
	if K > 2*N-1 {
		return 0
	}

	D := make([][]int, N*2)
	for i := range D {
		D[i] = make([]int, K+1)
		D[i][0] = 1
	}
	D[1][1] = 1

	for i := 2; i < N*2; i++ {
		for j := 1; j <= K; j++ {
			D[i][j] = (D[i-2][j] + D[i-2][j-1]*(squares(i)-j+1)) % mod
		}
	}

	ans := 0
	for i := 0; i <= K; i++ {
		ans = (ans + D[N*2-1][i]*D[N*2-2][K-i]) % mod
	}
	return ans
}

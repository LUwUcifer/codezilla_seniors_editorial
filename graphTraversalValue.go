package main

import (
	"math/rand"
	"sort"
)

func generatePattern() (int, [][]int) {
	n := rand.Intn(12) + 1
	return n, GenerateGraph(n)
}

func GenerateGraph(n int) [][]int {
	adj := make([]map[int]bool, n)
	for i := range adj {
		adj[i] = make(map[int]bool)
	}

	addEdge := func(a, b int) {
		adj[a][b] = true
		adj[b][a] = true
	}

	// 1. Random spanning tree: attach every node to a random earlier node.
	//    This guarantees the graph is connected. A shuffled labeling keeps
	//    the structure from always looking the same.
	perm := rand.Perm(n)
	for k := 1; k < n; k++ {
		parent := perm[rand.Intn(k)]
		addEdge(perm[k], parent)
	}

	// 2. Add a random number of extra edges (keeps it connected).
	maxEdges := n * (n - 1) / 2
	extra := 0
	if maxEdges > n-1 {
		extra = rand.Intn(maxEdges - (n - 1) + 1)
	}
	for tries := 0; extra > 0 && tries < 10*maxEdges+10; tries++ {
		a, b := rand.Intn(n), rand.Intn(n)
		if a == b || adj[a][b] {
			continue
		}
		addEdge(a, b)
		extra--
	}

	graph := make([][]int, n)
	for i := 0; i < n; i++ {
		graph[i] = make([]int, 0, len(adj[i]))
		for v := range adj[i] {
			graph[i] = append(graph[i], v)
		}
		sort.Ints(graph[i])
	}
	return graph
}

type State struct {
	mask, node, dist int
}

func shortestPathLength(graph [][]int) int {
	n := len(graph)
	allVisited := (1 << n) - 1
	var queue []State
	visited := make(map[int]bool)

	for i := 0; i < n; i++ {
		queue = append(queue, State{1 << i, i, 0})
		visited[(1<<i)*16+i] = true
	}

	for len(queue) > 0 {
		cur := queue[0]
		queue = queue[1:]

		if cur.mask == allVisited {
			return cur.dist
		}

		for _, neighbor := range graph[cur.node] {
			newMask := cur.mask | (1 << neighbor)
			hashValue := newMask*16 + neighbor

			if !visited[hashValue] {
				visited[hashValue] = true
				queue = append(queue, State{newMask, neighbor, cur.dist + 1})
			}
		}
	}

	return -1
}

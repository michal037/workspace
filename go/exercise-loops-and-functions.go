package main

import (
	"fmt"
	"math"
)

func sqrt(x float64) float64 {
	if x == 0 {
		return 0
	}

	if x < 0 {
		fmt.Println("cannot sqrt negative number: ", x)

		return math.NaN()
	}

	z := float64(x / 2)

	for i := 0; i < 10; i++ {
		z -= (z*z - x) / (2 * z)
	}

	return z
}

func main() {
	fmt.Println(sqrt(2))
	fmt.Println(sqrt(3))
	fmt.Println(sqrt(9))
}

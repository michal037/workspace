package main

import (
	"fmt"
	"math"
)

type errNegativeSqrt float64

func (e errNegativeSqrt) Error() string {
	return fmt.Sprint("cannot sqrt negative number: ", float64(e))
}

func sqrt(x float64) (float64, error) {
	if x == 0 {
		return 0, nil
	}

	if x < 0 {
		return math.NaN(), errNegativeSqrt(x)
	}

	z := float64(x / 2)

	for i := 0; i < 10; i++ {
		z -= (z*z - x) / (2 * z)
	}

	return z, nil
}

func main() {
	fmt.Println(sqrt(2))
	fmt.Println(sqrt(-2))
}

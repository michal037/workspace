package main

import "golang.org/x/tour/pic"

func picture(dx, dy int) [][]uint8 {
	pic := make([][]uint8, dy)

	for y := 0; y < dy; y++ {
		pic[y] = make([]uint8, dx)
	}

	for y := 0; y < dy; y++ {
		for x := 0; x < dx; x++ {
			pic[y][x] = uint8((x + y) / 2)
		}
	}

	return pic
}

func main() {
	pic.Show(picture)
}

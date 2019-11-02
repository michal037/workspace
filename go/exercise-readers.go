package main

import "golang.org/x/tour/reader"

type MyReader struct{}

func (r MyReader) Read(in []byte) (int, error) {
	for i := 0; i < len(in); i++ {
		in[i] = 'A'
	}

	return len(in), nil
}

func main() {
	reader.Validate(MyReader{})
}
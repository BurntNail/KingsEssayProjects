package main

import "fmt"

const (
	ASCII                       = " .:;+=xX$&"
	ASCII_LEN_MINUX_ONE         = len(ASCII) - 1
	WIDTH               int     = 100
	HEIGHT              int     = 70
	RE_START            float32 = -2.0
	RE_END              float32 = 1.0
	IM_START            float32 = -1.0
	IM_END              float32 = 1.0
	MAX_ITERS           uint16  = 100
)

func main() {
	iter_counts := make([]uint16, WIDTH*HEIGHT)
	for y := 0; y < HEIGHT; y++ {
		for x := 0; x < WIDTH; x++ {
			real := ((float32(x) / float32(WIDTH)) * (RE_END - RE_START)) + RE_START
			imaginary := ((float32(y) / float32(HEIGHT)) * (IM_END - IM_START)) + IM_START

			var result uint16 = 0
			var re float32 = 0.0
			var im float32 = 0.0
			for re*re+im*im < 4.0 && result < MAX_ITERS {
				re = re*re - im*im + real
				im = re*im + re*im + imaginary
				result++
			}

			iter_counts[y*WIDTH+x] = result
		}
	}

	var max uint16 = 0
	var min uint16 = MAX_ITERS

	for _, iter := range iter_counts {
		if iter < MAX_ITERS && iter > max {
			max = iter
		} else if iter < min {
			min = iter
		}
	}

	diff := float32(max - min)
	msg := make([]rune, (WIDTH+1)*HEIGHT+1)

	row_i := 0
	for _, iter := range iter_counts {
		if iter == MAX_ITERS {
			msg = append(msg, rune(ASCII[ASCII_LEN_MINUX_ONE]))
		} else {
			mapped := iter - min

			pos := float32(mapped) / diff
			true_pos := int(pos * float32(ASCII_LEN_MINUX_ONE))

			msg = append(msg, rune(ASCII[true_pos]))
		}

		row_i++
		if row_i == WIDTH {
			row_i = 0
			msg = append(msg, '\n')
		}
	}

	fmt.Println(string(msg))
}

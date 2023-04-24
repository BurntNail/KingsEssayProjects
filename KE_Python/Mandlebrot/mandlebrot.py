from math import floor

ASCII = " .:;+=xX$&"
ASCII_LEN_MINUS_ONE = len(ASCII) - 1

WIDTH = 100
HEIGHT = 70

RE_START = -2
RE_END = 1
IM_START = -1
IM_END = 1

MAX_ITERS = 100

if __name__ == "__main__":
    iters = []
    for y in range(HEIGHT):
        for x in range(WIDTH):
            real = (x / WIDTH) * (RE_END - RE_START) + RE_START
            imaginary = (y / HEIGHT) * (IM_END - IM_START) + IM_START

            base_complex_number = complex(real, imaginary)

            eval_cmplx_no = complex(0, 0)
            iter_count = 0
            while ((eval_cmplx_no.real * eval_cmplx_no.real) + (eval_cmplx_no.imag * eval_cmplx_no.imag)) < 4.0 and iter_count < MAX_ITERS:
                eval_cmplx_no = (eval_cmplx_no * eval_cmplx_no) + base_complex_number
                iter_count += 1

            iters.append(iter_count)

    max_from_list = max(iters)
    min_from_list = min(iters)
    diff = max_from_list - min_from_list

    print(f"Max is {max_from_list}, min is {min_from_list}, diff = {diff}.")

    s = ""
    row_pos = 0
    for iter_count in iters:
        if iter_count == MAX_ITERS:
            s += ASCII[ASCII_LEN_MINUS_ONE]
        else:
            mapped = iter_count - min_from_list
            pos = mapped / diff
            s += ASCII[floor(pos * ASCII_LEN_MINUS_ONE)]

        row_pos += 1
        if row_pos == WIDTH:
            row_pos = 0
            s += "\n"

    print(s)

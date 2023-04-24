package main

type Backing uint32

const BACKING_BITS = 32
const BACKING_MAX = 1<<BACKING_BITS - 1

type ExpandableBitVec struct {
	backing []Backing
}

func new_ebv(size int) ExpandableBitVec {
	return ExpandableBitVec{backing: make([]Backing, size)}
}

func (ebv *ExpandableBitVec) expand_to_size(size int) {
	old_len := len(ebv.backing)
	new_len := size/BACKING_BITS + 1

	if new_len > old_len {
		for i := 0; i < (new_len - old_len); i++ {
			ebv.backing = append(ebv.backing, 0)
		}
	}
}

func (ebv *ExpandableBitVec) index(index int) bool {
	ebv.expand_to_size(index + 1)
	vec_ind := index / BACKING_BITS
	backing_ind := index % BACKING_BITS

	return (ebv.backing[vec_ind] & (1 << backing_ind)) > 0
}

func (ebv *ExpandableBitVec) set(index int, state bool) {
	ebv.expand_to_size(index + 1)

	vec_ind := index / BACKING_BITS
	backing_ind := index % BACKING_BITS

	if state {
		ebv.backing[vec_ind] |= 1 << backing_ind
	} else {
		ebv.backing[vec_ind] &= BACKING_MAX - (1 << backing_ind)
	}
}

func (ebv *ExpandableBitVec) clear() {
	for i := 0; i < len(ebv.backing); i++ {
		ebv.backing[i] = 0
	}
}

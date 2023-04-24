BIT_COUNT = 32  # Python seems to dynamically switch, but if I stay consistent it should work...
MAX_IN_BC = (1 << BIT_COUNT) - 1


class ExpandableBitVec:

    def __init__(self, size):
        true_size = size // BIT_COUNT + 1
        self.backing = []
        for _i in range(true_size):
            self.backing.append(0)

    def extend_to_size (self, new_size):
        new_true_size = new_size // BIT_COUNT + 1
        current_size = len(self.backing)
        if new_true_size > current_size:
            for _i in range(new_true_size - current_size):
                self.backing.append(0)

    def clear (self):
        for i in range(len(self.backing)):
            self.backing[i] = 0

    def __getitem__(self, item):
        self.extend_to_size(item + 1)

        vec_ind = item // BIT_COUNT
        backing_ind = item % BIT_COUNT

        return (self.backing[vec_ind] & (1 << backing_ind)) > 0

    def __setitem__(self, key, value):
        self.extend_to_size(key + 1)

        vec_ind = key // BIT_COUNT
        backing_ind = key % BIT_COUNT

        if value:
            self.backing[vec_ind] |= 1 << backing_ind
        else:
            self.backing[vec_ind] &= MAX_IN_BC - (1 << backing_ind)

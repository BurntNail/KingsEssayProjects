package com.jackmaguire;

import java.util.ArrayList;
import java.util.List;

public class ExpandableBitVec {
    public final int NO_BITS = Integer.SIZE;

    private List<Integer> backing;

    public ExpandableBitVec (int size) {
        int true_size = size / NO_BITS + 1;
        backing = new ArrayList<>();
        for (int i = 0; i < true_size; i++)
        {
            backing.add(0);
        }
    }

    public void extend_to_size (int new_size)
    {
        int current_len = backing.size();
        int new_len = new_size / NO_BITS + 1;
        if (new_len > current_len)
        {
            for (int i = 0; i < new_len - current_len; i++)
            {
                backing.add(0);
            }
        }
    }

    public boolean index (int index)
    {
        extend_to_size(index + 1);

        int vec_ind = index / NO_BITS;
        int backing_ind = index % NO_BITS;

        return (backing.get(vec_ind) & (1 << backing_ind)) > 0;
    }

    public void set (int index)
    {
        extend_to_size(index + 1);

        int vec_ind = index / NO_BITS;
        int backing_ind = index % NO_BITS;

        backing.set(vec_ind, backing.get(vec_ind) | (1 << backing_ind));
    }

    public void unset (int index)
    {
        extend_to_size(index + 1);

        int vec_ind = index / NO_BITS;
        int backing_ind = index % NO_BITS;

        backing.set(vec_ind, backing.get(vec_ind) & Integer.MAX_VALUE - (1 << backing_ind));
    }

    public void clear ()
    {
        for (int i = 0; i < backing.size(); i++) {
            backing.set(i, 0);
        }
    }
}

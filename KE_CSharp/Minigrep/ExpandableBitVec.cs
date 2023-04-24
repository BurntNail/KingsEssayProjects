using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Minigrep
{
    class ExpandableBitVec
    {
        public const int NO_BITS = 32;

        private List<int> backing;

        public ExpandableBitVec (int size)
        {
            int true_size = size / NO_BITS + 1;
            backing = new List<int> ();
            for (int i = 0; i < true_size; i++)
            {
                backing.Add(0);
            }
        }

        public void extend_to_size (int new_size)
        {
            int current_len = backing.Count();
            int new_len = new_size / NO_BITS + 1;
            if (new_len > current_len)
            {
                for (int i = 0; i < new_len - current_len; i++)
                {
                    backing.Add(0);
                }
            }
        }

        public bool index (int index)
        {
            extend_to_size(index + 1);

            int vec_ind = index / NO_BITS;
            int backing_ind = index % NO_BITS;

            return (backing[vec_ind] & (1 << backing_ind)) > 0;
        }

        public void set (int index)
        {
            extend_to_size(index + 1);

            int vec_ind = index / NO_BITS;
            int backing_ind = index % NO_BITS;

            backing[vec_ind] |= 1 << backing_ind;
        }

        public void unset (int index)
        {
            extend_to_size(index + 1);

            int vec_ind = index / NO_BITS;
            int backing_ind = index % NO_BITS;

            backing[vec_ind] &= int.MaxValue - (1 << backing_ind);
        }

        public void clear ()
        {
            backing.Clear();
        }
    }
}

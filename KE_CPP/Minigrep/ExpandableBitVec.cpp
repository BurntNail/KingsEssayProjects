#include "ExpandableBitVec.h"
#include <limits>

ExpandableBitVec::ExpandableBitVec(size_t size)
{
	m_backing.reserve(size);
	for (int i = 0; i < size; i++) {
		m_backing.push_back(0);
	}
}

void ExpandableBitVec::ExtendToSize(size_t size)
{
	size_t old_len = m_backing.size();
	size_t new_len = size / BITS + 1;
	if (new_len > old_len) {
		for (int i = 0; i < new_len - old_len; i++) {
			m_backing.push_back(0);
		}
	}
}

bool ExpandableBitVec::Index(size_t index)
{
	ExtendToSize(index + 1);

	size_t vec_ind = index / BITS;
	size_t backing_ind = index % BITS;

	return (m_backing[vec_ind] & (1 << backing_ind)) > 0;
}

void ExpandableBitVec::Set(size_t index)
{
	ExtendToSize(index + 1);

	size_t vec_ind = index / BITS;
	size_t backing_ind = index % BITS;

	m_backing[vec_ind] |= 1 << backing_ind;
}

void ExpandableBitVec::Unset(size_t index)
{
	ExtendToSize(index + 1);

	size_t vec_ind = index / BITS;
	size_t backing_ind = index % BITS;

	m_backing[vec_ind] &= std::numeric_limits<uint32_t>::max() - (1 << backing_ind);
}

void ExpandableBitVec::Clear()
{
	for (int i = 0; i < m_backing.size(); i++) {
		m_backing[i] = 0;
	}
}

#pragma once

#include <cstdio>
#include <vector>

class ExpandableBitVec
{
private:
	const size_t BITS = 32;
	std::vector<uint32_t> m_backing;
public:
	ExpandableBitVec(size_t size);
	void ExtendToSize(size_t size);
	bool Index(size_t index);
	void Set(size_t index);
	void Unset(size_t index);
	void Clear();
};


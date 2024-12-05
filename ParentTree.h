#pragma once
template <class T>
class ParentTree
{
public:
	virtual void insert(const T& data, const long long& rowIndex) = 0;
	virtual void remove(const T& data) = 0;
	virtual void print() = 0;
};
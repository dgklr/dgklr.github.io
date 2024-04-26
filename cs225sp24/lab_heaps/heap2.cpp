
//#include "heap.h"
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    return 2 * currentIdx;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    return 2 * currentIdx + 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    return currentIdx / 2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    return currentIdx * 2 < _elems.size();
}



template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    std::cout << "call heapifydown id " << currentIdx << std::endl;
    if (!hasAChild(currentIdx)) return;
    size_t childIdx = maxPriorityChild(currentIdx);
    std::cout << "test" << currentIdx << ' ' << _elems[currentIdx] << ' ' << _elems[childIdx] << std::endl;
    if (!higherPriority(_elems[currentIdx], _elems[childIdx])) {
        std::cout << "swap" << std::endl;
        std::swap(_elems[currentIdx], _elems[childIdx]);
        heapifyDown(childIdx);
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    _elems.push_back(T());
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{
    std::cout << "call build heap" << std::endl;
	_elems.push_back(T());
	for(size_t i = 0; i < elems.size(); i++)
	{
		_elems.push_back(elems[i]);
	}
	for(size_t i = parent(_elems.size()-1); i > 0; i--)
	{
		heapifyDown(i);
	}
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    if (_elems.size() == 1) return T(); // or panic
    T ret = _elems[1];
    _elems[1] = *_elems.rbegin();
    _elems.pop_back();
    heapifyDown(1);
    return ret;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    if (_elems.size() == 1) return T();
    return _elems[1];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    _elems.push_back(elem);
    heapifyUp(_elems.size() - 1);
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    return (_elems.size() == 1);
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
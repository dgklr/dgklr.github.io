#include "list.h"
#include <iostream>
/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List() {
    clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear() {
    for (auto i = head_; i != nullptr;) {
        auto tmp = i->next;
        delete i;
        i = tmp;
    }
    head_ = tail_ = nullptr;
    length_ = 0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const& ndata) {
    ListNode* tmp = new ListNode(ndata);
    if (length_ == 0)
        head_ = tail_ = tmp;
    else
        tmp->next = head_,
        head_->prev = tmp,
        head_ = tmp;
    length_ ++;
  /// @todo Graded in MP3.1
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T& ndata) {
    ListNode* tmp = new ListNode(ndata);
    if (length_ == 0)
        head_ = tail_ = tmp;
    else
        tmp->prev = tail_,
        tail_->next = tmp,
        tail_ = tmp;
    length_ ++;
  /// @todo Graded in MP3.1
}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode*& startPoint, ListNode*& endPoint) {
    auto tmpst = startPoint, tmped = endPoint;
    if (startPoint == endPoint) return; // nothing to do, and also avoid nullptr case.
    if (startPoint == head_) {
        head_ = tmped;
    } else {
        tmpst->prev->next = tmped;
    }
    if (tmped == tail_) {
        tail_ = startPoint;
    } else {
        tmped->next->prev = tmpst;
    }
    for (auto i = tmpst; i != tmped; i = i -> prev) {
        swap(i->next, i->prev);
    }
    swap(tmped->next, tmped->prev);
    auto rec = tmpst->next;
    tmpst->next = tmped->prev;
    tmped->prev = rec;
    endPoint = tmpst;
    startPoint = tmped;
    /// @todo Graded in MP3.1
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n) {
    auto st = head_, ed = st;
    while (st != nullptr) {
        // move n steps if not touch the end
        int tmp = n-1;
        while (ed->next != nullptr && tmp > 0) tmp --, ed = ed -> next;
        reverse(st, ed);
        //cout << st -> data << ' ' << ed -> data << endl;
        st = ed -> next;
        ed = st;
    }
  /// @todo Graded in MP3.1
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall() {
    auto curr = head_;
    while (curr != tail_ && curr != nullptr && curr->next != tail_ && curr->next != nullptr) {
        //cout << curr -> data << ' ' << tail_ -> data << endl;
        auto tmp = curr;
        curr = curr -> next;
        tmp -> next = curr -> next;
        curr -> next -> prev = tmp; // delete in the list
        tail_ -> next = curr;
        curr -> prev = tail_;
        curr -> next = nullptr;
        tail_ = curr;
        curr = tmp -> next;
    }
  /// @todo Graded in MP3.1
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode* secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_->next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode* List<T>::split(ListNode* start, int splitPoint) {
    if (splitPoint >= length_)
        return NULL;

    if (splitPoint <= 0) {
        return start;
    }

    auto now = start;

    while (splitPoint --) {
        now = now -> next;
    }

    now -> prev -> next = nullptr;
    now -> prev = nullptr;
    return now; 
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T>& otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* second) {
    if (first == nullptr) return second;
    if (second == nullptr) return first;
    if (second -> data < first -> data) swap(first, second); // guess what?
    auto ret = first;
    while (second != nullptr) {
        auto tmp = second -> next;
        if (first -> next == nullptr) {
            first -> next = second;
            second -> prev = first;
            return ret;
        }
        if (second -> data < first -> next -> data) {
            first -> next -> prev = second;
            second -> next = first -> next;
            first -> next = second;
            second -> prev = first;
            first = first -> next;
            second = tmp;
        } else {
            first = first -> next;
        }
    }
    return ret;
  /// @todo Graded in MP3.2
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode* start, int chainLength) {
    if (chainLength <= 1) return start;
    int dividePlace = chainLength / 2;
    auto secondHead = split(start, dividePlace);
    start = mergesort(start, dividePlace);
    secondHead = mergesort(secondHead, chainLength - dividePlace);
    start = merge(start, secondHead);
    return start;
    /// @todo Graded in MP3.2
}

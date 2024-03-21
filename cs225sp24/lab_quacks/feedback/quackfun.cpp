/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 *  stacks and queues portion of the lab.
 */

namespace QuackFun {

/**
 * Sums items in a stack.
 * @param s A stack holding values to sum.
 * @return The sum of all the elements in the stack, leaving the original
 *  stack in the same state (unchanged).
 *
 * @note You may modify the stack as long as you restore it to its original
 *  values.
 * @note You may use only two local variables of type T in your function.
 *  Note that this function is templatized on the stack's type, so stacks of
 *  objects overloading the + operator can be summed.
 * @note We are using the Standard Template Library (STL) stack in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint Think recursively!
 */
template <typename T>
T sum(stack<T>& s)
{
    if (s.size() == 0) return T();
    T top = s.top();
    s.pop();
    T presum = sum(s);
    s.push(top);
    return top + presum;
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 * @param q A queue of items to be scrambled
 *
 * @note Any "leftover" numbers should be handled as if their block was
 *  complete.
 * @note We are using the Standard Template Library (STL) queue in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint You'll want to make a local stack variable.
 */
template <typename T>
void scramble(queue<T>& q)
{
    unsigned cnt = 0, tmp = 1, now = 0, total = q.size();
    stack<T> s;
    queue<T> q2;
    while (now < total) {
        now ++;
        cnt ++;
        if (tmp & 1) {
            q2.push(q.front());
        } else {
            s.push(q.front());
        }
        q.pop();

        if (tmp == cnt) {
            while (s.size()) {
                q.push(s.top()), s.pop();
            } 
            while (q2.size()) {
                q.push(q2.front()), q2.pop();
            } 
            tmp ++;
            cnt = 0;
        }
    }
    while (s.size()) {
        q.push(s.top()), s.pop();
    } 
    while (q2.size()) {
        q.push(q2.front()), q2.pop();
    } 
}

/**
 * @return true if the parameter stack and queue contain only elements of
 *  exactly the same values in exactly the same order; false, otherwise.
 *
 * @note You may assume the stack and queue contain the same number of items!
 * @note There are restrictions for writing this function.
 * - Your function may not use any loops
 * - In your function you may only declare ONE local boolean variable to use in
 *   your return statement, and you may only declare TWO local variables of
 *   parametrized type T to use however you wish.
 * - No other local variables can be used.
 * - After execution of verifySame, the stack and queue must be unchanged. Be
 *   sure to comment your code VERY well.
 */
template <typename T>
bool verifySame(stack<T>& s, queue<T>& q)
{
    /**
     * This function does a very interesting job.
     * First, we assume we are checking that stack and queue are the same, and 
     * in this case, there must exist size of s and q is equal.
     * but the value of the top of s and front of q is not we want to check,
     * we need to cycle the q and let the last number to check with top of s.
     * So I make a counter to count how many time we want to cycle. When size
     * of s and size of q are not equal, we just continue to cycle the queue 
     * and let the stack decrease. We need to cycle exactly size - 1 times, so
     * when we meet size of s equal to 1, we need to return.
     * At this time, we need to check whether q is also only have one element.
     * if it does, we are checking stack and queue whether is same! So we need
     * to return whether it is the same.
     * After doing this, we finally can check whether their top or front is the
     * same, so we just check them.
     * Then, if they are the same, we can then check the other part of the s 
     * and q whether they are the same. so we pop the front and the top, and 
     * return the verifysame method.
     * And, don't forget to cycle the queue when checking they are the same.
     * 
     * Overall, we can see how the function works.
     * 
     * At start, 
     * s = 1 1 3 4 5;    q = 1 2 3 4 5;      s.size(), q.size() 5 5
     * then pop the s
     * s = 1 1 3 4;      q = 2 3 4 5 1;      s.size(), q.size() 4 5
     * ...
     * time to return
     * s = 1;            q = 5 1 2 3 4;      s.size(), q.size() 1 5 
     * And we get...
     * s = 1 1 3 4 5;    q = 5 1 2 3 4;      s.size(), q.size() 5 5
     * Here we check s.top() and q.front(). They are the same number, and 
     * remove them.
     * s = 1 1 3 4;      q = 1 2 3 4;        s.size(), q.size() 4 4
     * ...
     * s = 1 1 3 4;      q = 4 1 2 3;        s.size(), q.size() 4 4
     * same, so
     * s = 1 1 3;        q = 1 2 3;          s.size(), q.size() 3 3
     * then
     * s = 1 1;          q = 1 2;            s.size(), q.size() 2 2
     * here we find they are not the same.
     * return false;
    */
    if (s.size() == 0) return 1; // this value doesn't (does!) matter
    if (s.size() == 1 && q.size() == 1) return s.top() == q.front();
    if (s.size() == 1) return 1; // this value doesn't matter
    bool retval = true; // optional
    T stacktop = s.top();
    s.pop();
    verifySame(s, q); // cycle the q with s.size()-1 times.
    s.push(stacktop);
    T queuefront = q.front();
    q.pop();
    q.push(queuefront); // cycle the q
    queuefront = q.front();
    if (s.size() == q.size()) {
        if (stacktop == queuefront) { // their front and top is same
            s.pop();
            q.pop();
            retval = verifySame(s, q); // recursive method
            s.push(stacktop);
            q.push(queuefront); // don't forget to cycle
        } else {
            q.pop();
            q.push(queuefront); // cycle
            retval = 0;
        }
    }
    return retval;
}

}
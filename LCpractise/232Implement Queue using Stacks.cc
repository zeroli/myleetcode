class Queue {
public:
// for two stacks 1 and 2
// when push, enqueue to stack 1
// when pop, push all from stack1 to stack2, pop from stack2
    // Push element x to the back of queue.
    void push(int x) {
        s1.push(x);
    }

    // Removes the element from in front of queue.
    void pop(void) {
        transferData(s1, s2);
        s2.pop();
        transferData(s2, s1);
    }

    // Get the front element.
    int peek(void) { // how to deal with empty
        transferData(s1, s2);
        int r = s2.top();
        transferData(s2, s1);
        return r;
    }

    // Return whether the queue is empty.
    bool empty(void) {
        return s1.empty() || s1.empty();
    }
    
private:
    void transferData(stack<int>& src, stack<int>& tgt) {
        while (!src.empty()) {
            tgt.push(src.top());
            src.pop();
        }
    }
private:
    stack<int> s1, s2;
};
class MinStack {
public:
// use two stack, one for normal stack, the other one is for minimal, when there is a value not larger come in, push it in.
    stack<int> s;
    stack<int> smin;
    void push(int x) {
        s.push(x);
        if (smin.empty() || x <= smin.top()) smin.push(x);
    }

    void pop() {
        if (s.top() == smin.top()) smin.pop();
        s.pop();
    }

    int top() {
        return s.top();
    }

    int getMin() {
        return smin.top();
    }
};
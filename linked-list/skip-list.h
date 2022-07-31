#ifndef SKIP_LIST_H_
#define SKIP_LIST_H_

#include <random>
#include <cassert>

namespace ds {
struct Random {
    Random(int a, int b)
        : rd_(), gen_(rd_()), distrib_(a, b)
    { }

    int Get()
    {
        return distrib_(gen_);
    }
private:
    std::random_device rd_;
    std::mt19937 gen_;
    std::uniform_int_distribution<> distrib_;
};

struct SkipList {
    static constexpr int kMaxHeight = 12;
    struct Node {
        int key_;
        // more next nodes will be appended after `next`
        Node* next[1];

        explicit Node(int key)
            : key_(key)
        { }

        int Key() const {
            return key_;
        }
        Node* Next(int level) const {
            return next[level];
        }
        void SetNext(int level, Node* x) {
            next[level] = x;
        }
    };

    struct Iterator {
        explicit Iterator(const SkipList* const list, Node* node = nullptr)
            : list_(list), node_(node)
        { }

        Iterator operator ++() {
            SeekNext();
            return *this;
        }
        Iterator operator ++(int) {
            Iterator tmp = *this;
            ++tmp;
            return tmp;
        }

        int operator *() const {
            assert(node_);
            return node_->Key();
        }

        friend bool operator ==(const Iterator& it1, const Iterator& it2)
        {
            return it1.list_ == it2.list_ && it1.node_ == it2.node_;
        }
        friend bool operator !=(const Iterator& it1, const Iterator& it2)
        {
            return !(it1 == it2);
        }
    private:
        void SeekNext() {
            if (node_) {
                node_ = node_->Next(0);
            }
        }
        void SeekToFirst() {
            node_ = list_->head_->Next(0);
        }

        friend class SkipList;
    private:
        const SkipList* const list_;
        Node* node_;
    };

    SkipList()
        : head_(NewNode(-1, kMaxHeight))
        , max_height_(1)
        , random_(1, kMaxHeight)
    {

    }
    ~SkipList()
    {
        Node* cur = head_;
        while (cur) {
            auto next = cur->Next(0);
            DestroyNode(cur);
            cur = next;
        }
    }

    // API
    void Insert(int key)
    {
        int height = random_.Get();
        assert(height <= kMaxHeight);
        Node* x = NewNode(key, height);
        Node* prev[kMaxHeight];
        Node* y = FindGreaterEqual(key, prev);
        assert(y == nullptr || y->Key() > key);

        if (height > CurMaxHeight()) {
            for (int i = CurMaxHeight(); i < height; i++) {
                prev[i] = head_;
            }
            max_height_ = height;
        }
        // do insertion of singly-linked list for node x between prev and their next
        for (int i = 0; i < height; i++) {
            x->SetNext(i, prev[i]->Next(i));
            prev[i]->SetNext(i, x);
        }
    }

    bool Delete(int key)
    {
        Node* prev[kMaxHeight];
        Node* x = FindGreaterEqual(key, prev);
        assert(x == nullptr || x->Key() >= key);
        if (x && x->Key() == key) {  // found it
            // fixme: 怎么去更新max_height_？？？
            for (int i = 0; i < CurMaxHeight(); i++) {
                Node* y = prev[i]->Next(i);
                if (y && y->Key() == key) {
                    prev[i]->SetNext(i, y->Next(i));
                }
            }
            DestroyNode(x);
            return true;
        } else {
            return false;
        }
    }

    bool Contains(int key) const
    {
        Node* x = FindGreaterEqual(key, nullptr);
        if (x != nullptr && x->Key() == key) {
            return true;
        }
        return false;
    }

    // return the first key (min)
    int First() const
    {
        Node* x = head_->Next(0);
        if (x != nullptr) {
            return x->Key();
        }
        assert(0);
    }

    // return the last key (max)
    int Last() const
    {
        Node* x = FindLast();
        if (x != nullptr) {
            return x->Key();
        }
        assert(0);
    }

    Iterator begin() const {
        Iterator iter(this, nullptr);
        iter.SeekToFirst();
        return iter;
    }
    Iterator end() const {
        Iterator iter(this, nullptr);
        return iter;
    }

    friend std::ostream& operator <<(std::ostream& outstr, const SkipList& sl)
    {
        outstr << "[ ";
        for (auto&& n : sl) {
            outstr << n << " => ";
        }
        outstr << "null ]";
        return outstr;
    }
private:
    Node* NewNode(int key, int height)
    {
        char* buf = new char [sizeof(Node) + sizeof(Node*) * (height - 1)];
        Node* newnode = new (buf) Node(key);  // placement new
        for (int i = 0; i < height; i++) {
            newnode->SetNext(i, nullptr);
        }
        return newnode;
    }
    void DestroyNode(Node* x)
    {
        delete [] reinterpret_cast<char*>(x);
    }

    Node* FindGreaterEqual(int key, Node** prev) const
    {
        int level = CurMaxHeight() - 1;
        Node* x = head_;
        while (true) {
            Node* next = x->Next(level);
            if (next && next->Key() < key) {  // key is after next node
                x = next;  // keep searching this list
            } else {
                if (prev) {
                    prev[level] = x;
                }
                if (level == 0) {  // find the exact bigger node (the first bigger or equal to)
                    return next;
                }
                level--;  // switch to next level
            }
        }
    }

    // it may return head_ if all nodes are bigger than or equal to `key`
    Node* FindLessThan(int key) const
    {
        int level = CurMaxHeight() - 1;
        Node* x = head_;
        while (true) {
            Node* next = x->Next(level);
            if (next && next->Key() < key) {
                x = next;  // keep searching this list
            } else {
                if (level == 0) {
                    return x;  // return previous one
                }
                level--;  // switch to next level
            }
        }
    }
    Node* FindLast() const {
        int level = CurMaxHeight() - 1;
        Node* x = head_;
        while (true) {
            Node* next = x->Next(level);
            if (next) {
                x = next;  // keep iterating this list
            } else {
                if (level == 0) {
                    return x;  // return the last non-null node
                }
                level--;  // switch to next level
            }
        }
    }

    int CurMaxHeight() const
    {
        return max_height_;
    }
private:
    Node* head_;
    int max_height_;
    Random random_;
};
}  // namespace ds

#endif  // SKIP_LIST_H_

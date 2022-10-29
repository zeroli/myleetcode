#ifndef MIN_HEAP_H_
#define MIN_HEAP_H_

template <typename T>
struct MinHeap {
    MinHeap()
        : size_(0)
    { }

    MinHeap(const std::vector<T>& arr)
        : size_(arr.size())
    {
        data_.resize(size_);
        std::copy(arr.begin(), arr.end(), &data_[0]);
        for (int i = size_ / 2; i >= 0; i--) {
            ShiftDown(i);
        }
    }

    void Push(const T& x)
    {
        data_.resize(data_.size() + 1);
        data_[size_++] = x;
        ShiftUp(size_-1);
    }

    const T& Top() const
    {
        if (size_ > 0) {
            return data_[0];
        } else {
            throw std::out_of_range("out of range");
        }
    }

    void Pop()
    {
        if (size_ > 0) {
            std::swap(data_[0], data_[size_-1]);
            size_--;
            ShiftDown(0);
        }
    }

    int Size() const {
        return size_;
    }

    bool IsEmpty() const {
        return Size() == 0;
    }

    friend std::ostream& operator <<(std::ostream& outstr, const MinHeap& mh)
    {
        mh.Print(outstr);
        return outstr;
    }
private:
    void Print(std::ostream& outstr) const
    {
        outstr << std::vector<T>(&data_[0], &data_[size_]);
    }

    void ShiftUp(int idx)
    {
        while (idx > 0) {  // idx=0是堆顶，不再继续
            int parent = (idx - 1) / 2;
            if (data_[idx] < data_[parent]) {
                std::swap(data_[idx], data_[parent]);
                idx = parent;
            } else {
                break;
            }
        }
    }
    void ShiftDown(int idx)
    {
        while (idx < size_) {
            int left = idx * 2 + 1;
            int right = idx * 2 + 2;
            int swpidx = idx;
            if (left < size_ && data_[swpidx] > data_[left]) {
                swpidx = left;
            }
            if (right < size_ && data_[swpidx] > data_[right]) {
                swpidx = right;
            }
            if (idx == swpidx) {
                break;
            }
            std::swap(data_[idx], data_[swpidx]);
            idx = swpidx;
        }
    }
private:
    std::vector<T> data_;
    int size_ = 0;
};

#endif  // MIN_HEAP_H_

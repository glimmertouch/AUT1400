template<typename T>
T* make_shared(T&& t) {
    T* ptr = new T{t};
    return ptr;
}


template<typename T>
class SharedPtr {
private:
    T* _p;
    int* ref_count;

public:
    SharedPtr(T* ptr = nullptr): _p(ptr), ref_count(new int{1}) {}
    SharedPtr(const SharedPtr& sharedptr): _p(sharedptr._p), ref_count(sharedptr.ref_count) {
        (*ref_count)++;
    }

    SharedPtr& operator=(const SharedPtr& ptr) {
        if(&ptr == this) {
            return *this;
        }
        _p = ptr._p;
        ref_count = ptr.ref_count;
        (*ref_count)++;
        return *this;
    }

    int use_count() const {
        if (ref_count == nullptr) {
            return 0;
        }
        return *ref_count;
    }

    T& operator*() {
        return *_p;
    }

    T* operator->() {
        return _p;
    }

    operator bool() const {
        return _p != nullptr;
    }

    T* get() {
        return _p;
    }

    void reset() {
        if(--(*ref_count) == 0) {
            delete _p;
            delete ref_count;
        } 
        _p = nullptr;
        ref_count = nullptr;
    }

    void reset(T* ptr) {
        if(--(*ref_count) == 0) {
            delete _p;
            delete ref_count;
        } 
        _p = ptr;
        ref_count = new int{1};

    }

    ~SharedPtr() {
        if(ref_count == nullptr) {
            return;
        }
        if(--(*ref_count) == 0) {
            delete _p;
            delete ref_count;
        }
        _p = nullptr;
        ref_count = nullptr;
    }

};
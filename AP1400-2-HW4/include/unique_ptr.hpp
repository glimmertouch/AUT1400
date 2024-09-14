template<typename T>
T* make_unique(T&& t) {
    T* ptr = new T{t};
    return ptr;
}


template<typename T>
class UniquePtr {
private:
    T* _p;


public:
    UniquePtr(T* ptr = nullptr) : _p(ptr) {}
    UniquePtr(const UniquePtr& ptr) {
        throw std::runtime_error("Not allowed to replicate the UniquePtr!\n");
    }

    UniquePtr& operator=(const UniquePtr& ptr) {
        throw std::runtime_error("Not allowed to replicate the UniquePtr!\n");
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
        delete _p;
        _p = nullptr;
    }

    void reset(T* ptr) {
        delete _p;
        _p = ptr;
    }

    T* release() {
        T* temp = _p;
        _p = nullptr;
        return temp;
    }

    ~UniquePtr() {
        delete _p;
        _p = nullptr;
    }
};
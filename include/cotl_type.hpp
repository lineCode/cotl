#ifndef _COTL_TYPE_HPP
#define _COTL_TYPE_HPP

#include "cotl_helper.hpp"

namespace cotl {

class Val: public gc_cleanup {
private:
    int_t _type;
    func_t _func;
    #ifdef _COTL_USE_REF_COUNT
        int_t _ref = 0;
    #endif

    inline Val() = delete;
    inline Val(const Val &) = delete;
    inline Val(Val &&) = delete;
    inline Val &operator=(const Val &) = delete;
    inline Val &operator=(Val &&) = delete;

    inline void *mem() {
        return this;
    }

protected:
    inline void *operator new(size_t size, PVal reused) {
        (void) size;

        if (reused) {
            reused->~Val();

            return reused->mem();
        } else {
            const size_t maxsize = sizeof(Val) + 16;

            if (size > maxsize) {
                // TODO: error
                exit(1);
            }

            return GC_MALLOC(maxsize);
        }
    }

    inline Val(const int_t type, const func_t func): gc_cleanup(), _type(type), _func(func) {}

    virtual ~Val() {/* inherit ~gc_cleanup() */}

    inline void setType(const int_t type) {
        _type = type;
    }

    inline void setFunc(const func_t func) {
        _func = func;
    }

    #ifdef _COTL_USE_REF_COUNT
        friend class PVal;

        inline void incRef() {
            ++_ref;
        }

        inline void decRef() {
            --_ref;

            if (!_ref) {
                delete this;
            }
        }
    #endif

public:
    inline int_t getType() const {
        return _type;
    }

    inline func_t getFunc() const {
        return _func;
    }

    virtual void repr(std::ostream &stream, const int_t level) const = 0;
};

// begin: from cotl_ptr.hpp

inline void PVal::operator()(PVal caller, PVal lib, PVal tunnel /* could be null */) {
    _val->getFunc()(_val, caller, lib, tunnel);
}

#ifdef _COTL_USE_REF_COUNT
    inline void PVal::doInc() {
        if (_val) {
            _val->incRef();
        }
    }

    inline void PVal::doDec() {
        if (_val) {
            _val->decRef();
        }
    }
#endif

// end: from cotl_ptr.hpp

inline std::ostream &operator<<(std::ostream &stream, const PVal &value) {
    value->repr(stream, 0);
    return stream;
}

class Atom: public Val {
protected:
    inline Atom(const int_t type, const func_t func): Val(type, func) {}

public:
    friend inline Atom *_atom(const int_t type, const func_t func, PVal reused);

    virtual void repr(std::ostream &stream, const int_t level) const;
};

template <class T> class NativeVal;

typedef NativeVal<int_t> Int;
typedef NativeVal<real_t> Real;
typedef NativeVal<func_t> Func;
typedef NativeVal<PVal> Ptr;
typedef NativeVal<std::string> Str;
typedef NativeVal</* std::map or std::unordered_map */map_t> Arr;
typedef NativeVal<std::pair<PVal, PVal>> Pair;

template <class T>
class NativeVal: public Val {
private:
    T _data;

protected:
    inline void set(const T &data) {
        _data = data;
    }

    inline NativeVal(const int_t type, const func_t func):
        Val(type, func), _data() {}

    inline NativeVal(const int_t type, const func_t func, const T &data):
        Val(type, func), _data(data) {}

public:
    friend inline Int *_int(const int_t type, const int_t &data, const func_t func, PVal reused);
    friend inline Real *_real(const int_t type, const real_t &data, const func_t func, PVal reused);
    friend inline Func *_func(const int_t type, const func_t &data, const func_t func, PVal reused);
    friend inline Ptr *_ptr(const int_t type, const PVal &data, const func_t func, PVal reused);
    friend inline Str *_str(const int_t type, const std::string &data, const func_t func, PVal reused);
    friend inline Arr *_arr(const int_t type, const func_t func, PVal reused);
    friend inline Pair *_pair(const int_t type, const PVal &data1, const PVal &data2, const func_t func, PVal reused);

    virtual void repr(std::ostream &stream, const int_t level) const;

    // should not be overused
    inline T &getVar() {
        return _data;
    }

    inline const T &get() const {
        return _data;
    }
};

}

#endif

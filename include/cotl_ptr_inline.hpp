#ifndef _COTL_PTR_INLINE_HPP
#define _COTL_PTR_INLINE_HPP

#include "cotl_helper.hpp"

namespace cotl {

template <bool maybe>
inline bool PValProto<maybe>::legal() const {
    return maybe || _val;
}

template <bool maybe>
inline bool PValProto<maybe>::exist() const {
    return !maybe || _val;
}

#ifdef _COTL_USE_REF_COUNT
    template <bool maybe>
    inline void PValProto<maybe>::doInc() const {
        if (exist()) {
            _val->incRef();
        }
    }

    template <bool maybe>
    inline void PValProto<maybe>::doDec() const {
        if (exist()) {
            _val->decRef();
        }
    }
#endif

template <bool maybe>
inline PValConst PValProto<maybe>::operator->() const {
    if (!exist()) {
        throw "bad pointer dereference";
    }

    return _val;
}

template <bool maybe>
inline void PValProto<maybe>::call(
    const PMaybe &caller, const PMaybe &lib, PMaybe &tunnel
) const {
    if (!exist()) {
        throw "bad pointer call";
    }

    _val->getFunc()(*this, caller, lib, tunnel); // _COTL_CALL
}

template <bool maybe>
inline PValRaw PValProto<maybe>::sure() const {
    if (exist()) {
        return _val;
    } else {
        return _atom(id_null);
    }
}

}

#endif

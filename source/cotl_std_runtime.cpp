#include "../cotl"

namespace cotlstd {

inline
namespace published {

// arg: self, caller, lib, tunnel

_COTL_FUNC_T(stdAuto)
_COTL_FUNC_BEGIN
    PMaybe func(nullptr);

    lib(self, lib, func);

    if (func) {
        func(self, lib, tunnel);
    } else {
        throw;
    }
_COTL_FUNC_END

_COTL_FUNC_T(stdLiteral)
_COTL_FUNC_BEGIN
    if (tunnel) {
        throw;
    } else {
        tunnel = self;
    }
_COTL_FUNC_END

_COTL_FUNC_T(stdBind)
_COTL_FUNC_BEGIN
    PMaybe func(nullptr);

    lib(self, lib, func);

    if (func) {
        if (auto func_p = func.as<cotl::Func>()) {
            self.raw()->setFunc(func_p->get());
            // or self(caller, lib, tunnel) ?
            self(self, lib, tunnel);
        } else {
            throw;
        }
    } else {
        throw;
    }
_COTL_FUNC_END

}

_COTL_FUNC_T(stdQuote)
_COTL_FUNC_BEGIN
    if (auto self_p = self.as<cotl::Ptr>()) {
        if (tunnel) {
            throw;
        } else {
            tunnel = self_p->get();
        }
    } else {
        throw;
    }
_COTL_FUNC_END

_COTL_FUNC_T(stdContain)
_COTL_FUNC_BEGIN
    if (auto self_p = self.raw<cotl::Ptr>()) {
        if (tunnel) {
            self_p->getVar() = tunnel;
            tunnel = nullptr;
        } else {
            tunnel = self_p->get();
        }
    } else {
        throw;
    }
_COTL_FUNC_END

_COTL_FUNC_T(initRuntime)
_COTL_FUNC_BEGIN
    // TODO

_COTL_FUNC_END

namespace {

long long ago = addInitializer(initRuntime);

}

}

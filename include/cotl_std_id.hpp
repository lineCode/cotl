#ifndef _COTL_STD_ID_HPP
#define _COTL_STD_ID_HPP

#include "cotl_helper.hpp"

namespace cotl {

inline
namespace stdid {

enum {
    id_type = IDX_TYPE,

        // atom
        id_atom  = IDX_TYPE + 16,
        id_null,
        id_false,
        id_true,

        // int
        id_int   = IDX_TYPE + 32,
        id_increment,
        id_decrement,

        // real
        id_real  = IDX_TYPE + 48,

        // func
        id_func  = IDX_TYPE + 64,

        // ptr
        id_ptr   = IDX_TYPE + 80,

        // pair
        id_pair  = IDX_TYPE + 96,

        // str
        id_str   = IDX_TYPE + 112,

        // arr
        id_arr   = IDX_TYPE + 128,
        id_stack,
        id_code, // code list

        // map
        id_map   = IDX_TYPE + 144,

        // special
        id_error = IDX_TYPE + 160,
            // members
            id_error_self,
            id_error_caller,
            id_error_lib,
            id_error_tunnel,
            id_error_func,
            id_error_detail,

        // override packages

        id_type_wrap = IDX_TYPE + 176,
        id_type_lib,
        id_type_misc
};

template <class T> struct DefaultId {};
template <> struct DefaultId<Atom> {static const int_t get = id_atom;};
template <> struct DefaultId<Int>  {static const int_t get = id_int;};
template <> struct DefaultId<Real> {static const int_t get = id_real;};
template <> struct DefaultId<Func> {static const int_t get = id_func;};
template <> struct DefaultId<Ptr>  {static const int_t get = id_ptr;};
template <> struct DefaultId<Pair> {static const int_t get = id_pair;};
template <> struct DefaultId<Str>  {static const int_t get = id_str;};
template <> struct DefaultId<Arr>  {static const int_t get = id_arr;};
template <> struct DefaultId<Map>  {static const int_t get = id_map;};

enum {
    id_std = IDX_CORE,
        // id_type,
            // <types> // value: aliases

            // id_type_wrap,
                // override: base types except error

            // id_type_lib,
                // override: func, map

            // id_type_misc,
                // override: non-base types

        id_runtime,
            id_auto,
            id_literal,
            id_bind,

            id_quote,
            id_blackhole,
            id_container,

            id_const,
            id_target,
            id_ref,

            id_before,
            id_after,
            id_also,

            id_void,
            id_exec,
            id_write,
            id_iftunnel,

            id_try,

        id_cast,

        id_dispatch,

        id_query,
            id_use,
            id_with,
            id_withnew,
            id_capture,

            id_def,
            id_quickdef,

            // members
            id_caller,
            id_global,

        id_math,
            id_add, // TODO: both int and real (auto detect)
            id_sub,
            id_mul,
            id_div,
            id_mod,
            id_rsub,
            id_rdiv,
            id_rmod,

            id_math_int,
                // override: add, sub, mul, div, ... // TODO

            id_math_real,
                // override: add, sub, mul, div, ... // TODO

        id_structural,
            id_ifthen, // or use switch+map[bool]?
            id_for,
            id_forin,
            id_foreach,
            id_while,
            id_until,

        id_call, // func(), call, closure, etc

        id_bool,
            //

            // TODO
            id_bool_int, // bitand, bitor, etc

        id_strutil,

        id_arrutil,

        id_maputil,

        id_compare,

        id_hash,

        // id_container, // rename

        id_meta,

        id_io, // time / file / console

        id_regex
};

}

}

#endif

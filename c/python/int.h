//------------------------------------------------------------------------------
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// © H2O.ai 2018
//------------------------------------------------------------------------------
#ifndef dt_PYTHON_INT_h
#define dt_PYTHON_INT_h
#include <Python.h>
#include "python/obj.h"

namespace py {


/**
 * C++ wrapper around PyLong_Object (python `int` object).
 *
 * Public API
 * ----------
 * value<T>()
 *   Return value as an integral T or double type. If the value cannot be
 *   represented as T, an overflow exception will be thrown.
 *
 * value<T>(int* overflow)
 *   Similar to the previous method, but if the value cannot be represented
 *   as T, sets the `overflow` flag to 1 (or -1) and returns the ±MAX<T>
 *   value depending on the sign of the underlying object.
 *
 * masked_value<T>()
 *   Similar to the first method, but if the value does not fit into <T>
 *   truncate it using `static_cast<T>`.
 *
 */
class oint : public oobj {
  public:
    oint();
    oint(int32_t n);
    oint(int64_t n);
    oint(size_t n);
    oint(double x);

    oint(const oint&);
    oint(oint&&);
    oint& operator=(const oint&);
    oint& operator=(oint&&);

    template<typename T> T value() const;
    template<typename T> T value(int* overflow) const;
    template<typename T> T masked_value() const;

  private:
    oint(PyObject*);
    static oint from_new_reference(PyObject*);
    friend class _obj;
};



// Explicit specializations
template<> float     oint::value<float>(int*) const;
template<> double    oint::value<double>(int*) const;
template<> long      oint::value<long>(int*) const;
template<> long long oint::value<long long>(int*) const;
template<> long long oint::masked_value<long long>() const;

// Forward-declare explicit instantiations
extern template int8_t  oint::value() const;
extern template int16_t oint::value() const;
extern template int32_t oint::value() const;
extern template int64_t oint::value() const;
extern template float   oint::value() const;
extern template double  oint::value() const;

extern template int8_t  oint::value(int*) const;
extern template int16_t oint::value(int*) const;
extern template int32_t oint::value(int*) const;
extern template int64_t oint::value(int*) const;

extern template int8_t  oint::masked_value() const;
extern template int16_t oint::masked_value() const;
extern template int32_t oint::masked_value() const;
extern template int64_t oint::masked_value() const;


}  // namespace py

#endif

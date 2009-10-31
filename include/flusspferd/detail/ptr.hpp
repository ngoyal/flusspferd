// vim:ts=2:sw=2:expandtab:autoindent:filetype=cpp:
/*
The MIT License

Copyright (c) 2008, 2009 Flusspferd contributors (see "CONTRIBUTORS" or
                                       http://flusspferd.org/contributors.txt)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef FLUSSPFERD_DETAIL_PTR_HPP
#define FLUSSPFERD_DETAIL_PTR_HPP

#include <boost/none.hpp>

namespace flusspferd { namespace detail {
  template<typename T>
  struct ptr {
    typedef ptr<T> self_type;
    typedef T value_type;
    typedef T const& const_reference_type;
    typedef T& reference_type;
    typedef T const* const_pointer_type;
    typedef T* pointer_type;
    typedef bool (self_type::*unspecified_bool_type)() const;

    bool is_initialized() const { return p; }
    operator unspecified_bool_type() const {
      return p ? &self_type::is_initialized : 0x0;
    }
    bool operator!() const { return !p; }

    const_reference_type operator*() const { return *p; }
    reference_type operator*() { return *p; }

    pointer_type get() { return p; }
    const_pointer_type get() const { return p; }

    pointer_type operator->() { return p; }
    const_pointer_type operator->() const { return p; }

    ptr(pointer_type p = 0x0) : p(p) { }

    template<typename U>
    explicit ptr(U *p) : p(p) { }

    ptr(boost::none_t) : p(0x0) { }

    void reset(pointer_type q = 0x0) {
      p = q;
    }
  private:
    pointer_type p;
  };

  template<typename T, typename U>
  bool operator==(ptr<T> lhs, ptr<U> rhs) {
    return lhs.get() == rhs.get();
  }

  template<typename T, typename U>
  bool operator!=(ptr<T> lhs, ptr<U> rhs) {
    return !(lhs == rhs);
  }

  template<typename T>
  void swap(ptr<T> &lhs, ptr<T> &rhs) {
    if(!lhs && !!rhs) {
      lhs.reset(rhs.get());
      rhs.reset();
    }
    else if(!!rhs && !lhs) {
      rhs.reset(lhs.get());
      lhs.reset();
    }
    else if(!!rhs && !lhs) {
      using std::swap;
      swap(*lhs, *rhs);
    }
  }
}}

#endif

// vim:ts=2:sw=2:expandtab:autoindent:filetype=cpp:
/*
Copyright (c) 2008 Aristid Breitkreuz, Ruediger Sonderfeld

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

#ifndef FLUSSPFERD_CONTEXT_HPP
#define FLUSSPFERD_CONTEXT_HPP

#include <flusspferd/value.hpp>
#include <boost/shared_ptr.hpp>

namespace flusspferd {
  class object;

  class context {
    class impl;
    boost::shared_ptr<impl> p;

  public:
    struct detail;
    friend struct detail;

    context();
    context(detail const&);
    ~context();

    bool is_valid() const;

    bool operator==(context const &o) const {
      return p == o.p;
    }

    static context create();

    object global();

    value evaluate(char const *source, std::size_t n,
                   char const *file = 0x0, unsigned int line = 0);
    value evaluate(char const *source, char const *file = 0x0,
                   unsigned int line = 0);
    value evaluate(std::string const &source, char const *file = 0x0,
                   unsigned int line = 0);

    void gc();
  };

  inline bool operator!=(context const &a, context const &b) {
    return !(a == b);
  }
}

#endif /* FLUSSPFERD_CONTEXT_HPP */
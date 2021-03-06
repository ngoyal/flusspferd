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

#ifndef FLUSSPFERD_TEST_ENVIRONMENT_HPP
#define FLUSSPFERD_TEST_ENVIRONMENT_HPP

#include "flusspferd/current_context_scope.hpp"
#include "flusspferd/load_core.hpp"
#include "flusspferd/security.hpp"
#include <boost/test/unit_test.hpp>

class context_fixture {
public:
  context_fixture() : scope(flusspferd::context::create()) {
    flusspferd::gc();
    flusspferd::security::create(flusspferd::current_context().global());
    flusspferd::gc();
    flusspferd::load_core(flusspferd::current_context().global(), "exeName");
    flusspferd::gc();
  }

  ~context_fixture() {
  }

private:
  flusspferd::current_context_scope scope;
};

#endif

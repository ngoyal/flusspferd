// vim:ts=2:sw=2:expandtab:autoindent:filetype=cpp:
/*
Copyright (c) 2008, 2009 Aristid Breitkreuz, Ash Berlin, Ruediger Sonderfeld

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
#ifndef FLUSSPFERD_BINARY_HPP
#define FLUSSPFERD_BINARY_HPP

#include "native_object_base.hpp"
#include "class_description.hpp"
#include <vector>

namespace flusspferd {

void load_binary_module(object container);

FLUSSPFERD_CLASS_DESCRIPTION(
  binary,
  (full_name, "binary.Binary")
  (constructor_name, "Binary")
  (constructible, 0))
{
protected:
  typedef unsigned char element_type;
  typedef std::vector<element_type> vector_type;

  binary(object const &, call_context &x);

  vector_type &get_data();
  std::size_t get_length() const;

private:
  std::vector<unsigned char> v_data;
};

FLUSSPFERD_CLASS_DESCRIPTION(
  byte_string,
  (full_name, "binary.ByteString")
  (constructor_name, "ByteString")
  (constructor_arity, 2)
  (base, binary)
  (methods, 
    ("toString", bind, to_string)))
{
public:
  byte_string(object const &o, call_context &x);

public:
  std::string to_string();
};

FLUSSPFERD_CLASS_DESCRIPTION(
  byte_array,
  (full_name, "binary.ByteArray")
  (constructor_name, "ByteArray")
  (constructor_arity, 2)
  (base, binary)
  (methods,
    ("toString", bind, to_string)))
{
public:
  byte_array(object const &o, call_context &x);

public:
  std::string to_string();
};

}

#endif

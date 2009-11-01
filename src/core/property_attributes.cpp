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
#include "flusspferd/property_attributes.hpp"
#include "flusspferd/function.hpp"

using namespace flusspferd;

class property_attributes::impl {
public:
  boost::optional<function> getter;
  boost::optional<function> setter;
};

property_attributes::property_attributes()
  : p(new impl),
    flags(no_property_flag),
    getter(p->getter),
    setter(p->setter)
{}

property_attributes::property_attributes(
  property_flag flags, 
  boost::optional<function const &> getter,
  boost::optional<function const &> setter
)
  : p(new impl),
    flags(flags),
    getter(p->getter),
    setter(p->setter)
{
  if (getter)
    this->getter = getter.get();
  if (setter)
    this->setter = setter.get();
}

property_attributes::property_attributes(property_attributes const &o)
  : p(new impl),
    flags(o.flags),
    getter(p->getter),
    setter(p->setter)
{
  this->getter = o.getter;
  this->setter = o.setter;
}

property_attributes::~property_attributes()
{}

// -*- mode:c++; -*- vim:ts=2:sw=2:expandtab:autoindent:filetype=cpp:enc=utf-8:
/*
Contains functions to convert SDL_Rect into a flusspferd object and vice versa

The MIT License

Copyright (c) 2009 Rüdiger Sonderfeld

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
#include "rect.hpp"

#include <flusspferd/create.hpp>
#include <flusspferd/exception.hpp>

using namespace flusspferd;
namespace sdl {
	object rect2object(SDL_Rect const &r) {
    object rect(flusspferd::create_object());
    rect.set_property("h", r.h);
    rect.set_property("w", r.w);
    rect.set_property("x", r.x);
    rect.set_property("y", r.y);
    return rect;
  }

  SDL_Rect object2rect(object const &o) {
    SDL_Rect ret;
    if(!o.has_property("h")) {
      throw flusspferd::exception("Rect: Missing property 'h'");
    }
    else if(!o.has_property("w")) {
      throw flusspferd::exception("Rect: Missing property 'w'");
    }
    else if(!o.has_property("x")) {
      throw flusspferd::exception("Rect: Missing property 'x'");
    }
    else if(!o.has_property("y")) {
      throw flusspferd::exception("Rect: Missing property 'y'");
    }
    ret.h = o.get_property("h").get_int();
    ret.w = o.get_property("w").get_int();
    ret.x = o.get_property("x").get_int();
    ret.y = o.get_property("y").get_int();
    return ret;
  }
}

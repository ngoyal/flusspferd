// vim:ts=2:sw=2:expandtab:autoindent:filetype=cpp:
/*
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
#include <flusspferd.hpp>
#include <boost/filesystem.hpp>

using namespace flusspferd;

namespace {
array ls(boost::optional<std::string> const &dir_) {
  std::string dir = dir_ ? dir_.get() : ".";

  array result = create_array();

  for (boost::filesystem::directory_iterator it(dir);
      it != boost::filesystem::directory_iterator();
      ++it)
  {
    result.call("push", it->path().string());
  }

  return result;
}

bool is_dir(std::string const &what) {

  return boost::filesystem::is_directory(what);
}
}

FLUSSPFERD_LOADER_SIMPLE(exports) {
  create_native_function(exports, "ls", &ls);
  create_native_function(exports, "isDirectory", &is_dir);
}


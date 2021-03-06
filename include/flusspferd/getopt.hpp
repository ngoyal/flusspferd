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

#ifndef FLUSSPFERD_GETOPT_HPP
#define FLUSSPFERD_GETOPT_HPP

#include <boost/optional.hpp>
#include <boost/none.hpp>

namespace flusspferd {

class string;
class object;
class array;

void load_getopt_module(object container);

/**
 * Parse the options.
 *
 * Specification syntax:
 *
 * @code
{
  "[options]": {
    "stop-early": true //default: false
  },
  "name": {
    "alias": ["abc", "d"],
    "argument": "none", // or "optional" or "required"
    "argument_type": "file", // or "dir" or "module" or ...
    "argument_bash": "bash script", // completion script for unkown types
    "doc": "documentation string",
    "hidden": true, // optional. if true no documentation is generated
    "callback": myfunction // takes (option, argument)
  },
  "name2": {}
}
@endcode
 *
 * @return
 * @code
{
  "name": ["arguments"],
  ...,
  "_": ["arguments"]
}
@endcode
 *
 * There are short options (-x) and long options (--xy). Short options cannot
 * take optional arguments, they will always @b require arguments or not accept
 * any at all.
 */
object getopt(
  object spec, boost::optional<array const &> const &arguments = boost::none);

/**
 * Returns a help text to a corresponding getopt call
 *
 */
string getopt_help(object spec);

/**
 * Returns a (nroff formated) manpage part to a corresponding getopt call
 *
 */
string getopt_man(object spec);

/**
 * Returns the content of a bash_completion function
 *
 * Has completions for all argument types supported by compgen/complete -A.
 * See http://www.gnu.org/software/bash/manual/bashref.html#Programmable-Completion-Builtins
 * Use the "argument_bash" property for your own completion scripts.
 *
 * @code
 cout << "_foo() {\n" + getopt_bash(spec) + "}\ncomplete -F _foo foo\n";
@endcode
 */
string getopt_bash(object spec);
}

#endif

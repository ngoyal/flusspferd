// -*- mode:c++; coding:utf-8; tab-width:2; indent-tabs-mode:nil; c-basic-offset:2; compile-command: cd ../../.. && make; -*- vim:ts=2:sw=2:expandtab:autoindent:filetype=cpp:enc=utf-8:
/*
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

// TODO split this mess into several files (e.g. for Video, WM, Events and so on)

#include "flusspferd/class.hpp"
#include "flusspferd/create.hpp"
#include "flusspferd/modules.hpp"
#include "flusspferd/security.hpp"
#include "flusspferd/class_description.hpp"

#include <stdexcept>
#include <cassert>
#include <limits>

#include <SDL.h>

#include "sdl-key.hpp"

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

  FLUSSPFERD_CLASS_DESCRIPTION
  (
   Color,
   (constructor_name, "Color")
   (full_name, "sdl.Color")
   (properties,
    ("r", getter_setter, (get_r, set_r))
    ("g", getter_setter, (get_g, set_g))
    ("b", getter_setter, (get_b, set_b)))
   )
  {
  public:
    SDL_Color color;

    int get_r() { return color.r; }
    void set_r(int r) { color.r = r; }
    int get_g() { return color.g; }
    void set_g(int g) { color.g = g; }
    int get_b() { return color.b; }
    void set_b(int b) { color.b = b; }

    Color(flusspferd::object const &self, SDL_Color const &color)
      : base_type(self), color(color)
    { }
    Color(flusspferd::object const &self, flusspferd::call_context &x)
      : base_type(self)
    {
      if(x.arg.size() == 3) {
        if(!x.arg[0].is_int() || x.arg[1].is_int() || x.arg[2].is_int()) {
          throw flusspferd::exception("Color constructor expected integers");
        }
        color.r = x.arg[0].get_int();
        color.g = x.arg[1].get_int();
        color.b = x.arg[2].get_int();
      }
      else if(x.arg.size() == 1) {
        if(!x.arg[0].is_object() ||
           !flusspferd::is_native<Color>(x.arg[0].get_object()))
        {
          throw flusspferd::exception("Color constructor expects r,g,b or color");
        }
        color = flusspferd::get_native<Color>(x.arg[0].get_object()).color;
      }
      else {
        throw flusspferd::exception("Color constructor expects r,g,b or color");
      }
    }

    static Color &create(SDL_Color const &color) {
      return flusspferd::create_native_object<Color>(object(), color);
    }
  };

  FLUSSPFERD_CLASS_DESCRIPTION
  (
   PixelFormat,
   (constructor_name, "PixelFormat")
   (constructible, false)
   (full_name, "sdl.PixelFormat")
   (properties,
    /* SDL_Palette *palette; */
    ("BitsPerPixel", getter, get_bitspp)
    ("BytesPerPixel", getter, get_bytespp)
    ("Rloss", getter, get_rloss)
    ("Gloss", getter, get_gloss)
    ("Bloss", getter, get_bloss)
    ("Aloss", getter, get_aloss)
    ("Rshift", getter, get_rshift)
    ("Gshift", getter, get_gshift)
    ("Bshift", getter, get_bshift)
    ("Ashift", getter, get_ashift)
    ("Rmask", getter, get_rmask)
    ("Gmask", getter, get_gmask)
    ("Bmask", getter, get_bmask)
    ("Amask", getter, get_amask)
    ("colorkey", getter, get_colorkey)
    ("alpha", getter, get_alpha))
   )
  {
  public:
    SDL_PixelFormat *format;

    int get_bitspp() {
      assert(format);
      return format->BitsPerPixel;
    }
    int get_bytespp() {
      assert(format);
      return format->BytesPerPixel;
    }
    int get_rloss() {
      assert(format);
      return format->Rloss;
    }
    int get_gloss() {
      assert(format);
      return format->Gloss;
    }
    int get_bloss() {
      assert(format);
      return format->Bloss;
    }
    int get_aloss() {
      assert(format);
      return format->Aloss;
    }
    int get_rshift() {
      assert(format);
      return format->Rshift;
    }
    int get_gshift() {
      assert(format);
      return format->Gshift;
    }
    int get_bshift() {
      assert(format);
      return format->Bshift;
    }
    int get_ashift() {
      assert(format);
      return format->Ashift;
    }
    int get_rmask() {
      assert(format);
      return format->Rmask;
    }
    int get_gmask() {
      assert(format);
      return format->Gmask;
    }
    int get_bmask() {
      assert(format);
      return format->Bmask;
    }
    int get_amask() {
      assert(format);
      return format->Amask;
    }
    int get_colorkey() {
      assert(format);
      return format->colorkey;
    }
    int get_alpha() {
      assert(format);
      return format->alpha;
    }

    PixelFormat(flusspferd::object const &self, SDL_PixelFormat *format)
      : base_type(self), format(format)
    {
      assert(format);
    }

    static PixelFormat &create(SDL_PixelFormat *format) {
      return flusspferd::create_native_object<PixelFormat>(object(), format);
    }
  };

  class Surface;

  FLUSSPFERD_CLASS_DESCRIPTION
  (
   PixelData,
   (constructor_name, "PixelData")
   (constructible, false)
   (full_name, "sdl.PixelData")
   (methods,
    ("get", bind, get)
    ("set", bind, set)
    ("getpixel", bind, getpixel)
    ("setpixel", bind, setpixel))
   )
  {
    Uint8 *data;
  public:
    int get(int n) {
      assert(data && n > 0);
      return data[n];
    }
    void set(int n, int byte) {
      assert(data && n > 0 && byte <= std::numeric_limits<Uint8>::max());
      data[n] = byte;
    }

    int getpixel(Surface &surface, int x, int y);
    void setpixel(Surface &surface, int x, int y, int color);

    PixelData(flusspferd::object const &self, Uint8 *data)
      : base_type(self), data(data)
    {
      assert(data);
    }

    static PixelData &create(void *data) {
      return flusspferd::create_native_object<PixelData>(object(), reinterpret_cast<Uint8*>(data));
    }
  };

  FLUSSPFERD_CLASS_DESCRIPTION
  (
   Surface,
   (constructor_name, "Surface")
   (constructible, false)
   (full_name, "sdl.Surface")
   (properties,
    ("flags", getter, get_flags)
    ("format", getter, get_format)
    ("width", getter, get_width)
    ("w", getter, get_width)
    ("height", getter, get_height)
    ("h", getter, get_height)
    ("pitch", getter, get_pitch)
    ("pixels", getter, get_pixels)
    ("clip_rect", getter, get_clip_rect)
    ("refcount", getter_setter, (get_refcount, set_refcount)))
   )
  {
  public:
    SDL_Surface *surface;

    Uint32 get_flags() {
      assert(surface);
      return surface->flags;
    }
    PixelFormat &get_format() {
      assert(surface);
      return PixelFormat::create(surface->format);
    }
    int get_width() {
      assert(surface);
      return surface->w;
    }
    int get_height() {
      assert(surface);
      return surface->h;
    }
    Uint16 get_pitch() {
      assert(surface);
      return surface->pitch;
    }
    PixelData &get_pixels() {
      assert(surface);
      return PixelData::create(surface->pixels);
    }
    object get_clip_rect() {
      assert(surface);
      return rect2object(surface->clip_rect);
    }
    int get_refcount() {
      assert(surface);
      return surface->refcount;
    }
    void set_refcount(int r) {
      assert(surface);
      surface->refcount = r;
    }

    Surface(flusspferd::object const &self, SDL_Surface *surface)
      : base_type(self), surface(surface)
    {
      assert(surface);
    }

    static Surface &create(SDL_Surface *surface) {
      return flusspferd::create_native_object<Surface>(object(), surface);
    }
  };

  int PixelData::getpixel(Surface &s, int x, int y) {
    assert(s.surface);
    SDL_Surface *surface = s.surface;
    int const bpp = surface->format->BytesPerPixel;
    Uint8 *p = data + y * surface->pitch + x * bpp;
    switch (bpp) {
    case 1:
      return *p;
      break;
    case 2:
      return *reinterpret_cast<Uint16*>(p);
      break;
    case 3:
      if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
        return p[0] << 16 | p[1] << 8 | p[2];
      else
        return p[0] | p[1] << 8 | p[2] << 16;
      break;
    case 4:
      return *reinterpret_cast<Uint32*>(p);
      break;
    default:
      throw flusspferd::exception("getpixel");
    }
  }
  void PixelData::setpixel(Surface &s, int x, int y, int color) {
    assert(s.surface);
    SDL_Surface *surface = s.surface;
    int const bpp = surface->format->BytesPerPixel;
    Uint8 *p = data + y * surface->pitch + x * bpp;
    switch(bpp) {
    case 1:
      *p = color;
      break;
    case 2:
      *reinterpret_cast<Uint16*>(p) = color;
      break;
    case 3:
      if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
        p[0] = (color >> 16) & 0xff;
        p[1] = (color >> 8) & 0xff;
        p[2] = color & 0xff;
      }
      else {
        p[0] = color & 0xff;
        p[1] = (color >> 8) & 0xff;
        p[2] = (color >> 16) & 0xff;
      }
      break;
    case 4:
      *reinterpret_cast<Uint32*>(p) = color;
      break;
   default:
     throw flusspferd::exception("setpixel");
    }
  }

  void quit() {
    SDL_Quit();
  }

  Surface &set_video_mode(int width, int height, int bpp, Uint32 flags) {
    SDL_Surface *surface = SDL_SetVideoMode(width, height, bpp, flags);
    if(!surface) {
      std::string const what = std::string("SDL_SetVideoMode: ") + SDL_GetError();
      throw flusspferd::exception(what.c_str());
    }
    return Surface::create(surface);
  }

  Surface &get_video_surface() {
    return Surface::create(SDL_GetVideoSurface());
  }

  int flip(Surface &surface) {
    return SDL_Flip(surface.surface);
  }

  void update_rect(Surface &screen, int x, int y, int w, int h) {
    SDL_UpdateRect(screen.surface, x, y, w, h);
  }

  int lock_surface(Surface &surface) {
    return SDL_LockSurface(surface.surface);
  }

  void unlock_surface(Surface &surface) {
    SDL_UnlockSurface(surface.surface);
  }

  void free_surface(Surface &surface) {
    SDL_FreeSurface(surface.surface);
  }

  Surface &load_BMP(char const *file) {
    SDL_Surface *surface = SDL_LoadBMP(file);
    if(!surface) {
      std::string const what = std::string("SDL_LoadBMP: ") + SDL_GetError();
      throw flusspferd::exception(what.c_str());
    }
    return Surface::create(surface);
  }

  void blit_surface(flusspferd::call_context &x) {
    if(x.arg.size() == 2) {
      if(!x.arg[0].is_object() || !flusspferd::is_native<Surface>(x.arg[0].get_object())) {
        throw flusspferd::exception("blitSurface: expected Surface as first parameter");
      }
      SDL_Surface *src = flusspferd::get_native<Surface>(x.arg[0].get_object()).surface;
      if(!x.arg[1].is_object() || !flusspferd::is_native<Surface>(x.arg[1].get_object())) {
        throw flusspferd::exception("blitSurface: expected Surface as second parameter");
      }
      SDL_Surface *dest = flusspferd::get_native<Surface>(x.arg[1].get_object()).surface;
      x.result = value(SDL_BlitSurface(src, 0x0, dest, 0x0));
      return;
    }
    else if(x.arg.size() == 4) {
      if(!flusspferd::is_native<Surface>(x.arg[0].get_object())) {
        throw flusspferd::exception("blitSurface: expected Surface as first parameter");
      }
      SDL_Surface *src = flusspferd::get_native<Surface>(x.arg[0].get_object()).surface;
      if(!flusspferd::is_native<Surface>(x.arg[1].get_object())) {
        throw flusspferd::exception("blitSurface: expected Rect as second parameter");
      }
      SDL_Rect srcrect = object2rect(x.arg[1].get_object());
      if(!flusspferd::is_native<Surface>(x.arg[2].get_object())) {
        throw flusspferd::exception("blitSurface: expected Surface as third parameter");
      }
      SDL_Surface *dest = flusspferd::get_native<Surface>(x.arg[2].get_object()).surface;
      if(!flusspferd::is_native<Surface>(x.arg[3].get_object())) {
        throw flusspferd::exception("blitSurface: expected Rect as fourth parameter");
      }
      SDL_Rect destrect = object2rect(x.arg[3].get_object());
      x.result = value(SDL_BlitSurface(src, &srcrect, dest, &destrect));
      return;
    }
    else {
      throw flusspferd::exception("blitSurface: expected two or four parameter ( blitSurface(from, to) || blitSurface(from, from_rect, to, to_rext) )");
    }
  }

  int set_colors(Surface &surface, Color &color, int firstcolor, int ncolors) {
    return SDL_SetColors(surface.surface, &color.color, firstcolor, ncolors);
  }

  Surface &create_RGB_surface(int flags, int width, int height, int bpp, int rmask, int gmask, int bmask, int amask) {
    SDL_Surface *surface = SDL_CreateRGBSurface(flags, width, height, bpp, rmask, gmask, bmask, amask);
    if(!surface) {
      std::string const what = std::string("SDL_CreateRGBSurface: ") + SDL_GetError();
      throw flusspferd::exception(what.c_str());
    }
    return Surface::create(surface);
  }

  int set_alpha(Surface &surface, int flags, int alpha) {
    return SDL_SetAlpha(surface.surface, flags, alpha);
  }

  int set_color_key(Surface &surface, int flag, int key) {
    return SDL_SetColorKey(surface.surface, flag, key);
  }

  Surface &display_format(Surface &in) {
    SDL_Surface *surface = SDL_DisplayFormat(in.surface);
    if(!surface) {
      std::string const what = std::string("SDL_DisplayFormat: ") + SDL_GetError();
      throw flusspferd::exception(what.c_str());
    }
    return Surface::create(surface);
  }

  Surface &display_format_alpha(Surface &in) {
    SDL_Surface *surface = SDL_DisplayFormatAlpha(in.surface);
    if(!surface) {
      std::string const what = std::string("SDL_DisplayFormatAlpha: ") + SDL_GetError();
      throw flusspferd::exception(what.c_str());
    }
    return Surface::create(surface);
  }

  Surface &convert_surface(Surface &in, PixelFormat &fmt, int flags) {
    SDL_Surface *surface = SDL_ConvertSurface(in.surface, fmt.format, flags);
    if(!surface) {
      std::string const what = std::string("SDL_ConvertSurface: ") + SDL_GetError();
      throw flusspferd::exception(what.c_str());
    }
    return Surface::create(surface);
  }

  std::string video_driver_name() {
    enum { MAXLEN = 1024 };
    char buffer[MAXLEN];
    return SDL_VideoDriverName(buffer, MAXLEN);
  }

  void error(int err) {
    SDL_Error((SDL_errorcode)err);
  }

  object sdl_version() {
    SDL_version v;
    SDL_VERSION(&v);
    object ver(flusspferd::create_object());
    ver.set_property("major", v.major);
    ver.set_property("minor", v.minor);
    ver.set_property("patch", v.patch);
    return ver;
  }

  object linked_version() {
    SDL_version const *v = SDL_Linked_Version();
    if(!v) {
      std::string const what = std::string("SDL_Linked_Version: ") + SDL_GetError();
      throw flusspferd::exception(what.c_str());
    }
    object ver(flusspferd::create_object());
    ver.set_property("major", v->major);
    ver.set_property("minor", v->minor);
    ver.set_property("patch", v->patch);
    return ver;
  }

  int map_RGB(PixelFormat &fmt, int r, int g, int b) {
    return SDL_MapRGB(fmt.format, r, g, b);
  }

  int map_RGBA(PixelFormat &fmt, int r, int g, int b, int a) {
    return SDL_MapRGBA(fmt.format, r, g, b, a);
  }

  Color &get_RGB(int pixel, PixelFormat &format) {
    SDL_Color color;
    SDL_GetRGB(pixel, format.format, &color.r, &color.g, &color.b);
    return Color::create(color);
  }

  int save_BMP(Surface &surface, char const *file) {
    return SDL_SaveBMP(surface.surface, file);
  }

  void set_clip_rect(Surface &surface, object const &o) {
    SDL_Rect rect = object2rect(o);
    SDL_SetClipRect(surface.surface, &rect);
  }
  object get_clip_rect(Surface &surface) {
    SDL_Rect rect;
    SDL_GetClipRect(surface.surface, &rect);
    return rect2object(rect);
  }

  int fill_rect(Surface &surface, object const &rect, int color) {
    SDL_Rect r = object2rect(rect);
    return SDL_FillRect(surface.surface, &r, color);
  }

  int wm_toggle_fullscreen(Surface &surface) {
    return SDL_WM_ToggleFullScreen(surface.surface);
  }

  void wm_set_icon(Surface &surface) {
    SDL_WM_SetIcon(surface.surface, 0x0);
  }

  int wm_grab_input(int mode) {
    return (int)SDL_WM_GrabInput((SDL_GrabMode)mode);
  }

  char const *get_key_name(int key) {
    return SDL_GetKeyName((SDLKey)key);
  }

  int get_app_state() {
    return SDL_GetAppState();
  }

  int event_state(int type, int state) {
    return event_state(type, state);
  }

  FLUSSPFERD_CLASS_DESCRIPTION
  (
   ActiveEvent,
   (constructor_name, "ActiveEvent")
   (constructible, false)
   (full_name, "sdl.ActiveEvent")
   (properties,
    ("type", getter, get_type)
    ("gain", getter, get_type)
    ("state", getter, get_state)))
  {
    SDL_ActiveEvent event;
  public:
    int get_type()  { return event.type; }
    int get_gain()  { return event.gain; }
    int get_state() { return event.state; }

    ActiveEvent(flusspferd::object const &self, SDL_ActiveEvent const &e)
      : base_type(self), event(e)
    { }

    static ActiveEvent &create(SDL_ActiveEvent const &e) {
      return flusspferd::create_native_object<ActiveEvent>(object(), e);
    }
  };

  FLUSSPFERD_CLASS_DESCRIPTION
  (
   Keysym,
   (constructor_name, "Keysym")
   (constructible, false)
   (full_name, "sdl.Keysym")
   (properties,
    ("scancode", getter, get_scancode)
    ("sym", getter, get_sym)
    ("mod", getter, get_mod)
    ("unicode", getter, get_unicode)))
  {
    SDL_keysym k;
  public:
    int get_scancode() { return k.scancode; }
    int get_sym()      { return k.sym; }
    int get_mod()      { return k.mod; }
    int get_unicode()  { return k.unicode; }

    Keysym(flusspferd::object const &self, SDL_keysym const &k)
      : base_type(self), k(k)
    { }

    static Keysym &create(SDL_keysym const &k) {
      return flusspferd::create_native_object<Keysym>(object(), k);
    }
  };

  FLUSSPFERD_CLASS_DESCRIPTION
  (
   KeyboardEvent,
   (constructor_name, "KeyboardEvent")
   (constructible, false)
   (full_name, "sdl.KeyboardEvent")
   (properties,
    ("type", getter, get_type)
    ("state", getter, get_state)
    ("keysym", getter, get_keysym)))
  {
    SDL_KeyboardEvent event;
  public:
    int    get_type()    { return event.type; }
    int    get_state()   { return event.state; }
    Keysym &get_keysym() { return Keysym::create(event.keysym); }

    KeyboardEvent(flusspferd::object const &o, SDL_KeyboardEvent const &e)
      : base_type(o), event(e)
    { }

    static KeyboardEvent &create(SDL_KeyboardEvent const &e) {
      return flusspferd::create_native_object<KeyboardEvent>(object(), e);
    }
  };

  FLUSSPFERD_CLASS_DESCRIPTION
  (MouseMotionEvent,
   (constructor_name, "MouseMotionEvent")
   (constructible, false)
   (full_name, "sdl.MouseMotionEvent")
   (properties,
    ("type", getter, get_type)
    ("state", getter, get_state)
    ("x", getter, get_x)
    ("y", getter, get_y)
    ("xrel", getter, get_xrel)
    ("yrel", getter, get_yrel)))
  {
    SDL_MouseMotionEvent e;
  public:

    int get_type() { return e.type; }
    int get_state() { return e.state; }
    int get_x() { return e.x; }
    int get_y() { return e.y; }
    int get_xrel() { return e.xrel; }
    int get_yrel() { return e.yrel; }

    MouseMotionEvent(flusspferd::object const &self, SDL_MouseMotionEvent const &e)
      : base_type(self), e(e)
    { }

    static MouseMotionEvent &create(SDL_MouseMotionEvent const &e) {
      return flusspferd::create_native_object<MouseMotionEvent>(object(), e);
    }
  };

  FLUSSPFERD_CLASS_DESCRIPTION
  (
   MouseButtonEvent,
   (constructor_name, "MouseButtonEvent")
   (constructible, false)
   (full_name, "sdl.MouseButtonEvent")
   (properties,
    ("type", getter, get_type)
    ("which", getter, get_which)
    ("button", getter, get_button)
    ("state", getter, get_state)
    ("x", getter, get_x)
    ("y", getter, get_y)))
  {
    SDL_MouseButtonEvent event;
  public:
    int get_type() { return event.type; }
    int get_which() { return event.which; }
    int get_button() { return event.button; }
    int get_state() { return event.state; }
    int get_x() { return event.x; }
    int get_y() { return event.y; }

    MouseButtonEvent(flusspferd::object const &self, SDL_MouseButtonEvent const &event)
      : base_type(self), event(event)
    { }

    static MouseButtonEvent &create(SDL_MouseButtonEvent const &e) {
      return flusspferd::create_native_object<MouseButtonEvent>(object(), e);
    }
  };

  FLUSSPFERD_CLASS_DESCRIPTION
  (
   JoyAxisEvent,
   (constructor_name, "JoyAxisEvent")
   (constructible, false)
   (full_name, "sdl.JoyAxisEvent")
   (properties,
    ("type", getter, get_type)
    ("which", getter, get_which)
    ("axis", getter, get_axis)
    ("value", getter, get_value)))
  {
    SDL_JoyAxisEvent event;
  public:
    int get_type() { return event.type; }
    int get_which() { return event.which; }
    int get_axis() { return event.axis; }
    int get_value() { return event.value; }

    JoyAxisEvent(flusspferd::object const &self, SDL_JoyAxisEvent const &event)
      : base_type(self), event(event)
    { }

    static JoyAxisEvent &create(SDL_JoyAxisEvent const &e) {
      return flusspferd::create_native_object<JoyAxisEvent>(object(), e);
    }
  };

  FLUSSPFERD_CLASS_DESCRIPTION
  (
   JoyButtonEvent,
   (constructor_name, "JoyButtonEvent")
   (constructible, false)
   (full_name, "sdl.JoyButtonEvent")
   (properties,
    ("type", getter, get_type)
    ("which", getter, get_which)
    ("button", getter, get_button)
    ("state", getter, get_state)
    ))
  {
    SDL_JoyButtonEvent event;
  public:
    int get_type() { return event.type; }
    int get_which() { return event.which; }
    int get_button() { return event.button; }
    int get_state() { return event.state; }

    JoyButtonEvent(flusspferd::object const &self, SDL_JoyButtonEvent const &event)
      : base_type(self), event(event)
    { }

    static JoyButtonEvent &create(SDL_JoyButtonEvent const &e) {
      return flusspferd::create_native_object<JoyButtonEvent>(object(), e);
    }
  };

  FLUSSPFERD_CLASS_DESCRIPTION
  (
   JoyHatEvent,
   (constructor_name, "JoyHatEvent")
   (constructible, false)
   (full_name, "sdl.JoyHatEvent")
   (properties,
    ("type", getter, get_type)
    ("which", getter, get_which)
    ("hat", getter, get_hat)
    ("value", getter, get_value)
    ))
  {
    SDL_JoyHatEvent event;
  public:
    int get_type() { return event.type; }
    int get_which() { return event.which; }
    int get_hat() { return event.hat; }
    int get_value() { return event.value; }

    JoyHatEvent(flusspferd::object const &self, SDL_JoyHatEvent const &event)
      : base_type(self), event(event)
    { }

    static JoyHatEvent &create(SDL_JoyHatEvent const &e) {
      return flusspferd::create_native_object<JoyHatEvent>(object(), e);
    }
  };

  FLUSSPFERD_CLASS_DESCRIPTION
  (
   JoyBallEvent,
   (constructor_name, "JoyBallEvent")
   (constructible, false)
   (full_name, "sdl.JoyBallEvent")
   (properties,
    ("type", getter, get_type)
    ("which", getter, get_which)
    ("ball", getter, get_ball)
    ("xrel", getter, get_xrel)
    ("yrel", getter, get_yrel)
    ))
  {
    SDL_JoyBallEvent event;
  public:
    int get_type() { return event.type; }
    int get_which() { return event.which; }
    int get_ball() { return event.ball; }
    int get_xrel() { return event.xrel; }
    int get_yrel() { return event.yrel; }

    JoyBallEvent(flusspferd::object const &self, SDL_JoyBallEvent const &event)
      : base_type(self), event(event)
    { }

    static JoyBallEvent &create(SDL_JoyBallEvent const &e) {
      return flusspferd::create_native_object<JoyBallEvent>(object(), e);
    }
  };

  FLUSSPFERD_CLASS_DESCRIPTION
  (
   ResizeEvent,
   (constructor_name, "ResizeEvent")
   (constructible, false)
   (full_name, "sdl.ResizeEvent")
   (properties,
    ("type", getter, get_type)
    ("w", getter, get_w)
    ("h", getter, get_h)
    ))
  {
    SDL_ResizeEvent event;
  public:
    int get_type() { return event.type; }
    int get_w() { return event.w; }
    int get_h() { return event.h; }

    ResizeEvent(flusspferd::object const &self, SDL_ResizeEvent const &event)
      : base_type(self), event(event)
    { }

    static ResizeEvent &create(SDL_ResizeEvent const &e) {
      return flusspferd::create_native_object<ResizeEvent>(object(), e);
    }
  };

  FLUSSPFERD_CLASS_DESCRIPTION
  (
   ExposeEvent,
   (constructor_name, "ExposeEvent")
   (constructible, false)
   (full_name, "sdl.ExposeEvent")
   (properties,
    ("type", getter, get_type)
    ))
  {
    SDL_ExposeEvent event;
  public:
    int get_type() { return event.type; }

    ExposeEvent(flusspferd::object const &self, SDL_ExposeEvent const &event)
      : base_type(self), event(event)
    { }

    static ExposeEvent &create(SDL_ExposeEvent const &e) {
      return flusspferd::create_native_object<ExposeEvent>(object(), e);
    }
  };

  FLUSSPFERD_CLASS_DESCRIPTION
  (
   QuitEvent,
   (constructor_name, "QuitEvent")
   (constructible, false)
   (full_name, "sdl.QuitEvent")
   (properties,
    ("type", getter, get_type)
    ))
  {
    SDL_QuitEvent event;
  public:
    int get_type() { return event.type; }

    QuitEvent(flusspferd::object const &self, SDL_QuitEvent const &event)
      : base_type(self), event(event)
    { }

    static QuitEvent &create(SDL_QuitEvent const &e) {
      return flusspferd::create_native_object<QuitEvent>(object(), e);
    }
  };

  FLUSSPFERD_CLASS_DESCRIPTION
  (
   Event,
   (constructor_name, "Event")
   (constructible, false)
   (full_name, "sdl.Event")
   (properties,
    ("type", getter, get_type)
    ("active", getter, get_active)
    ("key", getter, get_key)
    ("motion", getter, get_motion)
    ("button", getter, get_button)
    ("jaxis", getter, get_jaxis)
    ("jball", getter, get_jball)
    ("jhat", getter, get_jhat)
    ("jbutton", getter, get_jbutton)
    ("resize", getter, get_resize)
    ("expose", getter, get_expose)
    ("quit", getter, get_quit)
    /* TODO
    user     User defined event (see SDL_UserEvent)
    syswm    Undefined window manager event (see SDL_SysWMEvent)
    */
    ))
  {
    SDL_Event event;
  public:

    int get_type() {
      return event.type;
    }
    ActiveEvent &get_active() {
      return ActiveEvent::create(event.active);
    }
    KeyboardEvent &get_key() {
      return KeyboardEvent::create(event.key);
    }
    MouseMotionEvent &get_motion() {
      return MouseMotionEvent::create(event.motion);
    }
    MouseButtonEvent &get_button() {
      return MouseButtonEvent::create(event.button);
    }
    JoyAxisEvent &get_jaxis() {
      return JoyAxisEvent::create(event.jaxis);
    }
    JoyBallEvent &get_jball() {
      return JoyBallEvent::create(event.jball);
    }
    JoyHatEvent &get_jhat() {
      return JoyHatEvent::create(event.jhat);
    }
    JoyButtonEvent &get_jbutton() {
      return JoyButtonEvent::create(event.jbutton);
    }
    ResizeEvent &get_resize() {
      return ResizeEvent::create(event.resize);
    }
    ExposeEvent &get_expose() {
      return ExposeEvent::create(event.expose);
    }
    QuitEvent &get_quit() {
      return QuitEvent::create(event.quit);
    }
#if 0
    UserEvent &get_user() {
      return UserEvent::create(event.user);
    }
    SysWMEvent &get_syswm() {
      return SysWMEvent::create(event.syswm);
    }
#endif

    Event(flusspferd::object const &self, SDL_Event const &e)
      : base_type(self), event(e)
    { }

    static Event &create(SDL_Event const &e) {
      return flusspferd::create_native_object<Event>(object(), e);
    }
  };

  object poll_event() {
    SDL_Event event;
    int i = SDL_PollEvent(&event);
    if(i == 0) {
      return object();
    }
    else {
      return Event::create(event);
    }
  }

  object wait_event() {
    SDL_Event event;
    int i = SDL_WaitEvent(&event);
    if(i == 0) {
      return object();
    }
    else {
      return Event::create(event);
    }
  }

  int get_mod_state() {
    return SDL_GetModState();
  }
  void set_mod_state(int s) {
    SDL_SetModState((SDLMod)s);
  }

  object get_mouse_state() {
    int x, y;
    int ret = SDL_GetMouseState(&x, &y);
    object state(flusspferd::create_object());
    state.set_property("state", ret);
    state.set_property("x", x);
    state.set_property("y", y);
    return state;
  }

  object get_relative_mouse_state() {
    int x, y;
    int ret = SDL_GetRelativeMouseState(&x, &y);
    object state(flusspferd::create_object());
    state.set_property("state", ret);
    state.set_property("x", x);
    state.set_property("y", y);
    return state;
  }

  // Joystick
  FLUSSPFERD_CLASS_DESCRIPTION(
   Joystick,
   (constructor_name, "Joystick")
   (constructible, false)
   (full_name, "sdl.Joystick"))
  {
    SDL_Joystick *joystick;
  public:
    SDL_Joystick *get() {
      assert(joystick);
      return joystick;
    }

    Joystick(flusspferd::object const &self, SDL_Joystick *j)
      : base_type(self), joystick(j)
    { }

    void close() {
      SDL_JoystickClose(joystick);
      joystick = 0x0;
    }

    ~Joystick() {
      if(joystick)
        close();
    }

    static Joystick &create(SDL_Joystick *j) {
      return flusspferd::create_native_object<Joystick>(object(), j);
    }
  };

  Joystick &joystick_open(int index) {
    return Joystick::create(SDL_JoystickOpen(index));
  }

  void joystick_close(Joystick &j) {
    j.close();
  }

  int joystick_index(Joystick &j) {
    return SDL_JoystickIndex(j.get());
  }

  int joystick_num_axes(Joystick &j) {
    return SDL_JoystickNumAxes(j.get());
  }

  int joystick_num_balls(Joystick &j) {
    return SDL_JoystickNumBalls(j.get());
  }

  int joystick_num_hats(Joystick &j) {
    return SDL_JoystickNumHats(j.get());
  }

  int joystick_num_buttons(Joystick &j) {
    return SDL_JoystickNumButtons(j.get());
  }

  int joystick_get_axis(Joystick &j, int axis) {
    return SDL_JoystickGetAxis(j.get(), axis);
  }

  int joystick_get_hat(Joystick &j, int hat) {
    return SDL_JoystickGetHat(j.get(), hat);
  }

  int joystick_get_button(Joystick &j, int button) {
    return SDL_JoystickGetButton(j.get(), button);
  }

  object joystick_get_ball(Joystick &j, int ball) {
    int dx, dy;
    if(SDL_JoystickGetBall(j.get(), ball, &dx, &dy) == -1) {
      return object();
    }
    else {
      object ret(create_object());
      ret.set_property("dx", dx);
      ret.set_property("dy", dy);
      return ret;
    }
  }

  /* Missing:
  General:
    SDL_SetError - Sets SDL Error
    SDL_LoadObject - Loads a shared object.
    SDL_LoadFunction - Returns the address of a function in a loaded shared object.
    SDL_UnloadObject - Unloads a shared object.
    SDL_envvars - SDL environment variables

  Video:
    SDL_GetVideoInfo
    SDL_ListModes
    SDL_VideoModeOK
    SDL_UpdateRects
    SDL_SetPalette
    SDL_GetGammaRamp
    SDL_SetGammaRamp
    SDL_GetRGBA
    SDL_CreateRGBSurface
    SDL_CreateRGBSurfaceFrom
    SDL_GL*
    SDL_*YUV*

  Window Management:
    SDL_GetWMInfo - Gets window-manager specific information, if available
    SDL_WM_GetCaption - Gets the window title and icon name.

  Events:
    SDL_PeepEvents - Checks the event queue for messages and optionally returns them
    SDL_PushEvent - Pushes an event onto the event queue
    SDL_SetEventFilter - Sets up a filter to process all events
    SDL_GetKeyState - Gets a snapshot of the current keyboard state
    SDL_SetTextInputRect - Set the rectangle for input methods to display inputed Unicode text and candidate text 

  Mouse:
    SDL_CreateCursor - Creates a new mouse cursor.
    SDL_FreeCursor - Frees a cursor created with SDL_CreateCursor.
    SDL_SetCursor - Sets the currently active mouse cursor.
    SDL_GetCursor - Gets the currently active mouse cursor.

  Joystick:
    COMPLETE

  and everything else
   */

  FLUSSPFERD_LOADER_SIMPLE(sdl) {
    local_root_scope scope;

    // General
    sdl.define_property("INIT_TIMER", value(SDL_INIT_TIMER));
    sdl.define_property("INIT_AUDIO", value(SDL_INIT_AUDIO));
    sdl.define_property("INIT_VIDEO", value(SDL_INIT_VIDEO));
    sdl.define_property("INIT_CDROM", value(SDL_INIT_CDROM));
    sdl.define_property("INIT_JOYSTICK", value(SDL_INIT_JOYSTICK));
    sdl.define_property("INIT_EVERYTHING", value(SDL_INIT_EVERYTHING));
    sdl.define_property("INIT_NOPARACHUTE", value(SDL_INIT_NOPARACHUTE));
    sdl.define_property("INIT_EVENTTHREAD", value(SDL_INIT_EVENTTHREAD));
    create_native_function(sdl, "init", &::SDL_Init);
    create_native_function(sdl, "initSubSystem", &::SDL_InitSubSystem);
    create_native_function(sdl, "quit", &sdl::quit);
    create_native_function(sdl, "quitSubSystem", &::SDL_QuitSubSystem);
    sdl.define_property("ENOMEM", value((int)SDL_ENOMEM));
    sdl.define_property("EFREAD", value((int)SDL_EFREAD));
    sdl.define_property("EFWRITE", value((int)SDL_EFWRITE));
    sdl.define_property("EFSEEK", value((int)SDL_EFSEEK));
    sdl.define_property("UNSUPPORTED", value((int)SDL_UNSUPPORTED));
    sdl.define_property("LASTERROR", value((int)SDL_LASTERROR));
    create_native_function(sdl, "error", &sdl::error);
    create_native_function(sdl, "getError", &::SDL_GetError);
    create_native_function(sdl, "clearError", &::SDL_ClearError);
    create_native_function(sdl, "wasInit", &::SDL_WasInit);
    create_native_function(sdl, "version", &sdl::sdl_version);
    create_native_function(sdl, "linkedVersion", &sdl::linked_version);

    // Video
    sdl.define_property("SWSURFACE", value(SDL_SWSURFACE));
    sdl.define_property("HWSURFACE", value(SDL_HWSURFACE));
    sdl.define_property("ASYNCBLIT", value(SDL_ASYNCBLIT));
    sdl.define_property("ANYFORMAT", value(SDL_ANYFORMAT));
    sdl.define_property("HWPALETTE", value(SDL_HWPALETTE));
    sdl.define_property("DOUBLEBUF", value(SDL_DOUBLEBUF));
    sdl.define_property("FULLSCREEN", value(SDL_FULLSCREEN));
    sdl.define_property("OPENGL", value(SDL_OPENGL));
    sdl.define_property("OPENGLBLIT", value(SDL_OPENGLBLIT));
    sdl.define_property("RESIZABLE", value(SDL_RESIZABLE));
    sdl.define_property("NOFRAME", value(SDL_NOFRAME));
    create_native_function(sdl, "setVideoMode", &sdl::set_video_mode);
    create_native_function(sdl, "getVideoSurface", &sdl::get_video_surface);
    load_class<sdl::Surface>(sdl);
    load_class<sdl::PixelFormat>(sdl);
    load_class<sdl::Color>(sdl);
    load_class<sdl::PixelData>(sdl);
    create_native_function(sdl, "videoModeOK", &::SDL_VideoModeOK);
    create_native_function(sdl, "flip", &sdl::flip);
    create_native_function(sdl, "updateRect", &sdl::update_rect);
    create_native_function(sdl, "lockSurface", &sdl::lock_surface);
    create_native_function(sdl, "unlockSurface", &sdl::unlock_surface);
    create_native_function(sdl, "freeSurface", &sdl::free_surface);
    create_native_function(sdl, "loadBMP", &sdl::load_BMP);
    create_native_function(sdl, "saveBMP", &sdl::save_BMP);
    boost::function< void(call_context &)> blit_surface_ = &sdl::blit_surface;
    create_native_function(sdl, "blitSurface", blit_surface_);
    create_native_function(sdl, "setColors", &sdl::set_colors);
    //create_native_function(sdl, "createRGBSurface", &sdl::create_RGB_surface);
    sdl.define_property("SRCALPHA", value(SDL_SRCALPHA));
    sdl.define_property("RLEACCEL", value(SDL_RLEACCEL));
    create_native_function(sdl, "setAlpha", &sdl::set_alpha);
    sdl.define_property("SRCCOLORKEY", value(SDL_SRCCOLORKEY));
    create_native_function(sdl, "setColorKey", &sdl::set_color_key);
    create_native_function(sdl, "displayFormat", &sdl::display_format);
    create_native_function(sdl, "displayFormatAlpha", &sdl::display_format_alpha);
    create_native_function(sdl, "videoDriverName", &sdl::video_driver_name);
    create_native_function(sdl, "setGamma", &::SDL_SetGamma);
    create_native_function(sdl, "mapRGB", &sdl::map_RGB);
    create_native_function(sdl, "mapRGBA", &sdl::map_RGBA);
    create_native_function(sdl, "getRGB", &sdl::get_RGB);
    create_native_function(sdl, "setClipRect", &sdl::set_clip_rect);
    create_native_function(sdl, "getClipRect", &sdl::get_clip_rect);
    create_native_function(sdl, "fillRect", &sdl::fill_rect);

    // Window Management
    create_native_function(sdl, "WMSetCaption", &::SDL_WM_SetCaption);
    create_native_function(sdl, "WMToggleFullScreen", &sdl::wm_toggle_fullscreen);
    create_native_function(sdl, "WMSetIcon", &sdl::wm_set_icon);
    create_native_function(sdl, "WMIconifyWindow", &::SDL_WM_IconifyWindow);
    sdl.define_property("GRAB_QUERY", value((int)SDL_GRAB_QUERY));
    sdl.define_property("GRAB_OFF", value((int)SDL_GRAB_OFF));
    sdl.define_property("GRAB_ON", value((int)SDL_GRAB_ON));
    create_native_function(sdl, "WMGrabInput", &sdl::wm_grab_input);

    // Events
    sdl.define_property("key", key_object());
    sdl.define_property("kmod", mod_object());
    create_native_function(sdl, "enableUNICODE", &::SDL_EnableUNICODE);
    create_native_function(sdl, "enableKeyRepeat", &::SDL_EnableKeyRepeat);
    create_native_function(sdl, "getKeyName", &sdl::get_key_name);
    sdl.define_property("APPMOUSEFOCUS", value((int)SDL_APPMOUSEFOCUS));
    sdl.define_property("APPINPUTFOCUS", value((int)SDL_APPINPUTFOCUS));
    sdl.define_property("APPACTIVE", value((int)SDL_APPACTIVE));
    create_native_function(sdl, "getAppState", &sdl::get_app_state);
#if 0
    create_native_function(sdl, "startTextInput", &::SDL_StartTextInput);
    create_native_function(sdl, "stopTextInput", &::SDL_StopTextInput);
#endif
    sdl.define_property("IGNORE", value((int)SDL_IGNORE));
    sdl.define_property("ENABLE", value((int)SDL_ENABLE));
    sdl.define_property("QUERY", value((int)SDL_QUERY));
    create_native_function(sdl, "eventState", &sdl::event_state);
    load_class<sdl::ActiveEvent>(sdl);
    load_class<sdl::KeyboardEvent>(sdl);
    load_class<sdl::MouseMotionEvent>(sdl);
    load_class<sdl::MouseButtonEvent>(sdl);
    load_class<sdl::JoyAxisEvent>(sdl);
    load_class<sdl::JoyBallEvent>(sdl);
    load_class<sdl::JoyHatEvent>(sdl);
    load_class<sdl::JoyButtonEvent>(sdl);
    load_class<sdl::ResizeEvent>(sdl);
    load_class<sdl::ExposeEvent>(sdl);
    load_class<sdl::QuitEvent>(sdl);
    load_class<sdl::Event>(sdl);
    sdl.define_property("ACTIVEEVENT", value((int)SDL_ACTIVEEVENT));
    sdl.define_property("KEYDOWN", value((int)SDL_KEYDOWN));
    sdl.define_property("KEYUP", value((int)SDL_KEYUP));
    sdl.define_property("MOUSEMOTION", value((int)SDL_MOUSEMOTION));
    sdl.define_property("MOUSEBUTTONDOWN", value((int)SDL_MOUSEBUTTONDOWN));
    sdl.define_property("MOUSEBUTTONUP", value((int)SDL_MOUSEBUTTONUP));
    sdl.define_property("JOYAXISMOTION", value((int)SDL_JOYAXISMOTION));
    sdl.define_property("JOYBALLMOTION", value((int)SDL_JOYBALLMOTION));
    sdl.define_property("JOYHATMOTION", value((int)SDL_JOYHATMOTION));
    sdl.define_property("JOYBUTTONDOWN", value((int)SDL_JOYBUTTONDOWN));
    sdl.define_property("JOYBUTTONUP", value((int)SDL_JOYBUTTONUP));
    sdl.define_property("VIDEORESIZE", value((int)SDL_VIDEORESIZE));
    sdl.define_property("VIDEOEXPOSE", value((int)SDL_VIDEOEXPOSE));
    sdl.define_property("QUIT", value((int)SDL_QUIT));
    sdl.define_property("USEREVENT", value((int)SDL_USEREVENT));
    sdl.define_property("SYSWMEVENT", value((int)SDL_SYSWMEVENT));
    create_native_function(sdl, "pollEvent", &sdl::poll_event);
    create_native_function(sdl, "waitEvent", &sdl::wait_event);
    create_native_function(sdl, "getModState", &sdl::get_mod_state);
    create_native_function(sdl, "setModState", &sdl::set_mod_state);
    create_native_function(sdl, "pumpEvents", &::SDL_PumpEvents);
    create_native_function(sdl, "getMouseState", &sdl::get_mouse_state);
    create_native_function(sdl, "getRelativeMouseState", &sdl::get_relative_mouse_state);
    create_native_function(sdl, "joystickEventState", &::SDL_JoystickEventState);

    // Mouse
    create_native_function(sdl, "warpMouse", &::SDL_WarpMouse);
    create_native_function(sdl, "showCursor", &::SDL_ShowCursor);

    // Joystick
    create_native_function(sdl, "numJoysticks", &::SDL_NumJoysticks);
    create_native_function(sdl, "joystickName", &::SDL_JoystickName);
    create_native_function(sdl, "joystickOpened", &::SDL_JoystickOpened);
    create_native_function(sdl, "joystickUpdate", &::SDL_JoystickUpdate);
    load_class<sdl::Joystick>(sdl);
    create_native_function(sdl, "joystickOpen", &sdl::joystick_open);
    create_native_function(sdl, "joystickClose", &sdl::joystick_close);
    create_native_function(sdl, "joystickIndex", &sdl::joystick_index);
    create_native_function(sdl, "joystickNumAxes", &sdl::joystick_num_axes);
    create_native_function(sdl, "joystickNumBalls", &sdl::joystick_num_balls);
    create_native_function(sdl, "joystickNumHats", &sdl::joystick_num_hats);
    create_native_function(sdl, "joystickNumButtons", &sdl::joystick_num_buttons);
    create_native_function(sdl, "joystickGetAxis", &sdl::joystick_get_axis);
    create_native_function(sdl, "joystickGetHat", &sdl::joystick_get_hat);
    create_native_function(sdl, "joystickGetButton", &sdl::joystick_get_button);
    create_native_function(sdl, "joystickGetBall", &sdl::joystick_get_ball);
  }
}

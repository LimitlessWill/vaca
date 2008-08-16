// Vaca - Visual Application Components Abstraction
// Copyright (c) 2005, 2006, 2007, 2008, David A. Capello
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
// * Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in
//   the documentation and/or other materials provided with the
//   distribution.
// * Neither the name of the Vaca nor the names of its contributors
//   may be used to endorse or promote products derived from this
//   software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
// COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
// OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef VACA_WIDGETCLASS_HPP
#define VACA_WIDGETCLASS_HPP

#include "Vaca/base.h"
#include "Vaca/String.h"

namespace Vaca {

class VACA_DLL WidgetClassName
{
public:
  static const WidgetClassName None;

private:
  String m_className;

  WidgetClassName();		// None constructor

public:
  explicit WidgetClassName(const String& className);
  WidgetClassName(const WidgetClassName& className);
  virtual ~WidgetClassName();

  WidgetClassName& operator=(const WidgetClassName& className);
  bool operator==(const WidgetClassName& className) const;
  bool operator!=(const WidgetClassName& className) const;

  LPCTSTR toLPCTSTR() const;
};

/**
 * Base class to retrieve information about a new Win32 class to be
 * registered using the @c Register class.
 *
 * Vaca needs this class to register a Windows class (through the
 * Win32 RegisterClassEx function) before to construct the widget
 * because Widget::Widget calls the Win32 CreateWindowEx function. The
 * only way to register the class before and automatically, is using
 * multiple-inheritance.
 *
 * Here is an example that show how you can register your own widget
 * class before to create it:
 *
 * @code
 * class MyWidgetClass : public WidgetClass
 * {
 * public:
 *   static WidgetClassName getClassName()
 *   { return WidgetClassName("Vaca.MyWidget"); }
 * };
 * @endcode
 *
 * Then you should create your how @c MyWidget using:
 *
 * @code
 * class MyWidget : public Register<MyWidgetClass>, public Widget
 * {
 * public:
 *   MyWidget::MyWidget(..., Widget* parent, Style style = ...)
 *     : Widget(MyWidgetClass::getClassName(), parent, style)
 *   {
 *     // ...Your code here...
 *   }
 *   ...
 * };
 * @endcode
 *
 * @see @ref TN001.
 */
class WidgetClass
{
public:

  /**
   * Returns the class name to be used in the lpszClassName field of
   * the WNDCLASSEX structure in the @link Vaca::Register#Register Register constructor@endlink.
   */
  static WidgetClassName getClassName()
  { return WidgetClassName("Vaca.Widget"); }

  /**
   * Returns the set of CS_ Win32 flags.
   * 
   * All Widgets by default received double-clicks, so it returns
   * CS_DBLCLKS.
   * 
   */
  static int getStyle() { return CS_DBLCLKS; }

  static int getColor() { return COLOR_3DFACE; }

  static int getWndExtra() { return 0; }

};

} // namespace Vaca

#endif
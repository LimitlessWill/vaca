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

#ifndef VACA_FINDTEXTDIALOG_HPP
#define VACA_FINDTEXTDIALOG_HPP

#include "Vaca/base.hpp"
#include "Vaca/Dialog.hpp"
#include "Vaca/String.hpp"

namespace Vaca {

class Widget;

/**
 * A common dialog box to find (or replace) text.
 */
class VACA_DLL FindTextDialog : public Dialog
{
  bool m_replace;
  UINT m_findMsgId;
  FINDREPLACE m_findReplace;

public:

  FindTextDialog(bool replace, Widget* parent);
  virtual ~FindTextDialog();

  String getFindWhat();
  String getReplaceWith();

  bool isWholeWord();
  bool isMatchCase();
  bool isBackward();
  bool isForward();

  Signal0<void> FindNext;
  Signal0<void> Replace;
  Signal0<void> ReplaceAll;
  Signal0<void> Cancel;

protected:

  // new events
  virtual void onFindNext();
  virtual void onReplace();
  virtual void onReplaceAll();
  virtual void onCancel();

  virtual bool wndProc(UINT message, WPARAM wParam, LPARAM lParam, LRESULT& lResult);
private:
  virtual HWND createHWND(LPCTSTR className, Widget* parent, Style style);
  static UINT_PTR CALLBACK hookProc(HWND hdlg, UINT uiMsg, WPARAM wParam, LPARAM lParam);

};

} // namespace Vaca

#endif

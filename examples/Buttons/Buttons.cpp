// Vaca - Visual Application Components Abstraction
// Copyright (c) 2005-2009 David Capello
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
// * Neither the name of the author nor the names of its contributors
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

#include <Vaca/Vaca.h>

using namespace Vaca;

class MainFrame : public Frame
{
  Widget m_leftPanel;
  Widget m_rightPanel;
  Button m_button;
  ToggleButton m_toggleButton;
  CheckBox m_checkBox;
  RadioGroup m_radioGroup1;
  RadioGroup m_radioGroup2;
  RadioButton m_radioButton1;
  RadioButton m_radioButton2;
  RadioButton m_radioButton3;
  RadioButton m_radioButton4;
  Label m_label1;
  Label m_label2;
  ToggleButton m_disableButton;
  int m_actions;

public:

  MainFrame()
    : Frame(L"Buttons")
    , m_leftPanel(this)
    , m_rightPanel(this)
    , m_button(L"Button", &m_leftPanel)
    , m_toggleButton(L"ToggleButton", &m_leftPanel)
    , m_checkBox(L"CheckBox", &m_leftPanel)
    , m_radioButton1(L"RadioButton1_Group1", m_radioGroup1, &m_leftPanel)
    , m_radioButton2(L"RadioButton2_Group1", m_radioGroup1, &m_leftPanel)
    , m_radioButton3(L"RadioButton3_Group2", m_radioGroup2, &m_leftPanel)
    , m_radioButton4(L"RadioButton4_Group2", m_radioGroup2, &m_leftPanel)
    , m_label1(L"", &m_rightPanel)
    , m_label2(L"", &m_rightPanel)
    , m_disableButton(L"All Disabled", &m_rightPanel)
    , m_actions(-1)
  {
    setLayout(new BoxLayout(Orientation::Horizontal, true)); // homogeneous
    m_leftPanel.setLayout(new BoxLayout(Orientation::Vertical, true)); // homogeneous
    m_rightPanel.setLayout(new BoxLayout(Orientation::Vertical, false)); // no-homogeneous

    updateLabel();

    bindButton(m_button);
    bindButton(m_toggleButton);
    bindButton(m_checkBox);
    bindButton(m_radioButton1);
    bindButton(m_radioButton2);
    bindButton(m_radioButton3);
    bindButton(m_radioButton4);

    m_disableButton.Action.connect(&MainFrame::onToggleDisabled, this);

    setSize(getPreferredSize());
    center();
  }

private:

  void bindButton(ButtonBase& button)
  {
    button.Action.connect(Bind(&MainFrame::updateLabel, this));
  }

  void updateLabel()
  {
    m_actions++;
    m_label1.setText(format_string(L"Action signal fired %d time(s)", m_actions));
    m_label2.setText(format_string(L"CheckBox is %s", m_checkBox.isSelected() ? L"checked":
										L"unchecked"));

    // the labels are bigger and bigger, so a relayout isn't a bad idea
    layout();
  }

  void onToggleDisabled(Event& ev)
  {
    bool state = !m_disableButton.isSelected();
    m_button.setEnabled(state);
    m_toggleButton.setEnabled(state);
    m_checkBox.setEnabled(state);
    m_radioButton1.setEnabled(state);
    m_radioButton2.setEnabled(state);
    m_radioButton3.setEnabled(state);
    m_radioButton4.setEnabled(state);
  }

};

//////////////////////////////////////////////////////////////////////

class Example : public Application
{
  MainFrame m_mainFrame;

  virtual void main() {
    m_mainFrame.setVisible(true);
  }
};

int VACA_MAIN()
{
  Example app;
  app.run();
  return 0;
}

//$Id: examplewindow.cc 836 2007-05-09 03:02:38Z jjongsma $ -*- c++ -*-

/* gtkmm example Copyright (C) 2002 gtkmm development team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "examplewindow.h"

ExampleWindow::ExampleWindow()
: m_VBox(Gtk::ORIENTATION_VERTICAL),
  m_Label("Select cells in the grid, click Copy, then open a second "
        "instance of this example to try pasting the copied data."),
  m_ButtonA1("A1"), m_ButtonA2("A2"), m_ButtonB1("B1"), m_ButtonB2("B2"),
  m_Button_Copy("_Copy", /* mnemonic= */ true), m_Button_Paste("_Paste", true)
{
  set_title("Gtk::Clipboard example");
  set_border_width(12);

  add(m_VBox);

  m_VBox.pack_start(m_Label, Gtk::PACK_SHRINK);

  //Fill Grid:
  m_VBox.pack_start(m_Grid);
  m_Grid.set_row_homogeneous(true);
  m_Grid.set_column_homogeneous(true);
  m_Grid.attach(m_ButtonA1, 0, 0, 1, 1);
  m_Grid.attach(m_ButtonA2, 1, 0, 1, 1);
  m_Grid.attach(m_ButtonB1, 0, 1, 1, 1);
  m_Grid.attach(m_ButtonB2, 1, 1, 1, 1);

  //Add ButtonBox to bottom:
  m_VBox.pack_start(m_ButtonBox, Gtk::PACK_SHRINK);
  m_VBox.set_spacing(6);

  //Fill ButtonBox:
  m_ButtonBox.set_layout(Gtk::BUTTONBOX_END);
  m_ButtonBox.pack_start(m_Button_Copy, Gtk::PACK_SHRINK);
  m_Button_Copy.signal_clicked().connect(sigc::mem_fun(*this,
              &ExampleWindow::on_button_copy) );
  m_ButtonBox.pack_start(m_Button_Paste, Gtk::PACK_SHRINK);
  m_Button_Paste.signal_clicked().connect(sigc::mem_fun(*this,
              &ExampleWindow::on_button_paste) );

  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_copy()
{
  //Build a string representation of the stuff to be copied:
  //Ideally you would use XML, with an XML parser here:
  Glib::ustring strData;
  strData += m_ButtonA1.get_active() ? "1" : "0";
  strData += m_ButtonA2.get_active() ? "1" : "0";
  strData += m_ButtonB1.get_active() ? "1" : "0";
  strData += m_ButtonB2.get_active() ? "1" : "0";

  Glib::RefPtr<Gtk::Clipboard> refClipboard = Gtk::Clipboard::get();
  refClipboard->set_text(strData);
}

void ExampleWindow::on_button_paste()
{
  //Tell the clipboard to call our method when it is ready:
  Glib::RefPtr<Gtk::Clipboard> refClipboard = Gtk::Clipboard::get();
  refClipboard->request_text(sigc::mem_fun(*this,
              &ExampleWindow::on_clipboard_text_received) );
}

void ExampleWindow::on_clipboard_text_received(const Glib::ustring& text)
{
  //See comment in on_button_copy() about this silly clipboard format.
  if(text.size() >= 4)
  {
    m_ButtonA1.set_active( text[0] == '1' );
    m_ButtonA2.set_active( text[1] == '1' );
    m_ButtonB1.set_active( text[2] == '1' );
    m_ButtonB2.set_active( text[3] == '1' );
  }
}

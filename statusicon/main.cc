//$Id: main.cc 836 2007-05-09 03:02:38Z jjongsma $ -*- c++ -*-

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

#include <gtkmm.h>

int main(int argc, char *argv[])
{
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

  //Use your own icon in real life.
  Glib::RefPtr<Gtk::StatusIcon> status_icon =
      Gtk::StatusIcon::create("help-browser");
  status_icon->set_tooltip_text("gtkmm StatusIcon example tooltip.");

  //Show a window:
  //The program will stop, and the status icon will disappear, when the window
  //is closed.
  Gtk::Window window;
  window.set_title("gtkmm StatusIcon example.");
  window.set_default_size(300, 300);
  return app->run(window); //Shows the window and returns when it is closed.
}

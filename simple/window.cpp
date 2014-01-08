#include <gtkmm.h>

#include "window.h"

Window::Window() :
	m_Button("Show Dialog")
{
	set_title("Gtk::Dialog example");

	add(m_Button);
	m_Button.signal_clicked().connect(sigc::mem_fun(*this, &Window::on_button_clicked) );

	show_all_children();
}

Window::~Window()
{
}

void Window::on_button_clicked()
{
	Gtk::Dialog dialog;
	dialog.set_default_size(100,100);

	const Glib::RefPtr<const Gtk::IconTheme> m_IconTheme (Gtk::IconTheme::get_default());
	Gtk::Image m_Image;
	const char *icon_name = "abrt";
	std::vector<int> sizes = m_IconTheme->get_icon_sizes(icon_name);
	const std::vector<int>::const_iterator sizeiter = std::max_element(sizes.begin(), sizes.end());
	const int maxsize = (sizeiter != sizes.end() && *sizeiter > 48) ? *sizeiter : 48;
	printf ("max size = %d\n", maxsize);

	Glib::RefPtr< Gdk::Pixbuf > pb = m_IconTheme->load_icon(icon_name, maxsize, Gtk::ICON_LOOKUP_USE_BUILTIN);
	printf ("pb = %d\n", !!pb);

	Gtk::Label h ("hello");
	Gtk::Label b ("goodbye");
	Gtk::Button close ("_Close", true);
	m_Image.set(pb);
	dialog.get_content_area()->add(h);
	dialog.get_content_area()->add(m_Image);
	dialog.get_content_area()->add(b);
	dialog.get_action_area()->add(close);
	dialog.show_all();

	dialog.run();
}


#include "examplewindow.h"

#include <gtkmm.h>

ExampleWindow::ExampleWindow() :
	m_close_button_label("Show close button:", 1.0, 0.5),
	m_title_label("Title:", 1.0, 0.5),
	m_subtitle_label("Subtitle:", 1.0, 0.5)
{
	// Window properties
	set_title("HeaderBar Example");
	set_border_width(12);

	// Button
	m_button.set_image_from_icon_name("go-home-symbolic");
	m_button.signal_clicked().connect(sigc::mem_fun(*this, &ExampleWindow::on_button_clicked));

	// Entries
	m_title_entry.set_text("HeaderBar title");
	m_subtitle_entry.set_text("HeaderBar subtitle");
	m_title_entry.signal_activate().connect(sigc::mem_fun(*this, &ExampleWindow::on_title_entry_activate));
	m_subtitle_entry.signal_activate().connect(sigc::mem_fun(*this, &ExampleWindow::on_subtitle_entry_activate));

	// Header bar
	on_title_entry_activate();
	on_subtitle_entry_activate();
	m_header_bar.set_show_close_button();
	m_header_bar.pack_start(m_button);

	// Set headerbar as titlebar
	set_titlebar(m_header_bar);

	// Switch
	m_switch.set_active(true);
	m_switch.property_active().signal_changed().connect(sigc::mem_fun(*this, &ExampleWindow::on_switch_active_changed));

	// Layout
	m_grid.set_column_spacing(6);
	m_grid.set_row_spacing(6);
	m_grid.attach(m_close_button_label, 0, 0, 1, 1);
	m_grid.attach(m_switch, 1, 0, 1, 1);
	m_grid.attach(m_title_label, 0, 1, 1, 1);
	m_grid.attach(m_title_entry, 1, 1, 1, 1);
	m_grid.attach(m_subtitle_label, 0, 2, 1, 1);
	m_grid.attach(m_subtitle_entry, 1, 2, 1, 1);
	add(m_grid);

	show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_switch_active_changed()
{
	bool show_close_button = m_switch.get_active();
	m_header_bar.set_show_close_button(show_close_button);
}

void ExampleWindow::on_title_entry_activate()
{
	const Glib::ustring title = m_title_entry.get_text();
	if(!title.empty())
	{
		m_header_bar.set_title(title);
	}
}

void ExampleWindow::on_subtitle_entry_activate()
{
	const Glib::ustring subtitle = m_subtitle_entry.get_text();
	m_header_bar.set_subtitle(subtitle);
}

void ExampleWindow::on_button_clicked()
{
	Gtk::MessageDialog dialog(*this, "Button clicked");
	Gtk::Image i;
	i.set_from_icon_name ("dialog-password", Gtk::BuiltinIconSize::ICON_SIZE_DIALOG);
	dialog.set_image(i);
	dialog.show_all();
	dialog.run();
}


#ifndef GTKMM_EXAMPLEWINDOW_H
#define GTKMM_EXAMPLEWINDOW_H

#include <gtkmm.h>

class ExampleWindow : public Gtk::Window
{
public:
	ExampleWindow();
	virtual ~ExampleWindow();

protected:
	//Signal handlers:
	void on_menu_file_new_generic();
	void on_menu_file_quit();
	void on_menu_others();

	void on_menu_choices(const Glib::ustring& parameter);
	void on_menu_choices_other(int parameter);
	void on_menu_toggle();

	//Child widgets:
	Gtk::Box m_Box;

	Glib::RefPtr<Gtk::Builder> m_refBuilder;

	//Two sets of choices:
	Glib::RefPtr<Gio::SimpleAction> m_refChoice, m_refChoiceOther;

	Glib::RefPtr<Gio::SimpleAction> m_refToggle;
};

#endif //GTKMM_EXAMPLEWINDOW_H

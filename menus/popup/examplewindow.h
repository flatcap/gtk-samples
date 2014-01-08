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
	virtual bool on_button_press_event(GdkEventButton* event);
	void on_menu_file_popup_generic();
	void on_popup_menu_position (int& x, int& y, bool& push_in);

	//Child widgets:
	Gtk::Box m_Box;
	Gtk::EventBox m_EventBox;
	Gtk::Label m_Label;

	Gtk::Box inner;

	Gtk::Entry before1;
	Gtk::Entry before2;
	Gtk::Entry after1;
	Gtk::Entry after2;

	int menux, menuy;

	Glib::RefPtr<Gtk::Builder> m_refBuilder;

	Gtk::Menu* m_pMenuPopup;
};

#endif //GTKMM_EXAMPLEWINDOW_H

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
	virtual bool on_eventbox_button_press(GdkEventButton* event);

	//Child widgets:
	Gtk::EventBox m_EventBox;
	Gtk::Label m_Label;
};

#endif //GTKMM_EXAMPLEWINDOW_H

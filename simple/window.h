#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <gtkmm.h>

class Window : public Gtk::Window
{
public:
	Window();
	virtual ~Window();

protected:
	void on_button_clicked();

	Gtk::Button m_Button;
};

#endif // _WINDOW_H_


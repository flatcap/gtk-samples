#include <iostream>

#include <gtkmm/dialog.h>
#include <gtkmm/application.h>

class Window : public Gtk::Window
{
public:
	Window();
	virtual ~Window();

protected:
	void on_button_clicked (void);
	void on_dialog_response (int response_id);

	Gtk::Button button;
	Gtk::Dialog* dialog = nullptr;
};

Window::Window() :
	button ("Show/Hide non-modal dialog")
{
	set_title ("Non-modal example");

	add (button);

	button.signal_clicked().connect (sigc::mem_fun (*this, &Window::on_button_clicked));

	show_all_children();
}

Window::~Window()
{
}

void
Window::on_button_clicked (void)
{
	if (dialog) {
		delete dialog;
		dialog = nullptr;
	} else {
		dialog = new Gtk::Dialog ("Non-modal dialog", false);
		dialog->set_default_size (400, 200);
		dialog->set_transient_for (*this);
		dialog->signal_response().connect (sigc::mem_fun (*this, &Window::on_dialog_response));
		dialog->show();
	}
}

void
Window::on_dialog_response (int response_id)
{
	switch (response_id) {
		case Gtk::RESPONSE_DELETE_EVENT:
			std::cout << "Delete clicked." << std::endl;
			delete dialog;
			dialog = nullptr;
			break;
		default:
			std::cout << "Unexpected button clicked, response_id=" << response_id << std::endl;
			break;
	}
}

int
main (int argc, char *argv[])
{
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create (argc, argv, "org.gtkmm.example");

	Window window;

	return app->run (window);
}


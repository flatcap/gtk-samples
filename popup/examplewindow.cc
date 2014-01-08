#include "examplewindow.h"
#include <iostream>

#include <gtkmm/application.h>

int main(int argc, char *argv[])
{
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

	ExampleWindow window;

	//Shows the window and returns when it is closed.
	return app->run(window);
}

ExampleWindow::ExampleWindow() :
	m_Box(Gtk::ORIENTATION_VERTICAL),
	m_Label("Right-click to see the popup menu."),
	m_pMenuPopup(0)
{
	set_title("popup example");
	set_default_size(200, 200);

	add(m_Box);

	//Add an event box that can catch button_press events:
	m_Box.pack_start(m_EventBox);
	m_EventBox.signal_button_press_event().connect(sigc::mem_fun(*this, &ExampleWindow::on_button_press_event) );
	m_EventBox.add(m_Label);

	//Create actions:

	//Fill menu:

	Glib::RefPtr<Gio::SimpleActionGroup> refActionGroup = Gio::SimpleActionGroup::create();

	//File|New sub menu:
	//These menu actions would normally already exist for a main menu, because a
	//context menu should not normally contain menu items that are only available
	//via a context menu.

	refActionGroup->add_action("edit", sigc::mem_fun(*this, &ExampleWindow::on_menu_file_popup_generic));
	//TODO: How to specify "<control>P" as an accelerator.
	refActionGroup->add_action("process", sigc::mem_fun(*this, &ExampleWindow::on_menu_file_popup_generic));
	refActionGroup->add_action("remove", sigc::mem_fun(*this, &ExampleWindow::on_menu_file_popup_generic));

	insert_action_group("examplepopup", refActionGroup);

	m_refBuilder = Gtk::Builder::create();

	//Layout the actions in a menubar and toolbar:
	Glib::ustring ui_info =
		"<interface>"
		"	 <menu id='menu-examplepopup'>"
		"		 <section>"
		"			 <item>"
		"				 <attribute name='label' translatable='yes'>Edit</attribute>"
		"				 <attribute name='action'>examplepopup.edit</attribute>"
		"			 </item>"
		"			 <item>"
		"				 <attribute name='label' translatable='yes'>Process</attribute>"
		"				 <attribute name='action'>examplepopup.process</attribute>"
		"			 </item>"
		"			 <item>"
		"				 <attribute name='label' translatable='yes'>Remove</attribute>"
		"				 <attribute name='action'>examplepopup.remove</attribute>"
		"			 </item>"
		"		 </section>"
		"	 </menu>"
		"</interface>";

	try
	{
		m_refBuilder->add_from_string(ui_info);
	}
	catch(const Glib::Error& ex)
	{
		std::cerr << "building menus failed: " << ex.what();
	}

	//Get the menu:
	Glib::RefPtr<Glib::Object> object = m_refBuilder->get_object("menu-examplepopup");
	Glib::RefPtr<Gio::Menu> gmenu = Glib::RefPtr<Gio::Menu>::cast_dynamic(object);
	if(!gmenu)
		g_warning("GMenu not found");

	m_pMenuPopup = new Gtk::Menu(gmenu);

	show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_menu_file_popup_generic()
{
	 std::cout << "A popup menu item was selected." << std::endl;
}

bool ExampleWindow::on_button_press_event(GdkEventButton* event)
{
	if( (event->type == GDK_BUTTON_PRESS) && (event->button == 3) )
	{
		if(!m_pMenuPopup->get_attach_widget())
		{
			m_pMenuPopup->attach_to_widget(*this);
		}

		if(m_pMenuPopup)
			m_pMenuPopup->popup(event->button, event->time);


		return true; //It has been handled.
	}
	else
		return false;
}


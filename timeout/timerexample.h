#ifndef GTKMM_EXAMPLE_TIMEREXAMPLE_H
#define GTKMM_EXAMPLE_TIMEREXAMPLE_H

#include <gtkmm.h>
#include <iostream>
#include <map>

class TimerExample : public Gtk::Window
{
public:
	TimerExample();

protected:
	// signal handlers
	void on_button_add_timer();
	void on_button_delete_timer();
	void on_button_quit();

	// This is the callback function the timeout will call
	bool on_timeout(int timer_number);

	// Member data:

	Gtk::Box m_Box;
	Gtk::Button m_ButtonAddTimer, m_ButtonDeleteTimer, m_ButtonQuit;

	// Keep track of the timers being added:
	int m_timer_number;

	// These two constants are initialized in the constructor's member initializer:
	const int count_value;
	const int timeout_value;

	// STL map for storing our connections
	std::map<int, sigc::connection> m_timers;

	// STL map for storing our timer values.
	// Each timer counts back from COUNT_VALUE to 0 and is removed when it reaches 0
	std::map<int, int> m_counters;
};

#endif // GTKMM_EXAMPLE_TIMEREXAMPLE_H

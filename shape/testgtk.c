#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#include "gtk/gtk.h"
#include "gdk/gdk.h"
#include "gdk/gdkkeysyms.h"

typedef struct _cursoroffset {gint x,y;} CursorOffset;

static void
shape_pressed (GtkWidget *widget, GdkEventButton *event)
{
	CursorOffset *p;

	/* ignore double and triple click */
	if (event->type != GDK_BUTTON_PRESS)
		return;

	p = g_object_get_data (G_OBJECT (widget), "cursor_offset");
	p->x = (int) event->x;
	p->y = (int) event->y;

	gtk_grab_add (widget);
	gdk_device_grab (gdk_event_get_device ((GdkEvent*)event),
			gtk_widget_get_window (widget),
			GDK_OWNERSHIP_NONE,
			TRUE,
			GDK_BUTTON_RELEASE_MASK | GDK_BUTTON_MOTION_MASK | GDK_POINTER_MOTION_HINT_MASK,
			NULL,
			event->time);
}

static void
shape_released (GtkWidget *widget, GdkEventButton *event)
{
	gtk_grab_remove (widget);
	gdk_device_ungrab (gdk_event_get_device ((GdkEvent*)event), event->time);
}

static void
shape_motion (GtkWidget *widget, GdkEventMotion *event)
{
	gint xp, yp;
	CursorOffset *p;

	p = g_object_get_data (G_OBJECT (widget), "cursor_offset");

	/*
	 * Can't use event->x / event->y here
	 * because I need absolute coordinates.
	 */
	gdk_window_get_device_position (gdk_screen_get_root_window (gtk_widget_get_screen (widget)),
					gdk_event_get_device ((GdkEvent *) event),
					&xp, &yp, NULL);
	gtk_window_move (GTK_WINDOW (widget), xp - p->x, yp - p->y);
}

GtkWidget *
shape_create_icon (GdkScreen *screen)
{
	GtkWidget *window;
	GtkWidget *image;
	GtkWidget *fixed;
	CursorOffset* icon_pos;
	cairo_surface_t *mask;
	cairo_region_t *mask_region;
	GdkPixbuf *pixbuf;
	cairo_t *cr;

	window = gtk_window_new (GTK_WINDOW_POPUP);
	gtk_window_set_screen (GTK_WINDOW (window), screen);

	fixed = gtk_fixed_new();
	gtk_widget_set_size_request (fixed, 100, 100);
	gtk_container_add (GTK_CONTAINER (window), fixed);
	gtk_widget_show (fixed);

	gtk_widget_set_events (window, gtk_widget_get_events (window) | GDK_BUTTON_MOTION_MASK | GDK_POINTER_MOTION_HINT_MASK | GDK_BUTTON_PRESS_MASK);

	gtk_widget_realize (window);

	pixbuf = gdk_pixbuf_new_from_file ("FilesQueue.xpm", NULL);

	mask = cairo_image_surface_create (CAIRO_FORMAT_A1, gdk_pixbuf_get_width (pixbuf), gdk_pixbuf_get_height (pixbuf));
	cr = cairo_create (mask);
	gdk_cairo_set_source_pixbuf (cr, pixbuf, 0, 0);
	cairo_paint (cr);
	cairo_destroy (cr);

	mask_region = gdk_cairo_region_create_from_surface (mask);

	cairo_region_translate (mask_region, 0, 0);

	image = gtk_image_new_from_pixbuf (pixbuf);
	gtk_fixed_put (GTK_FIXED (fixed), image, 0, 0);
	gtk_widget_show (image);

	gtk_widget_shape_combine_region (window, mask_region);

	cairo_region_destroy (mask_region);
	cairo_surface_destroy (mask);
	g_object_unref (pixbuf);

	g_signal_connect (window, "button_press_event", G_CALLBACK (shape_pressed), NULL);
	g_signal_connect (window, "button_release_event", G_CALLBACK (shape_released), NULL);
	g_signal_connect (window, "motion_notify_event", G_CALLBACK (shape_motion), NULL);

	icon_pos = g_new (CursorOffset, 1);
	g_object_set_data (G_OBJECT (window), "cursor_offset", icon_pos);

	gtk_window_move (GTK_WINDOW (window), 400, 400);
	gtk_widget_show (window);

	return window;
}

void
create_shapes (GtkWidget *widget)
{
	static GtkWidget *sheets = NULL;
	GdkScreen *screen = gtk_widget_get_screen (widget);

	if (!sheets) {
		sheets = shape_create_icon (screen);
		g_signal_connect (sheets, "destroy", G_CALLBACK (gtk_widget_destroyed), &sheets);
	} else {
		gtk_widget_destroy (sheets);
	}
}

int
main (int argc, char *argv[])
{
	gtk_init (&argc, &argv);

	GtkWidget *window;
	GtkWidget *button;

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

	g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

	button = gtk_button_new_with_label ("shapes");
	g_signal_connect (button, "clicked", G_CALLBACK (create_shapes), NULL);
	gtk_container_add (GTK_CONTAINER (window), button);

	gtk_widget_show_all (window);

	gtk_main();

	while (g_main_context_pending (NULL))
		g_main_context_iteration (NULL, FALSE);

	return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

int state1 = 0;
int state2 = 0;
int state3 = 0;
int state4 = 0;
int state5 = 0;
int state6 = 0;
int state7 = 0;

GtkWidget *b1, *b2, *b3, *b4, *b5, *b6, *b7;
GtkWidget *x1, *x2, *x3, *x4, *x5, *x6, *x7;
GtkWidget *c1, *c2, *c3, *c4, *c5, *c6, *c7;

GdkRGBA red   = { 0.7, 0.0, 0.0, 1.0 };
GdkRGBA green = { 0.0, 0.7, 0.0, 1.0 };

/**
 * button_press
 */
static gboolean
button_press (GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
	int shift = FALSE;

	GdkEventButton *e = (GdkEventButton*) event;

	if ((e->type != GDK_BUTTON_PRESS) &&
	    (e->type != GDK_2BUTTON_PRESS))
		return TRUE;

	shift = ((e->type  == GDK_2BUTTON_PRESS) ||
		 (e->state && GDK_MOD1_MASK));

	if (widget == b1) { state1 = 1 - state1; gtk_toggle_button_set_active ((GtkToggleButton*) x1, state1); }
	if (widget == b2) { state2 = 1 - state2; gtk_toggle_button_set_active ((GtkToggleButton*) x2, state2); }
	if (widget == b3) { state3 = 1 - state3; gtk_toggle_button_set_active ((GtkToggleButton*) x3, state3); }
	if (widget == b4) { state4 = 1 - state4; gtk_toggle_button_set_active ((GtkToggleButton*) x4, state4); }
	if (widget == b5) { state5 = 1 - state5; gtk_toggle_button_set_active ((GtkToggleButton*) x5, state5); }
	if (widget == b6) { state6 = 1 - state6; gtk_toggle_button_set_active ((GtkToggleButton*) x6, state6); }
	if (widget == b7) { state7 = 1 - state7; gtk_toggle_button_set_active ((GtkToggleButton*) x7, state7); }

	if ((widget == b1) && shift) {
		state2 = state3 = state4 = state5 = state6 = state7 = state1;
	}

	if ((widget == b2) && shift) {
		state3 = state4 = state5 = state6 = state7 = state2;
	}

	if ((widget == b5) && shift) {
		state6 = state7 = state5;
	}

	gtk_color_chooser_set_rgba ((GtkColorChooser*) c1, (state1 == 1) ? &green : &red);
	gtk_color_chooser_set_rgba ((GtkColorChooser*) c2, (state2 == 1) ? &green : &red);
	gtk_color_chooser_set_rgba ((GtkColorChooser*) c3, (state3 == 1) ? &green : &red);
	gtk_color_chooser_set_rgba ((GtkColorChooser*) c4, (state4 == 1) ? &green : &red);
	gtk_color_chooser_set_rgba ((GtkColorChooser*) c5, (state5 == 1) ? &green : &red);
	gtk_color_chooser_set_rgba ((GtkColorChooser*) c6, (state6 == 1) ? &green : &red);
	gtk_color_chooser_set_rgba ((GtkColorChooser*) c7, (state7 == 1) ? &green : &red);

	return TRUE;
}


typedef GtkApplication PlugMan;
typedef GtkApplicationClass PlugManClass;

G_DEFINE_TYPE (PlugMan, plug_man, GTK_TYPE_APPLICATION)

/**
 * plug_man_activate
 */
static void
plug_man_activate (GApplication *app)
{
	GtkWidget *window = NULL;
	GtkBuilder *builder;
	GError *error = NULL;
	GtkWidget *vbox = NULL;

	window = gtk_application_window_new (GTK_APPLICATION (app));
	gtk_window_set_default_size ((GtkWindow*)window, 320, 120);
	gtk_window_set_title (GTK_WINDOW (window), "select");

	builder = gtk_builder_new ();
	gtk_builder_add_from_file (builder, "select.ui", &error);

	vbox = (GtkWidget *)gtk_builder_get_object (builder, "vbox2");
	gtk_widget_reparent (vbox, window);

	b1 = (GtkWidget *)gtk_builder_get_object (builder, "button1");
	b2 = (GtkWidget *)gtk_builder_get_object (builder, "button2");
	b3 = (GtkWidget *)gtk_builder_get_object (builder, "button3");
	b4 = (GtkWidget *)gtk_builder_get_object (builder, "button4");
	b5 = (GtkWidget *)gtk_builder_get_object (builder, "button5");
	b6 = (GtkWidget *)gtk_builder_get_object (builder, "button6");
	b7 = (GtkWidget *)gtk_builder_get_object (builder, "button7");

	x1 = (GtkWidget *)gtk_builder_get_object (builder, "checkbutton1");
	x2 = (GtkWidget *)gtk_builder_get_object (builder, "checkbutton2");
	x3 = (GtkWidget *)gtk_builder_get_object (builder, "checkbutton3");
	x4 = (GtkWidget *)gtk_builder_get_object (builder, "checkbutton4");
	x5 = (GtkWidget *)gtk_builder_get_object (builder, "checkbutton5");
	x6 = (GtkWidget *)gtk_builder_get_object (builder, "checkbutton6");
	x7 = (GtkWidget *)gtk_builder_get_object (builder, "checkbutton7");

	c1 = (GtkWidget *)gtk_builder_get_object (builder, "colorbutton1");
	c2 = (GtkWidget *)gtk_builder_get_object (builder, "colorbutton2");
	c3 = (GtkWidget *)gtk_builder_get_object (builder, "colorbutton3");
	c4 = (GtkWidget *)gtk_builder_get_object (builder, "colorbutton4");
	c5 = (GtkWidget *)gtk_builder_get_object (builder, "colorbutton5");
	c6 = (GtkWidget *)gtk_builder_get_object (builder, "colorbutton6");
	c7 = (GtkWidget *)gtk_builder_get_object (builder, "colorbutton7");

	gtk_toggle_button_set_inconsistent ((GtkToggleButton*) x1, FALSE);
	gtk_toggle_button_set_inconsistent ((GtkToggleButton*) x2, FALSE);
	gtk_toggle_button_set_inconsistent ((GtkToggleButton*) x3, FALSE);
	gtk_toggle_button_set_inconsistent ((GtkToggleButton*) x4, FALSE);
	gtk_toggle_button_set_inconsistent ((GtkToggleButton*) x5, FALSE);
	gtk_toggle_button_set_inconsistent ((GtkToggleButton*) x6, FALSE);
	gtk_toggle_button_set_inconsistent ((GtkToggleButton*) x7, FALSE);

	g_signal_connect (b1, "button-press-event", G_CALLBACK (button_press), NULL);
	g_signal_connect (b2, "button-press-event", G_CALLBACK (button_press), NULL);
	g_signal_connect (b3, "button-press-event", G_CALLBACK (button_press), NULL);
	g_signal_connect (b4, "button-press-event", G_CALLBACK (button_press), NULL);
	g_signal_connect (b5, "button-press-event", G_CALLBACK (button_press), NULL);
	g_signal_connect (b6, "button-press-event", G_CALLBACK (button_press), NULL);
	g_signal_connect (b7, "button-press-event", G_CALLBACK (button_press), NULL);

	g_object_unref (builder);
	gtk_widget_show_all (GTK_WIDGET (window));
}

/**
 * plug_man_finalize
 */
static void
plug_man_finalize (GObject *object)
{
	G_OBJECT_CLASS (plug_man_parent_class)->finalize (object);
}

/**
 * plug_man_startup
 */
static void
plug_man_startup (GApplication *application)
{
	G_APPLICATION_CLASS (plug_man_parent_class)->startup (application);
}

/**
 * plug_man_init
 */
static void
plug_man_init (PlugMan *app)
{
}

/**
 * plug_man_class_init
 */
static void
plug_man_class_init (PlugManClass *c)
{
	GApplicationClass *application_class = G_APPLICATION_CLASS (c);
	GObjectClass *object_class = G_OBJECT_CLASS (c);

	application_class->startup = plug_man_startup;
	application_class->activate = plug_man_activate;

	object_class->finalize = plug_man_finalize;

}


/**
 * main
 */
int
main (int argc, char **argv)
{
	gpointer plug_man;

	plug_man = g_object_new (plug_man_get_type (), "application-id", "org.flatcap.test.plugman", "flags", G_APPLICATION_HANDLES_OPEN, NULL);
	g_application_run (G_APPLICATION (plug_man), argc, argv);
	g_object_unref (plug_man);

	return 0;
}



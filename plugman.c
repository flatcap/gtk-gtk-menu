#include <stdlib.h>
#include <gtk/gtk.h>

int state_button1 = -1;
int state_button2 = -1;
int state_button3 = -1;
int state_button4 = -1;
int state_button5 = -1;
int state_button6 = -1;
int state_button7 = -1;

GtkWidget *b1, *b2, *b3, *b4, *b5, *b6, *b7;
GtkWidget *x1, *x2, *x3, *x4, *x5, *x6, *x7;
GtkWidget *c1, *c2, *c3, *c4, *c5, *c6, *c7;

GdkRGBA red   = { 1.0, 0.0, 0.0, 1.0 };
GdkRGBA green = { 0.0, 1.0, 0.0, 1.0 };

static void set_colours()
{
	GdkRGBA *col1 = &red;
	GdkRGBA *col2 = &red;
	GdkRGBA *col3 = &red;
	GdkRGBA *col4 = &red;
	GdkRGBA *col5 = &red;
	GdkRGBA *col6 = &red;
	GdkRGBA *col7 = &red;

	if (state_button1 == 1)
		col1 = &green;

	gtk_color_chooser_set_rgba ((GtkColorChooser*) c1, col1);
	gtk_color_chooser_set_rgba ((GtkColorChooser*) c2, col2);
	gtk_color_chooser_set_rgba ((GtkColorChooser*) c3, col3);
	gtk_color_chooser_set_rgba ((GtkColorChooser*) c4, col4);
	gtk_color_chooser_set_rgba ((GtkColorChooser*) c5, col5);
	gtk_color_chooser_set_rgba ((GtkColorChooser*) c6, col6);
	gtk_color_chooser_set_rgba ((GtkColorChooser*) c7, col7);
}

/**
 * set_tristate
 */
static void set_tristate (GtkWidget *check, int value)
{
	GtkToggleButton *t = (GtkToggleButton*) check;

	switch (value) {
		case -1:
			gtk_toggle_button_set_inconsistent (t, TRUE);
			break;
		case 0:
			gtk_toggle_button_set_inconsistent (t, FALSE);
			gtk_toggle_button_set_active       (t, FALSE);
			break;
		case 1:
			gtk_toggle_button_set_inconsistent (t, FALSE);
			gtk_toggle_button_set_active       (t, TRUE);
			break;
	}
	set_colours();
}

/**
 * button_press
 */
static void
button_press (GtkWidget *button, void *param)
{
	if (button == b1) {			// DEFAULT
		if (state_button1 == 1)
			state_button1 = 0;
		else
			state_button1 = 1;
		set_tristate (x1, state_button1);
	}
	if (button == b2) printf ("b2\n");
	if (button == b3) printf ("b3\n");
	if (button == b4) printf ("b4\n");
	if (button == b5) printf ("b5\n");
	if (button == b6) printf ("b6\n");
	if (button == b7) printf ("b7\n");
}


/**
 * new_window
 */
static void
new_window (GApplication *app, GFile *file)
{
	GtkWidget *window, *grid, *scrolled, *view;

	window = gtk_application_window_new (GTK_APPLICATION (app));
	gtk_window_set_default_size ((GtkWindow*)window, 640, 480);
	gtk_window_set_title (GTK_WINDOW (window), "Plugman");

	grid = gtk_grid_new ();
	gtk_container_add (GTK_CONTAINER (window), grid);

	scrolled = gtk_scrolled_window_new (NULL, NULL);
	gtk_widget_set_hexpand (scrolled, TRUE);
	gtk_widget_set_vexpand (scrolled, TRUE);
	view = gtk_text_view_new ();

	g_object_set_data ((GObject*)window, "plugman-text", view);

	gtk_container_add (GTK_CONTAINER (scrolled), view);

	gtk_grid_attach (GTK_GRID (grid), scrolled, 0, 0, 1, 1);

	if (file != NULL) {
		gchar *contents;
		gsize length;

		if (g_file_load_contents (file, NULL, &contents, &length, NULL, NULL)) {
			GtkTextBuffer *buffer;

			buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));
			gtk_text_buffer_set_text (buffer, contents, length);
			g_free (contents);
		}
	}

	gtk_widget_show_all (GTK_WIDGET (window));
}

/**
 * plug_man_activate
 */
static void
plug_man_activate (GApplication *application)
{
	new_window (application, NULL);
}

/**
 * plug_man_open
 */
static void
plug_man_open (GApplication *application, GFile **files, gint n_files, const gchar *hint)
{
	gint i;

	g_print ("plug_man_open %d\n", n_files);
	for (i = 0; i < n_files; i++)
		new_window (application, files[i]);
}


typedef GtkApplication PlugMan;
typedef GtkApplicationClass PlugManClass;

G_DEFINE_TYPE (PlugMan, plug_man, GTK_TYPE_APPLICATION)

/**
 * plug_man_finalize
 */
static void
plug_man_finalize (GObject *object)
{
	G_OBJECT_CLASS (plug_man_parent_class)->finalize (object);
}


/**
 * configure_plugins
 */
static void
configure_plugins (GSimpleAction *action, GVariant *parameter, gpointer user_data)
{
	GtkBuilder *builder;
	GtkWidget *dialog;
	//GtkWidget *check;
	GError *error = NULL;

	builder = gtk_builder_new ();
	gtk_builder_add_from_file (builder, "select.ui", &error);

	if (error) {
		g_warning ("%s", error->message);
		g_error_free (error);
		return;
	}

	dialog = (GtkWidget *)gtk_builder_get_object (builder, "window1");

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

	gtk_toggle_button_set_inconsistent ((GtkToggleButton*) x1, TRUE);
	gtk_toggle_button_set_inconsistent ((GtkToggleButton*) x2, TRUE);
	gtk_toggle_button_set_inconsistent ((GtkToggleButton*) x3, TRUE);
	gtk_toggle_button_set_inconsistent ((GtkToggleButton*) x4, TRUE);
	gtk_toggle_button_set_inconsistent ((GtkToggleButton*) x5, TRUE);
	gtk_toggle_button_set_inconsistent ((GtkToggleButton*) x6, TRUE);
	gtk_toggle_button_set_inconsistent ((GtkToggleButton*) x7, TRUE);

	g_signal_connect (b1, "clicked", G_CALLBACK (button_press), NULL);
	g_signal_connect (b2, "clicked", G_CALLBACK (button_press), NULL);
	g_signal_connect (b3, "clicked", G_CALLBACK (button_press), NULL);
	g_signal_connect (b4, "clicked", G_CALLBACK (button_press), NULL);
	g_signal_connect (b5, "clicked", G_CALLBACK (button_press), NULL);
	g_signal_connect (b6, "clicked", G_CALLBACK (button_press), NULL);
	g_signal_connect (b7, "clicked", G_CALLBACK (button_press), NULL);

	/*
	dialog = (GtkWidget *)gtk_builder_get_object (builder, "plugin-dialog");
	check = (GtkWidget *)gtk_builder_get_object (builder, "red-plugin");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (check), plugin_enabled ("red"));
	g_signal_connect (check, "toggled", G_CALLBACK (enable_or_disable_plugin), "red");
	check = (GtkWidget *)gtk_builder_get_object (builder, "black-plugin");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (check), plugin_enabled ("black"));
	g_signal_connect (check, "toggled", G_CALLBACK (enable_or_disable_plugin), "black");

	g_signal_connect (dialog, "response", G_CALLBACK (gtk_widget_destroy), NULL);
	*/

	gtk_window_present (GTK_WINDOW (dialog));
}

/**
 * GActionEntry app_entries[]
 */
static GActionEntry app_entries[] = {
	{ "plugins", configure_plugins, NULL, NULL, NULL },
};

/**
 * plug_man_startup
 */
static void
plug_man_startup (GApplication *application)
{
	GtkBuilder *builder;

	G_APPLICATION_CLASS (plug_man_parent_class)
		->startup (application);

	g_action_map_add_action_entries (G_ACTION_MAP (application), app_entries, G_N_ELEMENTS (app_entries), application);

	builder = gtk_builder_new ();
	gtk_builder_add_from_string (builder,
		"<interface>"
		"	<menu id='menubar'>"
		"		<submenu>"
		"			<attribute name='label' translatable='yes'>_Edit</attribute>"
		"			<item>"
		"				<attribute name='label' translatable='yes'>Plugins</attribute>"
		"				<attribute name='action'>app.plugins</attribute>"
		"			</item>"
		"		</submenu>"
		"	</menu>"
		"</interface>", -1, NULL);
	gtk_application_set_app_menu (GTK_APPLICATION (application), G_MENU_MODEL (gtk_builder_get_object (builder, "app-menu")));
	gtk_application_set_menubar (GTK_APPLICATION (application), G_MENU_MODEL (gtk_builder_get_object (builder, "menubar")));
	g_object_set_data_full (G_OBJECT (application), "plugin-menu", gtk_builder_get_object (builder, "plugins"), g_object_unref);
	g_object_unref (builder);
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
plug_man_class_init (PlugManClass *class)
{
	GApplicationClass *application_class = G_APPLICATION_CLASS (class);
	GObjectClass *object_class = G_OBJECT_CLASS (class);

	application_class->startup = plug_man_startup;
	application_class->activate = plug_man_activate;
	application_class->open = plug_man_open;

	object_class->finalize = plug_man_finalize;

}

/**
 * plug_man_new
 */
PlugMan *
plug_man_new (void)
{
	return g_object_new (plug_man_get_type (), "application-id", "org.flatcap.test.plugman", "flags", G_APPLICATION_HANDLES_OPEN, NULL);
}

/**
 * main
 */
int
main (int argc, char **argv)
{
	PlugMan *plug_man;
	int status;

	plug_man = plug_man_new ();
	status = g_application_run (G_APPLICATION (plug_man), argc, argv);
	g_object_unref (plug_man);

	return status;
}



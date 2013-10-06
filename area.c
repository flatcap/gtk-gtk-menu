#include <stdio.h>
#include <gtk/gtk.h>

typedef GtkApplication Area;
typedef GtkApplicationClass AreaClass;

G_DEFINE_TYPE (Area, area, GTK_TYPE_APPLICATION)

static GtkWidget *window = NULL;

/**
 * app_menu_preferences_cb
 */
static void
app_menu_preferences_cb (GSimpleAction *action, GVariant *parameter, gpointer user_data)
{
	printf ("%s\n", __func__);
}

/**
 * app_menu_help_cb (GSimpleAction *action, GVariant *parameter, gpointer user_data)
 */
static void
app_menu_help_cb (GSimpleAction *action, GVariant *parameter, gpointer user_data)
{
	printf ("%s\n", __func__);
}

/**
 * app_menu_about_cb (GSimpleAction *action, GVariant *parameter, gpointer user_data)
 */
static void
app_menu_about_cb (GSimpleAction *action, GVariant *parameter, gpointer user_data)
{
	printf ("%s\n", __func__);
}

/**
 * app_menu_quit_cb (GSimpleAction *action, GVariant *parameter, gpointer user_data)
 */
static void
app_menu_quit_cb (GSimpleAction *action, GVariant *parameter, gpointer user_data)
{
	printf ("%s\n", __func__);
	GtkApplication *application = user_data;
	GtkWindow *window;

	window = gtk_application_get_active_window (application);
	gtk_widget_destroy (GTK_WIDGET (window));
}


/**
 * app_has_app_menu
 */
static int
app_has_app_menu (void)
{
	GtkSettings *gtk_settings;
	gboolean show_app_menu;
	gboolean show_menubar;

	/* We have three cases:
	 * - GNOME 3: show-app-menu true, show-menubar false -> use the app menu
	 * - Unity, OSX: show-app-menu and show-menubar true -> use the normal menu
	 * - Other WM, Windows: show-app-menu and show-menubar false -> use the normal menu
	 */
	gtk_settings = gtk_settings_get_default();
	g_object_get (G_OBJECT (gtk_settings),
	              "gtk-shell-shows-app-menu", &show_app_menu,
	              "gtk-shell-shows-menubar", &show_menubar,
	              NULL);
	/* also: gtk-application-prefer-dark-theme */

	return show_app_menu && !show_menubar;
}

/**
 * area_activate
 */
static void
area_activate (GApplication *app)
{
	printf ("Entering: %s\n", __func__);
	if (!window) {
		//GtkBuilder *builder;
		//GError *error = NULL;
		//GtkWidget *vbox = NULL;

		window = gtk_application_window_new (GTK_APPLICATION (app));
		gtk_window_set_default_size (GTK_WINDOW (window), 320, 120);
		gtk_window_set_title (GTK_WINDOW (window), "area");

#if 0
		builder = gtk_builder_new();
		gtk_builder_add_from_file (builder, "area.ui", &error);

		vbox = (GtkWidget *)gtk_builder_get_object (builder, "vbox2");
		gtk_widget_reparent (vbox, window);

		g_object_unref (builder);
#endif
	}

	gtk_icon_theme_append_search_path (gtk_icon_theme_get_default(), "/home/flatcap/work/gtk-menu");

	const GActionEntry app_menu_actions[] = {
		{ "preferences", app_menu_preferences_cb,   NULL, NULL, NULL },
		{ "help",        app_menu_help_cb,          NULL, NULL, NULL },
		{ "about",       app_menu_about_cb,         NULL, NULL, NULL },
		{ "quit",        app_menu_quit_cb,          NULL, NULL, NULL }
	};

	if (app_has_app_menu()) {
		GtkBuilder *builder = gtk_builder_new();
		GError *error = NULL;

		g_action_map_add_action_entries (G_ACTION_MAP (app), app_menu_actions, G_N_ELEMENTS (app_menu_actions), app);

		if (!gtk_builder_add_from_file (builder, "appmenu.ui", &error)) {
			g_warning ("loading menu builder file: %s", error->message);
			g_error_free (error);
		} else {
			gtk_application_set_app_menu (GTK_APPLICATION (app), G_MENU_MODEL (gtk_builder_get_object (builder, "appmenu")));
			g_object_unref (builder);
		}
	}

	gtk_widget_show_all (window);
	gtk_window_present (GTK_WINDOW (window));
}

/**
 * area_finalize
 */
static void
area_finalize (GObject *object)
{
	printf ("Entering: %s\n", __func__);
	G_OBJECT_CLASS (area_parent_class)->finalize (object);
}

/**
 * area_startup
 */
static void
area_startup (GApplication *app)
{
	printf ("Entering: %s\n", __func__);
	G_APPLICATION_CLASS (area_parent_class)->startup (app);

}

/**
 * area_init
 */
static void
area_init (Area *app)
{
	printf ("Entering: %s\n", __func__);
}

/**
 * area_class_init
 */
static void
area_class_init (AreaClass *c)
{
	printf ("Entering: %s\n", __func__);
	GApplicationClass *application_class = G_APPLICATION_CLASS (c);
	GObjectClass *object_class = G_OBJECT_CLASS (c);

	application_class->startup = area_startup;
	application_class->activate = area_activate;

	object_class->finalize = area_finalize;
}


/**
 * main
 */
int
main (int argc, char **argv)
{
	printf ("Entering: %s\n", __func__);
	gpointer area;

	area = g_object_new (area_get_type(),
			"application-id", "org.flatcap.test.area",
			"flags", G_APPLICATION_FLAGS_NONE,
			NULL);
	g_application_run (G_APPLICATION (area), argc, argv);
	g_object_unref (area);

	return 0;
}



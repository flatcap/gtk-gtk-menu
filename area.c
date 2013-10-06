#include <stdio.h>
#include <gtk/gtk.h>

typedef GtkApplication Area;
typedef GtkApplicationClass AreaClass;

G_DEFINE_TYPE (Area, area, GTK_TYPE_APPLICATION)

static GtkWidget *window = NULL;

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
		builder = gtk_builder_new ();
		gtk_builder_add_from_file (builder, "area.ui", &error);

		vbox = (GtkWidget *)gtk_builder_get_object (builder, "vbox2");
		gtk_widget_reparent (vbox, window);

		g_object_unref (builder);
#endif
	}

	if (window) {
		gtk_widget_show_all (window);
		gtk_window_present (GTK_WINDOW (window));
	}
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
area_startup (GApplication *application)
{
	printf ("Entering: %s\n", __func__);
	G_APPLICATION_CLASS (area_parent_class)->startup (application);
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



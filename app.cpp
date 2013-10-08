/* Copyright (c) 2013 Richard Russon (FlatCap)
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Library General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place - Suite 330, Boston, MA 02111-1307, USA.
 */


#include <gtkmm/object.h>
#include <gtkmm/main.h>
#include <gtkmm/icontheme.h>
#include <gtkmm/settings.h>
#include <gtkmm/aboutdialog.h>
#include <gtkmm/stock.h>
#include <gtkmm/builder.h>
#include <giomm/menu.h>

#include "app.h"

/**
 * App
 */
App::App (int &argc, char **&argv, const Glib::ustring& application_id, Gio::ApplicationFlags flags) :
	Gtk::Application (argc, argv, application_id, flags)
{
	//printf ("App::App\n");
}

/**
 * ~App
 */
App::~App()
{
	//printf ("App::~App\n");
}


/**
 * on_startup
 */
void
App::on_startup (void)
{
	Gtk::Application::on_startup();

	Glib::RefPtr<Gtk::IconTheme> theme = Gtk::IconTheme::get_default();

	theme->append_search_path ("/home/flatcap/work/gtk-app/icons");

	if (have_appmenu()) {

		Glib::RefPtr<Gio::SimpleAction> action;

		add_action("preferences", sigc::mem_fun(*this, &App::menu_preferences));
		add_action("help",        sigc::mem_fun(*this, &App::menu_help));
		add_action("about",       sigc::mem_fun(*this, &App::menu_about));
		add_action("quit",        sigc::mem_fun(*this, &App::menu_quit));

		Glib::RefPtr<Gio::Menu> menu = Gio::Menu::create();

		menu->append ("_Preferences", "app.preferences");
		menu->append ("_Help",        "app.help");
		menu->append ("_About",       "app.about");
		menu->append ("_Quit",        "app.quit");

		set_app_menu (menu);
	}
}

/**
 * have_appmenu
 */
int
App::have_appmenu (void)
{
	/* We have three cases:
	 * - GNOME 3: show-app-menu true, show-menubar false -> use the app menu
	 * - Unity, OSX: show-app-menu and show-menubar true -> use the normal menu
	 * - Other WM, Windows: show-app-menu and show-menubar false -> use the normal menu
	 */
	Glib::RefPtr<Gtk::Settings> s = Gtk::Settings::get_default();

	bool show_app_menu = s->property_gtk_shell_shows_app_menu();
	bool show_menubar  = s->property_gtk_shell_shows_menubar();
	/* also: gtk-application-prefer-dark-theme */

	return show_app_menu && !show_menubar;
}


/**
 * menu_preferences
 */
void
App::menu_preferences (void)
{
	printf ("%s\n", __func__);
}

/**
 * menu_help
 */
void
App::menu_help (void)
{
	printf ("%s\n", __func__);
}

/**
 * menu_about
 */
void
App::menu_about (void)
{
	Gtk::AboutDialog about;

	about.set_name("DParted");
	about.set_program_name("DParted");
	//about.set_version(VERSION);
	//about.set_logo(IconManager::obj().get_icon(IconManager::GNOTE, 48));
	about.set_copyright("Copyright \xc2\xa9 2013 Richard Russon (FlatCap)\n");
	about.set_comments("Reorganise your disk.");
	about.set_website("http://flatcap.org/rich");
	about.set_website_label("Homepage");
	//about.set_authors(authors);
	//about.set_documenters(documenters);
	//about.set_translator_credits(translators);
	about.set_icon_name("dparted");
	//about.set_transient_for(recent_changes);

	about.run();
}

/**
 * menu_quit
 */
void
App::menu_quit (void)
{
	quit();
}


/**
 * main
 */
int
main (int argc, char *argv[])
{
	App app (argc, argv, "org.flatcap.test.area", Gio::APPLICATION_FLAGS_NONE);

	Area area;

	return app.run (area);
}



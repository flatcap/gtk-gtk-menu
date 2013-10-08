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
#include <glibmm.h>

#include "app.h"
#include "area.h"

/**
 * App
 */
App::App() :
	Gtk::Application("org.flatcap.test.area", Gio::APPLICATION_FLAGS_NONE)
{
	//printf ("App::App\n");
	Glib::set_application_name("dparted");
}

/**
 * ~App
 */
App::~App()
{
	//printf ("App::~App\n");
}

/**
 * create
 */
Glib::RefPtr<App>
App::create (void)
{
	return Glib::RefPtr<App> (new App());
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

/**
 * on_activate
 */
void
App::on_activate()
{
	//std::cout << "debug1: " << G_STRFUNC << std::endl;
	// The application has been started, so let's show a window.
	// A real application might want to reuse this "empty" window in on_open(),
	// when asked to open a file, if no changes have been made yet.

	Area *area = new Area();

	add_window(*area);

	//Delete the window when it is hidden.
	//That's enough for this simple example.
	//window->signal_hide().connect(sigc::bind<Gtk::Window*>(sigc::mem_fun(*this, &App::on_window_hide), window));

	area->show();
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
	const std::vector<Glib::ustring> authors     = {"Jim","Bob","Dave","Mike","Phil"};
	const std::vector<Glib::ustring> documenters = {"Mary","Jane","Gladys"};
	const std::vector<Glib::ustring> artists     = {"Van Gogh","Monet","Turner"};

	Gtk::AboutDialog about;

	about.set_name("DParted");
	about.set_program_name("dparted");
	about.set_version("0.1");
	about.set_logo_icon_name("dparted");
	about.set_copyright("Copyright \xc2\xa9 2013 Richard Russon (FlatCap)\n");
	about.set_comments("Reorganise your disk.");
	about.set_website("http://flatcap.org/rich");
	about.set_website_label("Rich's homepage");
	about.set_authors(authors);
	about.set_documenters(documenters);
	about.set_translator_credits("Bjorn ,Volker, Pierre");
	about.set_artists(artists);
	about.set_license_type(Gtk::LICENSE_GPL_3_0);

	//about.set_transient_for(recent_changes);

	about.set_icon_name("dparted");

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
	Glib::RefPtr<App> app = App::create();

	return app->run(argc, argv);
}



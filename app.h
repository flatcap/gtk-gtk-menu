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


#ifndef _APP_H_
#define _APP_H_

#include <string>

#include <gtkmm/application.h>

#include "area.h"

class App : public Gtk::Application
{
public:
	App (int &argc,
		char **&argv,
		const Glib::ustring& application_id = Glib::ustring(),
		Gio::ApplicationFlags flags = Gio::APPLICATION_FLAGS_NONE);
	virtual ~App();

protected:
	int have_appmenu (void);
	void menu_preferences (void);
	void menu_help        (void);
	void menu_about       (void);
	void menu_quit        (void);

	void on_startup (void);
};

#endif // _APP_H_


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


#ifndef _AREA_H_
#define _AREA_H_

#include "gtkmm/applicationwindow.h"
#include "gtkmm/scrolledwindow.h"
#include "gtkmm/drawingarea.h"

class Area : public Gtk::ApplicationWindow
{
public:
	Area();
	virtual ~Area();

	void menu_dummy (void);

protected:
	Gtk::ScrolledWindow	m_scroll;
	Gtk::DrawingArea	m_draw;

	bool on_my_draw (const Cairo::RefPtr<Cairo::Context> &cr);
	bool on_my_configure_event (GdkEventConfigure *event);

	virtual void on_hide (void);
	virtual void on_map (void);
	virtual void on_realize (void);
	virtual void on_show (void);
	virtual void on_unmap (void);
	virtual void on_unrealize (void);
};

#endif // _AREA_H_


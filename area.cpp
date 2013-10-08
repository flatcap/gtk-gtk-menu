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


#include <gtkmm/builder.h>

#include "area.h"

/**
 * Area
 */
Area::Area() :
	m_scroll(),
	m_draw()
{
	set_title("area test");

	set_default_size (1024, 640);

	this   ->add (m_scroll);
	m_scroll.add (m_draw);

	m_scroll.set_hexpand (true);
	m_scroll.set_vexpand (true);

	m_draw.set_size_request (400, 1024);
	m_draw.signal_draw().connect            (sigc::mem_fun (*this, &Area::on_my_draw));
	m_draw.signal_configure_event().connect (sigc::mem_fun (*this, &Area::on_my_configure_event));

	set_default_icon_name ("dparted");

	show_all_children();
}

/**
 * ~Area
 */
Area::~Area()
{
}


/**
 * on_my_draw
 */
bool
Area::on_my_draw (const Cairo::RefPtr<Cairo::Context> &cr)
{
	int width  = m_draw.get_allocated_width();
	int height = m_draw.get_allocated_height();

	cr->set_source_rgb (0.5, 0, 0.5);

	cr->rectangle (0, 0, 50, 50);
	cr->fill();

	cr->rectangle (width-50, 0, 50, 50);
	cr->fill();

	cr->rectangle (width-50, height-50, 50, 50);
	cr->fill();

	cr->rectangle (0, height-50, 50, 50);
	cr->fill();

	return true;
}

/**
 * on_my_configure_event
 */
bool
Area::on_my_configure_event (GdkEventConfigure *event)
{
	Gtk::Allocation allocation;

	allocation = get_allocation();

	set_size_request (-1, 400);

	//printf ("width = %d, height = %d\n", allocation.get_width(), allocation.get_height());

	return true;
}



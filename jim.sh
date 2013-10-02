#!/bin/bash

rm -f plugman

gcc								\
	$(pkg-config --cflags --libs gtk+-3.0)			\
	-DGDK_DISABLE_DEPRECATED				\
	-DGTK_DISABLE_DEPRECATED				\
	-DG_ENABLE_DEBUG					\
	-DHAVE_CONFIG_H						\
	-g							\
	-Wall							\
	-pthread						\
	-o plugman						\
	plugman.c

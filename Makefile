CC	= gcc
RM	= rm -fr
MKDIR	= mkdir -p

SRC	= select.c
HDR	=

DEPDIR	= .dep
OBJDIR	= .obj

OBJ	= $(SRC:%.c=$(OBJDIR)/%.o)

OUT	= select

CFLAGS	= -g -Wall
CFLAGS	+= -DGDK_DISABLE_DEPRECATED
CFLAGS	+= -DGTK_DISABLE_DEPRECATED
CFLAGS	+= -DG_ENABLE_DEBUG
CFLAGS	+= -DHAVE_CONFIG_H

CFLAGS	+= -pg -fprofile-arcs -ftest-coverage -fno-omit-frame-pointer
CFLAGS	+= -fno-inline-functions -fno-inline-functions-called-once -fno-optimize-sibling-calls

LDFLAGS	+= -pg -fprofile-arcs

PACKAGES = gtk+-3.0

CFLAGS	+= $(shell pkg-config --cflags $(PACKAGES))
LDFLAGS += $(shell pkg-config --libs   $(PACKAGES))

V	?= 0

ifeq ($(V),1)
	quiet=
else
	quiet=quiet_
endif

ifneq ($(filter s% -s%,$(MAKEFLAGS)),)
	quiet=silent_
endif

all:	$(OBJDIR) $(DEPDIR) $(OBJ) $(OUT) tags

# ----------------------------------------------------------------------------

# If quiet is set, only print short version of command
cmd	= @$(if $($(quiet)cmd_$(1)),\
		echo '$($(quiet)cmd_$(1))' &&) $(cmd_$(1))

# ----------------------------------------------------------------------------

quiet_cmd_TAGS	= CTAGS	$@
      cmd_TAGS	= ctags $(SRC)

tags:	$(SRC) $(HDR)
	$(call cmd,TAGS)

# ----------------------------------------------------------------------------

quiet_cmd_CC	= CC	$<
      cmd_CC	= $(CC) $(CFLAGS) -c $< -o $@ && (												\
		  $(CC) -MM $(CFLAGS) -c $< | sed 's/.*:/'$(OBJDIR)'\/\0/' > $(DEPDIR)/$*.d;							\
		  cp -f $(DEPDIR)/$*.d $(DEPDIR)/$*.d.tmp;											\
		  sed -e 's/.*://' -e 's/\\$$//' < $(DEPDIR)/$*.d.tmp | fmt -1 | sed -e 's/^ *//' -e 's/$$/:/' >> $(DEPDIR)/$*.d;		\
		  rm -f $(DEPDIR)/$*.d.tmp)

$(OBJDIR)/%.o: %.c
	$(call cmd,CC)

# ----------------------------------------------------------------------------

quiet_cmd_LD	= LD	$@
      cmd_LD	= $(CC) -o $@ $(OBJ) $(LDFLAGS)

$(OUT):	$(OBJ)
	$(call cmd,LD)

# ----------------------------------------------------------------------------

quiet_cmd_MKDIR	= MKDIR	$@
      cmd_MKDIR	= $(MKDIR) $@

$(DEPDIR) $(OBJDIR):
	$(call cmd,MKDIR)

# ----------------------------------------------------------------------------

quiet_cmd_CLEAN	= RM	$(OUT) $(OBJ) *.gcda *.gcno gmon.out
      cmd_CLEAN	= $(RM) $(OUT) $(OBJ) *.gcda *.gcno gmon.out

quiet_cmd_DCLEAN = RM	$(DEPDIR) $(OBJDIR) tags
      cmd_DCLEAN = $(RM) $(DEPDIR) $(OBJDIR) tags

clean:	force
	$(call cmd,CLEAN)

distclean: clean
	$(call cmd,DCLEAN)

force:

-include $(SRC:%.c=$(DEPDIR)/%.d)

wc:	force
	@wc -l $(SRC) $(HDR)


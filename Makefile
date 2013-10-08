CC	= g++
RM	= rm -fr
MKDIR	= mkdir -p

SRC	= app.cpp area.cpp
HDR	= app.h area.h

DEPDIR	= .dep
OBJDIR	= .obj

OBJ	= $(SRC:%.cpp=$(OBJDIR)/%.o)

OUT	= area

CFLAGS	+= -std=c++11
CFLAGS	+= -g -Wall
CFLAGS	+= -DGDK_DISABLE_DEPRECATED
CFLAGS	+= -DGTK_DISABLE_DEPRECATED
CFLAGS	+= -DG_ENABLE_DEBUG
CFLAGS	+= -DHAVE_CONFIG_H

CFLAGS	+= -fno-inline-functions
CFLAGS	+= -fno-inline-functions-called-once
CFLAGS	+= -fno-omit-frame-pointer
CFLAGS	+= -fno-optimize-sibling-calls

LDFLAGS	+= 

PACKAGES = gtkmm-3.0

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
      cmd_TAGS	= ctags $(SRC) $(HDR)

tags:	$(SRC) $(HDR)
	$(call cmd,TAGS)

# ----------------------------------------------------------------------------

quiet_cmd_CC	= CC	$<
      cmd_CC	= $(CC) $(CFLAGS) -c $< -o $@ && (												\
		  $(CC) -MM $(CFLAGS) -c $< | sed 's/.*:/'$(OBJDIR)'\/\0/' > $(DEPDIR)/$*.d;							\
		  cp -f $(DEPDIR)/$*.d $(DEPDIR)/$*.d.tmp;											\
		  sed -e 's/.*://' -e 's/\\$$//' < $(DEPDIR)/$*.d.tmp | fmt -1 | sed -e 's/^ *//' -e 's/$$/:/' >> $(DEPDIR)/$*.d;		\
		  rm -f $(DEPDIR)/$*.d.tmp)

$(OBJDIR)/%.o: %.cpp
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

quiet_cmd_CLEAN	= RM	$(OUT) $(OBJ)
      cmd_CLEAN	= $(RM) $(OUT) $(OBJ)

quiet_cmd_DCLEAN = RM	$(DEPDIR) $(OBJDIR) tags
      cmd_DCLEAN = $(RM) $(DEPDIR) $(OBJDIR) tags

clean:	force
	$(call cmd,CLEAN)

distclean: clean
	$(call cmd,DCLEAN)

force:

-include $(SRC:%.cpp=$(DEPDIR)/%.d)


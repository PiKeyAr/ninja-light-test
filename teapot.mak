#------------------------------------------------------------------------------
# teapot.mak
#------------------------------------------------------------------------------

PROJECT	= teapot

PROJECT_OBJS	= \
		  $(OBJDIR)\global32.obj\
		  $(OBJDIR)\model.obj\
		  $(OBJDIR)\njloop.obj\
		  $(OBJDIR)\sbinit.obj\
		  $(OBJDIR)\t009.obj\
		  $(OBJDIR)\test.obj\

PROJECT_LIBS	= \
				ninja,\
				nindows

GFX_API		= NINJA

OPTIMIZE        = 1

DEBUG           = TRUE
LIST            = FALSE
BIN             = FALSE
#GNU           = TRUE

include $(KATANA_ROOT)\sample\katana.inc

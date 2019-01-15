CRC=windres
RESOURCE=mendax_rc.rc icon.rc menu.rc dialog_about.rc important.rc confirm.rc bg.rc bindmore.rc
RESOBJECT=$(RESOURCE:.rc=.o)
CC=gcc
CFLAGS=-mwindows -v
DEPS=resources.h
EXECLI=mendax.exe
EXEGUI=mendax_binder.exe
SRCGUI=mendax_binder.c
SRCCLI=mendax.c
IMG=mendax.ico mendax.bmp

compileGUI: $(EXECLI) $(RESOBJECT) mendax_binder.c $(DEPS)
	$(CC) -o $(EXEGUI) $(SRCGUI) $(RESOBJECT) $(CFLAGS)

compileCLI: $(SRCCLI)
	$(CC) $(SRCCLI) -o $(EXECLI) -v
	
$(EXECLI): $(SRCCLI)
	$(CC) $(SRCCLI) -o $(EXECLI) -v

$(RESOBJECT): $(RESOURCE) $(IMG)
	$(CRC) mendax_rc.rc mendax_rc.o
	$(CRC) icon.rc icon.o
	$(CRC) menu.rc menu.o
	$(CRC) dialog_about.rc dialog_about.o
	$(CRC) important.rc important.o
	$(CRC) confirm.rc confirm.o
	$(CRC) bg.rc bg.o
	$(CRC) bindmore.rc bindmore.o

	

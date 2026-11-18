
AUTOMAKE_OPTIONS = subdir-objects
include ../flagsandlibs
include ../sources

kutegui_SOURCES = $(COMMONSRC)

pixfilesdir = $(pkgdatadir)/pixmaps
pixfiles_DATA = ../resources/pixmaps/*

gpldir = $(pkgdatadir)/docs
gpl_DATA = ../resources/docs/gpl-3.0.txt

helpdir = $(pkgdatadir)/docs/help
help_DATA = ../resources/docs/help/*

bin_PROGRAMS = kutegui

install-exec-hook:
	install -D ../resources/pixmaps/KUTEGui.png $(DESTDIR)${prefix}/share/pixmaps/KUTEGui.png
	install -D ../resources/pixmaps/KUTEGui.desktop $(DESTDIR)${prefix}/share/applications/KUTEGui.desktop
	strip --strip-unneeded $(DESTDIR)$(bindir)/kutegui
	cp -r "../resources/icons" "$(DESTDIR)$(pkgdatadir)"

uninstall-hook:
	rm -f $(DESTDIR)${prefix}/share/applications/KUTEGui.desktop
	rm -f $(DESTDIR)${prefix}/share/pixmaps/KUTEGui.png
	rm -fr $(pkgdatadir)


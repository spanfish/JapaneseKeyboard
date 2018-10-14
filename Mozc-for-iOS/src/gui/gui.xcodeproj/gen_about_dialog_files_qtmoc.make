all: \
    $(SHARED_INTERMEDIATE_DIR)/gui/about_dialog/moc_about_dialog.cc

$(SHARED_INTERMEDIATE_DIR)/gui/about_dialog/moc_about_dialog.cc \
    : \
    about_dialog/about_dialog.h
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/gui/about_dialog"
	@echo note: "Generatinc moc files from about_dialog/about_dialog.h"
	"$(QTDIR)/bin/moc" -p gui/about_dialog -o "$(SHARED_INTERMEDIATE_DIR)/gui/about_dialog/moc_about_dialog.cc" "about_dialog/about_dialog.h"

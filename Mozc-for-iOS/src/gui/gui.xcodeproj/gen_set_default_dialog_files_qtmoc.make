all: \
    $(SHARED_INTERMEDIATE_DIR)/gui/set_default_dialog/moc_set_default_dialog.cc

$(SHARED_INTERMEDIATE_DIR)/gui/set_default_dialog/moc_set_default_dialog.cc \
    : \
    set_default_dialog/set_default_dialog.h
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/gui/set_default_dialog"
	@echo note: "Generatinc moc files from set_default_dialog/set_default_dialog.h"
	"$(QTDIR)/bin/moc" -p gui/set_default_dialog -o "$(SHARED_INTERMEDIATE_DIR)/gui/set_default_dialog/moc_set_default_dialog.cc" "set_default_dialog/set_default_dialog.h"

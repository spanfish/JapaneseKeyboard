all: \
    $(SHARED_INTERMEDIATE_DIR)/gui/update_dialog/moc_update_dialog.cc

$(SHARED_INTERMEDIATE_DIR)/gui/update_dialog/moc_update_dialog.cc \
    : \
    update_dialog/update_dialog.h
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/gui/update_dialog"
	@echo note: "Generatinc moc files from update_dialog/update_dialog.h"
	"$(QTDIR)/bin/moc" -p gui/update_dialog -o "$(SHARED_INTERMEDIATE_DIR)/gui/update_dialog/moc_update_dialog.cc" "update_dialog/update_dialog.h"

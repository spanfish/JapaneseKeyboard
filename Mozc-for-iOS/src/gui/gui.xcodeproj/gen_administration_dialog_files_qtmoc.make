all: \
    $(SHARED_INTERMEDIATE_DIR)/gui/administration_dialog/moc_administration_dialog.cc

$(SHARED_INTERMEDIATE_DIR)/gui/administration_dialog/moc_administration_dialog.cc \
    : \
    administration_dialog/administration_dialog.h
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/gui/administration_dialog"
	@echo note: "Generatinc moc files from administration_dialog/administration_dialog.h"
	"$(QTDIR)/bin/moc" -p gui/administration_dialog -o "$(SHARED_INTERMEDIATE_DIR)/gui/administration_dialog/moc_administration_dialog.cc" "administration_dialog/administration_dialog.h"

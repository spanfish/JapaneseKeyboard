all: \
    $(SHARED_INTERMEDIATE_DIR)/gui/administration_dialog/ui_administration_dialog.h

$(SHARED_INTERMEDIATE_DIR)/gui/administration_dialog/ui_administration_dialog.h \
    : \
    administration_dialog/administration_dialog.ui
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/gui/administration_dialog"
	@echo note: "Generating UI header files from administration_dialog/administration_dialog.ui"
	"$(QTDIR)/bin/uic" -o "$(SHARED_INTERMEDIATE_DIR)/gui/administration_dialog/ui_administration_dialog.h" "administration_dialog/administration_dialog.ui"

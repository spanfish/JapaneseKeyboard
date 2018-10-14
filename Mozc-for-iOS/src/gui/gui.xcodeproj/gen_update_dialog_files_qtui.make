all: \
    $(SHARED_INTERMEDIATE_DIR)/gui/update_dialog/ui_update_dialog.h

$(SHARED_INTERMEDIATE_DIR)/gui/update_dialog/ui_update_dialog.h \
    : \
    update_dialog/update_dialog.ui
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/gui/update_dialog"
	@echo note: "Generating UI header files from update_dialog/update_dialog.ui"
	"$(QTDIR)/bin/uic" -o "$(SHARED_INTERMEDIATE_DIR)/gui/update_dialog/ui_update_dialog.h" "update_dialog/update_dialog.ui"

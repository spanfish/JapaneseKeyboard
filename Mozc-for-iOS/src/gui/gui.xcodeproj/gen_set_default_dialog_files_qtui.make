all: \
    $(SHARED_INTERMEDIATE_DIR)/gui/set_default_dialog/ui_set_default_dialog.h

$(SHARED_INTERMEDIATE_DIR)/gui/set_default_dialog/ui_set_default_dialog.h \
    : \
    set_default_dialog/set_default_dialog.ui
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/gui/set_default_dialog"
	@echo note: "Generating UI header files from set_default_dialog/set_default_dialog.ui"
	"$(QTDIR)/bin/uic" -o "$(SHARED_INTERMEDIATE_DIR)/gui/set_default_dialog/ui_set_default_dialog.h" "set_default_dialog/set_default_dialog.ui"

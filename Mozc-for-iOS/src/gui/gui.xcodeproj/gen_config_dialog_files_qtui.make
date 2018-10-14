all: \
    $(SHARED_INTERMEDIATE_DIR)/gui/config_dialog/ui_config_dialog.h \
    $(SHARED_INTERMEDIATE_DIR)/gui/config_dialog/ui_generic_table_editor.h \
    $(SHARED_INTERMEDIATE_DIR)/gui/config_dialog/ui_keybinding_editor.h

$(SHARED_INTERMEDIATE_DIR)/gui/config_dialog/ui_config_dialog.h \
    : \
    config_dialog/config_dialog.ui
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/gui/config_dialog"
	@echo note: "Generating UI header files from config_dialog/config_dialog.ui"
	"$(QTDIR)/bin/uic" -o "$(SHARED_INTERMEDIATE_DIR)/gui/config_dialog/ui_config_dialog.h" "config_dialog/config_dialog.ui"

$(SHARED_INTERMEDIATE_DIR)/gui/config_dialog/ui_generic_table_editor.h \
    : \
    config_dialog/generic_table_editor.ui
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/gui/config_dialog"
	@echo note: "Generating UI header files from config_dialog/generic_table_editor.ui"
	"$(QTDIR)/bin/uic" -o "$(SHARED_INTERMEDIATE_DIR)/gui/config_dialog/ui_generic_table_editor.h" "config_dialog/generic_table_editor.ui"

$(SHARED_INTERMEDIATE_DIR)/gui/config_dialog/ui_keybinding_editor.h \
    : \
    config_dialog/keybinding_editor.ui
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/gui/config_dialog"
	@echo note: "Generating UI header files from config_dialog/keybinding_editor.ui"
	"$(QTDIR)/bin/uic" -o "$(SHARED_INTERMEDIATE_DIR)/gui/config_dialog/ui_keybinding_editor.h" "config_dialog/keybinding_editor.ui"

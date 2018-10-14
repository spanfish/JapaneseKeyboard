all: \
    $(SHARED_INTERMEDIATE_DIR)/gui/dictionary_tool/ui_dictionary_tool.h \
    $(SHARED_INTERMEDIATE_DIR)/gui/dictionary_tool/ui_find_dialog.h \
    $(SHARED_INTERMEDIATE_DIR)/gui/dictionary_tool/ui_import_dialog.h

$(SHARED_INTERMEDIATE_DIR)/gui/dictionary_tool/ui_dictionary_tool.h \
    : \
    dictionary_tool/dictionary_tool.ui
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/gui/dictionary_tool"
	@echo note: "Generating UI header files from dictionary_tool/dictionary_tool.ui"
	"$(QTDIR)/bin/uic" -o "$(SHARED_INTERMEDIATE_DIR)/gui/dictionary_tool/ui_dictionary_tool.h" "dictionary_tool/dictionary_tool.ui"

$(SHARED_INTERMEDIATE_DIR)/gui/dictionary_tool/ui_find_dialog.h \
    : \
    dictionary_tool/find_dialog.ui
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/gui/dictionary_tool"
	@echo note: "Generating UI header files from dictionary_tool/find_dialog.ui"
	"$(QTDIR)/bin/uic" -o "$(SHARED_INTERMEDIATE_DIR)/gui/dictionary_tool/ui_find_dialog.h" "dictionary_tool/find_dialog.ui"

$(SHARED_INTERMEDIATE_DIR)/gui/dictionary_tool/ui_import_dialog.h \
    : \
    dictionary_tool/import_dialog.ui
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/gui/dictionary_tool"
	@echo note: "Generating UI header files from dictionary_tool/import_dialog.ui"
	"$(QTDIR)/bin/uic" -o "$(SHARED_INTERMEDIATE_DIR)/gui/dictionary_tool/ui_import_dialog.h" "dictionary_tool/import_dialog.ui"

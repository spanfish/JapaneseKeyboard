all: \
    $(SHARED_INTERMEDIATE_DIR)/gui/dictionary_tool/moc_dictionary_content_table_widget.cc \
    $(SHARED_INTERMEDIATE_DIR)/gui/dictionary_tool/moc_dictionary_tool.cc \
    $(SHARED_INTERMEDIATE_DIR)/gui/dictionary_tool/moc_find_dialog.cc \
    $(SHARED_INTERMEDIATE_DIR)/gui/dictionary_tool/moc_import_dialog.cc \
    $(SHARED_INTERMEDIATE_DIR)/gui/dictionary_tool/moc_zero_width_splitter.cc

$(SHARED_INTERMEDIATE_DIR)/gui/dictionary_tool/moc_dictionary_content_table_widget.cc \
    : \
    dictionary_tool/dictionary_content_table_widget.h
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/gui/dictionary_tool"
	@echo note: "Generatinc moc files from dictionary_tool/dictionary_content_table_widget.h"
	"$(QTDIR)/bin/moc" -p gui/dictionary_tool -o "$(SHARED_INTERMEDIATE_DIR)/gui/dictionary_tool/moc_dictionary_content_table_widget.cc" "dictionary_tool/dictionary_content_table_widget.h"

$(SHARED_INTERMEDIATE_DIR)/gui/dictionary_tool/moc_dictionary_tool.cc \
    : \
    dictionary_tool/dictionary_tool.h
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/gui/dictionary_tool"
	@echo note: "Generatinc moc files from dictionary_tool/dictionary_tool.h"
	"$(QTDIR)/bin/moc" -p gui/dictionary_tool -o "$(SHARED_INTERMEDIATE_DIR)/gui/dictionary_tool/moc_dictionary_tool.cc" "dictionary_tool/dictionary_tool.h"

$(SHARED_INTERMEDIATE_DIR)/gui/dictionary_tool/moc_find_dialog.cc \
    : \
    dictionary_tool/find_dialog.h
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/gui/dictionary_tool"
	@echo note: "Generatinc moc files from dictionary_tool/find_dialog.h"
	"$(QTDIR)/bin/moc" -p gui/dictionary_tool -o "$(SHARED_INTERMEDIATE_DIR)/gui/dictionary_tool/moc_find_dialog.cc" "dictionary_tool/find_dialog.h"

$(SHARED_INTERMEDIATE_DIR)/gui/dictionary_tool/moc_import_dialog.cc \
    : \
    dictionary_tool/import_dialog.h
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/gui/dictionary_tool"
	@echo note: "Generatinc moc files from dictionary_tool/import_dialog.h"
	"$(QTDIR)/bin/moc" -p gui/dictionary_tool -o "$(SHARED_INTERMEDIATE_DIR)/gui/dictionary_tool/moc_import_dialog.cc" "dictionary_tool/import_dialog.h"

$(SHARED_INTERMEDIATE_DIR)/gui/dictionary_tool/moc_zero_width_splitter.cc \
    : \
    dictionary_tool/zero_width_splitter.h
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/gui/dictionary_tool"
	@echo note: "Generatinc moc files from dictionary_tool/zero_width_splitter.h"
	"$(QTDIR)/bin/moc" -p gui/dictionary_tool -o "$(SHARED_INTERMEDIATE_DIR)/gui/dictionary_tool/moc_zero_width_splitter.cc" "dictionary_tool/zero_width_splitter.h"

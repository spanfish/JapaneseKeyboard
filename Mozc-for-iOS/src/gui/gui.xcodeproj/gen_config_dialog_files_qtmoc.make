all: \
    $(SHARED_INTERMEDIATE_DIR)/gui/config_dialog/moc_character_form_editor.cc \
    $(SHARED_INTERMEDIATE_DIR)/gui/config_dialog/moc_combobox_delegate.cc \
    $(SHARED_INTERMEDIATE_DIR)/gui/config_dialog/moc_config_dialog.cc \
    $(SHARED_INTERMEDIATE_DIR)/gui/config_dialog/moc_generic_table_editor.cc \
    $(SHARED_INTERMEDIATE_DIR)/gui/config_dialog/moc_keybinding_editor.cc \
    $(SHARED_INTERMEDIATE_DIR)/gui/config_dialog/moc_keybinding_editor_delegate.cc \
    $(SHARED_INTERMEDIATE_DIR)/gui/config_dialog/moc_keymap_editor.cc \
    $(SHARED_INTERMEDIATE_DIR)/gui/config_dialog/moc_roman_table_editor.cc

$(SHARED_INTERMEDIATE_DIR)/gui/config_dialog/moc_character_form_editor.cc \
    : \
    config_dialog/character_form_editor.h
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/gui/config_dialog"
	@echo note: "Generatinc moc files from config_dialog/character_form_editor.h"
	"$(QTDIR)/bin/moc" -p gui/config_dialog -o "$(SHARED_INTERMEDIATE_DIR)/gui/config_dialog/moc_character_form_editor.cc" "config_dialog/character_form_editor.h"

$(SHARED_INTERMEDIATE_DIR)/gui/config_dialog/moc_combobox_delegate.cc \
    : \
    config_dialog/combobox_delegate.h
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/gui/config_dialog"
	@echo note: "Generatinc moc files from config_dialog/combobox_delegate.h"
	"$(QTDIR)/bin/moc" -p gui/config_dialog -o "$(SHARED_INTERMEDIATE_DIR)/gui/config_dialog/moc_combobox_delegate.cc" "config_dialog/combobox_delegate.h"

$(SHARED_INTERMEDIATE_DIR)/gui/config_dialog/moc_config_dialog.cc \
    : \
    config_dialog/config_dialog.h
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/gui/config_dialog"
	@echo note: "Generatinc moc files from config_dialog/config_dialog.h"
	"$(QTDIR)/bin/moc" -p gui/config_dialog -o "$(SHARED_INTERMEDIATE_DIR)/gui/config_dialog/moc_config_dialog.cc" "config_dialog/config_dialog.h"

$(SHARED_INTERMEDIATE_DIR)/gui/config_dialog/moc_generic_table_editor.cc \
    : \
    config_dialog/generic_table_editor.h
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/gui/config_dialog"
	@echo note: "Generatinc moc files from config_dialog/generic_table_editor.h"
	"$(QTDIR)/bin/moc" -p gui/config_dialog -o "$(SHARED_INTERMEDIATE_DIR)/gui/config_dialog/moc_generic_table_editor.cc" "config_dialog/generic_table_editor.h"

$(SHARED_INTERMEDIATE_DIR)/gui/config_dialog/moc_keybinding_editor.cc \
    : \
    config_dialog/keybinding_editor.h
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/gui/config_dialog"
	@echo note: "Generatinc moc files from config_dialog/keybinding_editor.h"
	"$(QTDIR)/bin/moc" -p gui/config_dialog -o "$(SHARED_INTERMEDIATE_DIR)/gui/config_dialog/moc_keybinding_editor.cc" "config_dialog/keybinding_editor.h"

$(SHARED_INTERMEDIATE_DIR)/gui/config_dialog/moc_keybinding_editor_delegate.cc \
    : \
    config_dialog/keybinding_editor_delegate.h
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/gui/config_dialog"
	@echo note: "Generatinc moc files from config_dialog/keybinding_editor_delegate.h"
	"$(QTDIR)/bin/moc" -p gui/config_dialog -o "$(SHARED_INTERMEDIATE_DIR)/gui/config_dialog/moc_keybinding_editor_delegate.cc" "config_dialog/keybinding_editor_delegate.h"

$(SHARED_INTERMEDIATE_DIR)/gui/config_dialog/moc_keymap_editor.cc \
    : \
    config_dialog/keymap_editor.h
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/gui/config_dialog"
	@echo note: "Generatinc moc files from config_dialog/keymap_editor.h"
	"$(QTDIR)/bin/moc" -p gui/config_dialog -o "$(SHARED_INTERMEDIATE_DIR)/gui/config_dialog/moc_keymap_editor.cc" "config_dialog/keymap_editor.h"

$(SHARED_INTERMEDIATE_DIR)/gui/config_dialog/moc_roman_table_editor.cc \
    : \
    config_dialog/roman_table_editor.h
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/gui/config_dialog"
	@echo note: "Generatinc moc files from config_dialog/roman_table_editor.h"
	"$(QTDIR)/bin/moc" -p gui/config_dialog -o "$(SHARED_INTERMEDIATE_DIR)/gui/config_dialog/moc_roman_table_editor.cc" "config_dialog/roman_table_editor.h"

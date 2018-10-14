all: \
    $(SHARED_INTERMEDIATE_DIR)/gui/word_register_dialog/ui_word_register_dialog.h

$(SHARED_INTERMEDIATE_DIR)/gui/word_register_dialog/ui_word_register_dialog.h \
    : \
    word_register_dialog/word_register_dialog.ui
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/gui/word_register_dialog"
	@echo note: "Generating UI header files from word_register_dialog/word_register_dialog.ui"
	"$(QTDIR)/bin/uic" -o "$(SHARED_INTERMEDIATE_DIR)/gui/word_register_dialog/ui_word_register_dialog.h" "word_register_dialog/word_register_dialog.ui"

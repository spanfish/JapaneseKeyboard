all: \
    $(SHARED_INTERMEDIATE_DIR)/gui/word_register_dialog/moc_word_register_dialog.cc

$(SHARED_INTERMEDIATE_DIR)/gui/word_register_dialog/moc_word_register_dialog.cc \
    : \
    word_register_dialog/word_register_dialog.h
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/gui/word_register_dialog"
	@echo note: "Generatinc moc files from word_register_dialog/word_register_dialog.h"
	"$(QTDIR)/bin/moc" -p gui/word_register_dialog -o "$(SHARED_INTERMEDIATE_DIR)/gui/word_register_dialog/moc_word_register_dialog.cc" "word_register_dialog/word_register_dialog.h"

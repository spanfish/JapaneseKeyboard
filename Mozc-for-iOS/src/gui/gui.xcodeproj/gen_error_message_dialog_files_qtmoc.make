all: \
    $(SHARED_INTERMEDIATE_DIR)/gui/error_message_dialog/moc_error_message_dialog.cc

$(SHARED_INTERMEDIATE_DIR)/gui/error_message_dialog/moc_error_message_dialog.cc \
    : \
    error_message_dialog/error_message_dialog.h
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/gui/error_message_dialog"
	@echo note: "Generatinc moc files from error_message_dialog/error_message_dialog.h"
	"$(QTDIR)/bin/moc" -p gui/error_message_dialog -o "$(SHARED_INTERMEDIATE_DIR)/gui/error_message_dialog/moc_error_message_dialog.cc" "error_message_dialog/error_message_dialog.h"

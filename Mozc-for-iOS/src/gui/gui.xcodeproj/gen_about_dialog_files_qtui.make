all: \
    $(SHARED_INTERMEDIATE_DIR)/gui/about_dialog/ui_about_dialog.h

$(SHARED_INTERMEDIATE_DIR)/gui/about_dialog/ui_about_dialog.h \
    : \
    about_dialog/about_dialog.ui
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/gui/about_dialog"
	@echo note: "Generating UI header files from about_dialog/about_dialog.ui"
	"$(QTDIR)/bin/uic" -o "$(SHARED_INTERMEDIATE_DIR)/gui/about_dialog/ui_about_dialog.h" "about_dialog/about_dialog.ui"

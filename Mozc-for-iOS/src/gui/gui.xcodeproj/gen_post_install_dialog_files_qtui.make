all: \
    $(SHARED_INTERMEDIATE_DIR)/gui/post_install_dialog/ui_post_install_dialog.h

$(SHARED_INTERMEDIATE_DIR)/gui/post_install_dialog/ui_post_install_dialog.h \
    : \
    post_install_dialog/post_install_dialog.ui
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/gui/post_install_dialog"
	@echo note: "Generating UI header files from post_install_dialog/post_install_dialog.ui"
	"$(QTDIR)/bin/uic" -o "$(SHARED_INTERMEDIATE_DIR)/gui/post_install_dialog/ui_post_install_dialog.h" "post_install_dialog/post_install_dialog.ui"

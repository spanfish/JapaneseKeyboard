all: \
    $(SHARED_INTERMEDIATE_DIR)/gui/post_install_dialog/moc_post_install_dialog.cc

$(SHARED_INTERMEDIATE_DIR)/gui/post_install_dialog/moc_post_install_dialog.cc \
    : \
    post_install_dialog/post_install_dialog.h
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/gui/post_install_dialog"
	@echo note: "Generatinc moc files from post_install_dialog/post_install_dialog.h"
	"$(QTDIR)/bin/moc" -p gui/post_install_dialog -o "$(SHARED_INTERMEDIATE_DIR)/gui/post_install_dialog/moc_post_install_dialog.cc" "post_install_dialog/post_install_dialog.h"

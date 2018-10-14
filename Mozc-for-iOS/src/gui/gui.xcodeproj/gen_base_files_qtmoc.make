all: \
    $(SHARED_INTERMEDIATE_DIR)/gui/base/moc_window_title_modifier.cc

$(SHARED_INTERMEDIATE_DIR)/gui/base/moc_window_title_modifier.cc \
    : \
    base/window_title_modifier.h
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/gui/base"
	@echo note: "Generatinc moc files from base/window_title_modifier.h"
	"$(QTDIR)/bin/moc" -p gui/base -o "$(SHARED_INTERMEDIATE_DIR)/gui/base/moc_window_title_modifier.cc" "base/window_title_modifier.h"

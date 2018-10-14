all: \
    $(SHARED_INTERMEDIATE_DIR)/gui/character_pad/moc_character_palette.cc \
    $(SHARED_INTERMEDIATE_DIR)/gui/character_pad/moc_character_palette_table_widget.cc \
    $(SHARED_INTERMEDIATE_DIR)/gui/character_pad/moc_hand_writing.cc \
    $(SHARED_INTERMEDIATE_DIR)/gui/character_pad/moc_hand_writing_canvas.cc \
    $(SHARED_INTERMEDIATE_DIR)/gui/character_pad/moc_hand_writing_thread.cc \
    $(SHARED_INTERMEDIATE_DIR)/gui/character_pad/moc_result_list.cc

$(SHARED_INTERMEDIATE_DIR)/gui/character_pad/moc_character_palette.cc \
    : \
    character_pad/character_palette.h
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/gui/character_pad"
	@echo note: "Generatinc moc files from character_pad/character_palette.h"
	"$(QTDIR)/bin/moc" -p gui/character_pad -o "$(SHARED_INTERMEDIATE_DIR)/gui/character_pad/moc_character_palette.cc" "character_pad/character_palette.h"

$(SHARED_INTERMEDIATE_DIR)/gui/character_pad/moc_character_palette_table_widget.cc \
    : \
    character_pad/character_palette_table_widget.h
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/gui/character_pad"
	@echo note: "Generatinc moc files from character_pad/character_palette_table_widget.h"
	"$(QTDIR)/bin/moc" -p gui/character_pad -o "$(SHARED_INTERMEDIATE_DIR)/gui/character_pad/moc_character_palette_table_widget.cc" "character_pad/character_palette_table_widget.h"

$(SHARED_INTERMEDIATE_DIR)/gui/character_pad/moc_hand_writing.cc \
    : \
    character_pad/hand_writing.h
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/gui/character_pad"
	@echo note: "Generatinc moc files from character_pad/hand_writing.h"
	"$(QTDIR)/bin/moc" -p gui/character_pad -o "$(SHARED_INTERMEDIATE_DIR)/gui/character_pad/moc_hand_writing.cc" "character_pad/hand_writing.h"

$(SHARED_INTERMEDIATE_DIR)/gui/character_pad/moc_hand_writing_canvas.cc \
    : \
    character_pad/hand_writing_canvas.h
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/gui/character_pad"
	@echo note: "Generatinc moc files from character_pad/hand_writing_canvas.h"
	"$(QTDIR)/bin/moc" -p gui/character_pad -o "$(SHARED_INTERMEDIATE_DIR)/gui/character_pad/moc_hand_writing_canvas.cc" "character_pad/hand_writing_canvas.h"

$(SHARED_INTERMEDIATE_DIR)/gui/character_pad/moc_hand_writing_thread.cc \
    : \
    character_pad/hand_writing_thread.h
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/gui/character_pad"
	@echo note: "Generatinc moc files from character_pad/hand_writing_thread.h"
	"$(QTDIR)/bin/moc" -p gui/character_pad -o "$(SHARED_INTERMEDIATE_DIR)/gui/character_pad/moc_hand_writing_thread.cc" "character_pad/hand_writing_thread.h"

$(SHARED_INTERMEDIATE_DIR)/gui/character_pad/moc_result_list.cc \
    : \
    character_pad/result_list.h
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/gui/character_pad"
	@echo note: "Generatinc moc files from character_pad/result_list.h"
	"$(QTDIR)/bin/moc" -p gui/character_pad -o "$(SHARED_INTERMEDIATE_DIR)/gui/character_pad/moc_result_list.cc" "character_pad/result_list.h"

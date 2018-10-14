all: \
    $(SHARED_INTERMEDIATE_DIR)/gui/character_pad/ui_character_palette.h \
    $(SHARED_INTERMEDIATE_DIR)/gui/character_pad/ui_hand_writing.h

$(SHARED_INTERMEDIATE_DIR)/gui/character_pad/ui_character_palette.h \
    : \
    character_pad/character_palette.ui
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/gui/character_pad"
	@echo note: "Generating UI header files from character_pad/character_palette.ui"
	"$(QTDIR)/bin/uic" -o "$(SHARED_INTERMEDIATE_DIR)/gui/character_pad/ui_character_palette.h" "character_pad/character_palette.ui"

$(SHARED_INTERMEDIATE_DIR)/gui/character_pad/ui_hand_writing.h \
    : \
    character_pad/hand_writing.ui
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/gui/character_pad"
	@echo note: "Generating UI header files from character_pad/hand_writing.ui"
	"$(QTDIR)/bin/uic" -o "$(SHARED_INTERMEDIATE_DIR)/gui/character_pad/ui_hand_writing.h" "character_pad/hand_writing.ui"

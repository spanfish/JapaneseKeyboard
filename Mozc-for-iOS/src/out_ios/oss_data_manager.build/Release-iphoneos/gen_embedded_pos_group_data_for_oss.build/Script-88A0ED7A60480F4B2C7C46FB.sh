#!/bin/sh
exec python ../../build_tools/redirect.py "${SHARED_INTERMEDIATE_DIR}/data_manager/oss/pos_group_data.h" ../../dictionary/gen_pos_rewrite_rule.py ../../data/dictionary_oss/id.def ../../data/rules/special_pos.def ../../data/rules/user_segment_history_pos_group.def
exit 1


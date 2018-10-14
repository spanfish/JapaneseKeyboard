#!/bin/sh
echo note: "Generating ${SHARED_INTERMEDIATE_DIR}/dictionary/pos_map.h"
exec python gen_pos_map.py "--user_pos_file=../data/rules/user_pos.def" "--third_party_pos_map_file=../data/rules/third_party_pos_map.def" "--output=${SHARED_INTERMEDIATE_DIR}/dictionary/pos_map.h"
exit 1


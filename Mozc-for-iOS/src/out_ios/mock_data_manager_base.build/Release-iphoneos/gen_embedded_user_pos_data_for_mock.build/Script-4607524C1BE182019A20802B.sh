#!/bin/sh
echo note: "[mock] Generating ${SHARED_INTERMEDIATE_DIR}/data_manager/testing/user_pos_data.h."
exec python ../../dictionary/gen_user_pos_data.py "--id_file=../../data/test/dictionary/id.def" "--special_pos_file=../../data/rules/special_pos.def" "--user_pos_file=../../data/rules/user_pos.def" "--cforms_file=../../data/rules/cforms.def" "--output=${SHARED_INTERMEDIATE_DIR}/data_manager/testing/user_pos_data.h"
exit 1


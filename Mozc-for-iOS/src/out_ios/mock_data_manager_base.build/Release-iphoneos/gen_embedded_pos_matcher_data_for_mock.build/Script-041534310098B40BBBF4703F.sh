#!/bin/sh
echo note: "[mock] Generating ${SHARED_INTERMEDIATE_DIR}/data_manager/testing/pos_matcher_data.h"
exec python ../../dictionary/gen_pos_matcher_code.py "--id_file=../../data/test/dictionary/id.def" "--special_pos_file=../../data/rules/special_pos.def" "--pos_matcher_rule_file=../../data/rules/pos_matcher_rule.def" "--output_pos_matcher_data=${SHARED_INTERMEDIATE_DIR}/data_manager/testing/pos_matcher_data.h"
exit 1


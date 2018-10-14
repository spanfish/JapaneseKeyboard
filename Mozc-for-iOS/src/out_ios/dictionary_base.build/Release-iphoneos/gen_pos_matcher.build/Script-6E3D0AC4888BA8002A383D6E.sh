#!/bin/sh
echo note: "Generating ${SHARED_INTERMEDIATE_DIR}/dictionary/pos_matcher.h"
exec python gen_pos_matcher_code.py "--pos_matcher_rule_file=../data/rules/pos_matcher_rule.def" "--output_pos_matcher_h=${SHARED_INTERMEDIATE_DIR}/dictionary/pos_matcher.h"
exit 1


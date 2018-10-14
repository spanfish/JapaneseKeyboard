#!/bin/sh
exec "${BUILT_PRODUCTS_DIR}/gen_usage_rewriter_dictionary_main" "--usage_data_file=../third_party/japanese_usage_dictionary/usage_dict.txt" "--cforms_file=../data/rules/cforms.def" "--output=${SHARED_INTERMEDIATE_DIR}/rewriter/usage_rewriter_data.h"
exit 1


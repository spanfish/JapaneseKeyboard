#!/bin/sh
echo note: "[oss] Generating ${SHARED_INTERMEDIATE_DIR}/data_manager/oss/symbol_rewriter_data.h"
exec "${BUILT_PRODUCTS_DIR}/gen_symbol_rewriter_dictionary_main" ../../data/symbol/symbol.tsv ../../data/rules/sorting_map.tsv ../../data/symbol/ordering_rule.txt "--output=${SHARED_INTERMEDIATE_DIR}/data_manager/oss/symbol_rewriter_data.h"
exit 1


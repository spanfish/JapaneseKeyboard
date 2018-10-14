#!/bin/sh
exec python gen_single_kanji_rewriter_data.py "--single_kanji_file=../data/single_kanji/single_kanji.tsv" "--variant_file=../data/single_kanji/variant_rule.txt" "--output=${SHARED_INTERMEDIATE_DIR}/rewriter/single_kanji_rewriter_data.h"
exit 1


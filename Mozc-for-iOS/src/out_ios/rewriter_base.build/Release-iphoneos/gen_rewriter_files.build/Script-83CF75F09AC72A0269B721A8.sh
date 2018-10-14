#!/bin/sh
exec python gen_emoji_rewriter_data.py "--input=../data/emoji/emoji_data.tsv" "--output=${SHARED_INTERMEDIATE_DIR}/rewriter/emoji_rewriter_data.h"
exit 1


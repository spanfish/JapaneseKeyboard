#!/bin/sh
exec python gen_emoticon_rewriter_data.py "--input=../data/emoticon/emoticon.tsv" "--output=${SHARED_INTERMEDIATE_DIR}/rewriter/emoticon_rewriter_data.h"
exit 1


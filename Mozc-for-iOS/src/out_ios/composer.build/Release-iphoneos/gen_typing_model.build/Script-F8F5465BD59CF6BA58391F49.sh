#!/bin/sh
exec python ../composer/internal/gen_typing_model.py --input_path ../data/typing/typing_model_12keys-hiragana.tsv --output_path "${SHARED_INTERMEDIATE_DIR}/composer/internal/typing_model_12keys-hiragana.h" --variable_name 12keysHiragana
exit 1


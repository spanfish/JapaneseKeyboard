#!/bin/sh
echo note: "[oss] Generating ${SHARED_INTERMEDIATE_DIR}/data_manager/oss/suffix_data.h"
exec python ../../build_tools/redirect.py "${SHARED_INTERMEDIATE_DIR}/data_manager/oss/suffix_data.h" ../../dictionary/gen_suffix_data.py ../../data/dictionary_oss/suffix.txt
exit 1


#!/bin/sh
echo note: "[oss] Generating ${SHARED_INTERMEDIATE_DIR}/data_manager/oss/oss_segmenter_inl.h."
exec python ../../build_tools/redirect.py "${SHARED_INTERMEDIATE_DIR}/data_manager/oss/oss_segmenter_inl.h" ../../converter/gen_segmenter_code.py ../../data/dictionary_oss/id.def ../../data/rules/special_pos.def ../../data/rules/segmenter.def
exit 1


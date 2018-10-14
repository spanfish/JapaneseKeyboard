#!/bin/sh
exec python ../build_tools/replace_version.py --version_file ../mozc_version.txt --input version_def_template.h --output "${SHARED_INTERMEDIATE_DIR}/base/version_def.h" --branding Mozc
exit 1


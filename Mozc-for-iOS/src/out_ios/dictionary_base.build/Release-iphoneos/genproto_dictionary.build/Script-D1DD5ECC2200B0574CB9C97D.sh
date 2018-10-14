#!/bin/sh
JOB_COUNT="$(/usr/sbin/sysctl -n hw.ncpu)"
if [ "${JOB_COUNT}" -gt 4 ]; then
  JOB_COUNT=4
fi
exec xcrun make -f "${PROJECT_FILE_PATH}/genproto_dictionary_genproto.make" -j "${JOB_COUNT}"
exit 1


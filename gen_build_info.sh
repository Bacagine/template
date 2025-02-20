#!/bin/bash

OUTPUT_FILE="./include/build.h"
BUILD_OS_NAME=$(uname -s)
BUILD_OS_VERSION=$(uname -r)
BUILD_OS_ARCH=$(uname -m)
BUILD_HOSTNAME=$(uname -n)
BUILD_COMPILER=$(gcc --version | head -n 1)
BUILD_COMPILER_VERSION=$(gcc -dumpversion)

if [ -f $OUTPUT_FILE ]; then
  rm $OUTPUT_FILE
fi

cat <<EOL > "$OUTPUT_FILE"
#ifndef _BUILD_H_
#define _BUILD_H_

#define BUILD_OS_NAME "$BUILD_OS_NAME"
#define BUILD_OS_VERSION "$BUILD_OS_VERSION"
#define BUILD_OS_ARCH "$BUILD_OS_ARCH"
#define BUILD_HOSTNAME "$BUILD_HOSTNAME"

#define BUILD_COMPILER "$BUILD_COMPILER"
#define BUILD_COMPILER_VERSION "$BUILD_COMPILER_VERSION"

#endif

EOL


#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'
ERROR="${RED}[ERROR]${NC}"
SUCCESS="${GREEN}[SUCCESS]${NC}"

argline=""
for arg in "$@"
do
    if [[ $arg == "--"* ]]; then
        argline+="${arg:2}="
    else
        argline+="\"$arg\""
    fi
done

gn_args="--args='$argline'"
gn gen out --args=$argline
if [ $? -ne 0 ]; then echo -e "${ERROR} Can't do gn gen" && exit 1; fi
ninja -C out scripts
if [ $? -ne 0 ]; then echo -e "${ERROR} Can't do ninja -C out scripts" && exit 1; fi
chmod +x out/build.sh
chmod +x out/run.sh
chmod +x out/all.sh

echo -e "${SUCCESS} Generated files with args: $*"
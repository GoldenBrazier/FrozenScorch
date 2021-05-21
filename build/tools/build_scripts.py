# Copyright 2021 Nikita Melekhin. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

import sys
import os

out = sys.argv[1]

if out[-1] == '/':
    out = out[:-1]

build = open("{0}/build.sh".format(out), "w")
build.write(
    """#!/bin/bash
GREEN='\\033[0;32m'
RED='\\033[0;31m'
NC='\\033[0m'
ERROR="${{RED}}[ERROR]${{NC}}"
SUCCESS="${{GREEN}}[SUCCESS]${{NC}}"

ninja -C {0}
if [ $? -ne 0 ]; then echo -e "${{ERROR}} Can't build" && exit 1; fi
echo -e "${{SUCCESS}} Build"
""".format(os.getcwd()))
build.close()

run = open("{0}/run.sh".format(out), "w")
run.write(
    """#!/bin/bash
{0}/OpenRenderer""".format(os.getcwd())
)
run.close()

allf = open("{0}/all.sh".format(out), "w")
allf.write(
    """#!/bin/bash
GREEN='\\033[0;32m'
RED='\\033[0;31m'
NC='\\033[0m'
ERROR="${{RED}}[ERROR]${{NC}}"
SUCCESS="${{GREEN}}[SUCCESS]${{NC}}"

{0}/build.sh
if [ $? -ne 0 ]; then echo -e "${{ERROR}} All command failed" && exit 1; fi
{0}/run.sh
if [ $? -ne 0 ]; then echo -e "${{ERROR}} All command failed" && exit 1; fi
""".format(os.getcwd()))
allf.close()

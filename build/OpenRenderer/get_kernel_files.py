# Copyright 2021 Nikita Melekhin. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

import os
import glob
import sys
# sys.argv[2] Target to generate for

ignore_platforms = []

allow_file_types = ["cpp", "c", "mm"]

def is_file_type(name, ending):
    if len(name) <= len(ending):
        return False
    return (name[-len(ending)-1::] == '.'+ending)

def is_src_file(name):
    for i in allow_file_types:
        if is_file_type(name, i):
            return True
    return False

def is_file_blocked(name):
    global ignore_platforms
    for platform in ignore_platforms:
        if (name.find(platform) != -1):
            return True
    return False


for path, subdirs, files in os.walk("../"):
    for name in files:
        # It runs from out dir, at least it should
        file = "//" + path[3:] + "/" + name
        if not is_src_file(name):
            continue
        if is_file_blocked(file):
            continue
        print(file)


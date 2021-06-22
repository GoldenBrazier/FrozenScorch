#!/usr/bin/env python
# LAUNCH FROM THE PROJECT ROOT DIR

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


def is_in_ignore_list(name):
    ignore_list = [
        "Libraries/SDL",
        "Libraries/glew",
        "build/",
        "cmake-build-debug/",
    ]

    for ignore_entry in ignore_list:
        if name.find(ignore_entry) != -1:
            return True
    return False


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


def get_files():
    res = ""
    for path, subdirs, files in os.walk("."):
        for name in files:
            file = path + "/" + name
            if not is_src_file(name):
                continue
            if is_in_ignore_list(file):
                continue
            if is_file_blocked(file):
                continue
            res += file + "\n"
    return res

def open_template():
    f = open("./CodeAssist/CMakeListsTemplate.txt", "r")
    res = f.read()
    f.close()
    return res

def write_cmake():
    res = open_template().format(files=get_files())
    f = open("CMakeLists.txt", "w")
    f.write(res)
    f.close()

write_cmake()
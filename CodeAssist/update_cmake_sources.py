#!/usr/bin/env python
# LAUNCH FROM THE PROJECT ROOT DIR

import os
import glob
import sys

# sys.argv[2] Target to generate for

ignore_platforms = []

generic_file_types = [
    'cpp',
    'c',
]

metal_file_types = ['mm']


def is_file_type(name, ending):
    if len(name) <= len(ending):
        return False
    return (name[-len(ending) - 1::] == '.' + ending)


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


def is_generic_file(name):
    return (
        any(is_file_type(name, file_type) for file_type in generic_file_types) and
        'Metal' not in name
    )


def is_apple_file(name):
    return (
        any(is_file_type(name, file_type) for file_type in metal_file_types) or
        any(is_file_type(name, file_type)
            for file_type in generic_file_types) and 'Metal' in name
    )


def is_file_blocked(name):
    global ignore_platforms
    for platform in ignore_platforms:
        if name.find(platform) != -1:
            return True
    return False


def get_files():
    generic_files = ''
    apple_files = ''

    for path, subdirs, files in os.walk("."):
        for name in files:
            file = path + "/" + name
            if is_in_ignore_list(file):
                continue
            if is_file_blocked(file):
                continue

            if is_generic_file(file):
                generic_files += file + "\n"
            elif is_apple_file(file):
                apple_files += file + "\n"

    return generic_files, apple_files


def open_template():
    with open("./CodeAssist/CMakeListsTemplate.txt", "r") as f:
        return f.read()


def write_cmake():
    generic_files, apple_files = get_files()
    res = open_template().format(generic_files=generic_files, apple_files=apple_files)
    with open("CMakeLists.txt", "w") as f:
        f.write(res)

write_cmake()

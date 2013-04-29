#!/usr/bin/env python
#
# Script to parse and output a list of layouts from OGDF sources.
#
import os
import re
import mmap
import sys

re_comments = re.compile("/\*.*?\*/|//.*?\r?\n", re.DOTALL)
re_class_decl = re.compile("class\s+([\w\d\s:]+){")
re_class_id = re.compile("(?:OGDF_EXPORT\s+)?([\w\d]+).*")
def scan_file(filename):
    names = []
    with open(filename) as file:
        unit = mmap.mmap(file.fileno(), 0, access=mmap.ACCESS_READ)
        unit = re.sub(re_comments, "", unit)
        for match in re.finditer(re_class_decl, unit):
            base = match.group(1).strip()
            if "Layout" in base:
                id = re.search(re_class_id, base).group(1)
                names.append(id)
    return names

def find_layouts(dirname):
    layouts = {}
    for dirpath, dirnames, filenames in os.walk(dirname):
        for filename in filenames:
            if filename.endswith(".h"):
                header = os.path.join(dirpath, filename)
                names = scan_file(header)
                for name in names:
                    layouts[name] = os.path.relpath(header, dirname)
    return layouts

def print_layouts(layouts):
    print("")
    for header in sorted(layouts.values()):
        print("#include \"" + header.replace("\\", "/") + "\"")

    print("")
    for name in sorted(layouts.keys()):
        print("CREATE_MODULE(" + name + ");")

    print("")
    for name in sorted(layouts.keys()):
        print(name + ",")

    print("")
    print("Found {0} layouts.".format(len(layouts)))

if len(sys.argv) != 2:
    sys.stderr.write("Usage: {0} <dirname>\n".format(sys.argv[0]))
    sys.exit(1)

print_layouts(find_layouts(sys.argv[1]))
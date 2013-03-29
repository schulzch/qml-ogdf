#!/usr/bin/env python
#
# Utility script to generate factory code for layout modules.
#
import os
import sys

layouts = sorted([
    "BalloonLayout",
    "CircularLayout",
    "ComponentSplitterLayout",
    "DavidsonHarelLayout",
    "DominanceLayout",
    "FastMultipoleEmbedder",
    "FastMultipoleMultilevelEmbedder",
    "FMMMLayout",
    "FPPLayout",
    "GEMLayout",
    "MixedForceLayout",
    "MixedModelLayout",
    "MMMExampleFastLayout",
    "MMMExampleNiceLayout",
    "MMMExampleNoTwistLayout",
    "ModularMultilevelMixer",
    "MultilevelLayout",
    "PlanarDrawLayout",
    "PlanarizationGridLayout",
    "PlanarizationLayout",
    "PlanarStraightLayout",
    "PreprocessorLayout",
    #SKIP: "ProcrustesSubLayout",
    "RadialTreeLayout",
    "ScalingLayout",
    "SchnyderLayout",
    "SpringEmbedderFR",
    "SpringEmbedderFRExact",
    "SpringEmbedderKK",
    "StressMajorization",
    "SugiyamaLayout",
    "TreeLayout",
    "TutteLayout",
    "UpwardPlanarizationLayout",
    "VisibilityLayout"
    ])

headers = {}
for root, dirs, files in os.walk("../ogdf/ogdf/"):
    for file in files:
        basename = file.replace(".h", "")           
        if basename in layouts:
            header = os.path.relpath(os.path.join(root, file), "../ogdf")
            headers[basename] = header

if len(headers) != len(layouts):
    print "Skipped header files for:"
    misses = set(layouts) - set(headers.keys())
    for miss in misses:
        print "  " + miss

print ""
for header in sorted(headers.values()):
    print "#include \"" + header.replace("\\", "/") + "\""
    
print ""
for layout in layouts:
    print "CREATE_MODULE(" + layout + ");"

print ""
for layout in layouts:
    print layout + ","

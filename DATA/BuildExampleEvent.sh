#!/bin/sh

# Commands used to build program to create example events.
# 22-May-2009 <seligman@nevis.columbia.edu>

# I assume that you've typed "module load root" before executing this
# script.  Note that in a more realistic development project, I'd use
# a "make" file instead of a shell script.

# The dictionary and library will be located in the current directory.
LIBDIR=.

# Semi-experimental Macintosh support.
OSTYPE=`uname`

if [ ${OSTYPE} = Darwin ]; then
    export MACOSX_DEPLOYMENT_TARGET=10.5 # or whatever your OS version is
    SHEXT=dylib
    SHARED=-dynamiclib -single_module -undefined dynamic_lookup
    RUNPATH=
else
    SHEXT=so
    SHARED=--shared
    RUNPATH=-Wl,-rpath=${LIBDIR}
fi

# Compiler and linker flags come from ROOT's configuration
FLAGS="`root-config --cflags --libs` -fPIC"

# Build the ROOT dictionary so we can read and write ExampleEvent
# objects. The file Linkdef.h is required by rootcling/rootcint.  If
# you're using a version of ROOT prior to ROOT 6, you'll need to use
# "rootcint" and not "rootcling".

# Get a string containing the ROOT version.
ROOT_VERSION=`root-config --version`
# Test if the first character of that string is "6".
if [[ ${ROOT_VERSION} =~ ^6 ]]; then
    rootcling -f ExampleEventDictionary.cxx -rml libExampleEvent.so \
            -rmf ExampleEvent.rootmap -c ExampleEvent.h LinkDef.h
else
    rootcint -f ExampleEventDictionary.cxx -c ExampleEvent.h LinkDef.h
fi

# Create a library so that many programs can share the definition and
# ROOT dictionary associated with ExampleEvent.
g++ ExampleEvent.cxx ExampleEventDictionary.cxx \
   ${FLAGS} \
   ${SHARED} -o ${LIBDIR}/libExampleEvent.${SHEXT}

# Compile and link the program to generate ExampleEvent objects.
g++ BuildExampleEvent.cxx -L. -lExampleEvent \
   ${FLAGS} ${RUNPATH} \
   -o BuildExampleEvents

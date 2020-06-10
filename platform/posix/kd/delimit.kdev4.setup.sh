#!/bin/bash
# ********************************************************************************
# *                                                                              *
# * delimit.kdev4.setup.sh                                                       *
# *                                                                              *
# ********************************************************************************

#
# Setup project files.
#
setup_project_files()
{
    #
    # Remove project directory if it exists.
    #
    if [ -d ../../../delimit/src/delimit ]
    then
        rm -rf ../../../delimit/src/delimit
    fi

    #
    # Create project directory.
    #
    mkdir ../../../delimit/src/delimit

    #
    # Copy files from source to project directory.
    #
    cp ../../../delimit/src/*.* ../../../delimit/src/delimit

    #
    # Copy project and make files to project directory.
    #
    cp delimit.kdev4 ../../../delimit/src/delimit
    cp Makefile ../../../delimit/src/delimit
}

# ------------------------------------------------------------------------------

setup_project_files
 

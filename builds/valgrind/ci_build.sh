#!/usr/bin/env bash

################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  READ THE ZPROJECT/README.MD FOR INFORMATION ABOUT MAKING PERMANENT CHANGES. #
################################################################################

set -x

cd ../..

mkdir tmp
BUILD_PREFIX=$PWD/tmp

CONFIG_OPTS=()
CONFIG_OPTS+=("CFLAGS=-I${BUILD_PREFIX}/include")
CONFIG_OPTS+=("CPPFLAGS=-I${BUILD_PREFIX}/include")
CONFIG_OPTS+=("CXXFLAGS=-I${BUILD_PREFIX}/include")
CONFIG_OPTS+=("LDFLAGS=-L${BUILD_PREFIX}/lib")
CONFIG_OPTS+=("PKG_CONFIG_PATH=${BUILD_PREFIX}/lib/pkgconfig")
CONFIG_OPTS+=("--prefix=${BUILD_PREFIX}")
CONFIG_OPTS+=("--with-docs=no")
CONFIG_OPTS+=("--quiet")

# Clone and build dependencies
echo "`date`: Starting build of dependencies (if any)..."
time git clone --quiet --depth 1 https://github.com/zeromq/libzmq.git libzmq.git
cd libzmq.git
git --no-pager log --oneline -n1
if [ -e autogen.sh ]; then
    time ./autogen.sh 2> /dev/null
fi
if [ -e buildconf ]; then
    time ./buildconf 2> /dev/null
fi
time ./configure "${CONFIG_OPTS[@]}"
time make -j4
time make install
cd ..
time git clone --quiet --depth 1 https://github.com/zeromq/czmq.git czmq.git
cd czmq.git
git --no-pager log --oneline -n1
if [ -e autogen.sh ]; then
    time ./autogen.sh 2> /dev/null
fi
if [ -e buildconf ]; then
    time ./buildconf 2> /dev/null
fi
time ./configure "${CONFIG_OPTS[@]}"
time make -j4
time make install
cd ..
time git clone --quiet --depth 1 https://github.com/zeromq/malamute.git malamute.git
cd malamute.git
git --no-pager log --oneline -n1
if [ -e autogen.sh ]; then
    time ./autogen.sh 2> /dev/null
fi
if [ -e buildconf ]; then
    time ./buildconf 2> /dev/null
fi
time ./configure "${CONFIG_OPTS[@]}"
time make -j4
time make install
cd ..
time git clone --quiet --depth 1 https://github.com/zeromq/zyre.git zyre.git
cd zyre.git
git --no-pager log --oneline -n1
if [ -e autogen.sh ]; then
    time ./autogen.sh 2> /dev/null
fi
if [ -e buildconf ]; then
    time ./buildconf 2> /dev/null
fi
time ./configure "${CONFIG_OPTS[@]}"
time make -j4
time make install
cd ..

# Build and check this project
echo "`date`: Starting build of currently tested project..."
time ./autogen.sh 2> /dev/null
time ./configure --enable-drafts=yes "${CONFIG_OPTS[@]}"
time make VERBOSE=1 memcheck || exit 1
echo "`date`: Builds completed without fatal errors!"

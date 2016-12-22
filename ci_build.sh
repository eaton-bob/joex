#!/usr/bin/env bash

################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  READ THE ZPROJECT/README.MD FOR INFORMATION ABOUT MAKING PERMANENT CHANGES. #
################################################################################

set -x
set -e

if [ "$BUILD_TYPE" == "default" ] || [ "$BUILD_TYPE" == "default-Werror" ] ; then
    LANG=C
    LC_ALL=C
    export LANG LC_ALL

    if [ -d "./tmp" ]; then
        rm -rf ./tmp
    fi
    mkdir -p tmp .ccache
    BUILD_PREFIX=$PWD/tmp

    CCACHE_PATH="$PATH"
    CCACHE_DIR="$PWD/.ccache"
    export CCACHE_PATH CCACHE_DIR
    HAVE_CCACHE=no
    if which ccache && ls -la /usr/lib/ccache ; then
        HAVE_CCACHE=yes
    fi

    CONFIG_OPTS=()
    COMMON_CFLAGS=""
    EXTRA_CFLAGS=""
    EXTRA_CPPFLAGS=""
    EXTRA_CXXFLAGS=""

    is_gnucc() {
        if [ -z "$1" ] && "$1" --version 2>&1 | grep 'Free Software Foundation' > /dev/null ; then true ; else false ; fi
    }

        COMPILER_FAMILY=""
        if [ -n "$CC" -a -n "$CXX" ]; then
            if is_gnucc "$CC" && is_gnucc "$CXX" ; then
                COMPILER_FAMILY="GCC"
                export CC CXX
            fi
        else
            if is_gnucc "gcc" && is_gnucc "g++" ; then
                # Autoconf would pick this by default
                COMPILER_FAMILY="GCC"
                [ -n "$CC" ] || CC=gcc
                [ -n "$CXX" ] || CXX=g++
                export CC CXX
            elif is_gnucc "cc" && is_gnucc "c++" ; then
                COMPILER_FAMILY="GCC"
                [ -n "$CC" ] || CC=cc
                [ -n "$CXX" ] || CXX=c++
                export CC CXX
            fi
        fi

        if [ -n "$CPP" ] ; then
            [ -x "$CPP" ] && export CPP
        else
            if is_gnucc "cpp" ; then
                CPP=cpp && export CPP
            fi
        fi

    if [ "$BUILD_TYPE" == "default-Werror" ] ; then
        case "${COMPILER_FAMILY}" in
            GCC)
                echo "NOTE: Enabling ${COMPILER_FAMILY} compiler pedantic error-checking flags for BUILD_TYPE='$BUILD_TYPE'" >&2
                COMMON_CFLAGS="-Wall -Werror"
                EXTRA_CFLAGS="-std=c99"
                EXTRA_CPPFLAGS=""
                EXTRA_CXXFLAGS="-std=c++99"
                ;;
            *)
                echo "WARNING: Current compiler is not GCC, not enabling pedantic error-checking flags for BUILD_TYPE='$BUILD_TYPE'" >&2
                ;;
        esac
    fi
    CONFIG_OPTS+=("CFLAGS=-I${BUILD_PREFIX}/include ${COMMON_CFLAGS} ${EXTRA_CFLAGS}")
    CONFIG_OPTS+=("CPPFLAGS=-I${BUILD_PREFIX}/include ${COMMON_CFLAGS} ${EXTRA_CPPFLAGS}")
    CONFIG_OPTS+=("CXXFLAGS=-I${BUILD_PREFIX}/include ${COMMON_CFLAGS} ${EXTRA_CXXFLAGS}")
    CONFIG_OPTS+=("LDFLAGS=-L${BUILD_PREFIX}/lib")
    CONFIG_OPTS+=("PKG_CONFIG_PATH=${BUILD_PREFIX}/lib/pkgconfig")
    CONFIG_OPTS+=("--prefix=${BUILD_PREFIX}")
    CONFIG_OPTS+=("--with-docs=no")
    CONFIG_OPTS+=("--quiet")
    if [ "$HAVE_CCACHE" = yes ] && [ "${COMPILER_FAMILY}" = GCC ]; then
        PATH="/usr/lib/ccache:$PATH"
        export PATH
        if [ -n "$CC" ] && [ -x "/usr/lib/ccache/`basename "$CC"`" ]; then
            case "$CC" in
                */*) DIR_CC="`dirname "$CC"`" && [ -n "$DIR_CC" ] && DIR_CC="`cd "$DIR_CC" && pwd `" && [ -n "$DIR_CC" ] && [ -d "$DIR_CC" ] || DIR_CC=""
                    [ -z "$CCACHE_PATH" ] && CCACHE_PATH="$DIR_CC" || \
                    if echo "$CCACHE_PATH" | egrep '(^'"$DIR_CC"':.*|^'"$DIR_CC"'$|:'"$DIR_CC"':|:'"$DIR_CC"'$)' ; then
                        CCACHE_PATH="$DIR_CC:$CCACHE_PATH"
                    fi
                    ;;
            esac
            CC="/usr/lib/ccache/`basename "$CC"`"
        else
            : # CC="ccache $CC"
        fi
        if [ -n "$CXX" ] && [ -x "/usr/lib/ccache/`basename "$CXX"`" ]; then
            case "$CXX" in
                */*) DIR_CXX="`dirname "$CXX"`" && [ -n "$DIR_CXX" ] && DIR_CXX="`cd "$DIR_CXX" && pwd `" && [ -n "$DIR_CXX" ] && [ -d "$DIR_CXX" ] || DIR_CXX=""
                    [ -z "$CCACHE_PATH" ] && CCACHE_PATH="$DIR_CXX" || \
                    if echo "$CCACHE_PATH" | egrep '(^'"$DIR_CXX"':.*|^'"$DIR_CXX"'$|:'"$DIR_CXX"':|:'"$DIR_CXX"'$)' ; then
                        CCACHE_PATH="$DIR_CXX:$CCACHE_PATH"
                    fi
                    ;;
            esac
            CXX="/usr/lib/ccache/`basename "$CXX"`"
        else
            : # CXX="ccache $CXX"
        fi
        if [ -n "$CPP" ] && [ -x "/usr/lib/ccache/`basename "$CPP"`" ]; then
            case "$CPP" in
                */*) DIR_CPP="`dirname "$CPP"`" && [ -n "$DIR_CPP" ] && DIR_CPP="`cd "$DIR_CPP" && pwd `" && [ -n "$DIR_CPP" ] && [ -d "$DIR_CPP" ] || DIR_CPP=""
                    [ -z "$CCACHE_PATH" ] && CCACHE_PATH="$DIR_CPP" || \
                    if echo "$CCACHE_PATH" | egrep '(^'"$DIR_CPP"':.*|^'"$DIR_CPP"'$|:'"$DIR_CPP"':|:'"$DIR_CPP"'$)' ; then
                        CCACHE_PATH="$DIR_CPP:$CCACHE_PATH"
                    fi
                    ;;
            esac
            CPP="/usr/lib/ccache/`basename "$CPP"`"
        else
            : # CPP="ccache $CPP"
        fi

        CONFIG_OPTS+=("CC=${CC}")
        CONFIG_OPTS+=("CXX=${CXX}")
        CONFIG_OPTS+=("CPP=${CPP}")
    fi

    # Clone and build dependencies
    echo "`date`: Starting build of dependencies (if any)..."
    time git clone --quiet --depth 1 https://github.com/zeromq/libzmq.git libzmq.git
    BASE_PWD=${PWD}
    cd libzmq.git
    CCACHE_BASEDIR=${PWD}
    export CCACHE_BASEDIR
    git --no-pager log --oneline -n1
    if [ -e autogen.sh ]; then
        time ./autogen.sh 2> /dev/null
    fi
    if [ -e buildconf ]; then
        time ./buildconf 2> /dev/null
    fi
    if [ ! -e autogen.sh ] && [ ! -e buildconf ] && [ ! -e ./configure ] && [ -s ./configure.ac ]; then
        time libtoolize --copy --force && \
        time aclocal -I . && \
        time autoheader && \
        time automake --add-missing --copy && \
        time autoconf || \
        time autoreconf -fiv
    fi
    time ./configure "${CONFIG_OPTS[@]}"
    time make -j4
    time make install
    cd "${BASE_PWD}"
    time git clone --quiet --depth 1 https://github.com/zeromq/czmq.git czmq.git
    BASE_PWD=${PWD}
    cd czmq.git
    CCACHE_BASEDIR=${PWD}
    export CCACHE_BASEDIR
    git --no-pager log --oneline -n1
    if [ -e autogen.sh ]; then
        time ./autogen.sh 2> /dev/null
    fi
    if [ -e buildconf ]; then
        time ./buildconf 2> /dev/null
    fi
    if [ ! -e autogen.sh ] && [ ! -e buildconf ] && [ ! -e ./configure ] && [ -s ./configure.ac ]; then
        time libtoolize --copy --force && \
        time aclocal -I . && \
        time autoheader && \
        time automake --add-missing --copy && \
        time autoconf || \
        time autoreconf -fiv
    fi
    time ./configure "${CONFIG_OPTS[@]}"
    time make -j4
    time make install
    cd "${BASE_PWD}"
    time git clone --quiet --depth 1 https://github.com/zeromq/malamute.git malamute.git
    BASE_PWD=${PWD}
    cd malamute.git
    CCACHE_BASEDIR=${PWD}
    export CCACHE_BASEDIR
    git --no-pager log --oneline -n1
    if [ -e autogen.sh ]; then
        time ./autogen.sh 2> /dev/null
    fi
    if [ -e buildconf ]; then
        time ./buildconf 2> /dev/null
    fi
    if [ ! -e autogen.sh ] && [ ! -e buildconf ] && [ ! -e ./configure ] && [ -s ./configure.ac ]; then
        time libtoolize --copy --force && \
        time aclocal -I . && \
        time autoheader && \
        time automake --add-missing --copy && \
        time autoconf || \
        time autoreconf -fiv
    fi
    time ./configure "${CONFIG_OPTS[@]}"
    time make -j4
    time make install
    cd "${BASE_PWD}"
    time git clone --quiet --depth 1 https://github.com/zeromq/zyre.git zyre.git
    BASE_PWD=${PWD}
    cd zyre.git
    CCACHE_BASEDIR=${PWD}
    export CCACHE_BASEDIR
    git --no-pager log --oneline -n1
    if [ -e autogen.sh ]; then
        time ./autogen.sh 2> /dev/null
    fi
    if [ -e buildconf ]; then
        time ./buildconf 2> /dev/null
    fi
    if [ ! -e autogen.sh ] && [ ! -e buildconf ] && [ ! -e ./configure ] && [ -s ./configure.ac ]; then
        time libtoolize --copy --force && \
        time aclocal -I . && \
        time autoheader && \
        time automake --add-missing --copy && \
        time autoconf || \
        time autoreconf -fiv
    fi
    time ./configure "${CONFIG_OPTS[@]}"
    time make -j4
    time make install
    cd "${BASE_PWD}"

    # Build and check this project; note that zprojects always have an autogen.sh
    echo "`date`: Starting build of currently tested project with DRAFT APIs..."
    CCACHE_BASEDIR=${PWD}
    export CCACHE_BASEDIR
    time ./autogen.sh 2> /dev/null
    time ./configure --enable-drafts=yes "${CONFIG_OPTS[@]}"
    time make VERBOSE=1 all

    echo "=== Are GitIgnores good after 'make all' with drafts? (should have no output below)"
    git status -s || true
    echo "==="

    if [ "$BUILD_TYPE" == "default-Werror" ] ; then
        echo "NOTE: Skipping distcheck for BUILD_TYPE='$BUILD_TYPE'" >&2
    else
        export DISTCHECK_CONFIGURE_FLAGS="--enable-drafts=yes ${CONFIG_OPTS[@]}"
        time make VERBOSE=1 DISTCHECK_CONFIGURE_FLAGS="$DISTCHECK_CONFIGURE_FLAGS" distcheck

        echo "=== Are GitIgnores good after 'make distcheck' with drafts? (should have no output below)"
        git status -s || true
        echo "==="
    fi

    # Build and check this project without DRAFT APIs
    echo "`date`: Starting build of currently tested project without DRAFT APIs..."
    make distclean
    git clean -f
    git reset --hard HEAD
    (
        time ./autogen.sh 2> /dev/null
        time ./configure --enable-drafts=no "${CONFIG_OPTS[@]}" --with-docs=yes
        time make VERBOSE=1 all || exit $?
        if [ "$BUILD_TYPE" == "default-Werror" ] ; then
            echo "NOTE: Skipping distcheck for BUILD_TYPE='$BUILD_TYPE'" >&2
        else
            export DISTCHECK_CONFIGURE_FLAGS="--enable-drafts=no ${CONFIG_OPTS[@]} --with-docs=yes" && \
            time make VERBOSE=1 DISTCHECK_CONFIGURE_FLAGS="$DISTCHECK_CONFIGURE_FLAGS" distcheck || exit $?
        fi
    ) || exit 1
    echo "`date`: Builds completed without fatal errors!"

    echo "=== Are GitIgnores good after 'make distcheck' without drafts? (should have no output below)"
    git status -s || true
    echo "==="

    if [ "$HAVE_CCACHE" = yes ]; then
        ccache -s
    fi

elif [ "$BUILD_TYPE" == "bindings" ]; then
    pushd "./bindings/${BINDING}" && ./ci_build.sh
else
    pushd "./builds/${BUILD_TYPE}" && REPO_DIR="$(dirs -l +1)" ./ci_build.sh
fi

#!/bin/sh
export DYLD_LIBRARY_PATH=`pwd`
export DYLD_FORCE_FLAT_NAMESPACE=1
export DYLD_INSERT_LIBRARIES=malloc
export LD_LIBRARY_PATH=`pwd`
export LD_PRELOAD=`pwd`/libft_malloc.so
$@

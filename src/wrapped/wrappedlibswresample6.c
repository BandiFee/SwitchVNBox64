#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

#include "wrappedlibs.h"

#include "debug.h"
#include "wrapper.h"
#include "bridge.h"
#include "librarian/library_private.h"
#include "x64emu.h"
#include "wrappedffmpeg8.h"

const char* libswresample6Name = "libswresample.so.6";

#define LIBNAME libswresample6

#define PRE_INIT \
    if(wrapped_ffmpeg8_preinit()) return -2;

#include "wrappedlib_init.h"

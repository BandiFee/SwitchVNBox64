#define _GNU_SOURCE
#include <dlfcn.h>
#include <pthread.h>
#include <stddef.h>
#include <stdint.h>

#include "box64context.h"
#include "debug.h"
#include "pathcoll.h"
#include "wrappedffmpeg8.h"

typedef struct ffmpeg8_symbol_s {
    const char* name;
    int required;
} ffmpeg8_symbol_t;

#define GO(N, W)       {#N, 1},
#define GOM(N, W)      {#N, 1},
#define GO2(N, W, O)   {#O, 1},
#define DATA(N, S)     {#N, 1},
#define GOW(N, W)      {#N, 0},
#define GOWM(N, W)     {#N, 0},
#define GOW2(N, W, O)  {#O, 0},
#define DATAV(N, S)    {#N, 0},
#define DATAB(N, S)    {#N, 1},
#define DATAM(N, S)
#define GOD(N, W, O)   GO(N, W)
#define GOWD(N, W, O)  GOW(N, W)

static const ffmpeg8_symbol_t avcodec62_symbols[] = {
#include "wrappedlibavcodec62_private.h"
};

static const ffmpeg8_symbol_t avformat62_symbols[] = {
#include "wrappedlibavformat62_private.h"
};

static const ffmpeg8_symbol_t avutil60_symbols[] = {
#include "wrappedlibavutil60_private.h"
};

static const ffmpeg8_symbol_t swscale9_symbols[] = {
#include "wrappedlibswscale9_private.h"
};

static const ffmpeg8_symbol_t swresample6_symbols[] = {
#include "wrappedlibswresample6_private.h"
};

#undef GO
#undef GOM
#undef GO2
#undef DATA
#undef GOW
#undef GOWM
#undef GOW2
#undef DATAV
#undef DATAB
#undef DATAM
#undef GOD
#undef GOWD

typedef struct ffmpeg8_library_s {
    const char* soname;
    const char* version_symbol;
    uint32_t minimum_version;
    const ffmpeg8_symbol_t* symbols;
    size_t symbol_count;
    void* handle;
} ffmpeg8_library_t;

#define AV_VERSION_INT(A, B, C) (((A) << 16) | ((B) << 8) | (C))
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

static ffmpeg8_library_t ffmpeg8_libraries[] = {
    {"libavcodec.so.62", "avcodec_version", AV_VERSION_INT(62, 28, 100), avcodec62_symbols, ARRAY_SIZE(avcodec62_symbols), NULL},
    {"libavformat.so.62", "avformat_version", AV_VERSION_INT(62, 12, 100), avformat62_symbols, ARRAY_SIZE(avformat62_symbols), NULL},
    {"libavutil.so.60", "avutil_version", AV_VERSION_INT(60, 26, 100), avutil60_symbols, ARRAY_SIZE(avutil60_symbols), NULL},
    {"libswscale.so.9", "swscale_version", AV_VERSION_INT(9, 5, 100), swscale9_symbols, ARRAY_SIZE(swscale9_symbols), NULL},
    {"libswresample.so.6", "swresample_version", AV_VERSION_INT(6, 3, 100), swresample6_symbols, ARRAY_SIZE(swresample6_symbols), NULL},
};

static pthread_once_t ffmpeg8_preinit_once = PTHREAD_ONCE_INIT;
static int ffmpeg8_preinit_result = -1;

static void close_ffmpeg8_libraries(void)
{
    for(size_t i = 0; i < ARRAY_SIZE(ffmpeg8_libraries); ++i) {
        if(ffmpeg8_libraries[i].handle) {
            dlclose(ffmpeg8_libraries[i].handle);
            ffmpeg8_libraries[i].handle = NULL;
        }
    }
}

static int ffmpeg8_is_forced_emulated(void)
{
    if(!my_context)
        return 0;
    for(size_t i = 0; i < ARRAY_SIZE(ffmpeg8_libraries); ++i)
        if(FindInCollection(ffmpeg8_libraries[i].soname, &my_context->box64_emulated_libs))
            return 1;
    return 0;
}

static void check_ffmpeg8_libraries(void)
{
    if(BOX64ENV(prefer_emulated)) {
        printf_log(LOG_DEBUG, "FFmpeg 8 native wrapper set disabled by BOX64_PREFER_EMULATED\n");
        return;
    }

    if(ffmpeg8_is_forced_emulated()) {
        printf_log(LOG_DEBUG, "FFmpeg 8 native wrapper set disabled by BOX64_EMULATED_LIBS\n");
        return;
    }

    for(size_t i = 0; i < ARRAY_SIZE(ffmpeg8_libraries); ++i) {
        ffmpeg8_library_t* library = &ffmpeg8_libraries[i];
        library->handle = dlopen(library->soname, RTLD_LAZY | RTLD_GLOBAL);
        if(!library->handle) {
            printf_log(LOG_DEBUG, "FFmpeg 8 native wrapper set unavailable: cannot load %s\n", library->soname);
            close_ffmpeg8_libraries();
            return;
        }
    }

    for(size_t i = 0; i < ARRAY_SIZE(ffmpeg8_libraries); ++i) {
        ffmpeg8_library_t* library = &ffmpeg8_libraries[i];
        uint32_t (*version_fnc)(void) = (uint32_t(*)(void))dlsym(library->handle, library->version_symbol);
        if(!version_fnc) {
            printf_log(LOG_DEBUG, "FFmpeg 8 native wrapper set unavailable: %s has no %s\n", library->soname, library->version_symbol);
            close_ffmpeg8_libraries();
            return;
        }
        const uint32_t version = version_fnc();
        if((version >> 16) != (library->minimum_version >> 16) || version < library->minimum_version) {
            printf_log(LOG_DEBUG, "FFmpeg 8 native wrapper set unavailable: %s version %u.%u.%u is incompatible\n",
                library->soname, version >> 16, (version >> 8) & 0xff, version & 0xff);
            close_ffmpeg8_libraries();
            return;
        }
        for(size_t j = 0; j < library->symbol_count; ++j) {
            const ffmpeg8_symbol_t* symbol = &library->symbols[j];
            if(symbol->required && !dlsym(library->handle, symbol->name)) {
                printf_log(LOG_DEBUG, "FFmpeg 8 native wrapper set unavailable: %s has no %s\n", library->soname, symbol->name);
                close_ffmpeg8_libraries();
                return;
            }
        }
    }

    ffmpeg8_preinit_result = 0;
}

int wrapped_ffmpeg8_preinit(void)
{
    pthread_once(&ffmpeg8_preinit_once, check_ffmpeg8_libraries);
    return ffmpeg8_preinit_result;
}

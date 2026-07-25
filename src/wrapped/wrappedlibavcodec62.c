#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <pthread.h>
#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <dlfcn.h>

#include "wrappedlibs.h"

#include "debug.h"
#include "wrapper.h"
#include "bridge.h"
#include "librarian/library_private.h"
#include "x64emu.h"
#include "emu/x64emu_private.h"
#include "callback.h"
#include "librarian.h"
#include "box64context.h"
#include "myalign.h"
#include "wrappedffmpeg8.h"

const char* libavcodec62Name = "libavcodec.so.62";

#define LIBNAME libavcodec62
#define ALTMY my62_

#define ADDED_FUNCTIONS()

#include "generated/wrappedlibavcodec62types.h"

#include "wrappercallback.h"

static void codec62_prepare_context(void* avctx);
static void codec62_finish_context(void* avctx);
static void codec62_guest_callback_enter(void* avctx);
static void codec62_guest_callback_leave(void* avctx);
static uintptr_t codec62_guest_callback_enter_slot(void* avctx, int callback,
    uintptr_t fallback);

enum {
    CODEC62_DRAW_HORIZ_BAND,
    CODEC62_GET_FORMAT,
    CODEC62_GET_BUFFER2,
    CODEC62_EXECUTE,
    CODEC62_EXECUTE2,
    CODEC62_GET_ENCODE_BUFFER,
    CODEC62_CALLBACK_COUNT
};

#define SUPER() \
GO(0)           \
GO(1)           \
GO(2)           \
GO(3)           \
GO(4)           \
GO(5)           \
GO(6)           \
GO(7)           \
GO(8)           \
GO(9)           \
GO(10)          \
GO(11)          \
GO(12)          \
GO(13)          \
GO(14)          \
GO(15)

// avcodec_default_execute task callback
#define GO(A)                                                               \
static uintptr_t my_execute_fct_##A = 0;                                    \
static int my_execute_##A(void* avctx, void* arg)                           \
{                                                                           \
    codec62_guest_callback_enter(avctx);                                     \
    int ret = (int)RunFunctionFmt(my_execute_fct_##A, "pp", avctx, arg);    \
    codec62_guest_callback_leave(avctx);                                     \
    return ret;                                                              \
}
SUPER()
#undef GO

static void* find_execute_Fct(void* fct)
{
    if(!fct)
        return NULL;
    void* native = GetNativeFnc((uintptr_t)fct);
    if(native)
        return native;
#define GO(A) if(my_execute_fct_##A == (uintptr_t)fct) return my_execute_##A;
    SUPER()
#undef GO
#define GO(A) if(my_execute_fct_##A == 0) { my_execute_fct_##A = (uintptr_t)fct; return my_execute_##A; }
    SUPER()
#undef GO
    printf_log(LOG_NONE, "Warning, no more slot for libavcodec62 execute callback\n");
    return NULL;
}

// avcodec_default_execute2 task callback
#define GO(A)                                                                       \
static uintptr_t my_execute2_fct_##A = 0;                                           \
static int my_execute2_##A(void* avctx, void* arg, int jobnr, int threadnr)         \
{                                                                                   \
    codec62_guest_callback_enter(avctx);                                             \
    int ret = (int)RunFunctionFmt(my_execute2_fct_##A, "ppii", avctx, arg, jobnr, threadnr); \
    codec62_guest_callback_leave(avctx);                                             \
    return ret;                                                                      \
}
SUPER()
#undef GO

static void* find_execute2_Fct(void* fct)
{
    if(!fct)
        return NULL;
    void* native = GetNativeFnc((uintptr_t)fct);
    if(native)
        return native;
#define GO(A) if(my_execute2_fct_##A == (uintptr_t)fct) return my_execute2_##A;
    SUPER()
#undef GO
#define GO(A) if(my_execute2_fct_##A == 0) { my_execute2_fct_##A = (uintptr_t)fct; return my_execute2_##A; }
    SUPER()
#undef GO
    printf_log(LOG_NONE, "Warning, no more slot for libavcodec62 execute2 callback\n");
    return NULL;
}

typedef int (*codec62_execute_native_t)(void*, void*, void*, void*, int, int);
typedef int (*codec62_execute2_native_t)(void*, void*, void*, void*, int);
typedef int (*codec62_execute_task_native_t)(void*, void*);
typedef int (*codec62_execute2_task_native_t)(void*, void*, int, int);

static pthread_mutex_t codec62_reverse_mutex = PTHREAD_MUTEX_INITIALIZER;
static void* codec62_native_execute[16] = {0};
static void* codec62_native_execute2[16] = {0};
static void* codec62_native_execute_task[16] = {0};
static void* codec62_native_execute2_task[16] = {0};

static void* codec62_get_reverse_target(void** targets, int slot)
{
    pthread_mutex_lock(&codec62_reverse_mutex);
    void* target = targets[slot];
    pthread_mutex_unlock(&codec62_reverse_mutex);
    return target;
}

#define GO(A)                                                                       \
static int codec62_guest_execute_##A(void* avctx, void* func, void* arg,            \
    void* ret, int count, int size)                                                  \
{                                                                                   \
    codec62_prepare_context(avctx);                                                  \
    codec62_execute_native_t f = (codec62_execute_native_t)                          \
        codec62_get_reverse_target(codec62_native_execute, A);                      \
    int result = f ? f(avctx, find_execute_Fct(func), arg, ret, count, size) : -1;  \
    codec62_finish_context(avctx);                                                   \
    return result;                                                                  \
}
SUPER()
#undef GO

#define GO(A)                                                                       \
static int codec62_guest_execute2_##A(void* avctx, void* func, void* arg,           \
    void* ret, int count)                                                            \
{                                                                                   \
    codec62_prepare_context(avctx);                                                  \
    codec62_execute2_native_t f = (codec62_execute2_native_t)                        \
        codec62_get_reverse_target(codec62_native_execute2, A);                     \
    int result = f ? f(avctx, find_execute2_Fct(func), arg, ret, count) : -1;       \
    codec62_finish_context(avctx);                                                   \
    return result;                                                                  \
}
SUPER()
#undef GO

#define GO(A)                                                                       \
static int codec62_guest_execute_task_##A(void* avctx, void* arg)                   \
{                                                                                   \
    codec62_prepare_context(avctx);                                                  \
    codec62_execute_task_native_t f =                                               \
        (codec62_execute_task_native_t)                                              \
        codec62_get_reverse_target(codec62_native_execute_task, A);                 \
    int result = f ? f(avctx, arg) : -1;                                            \
    codec62_finish_context(avctx);                                                   \
    return result;                                                                  \
}
SUPER()
#undef GO

#define GO(A)                                                                       \
static int codec62_guest_execute2_task_##A(void* avctx, void* arg,                  \
    int jobnr, int threadnr)                                                         \
{                                                                                   \
    codec62_prepare_context(avctx);                                                  \
    codec62_execute2_task_native_t f =                                              \
        (codec62_execute2_task_native_t)                                             \
        codec62_get_reverse_target(codec62_native_execute2_task, A);                \
    int result = f ? f(avctx, arg, jobnr, threadnr) : -1;                          \
    codec62_finish_context(avctx);                                                   \
    return result;                                                                  \
}
SUPER()
#undef GO

#define GO(A) codec62_guest_execute_##A,
static void* const codec62_guest_execute_wrappers[16] = { SUPER() };
#undef GO
#define GO(A) codec62_guest_execute2_##A,
static void* const codec62_guest_execute2_wrappers[16] = { SUPER() };
#undef GO
#define GO(A) codec62_guest_execute_task_##A,
static void* const codec62_guest_execute_task_wrappers[16] = { SUPER() };
#undef GO
#define GO(A) codec62_guest_execute2_task_##A,
static void* const codec62_guest_execute2_task_wrappers[16] = { SUPER() };
#undef GO

static void* codec62_add_reverse_bridge(void* native, void** targets,
    void* const* wrappers, wrapper_t w, const char* name)
{
    if(!native)
        return NULL;

    int slot = -1;
    pthread_mutex_lock(&codec62_reverse_mutex);
    for(int i = 0; i < 16; ++i)
        if(targets[i] == native) {
            slot = i;
            break;
        }
    if(slot < 0)
        for(int i = 0; i < 16; ++i)
            if(!targets[i]) {
                targets[i] = native;
                slot = i;
                break;
            }
    pthread_mutex_unlock(&codec62_reverse_mutex);

    if(slot < 0) {
        printf_log(LOG_NONE, "Warning, no more slot for libavcodec62 %s bridge\n", name);
        return (void*)AddCheckBridge(my_lib->w.bridge, w, native, 0, name);
    }
    return (void*)AddCheckBridge(my_lib->w.bridge, w, wrappers[slot], 0, name);
}

static void* codec62_bridge_native_execute(void* native)
{
    return codec62_add_reverse_bridge(native, codec62_native_execute,
        codec62_guest_execute_wrappers, iFppppii, "AVCodecContext.execute");
}

static void* codec62_bridge_native_execute2(void* native)
{
    return codec62_add_reverse_bridge(native, codec62_native_execute2,
        codec62_guest_execute2_wrappers, iFppppi, "AVCodecContext.execute2");
}

static void* codec62_bridge_native_execute_task(void* native)
{
    return codec62_add_reverse_bridge(native, codec62_native_execute_task,
        codec62_guest_execute_task_wrappers, iFpp, "AVCodecContext.execute.func");
}

static void* codec62_bridge_native_execute2_task(void* native)
{
    return codec62_add_reverse_bridge(native, codec62_native_execute2_task,
        codec62_guest_execute2_task_wrappers, iFppii, "AVCodecContext.execute2.func");
}

static void* codec62_unwrap_reverse_bridge(void* wrapper, void** targets,
    void* const* wrappers)
{
    void* native = NULL;
    pthread_mutex_lock(&codec62_reverse_mutex);
    for(int i = 0; i < 16; ++i)
        if(wrappers[i] == wrapper) {
            native = targets[i];
            break;
        }
    pthread_mutex_unlock(&codec62_reverse_mutex);
    return native;
}

static uintptr_t codec62_guest_draw_horiz_band[16] = {0};
static uintptr_t codec62_guest_get_format[16] = {0};
static uintptr_t codec62_guest_get_buffer2[16] = {0};
static uintptr_t codec62_guest_execute_callback[16] = {0};
static uintptr_t codec62_guest_execute2_callback[16] = {0};
static uintptr_t codec62_guest_get_encode_buffer[16] = {0};

static uintptr_t codec62_get_guest_target(uintptr_t* targets, int slot)
{
    pthread_mutex_lock(&codec62_reverse_mutex);
    uintptr_t target = targets[slot];
    pthread_mutex_unlock(&codec62_reverse_mutex);
    return target;
}

static void* codec62_add_guest_callback(uintptr_t guest, uintptr_t* targets,
    void* const* wrappers, const char* name);

static uintptr_t codec62_guest_dct_block[16] = {0};
static uintptr_t codec62_guest_dct_pixels[16] = {0};

#define GO(A)                                                                       \
static void codec62_dct_block_##A(void* block)                                      \
{                                                                                   \
    uintptr_t guest = codec62_get_guest_target(codec62_guest_dct_block, A);         \
    if(guest)                                                                        \
        RunFunctionFmt(guest, "p", block);                                           \
}
SUPER()
#undef GO

#define GO(A)                                                                       \
static void codec62_dct_pixels_##A(void* block, void* pixels, ptrdiff_t line_size)  \
{                                                                                   \
    uintptr_t guest = codec62_get_guest_target(codec62_guest_dct_pixels, A);        \
    if(guest)                                                                        \
        RunFunctionFmt(guest, "ppl", block, pixels, line_size);                      \
}
SUPER()
#undef GO

#define GO(A) codec62_dct_block_##A,
static void* const codec62_dct_block_wrappers[16] = { SUPER() };
#undef GO
#define GO(A) codec62_dct_pixels_##A,
static void* const codec62_dct_pixels_wrappers[16] = { SUPER() };
#undef GO

static void* codec62_find_dct_block_Fct(void* fct)
{
    if(!fct)
        return NULL;
    void* native = GetNativeFnc((uintptr_t)fct);
    return native ? native : codec62_add_guest_callback((uintptr_t)fct,
        codec62_guest_dct_block, codec62_dct_block_wrappers, "AVDCT block");
}

static void* codec62_find_dct_pixels_Fct(void* fct)
{
    if(!fct)
        return NULL;
    void* native = GetNativeFnc((uintptr_t)fct);
    return native ? native : codec62_add_guest_callback((uintptr_t)fct,
        codec62_guest_dct_pixels, codec62_dct_pixels_wrappers, "AVDCT get_pixels");
}

static void* codec62_unwrap_guest_callback(void* callback, uintptr_t* targets,
    void* const* wrappers)
{
    void* guest = NULL;
    pthread_mutex_lock(&codec62_reverse_mutex);
    for(int i = 0; i < 16; ++i)
        if(wrappers[i] == callback) {
            guest = (void*)targets[i];
            break;
        }
    pthread_mutex_unlock(&codec62_reverse_mutex);
    return guest;
}

static void* codec62_reverse_dct_block_Fct(void* fct)
{
    if(!fct)
        return NULL;
    void* guest = codec62_unwrap_guest_callback(fct, codec62_guest_dct_block,
        codec62_dct_block_wrappers);
    return guest ? guest
        : (void*)AddCheckBridge(my_lib->w.bridge, vFp, fct, 0, "AVDCT block");
}

static void* codec62_reverse_dct_pixels_Fct(void* fct)
{
    if(!fct)
        return NULL;
    void* guest = codec62_unwrap_guest_callback(fct, codec62_guest_dct_pixels,
        codec62_dct_pixels_wrappers);
    return guest ? guest
        : (void*)AddCheckBridge(my_lib->w.bridge, vFppl, fct, 0,
            "AVDCT get_pixels");
}

static const size_t codec62_dct_callback_offsets[] = {8, 80, 96, 112};

static void codec62_dct_prepare(void* dct)
{
    if(!dct)
        return;
    for(int i = 0; i < 4; ++i) {
        void** field = (void**)((uintptr_t)dct + codec62_dct_callback_offsets[i]);
        *field = i < 2 ? codec62_find_dct_block_Fct(*field)
                       : codec62_find_dct_pixels_Fct(*field);
    }
}

static void codec62_dct_restore(void* dct)
{
    if(!dct)
        return;
    for(int i = 0; i < 4; ++i) {
        void** field = (void**)((uintptr_t)dct + codec62_dct_callback_offsets[i]);
        *field = i < 2 ? codec62_reverse_dct_block_Fct(*field)
                       : codec62_reverse_dct_pixels_Fct(*field);
    }
}

static uintptr_t codec62_guest_vdp_get_proc[16] = {0};

#define GO(A)                                                                       \
static uint32_t codec62_vdp_get_proc_##A(uint32_t device, uint32_t function_id,     \
    void* output)                                                                   \
{                                                                                   \
    uintptr_t guest = codec62_get_guest_target(codec62_guest_vdp_get_proc, A);      \
    uint32_t ret = guest                                                            \
        ? (uint32_t)RunFunctionFmt(guest, "uup", device, function_id, output)        \
        : 1;                                                                        \
    if(!ret && output && *(void**)output) {                                          \
        void* native = getBridgeFnc2(*(void**)output);                              \
        if(!native)                                                                  \
            native = GetNativeFnc((uintptr_t)*(void**)output);                      \
        if(!native) {                                                                \
            printf_log(LOG_NONE, "Warning, unsupported guest VDPAU function %u\n",  \
                function_id);                                                       \
            *(void**)output = NULL;                                                  \
            return 1;                                                               \
        }                                                                           \
        *(void**)output = native;                                                    \
    }                                                                               \
    return ret;                                                                      \
}
SUPER()
#undef GO

#define GO(A) codec62_vdp_get_proc_##A,
static void* const codec62_vdp_get_proc_wrappers[16] = { SUPER() };
#undef GO

static void* codec62_find_vdp_get_proc_Fct(void* fct)
{
    if(!fct)
        return NULL;
    void* native = getBridgeFnc2(fct);
    if(!native)
        native = GetNativeFnc((uintptr_t)fct);
    return native ? native : codec62_add_guest_callback((uintptr_t)fct,
        codec62_guest_vdp_get_proc, codec62_vdp_get_proc_wrappers,
        "VdpGetProcAddress");
}

#define GO(A)                                                                       \
static void codec62_draw_horiz_band_##A(void* avctx, void* frame, void* offset,     \
    int y, int type, int height)                                                     \
{                                                                                   \
    uintptr_t fallback = codec62_get_guest_target(                                  \
        codec62_guest_draw_horiz_band, A);                                          \
    uintptr_t guest = codec62_guest_callback_enter_slot(                            \
        avctx, CODEC62_DRAW_HORIZ_BAND, fallback);                                  \
    if(guest)                                                                        \
        RunFunctionFmt(guest, "pppiii", avctx, frame, offset, y, type, height);     \
    codec62_guest_callback_leave(avctx);                                             \
}
SUPER()
#undef GO

#define GO(A)                                                                       \
static int codec62_get_format_##A(void* avctx, void* formats)                       \
{                                                                                   \
    uintptr_t fallback = codec62_get_guest_target(codec62_guest_get_format, A);     \
    uintptr_t guest = codec62_guest_callback_enter_slot(                            \
        avctx, CODEC62_GET_FORMAT, fallback);                                       \
    int result = guest ? (int)RunFunctionFmt(guest, "pp", avctx, formats) : -1;    \
    codec62_guest_callback_leave(avctx);                                             \
    return result;                                                                  \
}
SUPER()
#undef GO

#define GO(A)                                                                       \
static int codec62_get_buffer2_##A(void* avctx, void* frame, int flags)             \
{                                                                                   \
    uintptr_t fallback = codec62_get_guest_target(codec62_guest_get_buffer2, A);    \
    uintptr_t guest = codec62_guest_callback_enter_slot(                            \
        avctx, CODEC62_GET_BUFFER2, fallback);                                      \
    int result = guest ? (int)RunFunctionFmt(guest, "ppi", avctx, frame, flags)    \
                       : -1;                                                        \
    codec62_guest_callback_leave(avctx);                                             \
    return result;                                                                  \
}
SUPER()
#undef GO

#define GO(A)                                                                       \
static int codec62_execute_callback_##A(void* avctx, void* func, void* arg,         \
    void* ret, int count, int size)                                                  \
{                                                                                   \
    uintptr_t fallback = codec62_get_guest_target(                                  \
        codec62_guest_execute_callback, A);                                         \
    uintptr_t guest = codec62_guest_callback_enter_slot(                            \
        avctx, CODEC62_EXECUTE, fallback);                                          \
    void* bridged = codec62_bridge_native_execute_task(func);                       \
    int result = guest                                                              \
        ? (int)RunFunctionFmt(guest, "ppppii", avctx, bridged, arg, ret, count, size) \
        : -1;                                                                       \
    codec62_guest_callback_leave(avctx);                                             \
    return result;                                                                  \
}
SUPER()
#undef GO

#define GO(A)                                                                       \
static int codec62_execute2_callback_##A(void* avctx, void* func, void* arg,        \
    void* ret, int count)                                                            \
{                                                                                   \
    uintptr_t fallback = codec62_get_guest_target(                                  \
        codec62_guest_execute2_callback, A);                                        \
    uintptr_t guest = codec62_guest_callback_enter_slot(                            \
        avctx, CODEC62_EXECUTE2, fallback);                                         \
    void* bridged = codec62_bridge_native_execute2_task(func);                      \
    int result = guest                                                              \
        ? (int)RunFunctionFmt(guest, "ppppi", avctx, bridged, arg, ret, count)      \
        : -1;                                                                       \
    codec62_guest_callback_leave(avctx);                                             \
    return result;                                                                  \
}
SUPER()
#undef GO

#define GO(A)                                                                       \
static int codec62_get_encode_buffer_##A(void* avctx, void* packet, int flags)      \
{                                                                                   \
    uintptr_t fallback = codec62_get_guest_target(                                  \
        codec62_guest_get_encode_buffer, A);                                        \
    uintptr_t guest = codec62_guest_callback_enter_slot(                            \
        avctx, CODEC62_GET_ENCODE_BUFFER, fallback);                                \
    int result = guest ? (int)RunFunctionFmt(guest, "ppi", avctx, packet, flags)   \
                       : -1;                                                        \
    codec62_guest_callback_leave(avctx);                                             \
    return result;                                                                  \
}
SUPER()
#undef GO

#define GO(A) codec62_draw_horiz_band_##A,
static void* const codec62_draw_horiz_band_wrappers[16] = { SUPER() };
#undef GO
#define GO(A) codec62_get_format_##A,
static void* const codec62_get_format_wrappers[16] = { SUPER() };
#undef GO
#define GO(A) codec62_get_buffer2_##A,
static void* const codec62_get_buffer2_wrappers[16] = { SUPER() };
#undef GO
#define GO(A) codec62_execute_callback_##A,
static void* const codec62_execute_callback_wrappers[16] = { SUPER() };
#undef GO
#define GO(A) codec62_execute2_callback_##A,
static void* const codec62_execute2_callback_wrappers[16] = { SUPER() };
#undef GO
#define GO(A) codec62_get_encode_buffer_##A,
static void* const codec62_get_encode_buffer_wrappers[16] = { SUPER() };
#undef GO

static void* codec62_add_guest_callback(uintptr_t guest, uintptr_t* targets,
    void* const* wrappers, const char* name)
{
    if(!guest)
        return NULL;

    int slot = -1;
    pthread_mutex_lock(&codec62_reverse_mutex);
    for(int i = 0; i < 16; ++i)
        if(targets[i] == guest) {
            slot = i;
            break;
        }
    if(slot < 0)
        for(int i = 0; i < 16; ++i)
            if(!targets[i]) {
                targets[i] = guest;
                slot = i;
                break;
            }
    pthread_mutex_unlock(&codec62_reverse_mutex);

    if(slot < 0) {
        printf_log(LOG_NONE, "Warning, no more slot for libavcodec62 %s callback\n",
            name);
        return NULL;
    }
    return wrappers[slot];
}

static void* codec62_find_guest_callback(int callback, void* guest)
{
    switch(callback) {
        case CODEC62_DRAW_HORIZ_BAND:
            return codec62_add_guest_callback((uintptr_t)guest,
                codec62_guest_draw_horiz_band, codec62_draw_horiz_band_wrappers,
                "draw_horiz_band");
        case CODEC62_GET_FORMAT:
            return codec62_add_guest_callback((uintptr_t)guest,
                codec62_guest_get_format, codec62_get_format_wrappers, "get_format");
        case CODEC62_GET_BUFFER2:
            return codec62_add_guest_callback((uintptr_t)guest,
                codec62_guest_get_buffer2, codec62_get_buffer2_wrappers, "get_buffer2");
        case CODEC62_EXECUTE:
            return codec62_add_guest_callback((uintptr_t)guest,
                codec62_guest_execute_callback, codec62_execute_callback_wrappers,
                "execute");
        case CODEC62_EXECUTE2:
            return codec62_add_guest_callback((uintptr_t)guest,
                codec62_guest_execute2_callback, codec62_execute2_callback_wrappers,
                "execute2");
        case CODEC62_GET_ENCODE_BUFFER:
            return codec62_add_guest_callback((uintptr_t)guest,
                codec62_guest_get_encode_buffer, codec62_get_encode_buffer_wrappers,
                "get_encode_buffer");
        default:
            return NULL;
    }
}

#undef SUPER

static const size_t codec62_callback_offsets[CODEC62_CALLBACK_COUNT] = {
    184, 192, 408, 672, 680, 816
};

typedef struct codec62_shadow_s {
    void* avctx;
    void* native[CODEC62_CALLBACK_COUNT];
    void* guest[CODEC62_CALLBACK_COUNT];
    void* installed[CODEC62_CALLBACK_COUNT];
    unsigned int native_depth;
    unsigned int callback_depth;
    struct codec62_shadow_s* next;
} codec62_shadow_t;

static pthread_mutex_t codec62_shadow_mutex = PTHREAD_MUTEX_INITIALIZER;
static codec62_shadow_t* codec62_shadows = NULL;

static codec62_shadow_t* codec62_find_shadow_locked(void* avctx)
{
    for(codec62_shadow_t* shadow = codec62_shadows; shadow; shadow = shadow->next)
        if(shadow->avctx == avctx)
            return shadow;
    return NULL;
}

static void* codec62_read_callback(void* avctx, int callback)
{
    void* value;
    memcpy(&value, (char*)avctx + codec62_callback_offsets[callback], sizeof(value));
    return value;
}

static void codec62_write_callback(void* avctx, int callback, void* value)
{
    memcpy((char*)avctx + codec62_callback_offsets[callback], &value, sizeof(value));
}

static void* codec62_bridge_native_callback(int callback, void* native)
{
    if(!native)
        return NULL;
    switch(callback) {
        case CODEC62_DRAW_HORIZ_BAND:
            return (void*)AddCheckBridge(my_lib->w.bridge, vFpppiii, native, 0,
                "AVCodecContext.draw_horiz_band");
        case CODEC62_GET_FORMAT:
            return (void*)AddCheckBridge(my_lib->w.bridge, iFpp, native, 0,
                "AVCodecContext.get_format");
        case CODEC62_GET_BUFFER2:
            return (void*)AddCheckBridge(my_lib->w.bridge, iFppi, native, 0,
                "AVCodecContext.get_buffer2");
        case CODEC62_EXECUTE:
            return codec62_bridge_native_execute(native);
        case CODEC62_EXECUTE2:
            return codec62_bridge_native_execute2(native);
        case CODEC62_GET_ENCODE_BUFFER:
            return (void*)AddCheckBridge(my_lib->w.bridge, iFppi, native, 0,
                "AVCodecContext.get_encode_buffer");
        default:
            return NULL;
    }
}

static void* codec62_guest_to_native_callback(int callback, void* guest)
{
    if(!guest)
        return NULL;
    void* native = GetNativeFnc((uintptr_t)guest);
    if(native && callback == CODEC62_EXECUTE) {
        void* target = codec62_unwrap_reverse_bridge(native, codec62_native_execute,
            codec62_guest_execute_wrappers);
        if(target)
            native = target;
    } else if(native && callback == CODEC62_EXECUTE2) {
        void* target = codec62_unwrap_reverse_bridge(native, codec62_native_execute2,
            codec62_guest_execute2_wrappers);
        if(target)
            native = target;
    }
    return native ? native : codec62_find_guest_callback(callback, guest);
}

static void codec62_capture_guest_callbacks_locked(codec62_shadow_t* shadow)
{
    for(int i = 0; i < CODEC62_CALLBACK_COUNT; ++i) {
        void* guest = codec62_read_callback(shadow->avctx, i);
        if(guest == shadow->guest[i])
            continue;
        shadow->guest[i] = guest;
        shadow->native[i] = codec62_guest_to_native_callback(i, guest);
    }
}

static void codec62_capture_native_callbacks_locked(codec62_shadow_t* shadow)
{
    for(int i = 0; i < CODEC62_CALLBACK_COUNT; ++i) {
        void* value = codec62_read_callback(shadow->avctx, i);
        if(value == shadow->installed[i])
            continue;

        void* native = GetNativeFnc((uintptr_t)value);
        if(native && i == CODEC62_EXECUTE) {
            void* target = codec62_unwrap_reverse_bridge(native,
                codec62_native_execute, codec62_guest_execute_wrappers);
            if(target)
                native = target;
        } else if(native && i == CODEC62_EXECUTE2) {
            void* target = codec62_unwrap_reverse_bridge(native,
                codec62_native_execute2, codec62_guest_execute2_wrappers);
            if(target)
                native = target;
        }

        if(native && native != value) {
            shadow->native[i] = native;
            shadow->guest[i] = value;
        } else if(native) {
            shadow->native[i] = native;
            shadow->guest[i] = codec62_bridge_native_callback(i, native);
        } else {
            shadow->guest[i] = value;
            shadow->native[i] = codec62_find_guest_callback(i, value);
        }
    }
}

static void codec62_install_native_callbacks_locked(codec62_shadow_t* shadow)
{
    for(int i = 0; i < CODEC62_CALLBACK_COUNT; ++i) {
        codec62_write_callback(shadow->avctx, i, shadow->native[i]);
        shadow->installed[i] = shadow->native[i];
    }
}

static void codec62_install_guest_callbacks_locked(codec62_shadow_t* shadow)
{
    for(int i = 0; i < CODEC62_CALLBACK_COUNT; ++i)
        codec62_write_callback(shadow->avctx, i, shadow->guest[i]);
}

static void codec62_register_context(void* avctx)
{
    if(!avctx)
        return;
    codec62_shadow_t* shadow = (codec62_shadow_t*)calloc(1, sizeof(*shadow));
    if(!shadow) {
        printf_log(LOG_NONE, "Warning, cannot allocate libavcodec62 callback shadow\n");
        return;
    }
    shadow->avctx = avctx;
    for(int i = 0; i < CODEC62_CALLBACK_COUNT; ++i) {
        shadow->native[i] = codec62_read_callback(avctx, i);
        shadow->installed[i] = shadow->native[i];
        shadow->guest[i] = codec62_bridge_native_callback(i, shadow->native[i]);
    }

    pthread_mutex_lock(&codec62_shadow_mutex);
    shadow->next = codec62_shadows;
    codec62_shadows = shadow;
    codec62_install_guest_callbacks_locked(shadow);
    pthread_mutex_unlock(&codec62_shadow_mutex);
}

static void codec62_prepare_context(void* avctx)
{
    if(!avctx)
        return;
    pthread_mutex_lock(&codec62_shadow_mutex);
    codec62_shadow_t* shadow = codec62_find_shadow_locked(avctx);
    if(shadow) {
        if(!shadow->native_depth)
            codec62_capture_guest_callbacks_locked(shadow);
        else if(shadow->callback_depth)
            codec62_capture_native_callbacks_locked(shadow);
        codec62_install_native_callbacks_locked(shadow);
        ++shadow->native_depth;
    }
    pthread_mutex_unlock(&codec62_shadow_mutex);
}

static void codec62_finish_context(void* avctx)
{
    if(!avctx)
        return;
    pthread_mutex_lock(&codec62_shadow_mutex);
    codec62_shadow_t* shadow = codec62_find_shadow_locked(avctx);
    if(shadow) {
        codec62_capture_native_callbacks_locked(shadow);
        if(shadow->native_depth)
            --shadow->native_depth;
        if(shadow->native_depth)
            codec62_install_native_callbacks_locked(shadow);
        else
            codec62_install_guest_callbacks_locked(shadow);
    }
    pthread_mutex_unlock(&codec62_shadow_mutex);
}

static uintptr_t codec62_guest_callback_enter_slot(void* avctx, int callback,
    uintptr_t fallback)
{
    uintptr_t guest = fallback;
    if(!avctx)
        return guest;
    pthread_mutex_lock(&codec62_shadow_mutex);
    codec62_shadow_t* shadow = codec62_find_shadow_locked(avctx);
    if(shadow) {
        ++shadow->callback_depth;
        guest = (uintptr_t)shadow->guest[callback];
    }
    pthread_mutex_unlock(&codec62_shadow_mutex);
    return guest;
}

static void codec62_guest_callback_enter(void* avctx)
{
    if(!avctx)
        return;
    pthread_mutex_lock(&codec62_shadow_mutex);
    codec62_shadow_t* shadow = codec62_find_shadow_locked(avctx);
    if(shadow)
        ++shadow->callback_depth;
    pthread_mutex_unlock(&codec62_shadow_mutex);
}

static void codec62_sanitize_untracked_context(void* avctx)
{
    for(int i = 0; i < CODEC62_CALLBACK_COUNT; ++i) {
        void* value = codec62_read_callback(avctx, i);
        if(!value)
            continue;
        void* native = GetNativeFnc((uintptr_t)value);
        if(native) {
            if(native != value)
                codec62_write_callback(avctx, i, native);
        } else {
            codec62_write_callback(avctx, i,
                codec62_find_guest_callback(i, value));
        }
    }
}

static void codec62_guest_callback_leave(void* avctx)
{
    if(!avctx)
        return;
    pthread_mutex_lock(&codec62_shadow_mutex);
    codec62_shadow_t* shadow = codec62_find_shadow_locked(avctx);
    if(shadow) {
        codec62_capture_native_callbacks_locked(shadow);
        if(shadow->callback_depth)
            --shadow->callback_depth;
        codec62_install_native_callbacks_locked(shadow);
    }
    pthread_mutex_unlock(&codec62_shadow_mutex);
    if(!shadow)
        codec62_sanitize_untracked_context(avctx);
}

static void codec62_forget_context(void* avctx)
{
    if(!avctx)
        return;
    pthread_mutex_lock(&codec62_shadow_mutex);
    codec62_shadow_t** link = &codec62_shadows;
    while(*link && (*link)->avctx != avctx)
        link = &(*link)->next;
    codec62_shadow_t* shadow = *link;
    if(shadow)
        *link = shadow->next;
    pthread_mutex_unlock(&codec62_shadow_mutex);
    free(shadow);
}

EXPORT void* my62_avcodec_dct_alloc(x64emu_t* emu)
{
    (void)emu;
    void* dct = my->avcodec_dct_alloc();
    codec62_dct_restore(dct);
    return dct;
}

EXPORT int my62_avcodec_dct_init(x64emu_t* emu, void* dct)
{
    (void)emu;
    codec62_dct_prepare(dct);
    int ret = my->avcodec_dct_init(dct);
    codec62_dct_restore(dct);
    return ret;
}

EXPORT int my62_av_vdpau_bind_context(x64emu_t* emu, void* avctx,
    unsigned int device,
    void* get_proc_address, unsigned int flags)
{
    (void)emu;
    codec62_prepare_context(avctx);
    int ret = my->av_vdpau_bind_context(avctx, device,
        codec62_find_vdp_get_proc_Fct(get_proc_address), flags);
    codec62_finish_context(avctx);
    return ret;
}

EXPORT void* my62_avcodec_alloc_context3(x64emu_t* emu, void* codec)
{
    (void)emu;
    void* avctx = my->avcodec_alloc_context3(codec);
    codec62_register_context(avctx);
    return avctx;
}

EXPORT int my62_avcodec_open2(x64emu_t* emu, void* avctx, void* codec, void* options)
{
    (void)emu;
    codec62_prepare_context(avctx);
    int ret = my->avcodec_open2(avctx, codec, options);
    codec62_finish_context(avctx);
    return ret;
}

EXPORT int my62_avcodec_send_packet(x64emu_t* emu, void* avctx, void* packet)
{
    (void)emu;
    codec62_prepare_context(avctx);
    int ret = my->avcodec_send_packet(avctx, packet);
    codec62_finish_context(avctx);
    return ret;
}

EXPORT int my62_avcodec_receive_frame(x64emu_t* emu, void* avctx, void* frame)
{
    (void)emu;
    codec62_prepare_context(avctx);
    int ret = my->avcodec_receive_frame(avctx, frame);
    codec62_finish_context(avctx);
    return ret;
}

EXPORT int my62_avcodec_receive_frame_flags(x64emu_t* emu, void* avctx,
    void* frame, unsigned int flags)
{
    (void)emu;
    codec62_prepare_context(avctx);
    int ret = my->avcodec_receive_frame_flags(avctx, frame, flags);
    codec62_finish_context(avctx);
    return ret;
}

EXPORT void my62_avcodec_flush_buffers(x64emu_t* emu, void* avctx)
{
    (void)emu;
    codec62_prepare_context(avctx);
    my->avcodec_flush_buffers(avctx);
    codec62_finish_context(avctx);
}

EXPORT void my62_avcodec_free_context(x64emu_t* emu, void* context)
{
    (void)emu;
    void* avctx = context ? *(void**)context : NULL;
    codec62_prepare_context(avctx);
    my->avcodec_free_context(context);
    codec62_forget_context(avctx);
}

EXPORT int my62_avcodec_send_frame(x64emu_t* emu, void* avctx, void* frame)
{
    (void)emu;
    codec62_prepare_context(avctx);
    int ret = my->avcodec_send_frame(avctx, frame);
    codec62_finish_context(avctx);
    return ret;
}

EXPORT int my62_avcodec_receive_packet(x64emu_t* emu, void* avctx, void* packet)
{
    (void)emu;
    codec62_prepare_context(avctx);
    int ret = my->avcodec_receive_packet(avctx, packet);
    codec62_finish_context(avctx);
    return ret;
}

EXPORT int my62_avcodec_decode_subtitle2(x64emu_t* emu, void* avctx,
    void* subtitle, void* got_subtitle, void* packet)
{
    (void)emu;
    codec62_prepare_context(avctx);
    int ret = my->avcodec_decode_subtitle2(avctx, subtitle, got_subtitle, packet);
    codec62_finish_context(avctx);
    return ret;
}

EXPORT int my62_avcodec_encode_subtitle(x64emu_t* emu, void* avctx,
    void* buffer, int buffer_size, void* subtitle)
{
    (void)emu;
    codec62_prepare_context(avctx);
    int ret = my->avcodec_encode_subtitle(avctx, buffer, buffer_size, subtitle);
    codec62_finish_context(avctx);
    return ret;
}

EXPORT int my62_avcodec_default_execute(x64emu_t* emu, void* avctx, void* func,
    void* arg, void* ret, int count, int size)
{
    (void)emu;
    codec62_prepare_context(avctx);
    int result = my->avcodec_default_execute(avctx, find_execute_Fct(func),
        arg, ret, count, size);
    codec62_finish_context(avctx);
    return result;
}

EXPORT int my62_avcodec_default_execute2(x64emu_t* emu, void* avctx, void* func,
    void* arg, void* ret, int count)
{
    (void)emu;
    codec62_prepare_context(avctx);
    int result = my->avcodec_default_execute2(avctx, find_execute2_Fct(func),
        arg, ret, count);
    codec62_finish_context(avctx);
    return result;
}

#define PRE_INIT \
    if(wrapped_ffmpeg8_preinit()) return -2;

#include "wrappedlib_init.h"

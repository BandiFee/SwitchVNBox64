#include <stdio.h>
#include <stdlib.h>
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

const char* libavformat62Name = "libavformat.so.62";

#define LIBNAME libavformat62
#define ALTMY my62_

#define ADDED_FUNCTIONS()

#include "generated/wrappedlibavformat62types.h"

#include "wrappercallback.h"

#define SUPER() \
GO(0)           \
GO(1)           \
GO(2)           \
GO(3)           \
GO(4)           \
GO(5)           \
GO(6)           \
GO(7)

// AVIOContext read callback
#define GO(A)                                                               \
static uintptr_t my_read_packet_fct_##A = 0;                                \
static int my_read_packet_##A(void* opaque, void* buffer, int size)         \
{                                                                           \
    return (int)RunFunctionFmt(my_read_packet_fct_##A, "ppi", opaque, buffer, size); \
}
SUPER()
#undef GO

static void* find_read_packet_Fct(void* fct)
{
    if(!fct)
        return NULL;
    void* native = GetNativeFnc((uintptr_t)fct);
    if(native)
        return native;
#define GO(A) if(my_read_packet_fct_##A == (uintptr_t)fct) return my_read_packet_##A;
    SUPER()
#undef GO
#define GO(A) if(my_read_packet_fct_##A == 0) { my_read_packet_fct_##A = (uintptr_t)fct; return my_read_packet_##A; }
    SUPER()
#undef GO
    printf_log(LOG_NONE, "Warning, no more slot for libavformat62 read_packet callback\n");
    return NULL;
}

// AVIOContext write callback
#define GO(A)                                                               \
static uintptr_t my_write_packet_fct_##A = 0;                               \
static int my_write_packet_##A(void* opaque, void* buffer, int size)        \
{                                                                           \
    return (int)RunFunctionFmt(my_write_packet_fct_##A, "ppi", opaque, buffer, size); \
}
SUPER()
#undef GO

static void* find_write_packet_Fct(void* fct)
{
    if(!fct)
        return NULL;
    void* native = GetNativeFnc((uintptr_t)fct);
    if(native)
        return native;
#define GO(A) if(my_write_packet_fct_##A == (uintptr_t)fct) return my_write_packet_##A;
    SUPER()
#undef GO
#define GO(A) if(my_write_packet_fct_##A == 0) { my_write_packet_fct_##A = (uintptr_t)fct; return my_write_packet_##A; }
    SUPER()
#undef GO
    printf_log(LOG_NONE, "Warning, no more slot for libavformat62 write_packet callback\n");
    return NULL;
}

// AVIOContext seek callback
#define GO(A)                                                               \
static uintptr_t my_seek_fct_##A = 0;                                       \
static int64_t my_seek_##A(void* opaque, int64_t offset, int whence)        \
{                                                                           \
    return (int64_t)RunFunctionFmt(my_seek_fct_##A, "pIi", opaque, offset, whence); \
}
SUPER()
#undef GO

static void* find_seek_Fct(void* fct)
{
    if(!fct)
        return NULL;
    void* native = GetNativeFnc((uintptr_t)fct);
    if(native)
        return native;
#define GO(A) if(my_seek_fct_##A == (uintptr_t)fct) return my_seek_##A;
    SUPER()
#undef GO
#define GO(A) if(my_seek_fct_##A == 0) { my_seek_fct_##A = (uintptr_t)fct; return my_seek_##A; }
    SUPER()
#undef GO
    printf_log(LOG_NONE, "Warning, no more slot for libavformat62 seek callback\n");
    return NULL;
}

// AVIOInterruptCB callback
#define GO(A)                                                               \
static uintptr_t my_interrupt_fct_##A = 0;                                  \
static int my_interrupt_##A(void* opaque)                                   \
{                                                                           \
    return (int)RunFunctionFmt(my_interrupt_fct_##A, "p", opaque);          \
}
SUPER()
#undef GO

static void* find_interrupt_Fct(void* fct)
{
    if(!fct)
        return NULL;
    void* native = GetNativeFnc((uintptr_t)fct);
    if(native)
        return native;
#define GO(A) if(my_interrupt_fct_##A == (uintptr_t)fct) return my_interrupt_##A;
    SUPER()
#undef GO
#define GO(A) if(my_interrupt_fct_##A == 0) { my_interrupt_fct_##A = (uintptr_t)fct; return my_interrupt_##A; }
    SUPER()
#undef GO
    printf_log(LOG_NONE, "Warning, no more slot for libavformat62 interrupt callback\n");
    return NULL;
}

// AVIOContext checksum callback
#define GO(A)                                                               \
static uintptr_t my_update_checksum_fct_##A = 0;                            \
static unsigned long my_update_checksum_##A(unsigned long checksum,         \
    const void* buffer, unsigned int size)                                  \
{                                                                           \
    return (unsigned long)RunFunctionFmt(my_update_checksum_fct_##A,        \
        "Lpu", checksum, buffer, size);                                     \
}
SUPER()
#undef GO

static void* find_update_checksum_Fct(void* fct)
{
    if(!fct)
        return NULL;
    void* native = GetNativeFnc((uintptr_t)fct);
    if(native)
        return native;
#define GO(A) if(my_update_checksum_fct_##A == (uintptr_t)fct) return my_update_checksum_##A;
    SUPER()
#undef GO
#define GO(A) if(my_update_checksum_fct_##A == 0) { my_update_checksum_fct_##A = (uintptr_t)fct; return my_update_checksum_##A; }
    SUPER()
#undef GO
    printf_log(LOG_NONE, "Warning, no more slot for libavformat62 update_checksum callback\n");
    return NULL;
}

// AVIOContext read_pause callback
#define GO(A)                                                               \
static uintptr_t my_read_pause_fct_##A = 0;                                 \
static int my_read_pause_##A(void* opaque, int pause)                       \
{                                                                           \
    return (int)RunFunctionFmt(my_read_pause_fct_##A, "pi", opaque, pause); \
}
SUPER()
#undef GO

static void* find_read_pause_Fct(void* fct)
{
    if(!fct)
        return NULL;
    void* native = GetNativeFnc((uintptr_t)fct);
    if(native)
        return native;
#define GO(A) if(my_read_pause_fct_##A == (uintptr_t)fct) return my_read_pause_##A;
    SUPER()
#undef GO
#define GO(A) if(my_read_pause_fct_##A == 0) { my_read_pause_fct_##A = (uintptr_t)fct; return my_read_pause_##A; }
    SUPER()
#undef GO
    printf_log(LOG_NONE, "Warning, no more slot for libavformat62 read_pause callback\n");
    return NULL;
}

// AVIOContext read_seek callback
#define GO(A)                                                               \
static uintptr_t my_read_seek_fct_##A = 0;                                  \
static int64_t my_read_seek_##A(void* opaque, int stream_index,             \
    int64_t timestamp, int flags)                                           \
{                                                                           \
    return (int64_t)RunFunctionFmt(my_read_seek_fct_##A, "piIi", opaque,    \
        stream_index, timestamp, flags);                                    \
}
SUPER()
#undef GO

static void* find_read_seek_Fct(void* fct)
{
    if(!fct)
        return NULL;
    void* native = GetNativeFnc((uintptr_t)fct);
    if(native)
        return native;
#define GO(A) if(my_read_seek_fct_##A == (uintptr_t)fct) return my_read_seek_##A;
    SUPER()
#undef GO
#define GO(A) if(my_read_seek_fct_##A == 0) { my_read_seek_fct_##A = (uintptr_t)fct; return my_read_seek_##A; }
    SUPER()
#undef GO
    printf_log(LOG_NONE, "Warning, no more slot for libavformat62 read_seek callback\n");
    return NULL;
}

// AVIOContext write_data_type callback
#define GO(A)                                                               \
static uintptr_t my_write_data_type_fct_##A = 0;                            \
static int my_write_data_type_##A(void* opaque, const void* buffer,         \
    int size, int type, int64_t time)                                       \
{                                                                           \
    return (int)RunFunctionFmt(my_write_data_type_fct_##A, "ppiiI", opaque, \
        buffer, size, type, time);                                          \
}
SUPER()
#undef GO

static void* find_write_data_type_Fct(void* fct)
{
    if(!fct)
        return NULL;
    void* native = GetNativeFnc((uintptr_t)fct);
    if(native)
        return native;
#define GO(A) if(my_write_data_type_fct_##A == (uintptr_t)fct) return my_write_data_type_##A;
    SUPER()
#undef GO
#define GO(A) if(my_write_data_type_fct_##A == 0) { my_write_data_type_fct_##A = (uintptr_t)fct; return my_write_data_type_##A; }
    SUPER()
#undef GO
    printf_log(LOG_NONE, "Warning, no more slot for libavformat62 write_data_type callback\n");
    return NULL;
}

// AVFormatContext control_message_cb callback
static void avformat_prepare(void* context);
static void avformat_restore(void* context);

#define GO(A)                                                               \
static uintptr_t my_control_message_fct_##A = 0;                            \
static int my_control_message_##A(void* context, int type, void* data,      \
    size_t data_size)                                                       \
{                                                                           \
    avformat_restore(context);                                              \
    int ret = (int)RunFunctionFmt(my_control_message_fct_##A, "pipL",       \
        context, type, data, data_size);                                    \
    avformat_prepare(context);                                              \
    return ret;                                                             \
}
SUPER()
#undef GO

static void* find_control_message_Fct(void* fct)
{
    if(!fct)
        return NULL;
    void* native = GetNativeFnc((uintptr_t)fct);
    if(native)
        return native;
#define GO(A) if(my_control_message_fct_##A == (uintptr_t)fct) return my_control_message_##A;
    SUPER()
#undef GO
#define GO(A) if(my_control_message_fct_##A == 0) { my_control_message_fct_##A = (uintptr_t)fct; return my_control_message_##A; }
    SUPER()
#undef GO
    printf_log(LOG_NONE, "Warning, no more slot for libavformat62 control_message callback\n");
    return NULL;
}

static void avio_prepare(void* context);
static void avio_restore(void* context);
static void avio_drop(void* context);

// AVFormatContext io_open callback
#define GO(A)                                                               \
static uintptr_t my_io_open_fct_##A = 0;                                    \
static int my_io_open_##A(void* context, void* avio, const char* url,       \
    int flags, void* options)                                               \
{                                                                           \
    avformat_restore(context);                                              \
    int ret = (int)RunFunctionFmt(my_io_open_fct_##A, "pppip", context,     \
        avio, url, flags, options);                                         \
    avformat_prepare(context);                                              \
    if(ret >= 0 && avio)                                                    \
        avio_prepare(*(void**)avio);                                        \
    return ret;                                                             \
}
SUPER()
#undef GO

static void* find_io_open_Fct(void* fct)
{
    if(!fct)
        return NULL;
    void* native = GetNativeFnc((uintptr_t)fct);
    if(native)
        return native;
#define GO(A) if(my_io_open_fct_##A == (uintptr_t)fct) return my_io_open_##A;
    SUPER()
#undef GO
#define GO(A) if(my_io_open_fct_##A == 0) { my_io_open_fct_##A = (uintptr_t)fct; return my_io_open_##A; }
    SUPER()
#undef GO
    printf_log(LOG_NONE, "Warning, no more slot for libavformat62 io_open callback\n");
    return NULL;
}

// AVFormatContext io_close2 callback
#define GO(A)                                                               \
static uintptr_t my_io_close2_fct_##A = 0;                                  \
static int my_io_close2_##A(void* context, void* avio)                      \
{                                                                           \
    avformat_restore(context);                                              \
    avio_restore(avio);                                                     \
    int ret = (int)RunFunctionFmt(my_io_close2_fct_##A, "pp", context, avio); \
    avio_drop(avio);                                                        \
    avformat_prepare(context);                                              \
    return ret;                                                             \
}
SUPER()
#undef GO

static void* find_io_close2_Fct(void* fct)
{
    if(!fct)
        return NULL;
    void* native = GetNativeFnc((uintptr_t)fct);
    if(native)
        return native;
#define GO(A) if(my_io_close2_fct_##A == (uintptr_t)fct) return my_io_close2_##A;
    SUPER()
#undef GO
#define GO(A) if(my_io_close2_fct_##A == 0) { my_io_close2_fct_##A = (uintptr_t)fct; return my_io_close2_##A; }
    SUPER()
#undef GO
    printf_log(LOG_NONE, "Warning, no more slot for libavformat62 io_close2 callback\n");
    return NULL;
}

#undef SUPER

static int native_control_message_proxy(void* context, int type, void* data,
    size_t data_size);
static int native_io_open_proxy(void* context, void* avio, const char* url,
    int flags, void* options);
static int native_io_close2_proxy(void* context, void* avio);

#define CHECK_REVERSE_CALLBACK(NAME)                                        \
    if(fct == (void*)my_##NAME##_0) return (void*)my_##NAME##_fct_0;       \
    if(fct == (void*)my_##NAME##_1) return (void*)my_##NAME##_fct_1;       \
    if(fct == (void*)my_##NAME##_2) return (void*)my_##NAME##_fct_2;       \
    if(fct == (void*)my_##NAME##_3) return (void*)my_##NAME##_fct_3;       \
    if(fct == (void*)my_##NAME##_4) return (void*)my_##NAME##_fct_4;       \
    if(fct == (void*)my_##NAME##_5) return (void*)my_##NAME##_fct_5;       \
    if(fct == (void*)my_##NAME##_6) return (void*)my_##NAME##_fct_6;       \
    if(fct == (void*)my_##NAME##_7) return (void*)my_##NAME##_fct_7;

#define REVERSE_CALLBACK(NAME, SIGNATURE, LABEL, TARGET)                    \
static void* reverse_##NAME##_Fct(void* fct)                                \
{                                                                           \
    if(!fct)                                                                \
        return NULL;                                                        \
    CHECK_REVERSE_CALLBACK(NAME)                                            \
    return (void*)AddCheckBridge(my_lib->w.bridge, SIGNATURE, (void*)(TARGET), 0, LABEL); \
}

REVERSE_CALLBACK(read_packet, iFppi, "avformat62_read_packet", fct)
REVERSE_CALLBACK(write_packet, iFppi, "avformat62_write_packet", fct)
REVERSE_CALLBACK(seek, IFpIi, "avformat62_seek", fct)
REVERSE_CALLBACK(interrupt, iFp, "avformat62_interrupt", fct)
REVERSE_CALLBACK(update_checksum, LFLpu, "avformat62_update_checksum", fct)
REVERSE_CALLBACK(read_pause, iFpi, "avformat62_read_pause", fct)
REVERSE_CALLBACK(read_seek, IFpiIi, "avformat62_read_seek", fct)
REVERSE_CALLBACK(control_message, iFpipL, "avformat62_control_message",
    native_control_message_proxy)
REVERSE_CALLBACK(io_open, iFpppip, "avformat62_io_open", native_io_open_proxy)
REVERSE_CALLBACK(io_close2, iFpp, "avformat62_io_close2", native_io_close2_proxy)

#undef REVERSE_CALLBACK
#undef CHECK_REVERSE_CALLBACK

static void* reverse_write_data_type_Fct(void* fct)
{
    if(!fct)
        return NULL;
#define SUPER() \
GO(0)           \
GO(1)           \
GO(2)           \
GO(3)           \
GO(4)           \
GO(5)           \
GO(6)           \
GO(7)
#define GO(A) if(fct == (void*)my_write_data_type_##A) return (void*)my_write_data_type_fct_##A;
    SUPER()
#undef GO
#undef SUPER
    return (void*)AddCheckBridge(my_lib->w.bridge, iFppiiI, fct, 0,
        "avformat62_write_data_type");
}

enum {
    AVIO_READ_PACKET_OFFSET       = 48,
    AVIO_WRITE_PACKET_OFFSET      = 56,
    AVIO_SEEK_OFFSET              = 64,
    AVIO_UPDATE_CHECKSUM_OFFSET   = 120,
    AVIO_READ_PAUSE_OFFSET        = 128,
    AVIO_READ_SEEK_OFFSET         = 136,
    AVIO_WRITE_DATA_TYPE_OFFSET   = 168,
    AVFORMAT_PB_OFFSET            = 32,
    AVFORMAT_FLAGS_OFFSET         = 128,
    AVFORMAT_INTERRUPT_OFFSET     = 216,
    AVFORMAT_CONTROL_OFFSET       = 424,
    AVFORMAT_IO_OPEN_OFFSET       = 448,
    AVFORMAT_IO_CLOSE2_OFFSET     = 456,
};

typedef void* (*callback_converter_t)(void*);

static const size_t avio_callback_offsets[] = {
    AVIO_READ_PACKET_OFFSET,
    AVIO_WRITE_PACKET_OFFSET,
    AVIO_SEEK_OFFSET,
    AVIO_UPDATE_CHECKSUM_OFFSET,
    AVIO_READ_PAUSE_OFFSET,
    AVIO_READ_SEEK_OFFSET,
    AVIO_WRITE_DATA_TYPE_OFFSET,
};

static callback_converter_t const avio_find_callbacks[] = {
    find_read_packet_Fct,
    find_write_packet_Fct,
    find_seek_Fct,
    find_update_checksum_Fct,
    find_read_pause_Fct,
    find_read_seek_Fct,
    find_write_data_type_Fct,
};

static callback_converter_t const avio_reverse_callbacks[] = {
    reverse_read_packet_Fct,
    reverse_write_packet_Fct,
    reverse_seek_Fct,
    reverse_update_checksum_Fct,
    reverse_read_pause_Fct,
    reverse_read_seek_Fct,
    reverse_write_data_type_Fct,
};

static const size_t avformat_callback_offsets[] = {
    AVFORMAT_INTERRUPT_OFFSET,
    AVFORMAT_CONTROL_OFFSET,
    AVFORMAT_IO_OPEN_OFFSET,
    AVFORMAT_IO_CLOSE2_OFFSET,
};

static callback_converter_t const avformat_find_callbacks[] = {
    find_interrupt_Fct,
    find_control_message_Fct,
    find_io_open_Fct,
    find_io_close2_Fct,
};

static callback_converter_t const avformat_reverse_callbacks[] = {
    reverse_interrupt_Fct,
    reverse_control_message_Fct,
    reverse_io_open_Fct,
    reverse_io_close2_Fct,
};

typedef struct callback_shadow_s {
    void* object;
    unsigned int active;
    unsigned int callback_count;
    const size_t* offsets;
    callback_converter_t const* find_callbacks;
    callback_converter_t const* reverse_callbacks;
    void* guest[7];
    void* native[7];
    struct callback_shadow_s* next;
} callback_shadow_t;

static pthread_mutex_t callback_shadow_mutex = PTHREAD_MUTEX_INITIALIZER;
static callback_shadow_t* avio_shadows;
static callback_shadow_t* avformat_shadows;

static inline void** callback_field(void* object, size_t offset)
{
    return (void**)((uintptr_t)object + offset);
}

static callback_shadow_t* find_shadow(callback_shadow_t* head, void* object)
{
    while(head && head->object != object)
        head = head->next;
    return head;
}

static callback_shadow_t* new_shadow(callback_shadow_t** head, void* object,
    const size_t* offsets, callback_converter_t const* find_callbacks,
    callback_converter_t const* reverse_callbacks, unsigned int callback_count,
    int from_native)
{
    callback_shadow_t* shadow = (callback_shadow_t*)calloc(1, sizeof(*shadow));
    if(!shadow)
        return NULL;

    shadow->object = object;
    shadow->offsets = offsets;
    shadow->find_callbacks = find_callbacks;
    shadow->reverse_callbacks = reverse_callbacks;
    shadow->callback_count = callback_count;
    shadow->next = *head;
    *head = shadow;

    for(unsigned int i = 0; i < callback_count; ++i) {
        void* callback = *callback_field(object, offsets[i]);
        if(from_native) {
            shadow->native[i] = callback;
            shadow->guest[i] = reverse_callbacks[i](callback);
            *callback_field(object, offsets[i]) = shadow->guest[i];
        } else {
            shadow->guest[i] = callback;
            shadow->native[i] = find_callbacks[i](callback);
        }
    }
    return shadow;
}

static void track_native_shadow(callback_shadow_t** head, void* object,
    const size_t* offsets, callback_converter_t const* find_callbacks,
    callback_converter_t const* reverse_callbacks, unsigned int callback_count)
{
    if(!object)
        return;
    pthread_mutex_lock(&callback_shadow_mutex);
    if(!find_shadow(*head, object))
        new_shadow(head, object, offsets, find_callbacks, reverse_callbacks,
            callback_count, 1);
    pthread_mutex_unlock(&callback_shadow_mutex);
}

static void prepare_shadow(callback_shadow_t** head, void* object,
    const size_t* offsets, callback_converter_t const* find_callbacks,
    callback_converter_t const* reverse_callbacks, unsigned int callback_count)
{
    if(!object)
        return;

    pthread_mutex_lock(&callback_shadow_mutex);
    callback_shadow_t* shadow = find_shadow(*head, object);
    if(!shadow)
        shadow = new_shadow(head, object, offsets, find_callbacks,
            reverse_callbacks, callback_count, 0);
    if(shadow && shadow->active++ == 0) {
        for(unsigned int i = 0; i < callback_count; ++i) {
            void* callback = *callback_field(object, offsets[i]);
            if(callback != shadow->guest[i]) {
                shadow->guest[i] = callback;
                shadow->native[i] = find_callbacks[i](callback);
            }
            *callback_field(object, offsets[i]) = shadow->native[i];
        }
    }
    pthread_mutex_unlock(&callback_shadow_mutex);
}

static void restore_shadow(callback_shadow_t** head, void* object)
{
    if(!object)
        return;

    pthread_mutex_lock(&callback_shadow_mutex);
    callback_shadow_t* shadow = find_shadow(*head, object);
    if(shadow && shadow->active && --shadow->active == 0) {
        for(unsigned int i = 0; i < shadow->callback_count; ++i) {
            void* callback = *callback_field(object, shadow->offsets[i]);
            if(callback != shadow->native[i]) {
                shadow->native[i] = callback;
                shadow->guest[i] = shadow->reverse_callbacks[i](callback);
            }
            *callback_field(object, shadow->offsets[i]) = shadow->guest[i];
        }
    }
    pthread_mutex_unlock(&callback_shadow_mutex);
}

static void drop_shadow(callback_shadow_t** head, void* object)
{
    if(!object)
        return;

    pthread_mutex_lock(&callback_shadow_mutex);
    callback_shadow_t** current = head;
    while(*current && (*current)->object != object)
        current = &(*current)->next;
    if(*current) {
        callback_shadow_t* old = *current;
        *current = old->next;
        free(old);
    }
    pthread_mutex_unlock(&callback_shadow_mutex);
}

static void avio_track_native(void* context)
{
    track_native_shadow(&avio_shadows, context, avio_callback_offsets,
        avio_find_callbacks, avio_reverse_callbacks,
        sizeof(avio_callback_offsets) / sizeof(avio_callback_offsets[0]));
}

static void avio_prepare(void* context)
{
    prepare_shadow(&avio_shadows, context, avio_callback_offsets,
        avio_find_callbacks, avio_reverse_callbacks,
        sizeof(avio_callback_offsets) / sizeof(avio_callback_offsets[0]));
}

static void avio_restore(void* context)
{
    restore_shadow(&avio_shadows, context);
}

static void avio_drop(void* context)
{
    drop_shadow(&avio_shadows, context);
}

static void avformat_track_native(void* context)
{
    track_native_shadow(&avformat_shadows, context, avformat_callback_offsets,
        avformat_find_callbacks, avformat_reverse_callbacks,
        sizeof(avformat_callback_offsets) / sizeof(avformat_callback_offsets[0]));
}

static void avformat_track_native_deep(void* context)
{
    if(!context)
        return;
    avformat_track_native(context);
    avio_track_native(*callback_field(context, AVFORMAT_PB_OFFSET));
}

static void avformat_prepare(void* context)
{
    prepare_shadow(&avformat_shadows, context, avformat_callback_offsets,
        avformat_find_callbacks, avformat_reverse_callbacks,
        sizeof(avformat_callback_offsets) / sizeof(avformat_callback_offsets[0]));
}

static void avformat_restore(void* context)
{
    restore_shadow(&avformat_shadows, context);
}

static void avformat_drop(void* context)
{
    drop_shadow(&avformat_shadows, context);
}

typedef struct avformat_scope_s {
    void* context;
    void* avio;
} avformat_scope_t;

static avformat_scope_t avformat_scope_begin(void* context)
{
    avformat_scope_t scope = {context, NULL};
    if(context) {
        scope.avio = *callback_field(context, AVFORMAT_PB_OFFSET);
        avio_prepare(scope.avio);
        avformat_prepare(context);
    }
    return scope;
}

static void avformat_scope_end(avformat_scope_t scope)
{
    if(!scope.context)
        return;
    void* current_avio = *callback_field(scope.context, AVFORMAT_PB_OFFSET);
    avformat_restore(scope.context);
    avio_restore(scope.avio);
    if(current_avio != scope.avio)
        avio_restore(current_avio);
}

static void* avformat_native_callback(void* context, unsigned int index)
{
    void* callback = NULL;
    pthread_mutex_lock(&callback_shadow_mutex);
    callback_shadow_t* shadow = find_shadow(avformat_shadows, context);
    if(shadow && index < shadow->callback_count)
        callback = shadow->native[index];
    pthread_mutex_unlock(&callback_shadow_mutex);
    return callback;
}

/*
 * These proxies are exposed to the guest for native callbacks stored in an
 * AVFormatContext.  Calling such a field directly from x86 must still switch
 * the context (and any AVIOContext argument) to its native callback view.
 */
static int native_control_message_proxy(void* context, int type, void* data,
    size_t data_size)
{
    void* callback = avformat_native_callback(context, 1);
    if(!callback || callback == (void*)native_control_message_proxy)
        return -1;
    avformat_prepare(context);
    int ret = ((int(*)(void*, int, void*, size_t))callback)(
        context, type, data, data_size);
    avformat_restore(context);
    return ret;
}

static int native_io_open_proxy(void* context, void* avio, const char* url,
    int flags, void* options)
{
    void* callback = avformat_native_callback(context, 2);
    if(!callback || callback == (void*)native_io_open_proxy)
        return -1;
    avformat_prepare(context);
    int ret = ((int(*)(void*, void*, const char*, int, void*))callback)(
        context, avio, url, flags, options);
    avformat_restore(context);
    if(ret >= 0 && avio && *(void**)avio)
        avio_track_native(*(void**)avio);
    return ret;
}

static int native_io_close2_proxy(void* context, void* avio)
{
    void* callback = avformat_native_callback(context, 3);
    if(!callback || callback == (void*)native_io_close2_proxy)
        return -1;
    avformat_prepare(context);
    avio_prepare(avio);
    int ret = ((int(*)(void*, void*))callback)(context, avio);
    avio_drop(avio);
    avformat_restore(context);
    return ret;
}

typedef struct avio_interrupt_cb_s {
    void* callback;
    void* opaque;
} avio_interrupt_cb_t;

EXPORT void* my62_avio_alloc_context(x64emu_t* emu, void* buffer, int buffer_size,
    int write_flag, void* opaque, void* read_packet, void* write_packet, void* seek)
{
    (void)emu;
    void* ret = my->avio_alloc_context(buffer, buffer_size, write_flag, opaque,
        find_read_packet_Fct(read_packet), find_write_packet_Fct(write_packet),
        find_seek_Fct(seek));
    avio_track_native(ret);
    return ret;
}

EXPORT int my62_avio_open2(x64emu_t* emu, void* context, void* url, int flags,
    void* interrupt_cb, void* options)
{
    (void)emu;
    int ret;
    if(!interrupt_cb) {
        ret = my->avio_open2(context, url, flags, NULL, options);
    } else {
        const avio_interrupt_cb_t* guest_cb = (const avio_interrupt_cb_t*)interrupt_cb;
        avio_interrupt_cb_t native_cb = {
            .callback = find_interrupt_Fct(guest_cb->callback),
            .opaque = guest_cb->opaque,
        };
        ret = my->avio_open2(context, url, flags, &native_cb, options);
    }
    if(context && *(void**)context)
        avio_track_native(*(void**)context);
    return ret;
}

EXPORT int my62_avio_printf(x64emu_t* emu, void* context, void* fmt, uint64_t* b)
{
    avio_prepare(context);
    myStackAlign(emu, (const char*)fmt, b, emu->scratch, R_EAX, 2);
    PREPARE_VALIST;
    int ret = my->avio_vprintf(context, fmt, VARARGS);
    avio_restore(context);
    return ret;
}

EXPORT int my62_avio_vprintf(x64emu_t* emu, void* context, void* fmt, x64_va_list_t b)
{
    avio_prepare(context);
#ifdef CONVERT_VALIST
    CONVERT_VALIST(b);
#else
    myStackAlignValist(emu, (const char*)fmt, emu->scratch, b);
    PREPARE_VALIST;
#endif
    int ret = my->avio_vprintf(context, fmt, VARARGS);
    avio_restore(context);
    return ret;
}

#define AVIO_WRAP_R1(NAME, RET)                                             \
EXPORT RET my62_##NAME(x64emu_t* emu, void* context)                        \
{                                                                           \
    (void)emu;                                                              \
    avio_prepare(context);                                                  \
    RET ret = my->NAME(context);                                            \
    avio_restore(context);                                                  \
    return ret;                                                             \
}

#define AVIO_WRAP_R2(NAME, RET, T2, A2)                                     \
EXPORT RET my62_##NAME(x64emu_t* emu, void* context, T2 A2)                 \
{                                                                           \
    (void)emu;                                                              \
    avio_prepare(context);                                                  \
    RET ret = my->NAME(context, A2);                                        \
    avio_restore(context);                                                  \
    return ret;                                                             \
}

#define AVIO_WRAP_R3(NAME, RET, T2, A2, T3, A3)                             \
EXPORT RET my62_##NAME(x64emu_t* emu, void* context, T2 A2, T3 A3)         \
{                                                                           \
    (void)emu;                                                              \
    avio_prepare(context);                                                  \
    RET ret = my->NAME(context, A2, A3);                                    \
    avio_restore(context);                                                  \
    return ret;                                                             \
}

#define AVIO_WRAP_R4(NAME, RET, T2, A2, T3, A3, T4, A4)                     \
EXPORT RET my62_##NAME(x64emu_t* emu, void* context, T2 A2, T3 A3, T4 A4)  \
{                                                                           \
    (void)emu;                                                              \
    avio_prepare(context);                                                  \
    RET ret = my->NAME(context, A2, A3, A4);                                \
    avio_restore(context);                                                  \
    return ret;                                                             \
}

#define AVIO_WRAP_V1(NAME)                                                  \
EXPORT void my62_##NAME(x64emu_t* emu, void* context)                       \
{                                                                           \
    (void)emu;                                                              \
    avio_prepare(context);                                                  \
    my->NAME(context);                                                      \
    avio_restore(context);                                                  \
}

#define AVIO_WRAP_V2(NAME, T2, A2)                                          \
EXPORT void my62_##NAME(x64emu_t* emu, void* context, T2 A2)                \
{                                                                           \
    (void)emu;                                                              \
    avio_prepare(context);                                                  \
    my->NAME(context, A2);                                                  \
    avio_restore(context);                                                  \
}

#define AVIO_WRAP_V3(NAME, T2, A2, T3, A3)                                  \
EXPORT void my62_##NAME(x64emu_t* emu, void* context, T2 A2, T3 A3)        \
{                                                                           \
    (void)emu;                                                              \
    avio_prepare(context);                                                  \
    my->NAME(context, A2, A3);                                              \
    avio_restore(context);                                                  \
}

AVIO_WRAP_R3(av_append_packet, int, void*, packet, int, size)
AVIO_WRAP_R3(av_get_packet, int, void*, packet, int, size)
AVIO_WRAP_R1(avio_feof, int)
AVIO_WRAP_V1(avio_flush)
AVIO_WRAP_R2(avio_get_dyn_buf, int, void*, buffer)
AVIO_WRAP_R4(avio_get_str, int, int, max_length, void*, buffer, int, buffer_size)
AVIO_WRAP_R4(avio_get_str16be, int, int, max_length, void*, buffer, int, buffer_size)
AVIO_WRAP_R4(avio_get_str16le, int, int, max_length, void*, buffer, int, buffer_size)
AVIO_WRAP_R1(avio_handshake, int)
AVIO_WRAP_R2(avio_pause, int, int, pause)
AVIO_WRAP_V2(avio_print_string_array, void*, strings)
AVIO_WRAP_R2(avio_put_str, int, void*, string)
AVIO_WRAP_R2(avio_put_str16be, int, void*, string)
AVIO_WRAP_R2(avio_put_str16le, int, void*, string)
AVIO_WRAP_R1(avio_r8, int)
AVIO_WRAP_R1(avio_rb16, unsigned int)
AVIO_WRAP_R1(avio_rb24, unsigned int)
AVIO_WRAP_R1(avio_rb32, unsigned int)
AVIO_WRAP_R1(avio_rb64, uint64_t)
AVIO_WRAP_R3(avio_read, int, void*, buffer, int, size)
AVIO_WRAP_R3(avio_read_partial, int, void*, buffer, int, size)
AVIO_WRAP_R3(avio_read_to_bprint, int, void*, bprint, size_t, max_size)
AVIO_WRAP_R1(avio_rl16, unsigned int)
AVIO_WRAP_R1(avio_rl24, unsigned int)
AVIO_WRAP_R1(avio_rl32, unsigned int)
AVIO_WRAP_R1(avio_rl64, uint64_t)
AVIO_WRAP_R3(avio_seek, int64_t, int64_t, offset, int, whence)
AVIO_WRAP_R4(avio_seek_time, int64_t, int, stream_index, int64_t, timestamp, int, flags)
AVIO_WRAP_R1(avio_size, int64_t)
AVIO_WRAP_R2(avio_skip, int64_t, int64_t, offset)
AVIO_WRAP_V2(avio_w8, int, value)
AVIO_WRAP_V2(avio_wb16, unsigned int, value)
AVIO_WRAP_V2(avio_wb24, unsigned int, value)
AVIO_WRAP_V2(avio_wb32, unsigned int, value)
AVIO_WRAP_V2(avio_wb64, uint64_t, value)
AVIO_WRAP_V2(avio_wl16, unsigned int, value)
AVIO_WRAP_V2(avio_wl24, unsigned int, value)
AVIO_WRAP_V2(avio_wl32, unsigned int, value)
AVIO_WRAP_V2(avio_wl64, uint64_t, value)
AVIO_WRAP_V3(avio_write, void*, buffer, int, size)
AVIO_WRAP_V3(avio_write_marker, int64_t, time, unsigned int, type)

#undef AVIO_WRAP_R1
#undef AVIO_WRAP_R2
#undef AVIO_WRAP_R3
#undef AVIO_WRAP_R4
#undef AVIO_WRAP_V1
#undef AVIO_WRAP_V2
#undef AVIO_WRAP_V3

EXPORT int my62_avio_open(x64emu_t* emu, void* context, void* url, int flags)
{
    (void)emu;
    int ret = my->avio_open(context, url, flags);
    if(context && *(void**)context)
        avio_track_native(*(void**)context);
    return ret;
}

EXPORT int my62_avio_open_dyn_buf(x64emu_t* emu, void* context)
{
    (void)emu;
    int ret = my->avio_open_dyn_buf(context);
    if(context && *(void**)context)
        avio_track_native(*(void**)context);
    return ret;
}

EXPORT int my62_avio_accept(x64emu_t* emu, void* server, void* client)
{
    (void)emu;
    avio_prepare(server);
    int ret = my->avio_accept(server, client);
    avio_restore(server);
    if(ret >= 0 && client && *(void**)client)
        avio_track_native(*(void**)client);
    return ret;
}

EXPORT int my62_avio_close(x64emu_t* emu, void* context)
{
    (void)emu;
    avio_prepare(context);
    int ret = my->avio_close(context);
    avio_drop(context);
    return ret;
}

EXPORT int my62_avio_closep(x64emu_t* emu, void* context)
{
    (void)emu;
    void* old = context ? *(void**)context : NULL;
    avio_prepare(old);
    int ret = my->avio_closep(context);
    avio_drop(old);
    return ret;
}

EXPORT int my62_avio_close_dyn_buf(x64emu_t* emu, void* context, void* buffer)
{
    (void)emu;
    avio_prepare(context);
    int ret = my->avio_close_dyn_buf(context, buffer);
    avio_drop(context);
    return ret;
}

EXPORT void my62_avio_context_free(x64emu_t* emu, void* context)
{
    (void)emu;
    void* old = context ? *(void**)context : NULL;
    avio_prepare(old);
    my->avio_context_free(context);
    avio_drop(old);
}

EXPORT int my62_av_probe_input_buffer(x64emu_t* emu, void* context, void* format,
    void* url, void* log_context, unsigned int offset, unsigned int max_probe_size)
{
    (void)emu;
    avio_prepare(context);
    int ret = my->av_probe_input_buffer(context, format, url, log_context,
        offset, max_probe_size);
    avio_restore(context);
    return ret;
}

EXPORT int my62_av_probe_input_buffer2(x64emu_t* emu, void* context, void* format,
    void* url, void* log_context, unsigned int offset, unsigned int max_probe_size)
{
    (void)emu;
    avio_prepare(context);
    int ret = my->av_probe_input_buffer2(context, format, url, log_context,
        offset, max_probe_size);
    avio_restore(context);
    return ret;
}

EXPORT void* my62_avformat_alloc_context(x64emu_t* emu)
{
    (void)emu;
    void* ret = my->avformat_alloc_context();
    avformat_track_native_deep(ret);
    return ret;
}

EXPORT int my62_avformat_alloc_output_context2(x64emu_t* emu, void* context,
    void* output_format, void* format_name, void* filename)
{
    (void)emu;
    int ret = my->avformat_alloc_output_context2(context, output_format,
        format_name, filename);
    if(context && *(void**)context)
        avformat_track_native_deep(*(void**)context);
    return ret;
}

EXPORT int my62_avformat_open_input(x64emu_t* emu, void* context, void* url,
    void* input_format, void* options)
{
    (void)emu;
    void* old = context ? *(void**)context : NULL;
    void* old_avio = old ? *callback_field(old, AVFORMAT_PB_OFFSET) : NULL;
    int custom_io = old
        ? ((*(int*)((uintptr_t)old + AVFORMAT_FLAGS_OFFSET) & 0x0080) != 0)
        : 0;
    avformat_scope_t scope = avformat_scope_begin(old);
    int ret = my->avformat_open_input(context, url, input_format, options);
    void* current = context ? *(void**)context : NULL;

    if(current == old && current) {
        void* current_avio = *callback_field(current, AVFORMAT_PB_OFFSET);
        if(current_avio && current_avio != old_avio)
            avio_track_native(current_avio);
        avformat_scope_end(scope);
    } else {
        avformat_drop(old);
        if(custom_io)
            avio_restore(old_avio);
        else
            avio_drop(old_avio);
        avformat_track_native_deep(current);
    }
    return ret;
}

EXPORT void my62_avformat_close_input(x64emu_t* emu, void* context)
{
    (void)emu;
    void* old = context ? *(void**)context : NULL;
    void* old_avio = old ? *callback_field(old, AVFORMAT_PB_OFFSET) : NULL;
    int custom_io = old
        ? ((*(int*)((uintptr_t)old + AVFORMAT_FLAGS_OFFSET) & 0x0080) != 0)
        : 0;
    avformat_scope_begin(old);
    my->avformat_close_input(context);
    avformat_drop(old);
    if(custom_io)
        avio_restore(old_avio);
    else
        avio_drop(old_avio);
}

EXPORT void my62_avformat_free_context(x64emu_t* emu, void* context)
{
    (void)emu;
    void* avio = context ? *callback_field(context, AVFORMAT_PB_OFFSET) : NULL;
    avformat_scope_begin(context);
    my->avformat_free_context(context);
    avformat_drop(context);
    // avformat_free_context does not own or free the user-visible AVIOContext.
    avio_restore(avio);
}

#define FORMAT_WRAP_R1(NAME, RET)                                           \
EXPORT RET my62_##NAME(x64emu_t* emu, void* context)                        \
{                                                                           \
    (void)emu;                                                              \
    avformat_scope_t scope = avformat_scope_begin(context);                 \
    RET ret = my->NAME(context);                                            \
    avformat_scope_end(scope);                                              \
    return ret;                                                             \
}

#define FORMAT_WRAP_R2(NAME, RET, T2, A2)                                   \
EXPORT RET my62_##NAME(x64emu_t* emu, void* context, T2 A2)                 \
{                                                                           \
    (void)emu;                                                              \
    avformat_scope_t scope = avformat_scope_begin(context);                 \
    RET ret = my->NAME(context, A2);                                        \
    avformat_scope_end(scope);                                              \
    return ret;                                                             \
}

#define FORMAT_WRAP_R3(NAME, RET, T2, A2, T3, A3)                           \
EXPORT RET my62_##NAME(x64emu_t* emu, void* context, T2 A2, T3 A3)         \
{                                                                           \
    (void)emu;                                                              \
    avformat_scope_t scope = avformat_scope_begin(context);                 \
    RET ret = my->NAME(context, A2, A3);                                    \
    avformat_scope_end(scope);                                              \
    return ret;                                                             \
}

#define FORMAT_WRAP_R4(NAME, RET, T2, A2, T3, A3, T4, A4)                  \
EXPORT RET my62_##NAME(x64emu_t* emu, void* context, T2 A2, T3 A3, T4 A4)  \
{                                                                           \
    (void)emu;                                                              \
    avformat_scope_t scope = avformat_scope_begin(context);                 \
    RET ret = my->NAME(context, A2, A3, A4);                                \
    avformat_scope_end(scope);                                              \
    return ret;                                                             \
}

FORMAT_WRAP_R2(avformat_find_stream_info, int, void*, options)
FORMAT_WRAP_R1(avformat_flush, int)
FORMAT_WRAP_R2(avformat_init_output, int, void*, options)
FORMAT_WRAP_R2(avformat_new_stream, void*, void*, codec)
FORMAT_WRAP_R1(avformat_queue_attached_pictures, int)
FORMAT_WRAP_R3(avformat_receive_command_reply, int, unsigned int, command, void*, data)
FORMAT_WRAP_R3(avformat_send_command, int, unsigned int, command, void*, data)
FORMAT_WRAP_R2(avformat_write_header, int, void*, options)
FORMAT_WRAP_R4(av_get_output_timestamp, int, int, stream, void*, dts, void*, wall)
FORMAT_WRAP_R2(av_read_frame, int, void*, packet)
FORMAT_WRAP_R1(av_read_pause, int)
FORMAT_WRAP_R1(av_read_play, int)
FORMAT_WRAP_R4(av_seek_frame, int, int, stream_index, int64_t, timestamp, int, flags)
FORMAT_WRAP_R2(av_write_frame, int, void*, packet)
FORMAT_WRAP_R2(av_interleaved_write_frame, int, void*, packet)
FORMAT_WRAP_R3(av_write_uncoded_frame, int, int, stream_index, void*, frame)
FORMAT_WRAP_R3(av_interleaved_write_uncoded_frame, int, int, stream_index, void*, frame)
FORMAT_WRAP_R2(av_write_uncoded_frame_query, int, int, stream_index)
FORMAT_WRAP_R1(av_write_trailer, int)

#undef FORMAT_WRAP_R1
#undef FORMAT_WRAP_R2
#undef FORMAT_WRAP_R3
#undef FORMAT_WRAP_R4

EXPORT int my62_avformat_seek_file(x64emu_t* emu, void* context, int stream_index,
    int64_t min_timestamp, int64_t timestamp, int64_t max_timestamp, int flags)
{
    (void)emu;
    avformat_scope_t scope = avformat_scope_begin(context);
    int ret = my->avformat_seek_file(context, stream_index, min_timestamp,
        timestamp, max_timestamp, flags);
    avformat_scope_end(scope);
    return ret;
}

#define PRE_INIT \
    if(wrapped_ffmpeg8_preinit()) return -2;

#include "wrappedlib_init.h"

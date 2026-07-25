#define _GNU_SOURCE         /* See feature_test_macros(7) */
#define __STDC_WANT_LIB_EXT2__ 1 // for vasprintf
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>

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

const char* libavutil60Name = "libavutil.so.60";

#define LIBNAME libavutil60
#define ALTMY my60_

#include "generated/wrappedlibavutil60types.h"

#include "wrappercallback.h"

#define SUPER() \
GO(0)   \
GO(1)   \
GO(2)   \
GO(3)   \
GO(4)   \
GO(5)   \
GO(6)   \
GO(7)

// log_callback ...
#define GO(A)   \
static uintptr_t my60_log_callback_fct_##A = 0;                                  \
static void my60_log_callback_##A(void* avcl, int level, void* fmt, va_list ap)  \
{                                                                                \
    va_list copy;                                                                \
    char* allocated = NULL;                                                      \
    const char* message = "<libavutil60: unable to format log message>";         \
    union { long double align; unsigned char bytes[X64_VA_MAX_XMM]; } regs = {0};\
    uintptr_t overflow[2] __attribute__((aligned(16))) = {0};                    \
    x64_va_list_t guest_ap = {{                                                  \
        .gp_offset = 3 * sizeof(uintptr_t),                                      \
        .fp_offset = X64_VA_MAX_REG,                                             \
        .overflow_arg_area = overflow,                                           \
        .reg_save_area = regs.bytes,                                             \
    }};                                                                          \
    if(fmt) {                                                                    \
        va_copy(copy, ap);                                                       \
        if(vasprintf(&allocated, (const char*)fmt, copy) >= 0 && allocated)       \
            message = allocated;                                                 \
        va_end(copy);                                                            \
    }                                                                            \
    ((uintptr_t*)regs.bytes)[3] = (uintptr_t)message;                            \
    overflow[0] = (uintptr_t)message;                                            \
    RunFunctionFmt(my60_log_callback_fct_##A, "pipp", avcl, level, "%s", guest_ap);\
    free(allocated);                                                             \
}
SUPER()
#undef GO
static void* find60_log_callback_Fct(void* fct)
{
    if(!fct) return fct;
    if(GetNativeFnc((uintptr_t)fct))  return GetNativeFnc((uintptr_t)fct);
    #define GO(A) if(my60_log_callback_fct_##A == (uintptr_t)fct) return my60_log_callback_##A;
    SUPER()
    #undef GO
    #define GO(A) if(my60_log_callback_fct_##A == 0) {my60_log_callback_fct_##A = (uintptr_t)fct; return my60_log_callback_##A; }
    SUPER()
    #undef GO
    printf_log(LOG_NONE, "Warning, no more slot for libavutil60 log callback\n");
    return NULL;
}
// alloc ...
#define GO(A)   \
static uintptr_t my60_alloc_fct_##A = 0;                         \
static void* my60_alloc_##A(size_t size)                         \
{                                                                \
    return (void*)RunFunctionFmt(my60_alloc_fct_##A, "L", size); \
}
SUPER()
#undef GO
static void* find60_alloc_Fct(void* fct)
{
    if(!fct) return fct;
    if(GetNativeFnc((uintptr_t)fct))  return GetNativeFnc((uintptr_t)fct);
    #define GO(A) if(my60_alloc_fct_##A == (uintptr_t)fct) return my60_alloc_##A;
    SUPER()
    #undef GO
    #define GO(A) if(my60_alloc_fct_##A == 0) {my60_alloc_fct_##A = (uintptr_t)fct; return my60_alloc_##A; }
    SUPER()
    #undef GO
    printf_log(LOG_NONE, "Warning, no more slot for libavutil60 alloc callback\n");
    return NULL;
}
// alloc2 ...
#define GO(A)   \
static uintptr_t my60_alloc2_fct_##A = 0;                                      \
static void* my60_alloc2_##A(void* opaque, size_t size)                        \
{                                                                              \
    return (void*)RunFunctionFmt(my60_alloc2_fct_##A, "pL", opaque, size);     \
}
SUPER()
#undef GO
static void* find60_alloc2_Fct(void* fct)
{
    if(!fct) return fct;
    if(GetNativeFnc((uintptr_t)fct)) return GetNativeFnc((uintptr_t)fct);
    #define GO(A) if(my60_alloc2_fct_##A == (uintptr_t)fct) return my60_alloc2_##A;
    SUPER()
    #undef GO
    #define GO(A) if(my60_alloc2_fct_##A == 0) {my60_alloc2_fct_##A = (uintptr_t)fct; return my60_alloc2_##A; }
    SUPER()
    #undef GO
    printf_log(LOG_NONE, "Warning, no more slot for libavutil60 alloc2 callback\n");
    return NULL;
}
// func1 ...
#define GO(A)   \
static uintptr_t my60_func1_fct_##A = 0;                          \
static double my60_func1_##A(void* opaque, double value)          \
{                                                                 \
    return RunFunctionFmtD(my60_func1_fct_##A, "pd", opaque, value);\
}
SUPER()
#undef GO
static void* find60_func1_Fct(void* fct)
{
    if(!fct) return fct;
    if(GetNativeFnc((uintptr_t)fct))  return GetNativeFnc((uintptr_t)fct);
    #define GO(A) if(my60_func1_fct_##A == (uintptr_t)fct) return my60_func1_##A;
    SUPER()
    #undef GO
    #define GO(A) if(my60_func1_fct_##A == 0) {my60_func1_fct_##A = (uintptr_t)fct; return my60_func1_##A; }
    SUPER()
    #undef GO
    printf_log(LOG_NONE, "Warning, no more slot for libavutil60 func1 callback\n");
    return NULL;
}
// func2 ...
#define GO(A)   \
static uintptr_t my60_func2_fct_##A = 0;                                \
static double my60_func2_##A(void* opaque, double a, double b)          \
{                                                                       \
    return RunFunctionFmtD(my60_func2_fct_##A, "pdd", opaque, a, b);    \
}
SUPER()
#undef GO
static void* find60_func2_Fct(void* fct)
{
    if(!fct) return fct;
    if(GetNativeFnc((uintptr_t)fct))  return GetNativeFnc((uintptr_t)fct);
    #define GO(A) if(my60_func2_fct_##A == (uintptr_t)fct) return my60_func2_##A;
    SUPER()
    #undef GO
    #define GO(A) if(my60_func2_fct_##A == 0) {my60_func2_fct_##A = (uintptr_t)fct; return my60_func2_##A; }
    SUPER()
    #undef GO
    printf_log(LOG_NONE, "Warning, no more slot for libavutil60 func2 callback\n");
    return NULL;
}
// worker ...
#define GO(A)   \
static uintptr_t my60_worker_fct_##A = 0;                         \
static void my60_worker_##A(void* a, int b, int c, int d, int e) \
{                                                                \
    RunFunctionFmt(my60_worker_fct_##A, "piiii", a, b, c, d, e); \
}
SUPER()
#undef GO
static void* find60_worker_Fct(void* fct)
{
    if(!fct) return fct;
    if(GetNativeFnc((uintptr_t)fct))  return GetNativeFnc((uintptr_t)fct);
    #define GO(A) if(my60_worker_fct_##A == (uintptr_t)fct) return my60_worker_##A;
    SUPER()
    #undef GO
    #define GO(A) if(my60_worker_fct_##A == 0) {my60_worker_fct_##A = (uintptr_t)fct; return my60_worker_##A; }
    SUPER()
    #undef GO
    printf_log(LOG_NONE, "Warning, no more slot for libavutil60 worker callback\n");
    return NULL;
}
// main ...
#define GO(A)   \
static uintptr_t my60_main_fct_##A = 0;          \
static void my60_main_##A(void* a)               \
{                                                \
    RunFunctionFmt(my60_main_fct_##A, "p", a);   \
}
SUPER()
#undef GO
static void* find60_main_Fct(void* fct)
{
    if(!fct) return fct;
    if(GetNativeFnc((uintptr_t)fct))  return GetNativeFnc((uintptr_t)fct);
    #define GO(A) if(my60_main_fct_##A == (uintptr_t)fct) return my60_main_##A;
    SUPER()
    #undef GO
    #define GO(A) if(my60_main_fct_##A == 0) {my60_main_fct_##A = (uintptr_t)fct; return my60_main_##A; }
    SUPER()
    #undef GO
    printf_log(LOG_NONE, "Warning, no more slot for libavutil60 main callback\n");
    return NULL;
}
// free2 ...
#define GO(A)   \
static uintptr_t my60_free2_fct_##A = 0;              \
static void my60_free2_##A(void* a, void* b)          \
{                                                     \
    RunFunctionFmt(my60_free2_fct_##A, "pp", a, b);   \
}
SUPER()
#undef GO
static void* find60_free2_Fct(void* fct)
{
    if(!fct) return fct;
    if(GetNativeFnc((uintptr_t)fct))  return GetNativeFnc((uintptr_t)fct);
    #define GO(A) if(my60_free2_fct_##A == (uintptr_t)fct) return my60_free2_##A;
    SUPER()
    #undef GO
    #define GO(A) if(my60_free2_fct_##A == 0) {my60_free2_fct_##A = (uintptr_t)fct; return my60_free2_##A; }
    SUPER()
    #undef GO
    printf_log(LOG_NONE, "Warning, no more slot for libavutil60 free2 callback\n");
    return NULL;
}
// free1 ...
#define GO(A)   \
static uintptr_t my60_free1_fct_##A = 0;            \
static void my60_free1_##A(void* a)                 \
{                                                   \
    RunFunctionFmt(my60_free1_fct_##A, "p", a);     \
}
SUPER()
#undef GO
static void* find60_free1_Fct(void* fct)
{
    if(!fct) return fct;
    if(GetNativeFnc((uintptr_t)fct)) return GetNativeFnc((uintptr_t)fct);
    #define GO(A) if(my60_free1_fct_##A == (uintptr_t)fct) return my60_free1_##A;
    SUPER()
    #undef GO
    #define GO(A) if(my60_free1_fct_##A == 0) {my60_free1_fct_##A = (uintptr_t)fct; return my60_free1_##A; }
    SUPER()
    #undef GO
    printf_log(LOG_NONE, "Warning, no more slot for libavutil60 free1 callback\n");
    return NULL;
}
// compare/enumerate ...
#define GO(A)   \
static uintptr_t my60_cmp_fct_##A = 0;                           \
static int my60_cmp_##A(void* a, void* b)                        \
{                                                                \
    return (int)RunFunctionFmt(my60_cmp_fct_##A, "pp", a, b);    \
}
SUPER()
#undef GO
static void* find60_cmp_Fct(void* fct)
{
    if(!fct) return fct;
    if(GetNativeFnc((uintptr_t)fct)) return GetNativeFnc((uintptr_t)fct);
    #define GO(A) if(my60_cmp_fct_##A == (uintptr_t)fct) return my60_cmp_##A;
    SUPER()
    #undef GO
    #define GO(A) if(my60_cmp_fct_##A == 0) {my60_cmp_fct_##A = (uintptr_t)fct; return my60_cmp_##A; }
    SUPER()
    #undef GO
    printf_log(LOG_NONE, "Warning, no more slot for libavutil60 compare callback\n");
    return NULL;
}

// void* callback(void*)
#define GO(A)   \
static uintptr_t my60_pFp_fct_##A = 0;                           \
static void* my60_pFp_##A(void* a)                               \
{                                                                \
    return (void*)RunFunctionFmt(my60_pFp_fct_##A, "p", a);      \
}
SUPER()
#undef GO
static void* find60_pFp_Fct(void* fct)
{
    if(!fct) return fct;
    if(GetNativeFnc((uintptr_t)fct)) return GetNativeFnc((uintptr_t)fct);
    #define GO(A) if(my60_pFp_fct_##A == (uintptr_t)fct) return my60_pFp_##A;
    SUPER()
    #undef GO
    #define GO(A) if(my60_pFp_fct_##A == 0) {my60_pFp_fct_##A = (uintptr_t)fct; return my60_pFp_##A; }
    SUPER()
    #undef GO
    printf_log(LOG_NONE, "Warning, no more slot for libavutil60 pFp callback\n");
    return NULL;
}

// int callback(void*, void*, void*)
#define GO(A)   \
static uintptr_t my60_iFppp_fct_##A = 0;                                      \
static int my60_iFppp_##A(void* a, void* b, void* c)                          \
{                                                                             \
    return (int)RunFunctionFmt(my60_iFppp_fct_##A, "ppp", a, b, c);           \
}
SUPER()
#undef GO
static void* find60_iFppp_Fct(void* fct)
{
    if(!fct) return fct;
    if(GetNativeFnc((uintptr_t)fct)) return GetNativeFnc((uintptr_t)fct);
    #define GO(A) if(my60_iFppp_fct_##A == (uintptr_t)fct) return my60_iFppp_##A;
    SUPER()
    #undef GO
    #define GO(A) if(my60_iFppp_fct_##A == 0) {my60_iFppp_fct_##A = (uintptr_t)fct; return my60_iFppp_##A; }
    SUPER()
    #undef GO
    printf_log(LOG_NONE, "Warning, no more slot for libavutil60 iFppp callback\n");
    return NULL;
}

// int callback(void*, void*, void*, unsigned)
#define GO(A)   \
static uintptr_t my60_iFpppu_fct_##A = 0;                                     \
static int my60_iFpppu_##A(void* a, void* b, void* c, unsigned d)             \
{                                                                             \
    return (int)RunFunctionFmt(my60_iFpppu_fct_##A, "pppu", a, b, c, d);      \
}
SUPER()
#undef GO
static void* find60_iFpppu_Fct(void* fct)
{
    if(!fct) return fct;
    if(GetNativeFnc((uintptr_t)fct)) return GetNativeFnc((uintptr_t)fct);
    #define GO(A) if(my60_iFpppu_fct_##A == (uintptr_t)fct) return my60_iFpppu_##A;
    SUPER()
    #undef GO
    #define GO(A) if(my60_iFpppu_fct_##A == 0) {my60_iFpppu_fct_##A = (uintptr_t)fct; return my60_iFpppu_##A; }
    SUPER()
    #undef GO
    printf_log(LOG_NONE, "Warning, no more slot for libavutil60 iFpppu callback\n");
    return NULL;
}

// int callback(AVRefStructOpaque, void*)
#define GO(A)   \
static uintptr_t my60_iFUp_fct_##A = 0;                              \
static int my60_iFUp_##A(uint64_t a, void* b)                        \
{                                                                    \
    return (int)RunFunctionFmt(my60_iFUp_fct_##A, "Up", a, b);       \
}
SUPER()
#undef GO
static void* find60_iFUp_Fct(void* fct)
{
    if(!fct) return fct;
    if(GetNativeFnc((uintptr_t)fct)) return GetNativeFnc((uintptr_t)fct);
    #define GO(A) if(my60_iFUp_fct_##A == (uintptr_t)fct) return my60_iFUp_##A;
    SUPER()
    #undef GO
    #define GO(A) if(my60_iFUp_fct_##A == 0) {my60_iFUp_fct_##A = (uintptr_t)fct; return my60_iFUp_##A; }
    SUPER()
    #undef GO
    printf_log(LOG_NONE, "Warning, no more slot for libavutil60 iFUp callback\n");
    return NULL;
}

// void callback(AVRefStructOpaque, void*)
#define GO(A)   \
static uintptr_t my60_vFUp_fct_##A = 0;                         \
static void my60_vFUp_##A(uint64_t a, void* b)                  \
{                                                               \
    RunFunctionFmt(my60_vFUp_fct_##A, "Up", a, b);              \
}
SUPER()
#undef GO
static void* find60_vFUp_Fct(void* fct)
{
    if(!fct) return fct;
    if(GetNativeFnc((uintptr_t)fct)) return GetNativeFnc((uintptr_t)fct);
    #define GO(A) if(my60_vFUp_fct_##A == (uintptr_t)fct) return my60_vFUp_##A;
    SUPER()
    #undef GO
    #define GO(A) if(my60_vFUp_fct_##A == 0) {my60_vFUp_fct_##A = (uintptr_t)fct; return my60_vFUp_##A; }
    SUPER()
    #undef GO
    printf_log(LOG_NONE, "Warning, no more slot for libavutil60 vFUp callback\n");
    return NULL;
}

// void callback(AVRefStructOpaque)
#define GO(A)   \
static uintptr_t my60_vFU_fct_##A = 0;                    \
static void my60_vFU_##A(uint64_t a)                      \
{                                                          \
    RunFunctionFmt(my60_vFU_fct_##A, "U", a);             \
}
SUPER()
#undef GO
static void* find60_vFU_Fct(void* fct)
{
    if(!fct) return fct;
    if(GetNativeFnc((uintptr_t)fct)) return GetNativeFnc((uintptr_t)fct);
    #define GO(A) if(my60_vFU_fct_##A == (uintptr_t)fct) return my60_vFU_##A;
    SUPER()
    #undef GO
    #define GO(A) if(my60_vFU_fct_##A == 0) {my60_vFU_fct_##A = (uintptr_t)fct; return my60_vFU_##A; }
    SUPER()
    #undef GO
    printf_log(LOG_NONE, "Warning, no more slot for libavutil60 vFU callback\n");
    return NULL;
}

#undef SUPER

typedef struct av_task_callbacks_s {
    void* user_data;
    int local_context_size;
    void* priority_higher;
    void* ready;
    void* run;
} av_task_callbacks_t;

EXPORT void my60_av_log_set_callback(x64emu_t* emu, void* f)
{
    my->av_log_set_callback(find60_log_callback_Fct(f));
}

EXPORT void* my60_av_asprintf(x64emu_t* emu, void * fmt, uint64_t * b) {
    myStackAlign(emu, (const char*)fmt, b, emu->scratch, R_EAX, 1);
    PREPARE_VALIST;
    char* buff = NULL;
    if(vasprintf(&buff, (char*)fmt, VARARGS) < 0 || !buff)
        return NULL;
    void* ret = my->av_asprintf("%s", buff);
    free(buff);
    return ret;
}

EXPORT void my60_av_vbprintf(x64emu_t* emu, void* buff, void* fmt, x64_va_list_t b)
{
    (void)emu;
    #ifdef CONVERT_VALIST
    CONVERT_VALIST(b);
    #else
    myStackAlignValist(emu, (const char*)fmt, emu->scratch, b);
    PREPARE_VALIST;
    #endif
    my->av_vbprintf(buff, fmt, VARARGS);
}
EXPORT void my60_av_bprintf(x64emu_t* emu, void** buff, void * fmt, uint64_t * b) {
    myStackAlign(emu, (const char*)fmt, b, emu->scratch, R_EAX, 2);
    PREPARE_VALIST;
    my->av_vbprintf((char**)buff, (char*)fmt, VARARGS);
}

EXPORT void my60_av_log_default_callback(x64emu_t* emu, void* avcl, int level, void* fmt, x64_va_list_t ap)
{
    (void)emu;
#ifdef CONVERT_VALIST
    CONVERT_VALIST(ap);
#else
    myStackAlignValist(emu, (const char*)fmt, emu->scratch, ap);
    PREPARE_VALIST;
#endif
    my->av_log_default_callback(avcl, level, fmt, VARARGS);
}

EXPORT void my60_av_vlog(x64emu_t* emu, void* avcl, int level, void* fmt, x64_va_list_t ap)
{
    (void)emu;
#ifdef CONVERT_VALIST
    CONVERT_VALIST(ap);
#else
    myStackAlignValist(emu, (const char*)fmt, emu->scratch, ap);
    PREPARE_VALIST;
#endif
    my->av_vlog(avcl, level, fmt, VARARGS);
}

EXPORT void my60_av_log_format_line(x64emu_t* emu, void* avcl, int level, void* fmt,
                                  x64_va_list_t ap, void* line, int line_size, void* print_prefix)
{
    (void)emu;
#ifdef CONVERT_VALIST
    CONVERT_VALIST(ap);
#else
    myStackAlignValist(emu, (const char*)fmt, emu->scratch, ap);
    PREPARE_VALIST;
#endif
    my->av_log_format_line(avcl, level, fmt, VARARGS, line, line_size, print_prefix);
}

EXPORT int my60_av_log_format_line2(x64emu_t* emu, void* avcl, int level, void* fmt,
                                  x64_va_list_t ap, void* line, int line_size, void* print_prefix)
{
    (void)emu;
#ifdef CONVERT_VALIST
    CONVERT_VALIST(ap);
#else
    myStackAlignValist(emu, (const char*)fmt, emu->scratch, ap);
    PREPARE_VALIST;
#endif
    return my->av_log_format_line2(avcl, level, fmt, VARARGS, line, line_size, print_prefix);
}

EXPORT void my60_av_log_once(x64emu_t* emu, void* avcl, int initial_level, int subsequent_level,
                           void* state, void* fmt, uint64_t* b)
{
    myStackAlign(emu, (const char*)fmt, b, emu->scratch, R_EAX, 5);
    PREPARE_VALIST;
    char* buff = NULL;
    if(vasprintf(&buff, (char*)fmt, VARARGS) < 0 || !buff)
        buff = strdup("<libavutil60: unable to format log message>");
    my->av_log_once(avcl, initial_level, subsequent_level, state, "%s",
                    buff ? buff : "<libavutil60: unable to format log message>");
    free(buff);
}

EXPORT int my60_av_sscanf(x64emu_t* emu, void* string, void* fmt, uint64_t* b)
{
    myStackAlignScanf(emu, (const char*)fmt, b, emu->scratch, 2);
    PREPARE_VALIST;
    return vsscanf((const char*)string, (const char*)fmt, VARARGS);
}

EXPORT void* my60_av_buffer_pool_init(x64emu_t* emu, size_t size, void* alloc)
{
    return my->av_buffer_pool_init(size, find60_alloc_Fct(alloc));
}

EXPORT void* my60_av_buffer_pool_init2(x64emu_t* emu, size_t size, void* opaque, void* alloc, void* pool_free)
{
    return my->av_buffer_pool_init2(size, opaque, find60_alloc2_Fct(alloc), find60_free1_Fct(pool_free));
}

EXPORT int my60_av_expr_parse(x64emu_t* emu, void* expr, void* s, void** const_names, void** func1_names, void** funcs1, void** func2_names, void** funcs2, int offset, void* log)
{
    size_t n_f1 = 0, n_f2 = 0;
    void** funcs1_ = NULL;
    void** funcs2_ = NULL;
    if(funcs1) {
        while(funcs1[n_f1]) ++n_f1;
        funcs1_ = calloc(n_f1 + 1, sizeof(void*));
        if(!funcs1_) return -12;
        for(size_t i=0; i<n_f1; ++i) funcs1_[i] = find60_func1_Fct(funcs1[i]);
    }
    if(funcs2) {
        while(funcs2[n_f2]) ++n_f2;
        funcs2_ = calloc(n_f2 + 1, sizeof(void*));
        if(!funcs2_) {
            free(funcs1_);
            return -12;
        }
        for(size_t i=0; i<n_f2; ++i) funcs2_[i] = find60_func2_Fct(funcs2[i]);
    }
    int ret = my->av_expr_parse(expr, s, const_names, func1_names, funcs1_,
                                func2_names, funcs2_, offset, log);
    free(funcs1_);
    free(funcs2_);
    return ret;
}

EXPORT int my60_av_expr_parse_and_eval(x64emu_t* emu, void* res, void* s, void** const_names,
    void* const_values, void** func1_names, void** funcs1, void** func2_names,
    void** funcs2, void* opaque, int offset, void* log)
{
    size_t n_f1 = 0, n_f2 = 0;
    void** funcs1_ = NULL;
    void** funcs2_ = NULL;
    if(funcs1) {
        while(funcs1[n_f1]) ++n_f1;
        funcs1_ = calloc(n_f1 + 1, sizeof(void*));
        if(!funcs1_) return -12;
        for(size_t i=0; i<n_f1; ++i) funcs1_[i] = find60_func1_Fct(funcs1[i]);
    }
    if(funcs2) {
        while(funcs2[n_f2]) ++n_f2;
        funcs2_ = calloc(n_f2 + 1, sizeof(void*));
        if(!funcs2_) {
            free(funcs1_);
            return -12;
        }
        for(size_t i=0; i<n_f2; ++i) funcs2_[i] = find60_func2_Fct(funcs2[i]);
    }
    int ret = my->av_expr_parse_and_eval(res, s, const_names, const_values,
        func1_names, funcs1_, func2_names, funcs2_, opaque, offset, log);
    free(funcs1_);
    free(funcs2_);
    return ret;
}

EXPORT void my60_av_log(x64emu_t* emu, void* avcl, int lvl, void* fmt, uint64_t* b)
{
    myStackAlign(emu, (const char*)fmt, b, emu->scratch, R_EAX, 3);
    PREPARE_VALIST;
    char* buff = NULL;
    if(vasprintf(&buff, (char*)fmt, VARARGS) < 0 || !buff)
        buff = strdup("<libavutil60: unable to format log message>");
    my->av_log(avcl, lvl, "%s", buff ? buff : "<libavutil60: unable to format log message>");
    free(buff);
}

static void my60_avpriv_loglike(x64emu_t* emu, void* avcl, void* fmt, uint64_t* b,
    void (*native_fnc)(void*, const char*, ...))
{
    char* buff = NULL;
    if(fmt) {
        myStackAlign(emu, (const char*)fmt, b, emu->scratch, R_EAX, 2);
        PREPARE_VALIST;
        if(vasprintf(&buff, (const char*)fmt, VARARGS) < 0)
            buff = NULL;
    }
    native_fnc(avcl, "%s", buff ? buff : "<libavutil60: unable to format message>");
    free(buff);
}

EXPORT void my60_avpriv_report_missing_feature(x64emu_t* emu, void* avcl,
    void* fmt, uint64_t* b)
{
    my60_avpriv_loglike(emu, avcl, fmt, b,
        (void (*)(void*, const char*, ...))my->avpriv_report_missing_feature);
}

EXPORT void my60_avpriv_request_sample(x64emu_t* emu, void* avcl,
    void* fmt, uint64_t* b)
{
    my60_avpriv_loglike(emu, avcl, fmt, b,
        (void (*)(void*, const char*, ...))my->avpriv_request_sample);
}

EXPORT size_t my60_av_strlcatf(x64emu_t* emu, void* dst, size_t size, void* fmt, uint64_t* b)
{
    myStackAlign(emu, (const char*)fmt, b, emu->scratch, R_EAX, 3);
    PREPARE_VALIST;
    char* buff = NULL;
    if(vasprintf(&buff, (char*)fmt, VARARGS) < 0 || !buff)
        return my->av_strlcatf(dst, size, "%s",
            "<libavutil60: unable to format string>");
    size_t ret = my->av_strlcatf(dst, size, "%s", buff);
    free(buff);
    return ret;
}

EXPORT int my60_avpriv_slicethread_create(x64emu_t* emu, void* pctx, void* priv, void* worker, void* main_func, int nb)
{
    return my->avpriv_slicethread_create(pctx, priv, find60_worker_Fct(worker), find60_main_Fct(main_func), nb);
}

EXPORT void* my60_av_buffer_create(x64emu_t* emu, void* data, size_t size, void* f, void* opaque, int flags)
{
    return my->av_buffer_create(data, size, find60_free2_Fct(f), opaque, flags);
}

EXPORT void* my60_av_container_fifo_alloc(x64emu_t* emu, void* opaque,
    void* container_alloc, void* container_reset, void* container_free,
    void* fifo_transfer, unsigned flags)
{
    (void)emu;
    return my->av_container_fifo_alloc(opaque, find60_pFp_Fct(container_alloc),
        find60_free2_Fct(container_reset), find60_free2_Fct(container_free),
        find60_iFpppu_Fct(fifo_transfer), flags);
}

EXPORT void* my60_av_csp_trc_func_from_id(x64emu_t* emu, unsigned trc)
{
    (void)emu;
    void* ret = my->av_csp_trc_func_from_id(trc);
    return ret ? (void*)AddCheckBridge(my_lib->w.bridge, dFd, ret, 0,
                                       "av_csp_trc_function") : NULL;
}

EXPORT void* my60_av_csp_trc_func_inv_from_id(x64emu_t* emu, unsigned trc)
{
    (void)emu;
    void* ret = my->av_csp_trc_func_inv_from_id(trc);
    return ret ? (void*)AddCheckBridge(my_lib->w.bridge, dFd, ret, 0,
                                       "av_csp_trc_function") : NULL;
}

EXPORT void* my60_av_csp_itu_eotf(x64emu_t* emu, unsigned trc)
{
    (void)emu;
    void* ret = my->av_csp_itu_eotf(trc);
    return ret ? (void*)AddCheckBridge(my_lib->w.bridge, vFddp, ret, 0,
                                       "av_csp_eotf_function") : NULL;
}

EXPORT void* my60_av_csp_itu_eotf_inv(x64emu_t* emu, unsigned trc)
{
    (void)emu;
    void* ret = my->av_csp_itu_eotf_inv(trc);
    return ret ? (void*)AddCheckBridge(my_lib->w.bridge, vFddp, ret, 0,
                                       "av_csp_eotf_function") : NULL;
}

EXPORT void* my60_av_executor_alloc(x64emu_t* emu, const av_task_callbacks_t* callbacks,
    int thread_count)
{
    (void)emu;
    if(!callbacks)
        return my->av_executor_alloc(NULL, thread_count);
    av_task_callbacks_t native_callbacks = {
        .user_data = callbacks->user_data,
        .local_context_size = callbacks->local_context_size,
        .priority_higher = find60_cmp_Fct(callbacks->priority_higher),
        .ready = find60_cmp_Fct(callbacks->ready),
        .run = find60_iFppp_Fct(callbacks->run),
    };
    return my->av_executor_alloc(&native_callbacks, thread_count);
}

EXPORT int my60_av_fifo_peek_to_cb(x64emu_t* emu, void* fifo, void* callback,
    void* opaque, void* nb_elems, size_t offset)
{
    (void)emu;
    return my->av_fifo_peek_to_cb(fifo, find60_iFppp_Fct(callback), opaque,
                                  nb_elems, offset);
}

EXPORT int my60_av_fifo_read_to_cb(x64emu_t* emu, void* fifo, void* callback,
    void* opaque, void* nb_elems)
{
    (void)emu;
    return my->av_fifo_read_to_cb(fifo, find60_iFppp_Fct(callback), opaque,
                                  nb_elems);
}

EXPORT int my60_av_fifo_write_from_cb(x64emu_t* emu, void* fifo, void* callback,
    void* opaque, void* nb_elems)
{
    (void)emu;
    return my->av_fifo_write_from_cb(fifo, find60_iFppp_Fct(callback), opaque,
                                     nb_elems);
}

EXPORT void* my60_av_pixelutils_get_sad_fn(x64emu_t* emu, int width_bits,
    int height_bits, int aligned, void* log_ctx)
{
    (void)emu;
    void* ret = my->av_pixelutils_get_sad_fn(width_bits, height_bits, aligned, log_ctx);
    return ret ? (void*)AddCheckBridge(my_lib->w.bridge, iFplpl, ret, 0,
                                       "av_pixelutils_sad_fn") : NULL;
}

EXPORT void* my60_av_refstruct_alloc_ext_c(x64emu_t* emu, size_t size,
    unsigned flags, uint64_t opaque, void* free_cb)
{
    (void)emu;
    return my->av_refstruct_alloc_ext_c(size, flags, opaque,
                                        find60_vFUp_Fct(free_cb));
}

EXPORT void* my60_av_refstruct_pool_alloc_ext_c(x64emu_t* emu, size_t size,
    unsigned flags, uint64_t opaque, void* init_cb, void* reset_cb,
    void* free_entry_cb, void* free_cb)
{
    (void)emu;
    return my->av_refstruct_pool_alloc_ext_c(size, flags, opaque,
        find60_iFUp_Fct(init_cb), find60_vFUp_Fct(reset_cb),
        find60_vFUp_Fct(free_entry_cb), find60_vFU_Fct(free_cb));
}

EXPORT int my60_av_tx_init(x64emu_t* emu, void* context, void* tx,
    unsigned type, int inverse, int length, void* scale, uint64_t flags)
{
    (void)emu;
    void* native_tx = NULL;
    int ret = my->av_tx_init(context, tx ? &native_tx : NULL, type, inverse,
                             length, scale, flags);
    if(tx)
        *(void**)tx = (ret >= 0 && native_tx)
            ? (void*)AddCheckBridge(my_lib->w.bridge, vFpppl, native_tx, 0, "av_tx_fn")
            : NULL;
    return ret;
}

EXPORT void my60_av_thread_message_queue_set_free_func(x64emu_t* emu, void* mq, void* free_func)
{
    my->av_thread_message_queue_set_free_func(mq, find60_free1_Fct(free_func));
}

EXPORT void* my60_av_tree_find(x64emu_t* emu, void* root, void* key, void* cmp, void* next)
{
    return my->av_tree_find(root, key, find60_cmp_Fct(cmp), next);
}

EXPORT void* my60_av_tree_insert(x64emu_t* emu, void* rootp, void* key, void* cmp, void* next)
{
    return my->av_tree_insert(rootp, key, find60_cmp_Fct(cmp), next);
}

EXPORT void my60_av_tree_enumerate(x64emu_t* emu, void* tree, void* opaque, void* cmp, void* enu)
{
    my->av_tree_enumerate(tree, opaque, find60_cmp_Fct(cmp), find60_cmp_Fct(enu));
}

#define PRE_INIT if(wrapped_ffmpeg8_preinit()) return -2;

#include "wrappedlib_init.h"

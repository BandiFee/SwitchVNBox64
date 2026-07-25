#ifndef __WRAPPEDFFMPEG8_H_
#define __WRAPPEDFFMPEG8_H_

// Returns 0 when the complete native FFmpeg 8 set can be wrapped.
// Any failure is cached for the lifetime of the process.
int wrapped_ffmpeg8_preinit(void);

#endif // __WRAPPEDFFMPEG8_H_

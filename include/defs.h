#ifndef __DEFS__
#define __DEFS__

#define WIDTH 1280
#define HEIGHT 720

#define MAX_OBJS 5
#define TOTAL_FRAMES 1000

#define SCALE_FACTOR 10

#define __DEBUG__ 1
// color-print reference: http://web.theurbanpenguin.com/adding-color-to-your-output-from-c/
#define debug_print(...) do { if (__DEBUG__) \
                              fprintf(stderr, "\033[1;31m[DEBUG] \033[0;32m[FUNC] %s \033[0m", __PRETTY_FUNCTION__); \
                              fprintf(stderr, __VA_ARGS__); \
                              fprintf(stderr, "\n"); } while (0)
#endif

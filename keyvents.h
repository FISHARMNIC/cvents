#ifndef STDIO_H
#include <stdio.h>
#endif

#ifndef STDARG_H
#include <stdarg.h>
#endif

#ifndef PTHREAD_H
#include <pthread.h>
#endif

#ifndef TERMIOS_H
#include <termios.h>
#endif

static void *__key_events__[255];
static char __keys_used__[255];
static char __use_multithread__[255];
static int __use_key__ = 0;

static char __use_global_event__ = 0;
static void *__global_trigger__;
static int __num_events__;

// static char __use_multithread__ = 1;

static struct termios __oldt__, __newt__;
typedef void void_void_func_ptr_t(void);
typedef void void_char_func_ptr_t(char);

#define TERM_MT() ({        \
        pthread_exit(NULL); \
    })

#define USE_MT 0
#define NO_MT 1

// activate the special interface
#define KEY_INIT_ENTER() ({                      \
    tcgetattr(STDIN_FILENO, &__oldt__);          \
    __newt__ = __oldt__;                         \
    __newt__.c_lflag &= ~(ICANON);               \
    tcsetattr(STDIN_FILENO, TCSANOW, &__newt__); \
})

// activate the key press events
#define KEY_INIT_EXIT() ({                                         \
    pthread_t __thread__;                                          \
    pthread_create(&__thread__, NULL, __kb_event_handler__, NULL); \
    tcsetattr(STDIN_FILENO, TCSANOW, &__oldt__);                   \
})

void use_key(char key, void *handler, ...)
{
    va_list args;
    va_start(args, handler);
    __use_multithread__[__use_key__] = va_arg(args, int);
    __keys_used__[__use_key__++] = key;
    __key_events__[key] = handler;
    __num_events__++;
}

void use_global(void *handler)
{
    __use_global_event__ = 1;
    __global_trigger__ = handler;
}

void *__kb_event_handler__(void *arg)
{
    char gotten;
    while (1)
    {
        // wait until something got pressed
        while ((gotten = getchar()) == 0)
            ;

        //"unprint" the printed character
        printf("\33[2K\33[A\r");

        // if you are using a global triger
        if (__global_trigger__)
            ((void_char_func_ptr_t *)(__global_trigger__))(gotten);


        // for each bound event
        pthread_t threads[__num_events__];
        for (int i = 0; i < __num_events__; i++)
            // if I bound this key
            if (gotten == __keys_used__[i])
            {
                if (__use_multithread__[i] == USE_MT)
                    pthread_create(&threads[i], NULL, (__key_events__[__keys_used__[i]]), NULL);
                else
                    ((void_void_func_ptr_t *)(__key_events__[__keys_used__[i]]))();
            }
    }
}

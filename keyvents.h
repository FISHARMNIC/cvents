#ifndef STDIO_H
#include <stdio.h>
#endif

#ifndef STDARG_H
#include <stdarg.h>
#endif

#ifndef STDLIB_H
#include <stdlib.h>
#endif

#include <pthread.h>
#include <termios.h>
#include <unistd.h>

typedef void void_void_func_ptr_t(void);
typedef void void_char_func_ptr_t(char);

void *__key_events__[255];
char __keys_used__[255];
char __use_multithread__[255];
int __use_key__ = 0;

char __use_global_event__ = 0;
void *__global_trigger__;
int __num_events__;

struct termios __oldt__, __newt__;

#define USE_MT 0
#define NO_MT 1

void *__kb_event_handler__(void *arg);
void KEY_INIT_ENTER();
void KEY_INIT_EXIT();
void PROGRAM_EXIT();
void use_key(char key, void *handler, ...);
void use_global(void *handler);

// Exit the multithreaded event
void TERM_MT() {pthread_exit(NULL);}

// activate the special interface
void KEY_INIT_ENTER()
{
    tcgetattr(STDIN_FILENO, &__oldt__);
    __newt__ = __oldt__;
    __newt__.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &__newt__);
}

// activate the key press events
void KEY_INIT_EXIT()
{
    pthread_t __thread__;
    pthread_create(&__thread__, NULL, __kb_event_handler__, NULL);
}

void PROGRAM_EXIT() { tcsetattr(STDIN_FILENO, TCSANOW, &__oldt__); exit(0);}

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

        //"unprint" the newline created by the terminal
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

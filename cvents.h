#ifndef STDIO_H
#include <stdio.h>
#endif

#ifndef PTHREAD_H
#include <pthread.h>
#endif

#ifndef TERMIOS_H
#include <termios.h>
#endif

void *__key_events__[104];
char __keys_used__[104];
int __use_key__ = 0;

char __use_global_event__ = 0;
void *__global_trigger__;
int __num_events__;

static struct termios oldt, newt;
typedef void void_void_func_ptr_t(void);
typedef void void_char_func_ptr_t(char);

#define TERM_EVENT pthread_exit(NULL)

// activate the special terminal
#define KEY_INIT_ENTER ({                    \
    tcgetattr(STDIN_FILENO, &oldt);          \
    newt = oldt;                             \
    newt.c_lflag &= ~(ICANON);               \
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); \
})

// restore the normal interface
#define KEY_INIT_EXIT_2 ({ tcsetattr(STDIN_FILENO, TCSANOW, &oldt); })

// activate the key press events
#define KEY_INIT_EXIT ({                                   \
    pthread_t thread;                                      \
    pthread_create(&thread, NULL, kb_event_handler, NULL); \
    KEY_INIT_EXIT_2;                                       \
})

void use_key(char key, void *handler)
{
    __keys_used__[__use_key__++] = key;
    __key_events__[key] = handler;
    __num_events__++;
}

void use_global(void *handler)
{
    __use_global_event__ = 1;
    __global_trigger__ = handler;
}

void *kb_event_handler(void *arg)
{
    char gotten;
    while (1)
    {
        while ((gotten = getchar()) == 0);

        // if you are using a global triger
        if (__global_trigger__)
            ((void_char_func_ptr_t *)(__global_trigger__))(gotten);

        // for each bound event
        for (int i = 0; i < __num_events__; i++)
        {
            // trigger the bound items
            if (gotten == __keys_used__[i])
                ((void_void_func_ptr_t *)(__key_events__[__keys_used__[i]]))();
        }
    }
}

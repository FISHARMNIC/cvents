#include "cvents.h"
#include <unistd.h>

void key_a_event()
{
    printf("\n -> apples\n");
}

void key_b_event()
{
    printf("\n -> bannanas\n");
}

void global_event(char c)
{
    printf("\n YOU CLICKED: %c\n", c);
}

void initiate_keys()
{
    KEY_INIT_ENTER;

    /* Here are your events */
    use_key('a', key_a_event);
    use_key('b', key_b_event);
    //activate a global event
    use_global(global_event);
    /* ------------ */

    KEY_INIT_EXIT;
}

int main()
{
    initiate_keys();

    // to show how it is multi-threaded
    for(int i = 0;;i++) {
        printf("%i\n",i);
        sleep(1);
    }
    pthread_exit(NULL);
    return 0;
}

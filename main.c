#include "keyvents.h"

void key_a_event()
{
    printf("private handler apples\n");
}

void key_b_event()
{
    printf("private handler bannanas\n");
}

void key_c_event()
{
    printf("private handler chicken\n");
}

void exit_event()
{
    printf("--exit--\n");
    PROGRAM_EXIT();
}


void global_event(char c)
{
    printf("\nglobal handler: %i\n", c);
}

void initiate_keys()
{
    KEY_INIT_ENTER();

    /* Here are your events */
    use_key('a', key_a_event, USE_MT);
    use_key('b', key_b_event, NO_MT);
    use_key('c', key_c_event);
    use_key(27, exit_event); //exit program
    //activate a global event
    use_global(global_event);
    /* ------------ */

    KEY_INIT_EXIT();
}

int main()
{
    initiate_keys();

    // to show how the key presses do not block the main execution
    for(int i = 0;;i++) {
        printf("--TIMESTAMP: %i\n",i);
        sleep(1);
    }

    return 0;
}

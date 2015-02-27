#ifndef __KERNEL__
#define __KERNEL__
#endif

#include <auto_config.h>

nomask int is_game_object(void) {
   return 0;
}

nomask int is_kernel_object(void) {
   return 1;
}

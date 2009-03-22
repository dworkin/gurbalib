/*
 * Secondary auto object, only inherited by objects
 * outside /kernel
 *
 * Please don't do anything here yet, this is unfinished,
 * and currently only included to test the overall framework.
 *
 * Check with Aidil for more details.
 *
 */

nomask int is_game_object() {
  return 1;
}

nomask int is_kernel_object() {
  return 0;
}

#include "afun-game/variables.c"
#include "afun-game/set_this_player.c"
#include "afun-game/this_player.c"
#include "afun-game/this_body.c"
#include "afun-game/this_race.c"
#include "afun-game/this_environment.c"
#include "afun-game/out_unmod.c"
#include "afun-game/out.c"
#include "afun-game/write.c"
#include "afun-game/cat_file.c"


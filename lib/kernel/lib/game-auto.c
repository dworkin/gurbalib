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

#include "game-afun/variables.c"
#include "game-afun/set_this_player.c"
#include "game-afun/this_player.c"
#include "game-afun/this_body.c"
#include "game-afun/this_race.c"
#include "game-afun/this_environment.c"
#include "game-afun/out_unmod.c"
#include "game-afun/out.c"
#include "game-afun/write.c"
#include "game-afun/cat_file.c"


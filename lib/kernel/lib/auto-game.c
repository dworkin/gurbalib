/*
 * Secondary auto object, only inherited by objects
 * outside /kernel
 */

#include <tlsvar.h>
#include <trace.h>

nomask int is_game_object() {
  return 1;
}

nomask int is_kernel_object() {
  return 0;
}

#include "afun-game/variables.c"

/*
 * Security related overrides.
 * Any afun not having an override here cannot be
 * used in combination with unguarded.
 */

#include "afun-game/require_priv.c"
#include "afun-game/valid.c"
#include "afun-game/valid_read.c"
#include "afun-game/valid_write.c"
#include "afun-game/read_file.c"
#include "afun-game/write_file.c"
#include "afun-game/restore_object.c"
#include "afun-game/save_object.c"
#include "afun-game/get_dir.c"
#include "afun-game/file_exists.c"
#include "afun-game/file_size.c"
#include "afun-game/rename_file.c"
#include "afun-game/remove_file.c"
#include "afun-game/make_dir.c"
#include "afun-game/remove_dir.c"
#include "afun-game/unguarded.c"

/*
 * Protect arguments on the call_stack from being inspected
 * by non-kernel code.
 */
#include "afun-game/call_trace.c"

/*
 * non kernel tls access, uses a special tls var containing
 * a map of 'user' tlsvars indexed by name.
 */
#include "afun-game/get_tlvar.c"
#include "afun-game/set_tlvar.c"
#include "afun-game/get_otlvar.c"
#include "afun-game/set_otlvar.c"

/*
 * Allow game objects to query user privileges by object or name
 */
#include "afun-game/query_user_priv.c"
#include "afun-game/query_mortal.c"
#include "afun-game/query_wizard.c"
#include "afun-game/query_admin.c"

/*
 * Some filtered lists
 */
#include "afun-game/players.c"

/*
 * Some 'real' game related stuff, shouldn't this be in /sys/safun
 * instead?
 */
#include "afun-game/random_element.c"
#include "afun-game/invert_exit.c"
#include "afun-game/this_body.c"
#include "afun-game/this_race.c"
#include "afun-game/this_environment.c"
#include "afun-game/out_unmod.c"
#include "afun-game/out.c"
#include "afun-game/cat_file.c"


/*
 * Gurbalib auto object
 *
 * Original code by Erlend Simonsen
 *
 */

#include <type.h>
#include <privileges.h>
#include <tlsvar.h>

#define LIST_PREV 0
#define LIST_NEXT 1

#include "afun/variables.c"
#include "afun/caught_error.c"
#include "afun/rethrow.c"
#include "afun/set_list.c"
#include "afun/get_list.c"
#include "afun/console_msg.c"
#include "afun/compile_object.c"
#include "afun/clone_object.c"
#include "afun/destruct_object.c"
#include "afun/set_this_player.c"
#include "afun/this_player.c"
#include "afun/this_body.c"
#include "afun/this_race.c"
#include "afun/this_environment.c"
#include "afun/file_exists.c"
#include "afun/absolute_path.c"
#include "afun/out_unmod.c"
#include "afun/out.c"
#include "afun/write.c"
#include "afun/capitalize.c"
#include "afun/lowercase.c"
#include "afun/uppercase.c"
#include "afun/article.c"
#include "afun/format_idle_time.c"
#include "afun/format_time.c"
#include "afun/member_array.c"
#include "afun/member_map.c"
#include "afun/cat_file.c"
#include "afun/dump_value.c"
#include "afun/wiz_dir.c"
#include "afun/normalize_path.c"
#include "afun/dir_size.c"
#include "afun/file_size.c"
#include "afun/random_element.c"
#include "afun/base_name.c"
#include "afun/file_name.c"
#include "afun/clone_num.c"
#include "afun/num_clones.c"
#include "afun/prev_clone.c"
#include "afun/next_clone.c"
#include "afun/call_out.c"
#include "afun/add_event.c"
#include "afun/remove_event.c"
#include "afun/subscribe_event.c"
#include "afun/unsubscribe_event.c"
#include "afun/event.c"
#include "afun/str2val.c"
#include "afun/intp.c"
#include "afun/floatp.c"
#include "afun/arrayp.c"
#include "afun/mappingp.c"
#include "afun/objectp.c"
#include "afun/stringp.c"
#include "afun/nullp.c"
#include "afun/strstr.c"
#include "afun/replace_string.c"
#include "afun/invert_exit.c"

#include "sys/_F_create.c"
#include "sys/_F_destruct.c"
#include "sys/_F_call_out.c"


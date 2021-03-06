/*
 * Gurbalib auto object
 *
 * Original code by Erlend Simonsen
 *
 */

#include <type.h>
#include <privileges.h>
#include <tlsvar.h>
#include <status.h>
#include <trace.h>

#define LIST_PREV 0
#define LIST_NEXT 1

#include "afun/variables.c"
#include "afun/prototypes.c"
#include "afun/require_priv.c"
#include "afun/unguarded.c"
#include "afun/find_object.c"
#include "afun/this_program.c"
#include "afun/caught_error.c"
#include "afun/rethrow.c"
#include "afun/intp.c"
#include "afun/floatp.c"
#include "afun/arrayp.c"
#include "afun/mappingp.c"
#include "afun/objectp.c"
#include "afun/stringp.c"
#include "afun/nilp.c"
#include "afun/argcheck.c"
#include "afun/set_list.c"
#include "afun/get_list.c"
#include "afun/console_msg.c"
#include "afun/compile_object.c"
#include "afun/compile_library.c"
#include "afun/clone_object.c"
#include "afun/destruct_object.c"
#include "afun/previous_function.c"
#include "afun/file_exists.c"
#include "afun/absolute_path.c"
#include "afun/capitalize.c"
#include "afun/lowercase.c"
#include "afun/uppercase.c"
#include "afun/article.c"
#include "afun/format_idle_time.c"
#include "afun/format_time.c"
#include "afun/member_array.c"
#include "afun/member_map.c"
#include "afun/filter_array.c"
#include "afun/map_array.c"
#include "afun/dump_value.c"
#include "afun/wiz_dir.c"
#include "afun/normalize_path.c"
#include "afun/owner_file.c"
#include "afun/owner_object.c"
#include "afun/copy.c"
#include "afun/dir_size.c"
#include "afun/file_size.c"
#include "afun/base_name.c"
#include "afun/file_name.c"
#include "afun/clone_num.c"
#include "afun/num_clones.c"
#include "afun/prev_clone.c"
#include "afun/next_clone.c"
#include "afun/query_cloner.c"
#include "afun/call_out.c"
#include "afun/add_event.c"
#include "afun/remove_event.c"
#include "afun/subscribe_event.c"
#include "afun/unsubscribe_event.c"
#include "afun/event.c"
#include "afun/rexplode.c"
#include "afun/str2val.c"
#include "afun/strstr.c"
#include "afun/strcmp.c"
#include "afun/replace_string.c"
#include "afun/path_file.c"
#include "afun/uniq_array.c"
#include "afun/shutdown.c"
#include "afun/this_user.c"
#include "afun/this_connection.c"
#include "afun/set_this_player.c"
#include "afun/this_player.c"
#include "afun/write.c"

#include "afun/sys/_F_create.c"
#include "afun/sys/_F_destruct.c"
#include "afun/sys/_F_call_out.c"
#include "afun/sys/_F_upgraded.c"
#include "afun/sys/_F_add_clone.c"
#include "afun/sys/_F_remove_clone.c"
#include "afun/sys/_F_set_cloner.c"

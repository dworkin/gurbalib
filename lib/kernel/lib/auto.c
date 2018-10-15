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
#include <auto_config.h>

#define LIST_PREV 0
#define LIST_NEXT 1
#define MODE_READ 0
#define MODE_WRITE 1

private mapping ltable;
static mapping events;
private object driver;
private object secure_d;
private int _clone_count;
private string _cloner;
private string _clone_trace;
private string _owner;

#include "afun/require_priv.c"

#ifdef CLOSURES_EXTENSION
#include "afun/functionp.c"
#endif

#include "afun/stringp.c"
#include "afun/argcheck.c"
#include "afun/unguarded.c"
#include "afun/find_object.c"
#include "afun/this_user.c"
#include "afun/this_connection.c"
#include "afun/caught_error.c"
#include "afun/rethrow.c"
#include "afun/intp.c"
#include "afun/floatp.c"
#include "afun/arrayp.c"
#include "afun/mappingp.c"
#include "afun/objectp.c"
#include "afun/dump_value.c"
#include "afun/nilp.c"
#include "afun/set_list.c"
#include "afun/get_list.c"
#include "afun/console_msg.c"
#include "afun/valid.c"
#include "afun/valid_read.c"
#include "afun/valid_write.c"
#include "afun/normalize_path.c"
#include "afun/file_exists.c"
#include "afun/compile_object.c"
#include "afun/compile_library.c"
#include "afun/clone_object.c"
#include "afun/new_object.c"
#include "afun/destruct_object.c"
#include "afun/lowercase.c"
#include "afun/uppercase.c"
#include "afun/filter_array.c"
#include "afun/filter_mapping.c"
#include "afun/map_array.c"
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
#include "afun/shutdown.c"
#include "afun/set_this_player.c"
#include "afun/this_player.c"
#include "afun/write.c"
#include "afun/editor.c"
#include "afun/blog_it.c"
#include "afun/bubblesort.c"
#include "afun/filelastmod.c"
#include "afun/files_modified.c"
#include "afun/sqlite3_exec.c"
#include "afun/sqlite3_select.c"
#include "afun/query_thousands_separator.c"
#include "afun/query_locale_data.c"
#include "afun/call_trace.c"
#include "afun/connect.c"
#include "afun/make_dir.c"
#include "afun/get_dir.c"
#include "afun/rename_file.c"
#include "afun/remove_file.c"
#include "afun/read_file.c"
#include "afun/write_file.c"
#include "afun/save_object.c"
#include "afun/restore_object.c"
#include "afun/remove_dir.c"
#include "afun/call_array.c"

#include "afun/sys/_F_create.c"
#include "afun/sys/_F_destruct.c"
#include "afun/sys/_F_call_out.c"
#include "afun/sys/_F_upgraded.c"
#include "afun/sys/_F_add_clone.c"
#include "afun/sys/_F_remove_clone.c"
#include "afun/sys/_F_set_cloner.c"

#include <std.h>
#include <status.h>

#define TIMEOUT 2000

void usage() {
   write("Usage: graph [-h] DIR\n");
   write("prints dot compatible output of a graph of the directory you " +
      "specify to /tmp/(wizardname).dot.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
}

string filename;

void print_node(string room, string dir) {
   mapping exits;
   string *keys, filepath, tmp;
   int i, maxi, len;
   object obj;

   dir = dir + "/";
   obj = find_object(dir + room);

   if (!obj) {
      obj = compile_object(dir + room);
   }

   if (obj) {
      len = strlen(dir);
      exits = obj->query_exits();
      keys = obj->query_exit_indices();
      if (exits) {
	 maxi = sizeof(keys);
	 for (i = 0; i < maxi; i++) {
	    tmp = exits[keys[i]] + ".c";
	    filepath = replace_string(tmp, dir, "");
	    write_file(filename, "\t\"" + room + "\" -> \"" + filepath +
	       "\" [label = \"" + keys[i] + "\"];\n");
	 }
      }
   } else {
      write_file(filename, "# Failed to load " + dir + room + "\n");
   }
}

void print_nodes_step(string * files, string str, int i) {
   int size, ticks;

   size = sizeof(files);
   if (i >= size) {
      write_file(filename, "}\n");
      write_file(filename, "# End: size = " + size + " Dir = " + str + "\n");
   } else {
      ticks = MAX_TICKS - status()[ST_TICKS];
      while ((i < size) && (ticks < TIMEOUT)) {
	 print_node(files[i], str);
	 ticks = MAX_TICKS - status()[ST_TICKS];
	 i = i + 1;
      }
      if (i >= size) {
	 write_file(filename, "}\n");
	 write_file(filename, "# End: size = " + size + " Dir = " + str + "\n");
      } else {
	 call_out("print_nodes_step", 0, files, str, i);
      }
   }
}

void main(string str) {
   string *files;
   mixed *dirent;

   if (!str || str == "") {
      usage();
      return;
   }
   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   str = normalize_path(str, this_player()->query_env("cwd"));

   if (!str || str == "") {
      write("Access denied.\n");
      return;
   }

   filename = "/tmp/" + this_player()->query_name() + ".dot";

   if (strlen(str) > 1 && str[strlen(str) - 1] == '/') {
      str = str[..strlen(str) - 2];
   }

   if (file_exists(str) != -1) {
      write("Dir not found.\n");
      return;
   }

   dirent = get_dir(str + "/*.c");

   if (!dirent) {
      write("Dir:" + str + " is empty.\n");
      return;
   }
   files = dirent[0];

   /* do the work here... */
   write_file(filename, "# Use neato -Tpng thisfile.dot -o thisfile.png\n");
   write_file(filename, "# Graph of : " + str + "\n");
   write_file(filename, "digraph G {\n");
   write_file(filename, "\toverlap = scale;\n");

   print_nodes_step(files, str, 0);
}

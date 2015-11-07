inherit "/sys/lib/menu";

#define TO this_object()

void browse(varargs string what);

static int show_file(string str) {
   string stuff, path;

   path = this_player()->query_env("cwd");

   path = normalize_path(str, path);

   switch (file_exists(path)) {
      case 1:
         stuff = read_file(path);
         this_player()->more(explode(stuff, "\n"));
         return 2;
         break;
      case -1:
         browse(path);
         return 2;
         break;
      default:
         write("File not found or no access");
         return 0;
         break;
   }
}

static int menu_action_quit(void) {
   write("Ok.");
   return 1;
}

private string format_file_info(string f, int size, int ts) {
   string result, tmp;

   result = "";


   tmp = owner_file(normalize_path(f, "/")) + "                ";
   tmp = tmp[0..11];

   result += tmp + " ";

   switch (size) {
      case -2:
         tmp = "DIR       ";
         break;
      default:
         tmp = "             " + size;
         tmp = tmp[strlen(tmp) - 10..];
         break;
   }

   result += tmp + " ";

   result += ctime(ts)[4..];
   return result;
}

void browse(varargs string what) {
   int k, i, sz;
   mixed *menu;
   mixed **files;
   string path;

   if (what && strlen(what) && valid_read(what)) {
      switch (file_exists(what)) {
         case 1:
            show_file(what);
            return;
            break;
         case -1:
            path = normalize_path(what, "/");
            this_player()->set_env("cwd", path);
            break;
         default:
            write("No such file or directory or no access.");
            return;
            break;
      }
   } else {
      path = this_player()->query_env("cwd");
   }

   if (!path) {
      path = "/";
      this_player()->set_env("cwd", path);
   }

   files = get_dir(path + "/*");
   menu = ( { } );
   k = 1;

   for (i = 0, sz = sizeof(files[0]); i < sz; i++) {
      menu += ({ 
         ({ "" + (k++), files[0][i],
            format_file_info(path + "/" + files[0][i], files[1][i],
            files[2][i]), make_fcall(TO, "show_file", files[0][i])
         })
      });
   }

   if (path != "/") {
      menu += ({
         ({
            "..", "<previous directory>", nil, make_fcall(TO, "show_file", "..")
         }) 
      });
   }

   menu += ({
      ({
         "q", "quit menu", nil, make_fcall(TO, "menu_action_quit") 
      })
   });

   do_menu("Browsing: " + path, menu);
}

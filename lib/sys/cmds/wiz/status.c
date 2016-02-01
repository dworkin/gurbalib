inherit M_COMMAND;

#include <status.h>

string *usage(void) {
   string *lines;

   lines = ({ "Usage: status [-h] [OBJ]" });
   lines += ({ " " });
   lines += ({ "Display various usage stat's about the object OBJ." });
   lines += ({ "If no object is given it displays stats for the driver." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tstatus" });
   lines += ({ "\tstatus sirdude" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("wiz", "date");
   add_also("wiz", "scan");
   add_also("wiz", "time");
}

void display_driver(mixed * stat) {
   string *lines;

   lines = ({ "Driver version         : " + (string) stat[ST_VERSION] });
   lines += ({ "System Start time      : " + 
      (string) ctime(stat[ST_STARTTIME]) });
   lines += ({ "System Boot time       : " + 
      (string) ctime(stat[ST_BOOTTIME]) });
   lines += ({ "Uptime                 :" + 
      fmt_time(stat[ST_UPTIME]) });
   lines += ({ "Swapsize               : " + 
      (string) stat[ST_SWAPSIZE] });
   lines += ({ "Swap used              : " + (string) stat[ST_SWAPUSED] });
   lines += ({ "Swap sector size       : " + (string) stat[ST_SECTORSIZE] });
   lines += ({ "Swap objects/1m        : " + (string) stat[ST_SWAPRATE1] });
   lines += ({ "Swap objects/5m        : " + (string) stat[ST_SWAPRATE5] });
   lines += ({ "Static mem allocated   : " + (string) stat[ST_SMEMSIZE] });
   lines += ({ "Static mem in use      : " + (string) stat[ST_SMEMUSED] });
   lines += ({ "Dynamic mem allocated  : " + (string) stat[ST_DMEMSIZE] });
   lines += ({ "Dynamic mem in use     : " + (string) stat[ST_DMEMUSED] });
   lines += ({ "Object table size      : " + (string) stat[ST_OTABSIZE] });
   lines += ({ "Number of objects      : " + (string) stat[ST_NOBJECTS] });
   lines += ({ "Callouts table size    : " + (string) stat[ST_COTABSIZE] });
   lines += ({ "Number of short call_ou: " + (string) stat[ST_NCOSHORT] });
   lines += ({ "Number of long call_out: " + (string) stat[ST_NCOLONG] });
   lines += ({ "User table size        : " + (string) stat[ST_UTABSIZE] });
   lines += ({ "Editor table size      : " + (string) stat[ST_ETABSIZE] });
   lines += ({ "Max string size        : " + (string) stat[ST_STRSIZE] });
   lines += ({ "Max array/mapping size : " + (string) stat[ST_ARRAYSIZE] });
   lines += ({ "Remaining stack depth   : " + (string) stat[ST_STACKDEPTH] });
   lines += ({ "Remaining ticks         : " + (string) stat[ST_TICKS] });

   this_player()->more(lines);
}

void display_obj(mixed * stat, object obj) {
   int i, maxi;
   mapping tmp;
   string *keys, *incs, *lines, *tmp2;
   string cloner;

   lines =  ({ "OBJ ID                 : " + (string) stat[O_INDEX] });
   lines += ({ "Filename               : " + obj->file_name() });
   lines += ({ "Compile Time           : " + (string) ctime(stat[O_COMPILETIME])
      });
   lines += ({ "Program Size           : " + (string) stat[O_PROGSIZE] });
   lines += ({ "Data Size              : " + (string) stat[O_DATASIZE] });
   lines += ({ "Sectors                : " + (string) stat[O_NSECTORS] });

   tmp2 = stat[O_CALLOUTS];
   if (tmp2) {
      maxi = sizeof(tmp2);
      lines += ({ "Call outs              : "  + maxi });
      for (i = 0; i < maxi; i++) {
         lines += ({ "\t" + tmp2[i] });
      }
   } else {
      lines += ({ "Call outs              : 0" });
   }

   tmp = stat[O_UNDEFINED];
   if (tmp) {
      keys = map_indices(tmp);
      maxi = sizeof(keys);
      lines += ({ "Undefined Functions    : " + maxi });
      for (i = 0; i < maxi; i++) {
         lines += ({ "\t" + keys[i] + ": " + dump_value(keys[i], tmp) });
      }
   } else {
      lines += ({ "Undefined Functions    : 0" });
   }

   tmp2 = DRIVER->find_all_depending_programs(obj->file_name());
   if (tmp2) {
      maxi = sizeof(tmp2);
      lines += ({ "Depending programs     : " + maxi});
      for (i = 0; i < maxi; i++) {
         lines += ({ "\t" + tmp2[i] });
      }
   } else {
      lines += ({ "Depending programs     : 0"});
   }

   incs = COMPILER_D->query_includes(obj->file_name());
   if (incs) {
      maxi = sizeof(incs);
      lines += ({ "Includes               : " + maxi });
      for (i = 0; i < maxi; i++) {
         lines += ({ "\t" + incs[i] });
      } 
   } else {
      lines += ({ "Includes               : 0" });
   }

   lines += ({ "File Owner             : " + owner_file(obj->file_name()) });
   lines += ({ "Object Owner           : " + owner_object(obj) });
   cloner = obj->query_cloner();
   if (cloner) { 
      lines += ({ "Cloner                 : " + cloner });
   }

   this_player()->more(lines);
}

static void main(string str) {
   mixed *stat;
   object obj;

   if (!alsos) {
      setup_alsos();
   }

   if (empty_str(str)) {
      stat = status();
      display_driver(stat);
   } else if (sscanf(str, "-%s", str)) {
      this_player()->more(usage());
      return;
   } else {
      obj = this_player()->query_environment()->present(str);

      if (!obj) {
         obj = this_player()->present(str);
      }

      if (!obj) {
         obj = USER_D->find_player(str);
      }

      if (!obj) {
         str = normalize_path(str, this_player()->query_env("cwd"));

         if (file_exists(str)) {
            if (!obj) {
               obj = find_object(str);
            }
            if (!obj) {
               obj = compile_object(str);
               if (obj) {
                  obj->setup();
                  obj->setup_mudlib();
               }
            }
         }
      }

      if (obj) {
         stat = status(obj);
         display_obj(stat, obj);
      } else {
         write("Unable to locate: " + str + "\n");
         return;
      }
   }
}

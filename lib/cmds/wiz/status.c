#include <status.h>

void usage() {
   write("Usage: status [-h] [OBJ]\n");
   write("Display various usage stat's about the object OBJ.\n");
   write("If no object is given it displays stats for the driver.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
   write("See also: date, time, wtime, scan\n");
}

// XXX Has a bunch of experimental stuff in it that needs to be cleaned up.

void display_driver(mixed * stat) {
   write("Driver version         : " + (string) stat[ST_VERSION] + "\n");
   write("System Start time      : " + (string) ctime(stat[ST_STARTTIME]) +
      "\n");
   write("System Boot time       : " + (string) ctime(stat[ST_BOOTTIME]) +
      "\n");
   write("Uptime                 :" + format_time(stat[ST_UPTIME]) + "\n");
   write("Swapsize               : " + (string) stat[ST_SWAPSIZE] + "\n");
   write("Swap used              : " + (string) stat[ST_SWAPUSED] + "\n");
   write("Swap sector size       : " + (string) stat[ST_SECTORSIZE] + "\n");
   write("Swap objects/1m        : " + (string) stat[ST_SWAPRATE1] + "\n");
   write("Swap objects/5m        : " + (string) stat[ST_SWAPRATE5] + "\n");
   write("Static mem allocated   : " + (string) stat[ST_SMEMSIZE] + "\n");
   write("Static mem in use      : " + (string) stat[ST_SMEMUSED] + "\n");
   write("Dynamic mem allocated  : " + (string) stat[ST_DMEMSIZE] + "\n");
   write("Dynamic mem in use     : " + (string) stat[ST_DMEMUSED] + "\n");
   write("Object table size      : " + (string) stat[ST_OTABSIZE] + "\n");
   write("Number of objects      : " + (string) stat[ST_NOBJECTS] + "\n");
   write("Callouts table size    : " + (string) stat[ST_COTABSIZE] + "\n");
   write("Number of short co     : " + (string) stat[ST_NCOSHORT] + "\n");
   write("Number of long co      : " + (string) stat[ST_NCOLONG] + "\n");
   write("User table size        : " + (string) stat[ST_UTABSIZE] + "\n");
   write("Editor table size      : " + (string) stat[ST_ETABSIZE] + "\n");
   write("Max string size        : " + (string) stat[ST_STRSIZE] + "\n");
   write("Max array/mapping size : " + (string) stat[ST_ARRAYSIZE] + "\n");
   write("Remaining stack depth   : " + (string) stat[ST_STACKDEPTH] + "\n");
   write("Remaining ticks         : " + (string) stat[ST_TICKS] + "\n");
}

void display_obj(mixed * stat, object obj) {
   int i, maxi;
   mixed *tmp;
   string *incs;

   write("OBJ ID                 : " + (string) stat[O_INDEX] + "\n");
   write("Filename               : " + obj->file_name() + "\n");
   write("Compile Time           : " + (string) ctime(stat[O_COMPILETIME]) +
      "\n");
   write("Program Size           : " + (string) stat[O_PROGSIZE] + "\n");
   write("Data Size              : " + (string) stat[O_DATASIZE] + "\n");
   write("Sectors                : " + (string) stat[O_NSECTORS] + "\n");
   write("Callout's              :\n");
   tmp = stat[O_CALLOUTS];
   if (tmp) {
      maxi = sizeof(tmp);
      for (i = 0; i < maxi; i++) {
	 write("\t" + tmp[i] + "\n");
      }
   }
   write("Undefined Functions    :  XXX (Need to implement this bit...)\n");
   tmp = stat[O_UNDEFINED];
   if (tmp) {
      maxi = sizeof(tmp);
      for (i = 0; i < maxi; i++) {
	 write("\t" + tmp[i] + "\n");
      }
   }
   write("Inherited              :" + (string) stat[O_INHERITED] + "\n");
   write("Instantiated           :" + (string) stat[O_INSTANTIATED] + "\n");
   tmp = DRIVER->find_all_depending_programs(obj->file_name());
   if (tmp) {
      maxi = sizeof(tmp);
      for (i = 0; i < maxi; i++) {
	 write("\t" + tmp[i] + "\n");
      }
   }
   incs = COMPILER_D->query_includes(obj->file_name());
   if (incs) {
      maxi = sizeof(incs);
      for (i = 0; i < maxi; i++) {
	 write("\t" + incs[i] + "\n");
      }
   }
   write("File Owner: " + owner_file(obj->file_name()) + "\n");
   write("Object Owner: " + owner_object(obj) + "\n");
}

void main(string str) {
   mixed *stat;
   object obj;

   if (!str || str == "") {
      stat = status();
      display_driver(stat);
   } else if (sscanf(str, "-%s", str)) {
      usage();
      return;
   } else {
      obj = this_player()->query_environment()->present(str);

      if (!obj) {
	 obj = this_player()->present(str);
      }

      if (!obj) {
	 obj = USER_D->find_player(str);
      }

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

      if (obj) {
	 stat = status(obj);
	 display_obj(stat, obj);
      } else {
	 write("Unable to locate: " + str + "\n");
	 return;
      }
   }
}

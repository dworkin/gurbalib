#include <status.h>

void usage() {
  write("Usage: status [-h]\n");
  write("Display various stat's about the server.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void main( string str ) {
  mixed *stat;

  stat = status();

  write("Driver version         : "+(string)stat[ST_VERSION]+"\n");
  write("System Start time      : "+(string)ctime(stat[ST_STARTTIME])+"\n");
  write("System Boot time       : "+(string)ctime(stat[ST_BOOTTIME])+"\n");
  write("Uptime                 :"+format_time(stat[ST_UPTIME])+"\n");
  write("Swapsize               : "+(string)stat[ST_SWAPSIZE]+"\n");
  write("Swap used              : "+(string)stat[ST_SWAPUSED]+"\n");
  write("Swap sector size       : "+(string)stat[ST_SECTORSIZE]+"\n");
  write("Swap objects/1m        : "+(string)stat[ST_SWAPRATE1]+"\n");
  write("Swap objects/5m        : "+(string)stat[ST_SWAPRATE5]+"\n");
  write("Static mem allocated   : "+(string)stat[ST_SMEMSIZE]+"\n");
  write("Static mem in use      : "+(string)stat[ST_SMEMUSED]+"\n");
  write("Dynamic mem allocated  : "+(string)stat[ST_DMEMSIZE]+"\n");
  write("Dynamic mem in use     : "+(string)stat[ST_DMEMUSED]+"\n");
  write("Object table size      : "+(string)stat[ST_OTABSIZE]+"\n");
  write("Number of objects      : "+(string)stat[ST_NOBJECTS]+"\n");
  write("Callouts table size    : "+(string)stat[ST_COTABSIZE]+"\n");
  write("Number of short co     : "+(string)stat[ST_NCOSHORT]+"\n");
  write("Number of long co      : "+(string)stat[ST_NCOLONG]+"\n");
  write("User table size        : "+(string)stat[ST_UTABSIZE]+"\n");
  write("Editor table size      : "+(string)stat[ST_ETABSIZE]+"\n");
  write("Max string size        : "+(string)stat[ST_STRSIZE]+"\n");
  write("Max array/mapping size : "+(string)stat[ST_ARRAYSIZE]+"\n");
  write("Remaning stack depth   : "+(string)stat[ST_STACKDEPTH]+"\n");
  write("Remaning ticks         : "+(string)stat[ST_TICKS]+"\n");
}


void usage() {
  write("Usage: call [-h] FUNCTION [ARGS]\n");
  write("call the function FUNCTION with arguments ARGS in this object.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void main( string arg ) {
   string *tmp;
   int i;

   if ( !arg || arg == "" ) {
     usage();
     return;
   }
   if (sscanf(arg, "-%s",arg)) {
      usage();
      return;
   }
 
   tmp = explode(arg, " ");
   i = sizeof(tmp);
   if( i==1 ) {
      call_other(this_player(), tmp[0]); 
   } else if( i==2 ) {
      call_other(this_player(), tmp[0], tmp[1]); 
   } else if( i==3 ) {
      call_other(this_player(), tmp[0], tmp[1], tmp[2]); 
   } else if( i==4 ) {
      call_other(this_player(), tmp[0], tmp[1], tmp[2], tmp[3]); 
   } else if( i==5 ) {
      call_other(this_player(), tmp[0], tmp[1], tmp[2], tmp[3], tmp[4]); 
   } 
}


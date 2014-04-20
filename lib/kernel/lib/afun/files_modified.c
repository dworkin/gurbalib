mixed *files_modified(string str, int hours, int maxsz, int dir) {
#ifdef LPC_EXT_FILES_MODIFIED
   return ::files_modified(str, hours, maxsz, dir);
#else
   return nil;
#endif
}

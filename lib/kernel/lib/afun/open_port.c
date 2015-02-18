static void open_port(mixed args ...) {
   if (!require_priv("system")) {
      error("Illegal call to open_port");
   }
#ifdef SYS_NETWORKING
   ::open_port(args...);
#endif
}

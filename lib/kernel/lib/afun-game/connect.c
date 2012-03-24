static void connect(mixed args ...) {
   if (!require_priv("system")) {
      error("Illegal call to connect");
   }
   ::connect(args...);
}

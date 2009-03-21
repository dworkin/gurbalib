void console_msg( string message ) {
  argcheck( message, 1, "string" );
  find_object("/kernel/sys/driver")->message(message);
}

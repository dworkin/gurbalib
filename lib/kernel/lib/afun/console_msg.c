void console_msg( string message ) {
  find_object("/kernel/sys/driver")->message(message);
}

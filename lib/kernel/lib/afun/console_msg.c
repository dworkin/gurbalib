static void console_msg(string message) {
   argcheck(message, 1, "string");

   driver->message(message);
}

static void notify_fail(string str) {
   DRIVER->set_tlvar(TLS_FAIL_MESSAGE, str);
}

static void notify_fail(string str) {
   DRIVER->set_tlsvar(TLS_FAIL_MESSAGE, str);
}

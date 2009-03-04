#define UDP_RINGBUF_SIZE 64

private mixed *buffer;
private int   read_pos;
private int   write_pos;
private int   udp_sending;

/*
 * Setup the buffer
 */
private void initialize_udp_buffer() {
  buffer = allocate(UDP_RINGBUF_SIZE);
  read_pos = 0;
  write_pos = 0;
  udp_sending = 0;
}

/*
 * Send the next datagram in the queue
 */
private void send_queued_packet() {
  mixed * datagram;

  if(read_pos != write_pos) {
    datagram = buffer[read_pos];
    if(datagram) ::send_datagram(datagram[0], datagram[1], datagram[2]);
    buffer[read_pos] = nil;
    read_pos++;
    if(read_pos == UDP_RINGBUF_SIZE) {
      read_pos = 0;
    }
  } else {
    udp_sending = 0;
  }
}

/*
 * Called by the driver when its done.
 */
nomask static void datagram_done() {
  send_queued_packet();
}

/*
 * Send a datagram to some destination.
 * Returns the number of datagrams in the queue
 */
nomask static int send_datagram(string data, string ip, int port) {
  int count;

  if(!buffer) initialize_udp_buffer();

  if(write_pos == read_pos-1 || (read_pos == 0 && write_pos == UDP_RINGBUF_SIZE-1)) {
    error("UDP send buffer full");
  }

  buffer[write_pos] = ({ data, ip, port });
  write_pos++;
  if(write_pos == UDP_RINGBUF_SIZE) {
    write_pos = 0;
  }

  if(!udp_sending) {
    udp_sending = 1;
    send_queued_packet();
  }

  count = (write_pos - read_pos) % UDP_RINGBUF_SIZE; 
  if(count < 0) count += UDP_RINGBUF_SIZE + 1; 
  return count;
}

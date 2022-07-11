# :full_moon: Topic
   * **rdt3.0-TCP Socket programming**
   * Communication Network project


# :page_with_curl: Summary
   * This project is **Stop-and-Wait protocol**. There are *ARQ*, *Toggled Indicator*(The role of sequence number), *Timeout*, *Ack* and *Packet's sequence number*.
   * Split the given src.jpg file into 4096 Bytes and send each data packet to the server.
   * Intentionally implementing packet loss by random process.

# :star: Main functions of rdt 3.0
   |Part|Function|
   |--|--|
   |MySender.c|rdtSend, isACK, udtSend|
   |MyReceiver.c|rdtACK, sendACKwithLoss|
   

# :full_moon: Topic
   * **rdt3.0-TCP Socket programming**
   * Communication Network project


# :page_with_curl: Summary
   * This project is **Stop-and-Wait protocol**. There are *ARQ*, *Toggled Indicator*(The role of sequence number), *Timeout*, *Ack* and *Packet's sequence number*.
   * Split the given src.jpg file into 4096 Bytes and send each data packet to the server.
   * Intentionally implementing packet loss by random process.
   * Open two terminals from Ubuntu: mysender.c and myreceiver.c

# :star: Main functions of rdt 3.0
   |Part|Function|
   |--|--|
   |MySender.c|rdtSend, isACK, udtSend|
   |MyReceiver.c|rdtACK, sendACKwithLoss|
   
   
# :mag: Simulation result
   |Terminal name|Simulation result|explanation|
   |--|--|--|
   |MySender.c|<img src="https://user-images.githubusercontent.com/106147142/178687685-48a5a76e-35dc-4950-a278-8a46dc17fe63.jpg" width="400">|1. You can see the sequence numbers and toggled indicator <br> 2.|
   |MyReceiver.c|<img src="https://user-images.githubusercontent.com/106147142/178687895-989ed269-30c4-46ba-833f-d9735b15659f.jpg" width="400">|
   
   

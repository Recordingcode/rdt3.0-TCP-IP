# rdt3.0-TCP-IP
TCP socket programming for both sender and receiver
You should turn on two terminals : mySender and myReceiver
You can transfer any file (in mySender code src.jpg file) from source to destination (in myReceiver code same picture but different name dst.jpg file is stored)
There are three main functions: ARQ, Indicator(Sequence number), Timeout 
Packetloss in the channel is considered, but packet error is excluded

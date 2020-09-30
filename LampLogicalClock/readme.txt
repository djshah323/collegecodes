This program simulates Lamport's Logical Scalar clocks as mentioned in the assignment. 
This is created as a java program. 
The program needs 2 arguments.
1) Number of processes (internally threads) to create.
2) Time to run. During this interval randomly messages (local and send) are generated 

Each node (thread) created generates messages for all other nodes and itself based on a random number.
It starts listening from port # 8000 onwards.
At the end of the running time, happened before events are arranged as per the local value of the nodes' 
logical clocks. 

It is assumed java path is set at the time of calling the script.
The script by default provides commandline arguments to create 5 processes and a running time of 1 min. 
This can be changed by modifying the script. 

sample run:

Z:\LampLogicalClock>script.bat
Node 0 created. Listening at 8000
Node 1 created. Listening at 8001
Node 2 created. Listening at 8002
Node 3 created. Listening at 8003
Node 4 created. Listening at 8004
Node 2 Sending message to Node 1 Last clock: 0 New Clock: 1
Node 0 Sending message to Node 4 Last clock: 0 New Clock: 1
Node 1 Sending message to Node 3 Last clock: 0 New Clock: 1
Node 3 Sending message to Node 2 Last clock: 0 New Clock: 1
Node 4 Sending message to Node 0 Last clock: 0 New Clock: 1
Node 1 Received message. Recv Clock: 1 Own Clock: 1 New Clock: 2
Node 3 Received message. Recv Clock: 1 Own Clock: 1 New Clock: 2
Node 2 Received message. Recv Clock: 1 Own Clock: 1 New Clock: 2
Node 0 Received message. Recv Clock: 1 Own Clock: 1 New Clock: 2
Node 4 Received message. Recv Clock: 1 Own Clock: 1 New Clock: 2
Node 1 Takes a local step  New Clock: 3
Node 0 Sending message to Node 1 Last clock: 2 New Clock: 3
Node 3 Sending message to Node 2 Last clock: 2 New Clock: 3
Node 1 Received message. Recv Clock: 3 Own Clock: 3 New Clock: 4
Node 2 Sending message to Node 0 Last clock: 2 New Clock: 3
Node 0 Received message. Recv Clock: 3 Own Clock: 3 New Clock: 4
Node 2 Received message. Recv Clock: 3 Own Clock: 3 New Clock: 4
Node 4 Sending message to Node 3 Last clock: 2 New Clock: 3
Node 3 Received message. Recv Clock: 3 Own Clock: 3 New Clock: 4
Node 1 Takes a local step  New Clock: 5
Node 0 Sending message to Node 1 Last clock: 4 New Clock: 5
Node 3 Sending message to Node 4 Last clock: 4 New Clock: 5
Node 1 Received message. Recv Clock: 5 Own Clock: 5 New Clock: 6
Node 4 Received message. Recv Clock: 5 Own Clock: 3 New Clock: 6
Node 2 Sending message to Node 3 Last clock: 4 New Clock: 5
Node 3 Received message. Recv Clock: 5 Own Clock: 5 New Clock: 6
Node 4 Sending message to Node 1 Last clock: 6 New Clock: 7
Node 1 Received message. Recv Clock: 7 Own Clock: 6 New Clock: 8
Node 1 Sending message to Node 4 Last clock: 8 New Clock: 9
Node 4 Received message. Recv Clock: 9 Own Clock: 7 New Clock: 10
Node 0 Sending message to Node 1 Last clock: 5 New Clock: 6
Node 3 Takes a local step  New Clock: 7
Node 1 Received message. Recv Clock: 6 Own Clock: 9 New Clock: 10
Node 2 Takes a local step  New Clock: 6
Node 4 Sending message to Node 2 Last clock: 10 New Clock: 11
Node 2 Received message. Recv Clock: 11 Own Clock: 6 New Clock: 12
Node 1 Sending message to Node 4 Last clock: 10 New Clock: 11
Node 0 Sending message to Node 4 Last clock: 6 New Clock: 7
Node 4 Received message. Recv Clock: 11 Own Clock: 11 New Clock: 12
Node 4 Received message. Recv Clock: 7 Own Clock: 12 New Clock: 13
Node 3 Sending message to Node 4 Last clock: 7 New Clock: 8
Node 2 Sending message to Node 1 Last clock: 12 New Clock: 13
Node 4 Received message. Recv Clock: 8 Own Clock: 13 New Clock: 14
Node 1 Received message. Recv Clock: 13 Own Clock: 11 New Clock: 14
Node 4 Sending message to Node 0 Last clock: 14 New Clock: 15
Node 0 Received message. Recv Clock: 15 Own Clock: 7 New Clock: 16
Node 1 Sending message to Node 2 Last clock: 14 New Clock: 15
Node 0 Takes a local step  New Clock: 17
Node 2 Received message. Recv Clock: 15 Own Clock: 13 New Clock: 16
Node 3 Sending message to Node 0 Last clock: 8 New Clock: 9
Node 0 Received message. Recv Clock: 9 Own Clock: 17 New Clock: 18
Node 2 Sending message to Node 3 Last clock: 16 New Clock: 17
Node 3 Received message. Recv Clock: 17 Own Clock: 9 New Clock: 18
Node 4 Sending message to Node 0 Last clock: 15 New Clock: 16
Node 0 Received message. Recv Clock: 16 Own Clock: 18 New Clock: 19
Node 0 Sending message to Node 2 Last clock: 19 New Clock: 20
Node 2 Received message. Recv Clock: 20 Own Clock: 17 New Clock: 21
Node 1 Sending message to Node 4 Last clock: 15 New Clock: 16
Node 4 Received message. Recv Clock: 16 Own Clock: 16 New Clock: 17
Node 2 Sending message to Node 3 Last clock: 21 New Clock: 22
Node 3 Sending message to Node 1 Last clock: 18 New Clock: 19
Node 1 Received message. Recv Clock: 19 Own Clock: 16 New Clock: 20
Node 3 Received message. Recv Clock: 22 Own Clock: 19 New Clock: 23
Node 4 Sending message to Node 1 Last clock: 17 New Clock: 18
Node 1 Received message. Recv Clock: 18 Own Clock: 20 New Clock: 21
Node 0 Sending message to Node 2 Last clock: 20 New Clock: 21
Node 1 Takes a local step  New Clock: 22
Node 2 Received message. Recv Clock: 21 Own Clock: 22 New Clock: 23
Node 3 Sending message to Node 0 Last clock: 23 New Clock: 24
Node 2 Sending message to Node 0 Last clock: 23 New Clock: 24
Node 0 Received message. Recv Clock: 24 Own Clock: 21 New Clock: 25
Node 0 Received message. Recv Clock: 24 Own Clock: 25 New Clock: 26
Node 4 Takes a local step  New Clock: 19
Node 0 Sending message to Node 2 Last clock: 26 New Clock: 27
Node 1 Sending message to Node 0 Last clock: 22 New Clock: 23
Node 2 Received message. Recv Clock: 27 Own Clock: 24 New Clock: 28
Node 0 Received message. Recv Clock: 23 Own Clock: 27 New Clock: 28
Node 3 Sending message to Node 1 Last clock: 24 New Clock: 25
Node 2 Sending message to Node 0 Last clock: 28 New Clock: 29
Node 1 Received message. Recv Clock: 25 Own Clock: 23 New Clock: 26
Node 0 Received message. Recv Clock: 29 Own Clock: 28 New Clock: 30
Node 4 Sending message to Node 2 Last clock: 19 New Clock: 20
Node 2 Received message. Recv Clock: 20 Own Clock: 29 New Clock: 30
Node 1 Sending message to Node 2 Last clock: 26 New Clock: 27
Node 0 Sending message to Node 2 Last clock: 30 New Clock: 31
Node 2 Received message. Recv Clock: 27 Own Clock: 30 New Clock: 31
Node 2 Received message. Recv Clock: 31 Own Clock: 31 New Clock: 32
Node 3 Sending message to Node 1 Last clock: 25 New Clock: 26
Node 1 Received message. Recv Clock: 26 Own Clock: 27 New Clock: 28
Node 2 Takes a local step  New Clock: 33
Node 4 Sending message to Node 1 Last clock: 20 New Clock: 21
Node 1 Received message. Recv Clock: 21 Own Clock: 28 New Clock: 29
Node 1 Sending message to Node 0 Last clock: 29 New Clock: 30
Node 0 Sending message to Node 2 Last clock: 31 New Clock: 32
Node 0 Received message. Recv Clock: 30 Own Clock: 32 New Clock: 33
Node 2 Received message. Recv Clock: 32 Own Clock: 33 New Clock: 34
Node 3 Sending message to Node 0 Last clock: 26 New Clock: 27
Node 2 Takes a local step  New Clock: 35
Node 0 Received message. Recv Clock: 27 Own Clock: 33 New Clock: 34
Node 4 Sending message to Node 3 Last clock: 21 New Clock: 22
Node 3 Received message. Recv Clock: 22 Own Clock: 27 New Clock: 28
Node 1 Takes a local step  New Clock: 31
Node 0 Sending message to Node 3 Last clock: 34 New Clock: 35
Node 3 Received message. Recv Clock: 35 Own Clock: 28 New Clock: 36
Node 3 Sending message to Node 1 Last clock: 36 New Clock: 37
Node 2 Sending message to Node 4 Last clock: 35 New Clock: 36
Node 1 Received message. Recv Clock: 37 Own Clock: 31 New Clock: 38
Node 4 Received message. Recv Clock: 36 Own Clock: 22 New Clock: 37
Node 4 Sending message to Node 0 Last clock: 37 New Clock: 38
Node 0 Received message. Recv Clock: 38 Own Clock: 35 New Clock: 39
Ordering of generated events are as -
e[Node][Event]: ClockValue
e[2][1]:1
e[4][1]:1
e[1][1]:1
e[0][1]:1
Happend before
e[3][1]:2
Happend before
e[4][2]:3
e[2][2]:3
e[1][2]:3
e[0][2]:3
e[3][2]:3
Happend before
e[1][3]:5
e[3][3]:5
e[2][3]:5
e[0][3]:5
Happend before
e[2][4]:6
e[0][4]:6
Happend before
e[0][5]:7
e[3][4]:7
e[4][3]:7
Happend before
e[3][5]:8
Happend before
e[3][6]:9
e[1][4]:9
Happend before
e[4][4]:11
e[1][5]:11
Happend before
e[2][5]:13
Happend before
e[1][6]:15
e[4][5]:15
Happend before
e[4][6]:16
e[1][7]:16
Happend before
e[0][6]:17
e[2][6]:17
Happend before
e[4][7]:18
Happend before
e[4][8]:19
e[3][7]:19
Happend before
e[0][7]:20
e[4][9]:20
Happend before
e[4][10]:21
e[0][8]:21
Happend before
e[4][11]:22
e[1][8]:22
e[2][7]:22
Happend before
e[1][9]:23
Happend before
e[3][8]:24
e[2][8]:24
Happend before
e[3][9]:25
Happend before
e[3][10]:26
Happend before
e[0][9]:27
e[1][10]:27
e[3][11]:27
Happend before
e[2][9]:29
Happend before
e[1][11]:30
Happend before
e[1][12]:31
e[0][10]:31
Happend before
e[0][11]:33
e[2][10]:33
Happend before
e[0][12]:35
e[2][11]:35
Happend before
e[2][12]:36
Happend before
e[3][12]:37
Happend before
e[4][12]:38
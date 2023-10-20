package main

import (
    "bufio"
    "net"
    "log"
    "encoding/binary"
    "fmt"
)

const SDP = 3

type Example struct {
    a float32;
    b uint32;
}

func parsePacket[T interface{Example}](reader *bufio.Reader) T {
    t := T{}
    err := binary.Read(reader, binary.BigEndian, &t)
    
    if err != nil {
        panic(err)
    }

    return t;
}

func nextByte(reader *bufio.Reader) byte {
    byte, err := reader.ReadByte()
    if err != nil {
        log.Println("Error when reading byte: " + err.Error())
    }
    return byte;
}

func readFromServer(conn net.Conn) {

    log.Println("server");

    for {
        reader := bufio.NewReader(conn)
        if nextByte(reader) != SDP {
            continue
        }
        
        packet_type := nextByte(reader)
        offset := nextByte(reader)
        
        log.Println("Offset: ", offset)

        for i := offset - 2; i < offset; i++ {
            nextByte(reader)
        }

        switch (packet_type) {
            case 0:
                example := parsePacket(reader)
                fmt.Println("{}", example)
        }

    }

}

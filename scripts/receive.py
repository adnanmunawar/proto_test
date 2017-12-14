import socket
from foo_pb2 import Foo

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.bind(("127.0.0.1", 5555))
sock.listen(1)
foo = Foo()
i = 0
while True:
    conn, addr = sock.accept()
    while conn > 0:
        data = conn.recv(1024)
        if not data: break
        foo.ParseFromString(data)
        print addr
        print i
        print("Got foo with id={0} and bar={1}".format(foo.id, foo.bar))
        data_out = ['Received, Thankyou\n']
        conn.send(data_out[0])
        i +=1

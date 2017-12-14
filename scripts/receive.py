import socket
from foo_pb2 import Foo

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.bind(("127.0.0.1", 5555))
sock.listen(5)
foo = Foo()
while True:
    conn, addr = sock.accept()
    data = conn.recv(1024)
    foo.ParseFromString(data)
    print addr
    print("Got foo with id={0} and bar={1}".format(foo.id, foo.bar))
    data_out = ['Received, Thankyou\n']
    conn.send(data_out[0])

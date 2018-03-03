import socket, threading

lock = threading.Lock()
clients = [] #list of clients connected

class TelnetServer(threading.Thread):
    def __init__(self, (sock, address)):
        threading.Thread.__init__(self)
        self.socket = sock
        self.address = address

    def run(self):
        lock.acquire()
        clients.append(self)
        lock.release()
        print '%s:%s connected.' % self.address
        while True:  # continously read data
            data = self.socket.recv(1024)
            if not data:
                break
            for c in clients:
                c.socket.send(data)
        self.socket.close()
        print '%s:%s disconnected.' % self.address
        lock.acquire()
        clients.remove(self)
        lock.release()

def main():
    HOST = '127.0.0.1'
    PORT = 8080
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind((HOST, PORT))
    s.listen(4)
    while True:  # multiple connections
        TelnetServer(s.accept()).start()

main()

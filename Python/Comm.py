import serial


class Comm:
    def __init__(self, comm_port, baud_rate):
        self.comm = serial.Serial(comm_port, baud_rate, timeout=1)
        return

    def close_serial(self):
        self.comm.close()
        return

    def open_serial(self, path):
        self.comm.close()
        self.comm = serial.Serial(path)
        return

    def write_anything(self, message):
        msg = '\r\n' + message
        self.comm.write(msg.encode())
        return

    def send_length(self, x, y):
        msg = '\r\n' + str(x) + ',' + str(y)
        print(msg)
        self.comm.write(msg.encode())
        print(self.comm.readline().decode().strip())
        return

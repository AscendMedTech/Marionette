import serial

class Comm:
    def __init__(self, comm_port, baud_rate):
        try:
            self.comm = serial.Serial(comm_port, baud_rate, timeout = 1)
        except:
            print("That port is not available")
        return

    def closeSerial(self):
        self.comm.close()
        return

    def openSerial(self, path):
        self.comm.close()
        self.comm = serial.Serial(path)
        return

    def writeAnything(self, message):
        msg = '\r\n' + message
        self.comm.write(msg.encode())
        return

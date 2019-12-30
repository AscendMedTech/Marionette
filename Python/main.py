from Comm import Comm
from inputs import get_gamepad
from inputs import get_key
import serial
#test = serial.Serial('COM11', 9600, timeout = 1)

ser = Comm('COM10', 9600)

def main():
    x,y = 0,0
    while True:
        keyboardEvents = get_key()
        for event in keyboardEvents:
            if event.state == 1:
                if event.code == 'KEY_W':
                    x += 1
                elif event.code == 'KEY_S':
                    x -= 1
                elif event.code == 'KEY_D':
                    y += 1
                elif event.code == 'KEY_A':
                    y -= 1
        print(x,y)
        ser.send_length(x,y)
    return

if __name__ == '__main__':
    main()
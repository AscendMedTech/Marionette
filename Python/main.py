from Comm import Comm
from inputs import get_gamepad
from inputs import get_key
import serial
#test = serial.Serial('COM11', 9600, timeout = 1)

ser = Comm('COM10', 9600)
def main():
    controller = True
    try:
        events = get_gamepad()
    except:
        print("No game controller found. Using keyboard.")
        controller = False
    x,y = 0,0
    while True:
        x2, y2 = x, y
        if controller == True:
            x,y = getController()
        else:
            x,y = getKeyboard()
        if x2 != x or y2 != y:
            ser.send_length(x,y)
    return

def getController(x, y):
    events = get_gamepad()
    for event in events:
        if event.code == 'ABS_X':
            x = round(event.state/32768, 2)
            if -0.15 < x < 0.15:
                x = 0
        elif event.code == 'ABS_Y':
            y = round(event.state/32768, 2)
            if -0.15 < y < 0.15:
                y = 0
    return x, y

def getKeyboard(x, y):
    keyboardEvents = get_key()
    for event in keyboardEvents:
        if event.state == 1:
            if event.code == 'KEY_W':
                x += 0.01
            elif event.code == 'KEY_S':
                x -= 0.01
            elif event.code == 'KEY_D':
                y += 0.01
            elif event.code == 'KEY_A':
                y -= 0.01
    return x, y

if __name__ == '__main__':
    main()
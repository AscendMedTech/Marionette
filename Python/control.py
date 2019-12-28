from inputs import get_gamepad
from Comm import Comm

x, y = 0, 0
ser = Comm('COM1', 9600) #the comm port is 100% wrong. Check it and change it.


try:
    get_gamepad()
except:
    print("No Controller Found!\nExiting...")
    exit()
while True:
    events = get_gamepad()
    for event in events:
        if event.code == 'ABS_Y':
            y = round(event.state/32768, 4)
        elif event.code == 'ABS_X':
            x = round(event.state/32768, 4)
    print(x,y)

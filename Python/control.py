from inputs import get_gamepad

def main():
    while True:
        try:
            events = get_gamepad()
        except:
            print("No Controller Found!\nExiting...")
            break
        for event in events:
            print(event.ev_type, event.code, event.state)


main()
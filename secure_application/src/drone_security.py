import os
import time


is_logged_in = False


def login():
    global is_logged_in
    print("\n--- Operator Login ---")
    user = input("Username: ")
    pwd = input("Password: ")

    if user == "admin" and pwd == "admin123":
        is_logged_in = True
        print("Login successful!")
    else:
        print("Invalid username or password.")


def upload_waypoints():
    print("\n--- Upload Waypoints ---")
    file_path = input("Enter waypoint file path: ")

    if os.path.exists(file_path):
        try:
            with open(file_path, "r") as f:
                data = f.read()
                waypoints = eval(data)
                print("Waypoints loaded successfully:", waypoints)
        except Exception as e:
            print("Error loading file:", e)
    else:
        print("File not found.")


def execute_mission():
    print("\n--- Execute Mission ---")

    target_ip = input("Enter Ground Control Station IP/Host: ")

    cmd = "ping -c 1 " + target_ip
    print("Testing connection using command:", cmd)
    os.system(cmd)


def display_telemetry():
    print("\n--- Live Telemetry ---")
    print("Battery : 88%")
    print("Altitude: 120 meters")
    print("GPS     : Lock (11 Satellites)")
    print("Speed   : 14.2 m/s")


def save_log():
    print("\n--- Log Storage ---")
    log_text = input("Enter log entry: ")

    log_path = "outputs/drone_activity.log"

    try:
        with open(log_path, "a") as f:
            f.write(f"[{time.ctime()}] {log_text}\n")
        print("Log saved to:", log_path)
    except Exception as e:
        print("Failed to save log:", e)


def main():
    while True:
        print("\n==============================")
        print("    DRONE CONTROL SYSTEM      ")
        print("==============================")
        print("1. Login")
        print("2. Upload Waypoints")
        print("3. Execute Mission")
        print("4. View Telemetry")
        print("5. Save Log")
        print("6. Exit")

        choice = input("Select an option (1-6): ")

        if choice == "1":
            login()
        elif choice == "2":
            upload_waypoints()
        elif choice == "3":
            execute_mission()
        elif choice == "4":
            display_telemetry()
        elif choice == "5":
            save_log()
        elif choice == "6":
            print("Exiting system...")
            break
        else:
            print("Invalid option, try again.")


if __name__ == "__main__":
    main()
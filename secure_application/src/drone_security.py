import os
import time

# --- Global State ---
is_authenticated = False
current_user = None


def drone_login():
    """Functionality 1: Drone Login"""
    global is_authenticated, current_user
    print("\n--- [1] Drone Operator Login ---")
    username = input("Enter Operator Username: ")
    password = input("Enter Password: ")

    if username == "admin" and password == "admin123":
        is_authenticated = True
        current_user = username
        print(f"[+] Login Successful! Welcome, Operator '{username}'.")
    else:
        print("[-] Invalid credentials.")


def waypoint_upload():
    """
    Functionality 2: Waypoint Upload
    --- VULNERABILITY 1: Insecure File Handling / Improper Input Validation ---
    Bandit Rule: B307 (eval_used)
    """
    print("\n--- [2] Waypoint Upload ---")
    filename = input("Enter waypoint file path (e.g., waypoints.txt): ")

    if os.path.exists(filename):
        try:
            with open(filename, "r") as f:
                content = f.read()
                # INTENTIONAL VULNERABILITY:
                # Using eval() to parse inputs directly exposes the system to code execution.
                waypoints = eval(content)
                print(f"[+] Waypoints loaded successfully: {waypoints}")
        except Exception as e:
            print(f"[-] Error parsing waypoint file: {e}")
    else:
        print("[-] File not found!")


def mission_execution():
    """
    Functionality 3: Mission Execution
    --- VULNERABILITY 2: Missing Authentication ---
    --- VULNERABILITY 3: Command Injection ---
    Bandit Rule: B605 / B602 (starting a process with a shell / os.system)
    """
    print("\n--- [3] Mission Execution ---")

    # INTENTIONAL VULNERABILITY: Missing Authentication
    # The application proceeds to execute missions without checking if `is_authenticated == True`.

    target_host = input("Enter target ground control IP/host to ping: ")

    print("[*] Initiating pre-flight system diagnostics...")

    # INTENTIONAL VULNERABILITY: Command Injection
    # Unsanitized user input concatenated directly into a system shell command.
    command = f"ping -c 1 {target_host}"
    print(f"[*] Executing command: {command}")
    os.system(command)


def telemetry_display():
    """Functionality 4: Telemetry Display"""
    print("\n--- [4] Telemetry Display ---")
    print("=" * 30)
    print(" Battery Level : 88%")
    print(" Altitude      : 120 meters")
    print(" GPS Status    : 11 Satellites (Lock)")
    print(" Heading       : 180° SW")
    print(" Speed         : 14.2 m/s")
    print("=" * 30)


def log_storage():
    """Functionality 5: Log Storage"""
    print("\n--- [5] Log Storage ---")
    log_entry = input("Enter telemetry/mission log entry: ")

    # Write logs to local storage file
    log_dir = os.path.join(
        os.path.dirname(__file__), "..", "outputs", "drone_activity.log"
    )

    try:
        with open(log_dir, "a") as log_file:
            log_file.write(f"[{time.ctime()}] {log_entry}\n")
        print(f"[+] Log successfully saved to {log_dir}")
    except Exception as e:
        print(f"[-] Log storage failed: {e}")


def main():
    while True:
        print("\n===================================")
        print("    DRONE CONTROL SYSTEM (v1.0)    ")
        print("===================================")
        print("1. Drone Login")
        print("2. Upload Waypoints")
        print("3. Execute Mission")
        print("4. View Telemetry Display")
        print("5. Write System Log")
        print("6. Exit")

        choice = input("\nSelect an option (1-6): ")

        if choice == "1":
            drone_login()
        elif choice == "2":
            waypoint_upload()
        elif choice == "3":
            mission_execution()
        elif choice == "4":
            telemetry_display()
        elif choice == "5":
            log_storage()
        elif choice == "6":
            print("Exiting Drone Control System. Standby.")
            break
        else:
            print("Invalid choice! Please select 1-6.")


if __name__ == "__main__":
    main()
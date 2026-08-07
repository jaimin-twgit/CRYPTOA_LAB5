import os
from collections import Counter
from datetime import datetime

# Directory Paths
BASE_DIR = os.path.dirname(os.path.abspath(__file__))
DATASETS_DIR = os.path.join(BASE_DIR, "datasets")
LOG_FILE = os.path.join(BASE_DIR, "outputs", "activity.log")


def log_action(option_name):
    """Task 5: Record date, time, and menu selection in logs."""
    os.makedirs(os.path.dirname(LOG_FILE), exist_ok=True)
    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    with open(LOG_FILE, "a") as f:
        f.write(f"[{timestamp}] Selected Option: {option_name}\n")


def analyze_file():
    """Task 4: Read dataset file and display text metrics."""
    if not os.path.exists(DATASETS_DIR):
        print("Error: datasets directory does not exist.")
        return

    files = [f for f in os.listdir(DATASETS_DIR) if f.endswith(".txt")]
    if not files:
        print("No text files found in the datasets directory.")
        return

    print("\n--- Available Datasets ---")
    for idx, filename in enumerate(files, 1):
        print(f"{idx}. {filename}")

    try:
        choice = int(input("\nSelect a file number to analyze: "))
        if choice < 1 or choice > len(files):
            print("Invalid file selection.")
            return
        selected_file = files[choice - 1]
    except ValueError:
        print("Invalid input. Please enter a valid number.")
        return

    file_path = os.path.join(DATASETS_DIR, selected_file)

    with open(file_path, "r", encoding="utf-8") as f:
        content = f.read()

    # Calculations
    num_chars = len(content)
    num_words = len(content.split())
    num_lines = len(content.splitlines()) if content else 0
    unique_chars = len(set(content))

    # Frequency analysis for alphabetic letters
    letters_only = [c.lower() for c in content if c.isalpha()]
    letter_counts = Counter(letters_only)

    print(f"\n================ File Analysis: {selected_file} ================")
    print(f"Total Characters : {num_chars}")
    print(f"Total Words      : {num_words}")
    print(f"Total Lines      : {num_lines}")
    print(f"Unique Characters: {unique_chars}")
    print("\nLetter Frequency:")
    for letter, freq in sorted(letter_counts.items()):
        print(f"  {letter.upper()}: {freq}")
    print("==================================================================")


def main():
    """Task 3: Command Line Interface menu."""
    while True:
        print("\n=== CryptoLab CLI ===")
        print("1. Encrypt")
        print("2. Decrypt")
        print("3. Attack")
        print("4. Analyze File")
        print("5. Exit")

        choice = input("Enter choice (1-5): ").strip()

        if choice == "1":
            log_action("Encrypt")
            print("\n[INFO] Encrypt module: Coming Soon")
        elif choice == "2":
            log_action("Decrypt")
            print("\n[INFO] Decrypt module: Coming Soon")
        elif choice == "3":
            log_action("Attack")
            print("\n[INFO] Attack module: Coming Soon")
        elif choice == "4":
            log_action("Analyze File")
            analyze_file()
        elif choice == "5":
            log_action("Exit")
            print("Exiting application.")
            break
        else:
            print("Invalid choice. Please select 1 through 5.")


if __name__ == "__main__":
    main()
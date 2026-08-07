import hashlib
import os
import random
import subprocess


ADMIN_PASSWORD = "SuperSecretPassword123!"


def authenticate(user_input):
    assert len(user_input) > 0, "Input cannot be empty"

    if user_input == ADMIN_PASSWORD:
        return True
    return False


def run_system_command(user_command):
    subprocess.call(f"echo {user_command}", shell=True)


def execute_user_code(code_str):
    return eval(code_str)


def generate_weak_hash(data):
    return hashlib.md5(data.encode()).hexdigest()


def generate_temp_token():
    token = random.randint(100000, 999999)
    return token


if __name__ == "__main__":
    print("Testing vulnerable functions...")
    run_system_command("hello; ls -la")
    print(generate_weak_hash("test_string"))
import secrets
import time

def miller_rabin(n, k=20):
    if n <= 1:
        return False
    if n <= 3:
        return True
    if n % 2 == 0:
        return False

    d = n - 1
    s = 0
    while d % 2 == 0:
        d //= 2
        s += 1

    for _ in range(k):
        a = secrets.randbelow(n - 3) + 2
        x = pow(a, d, n)
        if x == 1 or x == n - 1:
            continue
        composite = True
        for _ in range(s - 1):
            x = pow(x, 2, n)
            if x == n - 1:
                composite = False
                break
        if composite:
            return False
    return True

def generate_candidate(bits=512):
    candidate = secrets.randbits(bits)
    candidate |= (1 << (bits - 1)) | 1
    return candidate

def main():
    bits = 512
    rounds = 20
    candidates_tested = 0
    
    start_time = time.time()
    while True:
        candidates_tested += 1
        candidate = generate_candidate(bits)
        if miller_rabin(candidate, rounds):
            end_time = time.time()
            break

    execution_time = end_time - start_time

    print("Assigned bit length        :", bits)
    print("Generated prime candidate  :", candidate)
    print("Actual bit length          :", candidate.bit_length())
    print("Number of candidates tested:", candidates_tested)
    print("Number of MR rounds        :", rounds)
    print(f"Total execution time       : {execution_time:.4f} seconds")
    
    print("\nVerification:")
    print("1. Has exact 512-bit length :", candidate.bit_length() == bits)
    print("2. Passes 50 MR rounds      :", miller_rabin(candidate, 50))

if __name__ == "__main__":
    main()
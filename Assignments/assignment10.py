import random
import string
import time

def mt19937_stream_cipher(data, seed):
    rng = random.Random(seed)
    keystream = bytes([rng.getrandbits(8) for _ in range(len(data))])
    return bytes([b ^ k for b, k in zip(data, keystream)])

def generate_token(timestamp):
    rng = random.Random(timestamp)
    return bytes([rng.getrandbits(8) for _ in range(16)])

def part_a_demo():
    print("PART A: STREAM CIPHER DEMO")
    
    test_msg = b"Hello Cryptography Lab!"
    test_seed = 12345
    encrypted = mt19937_stream_cipher(test_msg, test_seed)
    decrypted = mt19937_stream_cipher(encrypted, test_seed)
    print("Decryption Verified:", decrypted == test_msg)
    
    prefix_length = random.randint(5, 20)
    prefix = "".join(random.choices(string.ascii_letters, k=prefix_length)).encode()
    plaintext = prefix + b"A" * 14
    secret_seed = random.randint(0, 65535)
    
    ciphertext = mt19937_stream_cipher(plaintext, secret_seed)
    print("Generated Plaintext:", plaintext)
    print("Secret Seed (Hidden):", secret_seed)
    print("Ciphertext (Hex):", ciphertext.hex())
    
    found_seed = None
    recovered_pt = None
    target = b"A" * 14
    
    for seed in range(65536):
        pt = mt19937_stream_cipher(ciphertext, seed)
        if target in pt:
            found_seed = seed
            recovered_pt = pt
            break
            
    print("Recovered Seed:", found_seed)
    print("Recovered Plaintext:", recovered_pt)
    print("Match Status:", "SUCCESS" if found_seed == secret_seed else "FAILED")

def part_b_demo():
    print("\nPART B: PREDICTABLE TOKEN DEMO")
    
    real_timestamp = int(time.time())
    token = generate_token(real_timestamp)
    print("Timestamp T:", real_timestamp)
    print("Observed Token (Hex):", token.hex())
    
    search_start = real_timestamp - 300
    search_end = real_timestamp + 300
    tested_count = 0
    recovered_timestamp = None
    
    for cand in range(search_start, search_end + 1):
        tested_count += 1
        if generate_token(cand) == token:
            recovered_timestamp = cand
            break
            
    print("Total Timestamps Tested:", tested_count)
    print("Recovered Timestamp:", recovered_timestamp)
    
    verification_token = generate_token(recovered_timestamp)
    print("Token Verified:", verification_token == token)

if __name__ == "__main__":
    part_a_demo()
    part_b_demo()
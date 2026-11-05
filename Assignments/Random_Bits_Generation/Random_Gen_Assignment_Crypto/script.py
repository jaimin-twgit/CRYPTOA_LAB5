import math
import os

def generate_windows_rng(filename, size_mb=1):
    with open(filename, "wb") as f:
        f.write(os.urandom(size_mb * 1024 * 1024))

def analyze_file(filepath):
    if not os.path.exists(filepath):
        print(f"File missing: {filepath}")
        return

    with open(filepath, "rb") as f:
        data = f.read()

    total_bytes = len(data)
    if total_bytes == 0:
        return

    freq = [0] * 256
    ones_count = 0
    for byte in data:
        freq[byte] += 1
        ones_count += bin(byte).count("1")

    bit_ratio = ones_count / (total_bytes * 8)
    expected = total_bytes / 256.0
    chi_square = sum(((count - expected) ** 2) / expected for count in freq)

    entropy = 0.0
    for count in freq:
        if count > 0:
            p = count / total_bytes
            entropy -= p * math.log2(p)

    mean = sum(data) / total_bytes
    num = sum((data[i] - mean) * (data[i + 1] - mean) for i in range(total_bytes - 1))
    den = sum((b - mean) ** 2 for b in data)
    serial_corr = num / den if den != 0 else 0.0

    print(f"=== Analysis: {filepath} ===")
    print(f"Total Size: {total_bytes} bytes")
    print(f"Bit Ratio (1s): {bit_ratio:.6f}")
    print(f"Shannon Entropy: {entropy:.6f} / 8.0")
    print(f"Chi-Square Score: {chi_square:.2f}")
    print(f"Serial Correlation: {serial_corr:.6f}\n")

if __name__ == "__main__":
    generate_windows_rng("win_rng.bin")
    
    files = ["win_rng.bin", "openssl_rng.bin", "urandom_rng.bin"]
    for file_path in files:
        analyze_file(file_path)

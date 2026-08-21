from shift_cipher import decrypt

ENGLISH_FREQ = {
    'a': 0.08167, 'b': 0.01492, 'c': 0.02782, 'd': 0.04253, 'e': 0.12702,
    'f': 0.02228, 'g': 0.02015, 'h': 0.06094, 'i': 0.06966, 'j': 0.00153,
    'k': 0.00772, 'l': 0.04025, 'm': 0.02406, 'n': 0.06749, 'o': 0.07507,
    'p': 0.01929, 'q': 0.00095, 'r': 0.05987, 's': 0.06327, 't': 0.09056,
    'u': 0.02758, 'v': 0.00978, 'w': 0.02360, 'x': 0.00150, 'y': 0.01974,
    'z': 0.00074
}

def chi_square_attack(ciphertext):
    best_key = 0
    min_chi = float('inf')
    for key in range(26):
        decrypted = decrypt(ciphertext, key)
        letters = [c.lower() for c in decrypted if c.isalpha()]
        n = len(letters)
        if n == 0:
            continue
        counts = {chr(i + 97): 0 for i in range(26)}
        for c in letters:
            counts[c] += 1
        chi_sq = 0.0
        for char in counts:
            expected = n * ENGLISH_FREQ[char]
            observed = counts[char]
            chi_sq += ((observed - expected) ** 2) / expected
        if chi_sq < min_chi:
            min_chi = chi_sq
            best_key = key
    return best_key
import re
from shift_cipher import decrypt

def load_dictionary(dict_path):
    with open(dict_path, 'r', encoding='utf-8') as f:
        return set(word.strip().lower() for word in f if word.strip())

def dictionary_attack(ciphertext, word_set):
    best_key = 0
    max_score = -1
    for key in range(26):
        decrypted = decrypt(ciphertext, key)
        words = re.findall(r'\b[a-zA-Z]+\b', decrypted.lower())
        score = sum(1 for w in words if w in word_set)
        if score > max_score:
            max_score = score
            best_key = key
    return best_key
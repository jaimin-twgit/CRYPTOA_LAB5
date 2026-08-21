import os
from shift_cipher import encrypt
from brute_force_dictionary import load_dictionary, dictionary_attack
from chi_square_attack import chi_square_attack

def main():
    dict_path = os.path.join(os.path.dirname(__file__), '..', 'dictionary', 'english_words.txt')
    word_set = load_dictionary(dict_path)
    test_cases = [
        ("THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG", 7),
        ("CRYPTOGRAPHY AND NETWORK SECURITY", 13),
        ("SHORT TEXT", 3),
        ("X", 20)
    ]
    print(f"{'Test Case':<10} | {'Actual Key':<10} | {'Dictionary Key':<15} | {'Chi-Square Key':<15} | {'Dictionary Correct?':<20} | {'Chi-Square Correct?'}")
    print("-" * 90)
    for idx, (plain, key) in enumerate(test_cases, 1):
        cipher = encrypt(plain, key)
        dict_key = dictionary_attack(cipher, word_set)
        chi_key = chi_square_attack(cipher)
        dict_corr = "Yes" if dict_key == key else "No"
        chi_corr = "Yes" if chi_key == key else "No"
        print(f"{idx:<10} | {key:<10} | {dict_key:<15} | {chi_key:<15} | {dict_corr:<20} | {chi_corr}")

if __name__ == "__main__":
    main()
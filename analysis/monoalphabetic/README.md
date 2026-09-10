# Monoalphabetic Substitution Cipher Cryptanalysis

## Group Members

- **Priyanshu Gupta** — 2024UCP1467
- **Jaimin** — 2024UCP1302

## Objective

The objective of this assignment is to implement a monoalphabetic
substitution cipher and study how it can be cryptanalyzed using
frequency analysis, word-frequency analysis, pattern analysis and
iterative key recovery.

## Files

- `monoalphabetic.cpp` - Performs monoalphabetic substitution
  encryption and frequency analysis.
- `cryptanalysis.cpp` - Performs frequency analysis, word-frequency
  analysis and pattern analysis and displays partial plaintext.
- `key_recovery.cpp` - Performs iterative key recovery, displays the
  recovered plaintext and verifies the recovered solution.

## Dataset

The plaintext used for the experiment is stored in:

`datasets/group5/plaintext.txt`

The encrypted text is generated and stored in:

`datasets/group5/ciphertext.txt`

The recovered plaintext is stored in:

`datasets/group5/recovered_plaintext.txt`

## Cryptanalysis Techniques

### 1. Frequency Analysis

The frequency of each letter in the ciphertext is calculated. Since
monoalphabetic substitution keeps the same letter relationships, the
frequency distribution can be compared with normal English letter
frequencies to make initial guesses.

### 2. Word Frequency Analysis

The program counts how frequently different words occur in the
ciphertext. Common words can help in identifying possible plaintext
words and improving the substitution key.

### 3. Pattern Analysis

Words are represented according to their repeated-letter pattern.
For example, a word such as `HELLO` has the pattern:

`0.1.2.2.3.`

This helps in finding plaintext words having a similar structure.

### 4. Iterative Key Recovery

An initial substitution key is generated using frequency information.
The key is then refined iteratively by changing the guessed
substitutions and observing the resulting partial plaintext.

### 5. Verification

After recovering the plaintext, it is re-encrypted using the recovered
substitution key. The regenerated ciphertext is then compared with the
original ciphertext.

If both ciphertexts are the same, the recovered solution is verified.

## Execution

### Encryption

Compile:

```bash
g++ analysis/monoalphabetic/monoalphabetic.cpp -o monoalphabetic
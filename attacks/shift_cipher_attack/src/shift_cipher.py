def encrypt(text, key):
    result = []
    for char in text:
        if char.isalpha():
            base = ord('A') if char.isupper() else ord('a')
            result.append(chr((ord(char) - base + key) % 26 + base))
        else:
            result.append(char)
    return "".join(result)

def decrypt(text, key):
    return encrypt(text, -key)
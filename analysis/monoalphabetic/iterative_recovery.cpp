#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cctype>

using namespace std;

// ============================================================
// READ FILE
// ============================================================

string readFile(const string& filename) {

    ifstream file(filename);

    if (!file) {
        cerr << "Error: Cannot open " << filename << endl;
        return "";
    }

    string text;
    string line;

    while (getline(file, line)) {
        text += line;
        text += '\n';
    }

    file.close();

    return text;
}

// ============================================================
// APPLY SUBSTITUTION
// ============================================================

string apply_substitution(
    const string& ciphertext,
    const map<char, char>& key) {

    string plaintext;

    for (char ch : ciphertext) {

        if (isupper(static_cast<unsigned char>(ch))) {

            if (key.count(ch))
                plaintext += key.at(ch);
            else
                plaintext += '_';
        }

        else if (islower(static_cast<unsigned char>(ch))) {

            char upper =
                toupper(static_cast<unsigned char>(ch));

            if (key.count(upper)) {

                plaintext += tolower(
                    static_cast<unsigned char>(
                        key.at(upper)
                    )
                );
            }
            else {
                plaintext += '_';
            }
        }

        else {
            plaintext += ch;
        }
    }

    return plaintext;
}

// ============================================================
// SWAP TWO SUBSTITUTIONS
// ============================================================

void swap_mapping(
    map<char, char>& key,
    char cipher1,
    char cipher2) {

    char temp = key[cipher1];

    key[cipher1] = key[cipher2];
    key[cipher2] = temp;
}

// ============================================================
// DISPLAY CURRENT KEY
// ============================================================

void display_key(const map<char, char>& key) {

    cout << "\n----------------------------------------\n";
    cout << "Current substitution key\n";
    cout << "----------------------------------------\n";

    cout << "Cipher : ABCDEFGHIJKLMNOPQRSTUVWXYZ\n";
    cout << "Plain  : ";

    for (char c = 'A'; c <= 'Z'; c++) {

        if (key.count(c))
            cout << key.at(c);
        else
            cout << '_';
    }

    cout << "\n";
}

// ============================================================
// DISPLAY PARTIAL PLAINTEXT
// ============================================================

void display_partial_plaintext(
    const string& ciphertext,
    const map<char, char>& key) {

    cout << "\n----------------------------------------\n";
    cout << "Partial plaintext\n";
    cout << "----------------------------------------\n\n";

    cout << apply_substitution(ciphertext, key)
         << "\n";
}

// ============================================================
// ITERATIVE KEY RECOVERY
// ============================================================

void iterative_key_recovery(
    const string& ciphertext,
    map<char, char>& key) {

    cout << "\n========================================\n";
    cout << "       ITERATIVE KEY RECOVERY\n";
    cout << "========================================\n";

    cout << "\nThe key is refined by replacing incorrect\n";
    cout << "substitution guesses and observing the\n";
    cout << "resulting plaintext.\n";

    while (true) {

        display_key(key);

        display_partial_plaintext(
            ciphertext,
            key
        );

        cout << "\nEnter two ciphertext letters to swap\n";
        cout << "or enter 0 to finish.\n";

        cout << "First letter: ";

        char a;
        cin >> a;

        if (a == '0')
            break;

        cout << "Second letter: ";

        char b;
        cin >> b;

        a = toupper(static_cast<unsigned char>(a));
        b = toupper(static_cast<unsigned char>(b));

        if (a < 'A' || a > 'Z' ||
            b < 'A' || b > 'Z') {

            cout << "Invalid letters.\n";
            continue;
        }

        swap_mapping(key, a, b);

        cout << "\nSubstitution updated.\n";
    }
}

// ============================================================
// CREATE REVERSE KEY
// ============================================================

map<char, char> reverse_key(
    const map<char, char>& key) {

    map<char, char> reverseKey;

    for (const auto& entry : key) {

        reverseKey[entry.second] =
            entry.first;
    }

    return reverseKey;
}

// ============================================================
// RE-ENCRYPT RECOVERED PLAINTEXT
// ============================================================

string re_encrypt(
    const string& plaintext,
    const map<char, char>& key) {

    map<char, char> reverseKey =
        reverse_key(key);

    string ciphertext;

    for (char ch : plaintext) {

        if (isupper(static_cast<unsigned char>(ch))) {

            if (reverseKey.count(ch))
                ciphertext += reverseKey[ch];
            else
                ciphertext += ch;
        }

        else if (islower(static_cast<unsigned char>(ch))) {

            char upper =
                toupper(static_cast<unsigned char>(ch));

            if (reverseKey.count(upper)) {

                ciphertext += tolower(
                    static_cast<unsigned char>(
                        reverseKey[upper]
                    )
                );
            }
            else {
                ciphertext += ch;
            }
        }

        else {
            ciphertext += ch;
        }
    }

    return ciphertext;
}

// ============================================================
// VERIFICATION
// ============================================================

bool verify_solution(
    const string& originalCiphertext,
    const string& recoveredPlaintext,
    const map<char, char>& key) {

    string regeneratedCiphertext =
        re_encrypt(
            recoveredPlaintext,
            key
        );

    return regeneratedCiphertext ==
           originalCiphertext;
}

// ============================================================
// MAIN
// ============================================================

int main() {

    string ciphertext =
        readFile(
            "datasets/group5/ciphertext.txt"
        );

    if (ciphertext.empty()) {

        cerr << "Ciphertext is empty."
             << endl;

        return 1;
    }

    // --------------------------------------------------------
    // Initial frequency-based key
    //
    // This is the starting hypothesis.
    // It can be refined interactively.
    // --------------------------------------------------------

    map<char, char> key = {

        {'A','E'}, {'B','T'}, {'C','A'},
        {'D','O'}, {'E','I'}, {'F','N'},
        {'G','S'}, {'H','R'}, {'I','H'},
        {'J','D'}, {'K','L'}, {'L','C'},
        {'M','U'}, {'N','M'}, {'O','W'},
        {'P','F'}, {'Q','G'}, {'R','Y'},
        {'S','P'}, {'T','B'}, {'U','V'},
        {'V','K'}, {'W','J'}, {'X','X'},
        {'Y','Q'}, {'Z','Z'}
    };

    // --------------------------------------------------------
    // Iterative refinement
    // --------------------------------------------------------

    iterative_key_recovery(
        ciphertext,
        key
    );

    // --------------------------------------------------------
    // Final recovered plaintext
    // --------------------------------------------------------

    string recoveredPlaintext =
        apply_substitution(
            ciphertext,
            key
        );

    cout << "\n========================================\n";
    cout << "        FINAL RECOVERED PLAINTEXT\n";
    cout << "========================================\n\n";

    cout << recoveredPlaintext << "\n";

    // --------------------------------------------------------
    // Save recovered plaintext
    // --------------------------------------------------------

    ofstream outputFile(
        "datasets/group5/recovered_plaintext.txt"
    );

    if (outputFile) {

        outputFile << recoveredPlaintext;
        outputFile.close();

        cout << "\nRecovered plaintext saved to:\n";
        cout << "datasets/group5/recovered_plaintext.txt\n";
    }

    // --------------------------------------------------------
    // Verification
    // --------------------------------------------------------

    cout << "\n========================================\n";
    cout << "             VERIFICATION\n";
    cout << "========================================\n";

    if (verify_solution(
            ciphertext,
            recoveredPlaintext,
            key)) {

        cout << "\nSUCCESS!\n";
        cout << "Re-encrypted recovered plaintext matches\n";
        cout << "the original ciphertext.\n";
    }
    else {

        cout << "\nVerification not successful yet.\n";
        cout << "The substitution key still needs refinement.\n";
    }

    return 0;
}
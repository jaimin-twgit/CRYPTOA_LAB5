#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

// ============================================================
// ALPHABETS
// ============================================================

const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

// Expected English frequency order
const string ENGLISH_FREQUENCY =
    "ETAOINSHRDLCUMWFGYPBVKJXQZ";

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
// FREQUENCY ANALYSIS
// ============================================================

vector<char> getFrequencyOrder(const string& ciphertext) {

    int frequency[26] = {0};

    for (char ch : ciphertext) {

        if (isalpha(static_cast<unsigned char>(ch))) {

            ch = toupper(static_cast<unsigned char>(ch));

            frequency[ch - 'A']++;
        }
    }

    vector<pair<char, int>> frequencies;

    for (int i = 0; i < 26; i++) {

        frequencies.push_back({
            static_cast<char>('A' + i),
            frequency[i]
        });
    }

    sort(
        frequencies.begin(),
        frequencies.end(),
        [](const pair<char, int>& a,
           const pair<char, int>& b) {

            return a.second > b.second;
        }
    );

    vector<char> order;

    for (const auto& entry : frequencies) {
        order.push_back(entry.first);
    }

    return order;
}

// ============================================================
// CREATE INITIAL KEY USING FREQUENCY ANALYSIS
// ============================================================

map<char, char> createInitialKey(
    const vector<char>& cipherOrder) {

    map<char, char> key;

    for (int i = 0; i < 26; i++) {

        key[cipherOrder[i]] =
            ENGLISH_FREQUENCY[i];
    }

    return key;
}

// ============================================================
// APPLY SUBSTITUTION
// ============================================================

string apply_substitution(
    const string& ciphertext,
    const map<char, char>& key) {

    string plaintext = "";

    for (char ch : ciphertext) {

        if (isupper(static_cast<unsigned char>(ch))) {

            if (key.find(ch) != key.end()) {
                plaintext += key.at(ch);
            }
            else {
                plaintext += '_';
            }
        }

        else if (islower(static_cast<unsigned char>(ch))) {

            char upper =
                toupper(static_cast<unsigned char>(ch));

            if (key.find(upper) != key.end()) {

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
// DISPLAY KEY
// ============================================================

void display_key(const map<char, char>& key) {

    cout << "\n========================================\n";
    cout << "        RECOVERED SUBSTITUTION KEY\n";
    cout << "========================================\n\n";

    cout << "Cipher : ABCDEFGHIJKLMNOPQRSTUVWXYZ\n";
    cout << "Plain  : ";

    for (char c : ALPHABET) {

        if (key.find(c) != key.end())
            cout << key.at(c);
        else
            cout << '_';
    }

    cout << "\n";
}

// ============================================================
// RE-ENCRYPTION
// ============================================================

string re_encrypt(
    const string& plaintext,
    const map<char, char>& key) {

    map<char, char> reverseKey;

    for (const auto& entry : key) {

        reverseKey[entry.second] = entry.first;
    }

    string ciphertext = "";

    for (char ch : plaintext) {

        if (isupper(static_cast<unsigned char>(ch))) {

            if (reverseKey.find(ch) != reverseKey.end())
                ciphertext += reverseKey[ch];
            else
                ciphertext += ch;
        }

        else if (islower(static_cast<unsigned char>(ch))) {

            char upper =
                toupper(static_cast<unsigned char>(ch));

            if (reverseKey.find(upper) != reverseKey.end()) {

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
// VERIFY SOLUTION
// ============================================================

bool verify_solution(
    const string& originalCiphertext,
    const string& recoveredPlaintext,
    const map<char, char>& key) {

    string regeneratedCiphertext =
        re_encrypt(recoveredPlaintext, key);

    return regeneratedCiphertext == originalCiphertext;
}

// ============================================================
// MAIN
// ============================================================

int main() {

    string ciphertext =
        readFile("datasets/group5/ciphertext.txt");

    if (ciphertext.empty()) {

        cerr << "Ciphertext is empty or could not be read."
             << endl;

        return 1;
    }

    cout << "\n========================================\n";
    cout << "       MONOALPHABETIC KEY RECOVERY\n";
    cout << "========================================\n";

    // --------------------------------------------------------
    // 1. Frequency Analysis
    // --------------------------------------------------------

    vector<char> cipherOrder =
        getFrequencyOrder(ciphertext);

    cout << "\nCiphertext frequency order:\n";

    for (char c : cipherOrder)
        cout << c << " ";

    cout << "\n";

    // --------------------------------------------------------
    // 2. Generate Initial Key
    // --------------------------------------------------------

    map<char, char> key =
        createInitialKey(cipherOrder);

    display_key(key);

    // --------------------------------------------------------
    // 3. Generate Partial Plaintext
    // --------------------------------------------------------

    string partialPlaintext =
        apply_substitution(ciphertext, key);

    cout << "\n========================================\n";
    cout << "          PARTIAL PLAINTEXT\n";
    cout << "========================================\n\n";

    cout << partialPlaintext << "\n";

    // --------------------------------------------------------
    // 4. Save Partial Plaintext
    // --------------------------------------------------------

    ofstream partialFile(
        "datasets/group5/recovered_plaintext.txt"
    );

    if (partialFile) {

        partialFile << partialPlaintext;
        partialFile.close();
    }

    // --------------------------------------------------------
    // 5. Verification
    // --------------------------------------------------------

    bool verified =
        verify_solution(
            ciphertext,
            partialPlaintext,
            key
        );

    cout << "\n========================================\n";
    cout << "             VERIFICATION\n";
    cout << "========================================\n\n";

    if (verified) {

        cout << "SUCCESS: Re-encrypted plaintext matches "
             << "the original ciphertext.\n";
    }
    else {

        cout << "NOTE: Frequency-based key is only an "
             << "initial hypothesis.\n";

        cout << "Manual/iterative substitution refinement "
             << "is required for complete recovery.\n";
    }

    cout << "\n========================================\n";
    cout << "Key recovery stage completed.\n";
    cout << "========================================\n";

    return 0;
}
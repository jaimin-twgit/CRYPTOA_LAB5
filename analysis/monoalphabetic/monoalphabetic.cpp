#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <iomanip>

using namespace std;

// ============================================================
// MONOALPHABETIC SUBSTITUTION KEY
// ============================================================

const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string KEY      = "QWERTYUIOPASDFGHJKLZXCVBNM";

// ============================================================
// ENCRYPTION
// ============================================================

string encryptText(const string& plaintext) {

    string ciphertext = "";

    for (char ch : plaintext) {

        if (isupper(static_cast<unsigned char>(ch))) {

            int index = ch - 'A';
            ciphertext += KEY[index];
        }

        else if (islower(static_cast<unsigned char>(ch))) {

            int index = ch - 'a';
            ciphertext += tolower(KEY[index]);
        }

        else {

            ciphertext += ch;
        }
    }

    return ciphertext;
}

// ============================================================
// FREQUENCY ANALYSIS
// ============================================================

void frequency_analysis(const string& ciphertext) {

    int frequency[26] = {0};
    int totalLetters = 0;

    for (char ch : ciphertext) {

        if (isalpha(static_cast<unsigned char>(ch))) {

            ch = toupper(static_cast<unsigned char>(ch));

            frequency[ch - 'A']++;
            totalLetters++;
        }
    }

    cout << "\n========================================\n";
    cout << "        FREQUENCY ANALYSIS\n";
    cout << "========================================\n\n";

    cout << left
         << setw(10) << "Letter"
         << setw(10) << "Count"
         << "Frequency\n";

    cout << "----------------------------------------\n";

    for (int i = 0; i < 26; i++) {

        double percentage = 0.0;

        if (totalLetters > 0) {
            percentage =
                (static_cast<double>(frequency[i]) / totalLetters) * 100.0;
        }

        cout << left
             << setw(10) << static_cast<char>('A' + i)
             << setw(10) << frequency[i]
             << fixed << setprecision(2)
             << percentage << "%\n";
    }

    cout << "\nTotal alphabetic characters: "
         << totalLetters << "\n";
}

// ============================================================
// MAIN
// ============================================================

int main() {

    // --------------------------------------------------------
    // Read plaintext
    // --------------------------------------------------------

    ifstream inputFile("datasets/group5/plaintext.txt");

    if (!inputFile) {

        cerr << "Error: Could not open datasets/group5/plaintext.txt"
             << endl;

        return 1;
    }

    string plaintext;
    string line;

    while (getline(inputFile, line)) {

        plaintext += line;
        plaintext += '\n';
    }

    inputFile.close();

    // --------------------------------------------------------
    // Encrypt plaintext
    // --------------------------------------------------------

    string ciphertext = encryptText(plaintext);

    // --------------------------------------------------------
    // Display encryption result
    // --------------------------------------------------------

    cout << "\n========================================\n";
    cout << "      MONOALPHABETIC ENCRYPTION\n";
    cout << "========================================\n\n";

    cout << ciphertext << endl;

    // --------------------------------------------------------
    // Frequency Analysis
    // --------------------------------------------------------

    frequency_analysis(ciphertext);

    // --------------------------------------------------------
    // Save ciphertext
    // --------------------------------------------------------

    ofstream outputFile("datasets/group5/ciphertext.txt");

    if (!outputFile) {

        cerr << "Error: Could not create "
             << "datasets/group5/ciphertext.txt"
             << endl;

        return 1;
    }

    outputFile << ciphertext;

    outputFile.close();

    cout << "\n========================================\n";
    cout << "Ciphertext saved successfully!\n";
    cout << "========================================\n";

    return 0;
}
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cctype>

using namespace std;

// ============================================================
// STRUCTURE FOR FREQUENCY INFORMATION
// ============================================================

struct FrequencyEntry {
    char letter;
    int count;
    double frequency;
};

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

vector<FrequencyEntry> frequency_analysis(const string& text) {

    int frequency[26] = {0};
    int totalLetters = 0;

    for (char ch : text) {

        if (isalpha(static_cast<unsigned char>(ch))) {

            ch = toupper(static_cast<unsigned char>(ch));

            frequency[ch - 'A']++;
            totalLetters++;
        }
    }

    vector<FrequencyEntry> result;

    for (int i = 0; i < 26; i++) {

        double percentage = 0.0;

        if (totalLetters > 0) {
            percentage =
                (static_cast<double>(frequency[i]) / totalLetters) * 100.0;
        }

        result.push_back({
            static_cast<char>('A' + i),
            frequency[i],
            percentage
        });
    }

    // Sort from most frequent to least frequent
    sort(result.begin(), result.end(),
         [](const FrequencyEntry& a, const FrequencyEntry& b) {

             return a.count > b.count;
         });

    return result;
}

// ============================================================
// DISPLAY FREQUENCY ANALYSIS
// ============================================================

void display_frequency_analysis(
    const vector<FrequencyEntry>& frequencies) {

    cout << "\n========================================\n";
    cout << "        FREQUENCY ANALYSIS\n";
    cout << "========================================\n\n";

    cout << left
         << setw(10) << "Letter"
         << setw(10) << "Count"
         << "Frequency\n";

    cout << "----------------------------------------\n";

    for (const auto& entry : frequencies) {

        cout << left
             << setw(10) << entry.letter
             << setw(10) << entry.count
             << fixed << setprecision(2)
             << entry.frequency << "%\n";
    }
}

// ============================================================
// WORD FREQUENCY ANALYSIS
// ============================================================

map<string, int> word_frequency_analysis(const string& text) {

    map<string, int> wordFrequency;

    string word = "";

    for (char ch : text) {

        if (isalpha(static_cast<unsigned char>(ch))) {

            word += tolower(static_cast<unsigned char>(ch));
        }

        else {

            if (!word.empty()) {

                wordFrequency[word]++;
                word.clear();
            }
        }
    }

    if (!word.empty()) {
        wordFrequency[word]++;
    }

    return wordFrequency;
}

// ============================================================
// DISPLAY WORD FREQUENCIES
// ============================================================

void display_word_frequency(
    const map<string, int>& wordFrequency) {

    vector<pair<string, int>> words(
        wordFrequency.begin(),
        wordFrequency.end()
    );

    sort(words.begin(), words.end(),
         [](const pair<string, int>& a,
            const pair<string, int>& b) {

             return a.second > b.second;
         });

    cout << "\n========================================\n";
    cout << "       WORD FREQUENCY ANALYSIS\n";
    cout << "========================================\n\n";

    cout << left
         << setw(25) << "Word"
         << "Count\n";

    cout << "----------------------------------------\n";

    int displayed = 0;

    for (const auto& entry : words) {

        cout << left
             << setw(25) << entry.first
             << entry.second << "\n";

        displayed++;

        // Display top 20 words
        if (displayed == 20)
            break;
    }
}

// ============================================================
// GENERATE PATTERN OF A WORD
// ============================================================

string getPattern(const string& word) {

    map<char, int> mapping;

    int nextNumber = 0;

    string pattern = "";

    for (char ch : word) {

        ch = tolower(static_cast<unsigned char>(ch));

        if (mapping.find(ch) == mapping.end()) {

            mapping[ch] = nextNumber++;
        }

        pattern += to_string(mapping[ch]);
        pattern += ".";
    }

    return pattern;
}

// ============================================================
// PATTERN ANALYSIS
// ============================================================

map<string, vector<string>> pattern_analysis(
    const map<string, int>& wordFrequency) {

    map<string, vector<string>> patterns;

    for (const auto& entry : wordFrequency) {

        string pattern = getPattern(entry.first);

        patterns[pattern].push_back(entry.first);
    }

    return patterns;
}

// ============================================================
// DISPLAY PATTERN ANALYSIS
// ============================================================

void display_pattern_analysis(
    const map<string, vector<string>>& patterns) {

    cout << "\n========================================\n";
    cout << "          PATTERN ANALYSIS\n";
    cout << "========================================\n\n";

    for (const auto& entry : patterns) {

        cout << "Pattern: " << entry.first << "\n";
        cout << "Words: ";

        for (const string& word : entry.second) {
            cout << word << " ";
        }

        cout << "\n\n";
    }
}

// ============================================================
// DISPLAY PARTIAL PLAINTEXT
// ============================================================

string apply_substitution(
    const string& ciphertext,
    const map<char, char>& substitution) {

    string plaintext = "";

    for (char ch : ciphertext) {

        if (isupper(static_cast<unsigned char>(ch))) {

            char upper = ch;

            if (substitution.find(upper) != substitution.end()) {
                plaintext += substitution.at(upper);
            }
            else {
                plaintext += '_';
            }
        }

        else if (islower(static_cast<unsigned char>(ch))) {

            char upper = toupper(
                static_cast<unsigned char>(ch)
            );

            if (substitution.find(upper) != substitution.end()) {

                plaintext += tolower(
                    static_cast<unsigned char>(
                        substitution.at(upper)
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

void display_partial_plaintext(
    const string& ciphertext,
    const map<char, char>& substitution) {

    cout << "\n========================================\n";
    cout << "         PARTIAL PLAINTEXT\n";
    cout << "========================================\n\n";

    cout << apply_substitution(
        ciphertext,
        substitution
    ) << "\n";
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
    cout << " MONOALPHABETIC CIPHER CRYPTANALYSIS\n";
    cout << "========================================\n";

    // --------------------------------------------------------
    // 1. Frequency Analysis
    // --------------------------------------------------------

    vector<FrequencyEntry> frequencies =
        frequency_analysis(ciphertext);

    display_frequency_analysis(frequencies);

    // --------------------------------------------------------
    // 2. Word Frequency Analysis
    // --------------------------------------------------------

    map<string, int> wordFrequency =
        word_frequency_analysis(ciphertext);

    display_word_frequency(wordFrequency);

    // --------------------------------------------------------
    // 3. Pattern Analysis
    // --------------------------------------------------------

    map<string, vector<string>> patterns =
        pattern_analysis(wordFrequency);

    display_pattern_analysis(patterns);

    // --------------------------------------------------------
    // 4. Example Partial Substitution
    // --------------------------------------------------------

    map<char, char> sampleSubstitution;

    // Initial frequency-based hypothesis
    // Most frequent English letter -> E
    if (!frequencies.empty()) {
        sampleSubstitution[frequencies[0].letter] = 'E';
    }

    display_partial_plaintext(
        ciphertext,
        sampleSubstitution
    );

    cout << "\n========================================\n";
    cout << "Cryptanalysis modules completed.\n";
    cout << "========================================\n";

    return 0;
}
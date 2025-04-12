#include <iostream>
#include <string>

using namespace std;

// Selected language ID by user
int languageID = 1;

// Language 1: a^n b^n
bool isL1(const string& s) {
    int i = 0;
    while (i < s.length() && s[i] == 'a') i++;
    int aCount = i;
    while (i < s.length() && s[i] == 'b') i++;
    int bCount = s.length() - aCount;
    return (i == s.length() && aCount == bCount);
}

// Language 2: a^n b^m c^n
bool isL2(const string& s) {
    int i = 0;
    while (i < s.length() && s[i] == 'a') i++;
    int aCount = i;
    int j = i;
    while (j < s.length() && s[j] == 'b') j++;
    int k = j;
    while (k < s.length() && s[k] == 'c') k++;
    int cCount = k - j;
    return (k == s.length() && aCount == cCount);
}

// Language 3: (ab)^n
bool isL3(const string& s) {
    if (s.length() % 2 != 0) return false;
    for (size_t i = 0; i < s.length(); i += 2) {
        if (s[i] != 'a' || s[i + 1] != 'b') return false;
    }
    return true;
}

// Language 4: equal number of a’s and b’s (in any order)
bool isL4(const string& s) {
    int a = 0, b = 0;
    for (char ch : s) {
        if (ch == 'a') a++;
        if (ch == 'b') b++;
    }
    return a == b;
}

// Language 5: a^m a^n
bool isL5(const std::string& s) {
    int i = 0;
    while (i < s.length() && s[i] == 'a') i++;
    int aCount = i;
    while (i < s.length() && s[i] == 'b') i++;
    return (i == s.length() && aCount % 2 == 0);
}

bool isInLanguage(const string& s) {
    switch (languageID) {
    case 1: return isL1(s);
    case 2: return isL2(s);
    case 3: return isL3(s);
    case 4: return isL4(s);
    case 5: return isL5(s);
    default: return false;
    }
}

void pumpingLemmaDemo(string word, int p) {
    cout << "\nPumping Lemma Demonstrator\n";
    cout << "Word: " << word << "\nPumping length: " << p << endl;

    if (word.length() < p) {
        cout << "Word is too short. Must be at least length p.\n";
        return;
    }

    bool disproved = false;

    for (int i = 1; i <= p; ++i) {
        for (int j = i; j <= p; ++j) {
            string x = word.substr(0, i);
            string y = word.substr(i, j - i);
            string z = word.substr(j);

            if (y.empty()) continue;

            cout << "\nTrying decomposition:\n";
            cout << "x = \"" << x << "\", y = \"" << y << "\", z = \"" << z << "\"\n";

            for (int k = 0; k <= 3; ++k) {
                string pumped = x + string(k, ' ').replace(0, k, y) + z;
                bool inLang = isInLanguage(pumped);
                cout << "  i=" << k << ": " << pumped << (inLang ? " In L" : " Not in L") << endl;
                if (k != 1 && !inLang) {
                    disproved = true;
                }
            }
        }
    }

    cout << "\nResult: ";
    if (disproved) {
        cout << "The language is NOT regular (irregular) ❌\n";
    }
    else {
        cout << "Could not disprove regularity using pumping lemma ✅\n";
    }
}

int chooseLanguage() {
    int choice;
    while (true) {
        cout << "\nChoose a language:\n";
        cout << "1. L = { a^n b^n | n => 0 }\n";
        cout << "2. L = { a^n b^m c^n | n, m => 0 }\n";
        cout << "3. L = { (ab)^n | n => 0 }\n";
        cout << "4. L = { strings with equal number of a’s and b’s }\n";
        cout << "5. L = { a^m b^n | m, n => 0 and m is even }\n";
        cout << "Enter choice (1 - 5): ";
        cin >> choice;

        if (cin.fail() || choice < 1 || choice > 5) {
            cin.clear(); // clear input
            cin.ignore(10000, '\n'); // discard invalid input
            cout << "Invalid input. Please enter a number between 1 and 5.\n";
        }
        else {
            return choice;
        }
    }
}

void getWordAndP(std::string& word, int& p) {
    // Input word (only letters)
    while (true) {
        cout << "\nEnter a word from the language: ";
        cin >> word;
        bool valid = true;
        for (char ch : word) {
            if (!isalpha(ch) || !islower(ch)) {
                valid = false;
                break;
            }
        }
        if (!valid) {
            std::cout << "Invalid word. Use only lowercase letters a-z.\n";
        }
        else {
            break;
        }
    }

    // Input pumping length (positive int)
    while (true) {
        cout << "Enter pumping length p (positive integer): ";
        cin >> p;
        if (cin.fail() || p <= 0) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a positive number.\n";
        }
        else {
            break;
        }
    }
}

int main() {
    languageID = chooseLanguage();
    string word;
    int p;
    getWordAndP(word, p);
    pumpingLemmaDemo(word, p);

    int x;
    cout << "Enter any input to exit";
    cin >> x;

    return 0;
}


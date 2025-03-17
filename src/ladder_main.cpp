#include "ladder.h"

int main() {
    set<string> word_list;
    load_words(word_list, "words.txt");
    
    if (word_list.empty()) {
        cerr << "Error: Dictionary is empty. Please check the words.txt file." << endl;
        return 1;
    }
    cout << "Enter 'verify' to run verification tests or 'exit' to quit." << endl;
    
    string start_word, end_word;
    
    while (true) {
        cout << "\nEnter start word (or command): ";
        cin >> start_word;
        
        // Check for commands
        if (start_word == "exit")
            break;
        else if (start_word == "verify") {
            verify_word_ladder();
            continue;
        }
        
        cout << "Enter end word: ";
        cin >> end_word;
        
        if (start_word == end_word) {
            error(start_word, end_word, "Start and end words are the same");
            continue;
        }
        vector<string> ladder = generate_word_ladder(start_word, end_word, word_list);
        print_word_ladder(ladder);
    }
    return 0;
}

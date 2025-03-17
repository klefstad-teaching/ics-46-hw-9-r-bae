#include "ladder.h"

void error(string word1, string word2, string msg) {
    cout << "Error from '" << word1 << "' to '" << word2 << "': " << msg << endl;
}

// Check if edit distance between two strings is within a specified limit
bool edit_distance_within(const string& str1, const string& str2, int d) {
    if (abs(int(str1.length()) - int(str2.length())) > d)
        return false;
    
    int m = str1.length();
    int n = str2.length();
    
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    
    for (int i = 0; i <= m; ++i)
        dp[i][0] = i;
    for (int j = 0; j <= n; ++j)
        dp[0][j] = j;
    
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (tolower(str1[i - 1]) == tolower(str2[j - 1]))
                dp[i][j] = dp[i - 1][j - 1];
            else {
                dp[i][j] = 1 + min({dp[i - 1][j],      // Delete
                                   dp[i][j - 1],       // Insert
                                   dp[i - 1][j - 1]}); // Replace
            }
            if (i == m && j == n && dp[i][j] > d)
                return false;
        }
    }
    return dp[m][n] <= d;
}

// Check if two words are adjacent
bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream file(file_name);
    if (!file) {
        cerr << "Error: Could not open dictionary file: " << file_name << endl;
        return;
    }
    
    string word;
    while (file >> word) {
        string lowercase_word = word;
        for (char& c : lowercase_word)
            c = tolower(c);
        word_list.insert(lowercase_word);
    }
    file.close();
}

// Print the word ladder
void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }
    
    cout << "Word ladder found:" << endl;
    for (size_t i = 0; i < ladder.size(); ++i) {
        cout << ladder[i];
        if (i < ladder.size() - 1)
            cout << " → ";
    }
    cout << endl;
    cout << "Length of ladder: " << ladder.size() << endl;
}

// Test function to verify word ladder implementation
void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");
    
    struct TestCase {
        string start;
        string end;
        int expected_length;
    };
    
    vector<TestCase> test_cases = {
        {"cat", "dog", 4},
        {"marty", "curls", 6},
        {"code", "data", 6},
        {"work", "play", 6},
        {"sleep", "awake", 8},
        {"car", "cheat", 4}
    };
    
    // Test each case
    for (const auto& test : test_cases) {
        vector<string> ladder = generate_word_ladder(test.start, test.end, word_list);
        
        cout << "Test: " << test.start << " -> " << test.end << ": ";
        if (ladder.size() == test.expected_length)
            cout << "PASSED" << endl;
        else
            cout << "FAILED (expected length " << test.expected_length << ", got " << ladder.size() << ")" << endl;
        
            if (!ladder.empty())
            print_word_ladder(ladder);
        cout << "-------------------------" << endl;
    }
}

// Generate a word ladder from begin_word to end_word using BFS
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    string begin_lower = begin_word;
    string end_lower = end_word;
    
    for (char& c : begin_lower) 
        c = tolower(c);
    for (char& c : end_lower)
        c = tolower(c);
    
    if (begin_lower == end_lower)
        return {begin_lower};
    
    // Check if the end word exists in the dictionary
    if (word_list.find(end_lower) == word_list.end()) {
        error(begin_lower, end_lower, "End word not found in dictionary");
        return {};
    }
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_lower});
    set<string> visited;
    visited.insert(begin_lower);
    
    // Start BFS
    while (!ladder_queue.empty()) {
        vector<string> current_ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = current_ladder.back();
        for (const string& word : word_list) {
            if (visited.find(word) != visited.end())
                continue;
            
            if (is_adjacent(last_word, word)) {
                vector<string> new_ladder = current_ladder;
                new_ladder.push_back(word);

                if (word == end_lower)
                    return new_ladder;

                visited.insert(word);
                ladder_queue.push(new_ladder);
            }
        }
    }
    error(begin_lower, end_lower, "No word ladder exists");
    return {};
}

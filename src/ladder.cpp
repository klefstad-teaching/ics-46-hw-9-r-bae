#include "ladder.h"

void error(string word1, string word2, string msg) {
    cout << "Error from '" << word1 << "' to '" << word2 << "': " << msg << endl;
}

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

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
	vector<string> result;
    queue<vector<string>> ladder_queue;
    set<string> visited;

    if (begin_word == end_word) {
    	error(begin_word, end_word, "same start and end");
        return result;
    }
    if (word_list.find(end_word) == word_list.end()) {
    	error(begin_word, end_word, "end word is invalid");
        return result;
    }
    ladder_queue.push({begin_word});
    visited.insert(begin_word);
    while (!ladder_queue.empty()) {
    	vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();
        for (auto word : word_list) {
        	if (is_adjacent(last_word, word) && visited.find(word) == visited.end()) {
            	visited.insert(word);
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                if (word == end_word)
                	return new_ladder;
                ladder_queue.push(new_ladder);
            }
        }
    }
    return result;
}

void load_words(set<string> & word_list, const string& file_name) {
	ifstream file(file_name);
    if(file) {
    	string word;
        while (getline(file, word))
        	word_list.insert(word);
        file.close();
    }
}
void print_word_ladder(const vector<string>& ladder) {
	if (ladder.empty())
    	cout << "No word ladder was found." << endl;
    else {
    	cout << "Word ladder found: ";
        for (auto word : ladder)
        	cout << word << " → ";
        cout << endl;
    }
}

void verify_word_ladder() {}

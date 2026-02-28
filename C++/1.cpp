#include <bits/stdc++.h>
using namespace std;

struct Trie {
    unordered_map<char, Trie*> children;
    int freq = 0;
    vector<pair<int, string>> top5; 
};
void insert(Trie* root, const string& word) {
    Trie* node = root;
    for (char c : word) {
        if (node->children.find(c) == node->children.end()) {
            node->children[c] = new Trie();
        }
        node = node->children[c];
    }
    node->freq++;
}

vector<pair<int, string>> getAllWords(Trie* node, const string& current) {
    vector<pair<int, string>> res;
    if (node->freq > 0) {
        res.push_back({node->freq, current});
    }
    for (auto& p : node->children) {
        auto sub = getAllWords(p.second, current + p.first);
        res.insert(res.end(), sub.begin(), sub.end());
    }
    return res;
}

void buildTop5(Trie* node, const string& current) {
    vector<pair<int, string>> all = getAllWords(node, current);
    sort(all.rbegin(), all.rend());
    for (int i = 0; i < min(5, (int)all.size()); ++i) {
        node->top5.push_back({all[i].first, all[i].second});
    }
    for (auto& p : node->children) {
        buildTop5(p.second, current + p.first);
    }
}

vector<string> getSuggestions(Trie* root, const string& prefix) {
    Trie* node = root;
    for (char c : prefix) {
        if (node->children.find(c) == node->children.end()) {
            return {};
        }
        node = node->children[c];
    }
    vector<string> res;
    for (auto& p : node->top5) {
        res.push_back(p.second);
    }
    return res;
}

int main() {
    Trie* root = new Trie();
    vector<string> words = {"apple", "app", "application", "ape", "bat", "ball", "batter"};
    for (const auto& word : words) {
        insert(root, word);
    }
    
    buildTop5(root, "");
    string prefix = "app";
    vector<string> suggestions = getSuggestions(root, prefix);
    cout << "Suggestions for '" << prefix << "': ";
    for (const auto& s : suggestions) {
        cout << s << " ";
    }
    cout << endl;
    return 0;
}
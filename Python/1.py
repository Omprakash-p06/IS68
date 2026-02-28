"""Trie-based Autocomplete with Top-5 Suggestions by Frequency"""

from collections import defaultdict

class TrieNode:
    def __init__(self):
        self.children = {}
        self.freq = 0
        self.top5 = []  # [(freq, word), ...]

def insert(root, word):
    node = root
    for ch in word:
        if ch not in node.children:
            node.children[ch] = TrieNode()
        node = node.children[ch]
    node.freq += 1

def get_all_words(node, prefix):
    """Collect all words under this node with their frequencies."""
    results = []
    if node.freq > 0:
        results.append((node.freq, prefix))
    for ch, child in node.children.items():
        results.extend(get_all_words(child, prefix + ch))
    return results

def build_top5(node, prefix):
    """Pre-compute top-5 most frequent words at every trie node."""
    all_words = get_all_words(node, prefix)
    all_words.sort(reverse=True)
    node.top5 = all_words[:5]
    for ch, child in node.children.items():
        build_top5(child, prefix + ch)

def get_suggestions(root, prefix):
    """Return top-5 suggestions for a given prefix."""
    node = root
    for ch in prefix:
        if ch not in node.children:
            return []
        node = node.children[ch]
    return [word for _, word in node.top5]

if __name__ == "__main__":
    root = TrieNode()
    words = ["apple", "app", "application", "ape", "bat", "ball", "batter"]
    for w in words:
        insert(root, w)

    build_top5(root, "")
    prefix = "app"
    suggestions = get_suggestions(root, prefix)
    print(f"Suggestions for '{prefix}': {' '.join(suggestions)}")

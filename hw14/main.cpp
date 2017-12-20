/*
 * Brian Clinkenbeard | CS1D | Assignment 14
 * This program will print out the frequency table and the Huffman Code for each letter of the Gettysburg address.
 * Then it will encode the Gettysburg address and print it. It will decode the compressed and encoded file that is
 * created and print out the compression ratio that was achieved.
 */

#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <string>
#include <cassert>
#include <stdexcept>
#include <iostream>
// main
#include <fstream>
#include <iomanip>
#include <sstream>
#include <iterator>

// source: ningke/huffman-codes

using namespace std;

// A Huffman Tree Node
struct HuffmanTree {
    char c; // character in an alphabet
    int cfreq; // frequency of c.
    struct HuffmanTree *left;
    struct HuffmanTree *right;
    HuffmanTree(char c, int cfreq, struct HuffmanTree *left=NULL,
                struct HuffmanTree *right=NULL) :
        c(c), cfreq(cfreq), left(left), right(right) {
    }
    ~HuffmanTree() {
        delete left, delete right;
    }
    // Compare two tree nodes
    class Compare {
    public:
        bool operator()(HuffmanTree *a, HuffmanTree *b) {
            return a->cfreq > b->cfreq;
        }
    };
};

/**
 * Builds a Huffman Tree from an input of alphabet C, where C is a vector
 * of (character, frequency) pairs.
 */
HuffmanTree *build_tree(vector< pair<char, unsigned> > &alph) {
    // First build a min-heap
    // Build leaf nodes first
    priority_queue<HuffmanTree *, vector<HuffmanTree *>, HuffmanTree::Compare > alph_heap;
    for (vector< pair<char, unsigned> >::iterator it = alph.begin();
         it != alph.end(); ++it) {
        HuffmanTree *leaf = new HuffmanTree(it->first, it->second);
        alph_heap.push(leaf);
    }

    // HuffmanTree algorithm: Merge two lowest weight leaf nodes until
    // only one node is left (root).
    HuffmanTree *root = NULL;
    while (alph_heap.size() > 1) {
        HuffmanTree *l, *r;
        l = alph_heap.top();
        alph_heap.pop();
        r = alph_heap.top();
        alph_heap.pop();
        root = new HuffmanTree(0, l->cfreq + r->cfreq, l, r);
        alph_heap.push(root);
    }

    return root;
}

/**
 * Prints the tree nodes in breadth-first order
 */
void print_tree(HuffmanTree *t) {
    deque< pair<HuffmanTree *, int> > q;

    q.push_back(make_pair(t, 0));
    int curlevel = -1;
    while (!q.empty()) {
        HuffmanTree *parent = q.front().first;
        int level = q.front().second;
        q.pop_front();
        if (curlevel != level) {
            curlevel = level;
            cout << "Level " << curlevel << endl;
        }
        cout << parent->cfreq << " " << parent->c << endl;
        if (parent->left)
            q.push_back(make_pair(parent->left, level + 1));
        if (parent->right)
            q.push_back(make_pair(parent->right, level + 1));
    }
}

typedef vector<bool> code_t;
typedef map<char, code_t> codetable;
/**
 * Makes a lookup table (std::map) of (c -> code) from a HuffmanTree, where
 * code is an unsigned long representing the binary code.
 */
map<char, code_t> build_lookup_table(HuffmanTree *htree) {
    codetable lookup;
    deque< pair<HuffmanTree *, code_t> > q;

    q.push_back(make_pair(htree, code_t()));
    while (!q.empty()) {
        HuffmanTree *node, *lc, *rc;
        code_t code;
        node = q.front().first;
        code = q.front().second;
        q.pop_front();
        lc = node->left;
        rc = node->right;
        if (lc) {
            // HuffmanTree is always full (either no children or two children)
            // Left child is appended a 0 and right child a 1.
            code_t code_cp(code);
            q.push_back(make_pair(lc, (code.push_back(0), code)));
            q.push_back(make_pair(rc, (code_cp.push_back(1), code_cp)));
        } else {
            // Leaf node: contains the character
            lookup.insert(make_pair(node->c, code));
            //cout << "(" << node->c << ", ";
            for (unsigned i = 0; i < code.size(); i++) {
                //cout << code[i];
            }
            //cout << ")" << endl;
        }
    }

    return lookup;
}

/**
 * Encodes an input string. returns a byte vector.
 */
code_t encode(string input, codetable &lookup) {
    code_t result;

    for (string::iterator it = input.begin(); it != input.end(); ++it) {
            code_t b = lookup[*it];
            result.insert(result.end(), b.begin(), b.end());
    }

    return result;
}

/**
 * Look up the next valid code in @biter using @htree and returns the
 * resulting string. Note the iterator @biter is advanced by the actual
 * length of the next valid code, which varies.
 */
char code_lookup(code_t::iterator &biter, const code_t::iterator &biter_end,
                 const HuffmanTree *htree) {
    const HuffmanTree *node = htree;

    while (true) {
        if (!node->left) {
            // Huffman tree is full: always contains both children or none.
            break;
        }
        if (biter == biter_end) {
            throw std::out_of_range("No more bits");
        }
        if (*biter) {
            node = node->right;
        } else {
            node =node->left;
        }
        ++biter;
    }

    return node->c;
}

/**
 * Decodes a compressed string represented by a bit vector (vector<char>)
 * @compressed, using a HuffmanTree @htree.
 * Returns the original string.
 */
string decode(code_t &compressed, const HuffmanTree *htree) {
    string result;

    code_t::iterator biter = compressed.begin();
    while (true) {
        try {
            result += code_lookup(biter, compressed.end(), htree);
        } catch (const std::out_of_range &oor) {
            // Iterator exhausted.
            break;
        }
    }

    return result;
}

/**
 * Tests
 */
// Make frequency table from a string.
vector< pair<char, unsigned> > make_freq_table(string inp) {
    map<char, unsigned> cfmap;
    vector< pair<char, unsigned> >cfvec;

    for (unsigned i = 0; i < inp.size(); i++) {
        if (cfmap.find(inp[i]) == cfmap.end()) {
            cfmap.insert(make_pair(inp[i], 1));
        }
        cfmap[inp[i]] += 1;
    }

    for (map<char, unsigned>::iterator it = cfmap.begin();
         it != cfmap.end(); ++it) {
        cfvec.push_back(make_pair(it->first, it->second));
    }

    return cfvec;
}

string bitvec_to_string(code_t &bitvec) {
    string result;
    size_t nbits;

    nbits = bitvec.size() & 7;

    // Write the number of "hanging bits" at the first byte
    result += static_cast<char>(nbits); // at most 7

    char byte = 0;
    for (unsigned i = 0; i < bitvec.size(); i++) {
        unsigned boff = i & 7;
        byte |= bitvec[i] << boff;
        if (boff == 7) {
            // Write a byte
            result += byte;
            byte = 0;
        }
    }
    if (nbits) {
        result += byte;
    }

    return result;
}

code_t string_to_bitvec(string packed) {
    code_t result;

    assert(packed.size());
    if (packed.size() == 1) {
        assert(packed[0] == 0);
        return result;
    }
    unsigned nbits = packed[0];
    for (string::iterator it = packed.begin() + 1; it != packed.end(); ++it) {
        for (unsigned i = 0; i < 8; i++) {
            result.push_back((*it >> i) & 1);
        }
    }
    // fix the last byte
    if (nbits) {
        for (unsigned i = 0; i < (8 - nbits); i++) {
            result.pop_back();
        }
    }

    return result;
}

int main() {
    // read input to string
    std::ifstream in_file("huffman_input.txt");
    std::string speech_text((std::istreambuf_iterator<char>(in_file)), std::istreambuf_iterator<char>());

    // create frequency table and use it to build the Huffman tree
    vector< pair<char, unsigned> > freq_table= make_freq_table(speech_text);
    HuffmanTree *htree = build_tree(freq_table);

    // create table of Huffman codes
    codetable table = build_lookup_table(htree);

    // print
    for (codetable::const_iterator it = table.begin(); it != table.end(); ++it) {
        // print characters
        if (it->first == '\n')
            std::cout << "\\n"; // print "\n" instead of a real newline
        else
            std::cout << " " << it->first;
        std::cout << ": " << std::setw(12);

        // print huffman code
        std::ostringstream code;
        std::copy(it->second.begin(), it->second.end(), std::ostream_iterator<bool>(code));
        std::cout << code.str();

        // find char within freq table
        char c = it->first;
        auto freq = std::find_if(freq_table.begin(), freq_table.end(), [c](const std::pair<char, unsigned>& element)
                              { return element.first == c; });

        // print frequency
        if (freq != freq_table.end())
            std::cout << ", " << std::setw(12) << "frequency: " << freq->second;
        else
            std::cout << ", ERROR: unable to find character in frequency table";

        std::cout << std::endl;
    }

    std::cout << std::endl;

    // encode
    code_t encoded_bitvec = encode(speech_text, table);
    std::string encoded_text = bitvec_to_string(encoded_bitvec);

    std::cout << "Encoded text:" << std::endl << encoded_text << std::endl;

    std::ofstream out_file("huffman_encoded.txt");
    std::cout << "Writing encoded text to file huffman_encoded.txt..." << std::endl;
    out_file << encoded_text;

    std::cout << "Compression ratio (" << encoded_text.size() << "/" << speech_text.size() << "): "
              << static_cast<double>(encoded_text.size()) / static_cast<double>(speech_text.size()) * 100 << "%" << std::endl;

    std::cout << std::endl;

    // decode
    code_t decoded_bitvec = string_to_bitvec(encoded_text);
    std::string decoded_text = decode(decoded_bitvec, htree);

    std::cout << "Decoded text:" << std::endl << decoded_text << std::endl;

    if (decoded_text == speech_text)
        std::cout << "Success: decoded text matches original." << std::endl;
    else
        std::cout << "Error: decoded text does not match original." << std::endl;
}

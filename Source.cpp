#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>


using namespace std;

struct Node {
	char ch;
	int frequency;
	Node* left;
	Node* right;

};

Node* getNode(char ch, int frequency, Node* left, Node* right) {

	Node* node = new Node();

	node->ch = ch;
	node->frequency = frequency;
	node->left = left;
	node->right = right;

	return node;

}

struct comp {

	bool operator()(Node* a, Node* b) {
		return a->frequency > b->frequency;
	}

};

void encode(Node* root, string str, unordered_map<char, string>& huffmanCode) {

	if (root == nullptr) {
		return;
	}

	if (!root->left && !root->right) {
		huffmanCode[root->ch] = str;
	}

	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}

void decode(Node* root, string str, int& index) {

	if (root == nullptr) {
		return;
	}

	if (!root->left && !root->right) {
		cout << root->ch;
		return;
	}

	index++;

	if (str[index] == '0') {
		decode(root->left, str, index);
	}
	else {
		decode(root->right, str, index);
	}

}

void buildHuffmanTree(string text)
{

	unordered_map<char, int> freq;
	for (char ch : text) {
		freq[ch]++;
	}

	priority_queue<Node*, vector<Node*>, comp> pq;

	for (auto pair : freq) {
		pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
	}

	while (pq.size() != 1)
	{
	
		Node* left = pq.top(); pq.pop();
		Node* right = pq.top();	pq.pop();

		int sum = left->frequency + right->frequency;
		pq.push(getNode('\0', sum, left, right));
	}

	Node* root = pq.top();

	unordered_map<char, string> huffmanCode;
	encode(root, "", huffmanCode);

	cout << "Huffman Codes are :\n" << '\n';
	for (auto pair : huffmanCode) {
		cout << pair.first << " " << pair.second << '\n';
	}

	cout << "\nOriginal string was :\n" << text << '\n';

	string str = "";
	for (char ch : text) {
		str += huffmanCode[ch];
	}

	cout << "\nEncoded string is :\n" << str << '\n';

	int index = -1;
	cout << "\nDecoded string is: \n";
	while (index < (int)str.size() - 2) {
		decode(root, str, index);
	}
}	

int main() {

	string text = "Huffman Algorithm is correct";

	buildHuffmanTree(text);

	return 0;

}
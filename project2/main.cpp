#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "Binary_Tree.h"

std::string decode_morse(const std::string morse, Binary_Tree<char>& morse_tree) {
  std::string decoded = "";
  BTNode<char>* current = morse_tree.getRoot();
  for(unsigned int i = 0; i < morse.length(); i++) {
    switch(morse[i]) {
      case '.':
        current = current->left;
        break;
      case '_':
        current = current->right;
        break;
      case ' ':
        decoded += (*current).data;
        current = morse_tree.getRoot();
        break;
    }
  }
  return decoded;
}

std::string encode_morse(const std::string text, const std::string filename) {
  std::string morse = "";
  std::ifstream file;
  file.open(filename);
  std::vector<std::string> lines;
  if (file.is_open()) {
      std::string line;
      while(getline(file, line))
        lines.push_back(line);
      for (unsigned int i = 0; i < text.length(); i++) {
        int k = 0;
        while (text[i] != lines[k][0])
          k++;
        morse = morse + lines[k].substr(1, lines[k].size()-2) + " ";
      }
  }
  file.close();
  return morse;
}

bool sort_by_length(const std::string &i, const std::string &j) {
  return j.length() > i.length();
}

Binary_Tree<char> create_morse_tree(std::string filename) {
  Binary_Tree<char> morse_tree;
  std::ifstream file;

  file.open(filename);
  std::vector<std::string> lines;
  if (file.is_open()) {
    std::string line;
    while(getline(file,line)){
      lines.push_back(line);
    }
  }
  file.close();
  //std::sort doesn't include sorting the element for some reason.
  //This is a quick hack around that.
  std::sort(lines.begin(), lines.end(), sort_by_length);
  std::sort(lines.begin(), lines.end(), sort_by_length);

  BTNode<char>* root = new BTNode<char>('^');
  BTNode<char>* current = root;
  for (unsigned int i = 0; i < lines.size(); i++) {
    if (lines[i].size() <= 3) {
      if (lines[i][1] == '.')
        current->left = new BTNode<char>(lines[i][0]);
      else
        current->right = new BTNode<char>(lines[i][0]);
    }
    else {
      for (unsigned int k = 1; k < lines[i].length() - 2; k++) {
        if(lines[i][k] == '.')
          current = (current->left);
        if(lines[i][k] == '_')
          current = (current->right);
      }
      if (lines[i][lines[i].size() - 2] == '.') {
        current->left = new BTNode<char>(lines[i][0]);
      }
      else {
        current->right = new BTNode<char>(lines[i][0]);
      }
    }
    current = root;
  }
  morse_tree.setRoot(root);
  return morse_tree;
}

int main() {
  Binary_Tree<char> morse_tree = create_morse_tree("morse.txt");
  std::string encoded = encode_morse("thisisthebesttestyouveeverseen", "morse.txt");
  std::string decoded = decode_morse(encoded, morse_tree);
  std::cout << encoded << " " << decoded << std::endl;
  return 0;
}

//
// Created by Qami on 12/22/2023.
//

#include "FileReader.h"
#include <fstream>
#include <iostream>
#include <utility>

namespace Logic {
void FileReader::mapReader(tilemap& tilemap, unique_ptr<AbstractFactory>& abstractFactory) {
    std::ifstream map;
    map.open(PATH_TILEMAPS + fileName);
    string line;

    try {
        int i = 0;
        while (getline(map, line)) {
            vector<sharedEntityModel> characters;
            int j = 0;
            for (char c : line) {
                characters.push_back(abstractFactory->modelFactory(c));
                j++;
            }
            i++;
            tilemap.push_back(characters);
            characters.clear();
        }
    } catch (string& e) {
        cout << "File not found: " << e << endl;
    }
}

FileReader::FileReader(string fileName) : fileName(std::move(fileName)) {}

void FileReader::scoreReader(vector<int>& highScores) {
    string highScore;
    ifstream file(PATH_HIGHSCORES + fileName);
    if (file.is_open()) {
        while (getline(file, highScore)) {
            string scoreS = highScore.substr(3, highScore.length());
            highScores.push_back(stoi(scoreS));
        }
        file.close();
    }
}
} // namespace Logic
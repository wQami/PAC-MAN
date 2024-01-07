//
// Created by Qami on 12/24/2023.
//

#include "FileWriter.h"

#include <fstream>
#include <iostream>
#include <utility>

namespace Logic {
FileWriter::FileWriter(string destination) : destination(std::move(destination)) {}

void FileWriter::mapOut(sharedmap& tilemap) {
    for (auto& i : tilemap) {
        for (const auto& j : i) {
            if (j) {
                switch (j->getType()) {
                case LOSER_PACMAN:
                case WINNER_PACMAN:
                case PACMAN:
                    cout << 'O';
                    break;
                case GHOST:
                    cout << 'g';
                    break;
                case SCATTER_GHOST:
                    cout << 's';
                    break;
                case FRIGHTENED_GHOST:
                    cout << 'w';
                    break;
                case EATEN_GHOST:
                    cout << ':';
                    break;
                case COIN:
                    cout << '-';
                    break;
                case FRUIT:
                    cout << 'y';
                    break;
                case WALL:
                    cout << 'x';
                    break;
                case DOOR:
                    (j->getValue() == 1) ? cout << '_' : cout << '=';
                    break;
                case EMPTY:
                    cout << ' ';
                    break;
                }
            } else {
                cout << ' ';
            }
        }
        cout << endl;
    }
}

void FileWriter::scoreWriter(const vector<int>& highScores) {
    ofstream file(destination);
    for (int i = 0; i < 5; i++) {
        file << i + 1 << ". " << highScores[i] << endl;
    }
    file.close();
}

void FileWriter::scoreOut(const vector<int>& highScores) {
    cout << "\n --------\nHIGHSCORES\n --------" << endl;
    for (int i = 0; i < 5; i++) {
        cout << " " << i + 1 << "." << highScores[i] << endl;
    }
    cout << endl;
}

} // namespace Logic
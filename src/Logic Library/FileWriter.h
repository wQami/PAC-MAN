//
// Created by Qami on 12/24/2023.
//

#ifndef PAC_MAN_FILEWRITER_H
#define PAC_MAN_FILEWRITER_H

#include "EntityModel.h"
#include <string>
#include <vector>

using namespace std;

namespace Logic {

class FileWriter {
private:
    string destination;

public:
    FileWriter() = default;

    explicit FileWriter(string destination);
    static void mapOut(sharedmap& tilemap);
    static void scoreOut(const vector<int>& highScores);
    void scoreWriter(const vector<int>& highScores);
};

} // namespace Logic

#endif // PAC_MAN_FILEWRITER_H

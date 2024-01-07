//
// Created by Qami on 12/22/2023.
//

#ifndef PAC_MAN_FILEREADER_H
#define PAC_MAN_FILEREADER_H

#include "../globalGame.h"
#include "AbstractFactory.h"
#include "EntityModel.h"
#include "Models/Ghost.h"
#include "Models/PacMan.h"
namespace Logic {

class FileReader {
private:
    string fileName;

public:
    explicit FileReader(string fileName);
    void mapReader(tilemap& tilemap, unique_ptr<AbstractFactory>& abstractFactory);
    void scoreReader(vector<int>& highScores);
};

} // namespace Logic

#endif // PAC_MAN_FILEREADER_H

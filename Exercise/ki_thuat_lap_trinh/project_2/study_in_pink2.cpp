#include "study_in_pink2.h"

// MapElement
MapElement::MapElement(ElementType in_type){
    type = in_type;
}

MapElement::~MapElement(){}

ElementType MapElement::getType() const {
    return type;
}

// Path
Path::Path(): MapElement(PATH){}

// Wall
Wall::Wall(): MapElement(WALL){}

// FakeWall
FakeWall::FakeWall(int in_req_exp): MapElement(FAKE_WALL), req_exp(in_req_exp){} 

int FakeWall::getReqExp() const {
    return req_exp;
}

// Position
Position::Position(int r = 0, int c = 0): r(r), c(c){}

Position::Position(const string & str_pos){
    int comma_position = str_pos.find(',');
    r = stoi(str_pos.substr(1, comma_position - 1));
    c = stoi(str_pos.substr(comma_position + 1, str_pos.length() - comma_position - 2));
}

int Position::getRow() const {
    return r;
}

int Position::getCol() const {
    return c;
}

void Position::setRow(int r) {
    this->r = r;
}

void Position::setCol(int c) {
    this->c = c;
}

string Position::str() const {
    return "(" + std::to_string(r) + "," + std::to_string(c) + ")";
}

bool Position::isEqual(Position y) const {
    return r == y.r && c == y.c;
}

const Position Position::npos = Position(-1, -1);

int operator - (Position x, Position y){
    return abs(x.getRow() - y.getRow()) + abs(y.getCol() - y.getCol());
}

// Map
Map::Map(
    int num_rows, 
    int num_cols, 
    int num_walls, 
    Position * array_walls, 
    int num_fake_walls, 
    Position * array_fake_walls
) : num_rows(num_rows), num_cols(num_cols){
    map = new MapElement**[num_rows];

    for (int i = 0; i < num_rows; i++){
        map[i] = new MapElement*[num_cols];
        for (int j = 0; j < num_cols; j++) map[i][j] = nullptr;
    }

    for (int i = 0; i < num_walls; i++){
        int r = array_walls[i].getRow();
        int c = array_walls[i].getCol();
        map[r][c] = new Wall();
    }

    for (int i = 0; i < num_fake_walls; i++){
        int r = array_fake_walls[i].getRow();
        int c = array_fake_walls[i].getCol();
        map[r][c] = new FakeWall((r * 257 + c * 139 + 89) % 900 + 1);
    }

    for (int i = 0; i < num_rows; i++){
        for (int j = 0; j < num_cols; j++){
            if (!map[i][j]) map[i][j] = new Path();
        }
    }
}

Map::~Map(){
    for (int i = 0; i < num_rows; i++){
        for (int j = 0; j < num_cols; j++){
            delete map[i][j];
        }
    } 

    for (int i = 0; i < num_rows; i++){
        delete[] map[i];
    }

    delete[] map;
}

// MovingObject
MovingObject::MovingObject(
    int index, 
    const Position pos, 
    Map * map, 
    const string & name=""
): index(index), pos(pos), map(map), name(name){}

MovingObject::~MovingObject(){}

string MovingObject::getName(){
    return name;
}

// Map
bool Map::isValid(const Position &pos , MovingObject *mv_obj) const {
    int r = pos.getRow();
    int c = pos.getCol();

    if (r < 0 || c < 0 || r > num_rows - 1 || c > num_cols - 1) return false;
    ElementType type = map[r][c]->getType();

    if (type == PATH) return true;
    if (type == WALL) return false;
    if (type == FAKE_WALL){
        string obj_name = mv_obj->getName();
        if (obj_name == "Sherlock" || obj_name == "Criminal" || obj_name == "") return true;
        if (obj_name == "Watson"){
            if (((Character*) mv_obj)->getExp() > ((FakeWall*) map[r][c])->getReqExp()) return true;
            else return false;
        }
    }
}

int Map::getNumRows() const {
    return num_rows;
}

int Map::getNumCols() const {
    return num_cols;
}

// Character
Character::Character(
    int index, 
    const Position pos, 
    Map * map,
    const string & name=""
): MovingObject(index, pos, map, name){}

Character::~Character(){}

int Character::getHp() const {}

int Character::getExp() const {}

void Character::setHp(int hp){}

void Character::setExp(int exp){}

// Sherlock
Sherlock::Sherlock(
    int index, 
    const string & moving_rule, 
    const Position & init_pos, 
    Map * map, 
    int init_hp, 
    int init_exp
): Character(index, init_pos, map, "Sherlock"), hp(init_hp), exp(init_exp), moving_rule(moving_rule){}

Sherlock::~Sherlock(){}

Position Sherlock::getNextPosition(){
    char direction = moving_rule[move_step];
    int r = pos.getRow();
    int c = pos.getCol();
    Position next_position;

    if (direction == 'L') next_position = Position(r, c - 1);
    else if (direction == 'R') next_position = Position(r, c + 1);
    else if (direction == 'U') next_position = Position(r - 1, c);
    else if (direction == 'D') next_position = Position(r + 1, c);

    if (map->isValid(next_position, this)) return next_position;
    else return Position::npos;
}

Position Sherlock::getCurrentPosition() const {
    return pos;
}

void Sherlock::move(){
    Position next_position = getNextPosition();
    if (!next_position.isEqual(Position::npos)) pos = next_position;
}

string Sherlock::str() const {
    return "Sherlock[index=" + to_string(index) + ";pos=" + pos.str() + ";moving_rule=" + moving_rule + "]";
}

int Sherlock::getHp() const {
    return hp;
}

int Sherlock::getExp() const {
    return exp;
}

void Sherlock::setHp(int hp){
    this->hp = hp;
}

void Sherlock::setExp(int exp){
    this->exp = exp;
}

// Watson
Watson::Watson(
    int index, 
    const string & moving_rule, 
    const Position & init_pos, 
    Map * map, 
    int init_hp, 
    int init_exp
): Character(index, init_pos, map, "Watson"), hp(init_hp), exp(init_exp), moving_rule(moving_rule){}

Watson::~Watson(){}

Position Watson::getNextPosition(){
    char direction = moving_rule[move_step];
    int r = pos.getRow();
    int c = pos.getCol();
    Position next_position;

    if (direction == 'L') next_position = Position(r, c - 1);
    else if (direction == 'R') next_position = Position(r, c + 1);
    else if (direction == 'U') next_position = Position(r - 1, c);
    else if (direction == 'D') next_position = Position(r + 1, c);

    if (map->isValid(next_position, this)) return next_position;
    else return Position::npos;
}

Position Watson::getCurrentPosition() const {
    return pos;
}

void Watson::move(){
    Position next_position = getNextPosition();
    if (!next_position.isEqual(Position::npos)) pos = next_position;
}

string Watson::str () const {
    return "Watson[index=" + to_string(index) + ";pos=" + pos.str() + ";moving_rule=" + moving_rule + "]";
}

int Watson::getHp() const {
    return hp;
}

int Watson::getExp() const {
    return exp;
}

void Watson::setHp(int hp){
    this->hp = hp;
}

void Watson::setExp(int exp){
    this->exp = exp;
}

// Criminal
Criminal::Criminal(
    int index, 
    const Position & init_pos, 
    Map * map, 
    Sherlock * sherlock, 
    Watson * watson
): Character(index, init_pos, map, "Criminal"), sherlock(sherlock), watson(watson){};

Criminal::~Criminal(){}

Position Criminal::getNextPosition(){
    int r = pos.getRow();
    int c = pos.getCol();
    int max_distance = 0;
    Position max_position = pos;
    Position temp = Position::npos;

    for (int i = 0; i < 4; i++){
        switch (i){
            case 0: temp = Position(r, c + 1); break;
            case 1: temp = Position(r + 1, c); break;
            case 2: temp = Position(r, c - 1); break;
            case 3: temp = Position(r - 1, c);
        }

        int distance = (temp - sherlock->getCurrentPosition()) + (temp - watson->getCurrentPosition());
        
        if (distance > max_distance && map->isValid(temp, this)){
            max_distance = distance;
            max_position = temp;
        }
    }

    return max_position;
}

Position Criminal::getCurrentPosition() const {
    return pos;
}

void Criminal::move(){
    Position next_position = getNextPosition();
    if (!next_position.isEqual(Position::npos)) pos = next_position;
}

string Criminal::str() const {
    return "Criminal[index=" + to_string(index) + ";pos=" + pos.str() + "]";
}

// ArrayMovingObject
ArrayMovingObject::ArrayMovingObject(int capacity): capacity(capacity){
    arr_mv_objs = new MovingObject*[capacity];
    for (int i = 0; i < capacity; i++) arr_mv_objs[i] = nullptr;
}

ArrayMovingObject::~ArrayMovingObject(){
    for (int i = 0; i < capacity; i++){
        if (arr_mv_objs[i]) delete arr_mv_objs[i];
    }

    delete [] arr_mv_objs;
}

bool ArrayMovingObject::isFull() const {
    return count == capacity;
}

bool ArrayMovingObject::add(MovingObject * mv_obj){
    if (isFull()) return false;
    else {
        arr_mv_objs[count] = mv_obj;
        count++;
        return true;
    }
}

MovingObject * ArrayMovingObject::get(int index) const {
    return arr_mv_objs[index];
}

int ArrayMovingObject::size() const {
    return count;
}

string ArrayMovingObject::str() const {
    string information = "ArrayMovingObject[count=" + to_string(count) + ";capacity=" + to_string(capacity);

    for (int i = 0; i < count; i++) information += ";" + arr_mv_objs[i]->str();

    return information;
}

// Từ chuỗi [(1,2);(3,4);(5,6)], trả về 1 Pointer đến 1 mảng trong Heap, mảng này có các phần tử là Position
Position * positionArrayAnalysis(const string & position_array, int n){
    Position * position_array_ptr = new Position[n];
    int current_char_index = 1;
    int current_position_index = 0;

    while (position_array[current_char_index] == '('){
        int delimiter = position_array.find(')', current_char_index);

        position_array_ptr[current_position_index] = 
        Position(position_array.substr(current_char_index, delimiter + 1 - current_char_index));

        current_char_index = delimiter + 2;
        current_position_index += 1;
    }
    return position_array_ptr;
}

// Configuration
Configuration::Configuration(const string & filepath){
    ifstream ifs(filepath);
    string attribute;

    while (getline(ifs, attribute)) {
        int delimiter_position = attribute.find('=');
        string attribute_name = attribute.substr(0, delimiter_position);
        string attribute_value = attribute.substr(delimiter_position + 1);
        
        if (attribute_name == "MAP_NUM_ROWS") map_num_rows = stoi(attribute_value);
        else if (attribute_name == "MAP_NUM_COLS") map_num_cols = stoi(attribute_value);
        else if (attribute_name == "MAX_NUM_MOVING_OBJECTS") max_num_moving_objects = stoi(attribute_value);
        else if (attribute_name == "NUM_WALLS") num_walls = stoi(attribute_value);
        else if (attribute_name == "ARRAY_WALLS") arr_walls = positionArrayAnalysis(attribute_value, num_walls);
        else if (attribute_name == "NUM_FAKE_WALLS") num_fake_walls = stoi(attribute_value);
        else if (attribute_name == "ARRAY_FAKE_WALLS") arr_fake_walls = positionArrayAnalysis(attribute_value, num_fake_walls);
        else if (attribute_name == "SHERLOCK_MOVING_RULE") sherlock_moving_rule = attribute_value;
        else if (attribute_name == "SHERLOCK_INIT_POS") sherlock_init_pos = Position(attribute_value);
        else if (attribute_name == "SHERLOCK_INIT_HP") sherlock_init_hp = stoi(attribute_value);
        else if (attribute_name == "SHERLOCK_INIT_EXP") sherlock_init_exp = stoi(attribute_value);
        else if (attribute_name == "WATSON_MOVING_RULE") sherlock_moving_rule = attribute_value;
        else if (attribute_name == "WATSON_INIT_POS") watson_init_pos = Position(attribute_value);
        else if (attribute_name == "WATSON_INIT_HP") watson_init_hp = stoi(attribute_value);
        else if (attribute_name == "WATSON_INIT_EXP") watson_init_exp = stoi(attribute_value);
        else if (attribute_name == "CRIMINAL_INIT_POS") criminal_init_pos = Position(attribute_value);
        else if (attribute_name == "NUM_STEPS") num_steps = stoi(attribute_value);
    }
}

Configuration::~Configuration(){
    if (arr_walls) delete [] arr_walls;
    if (arr_fake_walls) delete [] arr_fake_walls;
}

string Configuration::str() const {
    string arr_fake_walls_str = "[";
    string arr_walls_str = "[";

    for (int i = 0; i < num_walls; i++){
        arr_walls_str += arr_walls[i].str();
        if (i < num_walls - 1) arr_walls_str += ";";
        else arr_walls_str += "]";
    }

    for (int i = 0; i < num_fake_walls; i++){
        arr_fake_walls_str += arr_fake_walls[i].str();
        if (i < num_fake_walls - 1) arr_fake_walls_str += ";";
    }

    arr_fake_walls_str += "]";

    return 
    "Configuration[MAP_NUM_ROWS=" + to_string(map_num_rows) + 
    ";MAP_NUM_COLS=" + to_string(map_num_cols) +
    ";MAX_NUM_MOVING_OBJECTS=" + to_string(max_num_moving_objects) +
    ";NUM_WALLS=" + to_string(num_walls) +
    ";ARRAY_WALLS=" + arr_walls_str +
    ";NUM_FAKE_WALLS=" + to_string(num_fake_walls) +
    ";ARRAY_FAKE_WALLS=" + arr_fake_walls_str +
    ";SHERLOCK_MOVING_RULE=" + sherlock_moving_rule +
    ";SHERLOCK_INIT_POS=" + sherlock_init_pos.str() +
    ";SHERLOCK_INIT_HP=" + to_string(sherlock_init_hp) +
    ";SHERLOCK_INIT_EXP=" + to_string(sherlock_init_exp) +
    ";WATSON_MOVING_RULE=" + watson_moving_rule +
    ";WATSON_INIT_POS=" + watson_init_pos.str() +
    ";WATSON_INIT_HP=" + to_string(watson_init_hp) +
    ";WATSON_INIT_EXP=" + to_string(watson_init_exp) +
    ";CRIMINAL_INIT_POS=" + criminal_init_pos.str() +
    ";NUM_STEPS=" + to_string(num_steps);
}

// BaseItem
BaseItem::BaseItem(ItemType item_type): item_type(item_type){}

BaseItem * BaseItem::getNextItemPtr() const {
    return next_item_ptr;
}

ItemType BaseItem::getType() const {
    return item_type;
}

// MagicBook
class MagicBook: public BaseItem {
    friend class TestStudyInPink;

    public:
        MagicBook(): BaseItem(MAGIC_BOOK){}

        bool canUse(Character * obj, Robot * robot){
            if (obj->getExp() <= 350) return true;
            return false;
        }

        void use(Character * obj, Robot * robot){
            obj->setExp(obj->getExp() * 1.25);
        }
};

// EnergyDrink
class EnergyDrink: public BaseItem {
    friend class TestStudyInPink;

    public:
        EnergyDrink(): BaseItem(ENERGY_DRINK){}

        bool canUse(Character * obj, Robot * robot){
            if (obj->getHp() <= 100) return true;
            return false;
        }

        void use(Character * obj, Robot * robot){
            obj->setHp(obj->getHp() * 1.2);
        }
};

// FirstAid
class FirstAid: public BaseItem {
    friend class TestStudyInPink;

    public:
        FirstAid(): BaseItem(FIRST_AID){}

        bool canUse(Character * obj, Robot * robot){
            if (obj->getHp() <= 100 || obj->getExp() <= 350) return true;
            return false;
        }

        void use(Character * obj, Robot * robot){
            obj->setHp(obj->getHp() * 1.5);
        }
};

// ExcemptionCard
class ExcemptionCard: public BaseItem {
    friend class TestStudyInPink;

    public:
        ExcemptionCard(): BaseItem(EXCEMPTION_CARD){}

        bool canUse(Character * obj, Robot * robot){
            if (obj->getName() == "Sherlock" && obj->getHp() % 2) return true;
            return false;
        }

        void use(Character * obj, Robot * robot){
            //TODO
        }
};

// PassingCard
int recursiveSumOfDigits(int n) {
    if (n <= 9) return n;

    int sum = 0;
    while (n != 0) {
        sum += n % 10;
        n /= 10;
    }

    return recursiveSumOfDigits(sum);
}

class PassingCard: public BaseItem {
    friend class TestStudyInPink;

    private:
        string challenge;

    public:
        PassingCard(): BaseItem(PASSING_CARD){}

        bool canUse(Character * obj, Robot * robot){
            if (obj->getName() == "Watson" && !(obj->getHp() % 2)) return true;
            return false;
        }

        void use(Character * obj, Robot * robot){
            //TODO
            // if (challenge == robot->getType())
        }
};

// BaseBag
string BaseBag::str() const {
    string information = "Bag[count=" + to_string(count) + ";";
    BaseItem * traveler = first_item;

    while (traveler){
        switch(traveler->getType()){
            case MAGIC_BOOK: information += "MagicBook"; break;
            case ENERGY_DRINK: information += "EnergyDrink"; break;
            case FIRST_AID: information += "FirstAid"; break;
            case EXCEMPTION_CARD: information += "ExcemptionCard"; break;
            case PASSING_CARD: information += "PassingCard";
        }

        if (traveler->getNextItemPtr()) information += ";";
        else information += "]";
    }

    return  information;
};

class SherlockBag: BaseBag {
    friend class TestStudyInPink;

    
};

class WatsonBag: BaseBag {
    friend class TestStudyInPink;
    
};

// Robot
Robot::Robot(
    int index, 
    const Position & init_pos, 
    Map * map, 
    RobotType robot_type
): MovingObject(index, init_pos, map), robot_type(robot_type), map(map){}


RobotType Robot::getType() const {
    return robot_type;
}

// RobotC
RobotC::RobotC(
    int index, 
    const Position & init_pos, 
    Map * map,
    Criminal* criminal
): Robot(index, init_pos, map, C), criminal(criminal){}

Position RobotC::getNextPosition(){
    return criminal->getCurrentPosition();
}

Position RobotC::getCurrentPosition() const {
    return pos;
}

void RobotC::move(){
    pos = getNextPosition();
}

int RobotC::getDistance(Character * character) const {
    if (character->getName() == "Sherlock") return pos - character->getCurrentPosition();
    else if (character->getName() == "Watson") return pos - character->getCurrentPosition();
}

string RobotC::str() const {
    return "Robot[pos=" + pos.str() + ";type=C" + ";dist=]";
}

// RobotS
RobotS::RobotS(
    int index, 
    const Position & init_pos, 
    Map * map,
    Criminal* criminal,
    Sherlock * sherlock
): Robot(index, init_pos, map, S), criminal(criminal), sherlock(sherlock){}

Position RobotS::getNextPosition(){
    int r = pos.getRow();
    int c = pos.getCol();
    int min_distance = INT_MAX;
    Position min_position;
    Position temp;

    for (int i = 0; i < 4; i++){
        switch (i){
            case 0: temp = Position(r, c - 1); break;
            case 1: temp = Position(r + 1, c); break;
            case 2: temp = Position(r, c + 1); break;
            case 3: temp = Position(r - 1, c);
        }

        int distance = temp - sherlock->getCurrentPosition();
        
        if (distance < min_distance){
            min_distance = distance;
            min_position = temp;
        }
    }
    
    if (map->isValid(min_position, this)) return min_position;
    else return Position::npos;
}

Position RobotS::getCurrentPosition() const {
    return pos;
}

void RobotS::move(){
    Position next_position = getNextPosition();
    if (!next_position.isEqual(Position::npos)) pos = next_position;
}

int RobotS::getDistance() const {
    return pos - sherlock->getCurrentPosition();
}

string RobotS::str () const {
    int foo = getDistance();
    return "Robot[pos=" + pos.str() + ";type=S" + ";dist=" + to_string(getDistance()) + "]";
}

// RobotW
RobotW::RobotW(
    int index, 
    const Position & init_pos, 
    Map * map,
    Criminal* criminal,
    Watson * watson
): Robot(index, init_pos, map, W), criminal(criminal), watson(watson){}

Position RobotW::getNextPosition(){
    int r = pos.getRow();
    int c = pos.getCol();
    int min_distance = INT_MAX;
    Position min_position;
    Position temp;

    for (int i = 0; i < 4; i++){
        switch (i){
            case 0: temp = Position(r, c - 1); break;
            case 1: temp = Position(r + 1, c); break;
            case 2: temp = Position(r, c + 1); break;
            case 3: temp = Position(r - 1, c);
        }

        int distance = temp - watson->getCurrentPosition();
        
        if (distance < min_distance){
            min_distance = distance;
            min_position = temp;
        }
    }
    
    if (map->isValid(min_position, this)) return min_position;
    else return Position::npos;
}

Position RobotW::getCurrentPosition() const {
    return pos;
}

void RobotW::move(){
    Position next_position = getNextPosition();
    if (!next_position.isEqual(Position::npos)) pos = next_position;
}

int RobotW::getDistance() const {
    return pos - watson->getCurrentPosition();
}

string RobotW::str() const {
    return "Robot[pos=" + pos.str() + ";type=S" + ";dist=" + to_string(getDistance()) + "]";
}

// RobotSW
RobotSW::RobotSW(
    int index, 
    const Position & init_pos, 
    Map * map,
    Criminal* criminal,
    Sherlock * sherlock,
    Watson * watson
): Robot(index, init_pos, map, SW), criminal(criminal), sherlock(sherlock), watson(watson){}

Position RobotSW::getNextPosition(){
    int r = pos.getRow();
    int c = pos.getCol();
    int min_distance = INT_MAX;
    Position min_position;
    Position temp;

    for (int i = 0; i < 8; i++){
        switch (i){
            case 0: temp = Position(r - 1, c - 1); break;
            case 1: temp = Position(r, c - 2); break;
            case 2: temp = Position(r + 1, c - 1); break;
            case 3: temp = Position(r + 2, c); break;
            case 4: temp = Position(r + 1, c + 1); break;
            case 5: temp = Position(r, c + 2); break;
            case 6: temp = Position(r - 1, c + 1); break;
            case 7: temp = Position(r - 2, c);
        }

        int distance = (temp - sherlock->getCurrentPosition()) + (temp - watson->getCurrentPosition());
        
        if (distance < min_distance){
            min_distance = distance;
            min_position = temp;
        }
    }

    if (map->isValid(min_position, this)) return min_position;
    else return Position::npos;
}

Position RobotSW::getCurrentPosition() const {
    return pos;
}

void RobotSW::move(){
    Position next_position = getNextPosition();
    if (!next_position.isEqual(Position::npos)) pos = next_position;
}

int RobotSW::getDistance() const {
    return (pos - sherlock->getCurrentPosition()) + (pos - watson->getCurrentPosition());
}

string RobotSW::str() const {
    return "Robot[pos=" + pos.str() + ";type=S" + ";dist=" + to_string(getDistance()) + "]";
}

// Program
StudyPinkProgram::StudyPinkProgram(const string & config_file_path){
    config = new Configuration(config_file_path);

    sherlock = new Sherlock(
        1,
        config->sherlock_moving_rule,
        config->sherlock_init_pos, 
        map,
        config->sherlock_init_hp, 
        config->sherlock_init_exp
    );

    watson = new Watson(
        2,
        config->watson_moving_rule,
        config->watson_init_pos, 
        map,
        config->watson_init_hp, 
        config->watson_init_exp
    );

    criminal = new Criminal(
        0,
        config->criminal_init_pos, 
        map,
        sherlock, 
        watson
    );

    arr_mv_objs->add(criminal);
    arr_mv_objs->add(sherlock);
    arr_mv_objs->add(watson);
}

bool StudyPinkProgram::isStop() const {
    return 
        !sherlock->getHp() || 
        !watson->getHp() || 
        sherlock->getCurrentPosition().isEqual(criminal->getCurrentPosition()) ||
        watson->getCurrentPosition().isEqual(criminal->getCurrentPosition());
}

void StudyPinkProgram::printResult() const {
    if (sherlock->getCurrentPosition().isEqual(criminal->getCurrentPosition())) {
        cout << "Sherlock caught the criminal" << endl;
    }
    else if (watson->getCurrentPosition().isEqual(criminal->getCurrentPosition())) {
        cout << "Watson caught the criminal" << endl;
    }
    else {
        cout << "The criminal escaped" << endl;
    }
}

void StudyPinkProgram::printStep(int si) const {
    cout << "Step: " << setw(4) << setfill('0') << si
        << "--"
        << sherlock->str() << "--|--" << watson->str() << "--|--" << criminal->str() << endl;
}

void StudyPinkProgram::run(bool verbose) {
    for (int istep = 0; istep < config->num_steps; ++istep) {
        for (int i = 0; i < arr_mv_objs->size(); ++i) {
            arr_mv_objs->get(i)->move();

            if (isStop()) {
                printStep(istep);
                break;
            }

            if (verbose) {
                printStep(istep);
            }
        }
    }
    printResult();
}

StudyPinkProgram::~StudyPinkProgram(){}
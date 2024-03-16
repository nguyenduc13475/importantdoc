/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Initial code for Assignment 1
* Programming Fundamentals Spring 2023
* Author: Vu Van Tien
* Date: 02.02.2023
*/

//The library here is concretely set, students are not allowed to include any other libraries.
#ifndef _H_STUDY_IN_PINK_2_H_
#define _H_STUDY_IN_PINK_2_H_

#include "main.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

// Forward declaration
// class MovingObject;
// class Position;
// class Configuration;
// class Map;

// class Criminal;
// class RobotS;
// class RobotW;
// class RobotSW;
// class RobotC;

// class ArrayMovingObject;
// class StudyPinkProgram;

// class BaseItem;
// class BaseBag;
// class SherlockBag;
// class WatsonBag;

class TestStudyInPink;

enum ItemType {MAGIC_BOOK, ENERGY_DRINK, FIRST_AID, EXCEMPTION_CARD, PASSING_CARD};
enum ElementType {PATH, WALL, FAKE_WALL};
enum RobotType {C = 0, S, W, SW};

// Done
class MapElement {
    friend class StudyPinkProgram;

    protected:
        ElementType type;

    public:
        MapElement(ElementType in_type){
            type = in_type;
        }

        virtual ~MapElement(){}

        virtual ElementType getType() const {
            return type;
        }
};

// Done
class Path : public MapElement {
    friend class StudyPinkProgram;

    public:
        Path(): MapElement(PATH){}
};

// Done
class Wall : public MapElement {
    friend class StudyPinkProgram;

    public:
        Wall(): MapElement(WALL){};
};

// Done
class FakeWall : public MapElement {
    friend class StudyPinkProgram;

    private:
        int req_exp;
    
    public:
        FakeWall(int in_req_exp): MapElement(FAKE_WALL), req_exp(in_req_exp){} 

        int getReqExp() const {
            return req_exp;
        }
};

// Done
class Map {
    friend class StudyPinkProgram;

    private:
        int num_rows, num_cols;
        MapElement*** map;

    public:
        Map(
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

        ~Map(){
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

        bool isValid (const Position & pos , MovingObject * mv_obj) const {
            int r = pos.getRow();
            int c = pos.getCol();

            if (r < 0 || c << 0 || r > num_rows - 1 || c > num_cols - 1) return false;

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

        int getNumRows(){
            return num_rows;
        }

        int getNumCols(){
            return num_cols;
        }
};

// Done
class Position {
    friend class StudyPinkProgram;

    private:
        int r, c;

    public:
        static const Position npos;

        Position(int r = 0, int c = 0): r(r), c(c){}

        Position(const string & str_pos){
            int comma_position = str_pos.find(',');
            r = stoi(str_pos.substr(1, comma_position - 1));
            c = stoi(str_pos.substr(comma_position + 1, str_pos.length() - comma_position - 2));
        }

        int getRow() const {
            return r;
        }

        int getCol() const {
            return c;
        }

        void setRow(int r) {
            this->r = r;
        }

        void setCol(int c) {
            this->c = c;
        }

        string str() const {
            return "(" + std::to_string(r) + "," + std::to_string(r) + ")";
        }

        bool isEqual(Position y) const {
            return r == y.r && c == y.c;
        }

        int operator - (Position y){
            return abs(r - y.r) + abs(c - y.c);
        }
};

const Position Position::npos = {-1, -1};

// Done
class MovingObject {
    friend class StudyPinkProgram;

    protected:
        int index;
        Position pos;
        Map * map;
        string name;

    public:
        MovingObject(
            int index, 
            const Position pos, 
            Map * map, 
            const string & name=""
        ): index(index), pos(pos), map(map), name(name){}

        virtual ~MovingObject(){}

        virtual Position getNextPosition() = 0;

        virtual Position getCurrentPosition() const = 0;

        virtual void move() = 0;

        virtual string str() const = 0;

        string getName(){
            return name;
        }
};

// Done
class Character: public MovingObject {
    friend class StudyPinkProgram;

    public:
        Character(
            int index, 
            const Position pos, 
            Map * map,
            const string & name=""
        ): MovingObject(index, pos, map, name) {}

        virtual int getHp();
        virtual int getExp();
        virtual void setHp(int hp);
        virtual void setExp(int exp);
};

// Done
class Sherlock: public Character {
    friend class StudyPinkProgram;

    private:
        int hp, exp;
        const string moving_rule;
        int move_step = 0;
        
    public:
        Sherlock(
            int index, 
            const string & moving_rule, 
            const Position & init_pos, 
            Map * map, 
            int init_hp, 
            int init_exp
        ): Character(index, init_pos, map, "Sherlock"), hp(init_hp), exp(init_exp), moving_rule(moving_rule){}
        
        Position getNextPosition(){
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

        Position getCurrentPosition() const {
            return pos;
        }

        void move(){
            Position next_position = getNextPosition();
            if (!next_position.isEqual(Position::npos)) pos = next_position;
        }

        string str() const {
            return "Sherlock[index=" + to_string(index) + ";pos=" + pos.str() + ";moving_rule=" + moving_rule + "]";
        }

        int getHp(){
            return hp;
        }

        int getExp(){
            return exp;
        }

        void setHp(int hp){
            this->hp = hp;
        }

        void setExp(int exp){
            this->exp = exp;
        }
};

// Done
class Watson: public Character {
    friend class StudyPinkProgram;

    private:
        int hp, exp;
        const string moving_rule;
        int move_step = 0;

    public:
        Watson(
            int index, 
            const string & moving_rule, 
            const Position & init_pos, 
            Map * map, 
            int init_hp, 
            int init_exp
        ): Character(index, init_pos, map, "Watson"), hp(init_hp), exp(init_exp), moving_rule(moving_rule){}

        Position getNextPosition(){
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

        Position getCurrentPosition() const {
            return pos;
        }

        void move(){
            Position next_position = getNextPosition();
            if (!next_position.isEqual(Position::npos)) pos = next_position;
        }

        string str () const {
            return "Watson[index=" + to_string(index) + ";pos=" + pos.str() + ";moving_rule=" + moving_rule + "]";
        }

        int getHp(){
            return hp;
        }

        int getExp(){
            return exp;
        }

        void setHp(int hp){
            this->hp = hp;
        }

        void setExp(int exp){
            this->exp = exp;
        }
};

// Done
class Criminal: public Character{
    friend class StudyPinkProgram;

    private:
        Sherlock * sherlock;
        Watson * watson;

    public:
        Criminal(
            int index, 
            const Position & init_pos, 
            Map * map, 
            Sherlock * sherlock, 
            Watson * watson
        ): Character(index, init_pos, map, "Criminal"), sherlock(sherlock), watson(watson){};

        Position getNextPosition(){
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

        Position getCurrentPosition() const {
            return pos;
        }

        void move(){
            Position next_position = getNextPosition();
            if (!next_position.isEqual(Position::npos)) pos = next_position;
        }

        string str() const {
            return "Criminal[index=" + to_string(index) + ";pos=" + pos.str() + "]";
        }
};

// Done
class ArrayMovingObject {
    friend class StudyPinkProgram;

    private:
        MovingObject ** arr_mv_objs;
        int count = 0, capacity;

    public:
        ArrayMovingObject(int capacity): capacity(capacity){
            arr_mv_objs = new MovingObject*[capacity];
        }

        ~ArrayMovingObject(){
            for (int i = 0; i < capacity; i++){
                delete arr_mv_objs[i];
            }

            delete [] arr_mv_objs;
        }

        bool isFull() const {
            return count == capacity;
        }

        bool add(MovingObject * mv_obj){
            if (isFull()) return false;
            else {
                arr_mv_objs[count] = mv_obj;
                count++;
                return true;
            }
        }

        MovingObject * get(int index) const {
            return arr_mv_objs[index];
        }

        int size() const {
            return count;
        }

        string str() const {
            string information = "ArrayMovingObject[count=" + to_string(count) + ";capacity=" + to_string(capacity);

            for (int i = 0; i < count; i++) information += ";" + arr_mv_objs[i]->str();

            return information;
        }
};

// Từ chuỗi [(1,2);(3,4);(5,6)], trả về 1 Pointer đến 1 mảng trong Heap, mảng này có các phần tử là Position
Position * positionArrayAnalysis(const string & position_array, int n){
    Position * position_array_ptr = new Position[n];
    int current_char_index = 1;
    int current_position_index = 0;

    while (position_array[current_char_index] == '('){
        int delimiter = position_array.find(';', current_char_index);

        position_array_ptr[current_position_index] = 
        Position(position_array.substr(current_char_index, delimiter - current_char_index));

        current_char_index = delimiter + 1;
    }

    return position_array_ptr;
}

// Done
class Configuration {
    friend class StudyPinkProgram;

    private:
        int map_num_rows, map_num_cols;
        int max_num_moving_objects;
        int num_walls, num_fake_walls;
        Position * arr_walls, * arr_fake_walls;
        string sherlock_moving_rule, watson_moving_rule;
        Position sherlock_init_pos, watson_init_pos, criminal_init_pos;
        int sherlock_init_hp, sherlock_init_exp, watson_init_hp, watson_init_exp;
        int num_steps;

    public:
        Configuration(const string & filepath){
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

        ~Configuration(){
            delete [] arr_walls;
            delete [] arr_fake_walls;
        }

        string str() const {
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
                else arr_fake_walls_str += "]";
            }

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

        Position getSherlockInitPos(){
            return sherlock_init_pos;
        }

        Position getWatsonInitPos(){
            return watson_init_pos;
        }

        Position getCriminalInitPos(){
            return criminal_init_pos;
        }

        int getSherlockInitHp(){
            return sherlock_init_hp;
        }

        int getWatsonInitHp(){
            return watson_init_hp;
        }

        int getSherlockInitExp(){
            return sherlock_init_exp;
        }

        int getWatsonInitExp(){
            return watson_init_exp;
        }

        string getSherlockMovingRule(){
            return sherlock_moving_rule;
        }

        string getWatsonMovingRule(){
            return watson_moving_rule;
        }
};

// Robot, BaseItem, BaseBag,...
class BaseItem {
    friend class StudyPinkProgram;

    protected:
        BaseItem * next_item_ptr;
        ItemType item_type;

    public:
        BaseItem(ItemType item_type): item_type(item_type){}

        virtual bool canUse(Character * obj, Robot * robot) = 0;

        virtual void use(Character * obj, Robot * robot) = 0;

        BaseItem * getNextItemPtr(){
            return next_item_ptr;
        }

        ItemType getType(){
            return item_type;
        }
};

class MagicBook: public BaseItem {
    friend class StudyPinkProgram;

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

class EnergyDrink: public BaseItem {
    friend class StudyPinkProgram;

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

class FirstAid: public BaseItem {
    friend class StudyPinkProgram;

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

class ExcemptionCard: public BaseItem {
    friend class StudyPinkProgram;

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
    friend class StudyPinkProgram;

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

class BaseBag {
    friend class StudyPinkProgram;

    private:
        Character * obj;
        int count;
        BaseItem * first_item;
    
    public:
        virtual bool insert (BaseItem* item);

        virtual BaseItem* get();

        virtual BaseItem* get(ItemType itemType);

        virtual string str() const {
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
};

class SherlockBag: BaseBag {
    friend class StudyPinkProgram;

    
};

class WatsonBag: BaseBag {
    friend class StudyPinkProgram;
    
};

class Robot: public MovingObject {
    friend class StudyPinkProgram;

    protected:
        RobotType robot_type;
        BaseItem * item;
    
    public:
        Robot(
            int index, 
            const Position & init_pos, 
            Map * map, 
            RobotType robot_type
        ): MovingObject(index, init_pos, map), robot_type(robot_type){}

        virtual string str() = 0;

        RobotType getType(){
            return robot_type;
        }
};

class RobotC: public Robot {
    friend class StudyPinkProgram;

    private:
        Criminal * criminal;

    public:
        RobotC(
            int index, 
            const Position & init_pos, 
            Map * map,
            RobotType robot_type, 
            Criminal* criminal
        ): Robot(index, init_pos, map, robot_type), criminal(criminal){}

        Position getNextPosition(){
            return criminal->getCurrentPosition();
        }

        void move(){
            pos = getNextPosition();
        }

        int getDistance(Character * character){
            if (character->getName() == "Sherlock") return pos - character->getCurrentPosition();
            else if (character->getName() == "Watson") return pos - character->getCurrentPosition();
        }

        string str() const {
            return "Robot[pos=" + pos.str() + ";type=C" + ";dist=]";
        }
};

class RobotS: public Robot {
    friend class StudyPinkProgram;

    private:
        Criminal * criminal;
        Sherlock * sherlock;

    public:
        RobotS(
            int index, 
            const Position & init_pos, 
            Map * map,
            RobotType robot_type, 
            Criminal* criminal,
            Sherlock * sherlock
        ): Robot(index, init_pos, map, robot_type), criminal(criminal), sherlock(sherlock){}

        Position getNextPosition(){
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

        void move(){
            Position next_position = getNextPosition();
            if (!next_position.isEqual(Position::npos)) pos = next_position;
        }

        int getDistance(){
            return pos - sherlock->getCurrentPosition();
        }

        string str () const {
            return "Robot[pos=" + pos.str() + ";type=S" + ";dist=" + to_string(getDistance()) + "]";
        }
};

class RobotW: public Robot {
    friend class StudyPinkProgram;

    private:
        Criminal * criminal;
        Watson * watson;
    
    public:
        RobotW(
            int index, 
            const Position & init_pos, 
            Map * map,
            RobotType robot_type, 
            Criminal* criminal,
            Watson * watson
        ): Robot(index, init_pos, map, robot_type), criminal(criminal), watson(watson){}

        Position getNextPosition(){
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

        void move(){
            Position next_position = getNextPosition();
            if (!next_position.isEqual(Position::npos)) pos = next_position;
        }

        int getDistance(){
            return pos - watson->getCurrentPosition();
        }

        string str () const {
            return "Robot[pos=" + pos.str() + ";type=S" + ";dist=" + to_string(getDistance()) + "]";
        }
};

class RobotSW: public Robot {
    friend class StudyPinkProgram;

    private:
        Criminal * criminal;
        Sherlock * sherlock;
        Watson * watson;

    public:
        RobotSW(
            int index, 
            const Position & init_pos, 
            Map * map,
            RobotType robot_type, 
            Criminal* criminal,
            Sherlock * sherlock,
            Watson * watson
        ): Robot(index, init_pos, map, robot_type), criminal(criminal), sherlock(sherlock), watson(watson){}

        Position getNextPosition(){
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

        void move(){
            Position next_position = getNextPosition();
            if (!next_position.isEqual(Position::npos)) pos = next_position;
        }

        int getDistance(){
            return (pos - sherlock->getCurrentPosition()) + (pos - watson->getCurrentPosition());
        }

        string str() const {
            return "Robot[pos=" + pos.str() + ";type=S" + ";dist=" + to_string(getDistance()) + "]";
        }
};

class StudyPinkProgram {
    friend class StudyPinkProgram;

    private:
        Configuration * config;
        Sherlock * sherlock;
        Watson * watson;
        Criminal * criminal;
        Map * map;
        ArrayMovingObject * arr_mv_objs;

    public:
        StudyPinkProgram(const string & config_file_path){
            config = new Configuration(config_file_path);

            sherlock = new Sherlock(
                1,
                config->getSherlockMovingRule(),
                config->getSherlockInitPos(), 
                map,
                config->getSherlockInitHp(), 
                config->getSherlockInitExp()
            );

            watson = new Watson(
                2,
                config->getWatsonMovingRule(),
                config->getWatsonInitPos(), 
                map,
                config->getWatsonInitHp(), 
                config->getWatsonInitExp()
            );

            criminal = new Criminal(
                0,
                config->getCriminalInitPos(), 
                map,
                sherlock, 
                watson
            );

            arr_mv_objs->add(criminal);
            arr_mv_objs->add(sherlock);
            arr_mv_objs->add(watson);
        }

        bool isStop() const {
            return 
                !sherlock->getHp() || 
                !watson->getHp() || 
                sherlock->getCurrentPosition().isEqual(criminal->getCurrentPosition()) ||
                watson->getCurrentPosition().isEqual(criminal->getCurrentPosition());
        }

        void printResult() const {
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

        void printStep(int si) const {
            cout << "Step: " << setw(4) << setfill('0') << si
                << "--"
                << sherlock->str() << "--|--" << watson->str() << "--|--" << criminal->str() << endl;
        }

        void run(bool verbose) {
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

        ~StudyPinkProgram();
};
////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* _H_STUDY_IN_PINK_2_H_ */

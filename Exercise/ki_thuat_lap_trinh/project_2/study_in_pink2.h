#ifndef _H_STUDY_IN_PINK_2_H_
#define _H_STUDY_IN_PINK_2_H_

#include "main.h"

class TestStudyInPink;

enum ItemType {MAGIC_BOOK, ENERGY_DRINK, FIRST_AID, EXCEMPTION_CARD, PASSING_CARD};
enum ElementType {PATH, WALL, FAKE_WALL};
enum RobotType {C = 0, S, W, SW};

class MapElement {
    friend class TestStudyInPink;

    protected:
        ElementType type;

    public:
        MapElement(ElementType in_type);

        virtual ~MapElement();

        virtual ElementType getType() const;
};

class Path : public MapElement {
    friend class TestStudyInPink;

    public:
        Path();
};

class Wall : public MapElement {
    friend class TestStudyInPink;

    public:
        Wall();
};

class FakeWall : public MapElement {
    friend class TestStudyInPink;

    private:
        int req_exp;
    
    public:
        FakeWall(int in_req_exp);

        int getReqExp() const;
};

class Position {
    friend class TestStudyInPink;

    private:
        int r, c;

    public:
        static const Position npos;

        Position(int r, int c);

        Position(const string & str_pos);

        int getRow() const;

        int getCol() const;

        void setRow(int r);

        void setCol(int c);

        string str() const;

        bool isEqual(Position y) const;

        bool isEqual(int in_r, int in_c) const;
};

int operator - (Position x, Position y);

class Map;

class MovingObject {
    friend class TestStudyInPink;

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
            const string & name
        );

        virtual ~MovingObject();

        virtual Position getNextPosition() = 0;

        virtual Position getCurrentPosition() const = 0;

        virtual void move() = 0;

        virtual string str() const = 0;

        string getName();
};

class Map {
    friend class TestStudyInPink;

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
        );

        ~Map();

        bool isValid (const Position & pos , MovingObject * mv_obj) const;

        int getNumRows() const;

        int getNumCols() const;
};

class Character: public MovingObject {
    friend class TestStudyInPink;

    public:
        Character(
            int index, 
            const Position pos, 
            Map * map,
            const string & name
        );

        virtual ~Character();

        virtual int getHp() const;

        virtual int getExp() const;

        virtual void setHp(int hp);

        virtual void setExp(int exp);

        virtual bool isInvincible() const;

        virtual void setInvincible();

        virtual void setVulnerable();
};

class Sherlock: public Character {
    friend class TestStudyInPink;

    private:
        int hp, exp;
        const string moving_rule;
        int move_step = 0;
        bool invincible = false;
        
    public:
        Sherlock(
            int index, 
            const string & moving_rule, 
            const Position & init_pos, 
            Map * map, 
            int init_hp, 
            int init_exp
        );

        virtual ~Sherlock();

        Position getNextPosition();

        Position getCurrentPosition() const;

        void move();

        string str() const;

        int getHp() const;

        int getExp() const;

        void setHp(int hp);

        void setExp(int exp);

        bool isInvincible() const;

        void setInvincible();

        void setVulnerable();

        void teleport(Position new_position);
};

class Watson: public Character {
    friend class TestStudyInPink;

    private:
        int hp, exp;
        const string moving_rule;
        int move_step = 0;
        bool invincible = false;

    public:
        Watson(
            int index, 
            const string & moving_rule, 
            const Position & init_pos, 
            Map * map, 
            int init_hp, 
            int init_exp
        );

        virtual ~Watson();

        Position getNextPosition();

        Position getCurrentPosition() const;

        void move();

        string str() const;

        int getHp() const;

        int getExp() const;

        void setHp(int hp);

        void setExp(int exp);

        bool isInvincible() const;

        void setInvincible();

        void setVulnerable();

        void teleport(Position new_position);
};

class Criminal: public Character{
    friend class TestStudyInPink;

    private:
        Sherlock * sherlock;
        Watson * watson;
        int move_step = 0;

    public:
        Criminal(
            int index, 
            const Position & init_pos, 
            Map * map, 
            Sherlock * sherlock, 
            Watson * watson
        );

        virtual ~Criminal();

        Position getNextPosition();

        Position getCurrentPosition() const;

        void move();

        int getMoveStep() const;

        string str() const;
};

class ArrayMovingObject {
    friend class TestStudyInPink;

    private:
        MovingObject ** arr_mv_objs;
        int count = 0, capacity;

    public:
        ArrayMovingObject(int capacity);

        virtual ~ArrayMovingObject();

        bool isFull() const;

        bool add(MovingObject * mv_obj);

        MovingObject * get(int index) const;

        int size() const;

        string str() const;
};

Position * positionArrayAnalysis(const string & position_array, int n);

class Configuration {
    friend class TestStudyInPink;

    private:
        int map_num_rows, map_num_cols;
        int max_num_moving_objects;
        int num_walls, num_fake_walls;
        Position * arr_walls = nullptr, * arr_fake_walls = nullptr;
        string sherlock_moving_rule, watson_moving_rule;
        Position sherlock_init_pos, watson_init_pos, criminal_init_pos;
        int sherlock_init_hp, sherlock_init_exp, watson_init_hp, watson_init_exp;
        int num_steps;

    public:
        Configuration(const string & filepath);

        virtual ~Configuration();

        string str() const;

        int getNumSteps() const;

        string getSherlockMovingRule() const;

        Position getSherlockInitPos() const;

        int getSherlockInitHp() const;

        int getSherlockInitExp() const;

        string getWatsonMovingRule() const;

        Position getWatsonInitPos() const;

        int getWatsonInitHp() const;

        int getWatsonInitExp() const;

        Position getCriminalInitPos() const;

        int getMaxNumMovingObjects() const;
};

class Robot;

class BaseItem {
    friend class TestStudyInPink;

    protected:
        BaseItem * next_item_ptr = nullptr;
        ItemType item_type;

    public:
        BaseItem(ItemType item_type);

        virtual ~BaseItem();

        virtual bool canUse(Character * obj, Robot * robot) = 0;

        virtual void use(Character * obj, Robot * robot) = 0;

        BaseItem * getNextItemPtr() const;

        void setNextItemPtr(BaseItem * next_item_ptr);

        ItemType getType() const;
};

int dCeil(double n);

int clamp(int n, int lowerBound, int upperBound);

class MagicBook: public BaseItem {
    friend class TestStudyInPink;

    public:
        MagicBook();

        virtual ~MagicBook();

        bool canUse(Character * obj, Robot * robot);

        void use(Character * obj, Robot * robot);
};

class EnergyDrink: public BaseItem {
    friend class TestStudyInPink;

    public:
        EnergyDrink();

        virtual ~EnergyDrink();

        bool canUse(Character * obj, Robot * robot);

        void use(Character * obj, Robot * robot);
};

class FirstAid: public BaseItem {
    friend class TestStudyInPink;

    public:
        FirstAid();

        virtual ~FirstAid();

        bool canUse(Character * obj, Robot * robot);

        void use(Character * obj, Robot * robot);
};

class ExcemptionCard: public BaseItem {
    friend class TestStudyInPink;

    public:
        ExcemptionCard();

        virtual ~ExcemptionCard();

        bool canUse(Character * obj, Robot * robot);

        void use(Character * obj, Robot * robot);
};

class PassingCard: public BaseItem {
    friend class TestStudyInPink;

    private:
        const string challenge;

    public:
        PassingCard(int t);

        virtual ~PassingCard();

        bool canUse(Character * obj, Robot * robot);

        void use(Character * obj, Robot * robot);
};

class BaseBag {
    friend class TestStudyInPink;

    protected:
        Character * obj;
        int count;
        int capacity;
        BaseItem * first_item;
    
    public:
        BaseBag(Character * obj);

        virtual ~BaseBag();

        virtual bool insert (BaseItem* item);

        virtual BaseItem* get();

        virtual BaseItem* get(ItemType itemType);

        virtual BaseItem* getRestore();

        virtual string str() const;
};

class SherlockBag: public BaseBag {
    friend class TestStudyInPink;

    public:
        SherlockBag(Sherlock * sherlock);

        virtual ~SherlockBag();
};

class WatsonBag: public BaseBag {
    friend class TestStudyInPink;

    public:
        WatsonBag(Watson * watson);

        virtual ~WatsonBag();
};

class Robot: public MovingObject {
    friend class TestStudyInPink;

    protected:
        RobotType robot_type;
        BaseItem * item;
        Map * map;
    
    public:
        Robot(
            int index, 
            const Position & init_pos, 
            Map * map, 
            RobotType robot_type
        );

        virtual string str() const = 0;

        RobotType getType() const;

        BaseItem * getItem() const;
};

class RobotC: public Robot {
    friend class TestStudyInPink;

    private:
        Criminal * criminal;

    public:
        RobotC(
            int index, 
            const Position & init_pos, 
            Map * map,
            Criminal* criminal
        );

        Position getNextPosition();

        Position getCurrentPosition() const;

        void move();

        int getDistance(Character * character) const;

        string str() const;
};

class RobotS: public Robot {
    friend class TestStudyInPink;

    private:
        Criminal * criminal;
        Sherlock * sherlock;

    public:
        RobotS(
            int index, 
            const Position & init_pos, 
            Map * map,
            Criminal* criminal,
            Sherlock * sherlock
        );

        Position getNextPosition();

        Position getCurrentPosition() const;

        void move();

        int getDistance() const;

        string str () const;
};

class RobotW: public Robot {
    friend class TestStudyInPink;

    private:
        Criminal * criminal;
        Watson * watson;
    
    public:
        RobotW(
            int index, 
            const Position & init_pos, 
            Map * map,
            Criminal* criminal,
            Watson * watson
        );

        Position getNextPosition();

        Position getCurrentPosition() const;

        void move();

        int getDistance() const;

        string str () const;
};

// RobotSW
class RobotSW: public Robot {
    friend class TestStudyInPink;

    private:
        Criminal * criminal;
        Sherlock * sherlock;
        Watson * watson;

    public:
        RobotSW(
            int index, 
            const Position & init_pos, 
            Map * map,
            Criminal* criminal,
            Sherlock * sherlock,
            Watson * watson
        );

        Position getNextPosition();

        Position getCurrentPosition() const;

        void move();

        int getDistance() const;

        string str() const;
};

class StudyPinkProgram {
    friend class TestStudyInPink;

    private:
        Configuration * config;
        Sherlock * sherlock;
        Watson * watson;
        Criminal * criminal;
        Map * map;
        ArrayMovingObject * arr_mv_objs;
        bool is_first_robot = true;
        SherlockBag * sherlock_bag;
        WatsonBag * watson_bag;

    public:
        StudyPinkProgram(const string & config_file_path);

        bool isStop() const;

        void printResult() const;

        void printStep(int si) const;

        void run(bool verbose);

        virtual ~StudyPinkProgram();
};

#endif

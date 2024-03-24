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
        ~Path();
};

class Wall : public MapElement {
    friend class TestStudyInPink;

    public:
        Wall();
        ~Wall();
};

class FakeWall : public MapElement {
    friend class TestStudyInPink;

    private:
        int req_exp;
    
    public:
        FakeWall(int in_req_exp);
        ~FakeWall();

        int getReqExp() const;
};

class Position {
    friend class TestStudyInPink;

    private:
        int r, c;

    public:
        static const Position npos;

        Position(int r, int c);

        ~Position();

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

        string getName() const;
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

    protected:
        int move_step = 0;

    public:
        Character(
            int index, 
            const Position pos, 
            Map * map,
            const string & name
        );

        virtual ~Character();

        Position getCurrentPosition() const;

        virtual int getHp() const {return 0;}
        
        virtual int getExp() const {return 0;};
        
        virtual void setHp(int hp) {};
        
        virtual void setExp(int exp) {};

        virtual void toggleProtectedStatus() {};

        virtual bool isDoneFighting() const {return true;}
};

class Protagonist: public Character {
    protected:
        int hp, exp;
        const string moving_rule;
        bool is_invincible = false;
        bool is_done_fighting = false;

    public:
        Protagonist(
            int index, 
            const Position pos, 
            Map * map,
            const string & moving_rule,
            int init_hp,
            int init_exp,
            const string & name
        );

        virtual ~Protagonist();

        int getHp() const;

        int getExp() const;

        void setHp(int hp);

        void setExp(int exp);

        bool isInvincible() const;

        void toggleProtectedStatus();

        bool isDoneFighting() const;

        void toggleFightingStatus();

        Position getNextPosition();

        void move();
};

class Sherlock: public Protagonist {
    friend class TestStudyInPink;
        
    public:
        Sherlock(
            int index, 
            const string & moving_rule, 
            const Position & init_pos, 
            Map * map, 
            int init_hp, 
            int init_exp
        );

        ~Sherlock();

        string str() const;
};

class Watson: public Protagonist {
    friend class TestStudyInPink;

    public:
        Watson(
            int index, 
            const string & moving_rule, 
            const Position & init_pos, 
            Map * map, 
            int init_hp, 
            int init_exp
        );

        ~Watson();

        string str() const;
};

class Criminal: public Character{
    friend class TestStudyInPink;

    private:
        Position previous_pos;
        Sherlock * sherlock;
        Watson * watson;

    public:
        Criminal(
            int index, 
            const Position & init_pos, 
            Map * map, 
            Sherlock * sherlock, 
            Watson * watson
        );

        ~Criminal();

        Position getNextPosition();

        Position getPreviousPosition();

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

        ~ArrayMovingObject();

        bool isFull() const;

        bool add(MovingObject * mv_obj);

        MovingObject * get(int index) const;

        int size() const;

        string str() const;
};

int countNumOfWall(const string & position_array);

Position * positionArrayAnalysis(const string & position_array, int n);

class Configuration {
    friend class TestStudyInPink;

    private:
        int map_num_rows = 0, map_num_cols = 0;
        int max_num_moving_objects = 0;
        int num_walls = 0, num_fake_walls = 0;
        Position * arr_walls = nullptr, * arr_fake_walls = nullptr;
        string sherlock_moving_rule = "", watson_moving_rule = "";
        Position sherlock_init_pos = Position(0, 0), watson_init_pos = Position(0, 0), criminal_init_pos = Position(0, 0);
        int sherlock_init_hp = 0, sherlock_init_exp = 0, watson_init_hp = 0, watson_init_exp = 0;
        int num_steps = 0;

    public:
        Configuration(const string & filepath);

        ~Configuration();

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

        int getNumRows() const;

        int getNumCols() const;

        int getNumWalls() const;

        Position * getArrayWalls() const;

        int getNumFakeWalls() const;

        Position * getArrayFakeWalls() const;
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

BaseItem * deepCopyItem(BaseItem * item);

int dCeil(double n);

int clamp(int n, int lowerBound, int upperBound);

class MagicBook: public BaseItem {
    friend class TestStudyInPink;

    public:
        MagicBook();

        ~MagicBook();

        bool canUse(Character * obj, Robot * robot);

        void use(Character * obj, Robot * robot);
};

class EnergyDrink: public BaseItem {
    friend class TestStudyInPink;

    public:
        EnergyDrink();

        ~EnergyDrink();

        bool canUse(Character * obj, Robot * robot);

        void use(Character * obj, Robot * robot);
};

class FirstAid: public BaseItem {
    friend class TestStudyInPink;

    public:
        FirstAid();

        ~FirstAid();

        bool canUse(Character * obj, Robot * robot);

        void use(Character * obj, Robot * robot);
};

class ExcemptionCard: public BaseItem {
    friend class TestStudyInPink;

    public:
        ExcemptionCard();

        ~ExcemptionCard();

        bool canUse(Character * obj, Robot * robot);

        void use(Character * obj, Robot * robot);
};

class PassingCard: public BaseItem {
    friend class TestStudyInPink;

    private:
        const string challenge;

    public:
        PassingCard(int t);

        ~PassingCard();

        bool canUse(Character * obj, Robot * robot);

        void use(Character * obj, Robot * robot);

        int getChallenge() const;
};

class BaseBag {
    friend class TestStudyInPink;

    protected:
        Character * obj;
        int count;
        int capacity;
        BaseItem * first_item = nullptr;
    
    public:
        BaseBag(Character * obj);

        virtual ~BaseBag();

        virtual bool insert (BaseItem* item);

        virtual BaseItem* get();

        virtual BaseItem* get(ItemType itemType);

        virtual string str() const;
};

class SherlockBag: public BaseBag {
    friend class TestStudyInPink;

    public:
        SherlockBag(Sherlock * sherlock);

        ~SherlockBag();
};

class WatsonBag: public BaseBag {
    friend class TestStudyInPink;

    public:
        WatsonBag(Watson * watson);

        ~WatsonBag();
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

        virtual ~Robot();

        virtual string str() const = 0;

        Position getCurrentPosition() const;

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

        ~RobotC();

        Position getNextPosition();

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
        
        ~RobotS();

        Position getNextPosition();

        void move();

        int getDistance() const;

        string str() const;
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

        ~RobotW();

        Position getNextPosition();

        void move();

        int getDistance() const;

        string str() const;
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

        ~RobotSW();

        Position getNextPosition();

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

        ~StudyPinkProgram();

        bool isStop() const;

        void printResult() const;

        void printStep(int si) const;

        void printVerboseStep() const;

        void run(bool verbose);
};

#endif

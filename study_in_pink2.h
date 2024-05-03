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

enum ItemType { MAGIC_BOOK, ENERGY_DRINK, FIRST_AID, EXCEMPTION_CARD, PASSING_CARD };
enum ElementType { PATH, WALL, FAKE_WALL };
enum RobotType { C=0, S, W, SW };

class MapElement {
protected:
    ElementType type;
public:
    MapElement(ElementType in_type) : type(in_type){}
    virtual ~MapElement(){};
    virtual ElementType getType() const{return type;}
};

class Path : public MapElement {
    private:
    public:
    Path() : MapElement(PATH){}
    ~Path(){}
};

class Wall : public MapElement {
    private:
    public:
    Wall() : MapElement(WALL){};
    ~Wall(){}
};

class FakeWall : public MapElement {
    private:
    int req_exp;
    public:
    FakeWall(int in_req_exp) : MapElement(FAKE_WALL),req_exp(in_req_exp){}
    int getReqExp () const{return req_exp;};
    ~FakeWall(){}
};

class Map {
private:
    int num_rows, num_cols;
    MapElement *** map;
public:
    Map(int num_rows, int num_cols, int num_walls, Position * array_walls, int num_fake_walls, Position * array_fake_walls);
    ~Map();
    bool isValid ( const Position & pos , MovingObject * mv_obj ) const ;
};

class Position {
private:
    int r, c;
public:
    static const Position npos;

    Position(int r=0, int c=0) : r(r), c(c){}

    Position(const string & str_pos);

    int getRow() const {return this->r;}
    int getCol() const {return this->c;}
    void setRow(int r) {this->r=r;}
    void setCol(int c) {this->c=c;}

    string str() const;

    bool isEqual(int in_r, int in_c) const;
    friend bool operator == (Position a, Position b){
        return a.getCol() == b.getCol() && a.getRow() == b.getRow();
    }
};

class MovingObject {
protected:
    int index;
    Position pos;
    Map * map;
    string name;

public:
    MovingObject(int index, const Position pos, Map * map, const string & name="") : index(index), pos(pos), map(map), name(name) {}
    virtual ~MovingObject(){};
    virtual Position getNextPosition() = 0;
    Position getCurrentPosition() const;
    virtual void move() = 0;
    virtual string str() const = 0;
    string getname(){return name;}
};

class Sherlock : public MovingObject/* TODO */ {
private:
    // TODO
    int hp;
    int exp;
    string moving_rule;
    int move_index=0;
public:
    Sherlock(int index, const string & moving_rule, const Position & init_pos, Map * map, int init_hp, int init_exp) : MovingObject(index, pos, map, "Sherlock"){
        this->index=index;
        this->pos=init_pos;
        this->hp=init_hp;
        this->exp=init_exp;
        this->map=map;
        this->name=name;
        this->moving_rule=moving_rule;
    }
    Position getNextPosition() override;
    void move() override;
    string str() const override;
    Position getpos(){return pos;}
    // getNextPosition
    // move
    // str
    // ...
};

class Watson : public MovingObject/* TODO */ {
private:
    // TODO
    int hp;
    int exp;
    string moving_rule;
    int move_index=0;
public:
    Watson(int index, const string & moving_rule, const Position & init_pos, Map * map, int init_hp, int init_exp) : MovingObject(index, pos, map, "Watson"){
        this->index=index;
        this->pos=init_pos;
        this->hp=init_hp;
        this->exp=init_exp;
        this->map=map;
        this->name=name;
        this->moving_rule=moving_rule;
    }
    Position getNextPosition() override;
    void move() override;
    string str() const override;
    Position getpos(){return pos;}
    // getNextPosition
    // move
    // str
    // ...
};
//Khoang cach Manhattan
class Criminal : public MovingObject/* TODO */ {
private:
    // TODO
    Sherlock * sherlock;
    Watson * watson;
public:
    Criminal(int index, const Position & init_pos, Map * map, Sherlock * sherlock, Watson * watson) : MovingObject(index, pos, map, "Criminal"){
        this->index=index;
        this->pos=init_pos;
        this->map=map;
        this->sherlock=sherlock;
        this->watson=watson;
    }
    Position getNextPosition() override;
    void move() override;
    string str() const override;
    // getNextPosition
    // move
    // str
    // ...
};

class ArrayMovingObject {
private:
    // TODO
    int count, capacity;
    MovingObject ** arr_mv_objs;
public:
    ArrayMovingObject(int capacity);
    ~ArrayMovingObject();
    bool isFull() const {
        return count == capacity;
    }
    bool add(MovingObject * mv_obj);
    MovingObject * get(int index) const;
    int size() const; // return current number of elements in the array
    string str() const;
};

class Configuration {
    friend class StudyPinkProgram;

private:
    // TODO
    int map_num_rows, map_num_cols;
    int max_num_moving_objects;
    int num_walls, num_fake_walls;
    Position * arr_walls, * arr_fake_walls;
    string sherlock_moving_rule, watson_moving_rule;
    Position sherlock_init_pos,  watson_init_pos;
    int sherlock_init_hp, sherlock_init_exp, watson_init_hp, watson_init_exp;
    Position criminal_init_pos;
    int num_steps;
public:
    Configuration(const string & filepath);
    ~Configuration(){
        delete [] arr_walls;
        delete [] arr_fake_walls;
    }
    string str() const;
};

// Robot, BaseItem, BaseBag,...
class Robot : public MovingObject{
    protected:
    RobotType robot_type;
    BaseItem * item;
    public:
    Robot(int index, const Position& init_pos, Map* map, RobotType robot_type, BaseItem* item) : MovingObject(index, init_pos, map), robot_type(robot_type), item(item) {}
    ~Robot(){}
    virtual int getDistance() const;
};

class RobotC : public Robot{
    private:
    Criminal * criminal;
    public:
    RobotC (int index , const Position & init_pos , Map * map , Criminal * criminal) : Robot(index, init_pos,map, C, NULL), criminal(criminal) {}
    Position getNextPosition() override;
    void move() override;
    int getDistance() const override{}
    string str() const override;
};
class RobotS : public Robot{
    private:
    Criminal * criminal;
    Sherlock * sherlock; 
    public:
    RobotS (int index , const Position & init_pos , Map * map , Criminal * criminal , Sherlock * sherlock) : Robot(index, init_pos,map, S, NULL), criminal(criminal), sherlock(sherlock) {}
    Position getNextPosition() override;
    void move() override;
    int getDistance() const override;
    string str() const override;
};
class RobotW : public Robot{
    private:
    Criminal * criminal;
    Watson * watson; 
    public:
    RobotW (int index , const Position & init_pos , Map * map , Criminal * criminal , Watson * watson) : Robot(index, init_pos,map, W, NULL), criminal(criminal), watson(watson) {}
    Position getNextPosition() override;
    void move() override;
    int getDistance() const override;
    string str() const override;
};
class RobotSW : public Robot{
    private:
    Criminal * criminal;
    Sherlock * sherlock;
    Watson * watson; 
    public:
    RobotSW (int index , const Position & init_pos , Map * map , Criminal * criminal , Sherlock * sherlock , Watson * watson) : Robot(index, init_pos,map, SW, NULL), criminal(criminal), sherlock(sherlock), watson(watson) {}
    Position getNextPosition() override;
    void move() override;
    int getDistance() const override;
    string str() const override;
};
//Character
class Character : public MovingObject{
    protected:
    public:
};
//BaseItem
class BaseItem{

};
// StudyPinkProgram
class StudyPinkProgram {
private:
    // Sample attributes
    Configuration * config;
    
    Sherlock * sherlock;
    Watson * watson;
    Criminal * criminal;
    
    Map * map;
    ArrayMovingObject * arr_mv_objs;


public:
    StudyPinkProgram(const string & config_file_path);

    bool isStop() const;

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
        // Note: This is a sample code. You can change the implementation as you like.
        // TODO
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

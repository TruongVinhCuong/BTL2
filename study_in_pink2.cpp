#include "study_in_pink2.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////
class TestStudyInPink;
//3.1
/*MapElement::MapElement(ElementType in_type){
        type=in_type;
    }
    
ElementType MapElement::getType() const{
    return this->type;
}

FakeWall::FakeWall(int in_req_exp) : MapElement(FAKE_WALL){
        req_exp=in_req_exp;
    }

int FakeWall::getReqExp() const{
    return this->req_exp;
}*/
//3.2
Map::Map(int num_rows, int num_cols, int num_walls, Position * array_walls, int num_fake_walls, Position * array_fake_walls) : num_rows(num_rows), num_cols(num_cols){
    map = new MapElement ** [num_rows];
    for(int i=0; i<num_rows; i++){
        map[i] = new MapElement * [num_cols];
        for(int j=0; j<num_cols; j++){
            map[i][j]=new Path();
        }
    }
    for(int i=0; i<num_walls; i++){
        delete map[array_walls[i].getRow()][array_walls[i].getCol()];
        map[array_walls[i].getRow()][array_walls[i].getCol()]= new Wall();
    }
    for(int i=0; i<num_fake_walls; i++){
        int in_req_exp = (array_fake_walls[i].getRow() * 257 + array_fake_walls[i].getCol() * 139 + 89) % 900 + 1;
        delete map[array_fake_walls[i].getRow()][array_fake_walls[i].getCol()];
        map[array_walls[i].getRow()][array_walls[i].getCol()]= new FakeWall(in_req_exp);
    }
}

Map::~Map(){
    for(int i=0; i<num_rows; i++){
        for (int j=0; j<num_cols; j++){
            delete [] map[i][j];
        }
        delete [] map[i];
    }
    delete [] map;
}

bool Map::isValid ( const Position & pos , MovingObject * mv_obj ) const{}


//3.3
Position::Position(const string & str_pos){
        string a=str_pos.substr(1, str_pos.find(",") - 1);
        string b=str_pos.substr(str_pos.find(",") + 1, str_pos.find(")") - 1);
        this->r=stoi(a);
        this->c=stoi(b);
        /*stringstream str2num1(a);
        int x=0;
        str2num1 >> x;
        stringstream str2num2(b);
        int y=0;
        str2num2 >> y;
        this->r=x;
        this->c=y;*/
    }

/*int Position::getRow() const{
        return this->r;
    }
int Position::getCol() const{
        return this->c;
    }
void Position::setRow(int r){
        this->r=r;
    }
void Position::setCol(int c){
        this->c=c;
    }*/

string Position::str() const{
        string thongtin="(" + to_string(r) + "," + to_string(c) + ")";
        return thongtin;
    }

bool Position::isEqual(int in_r, int in_c) const{
    return r==in_r && c==in_c;
}

const Position Position::npos=Position(-1,-1);
//3.4
/*MovingObject::MovingObject(int index, const Position pos, Map * map, const string & name=""){
        this->index=index;
        this->pos=pos;
        this->map=map;
        this->name=name;
    }*/
//3.5
Position Sherlock::getNextPosition(){
    char move=moving_rule[move_index];
    move_index=(move_index + 1)%moving_rule.size();
    Position next_pos=pos;
    switch(move){
        case 'L':
        next_pos.setCol(pos.getCol()-1);
        break;
        case 'R':
        next_pos.setCol(pos.getCol()+1);
        break;
        case 'U':
        next_pos.setRow(pos.getRow()+1);
        break;
        case 'D':
        next_pos.setRow(pos.getRow()-1);
        break;
    }
    return map->isValid(next_pos, this) ? next_pos : Position::npos;
}

void Sherlock::move(){
    Position next_pos = getNextPosition();
    if(!(next_pos == Position::npos)){
        pos=next_pos;
    }
}

string Sherlock::str() const{
    return "Sherlock[index=" + to_string(index) + ";pos=" + pos.str() + ";moving_rule=" + moving_rule + "]";
}
//3.6
Position Watson::getNextPosition(){
    char move=moving_rule[move_index];
    move_index=(move_index + 1)%moving_rule.size();
    Position next_pos=pos;
    switch(move){
        case 'L':
        next_pos.setCol(pos.getCol()-1);
        break;
        case 'R':
        next_pos.setCol(pos.getCol()+1);
        break;
        case 'U':
        next_pos.setRow(pos.getRow()+1);
        break;
        case 'D':
        next_pos.setRow(pos.getRow()-1);
        break;
    }
    return map->isValid(next_pos, this) ? next_pos : Position::npos;
}

void Watson::move(){
    Position next_pos = getNextPosition();
    if(!(next_pos == Position::npos)){
        pos=next_pos;
    }
}

string Watson::str() const{
    return "Watson[index=" + to_string(index) + ";pos=" + pos.str() + ";moving_rule=" + moving_rule + "]";
}
//3.7
Position Criminal::getNextPosition(){
    int move_Up = abs(pos.getRow() + 1 - sherlock->getpos().getRow()) + abs(pos.getCol() - sherlock->getpos().getCol()) + abs(pos.getRow() + 1 - watson->getpos().getRow()) +abs(pos.getCol() - watson->getpos().getCol());
    int move_Left = abs(pos.getRow() - sherlock->getpos().getRow()) + abs(pos.getCol() - 1 - sherlock->getpos().getCol()) + abs(pos.getRow() - watson->getpos().getRow()) +abs(pos.getCol() - 1 - watson->getpos().getCol());
    int move_Down = abs(pos.getRow() - 1 - sherlock->getpos().getRow()) + abs(pos.getCol() - sherlock->getpos().getCol()) + abs(pos.getRow() - 1 - watson->getpos().getRow()) +abs(pos.getCol() - watson->getpos().getCol());
    int move_Right = abs(pos.getRow() - sherlock->getpos().getRow()) + abs(pos.getCol() + 1 - sherlock->getpos().getCol()) + abs(pos.getRow() - watson->getpos().getRow()) +abs(pos.getCol() + 1 - watson->getpos().getCol());
    int max=-1;
    if(move_Up > max && map->isValid(pos.getRow() + 1,this)) max=move_Up;
    if(move_Left > max && map->isValid(pos.getCol() - 1,this)) max=move_Left;
    if(move_Down > max && map->isValid(pos.getRow() - 1,this)) max=move_Down;
    if(move_Right > max && map->isValid(pos.getCol() + 1,this)) max=move_Right;
    Position next_pos=pos;
    if(max==move_Up){
        next_pos.setRow(pos.getRow()+1);
        return next_pos;
    }
    if(max==move_Left){
        next_pos.setCol(pos.getCol()-1);
        return next_pos;
    }
    if(max==move_Down){
        next_pos.setRow(pos.getRow()-1);
        return next_pos;
    }
    if(max==move_Right){
        next_pos.setCol(pos.getCol()+1);
        return next_pos;
    }
    /*int max=-1;
    if(move_Up > max) max=move_Up;
    if(move_Left > max) max=move_Left;
    if(move_Down > max) max=move_Down;
    if(move_Right > max) max=move_Right;
    Position next_pos=pos;
    if(max==move_Up){
        next_pos.setRow(pos.getRow()+1);
    } else if(max==move_Left){
        next_pos.setCol(pos.getCol()-1);
    }else if(max==move_Down){
        next_pos.setRow(pos.getRow()-1);
    }else if(max==move_Right){
        next_pos.setCol(pos.getCol()+1);
    }
    return map->isValid(next_pos, this) ? next_pos : Position::npos;*/
}
void Criminal::move(){
    //pos=getNextPosition();
    Position next_pos = getNextPosition();
    if(!(next_pos == Position::npos)){
        pos=next_pos;
    }
}
string Criminal::str() const{
    return "Criminal[index=" + to_string(index) + ";pos=" + pos.str() + "]";
}
//3.8
ArrayMovingObject::ArrayMovingObject(int capacity) : count(0),capacity(capacity){
    arr_mv_objs = new MovingObject * [capacity];
}
ArrayMovingObject::~ArrayMovingObject(){
    for(int i=0; i<capacity; i++){
        delete [] arr_mv_objs[i];
    }
    delete [] arr_mv_objs;
}
bool ArrayMovingObject::add(MovingObject * mv_obj){
    if(isFull()){
        return false;
    } else{
        arr_mv_objs[count++]=mv_obj;
        return true;
    }
}
int ArrayMovingObject::size() const{
    return count;
}
string ArrayMovingObject::str() const{
    string result= "ArrayMovingObject[count =" + to_string(count) + " ;capacity =" + to_string(capacity);
    for(int i=0; i<count; i++){
        result+=";" + arr_mv_objs[i]->str();
        result+="]";
    }
    return result;
}
//3.9
Configuration::Configuration(const string & filepath){
    string arr[30];
    ifstream file1;
    file1.open(filepath);
    while(!file1.eof()){
        for(int i=0; i<30; i++){
            file1 >> arr[i];
        }
    }
    for(int i=0; i<30; i++){
        cout << arr[i] << endl;
    }
    file1.close();
    for(int i=1; i<30; i+=2){
        if(arr[i].find("MAP_NUM_ROWS") != string::npos){
            string a=arr[i].substr(arr[i].find("=") + 1);
            /*stringstream str2num(a);
            int x=0;
            str2num >> x;*/
            map_num_rows=stoi(a);
        } else if(arr[i].find("MAP_NUM_COLS") != string::npos){
            string a=arr[i].substr(arr[i].find("=") + 1);
            /*stringstream str2num(a);
            int x=0;
            str2num >> x;*/
            map_num_cols=stoi(a);
        } else if(arr[i].find("MAX_NUM_MOVING_OBJECTS") != string::npos){
            string a=arr[i].substr(arr[i].find("=") + 1);
            /*stringstream str2num(a);
            int x=0;
            str2num >> x;*/
            max_num_moving_objects=stoi(a);
        } else if(arr[i].find("ARRAY_WALLS") != string::npos){
            string a=arr[i].substr(arr[i].find("=") + 1);
            /*stringstream str2num(a);
            int x=0;
            str2num >> x;*/
            int count=0;
            for(int i=0; i<a.size(); i++){
                if(a[i]=='('){
                    ++count;
                }
            }
            num_walls=count;
            arr_walls=new Position[count];
            int mang[count*3];
            int count1=0;
            for(int i=0; i<a.size(); i++){
                if(a[i]=='(' || a[i]==',' || a[i]==')'){
                    mang[count1]=i;
                    ++count1;
                }
            }
            int count2=0;
            for(int i=0; i<count*3 - 2; i+=3){
                arr_walls[count2].setRow(stoi(a.substr(mang[i] + 1,mang[i+1] - mang[i] - 1)));
                arr_walls[count2].setCol(stoi(a.substr(mang[i+1] + 1,mang[i+2] - mang[i+1] - 1)));
                ++count2;
            }
        } else if(arr[i].find("ARRAY_FAKE_WALLS") != string::npos){
            string a=arr[i].substr(arr[i].find("=") + 1);
            /*stringstream str2num(a);
            int x=0;
            str2num >> x;*/
            int count=0;
            for(int i=0; i<a.size(); i++){
                if(a[i]=='('){
                    ++count;
                }
            }
            num_fake_walls=count;
            arr_fake_walls=new Position[count];
            int mang[count*3];
            int count1=0;
            for(int i=0; i<a.size(); i++){
                if(a[i]=='(' || a[i]==',' || a[i]==')'){
                    mang[count1]=i;
                    ++count1;
                }
            }
            int count2=0;
            for(int i=0; i<count*3 - 2; i+=3){
                arr_fake_walls[count2].setRow(stoi(a.substr(mang[i] + 1,mang[i+1] - mang[i] - 1)));
                arr_fake_walls[count2].setCol(stoi(a.substr(mang[i+1] + 1,mang[i+2] - mang[i+1] - 1)));
                ++count2;
            }
        } else if(arr[i].find("SHERLOCK_MOVING_RULE") != string::npos){
            string a=arr[i].substr(arr[i].find("=") + 1);
            sherlock_moving_rule=a;
        } else if(arr[i].find("SHERLOCK_INIT_POS") != string::npos){
            Position vitri;
            string a=arr[i].substr(arr[i].find("(") + 1,arr[i].find(",") - arr[i].find("(") - 1);
            string b=arr[i].substr(arr[i].find(",") + 1,arr[i].find(")") - arr[i].find(",") - 1);
            vitri.setRow(stoi(a));
            vitri.setCol(stoi(b));
            sherlock_init_pos=vitri;
            /*stringstream str2num(a);
            int x=0;
            str2num >> x;*/
        } else if(arr[i].find("SHERLOCK_INIT_HP") != string::npos){
            string a=arr[i].substr(arr[i].find("=") + 1);
            /*stringstream str2num(a);
            int x=0;
            str2num >> x;*/
            sherlock_init_hp=stoi(a);
        } else if(arr[i].find("SHERLOCK_INIT_EXP") != string::npos){
            string a=arr[i].substr(arr[i].find("=") + 1);
            /*stringstream str2num(a);
            int x=0;
            str2num >> x;*/
            sherlock_init_exp=stoi(a);
        } else if(arr[i].find("WATSON_MOVING_RULE") != string::npos){
            string a=arr[i].substr(arr[i].find("=") + 1);
            watson_moving_rule=a;
        } else if(arr[i].find("WATSON_INIT_POS") != string::npos){
            Position vitri;
            string a=arr[i].substr(arr[i].find("(") + 1,arr[i].find(",") - arr[i].find("(") - 1);
            string b=arr[i].substr(arr[i].find(",") + 1,arr[i].find(")") - arr[i].find(",") - 1);
            vitri.setRow(stoi(a));
            vitri.setCol(stoi(b));
            watson_init_pos=vitri;
            /*string a=arr[i].substr(arr[i].find("="));
            stringstream str2num(a);
            int x=0;
            str2num >> x;*/
        } else if(arr[i].find("WATSON_INIT_HP") != string::npos){
            string a=arr[i].substr(arr[i].find("=") + 1);
            /*stringstream str2num(a);
            int x=0;
            str2num >> x;*/
            watson_init_hp=stoi(a);
        } else if(arr[i].find("WATSON_INIT_EXP") != string::npos){
            string a=arr[i].substr(arr[i].find("=") + 1);
            /*stringstream str2num(a);
            int x=0;
            str2num >> x;*/
            watson_init_exp=stoi(a);
        } else if(arr[i].find("CRIMINAL_INIT_POS") != string::npos){
            Position vitri;
            string a=arr[i].substr(arr[i].find("(") + 1,arr[i].find(",") - arr[i].find("(") - 1);
            string b=arr[i].substr(arr[i].find(",") + 1,arr[i].find(")") - arr[i].find(",") - 1);
            vitri.setRow(stoi(a));
            vitri.setCol(stoi(b));
            criminal_init_pos=vitri;
            /*string a=arr[i].substr(arr[i].find("="));
            stringstream str2num(a);
            int x=0;
            str2num >> x;*/
        } else if(arr[i].find("NUM_STEPS") != string::npos){
            string a=arr[i].substr(arr[i].find("=") + 1);
            /*stringstream str2num(a);
            int x=0;
            str2num >> x;*/
            num_steps=stoi(a);
        }
    }
}

string Configuration::str() const {
    string wall=arr_walls[0].str();
    for(int i=1; i<num_walls; i++){
        wall+= ";" + arr_walls[i].str();
    }

    string fakewall=arr_fake_walls[0].str();
    for(int i=1; i<num_fake_walls; i++){
        fakewall+= ";" + arr_fake_walls[i].str();
    }

    string result= "Configuration[";
    result+= "\nMAP_NUM_ROWS=";
    result+= to_string(map_num_rows);
    result+= "\nMAP_NUM_COLS=";
    result+= to_string(map_num_cols);
    result+= "\nMAX_NUM_MOVING_OBJECTS=";
    result+= to_string(max_num_moving_objects);
    result+= "\nNUM_WALLS=";
    result+= to_string(num_walls);
    result+= "\nARRAY_WALLS=";
    result+= "[" + wall + "]";
    result+= "\nNUM_FAKE_WALLS=";
    result+= to_string(num_fake_walls);
    result+= "\nARRAY_FAKE_WALLS=";
    result+= "[" + fakewall + "]";
    result+= "\nSHERLOCK_MOVING_RULE=";
    result+= sherlock_moving_rule;
    result+= "\nSHERLOCK_INIT_POS=";
    result+= sherlock_init_pos.str();
    result+= "\nSHERLOCK_INIT_HP=";
    result+= to_string(sherlock_init_hp);
    result+= "\nSHERLOCK_INIT_EXP=";
    result+= to_string(sherlock_init_exp);
    result+= "\nWATSON_MOVING_RULE=";
    result+= watson_moving_rule;
    result+= "\nWATSON_INIT_POS=";
    result+= watson_init_pos.str();
    result+= "\nWATSON_INIT_HP=";
    result+= to_string(watson_init_hp);
    result+= "\nWATSON_INIT_EXP=";
    result+= to_string(watson_init_exp);
    result+= "\nCRIMINAL_INIT_POS=";
    result+= criminal_init_pos.str();
    result+= "\nNUM_STEPS=";
    result+= to_string(num_steps);
    result+= "\n]";
}
//3.10
//ROBOT C
void RobotC::move(){
    Position next_pos = getNextPosition();
    if(!(next_pos == Position::npos)){
        pos=next_pos;
    }
}
string RobotC::str() const{
    return "Robot[pos=" + pos.str() + ";type=C" + ";dist=";
}
//ROBOT S
Position RobotS::getNextPosition(){
    int move_Up = abs(pos.getRow() + 1 - sherlock->getpos().getRow()) + abs(pos.getCol() - sherlock->getpos().getCol());
    int move_Left = abs(pos.getRow() - sherlock->getpos().getRow()) + abs(pos.getCol() - 1 - sherlock->getpos().getCol());
    int move_Down = abs(pos.getRow() - 1 - sherlock->getpos().getRow()) + abs(pos.getCol() - sherlock->getpos().getCol());
    int move_Right = abs(pos.getRow() - sherlock->getpos().getRow()) + abs(pos.getCol() + 1 - sherlock->getpos().getCol());
    int min=1000000;
    if(move_Up < min && map->isValid(pos.getRow() + 1,this)) min=move_Up;
    if(move_Left < min && map->isValid(pos.getCol() - 1,this)) min=move_Left;
    if(move_Down < min && map->isValid(pos.getRow() - 1,this)) min=move_Down;
    if(move_Right < min && map->isValid(pos.getCol() + 1,this)) min=move_Right;
    Position next_pos=pos;
    if(min==move_Up){
        next_pos.setRow(pos.getRow()+1);
        return next_pos;
    }
    if(min==move_Left){
        next_pos.setCol(pos.getCol()-1);
        return next_pos;
    }
    if(min==move_Down){
        next_pos.setRow(pos.getRow()-1);
        return next_pos;
    }
    if(min==move_Right){
        next_pos.setCol(pos.getCol()+1);
        return next_pos;
    }
    /*int max=-1;
    if(move_Up > max) max=move_Up;
    if(move_Left > max) max=move_Left;
    if(move_Down > max) max=move_Down;
    if(move_Right > max) max=move_Right;
    Position next_pos=pos;
    if(max==move_Up){
        next_pos.setRow(pos.getRow()+1);
    } else if(max==move_Left){
        next_pos.setCol(pos.getCol()-1);
    }else if(max==move_Down){
        next_pos.setRow(pos.getRow()-1);
    }else if(max==move_Right){
        next_pos.setCol(pos.getCol()+1);
    }
    return map->isValid(next_pos, this) ? next_pos : Position::npos;*/
}
void RobotS::move(){
    Position next_pos = getNextPosition();
    if(!(next_pos == Position::npos)){
        pos=next_pos;
    }
}
int RobotS::getDistance() const {
    int dist= abs(this->pos.getRow() - sherlock->getpos().getRow()) + abs(this->pos.getCol() - sherlock->getpos().getCol());
    return dist;
}
string RobotS::str() const{
    return "Robot[pos=" + pos.str() + ";type=S" + ";dist=" + to_string(getDistance());
}
//ROBOT W
Position RobotW::getNextPosition(){
    int move_Up = abs(pos.getRow() + 1 - watson->getpos().getRow()) + abs(pos.getCol() - watson->getpos().getCol());
    int move_Left = abs(pos.getRow() - watson->getpos().getRow()) + abs(pos.getCol() - 1 - watson->getpos().getCol());
    int move_Down = abs(pos.getRow() - 1 - watson->getpos().getRow()) + abs(pos.getCol() - watson->getpos().getCol());
    int move_Right = abs(pos.getRow() - watson->getpos().getRow()) + abs(pos.getCol() + 1 - watson->getpos().getCol());
    int min=1000000;
    if(move_Up < min && map->isValid(pos.getRow() + 1,this)) min=move_Up;
    if(move_Left < min && map->isValid(pos.getCol() - 1,this)) min=move_Left;
    if(move_Down < min && map->isValid(pos.getRow() - 1,this)) min=move_Down;
    if(move_Right < min && map->isValid(pos.getCol() + 1,this)) min=move_Right;
    Position next_pos=pos;
    if(min==move_Up){
        next_pos.setRow(pos.getRow()+1);
        return next_pos;
    }
    if(min==move_Left){
        next_pos.setCol(pos.getCol()-1);
        return next_pos;
    }
    if(min==move_Down){
        next_pos.setRow(pos.getRow()-1);
        return next_pos;
    }
    if(min==move_Right){
        next_pos.setCol(pos.getCol()+1);
        return next_pos;
    }
    /*int max=-1;
    if(move_Up > max) max=move_Up;
    if(move_Left > max) max=move_Left;
    if(move_Down > max) max=move_Down;
    if(move_Right > max) max=move_Right;
    Position next_pos=pos;
    if(max==move_Up){
        next_pos.setRow(pos.getRow()+1);
    } else if(max==move_Left){
        next_pos.setCol(pos.getCol()-1);
    }else if(max==move_Down){
        next_pos.setRow(pos.getRow()-1);
    }else if(max==move_Right){
        next_pos.setCol(pos.getCol()+1);
    }
    return map->isValid(next_pos, this) ? next_pos : Position::npos;*/
}
void RobotW::move(){
    Position next_pos = getNextPosition();
    if(!(next_pos == Position::npos)){
        pos=next_pos;
    }
}
int RobotW::getDistance() const {
    int dist= abs(this->pos.getRow() - watson->getpos().getRow()) + abs(this->pos.getCol() - watson->getpos().getCol());
    return dist;
}
string RobotW::str() const{
    return "Robot[pos=" + pos.str() + ";type=W" + ";dist=" + to_string(getDistance());
}
//ROBOT SW
/*Position RobotSW::getNextPosition(){
    int move_Up = abs(pos.getRow() + 1 - sherlock->getpos().getRow()) + abs(pos.getCol() - sherlock->getpos().getCol()) + abs(pos.getRow() + 1 - watson->getpos().getRow()) +abs(pos.getCol() - watson->getpos().getCol());
    int move_Left = abs(pos.getRow() - sherlock->getpos().getRow()) + abs(pos.getCol() - 1 - sherlock->getpos().getCol()) + abs(pos.getRow() - watson->getpos().getRow()) +abs(pos.getCol() - 1 - watson->getpos().getCol());
    int move_Down = abs(pos.getRow() - 1 - sherlock->getpos().getRow()) + abs(pos.getCol() - sherlock->getpos().getCol()) + abs(pos.getRow() - 1 - watson->getpos().getRow()) +abs(pos.getCol() - watson->getpos().getCol());
    int move_Right = abs(pos.getRow() - sherlock->getpos().getRow()) + abs(pos.getCol() + 1 - sherlock->getpos().getCol()) + abs(pos.getRow() - watson->getpos().getRow()) +abs(pos.getCol() + 1 - watson->getpos().getCol());
    int min=1000000;
    if(move_Up < min && map->isValid(pos.getRow() + 1,this)) min=move_Up;
    if(move_Left < min && map->isValid(pos.getCol() - 1,this)) min=move_Left;
    if(move_Down < min && map->isValid(pos.getRow() - 1,this)) min=move_Down;
    if(move_Right < min && map->isValid(pos.getCol() + 1,this)) min=move_Right;
    Position next_pos=pos;
    if(min==move_Up){
        next_pos.setRow(pos.getRow()+1);
        return next_pos;
    }
    if(min==move_Left){
        next_pos.setCol(pos.getCol()-1);
        return next_pos;
    }
    if(min==move_Down){
        next_pos.setRow(pos.getRow()-1);
        return next_pos;
    }
    if(min==move_Right){
        next_pos.setCol(pos.getCol()+1);
        return next_pos;
    }
    int max=-1;
    if(move_Up > max) max=move_Up;
    if(move_Left > max) max=move_Left;
    if(move_Down > max) max=move_Down;
    if(move_Right > max) max=move_Right;
    Position next_pos=pos;
    if(max==move_Up){
        next_pos.setRow(pos.getRow()+1);
    } else if(max==move_Left){
        next_pos.setCol(pos.getCol()-1);
    }else if(max==move_Down){
        next_pos.setRow(pos.getRow()-1);
    }else if(max==move_Right){
        next_pos.setCol(pos.getCol()+1);
    }
    return map->isValid(next_pos, this) ? next_pos : Position::npos;
}*/
void RobotSW::move(){
    Position next_pos = getNextPosition();
    if(!(next_pos == Position::npos)){
        pos=next_pos;
    }
}
int RobotSW::getDistance() const {
    int dist= abs(this->pos.getRow() - sherlock->getpos().getRow()) + abs(this->pos.getCol() - sherlock->getpos().getCol()) + abs(this->pos.getRow() - watson->getpos().getRow()) + abs(this->pos.getCol() - watson->getpos().getCol());
    return dist;
}
string RobotSW::str() const{
    return "Robot[pos=" + pos.str() + ";type=SW" + ";dist=" + to_string(getDistance());
}
//3.11
//3.12
//3.13
//3.14

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
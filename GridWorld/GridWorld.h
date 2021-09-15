//Abdul Shaqildi CS251 Summer 2021
#ifndef _GRID_WORLD_H
#define _GRID_WORLD_H
#include <stdlib.h>
#include <vector>
#include <iostream>
using namespace std;
using std::vector;


class GridWorld {

private:
    struct Members {
        int ID;
        Members* next;
        Members* prev;
        Members(int _ID = 0, Members* _next = nullptr, Members* _prev = nullptr) {
            ID = _ID; next = _next; prev = _prev;
        }
    };
    struct District 
    {
        int size;
        Members* Front;
        Members* Back;
        District(int _size = 0, Members* _front = nullptr, Members* _back = nullptr) {
            size = _size; Front = _front; Back = _back;
        }
        ~District()
        {
            Members* p, * pnxt;
            p = Front;
            while (p != nullptr) {
                pnxt = p->next;
                delete p;
                p = pnxt;
            }
            size = 0;
            Front = nullptr;
            Back = nullptr;
            
        }
    };
    struct People 
    {
        int row;
        int col;
        bool alive;
        Members* BackDoor;
    };

    District DeadPop;
    vector<People> MemList;
    vector<vector<District>> Grid;
    int pop_size;
    int nextID;
    int rows;
    int cols;
   
public:
    /**
    * constructor:  initializes a "world" with nrows and
    *    ncols (nrows*ncols districtcs) in which all
    *    districtricts are empty (a wasteland!).
    */
   GridWorld(unsigned nrows, unsigned ncols)
    {
       
        rows = nrows;
        cols = ncols;
        vector<vector<District>> vect1(rows, vector<District>(cols));
        pop_size = 0;
        nextID = 0;
        Grid = vect1;
    
    }
   ~GridWorld() 
    {
       //destructor in District struct deleted all that needed to be deleted
    }

    /*
     * function: birth
     * description:  if row/col is valid, a new person is created
     *   with an ID according to rules in handout.  New person is
     *   placed in district (row, col)
     *
     * return:  indicates success/failure
     */
    bool birth(int row, int col, int& id) 
    {
        if(row > rows ||  col > cols)
        {
            return false;
        }
       
        if (DeadPop.size > 0)
        {
            
            Members* Mem;
            Mem = DeadPop.Front;
            id = Mem->ID;
            DeadPop.Front = Mem->next;
            delete Mem;
            DeadPop.size--;
        }
        else 
        {
            id = nextID;
            nextID += 1;
        }

        Members* NewMem = new Members(id, nullptr, nullptr);
        if(Grid[row][col].Front != nullptr)
        {
            NewMem->prev = Grid[row][col].Back;
            Grid[row][col].Back->next = NewMem;
            Grid[row][col].Back = NewMem;
        }
        else
        {
            Grid[row][col].Front = NewMem;
            Grid[row][col].Back = NewMem;
        }
        pop_size+=1;
        Grid[row][col].size+=1;
        if(MemList.size()<=id)
        {
            People Mem;
            Mem.row = row;
            Mem.col = col;
            Mem.alive = true;
            Mem.BackDoor = Grid[row][col].Back;
            MemList.push_back(Mem);
        }
        else
        {
            MemList[id].row = row;
            MemList[id].col = col;
            MemList[id].alive = true;
            MemList[id].BackDoor = Grid[row][col].Back;
        }
          
        return true; 
        
    }

    /*
     * function: death
     * description:  if given person is alive, person is killed and
     *   data structures updated to reflect this change.
     *
     * return:  indicates success/failure
     */
    bool death(int personID) {
       if(MemList.size()<= personID || MemList[personID].alive == false)
       {
           return false;
       }

       MemList[personID].alive = false;
       Members* Mem = new Members(personID, nullptr, nullptr);
       if (DeadPop.Front != nullptr)
       {
           Mem->prev = DeadPop.Back;
           DeadPop.Back->next = Mem;
           DeadPop.Back = Mem;
       }
       else
       {
           DeadPop.Front = Mem;
           DeadPop.Back = Mem;
       }
       DeadPop.size++;
       pop_size--;
       Members* curr = MemList[personID].BackDoor;
       Members* prev = curr->prev;
       if (prev != nullptr)
       {
           prev->next = curr->next;
           if (curr->next != nullptr)
           {
               curr->next->prev = prev;
           }
          
       }
       else if(prev == nullptr && Grid[MemList[personID].row][MemList[personID].col].size>1)
       {
           
           Grid[MemList[personID].row][MemList[personID].col].Front = curr->next;
           Grid[MemList[personID].row][MemList[personID].col].Front->prev = nullptr;

       }
       else
       {
           Grid[MemList[personID].row][MemList[personID].col].Front = curr->next;
       }
     
       if (Grid[MemList[personID].row][MemList[personID].col].Back == curr)
       {
           Grid[MemList[personID].row][MemList[personID].col].Back = curr->prev;
       }
       delete curr;
       Grid[MemList[personID].row][MemList[personID].col].size--;
        return true;
    }

    /*
     * function: whereis
     * description:  if given person is alive, his/her current residence
     *   is reported via reference parameters row and col.
     *
     * return:  indicates success/failure
     */
    bool whereis(int id, int& row, int& col)const 
    {
        if (MemList.size() <= id || MemList[id].alive == false)
        {
            return false;
        }

        
        row = MemList[id].row;
        col = MemList[id].col;
        return true;
        
    }

    /*
     * function: move
     * description:  if given person is alive, and specified target-row
     *   and column are valid, person is moved to specified district and
     *   data structures updated accordingly.
     *
     * return:  indicates success/failure
     *
     * comment/note:  the specified person becomes the 'newest' member
     *   of target district (least seniority) --  see requirements of members().
     */
    bool move(int id, int targetRow, int targetCol)
    {
        if (MemList.size() <= id || MemList[id].alive == false)
        {
            return false;
        }
        if (targetRow > rows ||  targetCol > cols)
        {
            return false;
        }
        if(MemList[id].row == targetRow && MemList[id].col == targetCol)
        {
            return true;
        }
        Members* curr = MemList[id].BackDoor;
        Members* prev = curr->prev;
        if (prev != nullptr)
        {
            prev->next = curr->next;
            if(curr->next != nullptr)
            {
                curr->next->prev = prev;
            }
            
            
        }
        else if(prev == nullptr && Grid[MemList[id].row][MemList[id].col].size>1)
        {
            Grid[MemList[id].row][MemList[id].col].Front = curr->next;
            Grid[MemList[id].row][MemList[id].col].Front->prev = nullptr;
            
        }
        else
        {
            Grid[MemList[id].row][MemList[id].col].Front = curr->next;
        }
        if (Grid[MemList[id].row][MemList[id].col].Back == curr)
        {
            Grid[MemList[id].row][MemList[id].col].Back = curr->prev;
        }
        delete curr;
        Grid[MemList[id].row][MemList[id].col].size--;


        MemList[id].row = targetRow;
        MemList[id].col = targetCol;

        Members* Mem = new Members(0, nullptr, nullptr);
        Mem->ID = id;
        if (Grid[targetRow][targetCol].Front != nullptr)
        {
            Mem->prev = Grid[targetRow][targetCol].Back;
            Grid[targetRow][targetCol].Back->next = Mem;
            Grid[targetRow][targetCol].Back = Mem;
        }
        else
        {
            Grid[targetRow][targetCol].Front = Mem;
            Grid[targetRow][targetCol].Back = Mem;
        }
        Grid[targetRow][targetCol].size++;
        MemList[id].BackDoor = Grid[targetRow][targetCol].Back;
        return true;
    }

    std::vector<int>* members(int row, int col)const 
    {
       
        vector<int> *Mems  = new vector<int>();
        if (row > rows ||  col > cols)
        {
            return Mems;
        }
        

        Members* Mem;
        Mem = Grid[row][col].Front;
        while (Mem != nullptr)
        {
            Mems->push_back(Mem->ID);
            Mem = Mem->next;

        }
        delete Mem;

        return Mems;
    }

    /*
     * function: population
     * description:  returns the current (living) population of the world.
     */
    int population()const 
    {
      
        return pop_size;
    }

    /*
     * function: population(int,int)
     * description:  returns the current (living) population of specified
     *   district.  If district does not exist, zero is returned
     */
    int population(int row, int col)const 
    {
        if(row >= rows || col >= cols)
        {
            return 0;
        }
        return  Grid[row][col].size;
        
    }

    /*
     * function: num_rows
     * description:  returns number of rows in world
     */
    int num_rows()const 
    {
        return rows;
    }

    /*
     * function: num_cols
     * description:  returns number of columns in world
     */
    int num_cols()const
    {
        return cols;
    }



};

#endif
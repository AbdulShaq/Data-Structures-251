#include "GridWorld.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using std::cout;
using std::cin;
using std::string;

/**
 * simple driver program exercising some of the
 *   member functions in GridWorld.
 *
 */

enum CmdResult { failure, success, quit };

/* prints contens of an integer vector */
void pvec(vector<int>* v) {
    cout << "  [ ";
    for (int x : *v) {
        cout << x << " ";
    }
    cout << "]\n";
}

void arg_err(const string& cmd, int correct_nargs) {
    cout << "usage error: " << cmd << " expects "
        << correct_nargs << " argument(s)\n";
}

/* function for evaluating/applying a command:
 *
 *   cmd is a command name
 *   args[] is an array of nargs integer arguments
 *   gw is the GridWorld to which the command is applied if possible.
 *
 * returns:
 *   success / failure depending whether the command exists, has correct
 *     number of parameters and if/when invoked on the gw object, the success
 *     or failure operation.
 *
 *   Or returns quit if the "quit" command was issued.
 *
 */
CmdResult eval_cmd(GridWorld* gw, const string& cmd, int args[], int nargs) {

    if (cmd == "birth") {
        int id;

        if (nargs != 2) {
            arg_err(cmd, 2);
            return failure;
        }
        else {
            if (!gw->birth(args[0], args[1], id)) {
                cout << "  operation failed\n";
                return failure;
            }
            else {
                cout << "  operation succeeded\n";
                cout << "  PersonID: " << id << "\n";
                return success;
            }
        }
    }
    if (cmd == "death" || cmd == "kill") {
        if (nargs != 1) {
            arg_err(cmd, 1);
            return failure;
        }
        else {
            if (!gw->death(args[0])) {
                cout << "  operation failed\n";
                return failure;
            }
            else {
                cout << "  operation succeeded\n";
                return success;
            }
        }
    }
    if (cmd == "move") {
        if (nargs != 3) {
            arg_err(cmd, 3);
            return failure;
        }
        else {
            if (!gw->move(args[0], args[1], args[2])) {
                cout << "  operation failed\n";
                return failure;
            }
            else {
                cout << "  operation succeeded\n";
                return success;
            }
        }
    }
    if (cmd == "members") {
        if (nargs != 2) {
            arg_err(cmd, 2);
            return failure;
        }
        else {
            vector<int>* members;
            members = gw->members(args[0], args[1]);
            pvec(members);
            delete members;
            return success;
        }
    }
    if (cmd == "whereis") {
        if (nargs != 1) {
            arg_err(cmd, 1);
            return failure;
        }
        else {
            int row, col;

            if (!gw->whereis(args[0], row, col)) {
                cout << "  operation failed\n";
                return failure;
            }
            else {
                cout << "  district (" << row << ", " << col << ")\n";
                return success;
            }
        }
    }
    if (cmd == "pop" || cmd == "population") {
        if (nargs == 0) {
            cout << gw->population() << "\n";
            return success;
        }
        else if (nargs == 2) {
            cout << gw->population(args[0], args[1]) << "\n";
            return success;
        }
        else {
            arg_err(cmd, 0);
            cout << "      OR\n";
            arg_err(cmd, 2);
            return failure;
        }
    }
    if (cmd == "nrows" || cmd == "num_rows") {
        if (nargs != 0) {
            arg_err(cmd, 0);
            return failure;
        }
        else {
            cout << gw->num_rows() << "\n";
            return success;
        }
    }
    if (cmd == "ncols" || cmd == "num_cols") {
        if (nargs != 0) {
            arg_err(cmd, 0);
            return failure;
        }
        else {
            cout << gw->num_cols() << "\n";
            return success;
        }
    }
    if (cmd == "quit") {
        if (nargs != 0) {
            arg_err(cmd, 0);
            return failure;
        }
        return quit;
    }
    cout << "command '" << cmd << "' not supported\n";
    return failure;
}




/*
 * defaults to a 5x5 grid.
 *
 * Recommendation:  why not modify so you can take command-line
 *  arguments specifying the grid dimensions?
 */
int main() {
    GridWorld* gw = new GridWorld(5, 5);
    string line;

    cout << "Welcome to the GridWorld Interactive Frontend\n";
    cout << "=============================================\n";

    cout << "COMMANDS:\n\n";

    cout << "    birth <row> <col>\n";
    cout << "    death <id>\n";
    cout << "    move <id> <targe-row> <target-col>\n";
    cout << "    members <row> <col>\n";
    cout << "    whereis <id> \n";
    cout << "    population \n";
    cout << "    population <row> <col>\n";
    cout << "    num_rows\n";
    cout << "    num_cols\n";
    cout << "    quit\n\n";

  

    bool done = false;

    do {
        cout << "cmd> ";

        // read a complete line
        std::getline(std::cin, line);

        // now create a "stringstream" on the line just read
        std::stringstream ss(line);

        int i = 0;
        string cmd;
        string junk;

        ss >> cmd;  // extract first token as command

        // up to 3 integer arguments should follow
        int args[3];
        int n = 0;
        // extract command arguments
        while (n < 3 && ss >> args[n]) {
            n++;
        }

        // now we have the command string and have
        //   parsed 0-3 integer arguments into args[]
        //
        // let eval_cmd try to apply the command
        if (eval_cmd(gw, cmd, args, n) == quit)
            done = true;

    } while (!done && !cin.eof());

    delete gw;

    return 0;
}
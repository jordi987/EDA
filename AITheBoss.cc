#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME THEBOSS


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

  typedef vector<int> VE;

/*  bool safe(Pos& pos) {
    if (cell(pos).type != Wall and not cell(pos).haunted and cell(pos).id == 1) return false;
    else return true;
  }*/

  /*bool dfsfarmers(Pos pos) {
   if (unit(cell(pos).id).type == Knight and unit(cell(pos).id).player > 0) return false;
    if (unit(cell(pos).id).type == Witch) return false;
  else if (cell(pos).type == Wall) return false;
    /*else {
        int x, y;
        x = pos.i;
        y = pos.j;
        if (x + 1 < 37 and dfsfarmers(pos+Bottom)) return true;
        if (x - 1 < 37 and dfsfarmers(pos+Right)) return true;
        if (y + 1 < 37 and dfsfarmers(pos+Top)) return true;
        if (y - 1 < 37 and dfsfarmers(pos+Left)) return true;
    }
    else return true;
  }*/

  virtual void play () {
    //TODO farmers dfs teniendo en cuenta que no este ocupada
    // que no haya brujan a distancia manhattan y knights. Si mal salud tirar para atras
    VE f = farmers(0);
    for (int id : f) {
      Pos pos= unit(id).pos;
    }


    VE k = knights(0);
    for (int id : k) {
      //TODO: knight
      command(id, Left);

    }
    VE w = witches(0);
    for (int id : w) {
      //TODO: bruja bfs que mate todo aquello que este cerca
      command(id, Right);
    }

  }

};



/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);

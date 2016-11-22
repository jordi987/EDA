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

  bool safe(Pos& pos) {
    if (cell(pos+Bottom).type == Wall or cell(pos+Bottom).haunted or cell(pos+Bottom).id == 1) return false;
    else return true;
  }

  virtual void play () {
    VE f = farmers(0);
    for (int id : f) {
      //TODO detectar a los de mi equipo
      Pos pos= unit(id).pos;
      if ( not safe(pos) and cell(pos+Right).type == Empty) command(id,Right);
      else if ( not safe(pos) and cell(pos+Left).type == Empty) command(id, Left);
      else command(id, Bottom);
    }

    VE k = knights(0);
    for (int id : k) {
      //TODO: knight
      command(id, None);

    }
    VE w = witches(0);
    for (int id : w) {
      //TODO: witches in the exactly position
      command(id, None);
    }

  }

};



/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);

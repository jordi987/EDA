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
  typedef vector <vector <bool> > graph;

  bool bfs(graph& g, int x, int y){
    if (!g[x][y]) {
      g[x][y] = true;

    }
  }


  virtual void play () {
    //TODO farmers dfs teniendo en cuenta que no este ocupada
    // que no haya brujan a distancia manhattan y knights. Si mal salud tirar para atras
    VE f = farmers(0);
    for (int id : f) {
      graph g(37, vector<bool>(37, false));
      if (unit(id).health >= 50) {
        int x,y;
        x = unit(id).pos.i;
        y = unit(id).pos.j;
        //TODO bfs de hasta distancia tres y si todos libres random

      }
      else command(id, None);
    }


    VE k = knights(0);
    for (int id : k) {
      //TODO: knight
      command(id, Left);

    }
    VE w = witches(0);
    for (int id : w) {

    }      //TODO: bruja bfs que mate todo aquello que este cerca
      command(id, None);
  }
};

/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);

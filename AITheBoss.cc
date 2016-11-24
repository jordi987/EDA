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

  map <int, bool> path; //farmers map para saber si tienen camino si no tienen bfs



  bool security(const Pos& p) {
    if (cell(p).type == Wall) return false;
    else if (cell(p).haunted) return false;
    else if (cell(p).id != -1) return false;
    else return true;
  }

  Dir dirfast(Pos& act, Pos& aux) {
    int x,y,a,b;
    x = act.i;
    y = act.j;
    a = aux.i;
    b = aux.j;
    if ( x == a and y < b) return Top;
    if ( x == a and y > b) return Bottom;
    if ( x > a and y == b) return Left;
    if ( x < a and y == b) return Right;
    else None;
  }

  // TODO: si hay mas de una posicion vacia random!!!!
  Pos bfs_farmers(graph& g, Pos& pos, queue <Pos>& Q ){
    bool found = false; // camino
    Q.push(pos);
    while (not Q.empty() and not found) {
      Pos aux = Q.front();  Q.pop();
      int x = aux.i;
      int y = aux.j;
      if (!g[x][y]) {
        g[x][y] = true;
        Pos aux2;
       aux2 = aux + Top;
        if ( security(aux2) and cell(aux2).owner >= 0) {
          Q.push(aux2);
        }
        else if (security(aux2) and cell(aux2).owner == -1) {
          found = true;
          return aux2;
        }
        aux2 = aux + Right;
        if ( security(aux2) and cell(aux2).owner >= 0) {
          Q.push(aux2);
        }
        else if (security(aux2) and cell(aux2).owner == -1) {
          found = true;
          return aux2;
        }
        aux2 = aux + Left;
        if ( security(aux2) and cell(aux2).owner >= 0) {
           Q.push(aux2);
        }
        else if (security(aux2) and cell(aux2).owner == -1) {
          found = true;
          return aux2;
        }
        aux2 = aux + Bottom;
        if ( security(aux2) and cell(aux2).owner >= 0) {
          Q.push(aux2);
        }
        else if (security(aux2) and cell(aux2).owner == -1) {
          found = true;
          return aux2;
        }
      }
    }
  }


  virtual void play () {
    VE f = farmers(0);
    for (int id : f) {
      graph g(37, vector<bool>(37, false));
    //  map <int, bool>::const_iterator aux = path.find(id);
    //  if (aux == path.end() ) path.insert(make_pair(id, false));
      //  map <int, bool>::const_iterator i = path.find(id);
    //  if (unit(id).health >= 50 and (i->second == false)) {
        Pos act = unit(id).pos;
        Pos aux;
        queue <Pos> Q;
        aux = bfs_farmers(g, act, Q);
        command(id, dirfast(act,aux) );
      //}
    }


    VE k = knights(0);
    for (int id : k) {
      //TODO: knight

    }
    VE w = witches(0);
    for (int id : w) {
        //TODO: bruja bfs que mate todo aquello que este cerca
    }
  }
};

/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);

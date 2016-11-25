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
  typedef pair <int, bool> Frm; // int = distancia y bool es camino

  map <int, pair<Pos, bool> > cami; //farmers map para saber si tienen camino si no tienen bfs.
  //pos es la posicion a la que tiene que ir.

  map <Pos, int > distancias; // si la casilla esta en distancias es que hay un farmer
  //que tiene que ir a esa posicion. Si hay otro farmer que tiene que ir a la misma
  //cell entonces coger el que tenga la distancia mas corta y hacer que el otro busque otra


  bool security(const Pos& p) {
    if (cell(p).type == Wall) return false;
    else if (cell(p).haunted) return false;
    else if (cell(p).id != -1) return false;
    else return true;
  }

  Dir dirfast(Pos& act, Pos& aux) {
    if ( act.j == aux.j and act.i > aux.i) return Top;
    if ( act.j == aux.j and act.i < aux.i) return Bottom;
    if ( act.j > aux.j and act.i == aux.i) return Left;
    if ( act.j < aux.j and act.i == act.i) return Right;
    else None;
  }

  // TODO: si hay mas de una posicion vacia random!!!!
  Pos bfs_farmers(Pos& pos, queue <Pos>& Q ){
    bool found = false; // camino
    Q.push(pos);
    while (not Q.empty() and not found) {
      Pos seg = Q.front();  Q.pop();
      Pos seg2;
      seg2 = seg + Top;
      //SOLO TIENES QUE AÑADIR POSICIONES EN LA COLA SI NOT FOUND D:
    }
  }
  virtual void play () {
    VE f = farmers(0);
    for (int id : f) {
      //TODO : revisar
      Pos act = unit(id).pos;
      Pos fut;
      queue<Pos> Q;
      auto it = cami.find(id);
      if (it != cami.end()) {
        if (it->second.second)  {
          command(id, dirfast(act, it->second.first));
        }
        else {
          fut = bfs_farmers(act, Q);
        }
      }else {
        cami.insert(make_pair(id,pair<Pos,bool>(act,false)));
        it ->second.first = bfs_farmers(act, Q);
        it ->second.second = true;
      }
    }


//1. provar que funcione la funcion dirfast

// si tiene cmamino enviar pos actual y final


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

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

  bool security(const Pos& p) {
    if (cell(p).type == Wall) return false;
    else if (cell(p).haunted) return false;
    else if (cell(p).id != -1) return false;
    else return true;
  }

  Dir dirfast(const Pos& act, const Pos& aux) {
    if ( act.j == aux.j and act.i > aux.i) return Top;
    if ( act.j == aux.j and act.i < aux.i) return Bottom;
    if ( act.j > aux.j and act.i == aux.i) return Left;
    if ( act.j < aux.j and act.i == aux.i) return Right;
    if (act.j == aux.j and act.i == aux.i) return None;
  }

  Pos res_bfs (const Pos& res, const Pos& act, const map <Pos,Pos>& camino) {
    auto it = camino.find(res);
    Pos aux = it->second;
    while ( aux != act) {
        it = camino.find(aux);
        aux = it->second;
        break;
    }
    return it->first;
  }


  Pos bfs_farmers(const Pos& act, queue <Pos>& Q){
    bool found = false; // camino
    map <Pos, Pos> camino;
    vector<Pos> posibles;
    Q.push(act);
    Pos ant = Q.front(); // anterior es para que el bfs en la busqueda no mire la posicion de donde viene. El "padre"
    while (not found and not Q.empty() ) {
      Pos pos = Q.front();
      Q.pop();
      // Miramos arriba
      Pos pos2 = pos + Top;
      if (security(pos2) and pos2 != ant) {
        if (cell(pos2).owner == -1) {
          found = true;
          posibles.push_back(pos2);
          camino.insert(make_pair(pos2,pos));
        } else if (cell(pos2).owner >= 0) {
          Q.push(pos2);
          camino.insert(make_pair(pos2,pos));
        }
      }
      //miramos izquierda
      pos2 = pos + Left;
      if (security(pos2) and pos2 != ant) {
        if (cell(pos2).owner == -1) {
          found = true;
          posibles.push_back(pos2);
          camino.insert(make_pair(pos2,pos));
        } else if (cell(pos2).owner >= 0) {
          Q.push(pos2);
          camino.insert(make_pair(pos2,pos));
        }
      }

      //miramos abajo
      pos2 = pos + Bottom;
      if (security(pos2) and pos2 != ant) {
        if (cell(pos2).owner == -1) {
          found = true;
          posibles.push_back(pos2);
          camino.insert(make_pair(pos2,pos));
        } else if (cell(pos2).owner >= 0) {
          Q.push(pos2);
          camino.insert(make_pair(pos2,pos));
        }
      }
      //miramos derecha
      pos2 = pos + Right;
      if (security(pos2) and pos2 != ant) {
        if (cell(pos2).owner == -1) {
          found = true;
          posibles.push_back(pos2);
          camino.insert(make_pair(pos2,pos));
        } else if (cell(pos2).owner >= 0) {
          Q.push(pos2);
          camino.insert(make_pair(pos2,pos));
        }
      }
      ant = pos;
    }
    if (posibles.size() > 0) return res_bfs(posibles[random(0, posibles.size() - 1)], act, camino);
    else if (posibles.size() == 0 ) return act;
  }


  virtual void play () {
    VE f = farmers(0);
    for (int id : f) {
      //TODO : revisar
      if (round() == 5) cerr << "ronda 5" << endl;
      Pos act = unit(id).pos;
      queue<Pos> Q; //cola para bfs
      Pos fin = bfs_farmers(act, Q);
      command(id,dirfast(act, fin));
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

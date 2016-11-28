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

//TODO se quedan parados farmers y caballeros acceso error memoria


  //INICIALIZAMOS MATRIZES

  void secureWithces(graph& g, const Pos& p) {
    for (int a = 0; a < 4; ++a) {
      Pos sec = p;
      //primero bottom, luego right, luego top, luego left
      for ( int b = 0; b < 3; ++b) {
        sec = sec + Dir(a*2);
        if (pos_ok(sec)) {
          g[sec.i][sec.j] = false;
          if ( a == 0 or a == 2) {
            Pos sec2 = sec + Right;
            Pos sec3 = sec2 + Right;
            Pos sec4 = sec + Left;
            Pos sec5 = sec4 + Left;
            if (b == 0) {
              if (pos_ok(sec2)) g[sec2.i][sec2.j] = false;
              if (pos_ok(sec3)) g[sec3.i][sec3.j] = false;
              if (pos_ok(sec4)) g[sec4.i][sec4.j] = false;
              if (pos_ok(sec5)) g[sec5.i][sec5.j] = false;
            } else if (b == 1) {
              if (pos_ok(sec2)) g[sec2.i][sec2.j] = false;
              if (pos_ok(sec4)) g[sec4.i][sec4.j] = false;
            }
          }
        }
      }
    }
  }

  void secureKnight(graph& g,const Pos& p) {
    for (int a = 0; a < 8; ++a) {
      Pos sec = p;
      sec = sec + Dir(a);
      if (pos_ok(sec)) g[sec.i][sec.j] = false;
    }
  }

  void inic (graph& farm) {
    for (int i = 0; i < rows(); ++i) {
      for ( int  j = 0; j < cols(); ++j) {
        //muro
        if (cell(i,j).type == Wall) farm[i][j] = false;
        //farm
        if (cell(i,j).id != -1 and unit(cell(i,j).id).type == Farmer) farm[i][j] = false;
        //witches y posiciones a atacar
        if (cell(i,j).id != -1 and unit(cell(i,j).id).type == Witch) {
          farm[i][j] = false;
          Pos p;
          p.i = i;
          p.j = j;
          secureWithces(farm, p);
        }
        //knights y posiciones a atacar
        //TODO PAU CON unit(cell(i,j).id).player > 0  o sin esto en el if
        if (cell(i,j).id != -1 and unit(cell(i,j).id).type == Knight) {
          farm[i][j] = false;
          Pos p;
          p.i = i;
          p.j = j;
          secureKnight(farm, p);
        }
      }
    }
  }

  void inic2(graph& kni) {
    for (int i = 0; i < rows(); ++i) {
      for ( int  j = 0; j < cols(); ++j) {
        //muro
        if (cell(i,j).type == Wall) kni[i][j] = false;
        //farm mios
        if (cell(i,j).id != -1 and unit(cell(i,j).id).type == Farmer and unit(cell(i,j).id).player == 0) kni[i][j] = false;
        //witches y posiciones a atacar
        if (cell(i,j).id != -1 and unit(cell(i,j).id).type == Witch) {
          kni[i][j] = false;
          Pos p;
          p.i = i;
          p.j = j;
          secureWithces(kni, p);
        }
      }
    }
  }

  void inic3(graph& witch) {
    for (int i = 0; i < rows(); ++i) {
      for ( int  j = 0; j < cols(); ++j) {
        //muro
        if (cell(i,j).type == Wall) witch[i][j] = false;
        //farmers mios
        if (cell(i,j).id != -1 and unit(cell(i,j).id).type == Farmer and unit(cell(i,j).id).player == 0) witch[i][j] = false;
        //witches y posiciones a atacar
        if (cell(i,j).id != -1 and unit(cell(i,j).id).type == Witch and unit(cell(i,j).id).player > 0) {
          witch[i][j] = false;
          Pos p;
          p.i = i;
          p.j = j;
          secureWithces(witch, p);
        }
      }
    }
  }

  //FINALIZAMOS INICIALIZACIONES MATRIZES

  Dir dirfast(const Pos& act, const Pos& aux) {
    if ( act.j == aux.j and act.i > aux.i) return Top;
    if ( act.j == aux.j and act.i < aux.i) return Bottom;
    if ( act.j > aux.j and act.i == aux.i) return Left;
    if ( act.j < aux.j and act.i == aux.i) return Right;
    if (act.j == aux.j and act.i == aux.i) return None;
  }

  Pos res_bfs (const Pos& res, const Pos& act, const map <Pos,Pos>& camino) {
    auto it = camino.find(res);
    auto it2 = camino.find(act);
    while ( (it->second) != (it2->first)) {
        it = camino.find(it->second);
    }
    return it->first;
  }

  //BFS

  Pos bfs_knight(const Pos& act, queue <Pos>& Q, const graph& kni){
    cerr << "hola" << endl;
    bool found = false; // camino
    map <Pos, Pos> camino; //llave hijo, referencia padre
    vector<Pos> posibles;
    graph vis(rows(), vector <bool> (cols(), false));
    Pos padre;
    padre.i = -1;
    padre.j = -1;
    camino.insert(make_pair(act,padre));
    Q.push(act);
    vis[act.i][act.j] = true;
    while (not found and not Q.empty() ) {
      Pos pos = Q.front();
      Q.pop();
      for ( int i = 0; i < 8; ++i) {
        Pos pos2 = pos + Dir(i);
        if (pos_ok(pos2) and kni[pos2.i][pos2.j] and !vis[pos2.i][pos2.j]) {
          if (unit(cell(pos2).id).type == Farmer and unit(cell(pos2).id).player > 0) {
            found = true;
            posibles.push_back(pos2);
            camino.insert(make_pair(pos2,pos));
          } else if (unit(cell(pos2).id).type == Knight and unit(cell(pos2).id).player > 0){
            found = true;
            posibles.push_back(pos2);
            camino.insert(make_pair(pos2,pos));
          } else {
            vis[pos2.i][pos2.j] = true;
            Q.push(pos2);
            camino.insert(make_pair(pos2,pos));
          }
        }
      }
    }
    if (posibles.size() > 0) return res_bfs(posibles[random(0, posibles.size() - 1)], act, camino);
    else if (posibles.size() == 0 ) return act;
  }


  Pos bfs_farmers(const Pos& act, queue <Pos>& Q, const graph& farm){
    bool found = false; // camino
    map <Pos, Pos> camino; //llave hijo, referencia padre
    vector<Pos> posibles;
    graph vis(rows(), vector <bool> (cols(), false));
    Pos padre;
    padre.i = -1;
    padre.j = -1;
    camino.insert(make_pair(act,padre));
    Q.push(act);
    vis[act.i][act.j] = true;
    while (not found and not Q.empty() ) {
      Pos pos = Q.front();
      Q.pop();
      for ( int i = 0; i < 4; ++i) {
        Pos pos2 = pos + Dir(i*2);
        if (pos_ok(pos2) and farm[pos2.i][pos2.j] and !vis[pos2.i][pos2.j]) {
          if (cell(pos2).owner == -1) {
            found = true;
            posibles.push_back(pos2);
            camino.insert(make_pair(pos2,pos));
          } else if (cell(pos2).owner >= 0) {
            vis[pos2.i][pos2.j] = true;
            Q.push(pos2);
            camino.insert(make_pair(pos2,pos));
          }
        }
      }
    }
    if (posibles.size() > 0) return res_bfs(posibles[random(0, posibles.size() - 1)], act, camino);
    else if (posibles.size() == 0 ) return act;
  }

  virtual void play () {
    //falso MALO
    graph farm(rows(), vector <bool> (cols(), true));
    graph kni(rows(), vector <bool> (cols(), true));
    graph witch(rows(), vector <bool> (cols(), true));
    inic(farm);
    inic2(kni);
    inic3(witch);
    VE f = farmers(0);
    for (int id : f) {
      Pos act = unit(id).pos;
      queue<Pos> Q; //cola para bfs
      Pos fin = bfs_farmers(act, Q, farm);
      command(id,dirfast(act, fin));
    }



    VE k = knights(0);
    for (int id : k) {
      Pos act = unit(id).pos;
      queue<Pos> Q; //cola para bfs
      Pos fin = bfs_knight(act, Q, kni);
      command(id,dirfast(act, fin));
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

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

  struct D {
    Pos p;
    Dir dir;
  };
  //INICIALIZAMOS MATRIZES

  void secureWithces(graph& g, const Pos& p) {
    for (int a = 0; a < 4; ++a) {
      Pos sec = p;
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
        if (cell(i,j).type == Wall) farm[i][j] = false;
        if (cell(i,j).id != -1 and unit(cell(i,j).id).type == Farmer) farm[i][j] = false;
        if (cell(i,j).id != -1 and unit(cell(i,j).id).type == Witch) {
          farm[i][j] = false;
          Pos p;
          p.i = i;
          p.j = j;
          secureWithces(farm, p);
        }
        if (cell(i,j).id != -1 and unit(cell(i,j).id).type == Knight and unit(cell(i,j).id).player != 0) {
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
        if (cell(i,j).type == Wall) kni[i][j] = false;
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
        if (cell(i,j).type == Wall) witch[i][j] = false;
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

  //BFS

  Dir bfs_witch(const Pos& act, queue <D>& Q, const graph& witch){
    bool found = false;
    graph vis(rows(), vector <bool> (cols(), false));
    D pres;
    pres.p = act;
    pres.dir = None;
    Q.push(pres);
    vis[act.i][act.j] = true;
    while (not found and not Q.empty() ) {
      D pos = Q.front();
      Q.pop();
      for ( int i = 0; i < 4; ++i) {
        D pos2;
        pos2.p = pos.p + Dir(i*2);
        pos2.dir = pos.dir;
        if (pos_ok(pos2.p) and witch[pos2.p.i][pos2.p.j] and !vis[pos2.p.i][pos2.p.j]) {
          if (pos2.dir == None) pos2.dir = Dir(i*2);
          if (cell(pos2.p).id != -1 and unit(cell(pos2.p).id).type == Knight and unit(cell(pos2.p).id).player != 0){
            found = true;
            return pos2.dir;
          } else {
            vis[pos2.p.i][pos2.p.j] = true;
            Q.push(pos2);
          }
        }
      }
    }
    if (!found) return None;
  }


  Dir bfs_knight(const Pos& act, queue <D>& Q, const graph& kni){
    bool found = false;
    graph vis(rows(), vector <bool> (cols(), false));
    D pres;
    pres.p = act;
    pres.dir = None;
    Q.push(pres);
    vis[act.i][act.j] = true;
    while (not found and not Q.empty() ) {
      D pos = Q.front();
      Q.pop();
      for ( int i = 0; i < 8; ++i) {
        D pos2;
        pos2.p = pos.p + Dir(i);
        pos2.dir = pos.dir;
        if (pos_ok(pos2.p) and kni[pos2.p.i][pos2.p.j] and !vis[pos2.p.i][pos2.p.j]) {
          if (pos2.dir == None) pos2.dir = Dir(i);
          if (cell(pos2.p).id != -1 and unit(cell(pos2.p).id).type != Witch and unit(cell(pos2.p).id).player != 0) {
            found = true;
            return pos2.dir;
          } else {
            vis[pos2.p.i][pos2.p.j] = true;
            Q.push(pos2);
          }
        }
      }
    }
    if (!found) return None;
  }

  Dir bfs_farmers(const Pos& act, queue <D>& Q, const graph& farm){
    bool found = false;
    graph vis(rows(), vector <bool> (cols(), false));
    D pres;
    pres.p = act;
    pres.dir = None;
    Q.push(pres);
    vis[act.i][act.j] = true;
    while (not found and not Q.empty() ) {
      D pos = Q.front();
      Q.pop();
      for ( int i = 0; i < 4; ++i) {
        D pos2;
        pos2.p = pos.p + Dir(i*2);
        pos2.dir = pos.dir;
        if (pos_ok(pos2.p) and farm[pos2.p.i][pos2.p.j] and !vis[pos2.p.i][pos2.p.j]) {
          if (pos2.dir == None) pos2.dir = Dir(i*2);
          if (cell(pos2.p).owner != 0) {
            found = true;
            return pos2.dir;
          } else if (cell(pos2.p).owner == 0) {
            vis[pos2.p.i][pos2.p.j] = true;
            Q.push(pos2);
          }
        }
      }
    }
    if (!found) return None;
  }

  virtual void play () {
    graph farm(rows(), vector <bool> (cols(), true));
    graph kni(rows(), vector <bool> (cols(), true));
    graph witch(rows(), vector <bool> (cols(), true));
    inic(farm);
    inic2(kni);
    inic3(witch);
    VE f = farmers(0);
    for (int id : f) {
      Pos act = unit(id).pos;
      queue <D> Q;
      command(id, bfs_farmers(act, Q, farm));
    }

    VE k = knights(0);
    for (int id : k) {
      Pos act = unit(id).pos;
      queue <D> Q;
      command(id, bfs_knight(act, Q, kni));
    }

    VE w = witches(0);
    for (int id : w) {
      Pos act = unit(id).pos;
      queue <D> Q;
      command(id, bfs_witch(act, Q, witch));
    }
  }
};

/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);

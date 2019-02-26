#ifndef Commande_h
#define Commande_h

#include <Arduino.h>

#include "MeubleLumineux.h"

class Commande
{
  public:
    Commande(MeubleLumineux *meubleTV, Commande *next) {
      _next = next;
      _meubleTV = meubleTV;
    }
    virtual bool isCommande(String cmd);
    virtual int executeCommande(String cmd, bool isLoop);
    int analyserCommande(String cmd, bool isLoop) {
      if (isCommande(cmd)) {
        return executeCommande(cmd, isLoop);
      } else if (_next != NULL) {
        return _next->analyserCommande(cmd, isLoop);
      } else {
        return 0;
      }
    }
  protected:
    MeubleLumineux *_meubleTV;
  private:
    Commande *_next;
};


class Off : public Commande {
  public:
    bool isCommande(String cmd) {
      return cmd == "OFF";
    }
  
    int executeCommande(String cmd, bool isLoop) {
      if (isLoop == false){
        _meubleTV->clear();
        _meubleTV->show();
      }
      return 1;
    }
};

class S : public Commande {
  public:
    bool isCommande(String cmd) {
      return cmd != "OFF";
    }

    int executeCommande(String cmd, bool isLoop) {
       if (cmd == "S1") {
          _meubleTV->rainbow();
       } else if (cmd == "S2" && isLoop == false) {
          _meubleTV->setColor(1,CRGB::White);
          _meubleTV->setColor(2,CRGB::White);
          _meubleTV->setColor(3,CRGB::White);
          _meubleTV->setColor(4,CRGB::White);
          _meubleTV->show();
       } else if (cmd == "S3" && isLoop == false) {
          _meubleTV->setColor(1,CRGB::Blue);
          _meubleTV->setColor(2,CRGB::Blue);
          _meubleTV->setColor(3,CRGB::Blue);
          _meubleTV->setColor(4,CRGB::Blue);
          _meubleTV->show();
       } else if (cmd == "S4" && isLoop == false) {
          _meubleTV->setColor(1,CRGB::Red);
          _meubleTV->setColor(2,CRGB::Red);
          _meubleTV->setColor(3,CRGB::Red);
          _meubleTV->setColor(4,CRGB::Red);
          _meubleTV->show();
       } else if (cmd == "S5" && isLoop == false) {
          _meubleTV->setColor(1,CRGB::Green);
          _meubleTV->setColor(2,CRGB::Green);
          _meubleTV->setColor(3,CRGB::Green);
          _meubleTV->setColor(4,CRGB::Green);
          _meubleTV->show();
      } else {
        return -1;
      }
      return 1;
    }
};

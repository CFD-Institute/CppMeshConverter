/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NodeIdentMsh.h
 * Author: HP
 *
 * Created on June 12, 2021, 1:02 PM
 */
#include "NodeIdent.h"

class NodeIdentMsh : public NodeIdent {

    public:
        NodeIdentMsh() {};
        NodeIdentMsh(unsigned, unsigned, unsigned, unsigned, unsigned);
        unsigned getIdent();
        unsigned getElemTyp();
        unsigned getNbTags();
        unsigned getTag1();
        unsigned getTag2();
        NodeIdentMsh* setIdent(unsigned);
        NodeIdentMsh* setElemTyp(unsigned);
        NodeIdentMsh* setNbTags(unsigned);
        NodeIdentMsh* setTag1(unsigned);
        NodeIdentMsh* setTag2(unsigned);
        
    private:
        unsigned ident;
        unsigned elemTyp;
        unsigned nbTags;
        unsigned tag1;
        unsigned tag2;
};


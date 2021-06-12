
#include "NodeIdentMsh.h"

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
NodeIdentMsh::NodeIdentMsh() {
    
}

NodeIdentMsh::NodeIdentMsh(unsigned ident, unsigned elemTyp, unsigned nbTags, unsigned tag1, unsigned tag2) {
    this->setIdent(ident)
            .setElemTyp(elemTyp)
            .setNbTags(nbTags)
            .setTag1(tag1)
            .setTag2(tag2);
}

unsigned NodeIdentMsh::getIdent() {
    return this->ident;
}

NodeIdentMsh NodeIdentMsh::setIdent(unsigned ident) {
    this->ident = ident;
    return this;
}

unsigned NodeIdentMsh::getElemTyp() {
    return this->elemTyp;
}

NodeIdentMsh NodeIdentMsh::setElemTyp(unsigned elemTyp) {
    this->elemTyp = elemTyp;
    return this;
}

unsigned NodeIdentMsh::getNbTags() {
    return this->nbTags;
}

NodeIdentMsh NodeIdentMsh::setNbTags(unsigned nbTags) {
    this->nbTags = nbTags;
    return this;
}

unsigned NodeIdentMsh::getTag1() {
    return this->tag1;
}

NodeIdentMsh NodeIdentMsh::setTag1(unsigned tag1) {
    this->tag1 = tag1;
    return this;
}

unsigned NodeIdentMsh::getTag2() {
    return this->tag2;
}

NodeIdentMsh NodeIdentMsh::setTag2(unsigned tag2) {
    this->tag2 = tag2;
    return this;
}
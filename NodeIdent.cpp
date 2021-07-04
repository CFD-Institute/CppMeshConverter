
#include "NodeIdent.h"

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

std::vector<unsigned> & NodeIdent::getIdNode() {
    return this->idNode;
}

NodeIdent* NodeIdent::setIdNode(std::vector<unsigned> idNodes) {
    this->idNode = idNodes;
    return this;
}
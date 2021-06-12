/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NodeIdent.h
 * Author: HP
 *
 * Created on June 12, 2021, 12:14 PM
 */

#pragma once

#include <vector>

class NodeIdent {
    
public:
    NodeIdent() {};
    std::vector<unsigned> getIdNode();
    NodeIdent* setIdNode(std::vector<unsigned>);
    
private:
    std::vector<unsigned> idNode;
};



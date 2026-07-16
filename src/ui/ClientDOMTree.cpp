module;

#include "PCH.hpp"

module UI.ClientDOMTree;

import UI.ClientConnection;



tatzel::ClientDOMTree::ClientDOMTree() :
	root{ "main", "root", nullptr }
{}

tatzel::ClientDOMTree::~ClientDOMTree()
{}

module;

#include "PCH.hpp"

module UI.ClientDOMTree;

import UI.ClientConnection;



ui::ClientDOMTree::ClientDOMTree() :
	root{ "main", "root", nullptr }
{}

ui::ClientDOMTree::~ClientDOMTree()
{}

module;

#include "PCH.hpp"

module UI.ClientDOMTree;

import UI.ClientConnection;



tatzel::ClientDOMTree::ClientDOMTree() :
	root{
		"",
		nullptr,
		std::span<const dom::ElementPart>{ {
			dom::ElementPart{
				"root",
				"main",
				std::span<const std::string_view>{ { "container" } } }
			} }
		}
{}

tatzel::ClientDOMTree::~ClientDOMTree()
{}

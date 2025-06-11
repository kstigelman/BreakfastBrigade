#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using std::string;

class Item {
	private:
		string m_name;
	public:
		Item () {
			m_name = "null";
		}
		Item (string name) {
			m_name = name;
		}
		string print ();
		string getName () {
			return m_name;
		}
};
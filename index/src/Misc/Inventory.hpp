#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Item.hpp"

using std::string;
using std::vector;

class Inventory {
	private:
		int slots;
		vector<Item> items;
		int nextIndex = 0;
	public:
		Inventory ();
		Inventory (int SLOTS = 3) {
			items = vector<Item> (SLOTS);
		}


		Item& operator[] (int index)
		{
			return items[index];
		}

		friend std::ostream& operator<< (std::ostream& os, const Inventory& e) {
			
			//os <<  "\n";
			return os;
		}

		std::string getItemsList () {
			std::string accum = "";
			for (size_t i = 0; i < items.size (); ++i) {
				accum += "\t[";
				accum += std::to_string (i);
				accum += "] - ";
				accum += items[i].getName ();
				accum += "\n";
			}
			return accum;

		}
		size_t getSize () {
			return items.size ();
		}
		
		std::string print () {
			/*std::string message = ("Inventory (" + std::to_string (items.size ())) + " items):\n";
			message += getItemsList ();
			return message;*/


			printf ("Inventory (%d items):\n", items.size ());
			for (size_t i = 0; i < items.size (); ++i)
				printf ("\t[%d] - %s\n", (unsigned) i, items[i].getName().c_str ());
			return "";
		}

		bool add (Item i) {
			if (nextIndex >= items.size ())
				return false;
			items[nextIndex] = i;
			++nextIndex;
		}

		Item swap (int index, Item i) {
			if (index >= items.size ())
				return i;
			
			Item temp = items[index];
			items[index] = i;
			return temp;
		}
		bool swap (int index1, int index2) {
			if (index1 >= nextIndex || index2 >= nextIndex)
				return false;

			Item temp = items[index1];
			items[index1] = items[index2];
			items[index2] = temp;
			return true;
		}
		Item drop (int index) {
			if (index >= nextIndex && nextIndex > 0)
				return Item ();
			--nextIndex;
			return items[nextIndex + 1];
		}
		Item drop () {
			return drop (nextIndex - 1);
		}
		

};
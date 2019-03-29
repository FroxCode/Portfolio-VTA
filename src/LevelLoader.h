#ifndef _levelLoader_h_
#define _levelLoader_h_

#include<iostream>
#include<fstream>
#include<string>
#include<limits>
#include"Rooms.h"

class LevelLoader {
	private:
		static const int WIDTH = 20;
		static const int HEIGHT = 11;
	
		
	public:
		////////////////////////////////////////////////////////////
		/// Default constructor
		///
		////////////////////////////////////////////////////////////
		LevelLoader();

		////////////////////////////////////////////////////////////
		/// Default destructor
		///
		////////////////////////////////////////////////////////////
		~LevelLoader();
		int level[HEIGHT][WIDTH];
		void load(std::string textFile);
		void loadRoom(Rooms *newRoom);
};

#endif;

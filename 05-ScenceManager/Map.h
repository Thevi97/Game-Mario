#pragma once
#define MAX_MAP_X 100
#define MAX_MAP_Y 12
class Map
{
public:
	int start_x_;
	int start_y_;

	int max_x_;
	int max_y_;
	char* file_name_;

	int tile[MAX_MAP_Y][MAX_MAP_X];

};
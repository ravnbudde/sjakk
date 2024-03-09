#pragma once

namespace TDT4102 {
	struct Point {
		int x = 0;
		int y = 0;
	};	

	inline bool operator==(const TDT4102::Point& lhs, const TDT4102::Point& rhs){
    	return lhs.x == rhs.x and lhs.y == rhs.y;
	}
	inline bool operator!=(const TDT4102::Point& lhs, const TDT4102::Point& rhs){
    	return lhs.x != rhs.x and lhs.y != rhs.y;
	}
	inline bool operator<(const TDT4102::Point& lhs, const TDT4102::Point& rhs){
		if(lhs.y == rhs.y){
			return lhs.x < rhs.x;
		}
		return lhs.y < rhs.y; // or (lhs.y == rhs.y and lhs.x < rhs.x);
	}
	inline bool operator>(const TDT4102::Point& lhs, const TDT4102::Point& rhs){
		if(lhs.y == rhs.y){
			return lhs.x>rhs.x;
		}
		return lhs.y > rhs.y;
	}
}

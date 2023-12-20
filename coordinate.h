class Coordinate{

	private:
		int x;
		int y;

	public:
		Coordinate();
		Coordinate(int x, int y);
		int getX();
		int getY();
		bool operator<(const Coordinate& other) const;
		bool operator==(const Coordinate& other) const;
};
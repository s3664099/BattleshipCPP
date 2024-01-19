Coordinate getNextShot(int selected, Coordinate hit);
set<int> checkShipShots(set<Coordinate> potentialShots, Coordinate shot, Board* defender);

int fire(Board* defender, Board* attacker) {

	int result = 0;
	int selectShot;

	//Sets the variables used in the algorithm including information from the previous turn
	Coordinate originalHit(0,0);
	Coordinate shot(0,0);

	std::vector<std::vector<std::string>>* grid = defender->getGrid();
	std::vector<std::vector<std::string>>* spotsHit = defender->getGrid();
	int hitShip = defender->getHitShip();
	int hitResult = 0;
	std::set<Coordinate> potentialShots = attacker->getPotentialShots();

	//Has the ship already been hit
	if (hitShip == 1) {

		//Gets the previous hit and sets it as the original
		Coordinate hit = defender->getHit();
		originalHit = hit;
		std::set<int> shipShots = defender->getShipShots();

		//Selects a shot and removes it from the list
		int shotSelected = rand()%shipShots.size()-1;
		std::vector<int> shstList(shipShots.begin(),shipShots.end());
		selectShot = shstList.at(shotSelected);
		shstList.erase(shstList.begin()+selectShot);
		shipShots.clear();

		for (int remainShots:shstList) {
			shipShots.insert(remainShots);
		}

		defender->setShipShots(shipShots);
		defender->setMovement(selectShot);
		shot = getNextShot(selectShot,hit);

		//checks to see if there is anything left in potential shots
		if(potentialShots.size()>0) {
			potentialShots.erase(shot);
		}

	//The shipt has been hit more than once
	} else if (hitShip ==2) {

		//Retrieves the next shot
		set<int> shipShots = defender->getShipShots();
		Coordinate hit = defender->getHit();
		selectShot = defender->getMovement();
		shot = getNextShot(selectShot,hit);

		//Checks to see if there is anything left in potential shots
		if (potentialShots.size()>0) {
			potentialShots.erase(shot);
		}
	} else {

		//Otherwise selects a random shot from the list of potential shots
		int shotSelected = rand()%potentialShots.size()-1;

		vector<Coordinate> ptshList(potentialShots.begin(),potentialShots.end());

		if (potentialShots.size()>0) {
			potentialShots.erase(shot);
		}
	}

	attacker->setPotentialShots(potentialShots);

	string hitPosition = "0";

	std::cout<<"Shot fired at: "<<shot.getX()<<","<<shot.getY()<<std::endl;

	//Has this empty spot already been hit
	if ((*grid)[shot.getX()][shot.getY()] == "0") {
		(*grid)[shot.getX()][shot.getY()] == ".";
	}

	if ((*grid)[shot.getX()][shot.getY()] != ".") {
		
		//Marks it as a ship
		hitPosition = "X";

		//Sets the flag that a ship has been hit and checks if it has been sunk
		defender->setHit(shot);
		hitResult = defender->checkWhichShip(shot,attacker->getName());

		std::cout<<"Hit result "<<hitResult<<std::endl;

		if (hitShip == 0) {
			defender->setHitShip(1);
			set<int> shipShots = checkShipShots(potentialShots,shot,defender);
			defender->setShipShots(shipShots);
		}

		//If it has, sets it that it has been hit more than once
		if (hitShip == 1) {
			defender->setHitShip(2);
			defender->setOriginalHit(originalHit);

			set<int> shipShots;

			//Sets the next potential shot in case the shot misses
			if(selectShot == 0) {
				shipShots.insert(1);
			} else if (selectShot == 1) {
				shipShots.insert(0);
			} else if (selectShot == 2) {
				shipShots.insert(3);
			} else {
				shipShots.insert(2);
			}

			//Checks if the next shot will be off the board
			if ((selectShot == 0) && (shot.getX()+1>defender->getSize()-1)) {
				defender->setMovement(1);
			} else if ((selectShot == 1) && (shot.getX()+1<0)) {
				defender->setMovement(0);
			} else if ((selectShot == 2) && (shot.getY()+1>defender->getSize()-1)) {
				defender->setMovement(3);
			} else if ((selectShot == 4) && (shot.getY()+1<0)) {
				defender->setMovement(2);
			}

			defender->setShipShots(shipShots);
		}

	//If it was a miss
	} else {

		//If the previous shots hit the ship, then goes back to the original spot
		//and sets it in the opposite direction
		if (hitShip == 2) {
			defender->setHitShip(1);
			defender->setHit(defender->getOriginalHit());
		}
	}

	(*grid)[shot.getX()][shot.getY()] == hitPosition;
	(*spotsHit)[shot.getX()][shot.getY()] == hitPosition;

	if (hitResult == 2) {
		defender->setHitShip(0);
	}

	return hitResult;
}

Coordinate getNextShot(int selected, Coordinate hit) {

	Coordinate shot;

	if (selected == 0) {
		shot = Coordinate(hit.getX()+1,hit.getY());
	} else if (selected == 1) {
		shot = Coordinate(hit.getX()-1,hit.getY());
	} else if (selected == 2) {
		shot = Coordinate(hit.getX(),hit.getY()+1);
	} else {
		shot = Coordinate(hit.getX(),hit.getY()-1);
	}

	return shot;
}

//Checks to see if the potential shots once the ship is hit, haven't already been taken. If they
//haven't it adds the potential shot to the list
set<int> checkShipShots(set<Coordinate> potentialShots, Coordinate shot, Board* defender) {

	set<int> shipShots;

	for (Coordinate ptshCoords:potentialShots) {

		if ((ptshCoords.getX() == shot.getX()+1) && (ptshCoords.getY() == shot.getY())) {
			if (shot.getX()+1<defender->getSize()) {
				shipShots.insert(0);
			}
		} else if ((ptshCoords.getX() == shot.getX()+1) && (ptshCoords.getY() == shot.getY())) {
			if (shot.getX()-1>-1) {
				shipShots.insert(1);
			}
		} else if ((ptshCoords.getX() == shot.getX()) && (ptshCoords.getY() == shot.getY()+1)) {
			if (shot.getY()+1<defender->getSize()) {
				shipShots.insert(2);
			}
		} else if ((ptshCoords.getX() == shot.getX()) && (ptshCoords.getY() == shot.getY()-1)) {
			if (shot.getY()>-1) {
				shipShots.insert(3);
			}
		}
	}
	return shipShots;

}
		/*

	//Method that takes a set and a coordinate and removes it from the set
	private Set<Coordinate> removeShot(Set<Coordinate> potentialShots,Coordinate shot) {
		
		//Converts the set into a list
		List<Coordinate> ptshList = new ArrayList<>(potentialShots);
		
		//Locates the coordinate in the list
		for (int x=0;x<ptshList.size();x++) {
			if ((ptshList.get(x).getX() == shot.getX()) && (ptshList.get(x).getY() == shot.getY())) {

				//Removes it from the list
				ptshList.remove(x);
			}
		}
		
		//Clears the set and converts the list back to a new set
		potentialShots.clear();
		potentialShots = new HashSet<Coordinate>(ptshList);
		
		return potentialShots;
	}	
	*/

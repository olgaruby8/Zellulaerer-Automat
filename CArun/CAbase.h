#pragma once
#include <stdlib.h>
#include <ctime>

class CAbase
{
public:
	CAbase(int nx, int ny)
		: Ny(ny)
		, Nx(nx)
		
	{
		ResetWorldSize(Nx, Ny, 1);
	}

	void ResetWorldSize(int nx, int ny, bool del = 0);

	int GetNy() { return Ny; }
	int GetNx() { return Nx; }
	void SetAlive(int x, int y, int i);
	void SetAliveEvo(int x, int y, int i);
	int IsAlive(int x, int y) { return world[y * (Nx + 2) + x]; }
	int CellEvolutionLife(int x, int y);
	void WorldEvolutionLife();


	// ---
	~CAbase()
	{
	}
private:
	int Ny;
	int Nx;
	int* world;
	int* worldNew;	
};

inline void CAbase::SetAlive(int x, int y, int i)
{
	world[y * (Nx + 2) + x] = i;
}

inline void CAbase::SetAliveEvo(int x, int y, int i)
{
	worldNew[y * (Nx + 2) + x] = i;
}

inline int CAbase::CellEvolutionLife(int x, int y) // Die nächste Generation wird durch die Befolgung einfacher Regeln ergeben
{
	int n_sum = 0;
	int x1(0), y1(0);
	for (int ix = -1; ix <= 1; ix++) {
		for (int iy = -1; iy <= 1; iy++) {
			if (ix == 0 && iy == 0) continue;
			x1 = x + ix;
			y1 = y + iy;
			if (x1 < 1) x1 = Nx;
			if (x1 > Nx) x1 = 1;
			if (y1 < 1) y1 = Ny;
			if (y1 > Ny) y1 = 1;
			if (IsAlive(x1, y1) == 1) n_sum++;
		}
	}
	if (IsAlive(x, y) == 1) {
		if (n_sum == 2 || n_sum == 3) SetAliveEvo(x, y, 1);
		else SetAliveEvo(x, y, 0);
	}
	else {
		if (n_sum == 3) SetAliveEvo(x, y, 1);
	}
	return 0;
}


// Starten die Evolution für jede Zelle des Universum Arrays
// Nach der vollständigen Evolution wird der neue Zustand des Universums in den aktuellen Zustand kopiert
inline void CAbase::WorldEvolutionLife()
{
	for (int ix = 1; ix <= Nx; ix++) {			// Universum-Evolution für jede Zelle
		for (int iy = 1; iy <= Ny; iy++) {
			CellEvolutionLife(ix, iy);
		}
	}
	
	for (int ix = 1; ix <= Nx; ix++) {			// Kopieren den neuen Status in das aktuelle Universum
		for (int iy = 1; iy <= Ny; iy++) {
						world[iy * (Nx + 2) + ix] = worldNew[iy * (Nx + 2) + ix];
		}
	}							
}



inline void CAbase::ResetWorldSize(int nx, int ny, bool del)
{
	Nx = nx;
	Ny = ny;
	if (!del) {
		delete[] world;
		delete[] worldNew;
	}
	world = new int[(Ny + 2) * (Nx + 2) + 1];
	worldNew = new int[(Ny + 2) * (Nx + 2) + 1];

	for (int i = 0; i <= (Ny + 2) * (Nx + 2); i++) {
		if ((i < (Nx + 2)) || (i >= (Ny + 1) * (Nx + 2)) || (i % (Nx + 2) == 0) || (i % (Nx + 2) == (Nx + 1))) {
			world[i] = -1;
			worldNew[i] = -1;
		}
		else {
			world[i] = 0;
			worldNew[i] = 0;
		}
	}
}

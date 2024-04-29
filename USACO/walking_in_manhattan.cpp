#include <algorithm>
#include <iostream>
 
const int MAXN = 200005;
const int MAXL = 18;
const int INFTY = 2e9+7;
 
int N, Q;
int H, V;
int horiz[MAXN];
int vert[MAXN];
int hn[MAXN][MAXL];
int vn[MAXN][MAXL];
 
void input () {
	std::cin >> N >> Q;
	while (N--) {
		char c; int x;
		std::cin >> c >> x;
		if (c == 'H') {
			horiz[H] = x;
			H++;
		}
		else {
			vert[V] = x;
			V++;
		}
	}
}
 
void proc () {
	std::sort(horiz, horiz+H);
	std::sort(vert, vert+V);
	horiz[H] = INFTY;
	vert[V] = INFTY;
	for (int i = 0; i < MAXL; i++) {
		hn[H][i] = H;
		vn[V][i] = V;
	}
 
	for (int i = H-1; i >= 0; i--) {
		if (horiz[i]%2 != horiz[i+1]%2) {
			hn[i][0] = i+1;
		}
		else {
			hn[i][0] = hn[i+1][0];
		}
		for (int t = 1; t < MAXL; t++) {
			hn[i][t] = hn[hn[i][t-1]][t-1];
		}
	}
 
	for (int i = V-1; i >= 0; i--) {
		if (vert[i]%2 != vert[i+1]%2) {
			vn[i][0] = i+1;
		}
		else {
			vn[i][0] = vn[i+1][0];
		}
		for (int t = 1; t < MAXL; t++) {
			vn[i][t] = vn[vn[i][t-1]][t-1];
		}
	}	
}
 
std::pair<int, int> query (int x, int y, int d) {
	int hlo = 0, hhi = H;
	while (hlo < hhi) {
		int hmi = (hlo + hhi) / 2;
		if (horiz[hmi] >= y) {
			hhi = hmi;
		}
		else {
			hlo = hmi + 1;
		}
	}
	int vlo = 0, vhi = V;
	while (vlo < vhi) {
		int vmi = (vlo + vhi) / 2;
		if (vert[vmi] >= x) {
			vhi = vmi;
		}
		else {
			vlo = vmi + 1;
		}
	}
	int t = 0;
	if (y < horiz[hlo]) {
		if (d + y <= horiz[hlo]) {
			return {x, d+y};
		}
		d -= (horiz[hlo] - y);
		t += horiz[hlo] - y;
	}
	if (x < vert[vlo]) {
		if (d + x <= vert[vlo]) {
			return {d+x, y};
		}
		d -= (vert[vlo] - x);
		t += vert[vlo] - x;
	}
	for (int k = MAXL-1; k >= 0; k--) {
		int h = hn[hlo][k], v = vn[vlo][k];
		if (horiz[h] - horiz[hlo] > d) {
			continue;
		}
		if (vert[v] - vert[vlo] > d) {
			continue;
		}
		if ((vert[v] - vert[vlo]) + (horiz[h] - horiz[hlo]) > d) {
			continue;
		}
		d -= (vert[v] - vert[vlo]) + (horiz[h] - horiz[hlo]);
		t += (vert[v] - vert[vlo]) + (horiz[h] - horiz[hlo]);
		hlo = h;
		vlo = v;
	}
	if (t%2) {
		int v = vn[vlo][0];
		if (vert[v] - vert[vlo] >= d) {
			return {vert[vlo] + d, horiz[hlo]};
		}
		d -= (vert[v] - vert[vlo]);
		return {vert[v], horiz[hlo]+d};
	}
	int h = hn[hlo][0];
	if (horiz[h] - horiz[hlo] >= d) {
		return {vert[vlo], horiz[hlo]+d};
	}
	d -= (horiz[h] - horiz[hlo]);
	return {vert[vlo]+d, horiz[h]};
}
 
int main () {
	input();
	proc();
	while (Q--) {
		int x, y, d; std::cin >> x >> y >> d;
		std::pair<int,int> pi = query(x, y, d);
		std::cout << pi.first << " " << pi.second << "\n";
	}
}
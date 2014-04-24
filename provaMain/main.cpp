#include <iostream>
#include "face.h"


using namespace std;

int main() {

	if ( !init() )
		cout << "errore init" << endl;
    int x=0, y=0, area=0;    
    while (true) {
        int x=0, y=0, area=0; 
	    getFaceCoord(&x,&y,&area);
	    cout << x << ", " << y << " , " << area << endl;
    }	
    finalize();

	

	int z;
	cin >> z;

}

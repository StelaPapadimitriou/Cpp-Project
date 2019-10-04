#include <iostream>
#include <string>
#include "Image.h"
#include "BaseFilter.h"
#include "LocalFilters.h"
#include "NeighborhoodFilters.h"

using namespace std;
using namespace imaging;

int main(int argc, char * argv[]) {
	if (argc > 1) {
		Image* img = new imaging::Image();
		if ((*img) << argv[argc - 1] == false) {
			cerr << "No image data";
			return 0;
		}

		BaseFilter* fl=nullptr;
		for (int i = 0; i < argc - 2; i++) {
			if (strcmp(argv[i], "-f") == 0) {

				if (strcmp(argv[i + 1], "blur") == 0) {
					fl = new Blur();
				}
				else if (strcmp(argv[i + 1], "gray") == 0) {
					fl = new Gray();
				}
				else if (strcmp(argv[i + 1], "median") == 0) {
					fl = new Median();
				}
				else if (strcmp(argv[i + 1], "diff") == 0) {
					fl = new Diff();
				}
				else if (strcmp(argv[i + 1], "color") == 0) {
					fl = new Color();
					Vec3<float> c;
					//string to float
					c.r = atof(argv[i + 2]);
					c.g = atof(argv[i + 3]);
					c.b = atof(argv[i + 4]);
					Color *p = dynamic_cast<Color *>(fl);
					p->setColor(c);
				}
				else {
					cerr << "Wrong filter";
					continue;
				}

				fl->filter(*img);
				delete fl;
			}
		}

		string newname = argv[argc - 1];
		//Erase "ppm" and add "filtered.ppm"
		newname.erase(newname.end() - 3, newname.end());
		newname += "filtered.ppm";
		(*img) >> (newname);
	}
	else {
		cerr << "Error! Invalid input" << endl;
		return 0;
	}

	return 0;
}
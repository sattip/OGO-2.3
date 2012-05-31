#ifndef _LOADER3DS_H
#define _LOADER3DS_H

//--------------------------------------------

#include "core.h"
#include "base.h"

#include <3ds/lib3ds.h>

//--------------------------------------------

namespace Loader {

using namespace Base;
using namespace Core;

//--------------------------------------------

class ModelObject : public Object {
	Lib3dsFile * file;
	void load(const char * path);
	void displaylist(Lib3dsMesh * mesh);
	void render(Lib3dsNode * n);
public:
	ModelObject(Point<double> P = Point<double>(), Quaternion<double> R = Quaternion<double>());
	virtual ~ModelObject() {};
	virtual void render();
};

//--------------------------------------------

} // namespace Loader

#endif _LOADER3DS_H
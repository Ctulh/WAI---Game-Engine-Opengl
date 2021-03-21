
#include <vector>
#include "Renderer.h"
#include "returned.h"

class Object;

class ObjectArray
{
public:
	std::vector<Object*> Array;
	std::size_t size;

	ObjectArray();
	void Add(Object *obj);
	void Add(returned& RreturnedStruct, std::string& path);
	void Draw(Renderer& renderer);
};
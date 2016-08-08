#include "Obj.h"

//从某个列表，以ID为识别，删除子项
void Obj::RemoveNode(std::vector<Obj*>* src, std::vector<int> node) {
	int deleteLength = node.size();
	bool bHas = false;//当前孩子节点是否需要删除
	int srcLength = (*src).size();

	for (int i = 0; i < srcLength; ) {
		bHas = false;
		for (int j = 0; j < deleteLength; j++) {
			if (node[j] == (*src)[i]->getID()) {//从要删列表中清除孩子节点
				bHas = true;
				node.erase(node.begin() + j);
				deleteLength--;
				break;
			}
		}
		if (bHas) {
			this->BeforeRemoveNode();
			(*src).erase((*src).begin() + i);
			srcLength--;
		}
		else {
			i++;
		}
	}
}
void Obj::BeforeRemoveNode() {
}

void Obj::die() {}

void Obj::run() {

}
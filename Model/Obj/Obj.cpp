#include "Obj.h"

//��ĳ���б���IDΪʶ��ɾ������
void Obj::RemoveNode(std::vector<Obj*>* src, std::vector<int> node) {
	int deleteLength = node.size();
	bool bHas = false;//��ǰ���ӽڵ��Ƿ���Ҫɾ��
	int srcLength = (*src).size();

	for (int i = 0; i < srcLength; ) {
		bHas = false;
		for (int j = 0; j < deleteLength; j++) {
			if (node[j] == (*src)[i]->getID()) {//��Ҫɾ�б���������ӽڵ�
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
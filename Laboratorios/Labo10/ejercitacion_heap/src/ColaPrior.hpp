
template<class T>
ColaPrior<T>::ColaPrior(): heap({}) {} // constructor vacio

template<class T>
int ColaPrior<T>::tam() const {
	return this->heap.size();
}

template<class T>
void ColaPrior<T>::encolar(const T& elem) {
	this->heap.push_back(elem);
    heapify(this->heap);
}

template<class T>
const T& ColaPrior<T>::proximo() const {
	return this->heap[0];
}

template<class T>
void ColaPrior<T>::desencolar() {
    this->heap.erase(this->heap.begin());
    heapify(this->heap);
}

template<class T>
ColaPrior<T>::ColaPrior(const vector<T>& elems) {
	this->heap = elems;
    heapify(this->heap);
}

template<class T>
void ColaPrior<T>::heapify(vector<T> &v) {
    int iPapu = (v.size() - 2) / 2;
    for (; iPapu >= 0; iPapu--){
        int iHijo1 = (2 * iPapu) + 1;
        int iHijo2 = (2 * iPapu) + 2;

        if (v[iPapu] < v[iHijo1])
            swap(v[iPapu], v[iHijo1]);

        if (iHijo2 < v.size()) {
            if (v[iPapu] < v[iHijo2])
                swap(v[iPapu], v[iHijo2]);
        }
    }
}
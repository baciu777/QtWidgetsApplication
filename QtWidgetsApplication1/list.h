#pragma once
template <typename ElementT>
class IteratorVectorT;

template <typename ElementT>
class VectDinNewDeleteT
{
private:
	int lg; //numar de elemente
	int cap; //capacitate
	ElementT* elems; //elemente

	void ensureCapacity();

public:

	/*
	Constructor default
	Alocam loc pentru 5 elemente
	*/
	VectDinNewDeleteT();

	/*
	Constructor de copiere
	*/
	VectDinNewDeleteT(const VectDinNewDeleteT& ot); //rule of 3

	/*
	Eliberam memoria
	*/
	~VectDinNewDeleteT(); //rule of 3

	/*
	Operator assignment
	elibereaza ce era in obicetul curent (this)
	aloca spatiu pentru elemente
	copiaza elementele din ot in this
	*/
	VectDinNewDeleteT& operator=(const VectDinNewDeleteT& ot); //rule of 3


	/*
	Move constructor
	Apelat daca construim un nou vector dintr-un r-value (ex temporary, expresie de la re
	Obiectul ot nu se mai foloseste astfel se poate refolosi interiorul lui
	*/
	VectDinNewDeleteT(VectDinNewDeleteT&& ot) noexcept; //rule of 5

	/*
	Move assignment
	Similar cu move constructor
	Folosit la assignment
	*/
	VectDinNewDeleteT& operator=(VectDinNewDeleteT&& ot) noexcept; //rule of 5


	void push_back(const ElementT& el);

	void erase(int poz);


	ElementT& get(int poz) const noexcept;

	void set(int poz, const ElementT& el);

	int size() const noexcept;

	friend class IteratorVectorT <ElementT>;
	//functii care creaza iteratori
	IteratorVectorT<ElementT> begin() noexcept;
	IteratorVectorT<ElementT> end() noexcept;

	//void test_list();

};


template<typename ElementT>
void VectDinNewDeleteT<ElementT>::push_back(const ElementT& el) {
	ensureCapacity(); //daca e nevoie mai alocam memorie
	elems[lg++] = el;
}

template<typename ElementT>
void VectDinNewDeleteT<ElementT>::erase(int poz)
{
	for (int i = poz; i < lg - 1; i++)
	{
		elems[i] = elems[i + 1];
	}
	lg--;
}



template<typename ElementT>
ElementT& VectDinNewDeleteT<ElementT>::get(int poz) const noexcept {
	return elems[poz];
}

template<typename ElementT>
void VectDinNewDeleteT<ElementT>::set(int poz, const ElementT& el) {
	elems[poz] = el;
}

template<typename ElementT>
int VectDinNewDeleteT<ElementT>::size() const noexcept {
	return lg;
}

template<typename ElementT>
void VectDinNewDeleteT<ElementT>::ensureCapacity() {
	if (lg < cap) {
		return; //mai avem loc
	}
	cap *= 2;
	ElementT* aux = new ElementT[cap];
	for (int i = 0; i < lg; i++) {
		aux[i] = elems[i];
	}
	delete[] elems;
	elems = aux;
}

template<typename ElementT>
IteratorVectorT<ElementT> VectDinNewDeleteT<ElementT>::begin()  noexcept {
	return IteratorVectorT<ElementT>(*this);
}

template<typename ElementT>
IteratorVectorT<ElementT> VectDinNewDeleteT<ElementT>::end() noexcept {
	return IteratorVectorT<ElementT>(*this, lg);
}

/*
Constructor default
Alocam loc pentru 5 elemente
*/
template<typename ElementT>
VectDinNewDeleteT<ElementT>::VectDinNewDeleteT()
	:elems{ new ElementT[1] }, cap{ 1 }, lg{ 0 }
{
}

/*
Constructor de copiere
Obictul curent (this) acum se creeaza
aloca spatiu pentru elemente
copieaza elementele din ot in this
*/
template<typename ElementT>
VectDinNewDeleteT<ElementT>::VectDinNewDeleteT(const VectDinNewDeleteT<ElementT>& ot) {
	elems = new ElementT[ot.cap];
	//copiez elementele
	for (int i = 0; i < ot.lg; i++) {
		elems[i] = ot.elems[i];
	}
	lg = ot.lg;
	cap = ot.cap;
}

/*
Operator assignment
elibereaza ce era in obiectul curent (this)
aloca spatiu pentru elemente
copieaza elementele din ot in this
*/
template<typename ElementT>
VectDinNewDeleteT<ElementT>& VectDinNewDeleteT<ElementT>::operator=(const VectDinNewDeleteT& ot) {
	if (this == &ot) {
		return *this; // s-a facut l=l
	}
	delete[] elems;
	elems = new ElementT[ot.cap];
	// copiez elementele
	for (int i = 0; i < ot.lg; i++) {
		elems[i] = ot.elems[i]; // assignment din Pet
	}
	lg = ot.lg;
	cap = ot.cap;
	return *this;
}

/*
Eliberam memoria
*/
template<typename ElementT>
VectDinNewDeleteT<ElementT>::~VectDinNewDeleteT() {
	delete[] elems;
}


/*
Move constructor
Apelat daca construim un nou vector dintr-un r-value (ex temporaty)
Obiectul ot nu se mai foloseste astfel se poate refolosi interiorul lui
*/
template<typename ElementT>
VectDinNewDeleteT<ElementT>::VectDinNewDeleteT(VectDinNewDeleteT&& ot) noexcept {
	// Copy the data pointer form other
	elems = ot.elems;
	lg = ot.lg;
	cap = ot.cap;

	// Release the data pointer form the source object so that
	// the destructor does not free the memory multiple times.
	ot.elems = nullptr;
	ot.lg = 0;
	ot.cap = 0;
}

/*
Move assignment
Similar cu move constructor
Folosit la assignment
Elibereaza ce continea obictul curent (this)
"Fura" interiorul lui ot
pregateste ot pentru distrugere
*/
template<typename ElementT>
VectDinNewDeleteT<ElementT>& VectDinNewDeleteT<ElementT>::operator=(VectDinNewDeleteT&& ot)   noexcept { // ??????????
	if (this == &ot) {
		return *this;
	}
	delete[] elems;
	// Copy the data pointer from other
	elems = ot.elems;
	lg = ot.lg;
	cap = ot.cap;
	// Release the data pointer form the source object so that
	// the destructor does not free the memory multiple times.
	ot.elems = nullptr;
	ot.lg = 0;
	ot.cap = 0;
	return *this;
}


template<typename ElementT>
class IteratorVectorT {
private:
	const VectDinNewDeleteT < ElementT>& v;
	int poz = 0;

public:
	IteratorVectorT(const VectDinNewDeleteT<ElementT>& v) noexcept;
	IteratorVectorT(const VectDinNewDeleteT<ElementT>& v, int poz) noexcept;
	bool valid() const;
	ElementT& element() const noexcept;
	void next() noexcept;
	ElementT& operator*() noexcept;
	IteratorVectorT& operator++() noexcept;
	bool operator==(const IteratorVectorT& ot) noexcept;
	bool operator!=(const IteratorVectorT& ot) noexcept;
};

template<typename ElementT>
IteratorVectorT<ElementT>::IteratorVectorT(const VectDinNewDeleteT<ElementT>& v)noexcept :v{ v } {}

template<typename ElementT>
IteratorVectorT<ElementT>::IteratorVectorT(const VectDinNewDeleteT<ElementT>& v, int poz)noexcept : v{ v }, poz{ poz } {}

template<typename ElementT>
bool IteratorVectorT<ElementT>::valid() const {
	return poz < v.lg;
}

template<typename ElementT>
ElementT& IteratorVectorT<ElementT>::element() const noexcept {
	return v.elems[poz];
}

template<typename ElementT>
void IteratorVectorT<ElementT>::next()  noexcept {
	poz++;
}

template<typename ElementT>
ElementT& IteratorVectorT<ElementT>::operator*() noexcept {
	return element();
}

template<typename ElementT>
IteratorVectorT<ElementT>& IteratorVectorT<ElementT>::operator++() noexcept {
	next();
	return *this;
}

template<typename ElementT>
bool IteratorVectorT<ElementT>::operator==(const IteratorVectorT<ElementT>& ot) noexcept {
	return poz == ot.poz;
}

template<typename ElementT>
bool IteratorVectorT<ElementT>::operator!=(const IteratorVectorT<ElementT>& ot) noexcept {
	return !(*this == ot);
}


#include <iostream>
#include<cstring>
#include<stdexcept>

using namespace std;

// functiile friend in clase nu apartin clasei, si trebuie facut template pt ele separat

template<class T>
class Lista;

template<class T>
class Iterator;

/*******************************/

template<class T>
class Nod {
private:
    T info;
    Nod<T> *urm;

public:
    friend class Lista<T>;

    friend class Iterator<T>;

    template<class U>
    friend ostream &operator<<(ostream &out, const Lista<U> &L);

    Nod();

    ~Nod();

    Nod(T, Nod<T> *);

    Nod(T);

    Nod(Nod<T> &);

    Nod &operator=(const Nod<T> &x) {
        if (this != &x) {
            urm = NULL;
            info = x.info;
        }
        return *this;
    }
};

template<class T>
Nod<T>::Nod() {
    info = 0;
    urm = NULL;
}

template<class T>
Nod<T>::Nod(T x, Nod *y) {
    info = x;
    urm = y;
}

template<class T>
Nod<T>::Nod(T x) {
    info = x;
    urm = NULL;
}

template<class T>
Nod<T>::~Nod() {
    info = 0;
    urm = NULL;
}

template<class T>
Nod<T>::Nod(Nod<T> &x) {
    urm = new Nod<T>;
    urm = x.urm;
    info = x.info;
}

/*******************************/

template<class T>
class Iterator {
private:
    Nod<T> *curent;
public:

    Iterator(Nod<T> *curent = NULL) : curent(curent) {
        // #Nimic
    }

    bool operator!=(Iterator<T> x) {
        return curent != x.curent;
    }

    void increment() {
        curent = curent->urm;
    }

    T &operator*() {
        return curent->info;
    }

    Nod<T> *operator->() {
        return curent;
    }

    bool operator==(Iterator<T> x) {
        return (curent == x.curent);
    }

    Iterator<T> operator++() {
        this->increment();
        return *this;
    }

    Iterator<T> operator++(int) {
        Iterator<T> temp;
        temp = (*this);
        this->increment();
        return temp;
    }

};

/*******************************/

template<class T>
class Lista {
private:
    Nod<T> *prim;
    Nod<T> *ultim;
    Iterator<T> *curent;
public:
    friend class Nod<T>;

    Lista();  // constructor
    ~Lista(); // destructor
    Lista(Lista &);    // constructor de copiere
    Lista(int, T);

    void push_front(T);

    void push_back(T);

    void pop_back();

    void pop_front();

    void insert(T, int);

    void remove(int);

    Iterator<T> begin() { return Iterator<T>(prim); }

    Iterator<T> end() { return Iterator<T>(NULL); }

    T &operator[](int);

    operator bool() const {
        return (prim != NULL);
    }

    operator int() const {
        int k = 0;
        for (Nod<T> *q = prim; q; q = q->urm, k++);

        return k;
    }


    template<class U>
    friend ostream &operator<<(ostream &out, const Lista<U> &L) {
        Nod<T> *q;
        for (q = L.prim; q; q = q->urm)
            out << q->info << " ";
        return out;
    }

    Lista &operator=(const Lista &x) // operator = de atribuire
    {

        if (this != &x) {
            Nod<T> *q, *r;

            for (q = this->prim; q;) {
                r = q;
                q = q->urm;
                delete r;
            }

            for (q = x.prim; q; q = q->urm)
                this->push_back(q->info);
        }
        return *this;
    }
};

template<class T>
Lista<T>::Lista() {
    prim = NULL;
    ultim = NULL;
}

template<class T>
Lista<T>::~Lista() {
    // parcurg lista si sterg
    Nod<T> *q, *r;
    for (q = prim; q != NULL;) {
        r = q;
        q = q->urm;
        delete r;
    }
}

template<class T>
Lista<T>::Lista(Lista<T> &L) {
    // constuctor de copiere
    prim = ultim = NULL;
    Nod<T> *q;
    for (q = L.prim; q; q = q->urm)
        this->push_back(q->info);
}

template<class T>
void Lista<T>::push_front(T x) {

    if (prim)
        prim = new Nod<T>(x, prim);
    else {
        prim = ultim = new Nod<T>(x, prim);
        ultim->urm = NULL;
    }
}

template<class T>
void Lista<T>::pop_back() {

    if (!prim)
        throw invalid_argument("Lisa este vida, nu se poate sterge");

    Nod<T> *q;
    for (q = prim; q->urm->urm; q = q->urm);

    delete q->urm;
    q->urm = NULL;
    ultim = q;
}

template<class T>
void Lista<T>::pop_front() {

    if (!prim)
        throw invalid_argument("Lisa este vida, nu se poate sterge");

    Nod<T> *q;
    q = prim;
    prim = prim->urm;
    delete q;
}

template<class T>
void Lista<T>::insert(T val, int poz) {
    // functie care insereaza pe o pozitie o valoare
    int k = 1;
    Nod<T> *q;

    if (poz <= 0)
        throw invalid_argument("Nu se poate insera pe pozitia respectiva");
    if (poz == 1)
        this->push_front(val);
    else {
        for (q = prim; q && k != poz - 1; q = q->urm, k++);

        if (k == poz - 1 && q) {
            if (q->urm == NULL)
                this->push_back(val);
            else {
                Nod<T> *r;
                r = new Nod<T>;
                r->info = val;
                r->urm = q->urm;
                q->urm = r;
            }
        } else throw invalid_argument("Nu se poate insera pe pozitia respectiva");
    }
}

template<class T>
void Lista<T>::remove(int poz) {
    int k = 1;
    Nod<T> *q;

    if (!prim)
        throw invalid_argument("Nu se poate sterge de pe pozitia respectiva");
    if (poz <= 0)
        throw invalid_argument("Nu se poate sterge de pe pozitia respectiva");
    if (poz == 1)
        this->pop_front();
    else {

        for (q = prim; q && poz != k + 1; q = q->urm, k++);

        if (poz == k + 1 && q) {
            if (q->urm == NULL)
                throw 2;

            Nod<T> *r;
            r = q->urm;
            q->urm = q->urm->urm;
            delete r;
        } else throw invalid_argument("Nu se poate sterge de pe pozitia respectiva");
    }
}


template<class T>
Lista<T>::Lista(int nr_elem, T val) {
    prim = NULL;
    ultim = NULL;

    for (int i = 1; i <= nr_elem; i++)
        this->push_back(val);
}


template<class T>
void Lista<T>::push_back(T x) {
    if (prim) {
        Nod<T> *q;
        q = new Nod<T>;
        q->info = x;
        ultim->urm = q;
        ultim = q;
        ultim->urm = NULL;
    } else {
        prim = ultim = new Nod<T>(x, prim);
        ultim->urm = NULL;
    }
}

template<class T>
T &Lista<T>::operator[](int poz) {
    Nod<T> *q;
    int k = 1;
    for (q = prim; q && k != poz; q = q->urm, k++);

    if (poz <= 0 || !q)
        throw invalid_argument("Nu se poate accesa de pe pozitia respectiva");

    return q->info;
}

/*****************************************************************************/

template<>
class Nod<char *> {
private:
    char *info;
    Nod<char *> *urm;

public:
    friend class Lista<char *>;

    friend class Iterator<char *>;

    Nod();

    ~Nod();

    Nod(char *, Nod<char *> *);

    Nod(char *);

    Nod(Nod<char *> &);

    Nod &operator=(Nod<char *> &x) {
        if (this != &x) {
            delete[]this->info;
            urm = NULL;
            info = new char[strlen(x.info) + 1];
            strcpy(info, x.info);
        }
        return *this;
    }
};

Nod<char *>::Nod() {
    info = NULL;
    urm = NULL;
}

Nod<char *>::Nod(char *x, Nod<char *> *y) {
    info = new char[strlen(x) + 1];
    strcpy(info, x);
    urm = y->urm;
}

Nod<char *>::Nod(char *x) {
    info = new char[strlen(x) + 1];
    strcpy(info, x);
    urm = NULL;
}

Nod<char *>::~Nod() {
    delete[]info;
    urm = NULL;
}

Nod<char *>::Nod(Nod<char *> &x) {
    urm = new Nod<char *>;
    urm = x.urm;
    info = new char[strlen(x.info) + 1];
    strcpy(info, x.info);
}

template<>
class Iterator<char *> {
private:
    Nod<char *> *curent;
public:

    Iterator(Nod<char *> *curent = NULL) : curent(curent) {

    }

    bool operator!=(Iterator<char *> x) {
        return curent != x.curent;
    }

    void increment() {
        curent = curent->urm;
    }

    char *operator*() {
        return curent->info;
    }

    bool operator==(Iterator<char *> x) {
        return (curent == x.curent);
    }

    Nod<char *> *operator->() {
        return curent;
    }

    Iterator<char *> operator++() {
        this->increment();
        return curent;
    }

    Iterator<char *> operator++(int) {
        Iterator<char *> temp;
        temp = (*this);
        this->increment();
        return temp;
    }

};

template<>
class Lista<char *> {

private:
    Nod<char *> *prim;
    Nod<char *> *ultim;
    Iterator<char *> *curent;
public:

    Lista();  // constructor
    ~Lista(); // destructor
    Lista(Lista &);    // constructor de copiere
    Lista(int, char *);

    void push_front(char *);

    void push_back(char *);

    void pop_back();

    void pop_front();

    void insert(char *, int);

    void remove(int);

    Iterator<char *> begin() { return Iterator<char *>(prim); }

    Iterator<char *> end() { return Iterator<char *>(NULL); }

    char *operator[](int);

    operator bool() const {
        return (prim != NULL);
    }

    operator int() const {
        int k = 0;
        for (Nod<char *> *q = prim; q; q = q->urm, k++);

        return k;
    }

    Lista &operator=(Lista &x) // operator = de atribuire
    {

        if (this != &x) {
            Nod<char *> *q, *r;
            for (q = prim; q;) {
                r = q;
                q = q->urm;
                delete r;
            }

            for (q = x.prim; q; q = q->urm)
                this->push_back(q->info);
        }
        return *this;
    }
};


Lista<char *>::Lista() {
    prim = NULL;
    ultim = NULL;
}


Lista<char *>::~Lista() {
    // parcurg lista si sterg
    Nod<char *> *q, *r;
    for (q = prim; q != NULL;) {
        r = q;
        q = q->urm;
        delete r;
    }
}


Lista<char *>::Lista(Lista<char *> &L) {
    // constuctor de copiere
    prim = ultim = NULL;
    Nod<char *> *q;
    for (q = L.prim; q; q = q->urm)
        this->push_back(q->info);
}


void Lista<char *>::push_front(char *x) {
    if (!prim) {
        Nod<char *> *q;
        q = new Nod<char *>;

        q->info = new char[strlen(x) + 1];
        strcpy(q->info, x);

        prim = ultim = q;
        ultim->urm = NULL;
    } else {
        Nod<char *> *q;
        q = new Nod<char *>;

        q->info = new char[strlen(x) + 1];
        strcpy(q->info, x);

        q->urm = prim;
        prim = q;
    }
}


void Lista<char *>::pop_back() {

    if (!prim)
        throw invalid_argument("Nu se poate sterge de pe pozitia respectiva");;
    Nod<char *> *q;
    for (q = prim; q->urm->urm; q = q->urm);

    delete q->urm;

    q->urm = NULL;
    ultim = q;
}


void Lista<char *>::pop_front() {
    Nod<char *> *q;
    q = prim;
    prim = prim->urm;
    delete q;
}


void Lista<char *>::insert(char *val, int poz) {
    // functie care insereaza pe o pozitie o valoare
    int k = 1;
    Nod<char *> *q;

    if (poz <= 0)
        throw invalid_argument("Nu se poate insera pe pozitia respectiva");
    if (poz == 1)
        this->push_front(val);
    else {
        for (q = prim; q && k != poz - 1; q = q->urm, k++);

        if (k == poz - 1 && q) {
            if (q->urm == NULL)
                this->push_back(val);
            else {
                Nod<char *> *r;
                r = new Nod<char *>;

                r->info = new char[strlen(val) + 1];
                strcpy(r->info, val);

                r->urm = q->urm;
                q->urm = r;
            }
        } else throw invalid_argument("Nu se poate sterge de pe pozitia respectiva");
    }
}

void Lista<char *>::remove(int poz) {
    int k = 1;
    Nod<char *> *q;

    if (!prim)
        throw invalid_argument("Nu se poate sterge de pe pozitia respectiva");
    if (poz <= 0)
        throw invalid_argument("Nu se poate sterge de pe pozitia respectiva");
    if (poz == 1)
        this->pop_front();
    else {
        for (q = prim; q && poz != k + 1; q = q->urm, k++);

        if (poz == k + 1 && q) {
            if (q->urm == NULL)
                throw invalid_argument("Nu se poate sterge de pe pozitia respectiva");

            Nod<char *> *r;
            r = q->urm;
            q->urm = q->urm->urm;
            delete r;
        } else throw invalid_argument("Nu se poate sterge de pe pozitia respectiva");
    }
}


Lista<char *>::Lista(int nr_elem, char *val) {
    prim = NULL;
    ultim = NULL;

    for (int i = 1; i <= nr_elem; i++)
        this->push_back(val);
}


void Lista<char *>::push_back(char *x) {
    if (prim) {
        Nod<char *> *q;
        q = new Nod<char *>;

        q->info = new char[strlen(x) + 1];
        strcpy(q->info, x);

        ultim->urm = q;
        ultim = q;
        ultim->urm = NULL;
    } else {
        Nod<char *> *q;
        q = new Nod<char *>;

        q->info = new char[strlen(x) + 1];
        strcpy(q->info, x);

        prim = ultim = q;
        ultim->urm = NULL;
    }
}


char *Lista<char *>::operator[](int poz) {
    Nod<char *> *q;
    int k = 1;
    for (q = prim; q && k < poz; q = q->urm, k++);

    if (poz <= 0)
        throw invalid_argument("Nu se poate accesa de pe pozitia respectiva");
    if (!q)
        throw invalid_argument("Nu se poate accesa de pe pozitia respectiva");

    return q->info;
}

int main() {
    try {
        Lista<char *> l;
        l.push_front("bala");
        l.push_front("ala");
        l.push_back("portocala");

        Lista<char *> w;
        w = l;
        cout << "Lista w:\n";
        for (Iterator<char *> i = w.begin(); i != w.end(); i++)
            cout << *i << " ";

        cout << "\nLista l:\n";
        for (Iterator<char *> i = l.begin(); i != l.end(); i++)
            cout << *i << " ";

        int x = l;
        cout << "\nDimensiunea listei l este " << x << "\n";
        cout << l[2] << "\n";
        cout << l[3] << "\n";
        cout << l[1] << "\n";
        cout << l[4] << "\n";

        if (l)
            cout << "\nLista l nu este vida";
        else cout << "\nLista l este vida";

        cout << "Aceasta linie nu se executa";
        cout << "Si nici aceasta";
    }
    catch (invalid_argument &x) {
        cerr << x.what();
    }
    return 0;
}

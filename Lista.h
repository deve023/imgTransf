#ifndef _LISTA_H_
#define _LISTA_H_

#include <cstdlib>
#include <iostream>

//LISTA DOBLEMENTE ENLAZADA

template<typename T>
class Lista
{	
    private:
    
        class Nodo
    	{
    		friend class Lista;
    
    		Nodo *sig_;
    		Nodo *ant_;
    		T dato_;
    
    	public:
    		Nodo(T const&);
    		~Nodo();
    	};
    
    	Nodo *pri_;
    	Nodo *ult_;
    	size_t tam_;
    
    public:
    
        class Iterador
        {
                friend class Lista;
                
                Nodo* actual_;
                Iterador(Nodo*);
            
            public:
                Iterador();
                Iterador(const Iterador &);
                Iterador(const Lista &);
                ~Iterador();
                
                T& dato();
                const T& dato() const;
                Iterador& avanzar();
                Iterador& retroceder();
                bool extremo() const;
        };
    
    	Lista();
    	Lista(const Lista &);
    	~Lista();
    
    	size_t tamano() const;
    	bool vacia() const;
    	bool contiene(const T &) const;
    	
    	
    	//Inserta un nodo al principio de la lista
    	void insertar(const T &);
        
        //Inserta un nodo al final de la lista
        void agregar(const T &);
        
        //Elimina el i-esimo nodo, si existe
        void borrar(size_t i);
        
        //Devuelve el dato correspondiente al primer nodo de la lista.
        //Precondicion: La lista existe y no está vacía
        T& primero() const;
        


        const Lista<T> & operator = (const Lista<T> &);
    
};

template<typename T>
Lista<T>::Iterador::Iterador() : actual_(0)
{
}

template<typename T>
Lista<T>::Iterador::Iterador(Nodo* actual) : actual_(actual)
{
}

template<typename T>
Lista<T>::Iterador::Iterador(const Iterador & it) : actual_(it.actual_)
{
}

template<typename T>
Lista<T>::Iterador::Iterador(const Lista & l) : actual_(l.pri_)
{
}

template<typename T>
Lista<T>::Iterador::~Iterador()
{
}

template<typename T>
T& Lista<T>::Iterador::dato()
{
    return actual_->dato_;
}

template<typename T>
const T& Lista<T>::Iterador::dato() const
{
    return actual_->dato_;
}

template<typename T>
typename Lista<T>::Iterador& Lista<T>::Iterador::avanzar()
{
    if(actual_)
        actual_ = actual_->sig_;
        
    return *this;
}

template<typename T>
typename Lista<T>::Iterador& Lista<T>::Iterador::retroceder()
{
    if(actual_)
        actual_ = actual_->ant_;
        
    return *this;
}

template<typename T>
bool Lista<T>::Iterador::extremo() const
{
    return actual_ == 0;
}

template<typename T>
Lista<T>::Nodo::Nodo(const T &t) : sig_(0), ant_(0), dato_(t)
{
}

template<typename T>
Lista<T>::Nodo::~Nodo()
{
}

template<typename T>
Lista<T>::Lista() : pri_(0), ult_(0), tam_(0)
{
}

template<typename T>
Lista<T>::Lista(const Lista &orig) : pri_(0), ult_(0), tam_(orig.tam_)
{
	Nodo* iter = orig.pri_;
	Nodo* ant = 0;

	while(iter)
	{
		Nodo* nuevo = new Nodo(iter->dato_);
		nuevo->ant_ = ant;
		nuevo->sig_ = 0;
		if (ant != 0)
			ant->sig_ = nuevo;
		if (pri_ == 0)
			pri_ = nuevo;
		ant = nuevo;
		iter=iter->sig_;
	}
	ult_ = ant;
}

template<typename T>
Lista<T>::~Lista()
{
	for (Nodo* p = pri_; p; )
	{
		Nodo* q = p->sig_;
		delete p;
		p = q;
	}
}

template<typename T>
size_t Lista<T>::tamano() const
{
	return tam_;
}

template<typename T>
bool Lista<T>::vacia() const
{
    return pri_ == 0;
}

template<typename T>
bool Lista<T>::contiene(const T & elem) const
{
    Nodo* iter = pri_;
    while(iter)
    {
        if(iter->dato_ == elem)
            return true;
            
        iter = iter->sig_;
    }
    
    return false;
}

template<typename T>
void Lista<T>::insertar(const T & elem)
{
    Nodo* nuevo = new Nodo(elem);
    nuevo->sig_ = pri_;
    
    if(pri_)
        pri_->ant_ = nuevo;
        
    pri_ = nuevo;
    
    if(ult_ == 0)
        ult_ = nuevo;
        
    tam_++;
}

template<typename T>
void Lista<T>::agregar(const T & elem)
{
    if(pri_ == 0)
        insertar(elem);
    else
    {
        Nodo* nuevo = new Nodo(elem);
        nuevo->ant_ = ult_;
        ult_->sig_ = nuevo;
        ult_ = nuevo;
    }
    
    tam_++;
}

template<typename T>
T& Lista<T>::primero() const
{
    return pri_->dato_;
}

template<typename T>
void Lista<T>::borrar(size_t i)
{
    Nodo* iter = pri_;
    size_t pos = 0;
    while(iter!=0 && pos<i)
    {
        iter = iter->sig_;
        pos++;
    }
    
    if(iter!=0)
    {
        Nodo* anterior = iter->ant_;
        Nodo* siguiente = iter->sig_;
        delete iter;
        if(siguiente==0 && anterior ==0)
        {
            pri_ = 0;
            ult_ = 0;
        }
        if(anterior !=0)
        {
            anterior->sig_ = siguiente;
            if(siguiente == 0)
                ult_ = anterior;
        }
        if(siguiente !=0)
        {
            siguiente->ant_ = anterior;
            if(anterior == 0)
                pri_ = siguiente;
        }
        
        tam_--;
    }
}

template<typename T>
const Lista<T> & Lista<T>::operator = (const Lista<T> &orig)
{
	if(this == &orig)
		return *this;
	
    // Primero se vacia la lista;
    for (Nodo* p = pri_; p; )
    {
        Nodo* q = p->sig_;
        delete p;
        p = q;
    }

    pri_ = 0;
    ult_ = 0;
    tam_ = orig.tam_;

    Nodo* iter = orig.pri_;
    Nodo* ant = 0;

    while(iter)
    {
        Nodo* nuevo = new Nodo(iter->dato_);
        nuevo->ant_ = ant;
        nuevo->sig_ = 0;
        if (ant != 0)
            ant->sig_ = nuevo;
        if (pri_ == 0)
            pri_ = nuevo;
        ant = nuevo;
        iter=iter->sig_;
    }
    ult_ = ant;

    return *this;
}

#endif //_LISTA_H_
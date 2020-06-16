#ifndef _LISTA_H_
#define _LISTA_H_

#include <cstdlib>
#include <iostream>

//LISTA DOBLEMENTE ENLAZADA

template<typename T>
class lista
{	
    private:
    
        class nodo
    	{
    		friend class lista;
    
    		nodo *sig_;
    		nodo *ant_;
    		T dato_;
    
    	public:
    		nodo(T const&);
    		~nodo();
    	};
    
    	nodo *pri_;
    	nodo *ult_;
    	size_t tam_;
    
    public:
    
        class iterador
        {
                friend class lista;
                
                nodo* actual_;
                iterador(nodo*);
            
            public:
                iterador();
                iterador(const iterador &);
                iterador(const lista &);
                ~iterador();
                
                T& dato();
                const T& dato() const;
                iterador& avanzar();
                iterador& retroceder();
                bool extremo() const;
        };
    
    	lista();
    	lista(const lista &);
    	~lista();
    
    	size_t tamano() const;
    	bool vacia() const;
    	bool contiene(const T &) const;
    	void insertar(const T &); //inserta nodo al principio
        void agregar(const T &); //inserta nodo al final
        T& primero() const; //devuelve el dato del primer nodo
        void borrar(size_t); //borra el i-esimo nodo
        void swap_primeros2(); //intercambia los primeros dos elementos
        void imprimir() const;

        const lista<T> & operator = (const lista<T> &);
    
};

template<typename T>
lista<T>::iterador::iterador() : actual_(0)
{
}

template<typename T>
lista<T>::iterador::iterador(nodo* actual) : actual_(actual)
{
}

template<typename T>
lista<T>::iterador::iterador(const iterador & it) : actual_(it.actual_)
{
}

template<typename T>
lista<T>::iterador::iterador(const lista & l) : actual_(l.pri_)
{
}

template<typename T>
lista<T>::iterador::~iterador()
{
}

template<typename T>
T& lista<T>::iterador::dato()
{
    return actual_->dato_;
}

template<typename T>
const T& lista<T>::iterador::dato() const
{
    return actual_->dato_;
}

template<typename T>
typename lista<T>::iterador& lista<T>::iterador::avanzar()
{
    if(actual_)
        actual_ = actual_->sig_;
        
    return *this;
}

template<typename T>
typename lista<T>::iterador& lista<T>::iterador::retroceder()
{
    if(actual_)
        actual_ = actual_->ant_;
        
    return *this;
}

template<typename T>
bool lista<T>::iterador::extremo() const
{
    return actual_ == 0;
}

template<typename T>
lista<T>::nodo::nodo(const T &t) : sig_(0), ant_(0), dato_(t)
{
}

template<typename T>
lista<T>::nodo::~nodo()
{
}

template<typename T>
lista<T>::lista() : pri_(0), ult_(0), tam_(0)
{
}

template<typename T>
lista<T>::lista(const lista &orig) : pri_(0), ult_(0), tam_(orig.tam_)
{
	nodo* iter = orig.pri_;
	nodo* ant = 0;

	while(iter)
	{
		nodo* nuevo = new nodo(iter->dato_);
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
lista<T>::~lista()
{
	for (nodo* p = pri_; p; )
	{
		nodo* q = p->sig_;
		delete p;
		p = q;
	}
}

template<typename T>
size_t lista<T>::tamano() const
{
	return tam_;
}

template<typename T>
bool lista<T>::vacia() const
{
    return pri_ == 0;
}

template<typename T>
bool lista<T>::contiene(const T & elem) const
{
    nodo* iter = pri_;
    while(iter)
    {
        if(iter->dato_ == elem)
            return true;
            
        iter = iter->sig_;
    }
    
    return false;
}

template<typename T>
void lista<T>::insertar(const T & elem)
{
    nodo* nuevo = new nodo(elem);
    nuevo->sig_ = pri_;
    
    if(pri_)
        pri_->ant_ = nuevo;
        
    pri_ = nuevo;
    
    if(ult_ == 0)
        ult_ = nuevo;
        
    tam_++;
}

template<typename T>
void lista<T>::agregar(const T & elem)
{
    if(pri_ == 0)
        insertar(elem);
    else
    {
        nodo* nuevo = new nodo(elem);
        nuevo->ant_ = ult_;
        ult_->sig_ = nuevo;
        ult_ = nuevo;
    }
    
    tam_++;
}

template<typename T>
T& lista<T>::primero() const
{
    return pri_->dato_;
}

template<typename T>
void lista<T>::borrar(size_t i)
{
    nodo* iter = pri_;
    size_t pos = 0;
    while(iter!=0 && pos<i)
    {
        iter = iter->sig_;
        pos++;
    }
    
    if(iter!=0)
    {
        nodo* anterior = iter->ant_;
        nodo* siguiente = iter->sig_;
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
void lista<T>::swap_primeros2()
{
    if(tam_>=2)
    {
        T aux = pri_->dato_;
        pri_->dato_ = pri_->sig_->dato_;
        pri_->sig_->dato_ = aux;
    }
}


template<typename T>
void lista<T>::imprimir() const
{
    lista<T>::iterador iter(pri_);
    if(!vacia())
    {
        while(!iter.extremo())
        {
            std::cout<<iter.dato()<<" ";
            iter.avanzar();
        }
    }
    else
    {
        std::cout<<"lista vacia";
    }
    std::cout<<std::endl;
}

template<typename T>
const lista<T> & lista<T>::operator = (const lista<T> &orig)
{
    // Primero se vacia la lista;
    for (nodo* p = pri_; p; )
    {
        nodo* q = p->sig_;
        delete p;
        p = q;
    }

    pri_ = 0;
    ult_ = 0;
    tam_ = orig.tam_;

    nodo* iter = orig.pri_;
    nodo* ant = 0;

    while(iter)
    {
        nodo* nuevo = new nodo(iter->dato_);
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
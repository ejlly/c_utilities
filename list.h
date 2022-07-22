#ifndef MA_LISTE_PERSONNELLE
#define MA_LISTE_PERSONNELLE

template<typename T>
class Intermediate_list{
	public:
		T *elem;
		Intermediate_list *next;
		int length;

		inline Intermediate_list<T>(){
			elem = NULL;
			next = NULL;
			length = 0;
		}

		inline Intermediate_list<T>(T n){
			elem = new T(n);
			next = new Intermediate_list();
			length = 1;
		}

		inline Intermediate_list<T>(T n, Intermediate_list<T> *next_ptr){
			elem = new T(n);
			next = next_ptr;
			length = 1 + (next_ptr->length);
		}

		inline T operator[](int index){
			if(index < 0 || index >= length){
				throw std::out_of_range("Index out of range");
			}
			Intermediate_list *cur = this;
			int i = 0;
			while((i++ != index) && (cur = cur->next)){}

			return *(cur->elem);
		}

};

/*
template<typename T>
inline void print_intermediate(Intermediate_list<T> *l){
	std::cout << "[";
	for(Intermediate_list<T> *cur = l; cur->elem != NULL; cur = cur->next){
		std::cout << *(cur->elem);
		if(cur->next->elem != NULL) std::cout << " , ";
	}
	std::cout << "]\n";
}
*/

template<typename T>
inline void push_intermediate(Intermediate_list<T> **l_ptr, T new_elem){
	Intermediate_list<T> *new_head = new Intermediate_list<T>(new_elem, *l_ptr);
	*l_ptr = new_head;
}

template<typename T>
inline T pop_intermediate(Intermediate_list<T> **l_ptr){
	if((*l_ptr)->length == 0){
		throw std::length_error("Empty list");
	}
	
	T const a = *((*l_ptr)->elem);
	delete (*l_ptr)->elem;

	Intermediate_list<T> const *list_ptr = *l_ptr;
	*l_ptr = (*l_ptr)->next;
	delete list_ptr;

	return a;
}

template<typename T>
class List{

	private:
		Intermediate_list<T> *list;
	
	public:
		inline List<T>(){
			list = new Intermediate_list<T>();
		} 
	
		inline List<T>(T n){
			list = new Intermediate_list<T>(n);
		}
		
		inline List<T>(T n, List<T> *next){
			list = new Intermediate_list<T>(n, &(next->list));
		}
	
		inline int length(){
			return list->length;
		}

		inline void push(T n){
			push_intermediate(&list, n);
		}
		
		inline void affiche(){
			print_intermediate(list);
		}

		inline T pop(){
			return pop_intermediate(&list);
		}
	
		inline T operator[](int n){
			return (*list)[n];
		}

		inline friend std::ostream& operator<<(std::ostream& flux, List<T>& liste){
			flux << "[";
			for(Intermediate_list<T> *cur = liste.list; cur->elem != NULL; cur = cur->next){
				flux << *(cur->elem);
				if(cur->next->elem != NULL) flux << " , ";
			}
			flux << "]";
			return flux;
		}
};


#endif

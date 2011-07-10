template <typename ReturnType>
struct Functor { 
	public:
		virtual ReturnType operator()(void)=0;
};

template <typename T, typename ReturnType>
struct Functor_impl : public Functor<ReturnType> {
	private:
		T* wrapped_object;
	public:
		ReturnType operator()(void) {
			return (wrapped_object->operator())();
		}

		T* get_wrapped() {
			return wrapped_object;
		}

		Functor_impl(T* object) : wrapped_object(object) { }
};

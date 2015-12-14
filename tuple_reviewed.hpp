//tuple_reviewed.hpp

namespace MySpace
{
	template<int N, class... Ts> 
	struct tuple_data;

	template<int N>
	struct tuple_data<N>{};

	template<int N, class Thead, class... Tbody>
	struct tuple_data<N, Thead, Tbody...> : public tuple_data<N + 1, Tbody...>
	{
		Thead value;
	};

	template<int N, class Thead,class... Tbody>
	Thead& get_tuple_data(tuple_data<N, Thead, Tbody...>& _t)
	{
		return _t.value;
	}

	template<class... Ts>
	struct tuple : tuple_data<0, Ts...>
	{
		static constexpr std::size_t size(void){return sizeof...(Ts);}
	};

	template<int N, class... Ts>
	auto get(tuple<Ts...>& _t) ->decltype(get_tuple_data<N>(_t))
	{
		return get_tuple_data<N>(_t);
	}
}

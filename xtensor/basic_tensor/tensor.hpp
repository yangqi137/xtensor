#ifndef XTENSOR_BASIC_TENSOR_TENSOR_HPP
#define XTENSOR_BASIC_TENSOR_TENSOR_HPP

namespace xtensor { namespace basic {
    template <typename VALUE, unsigned RANK,
	      typename STORAGE = unbounded_array<VALUE> >
    class Tensor {
    public:
      typedef VALUE value_type;
      const static unsigned rank = RANK;
      typedef STORAGE storage_type;
      typedef typename storage_type::size_type size_type;
      typedef Tensor<value_type, rank, storage_type> self_type;
      typedef value_type& reference;
      typedef const value_type& const_reference;

    public:
      Tensor() {}

      template <typename... Args>
      explicit Tensor(size_type d0, Args... args)
	: dims{d0, args...} {
	static_assert(sizeof...(args)+1 == rank, 
		      "# of arguments must equal to the rank");
	//impl_::ReadIndices(dims, d0, args...);
	storage.resize(impl_::GetSize(dims));
      }

      template <typename... Args>
      Tensor(storage_type&& stor_, size_type d0, Args... args)
	: storage(stor_), dims{d0, args...} {
	static_assert(sizeof...(args)+1 == rank, 
		      "# of arguments must equal to the rank");
	//impl_::ReadIndices(dims, d0, args...);
	storage.resize(impl_::GetSize(dims));
      }

      template <typename... Args>
      value_type& at(Args... args) {
	static_assert(sizeof...(args) == rank,
		      "# of arguments must equal to the rank");
	return storage.at(impl_::GetIdx({args...}, dims));
      }
      
      private:
	std::array<size_type, rank> dims;
	array_type storage;
    };
    
  }
}
#endif

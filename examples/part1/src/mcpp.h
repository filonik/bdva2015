#ifndef GLUE_INTERNALS_MCPP_HPP
#define GLUE_INTERNALS_MCPP_HPP

extern "C"
{
#if defined(OUT)
#undef OUT
#endif
#include <mcpp_lib.h>
}

namespace mcpp {
namespace detail {

template<typename T, std::size_t size>
std::size_t array_size(T(&)[size])
{
    return size;
}

inline int process(int argc, char* argv[], char** out = nullptr, char** err = nullptr)
{
    mcpp_use_mem_buffers(1);
    
    //char const* argv[]{ "mcpp", "-P", path, /* "-D", "LOL", "-I", "/data/..." */  };
    //int retval = mcpp_lib_main(array_size(argv), const_cast<char**>(argv));
    
	int retval = mcpp_lib_main(argc, argv);

    if (out != nullptr)
    {
        *out = mcpp_get_mem_buffer(OUT);
    }
    
    if (err != nullptr)
    {
        *err = mcpp_get_mem_buffer(ERR);
    }
    
    return retval;
}

}

inline std::tuple<std::string, std::string> process(std::string const& path, const std::vector<std::string>& arguments = {})
{
    char* out;
    char* err;
    
	auto argv = std::vector<const char*>{"mcpp", "-P", "-a", path.c_str()};
	for (auto& argument : arguments) { argv.push_back(argument.c_str()); }

	if (detail::process(argv.size(), const_cast<char**>(argv.data()), &out, &err) != 0)
    {
        throw std::runtime_error("Failed to preprocess file.");
    }
    
	auto _out = std::string{ out == nullptr ? "" : out };
	auto _err = std::string{ err == nullptr ? "" : err };

	return std::make_tuple(_out, _err);
}

}

#endif
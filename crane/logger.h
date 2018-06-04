#ifndef CRANE_LOGGER_H_
#define CRANE_LOGGER_H_

#include <string>
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <mutex> 

using namespace std;

#define USE_LOGGING			1
#define STD_OUTPUT			1
#define LOG_FILE			"crane.log"

class log_policy_interface
{
public:
	virtual void		open_ostream(const std::string& name) = 0;
	virtual void		close_ostream() = 0;
	virtual void		write(const std::string& msg) = 0;

};

/*
* Implementation which allow to write into a file
*/

class file_log_policy : public log_policy_interface
{
	std::unique_ptr< std::ofstream > out_stream;
public:
	file_log_policy() : out_stream(new std::ofstream) {}
	void open_ostream(const std::string& name);
	void close_ostream();
	void write(const std::string& msg);
	~file_log_policy();
};


enum severity_type
{
	debug = 1,
	error,
	warning
};



template< typename log_policy >
class logger
{
	unsigned log_line_number;
	std::string get_time();
	std::string get_logline_header();
	std::stringstream log_stream;
	log_policy* policy;
	std::mutex write_mutex;

	//Core printing functionality
	void print_impl();
	template<typename First, typename...Rest>
	void print_impl(First parm1, Rest...parm);
public:
	logger(const std::string& name);

	template< severity_type severity, typename...Args >
	void print(Args...args);

	~logger();
};


template< typename log_policy >
logger< log_policy >::logger(const std::string& name)
{
	log_line_number = 0;
	policy = new log_policy;
	if (!policy)
	{
		throw std::runtime_error("LOGGER: Unable to create the logger instance");
	}
	policy->open_ostream(name);
}

template< typename log_policy >
template< severity_type severity, typename...Args >
void logger< log_policy >::print(Args...args)
{
	write_mutex.lock();
	switch (severity)
	{
	case severity_type::debug:
		log_stream << "<DEBUG>   :";
		break;
	case severity_type::warning:
		log_stream << "<WARNING> :";
		break;
	case severity_type::error:
		log_stream << "<ERROR>   :";
		break;
	};
	print_impl(args...);
	write_mutex.unlock();
}

template< typename log_policy >
logger< log_policy >::~logger()
{
	if (policy)
	{
		policy->close_ostream();
		delete policy;
	}
}


template< typename log_policy >
void logger< log_policy >::print_impl()
{
#if STD_OUTPUT
	cout << log_stream.str() << endl;
#endif // STD_OUTPUT

	string line = get_logline_header() + log_stream.str();
	policy->write(line);
	log_stream.str("");
}

template< typename log_policy >
template<typename First, typename...Rest >
void logger< log_policy >::print_impl(First parm1, Rest...parm)
{
	log_stream << parm1;
	print_impl(parm...);
}

template< typename log_policy >
std::string logger< log_policy >::get_time()
{
	time_t raw_time;

	time(&raw_time);

	struct tm *time_info = localtime(&raw_time);

	char buffer[80];
	strftime(buffer, 80, "%F %X", time_info);
	std::string time_str(buffer);

	return time_str;
}

template< typename log_policy >
std::string logger< log_policy >::get_logline_header()
{
	std::stringstream header;

	header.str("");
	header.fill('0');
	header.width(7);
	header << log_line_number++ << " | " << get_time() << " ";

	header.fill('0');
	header.width(7);
	header << clock() << " | ";

	return header.str();
}

extern logger< file_log_policy > log_inst;

#if USE_LOGGING
#define LOG log_inst.print< severity_type::debug >
#define LOG_ERR log_inst.print< severity_type::error >
#define LOG_WARN log_inst.print< severity_type::warning >
#else
#define LOG(...) 
#define LOG_ERR(...)
#define LOG_WARN(...)
#endif


#endif //!CRANE_LOGGER_H_


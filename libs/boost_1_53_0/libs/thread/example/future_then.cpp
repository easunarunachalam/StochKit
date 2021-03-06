// Copyright (C) 2012 Vicente Botet
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//#define BOOST_THREAD_VERSION 4
//#define BOOST_THREAD_USES_LOG
#define BOOST_THREAD_USES_LOG_THREAD_ID
//#define BOOST_THREAD_DONT_PROVIDE_FUTURE_INVALID_AFTER_GET

#include <boost/thread/detail/log.hpp>
#include <boost/thread/future.hpp>
#include <boost/assert.hpp>
#include <string>
#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION

int p1()
{
  BOOST_THREAD_LOG << "P1" << BOOST_THREAD_END_LOG;
  return 123;
}

int p2(boost::future<int>& f)
{
  BOOST_THREAD_LOG << "<P2" << BOOST_THREAD_END_LOG;
  try
  {
    return 2 * f.get();
  }
  catch (std::exception& ex)
  {
    BOOST_THREAD_LOG << "ERRORRRRR "<<ex.what() << "" << BOOST_THREAD_END_LOG;
    BOOST_ASSERT(false);
  }
  catch (...)
  {
    BOOST_THREAD_LOG << " ERRORRRRR exception thrown" << BOOST_THREAD_END_LOG;
    BOOST_ASSERT(false);
  }
  BOOST_THREAD_LOG << "P2>" << BOOST_THREAD_END_LOG;
}

int main()
{
  BOOST_THREAD_LOG << "<MAIN" << BOOST_THREAD_END_LOG;
  try
  {
    boost::future<int> f1 = boost::async(&p1);
    BOOST_THREAD_LOG <<  BOOST_THREAD_END_LOG;
    boost::future<int> f2 = f1.then(&p2);
    BOOST_THREAD_LOG << BOOST_THREAD_END_LOG;
    BOOST_THREAD_LOG << f2.get() << BOOST_THREAD_END_LOG;
  }
  catch (std::exception& ex)
  {
    BOOST_THREAD_LOG << "ERRORRRRR "<<ex.what() << "" << BOOST_THREAD_END_LOG;
    return 1;
  }
  catch (...)
  {
    BOOST_THREAD_LOG << " ERRORRRRR exception thrown" << BOOST_THREAD_END_LOG;
    return 2;
  }
  BOOST_THREAD_LOG << "MAIN>" << BOOST_THREAD_END_LOG;
  return 0;
}
#else

int main()
{
  return 0;
}
#endif

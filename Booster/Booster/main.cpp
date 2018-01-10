//
//  main.cpp
//  Booster
//
//  Created by Ruchir Patel on 10/01/18.
//  Copyright © 2018 Ruchir Patel. All rights reserved.
//

#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

int main()
{
    boost::asio::io_context io;
    
    boost::asio::deadline_timer t(io, boost::posix_time::seconds(5));
    t.wait();
    
    std::cout << "Hello, world! #Ruchir" << std::endl;
    
    return 0;
}

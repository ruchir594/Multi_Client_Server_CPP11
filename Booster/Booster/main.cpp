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
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>


class printer
{
public:
    printer(boost::asio::io_context& io)
    : strand_(io),
      timer1_(io, boost::posix_time::seconds(1)),
      timer2_(io, boost::posix_time::seconds(1)),
      count_(0)
    {
        timer1_.async_wait(boost::asio::bind_executor(strand_, boost::bind(&printer::print1, this)));
        timer2_.async_wait(boost::asio::bind_executor(strand_, boost::bind(&printer::print2, this)));
        
    }
    ~printer()
    {
        std::cout<<"object is destroyed"<<std::endl;
    }
    void print1()
    {
        if (count_ < 5){
            std::cout <<"count timer1 " <<count_<<std::endl;
            ++count_;
            
            timer1_.expires_at(timer1_.expires_at() + boost::posix_time::seconds(1));
            timer2_.async_wait(boost::asio::bind_executor(strand_, boost::bind(&printer::print2, this)));
        }
    }
    void print2()
    {
        if (count_ < 5){
            std::cout <<"count timer2 " <<count_<<std::endl;
            ++count_;
            timer2_.expires_at(timer2_.expires_at() + boost::posix_time::seconds(1));
            timer1_.async_wait(boost::asio::bind_executor(strand_, boost::bind(&printer::print1, this)));
        }
    }
private:
    boost::asio::deadline_timer timer1_, timer2_;
    boost::asio::io_context::strand strand_;
    int count_;
};



int main()
{
    boost::asio::io_context io;
    printer p(io);
    boost::thread t(boost::bind(&boost::asio::io_context::run, &io));
    io.run();
    t.join();
    return 0;
}

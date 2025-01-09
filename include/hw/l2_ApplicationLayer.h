/* 
MIT License 

Copyright (c) 2019 МГТУ им. Н.Э. Баумана, кафедра ИУ-6, Михаил Фетисов, 

Программа-заготовка для домашнего задания
*/

#ifndef HW_L2_APPLICATION_LAYER_H
#define HW_L2_APPLICATION_LAYER_H

#include <string>

#include "tp/Task_interface.h"

#include "l3_DomainLayer.h"

class IOutput
{
public:
    virtual ~IOutput() = default;

    virtual void Output(std::string s) const = 0;
};

class Application : public tp::Task_interface
{
public:
    Application() = delete;
    Application(const Application &) = delete;

    Application & operator=(const Application &) = delete;

    Application(ItemCollector & col, const std::string & command, const IOutput & out)
        : _col(col)
        , _command(command)
        , _out(out)
    {}

    // bool performCommand(const std::vector<std::string> & args);

    virtual void work() override;
private:
     ItemCollector & _col;
    std::string     _command;
    const IOutput & _out;

    std::vector<std::string> split(const std::string & str);
};

#endif // HW_L2_APPLICATION_LAYER_H

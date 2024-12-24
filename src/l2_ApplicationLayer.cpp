/* Программа-заготовка для домашнего задания
*/

#include "hw/l2_ApplicationLayer.h"

using namespace std;

inline const string DATA_DEFAULT_NAME = "lab.data";

bool Application::performCommand(const vector<string> & args)
{
    if (args.empty())
        return false;

    if (args[0] == "l" || args[0] == "load")
    {
        string filename = (args.size() == 1) ? DATA_DEFAULT_NAME : args[1];

        if (!_col.loadCollection(filename))
        {
            _out.Output("Ошибка при загрузке файла '" + filename + "'");
            return false;
        }

        return true;
    }

    if (args[0] == "s" || args[0] == "save")
    {
        string filename = (args.size() == 1) ? DATA_DEFAULT_NAME : args[1];

        if (!_col.saveCollection(filename))
        {
            _out.Output("Ошибка при сохранении файла '" + filename + "'");
            return false;
        }

        return true;
    }

    if (args[0] == "c" || args[0] == "clean")
    {
        if (args.size() != 1)
        {
            _out.Output("Некорректное количество аргументов команды clean");
            return false;
        }

        _col.clean();

        return true;
    }

    if (args[0] == "a" || args[0] == "add")
    {
        if (args.size() != 7)
        {
            _out.Output("Некорректное количество аргументов команды add");
            return false;
        }

        _col.addItem(make_shared<DeviceApp>(args[1].c_str(), args[2].c_str(), stoul(args[3]), stoul(args[4]), stoul(args[5]), stoul(args[6])));
        return true;
    }


    if (args[0] == "ao" || args[0] == "add_order")
    {
        if (args.size() != 5)
        {
            _out.Output("Некорректное количество аргументов команды add_order");
            return false;
        }

        Buyer & b = _col.getBuyerRef(stoul(args[1]));

        vector<Order> o = b.getCart();
        o.push_back(Order(stod(args[2]),stod(args[3]),stod(args[4])));
        b.setCart(o);

        return true;
    }

    if (args[0] == "r" || args[0] == "remove")
    {
        if (args.size() != 2)
        {
            _out.Output("Некорректное количество аргументов команды remove");
            return false;
        }

        _col.removeItem(stoul(args[1]));
        return true;
    }

    if (args[0] == "u" || args[0] == "update")
    {
        if (args.size() != 8)
        {
            _out.Output("Некорректное количество аргументов команды update");
            return false;
        }

        _col.updateItem(stoul(args[1]), make_shared<DeviceApp>(args[2].c_str(), args[3].c_str(), stoul(args[4]), stoul(args[5]), stoul(args[6]), stoul(args[7])));
        return true;
    }

    if (args[0] == "v" || args[0] == "view")
    {
        if (args.size() != 1)
        {
            _out.Output("Некорректное количество аргументов команды view");
            return false;
        }

        size_t count = 0;
        for(size_t i=0; i < _col.getSize(); ++i)
        {
            const DeviceApp & item = static_cast<DeviceApp &>(*_col.getItem(i));

            if (!_col.isRemoved(i))
            {
                _out.Output("[" + to_string(i) + "] "
                        + item.getAppName() + " "
                        + item.getCategory() + " "
                        + to_string(item.getAppCost()) + "$ "
                        + to_string(item.getAppSize()) + "MB "
                        + to_string(item.getInstallingNum()) + " "
                        + to_string(item.getEvaluation()) + "/5"
                    );
                count ++;
            }
        }

        _out.Output("Количество элементов в коллекции: " + to_string(count));
        return true;
    }

    _out.Output("Недопустимая команда '" + args[0] + "'");
    return false;
}

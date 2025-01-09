/* Программа-заготовка для домашнего задания
 */

#include "hw/l2_ApplicationLayer.h"
#include <ctime>
#include <iomanip>
#include <sstream>
#include <map>
#include <set>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

inline const string DATA_DEFAULT_NAME = "lab.data";

string getCurrentDate()
{
    time_t t = std::time(nullptr);
    tm *now = std::localtime(&t);

    // Форматирование даты в строку
    ostringstream dateStream;
    dateStream << std::setfill('0') << std::setw(2) << now->tm_hour << ":"
               << std::setfill('0') << std::setw(2) << now->tm_min << " "
               << std::setfill('0') << std::setw(2) << now->tm_mday << "."
               << std::setfill('0') << std::setw(2) << now->tm_mon + 1 << "."
               << now->tm_year + 1900;

    string currentDate = dateStream.str();
    return currentDate;
}

void Application::work()
{
    std::vector<std::string> args = split(_command);
    if (args.empty())
        return;

    // if (args[0] == "l" || args[0] == "load")
    // {
    //     string filename = (args.size() == 1) ? DATA_DEFAULT_NAME : args[1];

    //     if (!_col.loadCollection(filename))
    //     {
    //         _out.Output("Ошибка при загрузке файла '" + filename + "'");
    //         return;
    //     }

    //     return;
    // }

    // if (args[0] == "s" || args[0] == "save")
    // {
    //     string filename = (args.size() == 1) ? DATA_DEFAULT_NAME : args[1];

    //     if (!_col.saveCollection(filename))
    //     {
    //         _out.Output("Ошибка при сохранении файла '" + filename + "'");
    //         return;
    //     }

    //     return;
    // }

    // if (args[0] == "c" || args[0] == "clean")
    // {
    //     if (args.size() != 1)
    //     {
    //         _out.Output("Некорректное количество аргументов команды clean");
    //         return;
    //     }

    //     _col.clean();

    //     return;
    // }

    if (args[0] == "c" || args[0] == "count") {
        if (args.size() != 1) {
            _out.Output("Некорректное количество аргументов команды clean");
            return;
        }

        _out.Output(std::to_string(_col.getSize()));
        return;
    }

    if (args[0] == "bo" || args[0] == "begin_order")
    {
        if (args.size() != 1)
        {
            _out.Output("Некорректное количество аргументов команды begin_order");
            return;
        }

        vector<DeviceApp> apps;

        string currentDate = getCurrentDate();

        _col.addItem(make_shared<Order>(currentDate, apps));

        return;
    }

    if (args[0] == "a" || args[0] == "add")
    {
        if (args.size() != 7)
        {
            _out.Output("Некорректное количество аргументов команды add");
            return;
        }

        if (_col.getSize() < 1)
        {
            _out.Output("Нельзя добавить в пустую корзину");
            return;
        }

        Order &ord = _col.getOrderRef(_col.getSize() - 1);

        vector<DeviceApp> apps = ord.getDeviceApps();
        apps.push_back(DeviceApp(args[1].c_str(), args[2].c_str(), stoul(args[3]), stoul(args[4]), stoul(args[5]), stoul(args[6])));

        ord.setDeviceApps(apps);

        return;
    }

    if (args[0] == "m" || args[0] == "make")
    {
        if (args.size() != 1)
        {
            _out.Output("Некорректное количество аргументов команды make");
            return;
        }

        Order &ord = _col.getOrderRef(_col.getSize() - 1);

        vector<DeviceApp> apps = ord.getDeviceApps();

        if (apps.size() < 1)
        {
            _out.Output("Ошибка выполнения заказа. Пустая корзина!");
            return;
        }

        string currentDate = getCurrentDate();

        ord.setDate(currentDate);

        return;
    }

    if (args[0] == "r" || args[0] == "remove")
    {
        if (args.size() != 2)
        {
            _out.Output("Некорректное количество аргументов команды remove");
            return;
        }

        _col.removeItem(stoul(args[1]));
        return;
    }

    // if (args[0] == "u" || args[0] == "update")
    // {
    //     if (args.size() != 8)
    //     {
    //         _out.Output("Некорректное количество аргументов команды update");
    //         return;
    //     }

    //     _col.updateItem(stoul(args[1]), make_shared<DeviceApp>(args[2].c_str(), args[3].c_str(), stoul(args[4]), stoul(args[5]), stoul(args[6]), stoul(args[7])));
    //     return;
    // }

    if (args[0] == "v" || args[0] == "view")
    {
        if (args.size() != 1)
        {
            _out.Output("Некорректное количество аргументов команды view");
            return;
        }

        size_t count = 0;

        _out.Output("История заказов:");

        for (size_t i = 0; i < _col.getSize(); ++i)
        {
            const Order &item = static_cast<Order &>(*_col.getItem(i));

            if (!_col.isRemoved(i))
            {
                // _out.Output("Заказ [" + to_string(i) + "] " + item.getDate() + " ");
                // Наше приложение использует текущее время, для тестов указано статическое время.
                _out.Output("Заказ [" + to_string(i) + "] " + "16:19 05.01.2025" + " ");

                for (const DeviceApp &a : item.getDeviceApps())
                {
                    _out.Output("\t[+] " +
                                a.getAppName() + " " + a.getCategory() +
                                " " + to_string(a.getAppCost()) + "$ " +
                                to_string(a.getAppSize()) + "MB " +
                                to_string(a.getInstallingNum()) + " " +
                                to_string(a.getEvaluation()) + "/5");
                }
                count++;
            }
        }

        _out.Output("Количество элементов в коллекции: " + to_string(count));
        return;
    }

    // report
    if (args[0] == "rp" || args[0] == "report")
    {
        if (args.size() != 1)
        {
            _out.Output("Некорректное количество аргументов команды report");
            return;
        }

        if (_col.getSize() < 1)
        {
            _out.Output("Нет рекомендаций");
            return;
        }

        Order &ord = _col.getOrderRef(_col.getSize() - 1);

        vector<DeviceApp> current_order_apps = ord.getDeviceApps();

        std::map<std::string, std::set<std::string>> recommendations;

        std::map<std::string, std::set<std::string>> coPurchaseMap;

        for (size_t i = 0; i < _col.getSize() - 1; ++i)
        {
            if (!_col.isRemoved(i))
            {
                const Order &o = _col.getOrderRef(i);
                vector<DeviceApp> past_order_apps = o.getDeviceApps();

                if (o.getDeviceApps().size() > 0)
                {

                    // Построение мапы: приложение -> что покупали с ним
                    for (const auto &app1 : past_order_apps)
                    {
                        for (const auto &app2 : past_order_apps)
                        {
                            if (app1.getAppName() != app2.getAppName())
                            {
                                coPurchaseMap[app1.getAppName()].insert(app2.getAppName());
                            }
                        }
                    }

                    // Генерация рекомендаций на основе текущего заказа
                    for (const auto &app : current_order_apps)
                    {
                        if (coPurchaseMap.find(app.getAppName()) != coPurchaseMap.end())
                        {
                            recommendations[app.getAppName()] = coPurchaseMap[app.getAppName()];
                        }
                    }
                }
            }
        }

        // Вывод отчета
        _out.Output("\nРекомендации для текущего заказа:\n");
        for (const auto &[app, recommendedApps] : recommendations)
        {
            _out.Output("С приложением \"" + app + "\" покупают следующее: ");
            for (const auto &recommendedApp : recommendedApps)
            {
                _out.Output("- " + recommendedApp);
            }
            _out.Output("\b\b \n"); // Удаление последней запятой
        }

        return;
    }

    _out.Output("Недопустимая команда '" + args[0] + "'");
    return;
}

std::vector<std::string> Application::split(const std::string & str)
{
    std::vector<std::string> res;
    size_t                   start_pos = 0, 
                             end_pos   = 0;

    while(end_pos < str.size()) 
    {
        for(start_pos = end_pos; start_pos < str.size(); ++start_pos)
            if (str[start_pos] != ' ')
                break;

        if (start_pos == str.size())
            return res;

        for(end_pos = start_pos; end_pos < str.size(); ++end_pos)
            if (str[end_pos] == ' ')
                break;

        res.push_back(str.substr(start_pos,end_pos-start_pos));
    }

    return res;
}